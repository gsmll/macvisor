/* Recreated from kernelcache.arm64.kc (XNU, arm64e, image base fffffe0007004000) —
 * the kernel-side SPTM (GL2) / TXM (GL0) / SK (GL3) client interface. Ground
 * truth: Ghidra FUN_ names + addresses; public API names and SPTM_FUNCTIONID_*
 * endpoint ids from docs/sptm/headers/sptm_common.h + sptm_xnu.h (Apple's own
 * headers). Each sptm_* client wrapper is a tiny GENTER stub: it calls the
 * pre-entry hook, loads the SPTM dispatch id into x16, executes the GENTER
 * opcode, calls the post-exit hook, and returns. Confidence is high for every
 * entry (endpoint ids read directly from the stub disassembly and equal
 * SPTM_FUNCTIONID_*). */

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

/* GENTER (0x00201420) / GEXIT (0x00201400) — the only instruction that crosses
 * into a guarded (ring -1) level. Rendered opaque. The dispatch endpoint is
 * selected by the value in x16. */
#define GENTER() __asm__ volatile(".long 0x00201420" ::: "memory")
#define GEXIT()  __asm__ volatile(".long 0x00201400" ::: "memory")

/* ------------------------------------------------------------------ *
 * Dispatch-id encoding (mirrors docs/sptm/headers/sptm_common.h).
 *
 *   x16 = (domain << 48) | (dispatch_table << 32) | endpoint
 * ------------------------------------------------------------------ */

#define DOMAIN_ID_SHIFT       48
#define DISPATCH_TABLE_ID_SHIFT 32
#define ENDPOINT_ID_SHIFT     0
#define BUILD_DISPATCH_ID(domain, table, endpoint) \
	(((uint64_t)(domain) << DOMAIN_ID_SHIFT) | \
	 ((uint64_t)(table)  << DISPATCH_TABLE_ID_SHIFT) | \
	 ((uint64_t)(endpoint) << ENDPOINT_ID_SHIFT))

/* Domain ids (SPTM_DOMAIN is the guarded level the XNU client enters). */
#define SPTM_DOMAIN 0U
#define XNU_DOMAIN  1U
#define TXM_DOMAIN  2U
#define SK_DOMAIN   3U

/* Dispatch-table id used by the sptm_* client wrappers. */
#define SPTM_DISPATCH_TABLE_XNU_BOOTSTRAP 0

/* SPTM client endpoint ids (SPTM_FUNCTIONID_* from sptm_xnu.h). */
#define SPTM_FUNCTIONID_LOCKDOWN                  0
#define SPTM_FUNCTIONID_RETYPE                    1
#define SPTM_FUNCTIONID_MAP_PAGE                  2
#define SPTM_FUNCTIONID_MAP_TABLE                 3
#define SPTM_FUNCTIONID_UNMAP_TABLE               4
#define SPTM_FUNCTIONID_UPDATE_REGION             5
#define SPTM_FUNCTIONID_UPDATE_DISJOINT           6
#define SPTM_FUNCTIONID_UNMAP_REGION              7
#define SPTM_FUNCTIONID_UNMAP_DISJOINT            8
#define SPTM_FUNCTIONID_CONFIGURE_SHAREDREGION    9
#define SPTM_FUNCTIONID_NEST_REGION               10
#define SPTM_FUNCTIONID_UNNEST_REGION             11
#define SPTM_FUNCTIONID_CONFIGURE_ROOT            12
#define SPTM_FUNCTIONID_SWITCH_ROOT               13
#define SPTM_FUNCTIONID_REGISTER_CPU              14
#define SPTM_FUNCTIONID_FIXUPS_COMPLETE           15
#define SPTM_FUNCTIONID_SIGN_USER_POINTER         16
#define SPTM_FUNCTIONID_AUTH_USER_POINTER         17
#define SPTM_FUNCTIONID_REGISTER_EXC_RETURN       18
#define SPTM_FUNCTIONID_CPU_ID                    19
#define SPTM_FUNCTIONID_SLIDE_REGION              20
#define SPTM_FUNCTIONID_UPDATE_DISJOINT_MULTIPAGE 21
#define SPTM_FUNCTIONID_REG_READ                  22
#define SPTM_FUNCTIONID_REG_WRITE                 23
#define SPTM_FUNCTIONID_GUEST_VA_TO_IPA           24
#define SPTM_FUNCTIONID_GUEST_STAGE1_TLBOP        25
#define SPTM_FUNCTIONID_GUEST_STAGE2_TLBOP        26
#define SPTM_FUNCTIONID_GUEST_DISPATCH            27
#define SPTM_FUNCTIONID_GUEST_EXIT                28
#define SPTM_FUNCTIONID_MAP_SK_DOMAIN             29
#define SPTM_FUNCTIONID_HIB_BEGIN                 30
#define SPTM_FUNCTIONID_HIB_VERIFY_HASH_NON_WIRED 31
#define SPTM_FUNCTIONID_HIB_FINALIZE_NON_WIRED    32
#define SPTM_FUNCTIONID_IOFILTER_PROTECTED_WRITE  33
#define SPTM_FUNCTIONID_SPTM_SYSCTL               37
#define SPTM_FUNCTIONID_DISABLE_KERNEL_MODE_CPA2  38
#define SPTM_FUNCTIONID_SET_SHARED_REGION         39
#define SPTM_FUNCTIONID_BATCH_SIGN_USER_POINTER   40
#define SPTM_FUNCTIONID_SURT_ALLOC                41
#define SPTM_FUNCTIONID_SURT_FREE                 42
#define SPTM_FUNCTIONID_CONDEMN_LEAF_TABLE        43
#define SPTM_FUNCTIONID_UNCONDEMN_LEAF_TABLE      44
#define SPTM_FUNCTIONID_SPTM_SERIAL_PUTC          45
#define SPTM_FUNCTIONID_SPTM_SERIAL_DISABLE       46
#define SPTM_FUNCTIONID_PROGRAM_IRGKEY            48
#define SPTM_FUNCTIONID_REG_SNAPSHOT              49

/* Arguments for a domain-specific call, passed to a GEN_DOMAIN_ENTRY_STUB
 * stub. Mirrors sptm_call_regs_t in sptm_common.h (field offsets hard-coded in
 * the stub-generating assembly macro). */
typedef struct {
	uint64_t x0;
	uint64_t x1;
	uint64_t x2;
	uint64_t x3;
	uint64_t x4;
	uint64_t x5;
	uint64_t x6;
	uint64_t x7;
} sptm_call_regs_t;

/* ------------------------------------------------------------------ *
 * Shared kernel-side hooks and helpers (owned by the hypervisor / other
 * kernel trees; referenced here as externs).
 * ------------------------------------------------------------------ */

/* FUN_fffffe000b75e8e8 — _sptm_pre_entry_hook: increments a per-CPU enter
 * counter at tpidr_el1+0x1c0, then spins on a system register read (pre-entry
 * sync). Must preserve x0-x7 (the SPTM arguments) across the call. Declared
 * weak per sptm_xnu.h. */
extern void _sptm_pre_entry_hook(void);

/* FUN_fffffe000b75e954 — _sptm_post_exit_hook: decrements the per-CPU enter
 * counter; on underflow calls hv_el2_preemption_panic. */
extern void _sptm_post_exit_hook(void);

/* Kernel lock / panic / trace helpers referenced by txm_enter (kernel tree,
 * recreated in the hypervisor audit files). */
extern void lck_mtx_lock(void *lock, void *thread, uint64_t old, uint32_t flags); /* FUN_fffffe000b7f0afc */
extern void lck_mtx_unlock(void *lock, void *thread);                              /* FUN_fffffe000b7f1e80 */
extern uint64_t lck_mtx_lock_wait(void *lock, uint32_t action, void *event, uint64_t); /* FUN_fffffe000b7f9088 */
extern void hv_flush_lock_op(void *lock, void *cond, uint64_t, uint64_t, uint64_t);    /* FUN_fffffe000b8563f8 */
extern void kernel_printf(const char *fmt, ...);                                   /* FUN_fffffe000bf72568 */
extern void kernel_panic_msg_fmt(const char *fmt, ...) __attribute__((noreturn));  /* FUN_fffffe000c0e11ec */

/* ------------------------------------------------------------------ *
 * Common GENTER-dispatch body for the sptm_* client wrappers.
 *
 * Each XNU-table client stub executes:
 *     pacibsp; stp x29,x30,[sp,#-0x10]!; mov x29,sp
 *     bl  _sptm_pre_entry_hook
 *     mov x16, #<endpoint>          (+ movk x16,#<table>,LSL#32 for non-XNU)
 *     genter                         0x20 14 20 00
 *     bl  _sptm_post_exit_hook
 *     mov sp,x29; ldp x29,x30,[sp],#0x10; retab
 *
 * domain (SPTM_DOMAIN=0) and table (XNU_BOOTSTRAP=0) are both zero for every
 * sptm_* wrapper, so the dispatch id equals the endpoint. The caller's
 * arguments pass through x0-x7 untouched to the SPTM endpoint.
 * ------------------------------------------------------------------ */
#define SPTM_XNU_ENTER(endpoint)                                        \
	do {                                                                \
		_sptm_pre_entry_hook();                                         \
		/* x16 := BUILD_DISPATCH_ID(SPTM_DOMAIN, XNU_BOOTSTRAP, endpt) */ \
		__asm__ volatile("mov x16, #" #endpoint ::: "x16");             \
		GENTER(); /* enters SPTM (GL2); endpoint selected by x16 */     \
		_sptm_post_exit_hook();                                         \
	} while (0)

/* Same as SPTM_XNU_ENTER but without the pre/post hooks: used by the
 * hypervisor guest-entry id-loaders (endpoints 24-28), which are bare
 * `pacibsp; mov x16,#id; genter; retab` (12 bytes, no frame, no hooks). */
#define SPTM_XNU_ENTER_NO_HOOK(endpoint)                                \
	do {                                                                \
		__asm__ volatile("mov x16, #" #endpoint ::: "x16");             \
		GENTER(); /* enters SPTM (GL2); endpoint selected by x16 */     \
	} while (0)

/* ================================================================== *
 * sptm_* XNU client wrappers — dispatch table 0
 * (SPTM_DISPATCH_TABLE_XNU_BOOTSTRAP, endpoint = SPTM_FUNCTIONID_*).
 * ================================================================== */

/* FUN_fffffe000c0d83c0 @ 0xfffffe000c0d83c0   (sptm_lockdown)
 * Ghidra: FUN_fffffe000c0d83c0(void) -> calls FUN_fffffe000b75e8e8 (the
 *   pre-entry hook); the GENTER opcode truncates the decompile.
 * Locks down the SPTM (endpoint 0). Once lockdown completes the SPTM no
 * longer accepts further structural requests.
 * Confidence: high  Notes: `mov x16,#0x0` @ 0xfffffe000c0d83d0; GENTER @
 *   0xfffffe000c0d83d4. */
uint64_t
sptm_lockdown(void)
{
	SPTM_XNU_ENTER(SPTM_FUNCTIONID_LOCKDOWN);
	return 0;
}

/* FUN_fffffe000c0d83e8 @ 0xfffffe000c0d83e8   (sptm_retype)
 * Ghidra: FUN_fffffe000c0d83e8(void)
 * Retypes a frame to a new SPTM frame type (endpoint 1). x1-x7 carry the
 * retype parameters.
 * Confidence: high  Notes: `mov x16,#0x1` @ 0xfffffe000c0d83f8; GENTER @
 *   0xfffffe000c0d83fc. */
uint64_t
sptm_retype(void)
{
	SPTM_XNU_ENTER(SPTM_FUNCTIONID_RETYPE);
	return 0;
}

/* FUN_fffffe000c0d8410 @ 0xfffffe000c0d8410   (sptm_map_page)
 * Ghidra: FUN_fffffe000c0d8410(void)
 * Maps a single page (endpoint 2); the previous PTE and PTE VA are returned
 * in the per-CPU scratch page unless SPTM_MAP_PAGE_NO_OUTPUT is set.
 * Confidence: high  Notes: `mov x16,#0x2` @ 0xfffffe000c0d8420; GENTER @
 *   0xfffffe000c0d8424. */
uint64_t
sptm_map_page(void)
{
	SPTM_XNU_ENTER(SPTM_FUNCTIONID_MAP_PAGE);
	return 0;
}

/* FUN_fffffe000c0d8438 @ 0xfffffe000c0d8438   (sptm_map_table)
 * Ghidra: FUN_fffffe000c0d8438(void)
 * Maps a page-table frame (endpoint 3).
 * Confidence: high  Notes: `mov x16,#0x3` @ 0xfffffe000c0d8448; GENTER @
 *   0xfffffe000c0d844c. */
uint64_t
sptm_map_table(void)
{
	SPTM_XNU_ENTER(SPTM_FUNCTIONID_MAP_TABLE);
	return 0;
}

/* FUN_fffffe000c0d8460 @ 0xfffffe000c0d8460   (sptm_unmap_table)
 * Ghidra: FUN_fffffe000c0d8460(void)
 * Unmaps a page-table frame (endpoint 4).
 * Confidence: high  Notes: `mov x16,#0x4` @ 0xfffffe000c0d8470; GENTER @
 *   0xfffffe000c0d8474. */
uint64_t
sptm_unmap_table(void)
{
	SPTM_XNU_ENTER(SPTM_FUNCTIONID_UNMAP_TABLE);
	return 0;
}

/* FUN_fffffe000c0d8488 @ 0xfffffe000c0d8488   (sptm_update_region)
 * Ghidra: FUN_fffffe000c0d8488(void)
 * Updates a mapped region's permissions (endpoint 5).
 * Confidence: high  Notes: `mov x16,#0x5` @ 0xfffffe000c0d8498; GENTER @
 *   0xfffffe000c0d849c. */
uint64_t
sptm_update_region(void)
{
	SPTM_XNU_ENTER(SPTM_FUNCTIONID_UPDATE_REGION);
	return 0;
}

/* FUN_fffffe000c0d84b0 @ 0xfffffe000c0d84b0   (sptm_update_disjoint)
 * Ghidra: FUN_fffffe000c0d84b0(void)
 * Updates a disjoint (non-contiguous) region's permissions (endpoint 6).
 * Confidence: high  Notes: `mov x16,#0x6` @ 0xfffffe000c0d84c0; GENTER @
 *   0xfffffe000c0d84c4. */
uint64_t
sptm_update_disjoint(void)
{
	SPTM_XNU_ENTER(SPTM_FUNCTIONID_UPDATE_DISJOINT);
	return 0;
}

/* FUN_fffffe000c0d84d8 @ 0xfffffe000c0d84d8   (sptm_unmap_region)
 * Ghidra: FUN_fffffe000c0d84d8(void)
 * Unmaps a region (endpoint 7).
 * Confidence: high  Notes: `mov x16,#0x7` @ 0xfffffe000c0d84e8; GENTER @
 *   0xfffffe000c0d84ec. */
uint64_t
sptm_unmap_region(void)
{
	SPTM_XNU_ENTER(SPTM_FUNCTIONID_UNMAP_REGION);
	return 0;
}

/* FUN_fffffe000c0d8500 @ 0xfffffe000c0d8500   (sptm_unmap_disjoint)
 * Ghidra: FUN_fffffe000c0d8500(void)
 * Unmaps a disjoint region (endpoint 8).
 * Confidence: high  Notes: `mov x16,#0x8` @ 0xfffffe000c0d8510; GENTER @
 *   0xfffffe000c0d8514. */
uint64_t
sptm_unmap_disjoint(void)
{
	SPTM_XNU_ENTER(SPTM_FUNCTIONID_UNMAP_DISJOINT);
	return 0;
}

/* FUN_fffffe000c0d8528 @ 0xfffffe000c0d8528   (sptm_configure_sharedregion)
 * Ghidra: FUN_fffffe000c0d8528(void)
 * Configures the shared (commpage) region (endpoint 9).
 * Confidence: high  Notes: `mov x16,#0x9` @ 0xfffffe000c0d8538; GENTER @
 *   0xfffffe000c0d853c. */
uint64_t
sptm_configure_sharedregion(void)
{
	SPTM_XNU_ENTER(SPTM_FUNCTIONID_CONFIGURE_SHAREDREGION);
	return 0;
}

/* FUN_fffffe000c0d8578 @ 0xfffffe000c0d8578   (sptm_nest_region)
 * Ghidra: FUN_fffffe000c0d8578(void)
 * Nests one region into another (endpoint 10).
 * Confidence: high  Notes: `mov x16,#0xa` @ 0xfffffe000c0d8588; GENTER @
 *   0xfffffe000c0d858c. */
uint64_t
sptm_nest_region(void)
{
	SPTM_XNU_ENTER(SPTM_FUNCTIONID_NEST_REGION);
	return 0;
}

/* FUN_fffffe000c0d85a0 @ 0xfffffe000c0d85a0   (sptm_unnest_region)
 * Ghidra: FUN_fffffe000c0d85a0(void)
 * Removes a nested region (endpoint 11).
 * Confidence: high  Notes: `mov x16,#0xb` @ 0xfffffe000c0d85b0; GENTER @
 *   0xfffffe000c0d85b4. */
uint64_t
sptm_unnest_region(void)
{
	SPTM_XNU_ENTER(SPTM_FUNCTIONID_UNNEST_REGION);
	return 0;
}

/* FUN_fffffe000c0d85c8 @ 0xfffffe000c0d85c8   (sptm_configure_root)
 * Ghidra: FUN_fffffe000c0d85c8(void)
 * Configures a root page table (endpoint 12).
 * Confidence: high  Notes: `mov x16,#0xc` @ 0xfffffe000c0d85d8; GENTER @
 *   0xfffffe000c0d85dc. */
uint64_t
sptm_configure_root(void)
{
	SPTM_XNU_ENTER(SPTM_FUNCTIONID_CONFIGURE_ROOT);
	return 0;
}

/* FUN_fffffe000c0d85f0 @ 0xfffffe000c0d85f0   (sptm_switch_root)
 * Ghidra: FUN_fffffe000c0d85f0(void)
 * Switches the active root page table (endpoint 13).
 * Confidence: high  Notes: `mov x16,#0xd` @ 0xfffffe000c0d8600; GENTER @
 *   0xfffffe000c0d8604. */
uint64_t
sptm_switch_root(void)
{
	SPTM_XNU_ENTER(SPTM_FUNCTIONID_SWITCH_ROOT);
	return 0;
}

/* FUN_fffffe000c0d8618 @ 0xfffffe000c0d8618   (sptm_register_cpu)
 * Ghidra: FUN_fffffe000c0d8618(void)
 * Registers a logical CPU with the SPTM (endpoint 14).
 * Confidence: high  Notes: `mov x16,#0xe` @ 0xfffffe000c0d8628 (verified);
 *   GENTER @ 0xfffffe000c0d862c. */
uint64_t
sptm_register_cpu(void)
{
	SPTM_XNU_ENTER(SPTM_FUNCTIONID_REGISTER_CPU);
	return 0;
}

/* FUN_fffffe000c0d8668 @ 0xfffffe000c0d8668   (sptm_init_xnu_fixups_complete)
 * Ghidra: FUN_fffffe000c0d8668(void)
 * Signals that XNU's page-table fixups are complete (endpoint 15).
 * Confidence: high  Notes: `mov x16,#0xf` @ 0xfffffe000c0d867c; GENTER @
 *   0xfffffe000c0d8680. */
uint64_t
sptm_init_xnu_fixups_complete(void)
{
	SPTM_XNU_ENTER(SPTM_FUNCTIONID_FIXUPS_COMPLETE);
	return 0;
}

/* FUN_fffffe000c0d87a8 @ 0xfffffe000c0d87a8   (sptm_sign_user_pointer)
 * Ghidra: FUN_fffffe000c0d87a8(void)
 * Signs a user pointer for the SPTM's PAC scheme (endpoint 16).
 * Confidence: high  Notes: `mov x16,#0x10` @ 0xfffffe000c0d87b8; GENTER @
 *   0xfffffe000c0d87bc. */
uint64_t
sptm_sign_user_pointer(void)
{
	SPTM_XNU_ENTER(SPTM_FUNCTIONID_SIGN_USER_POINTER);
	return 0;
}

/* FUN_fffffe000c0d87d0 @ 0xfffffe000c0d87d0   (sptm_auth_user_pointer)
 * Ghidra: FUN_fffffe000c0d87d0(void)
 * Authenticates a user pointer (endpoint 17).
 * Confidence: high  Notes: `mov x16,#0x11` @ 0xfffffe000c0d87e0; GENTER @
 *   0xfffffe000c0d87e4. */
uint64_t
sptm_auth_user_pointer(void)
{
	SPTM_XNU_ENTER(SPTM_FUNCTIONID_AUTH_USER_POINTER);
	return 0;
}

/* FUN_fffffe000c0d87f8 @ 0xfffffe000c0d87f8   (sptm_register_exc_return)
 * Ghidra: FUN_fffffe000c0d87f8(void)
 * Registers an exception-return vector with the SPTM (endpoint 18).
 * Confidence: high  Notes: `mov x16,#0x12` @ 0xfffffe000c0d8808; GENTER @
 *   0xfffffe000c0d880c. */
uint64_t
sptm_register_exc_return(void)
{
	SPTM_XNU_ENTER(SPTM_FUNCTIONID_REGISTER_EXC_RETURN);
	return 0;
}

/* FUN_fffffe000c0d8820 @ 0xfffffe000c0d8820   (sptm_cpu_id)
 * Ghidra: FUN_fffffe000c0d8820(void)
 * Queries the SPTM's CPU id (endpoint 19).
 * Confidence: high  Notes: `mov x16,#0x13` @ 0xfffffe000c0d8830; GENTER @
 *   0xfffffe000c0d8834. */
uint64_t
sptm_cpu_id(void)
{
	SPTM_XNU_ENTER(SPTM_FUNCTIONID_CPU_ID);
	return 0;
}

/* FUN_fffffe000c0d8640 @ 0xfffffe000c0d8640   (sptm_slide_region)
 * Ghidra: FUN_fffffe000c0d8640(void)
 * Slides a region (endpoint 20) — used for KASLR region relocation.
 * Confidence: high  Notes: `mov x16,#0x14` @ 0xfffffe000c0d8650; GENTER @
 *   0xfffffe000c0d8654. */
uint64_t
sptm_slide_region(void)
{
	SPTM_XNU_ENTER(SPTM_FUNCTIONID_SLIDE_REGION);
	return 0;
}

/* FUN_fffffe000c0d8848 @ 0xfffffe000c0d8848   (sptm_update_disjoint_multipage)
 * Ghidra: FUN_fffffe000c0d8848(void)
 * Updates a disjoint region spanning multiple pages (endpoint 21).
 * Confidence: high  Notes: `mov x16,#0x15` @ 0xfffffe000c0d8858; GENTER @
 *   0xfffffe000c0d885c. */
uint64_t
sptm_update_disjoint_multipage(void)
{
	SPTM_XNU_ENTER(SPTM_FUNCTIONID_UPDATE_DISJOINT_MULTIPAGE);
	return 0;
}

/* FUN_fffffe000c0d88e8 @ 0xfffffe000c0d88e8   (sptm_reg_read)
 * Ghidra: FUN_fffffe000c0d88e8(void)
 * Reads a protected SPTM system register (endpoint 22).
 * Confidence: high  Notes: `mov x16,#0x16` @ 0xfffffe000c0d88f8; GENTER @
 *   0xfffffe000c0d88fc. */
uint64_t
sptm_reg_read(void)
{
	SPTM_XNU_ENTER(SPTM_FUNCTIONID_REG_READ);
	return 0;
}

/* FUN_fffffe000c0d8910 @ 0xfffffe000c0d8910   (sptm_reg_write)
 * Ghidra: FUN_fffffe000c0d8910(void)
 * Writes a protected SPTM system register (endpoint 23).
 * Confidence: high  Notes: `mov x16,#0x17` @ 0xfffffe000c0d8920; GENTER @
 *   0xfffffe000c0d8924. */
uint64_t
sptm_reg_write(void)
{
	SPTM_XNU_ENTER(SPTM_FUNCTIONID_REG_WRITE);
	return 0;
}

/* FUN_fffffe000c0d8a00 @ 0xfffffe000c0d8a00   (sptm_map_sk_domain)
 * Ghidra: FUN_fffffe000c0d8a00(void)
 * Maps all SK_DOMAIN (GL3) pages into the PAPT so XNU can read them for
 * on-device coredump (endpoint 29). Development/DEBUG only.
 * Confidence: high  Notes: `mov x16,#0x1d` @ 0xfffffe000c0d8a10 (verified);
 *   GENTER @ 0xfffffe000c0d8a14. */
uint64_t
sptm_map_sk_domain(void)
{
	SPTM_XNU_ENTER(SPTM_FUNCTIONID_MAP_SK_DOMAIN);
	return 0;
}

/* FUN_fffffe000c0d8a28 @ 0xfffffe000c0d8a28   (sptm_hib_begin)
 * Ghidra: FUN_fffffe000c0d8a28(void)
 * Begins the hibernation (HIB) sequence in the SPTM (endpoint 30).
 * Confidence: high  Notes: `mov x16,#0x1e` @ 0xfffffe000c0d8a38; GENTER @
 *   0xfffffe000c0d8a3c. */
uint64_t
sptm_hib_begin(void)
{
	SPTM_XNU_ENTER(SPTM_FUNCTIONID_HIB_BEGIN);
	return 0;
}

/* FUN_fffffe000c0d8a50 @ 0xfffffe000c0d8a50   (sptm_hib_verify_hash_non_wired)
 * Ghidra: FUN_fffffe000c0d8a50(void)
 * Verifies a hibernation image hash in non-wired memory (endpoint 31).
 * Confidence: high  Notes: `mov x16,#0x1f` @ 0xfffffe000c0d8a60; GENTER @
 *   0xfffffe000c0d8a64. */
uint64_t
sptm_hib_verify_hash_non_wired(void)
{
	SPTM_XNU_ENTER(SPTM_FUNCTIONID_HIB_VERIFY_HASH_NON_WIRED);
	return 0;
}

/* FUN_fffffe000c0d8a78 @ 0xfffffe000c0d8a78   (sptm_hib_finalize_non_wired)
 * Ghidra: FUN_fffffe000c0d8a78(void)
 * Finalizes the hibernation image in non-wired memory (endpoint 32).
 * Confidence: high  Notes: `mov x16,#0x20` @ 0xfffffe000c0d8a88; GENTER @
 *   0xfffffe000c0d8a8c. */
uint64_t
sptm_hib_finalize_non_wired(void)
{
	SPTM_XNU_ENTER(SPTM_FUNCTIONID_HIB_FINALIZE_NON_WIRED);
	return 0;
}

/* FUN_fffffe000c0d8870 @ 0xfffffe000c0d8870   (sptm_iofilter_protected_write)
 * Ghidra: FUN_fffffe000c0d8870(void)
 * Performs a protected I/O filter write (endpoint 33).
 * Confidence: high  Notes: `mov x16,#0x21` @ 0xfffffe000c0d8880; GENTER @
 *   0xfffffe000c0d8884. */
uint64_t
sptm_iofilter_protected_write(void)
{
	SPTM_XNU_ENTER(SPTM_FUNCTIONID_IOFILTER_PROTECTED_WRITE);
	return 0;
}

/* FUN_fffffe000c0d8960 @ 0xfffffe000c0d8960   (sptm_sysctl)
 * Ghidra: FUN_fffffe000c0d8960(void)
 * SPTM sysctl entry point (endpoint 37; set/get of e.g.
 * SPTM_SYSCTL_DISARM_PROTECTED_IO).
 * Confidence: high  Notes: `mov x16,#0x25` @ 0xfffffe000c0d8970 (verified);
 *   GENTER @ 0xfffffe000c0d8974. */
uint64_t
sptm_sysctl(void)
{
	SPTM_XNU_ENTER(SPTM_FUNCTIONID_SPTM_SYSCTL);
	return 0;
}

/* FUN_fffffe000c0d8690 @ 0xfffffe000c0d8690   (sptm_disable_kernel_mode_cpa2)
 * Ghidra: FUN_fffffe000c0d8690(void)
 * Disables kernel-mode CPA2 (endpoint 38).
 * Confidence: high  Notes: `mov x16,#0x26` @ 0xfffffe000c0d86a0; GENTER @
 *   0xfffffe000c0d86a4. */
uint64_t
sptm_disable_kernel_mode_cpa2(void)
{
	SPTM_XNU_ENTER(SPTM_FUNCTIONID_DISABLE_KERNEL_MODE_CPA2);
	return 0;
}

/* FUN_fffffe000c0d8550 @ 0xfffffe000c0d8550   (sptm_set_shared_region)
 * Ghidra: FUN_fffffe000c0d8550(void)
 * Sets the shared-region descriptor (endpoint 39).
 * Confidence: high  Notes: `mov x16,#0x27` @ 0xfffffe000c0d8560; GENTER @
 *   0xfffffe000c0d8564. */
uint64_t
sptm_set_shared_region(void)
{
	SPTM_XNU_ENTER(SPTM_FUNCTIONID_SET_SHARED_REGION);
	return 0;
}

/* FUN_fffffe000c0d8988 @ 0xfffffe000c0d8988   (sptm_batch_sign_user_pointer)
 * Ghidra: FUN_fffffe000c0d8988(void)
 * Signs a batch of user pointers (endpoint 40).
 * Confidence: high  Notes: `mov x16,#0x28` @ 0xfffffe000c0d8998; GENTER @
 *   0xfffffe000c0d899c. */
uint64_t
sptm_batch_sign_user_pointer(void)
{
	SPTM_XNU_ENTER(SPTM_FUNCTIONID_BATCH_SIGN_USER_POINTER);
	return 0;
}

/* FUN_fffffe000c0d86b8 @ 0xfffffe000c0d86b8   (sptm_surt_alloc)
 * Ghidra: FUN_fffffe000c0d86b8(void)
 * Allocates a subpage user root table (SURT) (endpoint 41).
 * Confidence: high  Notes: `mov x16,#0x29` @ 0xfffffe000c0d86c8; GENTER @
 *   0xfffffe000c0d86cc. */
uint64_t
sptm_surt_alloc(void)
{
	SPTM_XNU_ENTER(SPTM_FUNCTIONID_SURT_ALLOC);
	return 0;
}

/* FUN_fffffe000c0d86e0 @ 0xfffffe000c0d86e0   (sptm_surt_free)
 * Ghidra: FUN_fffffe000c0d86e0(void)
 * Frees a subpage user root table (SURT) (endpoint 42).
 * Confidence: high  Notes: `mov x16,#0x2a` @ 0xfffffe000c0d86f0; GENTER @
 *   0xfffffe000c0d86f4. */
uint64_t
sptm_surt_free(void)
{
	SPTM_XNU_ENTER(SPTM_FUNCTIONID_SURT_FREE);
	return 0;
}

/* FUN_fffffe000c0d89b0 @ 0xfffffe000c0d89b0   (sptm_condemn_leaf_table)
 * Ghidra: FUN_fffffe000c0d89b0(void)
 * Condemns a leaf page-table frame (endpoint 43).
 * Confidence: high  Notes: `mov x16,#0x2b` @ 0xfffffe000c0d89c0; GENTER @
 *   0xfffffe000c0d89c4. */
uint64_t
sptm_condemn_leaf_table(void)
{
	SPTM_XNU_ENTER(SPTM_FUNCTIONID_CONDEMN_LEAF_TABLE);
	return 0;
}

/* FUN_fffffe000c0d89d8 @ 0xfffffe000c0d89d8   (sptm_uncondemn_leaf_table)
 * Ghidra: FUN_fffffe000c0d89d8(void)
 * Un-condemns a leaf page-table frame (endpoint 44).
 * Confidence: high  Notes: `mov x16,#0x2c` @ 0xfffffe000c0d89e8; GENTER @
 *   0xfffffe000c0d89ec. */
uint64_t
sptm_uncondemn_leaf_table(void)
{
	SPTM_XNU_ENTER(SPTM_FUNCTIONID_UNCONDEMN_LEAF_TABLE);
	return 0;
}

/* FUN_fffffe000c0d8708 @ 0xfffffe000c0d8708   (sptm_serial_putc)
 * Ghidra: FUN_fffffe000c0d8708(void)
 * Sends a single character to the SPTM's debug serial port (endpoint 45).
 * Confidence: high  Notes: `mov x16,#0x2d` @ 0xfffffe000c0d8718 (verified);
 *   GENTER @ 0xfffffe000c0d871c. */
uint64_t
sptm_serial_putc(void)
{
	SPTM_XNU_ENTER(SPTM_FUNCTIONID_SPTM_SERIAL_PUTC);
	return 0;
}

/* FUN_fffffe000c0d8730 @ 0xfffffe000c0d8730   (sptm_serial_disable)
 * Ghidra: FUN_fffffe000c0d8730(void)
 * Disables the SPTM's debug serial port (endpoint 46).
 * Confidence: high  Notes: `mov x16,#0x2e` @ 0xfffffe000c0d8740; GENTER @
 *   0xfffffe000c0d8744. */
uint64_t
sptm_serial_disable(void)
{
	SPTM_XNU_ENTER(SPTM_FUNCTIONID_SPTM_SERIAL_DISABLE);
	return 0;
}

/* FUN_fffffe000c0d8758 @ 0xfffffe000c0d8758   (sptm_program_irgkey)
 * Ghidra: FUN_fffffe000c0d8758(void)
 * Programs an IRG key (endpoint 48).
 * Confidence: high  Notes: `mov x16,#0x30` @ 0xfffffe000c0d8768 (verified);
 *   GENTER @ 0xfffffe000c0d876c. */
uint64_t
sptm_program_irgkey(void)
{
	SPTM_XNU_ENTER(SPTM_FUNCTIONID_PROGRAM_IRGKEY);
	return 0;
}

/* FUN_fffffe000c0d8938 @ 0xfffffe000c0d8938   (sptm_reg_snapshot)
 * Ghidra: FUN_fffffe000c0d8938(void)
 * Takes a snapshot of the SPTM's protected register state (endpoint 49).
 * Confidence: high  Notes: `mov x16,#0x31` @ 0xfffffe000c0d8948 (verified);
 *   GENTER @ 0xfffffe000c0d894c. */
uint64_t
sptm_reg_snapshot(void)
{
	SPTM_XNU_ENTER(SPTM_FUNCTIONID_REG_SNAPSHOT);
	return 0;
}

/* ================================================================== *
 * Guest dispatch id-loaders (endpoints 24-28) — used by the EL2
 * hypervisor guest-exit path in osfmk/arm64/hypervisor/hv_el2.c.
 * These are bare `pacibsp; mov x16,#id; genter; retab` (no pre/post
 * hooks, no frame). x0-x7 carry the guest/EL2 arguments to the SPTM.
 * ================================================================== */

/* FUN_fffffe000c0d993c @ 0xfffffe000c0d993c   (sptm_guest_va_to_ipa)
 * Ghidra: FUN_fffffe000c0d993c(void)
 * Translates a guest VA to an IPA through the SPTM's stage-2 tables
 * (endpoint 24). Called from hv_el2_guest_fault (0xfffffe000b967768).
 * Confidence: high  Notes: `mov x16,#0x18` @ 0xfffffe000c0d9940 (verified);
 *   GENTER @ 0xfffffe000c0d9944. */
uint64_t
sptm_guest_va_to_ipa(void)
{
	SPTM_XNU_ENTER_NO_HOOK(SPTM_FUNCTIONID_GUEST_VA_TO_IPA);
	return 0;
}

/* FUN_fffffe000c0d994c @ 0xfffffe000c0d994c   (sptm_guest_stage1_tlb_op)
 * Ghidra: FUN_fffffe000c0d994c(void)
 * Issues a stage-1 TLB operation for a guest (endpoint 25).
 * Confidence: high  Notes: `mov x16,#0x19` @ 0xfffffe000c0d9950 (verified);
 *   GENTER @ 0xfffffe000c0d9954. */
uint64_t
sptm_guest_stage1_tlb_op(void)
{
	SPTM_XNU_ENTER_NO_HOOK(SPTM_FUNCTIONID_GUEST_STAGE1_TLBOP);
	return 0;
}

/* FUN_fffffe000c0d995c @ 0xfffffe000c0d995c   (sptm_guest_stage2_tlb_op)
 * Ghidra: FUN_fffffe000c0d995c(void)
 * Issues a stage-2 TLB operation for a guest (endpoint 26).
 * Confidence: high  Notes: `mov x16,#0x1a` @ 0xfffffe000c0d9960; GENTER @
 *   0xfffffe000c0d9964. */
uint64_t
sptm_guest_stage2_tlb_op(void)
{
	SPTM_XNU_ENTER_NO_HOOK(SPTM_FUNCTIONID_GUEST_STAGE2_TLBOP);
	return 0;
}

/* FUN_fffffe000c0d996c @ 0xfffffe000c0d996c   (sptm_guest_exit)
 * Ghidra: FUN_fffffe000c0d996c(void)
 * Signals a guest exit to the SPTM (endpoint 28).
 * Confidence: high  Notes: `mov x16,#0x1c` @ 0xfffffe000c0d9970 (verified);
 *   GENTER @ 0xfffffe000c0d9974. */
uint64_t
sptm_guest_exit(void)
{
	SPTM_XNU_ENTER_NO_HOOK(SPTM_FUNCTIONID_GUEST_EXIT);
	return 0;
}

/* FUN_fffffe000c0d997c @ 0xfffffe000c0d997c   (sptm_guest_dispatch)
 * Ghidra: FUN_fffffe000c0d997c(void)
 * Dispatches a guest entry into the SPTM's guest handling (endpoint 27).
 * Called from FUN_fffffe000b953e14 (the hypervisor guest-entry hub).
 * Confidence: high  Notes: `mov x16,#0x1b` @ 0xfffffe000c0d9980 (verified);
 *   GENTER @ 0xfffffe000c0d9984. */
uint64_t
sptm_guest_dispatch(void)
{
	SPTM_XNU_ENTER_NO_HOOK(SPTM_FUNCTIONID_GUEST_DISPATCH);
	return 0;
}

/* ================================================================== *
 * Generic domain-entry genter cores (SK and TXM).
 *
 * These parameterize the dispatch id with a runtime endpoint id in w0:
 *     pacibsp
 *     mov  w16, w0            ; endpoint id
 *     movk x16, #<domain>, LSL #48
 *     mov  x10, x1            ; sptm_call_regs_t *
 *     ldp  x0, x1, [x10]
 *     ldp  x2, x3, [x10, #0x10]
 *     ldp  x4, x5, [x10, #0x20]
 *     ldp  x6, x7, [x10, #0x30]
 *     genter
 *     retab
 * so x16 = (domain << 48) | endpoint, and the call args are loaded from the
 * sptm_call_regs_t (x0=x0..x7=x7). Decompiler fails here (GENTER opcode);
 * reconstructed from disassembly. Confidence: high.
 * ================================================================== */

/* FUN_fffffe000c0d7948 @ 0xfffffe000c0d7948   (sk_enter genter core)
 * Enters the SK domain (GL3): dispatch id = (SK_DOMAIN=3) << 48 | endpoint.
 * Confidence: high  Notes: `movk x16,#0x3,LSL#48` @ 0xfffffe000c0d7950;
 *   GENTER @ 0xfffffe000c0d7968. Single-purpose domain-entry core. */
uint64_t
sk_enter_genter_core(uint32_t endpoint_id, sptm_call_regs_t *argsp)
{
	__asm__ volatile(
	    "mov x10, %1\n"
	    "ldp x0, x1, [x10]\n"
	    "ldp x2, x3, [x10, #0x10]\n"
	    "ldp x4, x5, [x10, #0x20]\n"
	    "ldp x6, x7, [x10, #0x30]\n"
	    "mov w16, %w0\n"
	    "movk x16, #0x3, lsl #48\n"
	    :
	    : "r"(endpoint_id), "r"(argsp)
	    : "x0", "x1", "x2", "x3", "x4", "x5", "x6", "x7", "x10", "x16", "memory");
	GENTER(); /* enters SK (GL3); dispatch id in x16 */
	return 0;
}

/* FUN_fffffe000c0d7970 @ 0xfffffe000c0d7970   (txm_enter genter core)
 * Enters the TXM domain (GL0): dispatch id = (TXM_DOMAIN=2) << 48 | endpoint.
 * Confidence: high  Notes: `movk x16,#0x2,LSL#48` @ 0xfffffe000c0d7978;
 *   GENTER @ 0xfffffe000c0d7990. Single caller: txm_enter
 *   (FUN_fffffe000bdbba20). */
uint64_t
txm_enter_genter_core(uint32_t endpoint_id, sptm_call_regs_t *argsp)
{
	__asm__ volatile(
	    "mov x10, %1\n"
	    "ldp x0, x1, [x10]\n"
	    "ldp x2, x3, [x10, #0x10]\n"
	    "ldp x4, x5, [x10, #0x20]\n"
	    "ldp x6, x7, [x10, #0x30]\n"
	    "mov w16, %w0\n"
	    "movk x16, #0x2, lsl #48\n"
	    :
	    : "r"(endpoint_id), "r"(argsp)
	    : "x0", "x1", "x2", "x3", "x4", "x5", "x6", "x7", "x10", "x16", "memory");
	GENTER(); /* enters TXM (GL0); dispatch id in x16 */
	return 0;
}

/* ------------------------------------------------------------------ *
 * Kernel-internal TXM call record.
 *
 * Layout matches the offsets read by txm_enter below (Ghidra `param_1 + N`
 * is a byte offset; `param_1[N]` is an 8-byte unit).
 * ------------------------------------------------------------------ */
struct txm_call_t {
	uint32_t selector;            /* +0: TXM endpoint id passed to genter core */
	uint32_t expected_rc_low;     /* +4: expected return status (low 16 bits) */
	uint8_t  flag_byte2;          /* +8: bit0 = suppress TXM-error printf */
	uint8_t  pad1[3];             /* +9..+11 */
	uint32_t nargs;               /* +12: number of call arguments (0..7) */
	uint32_t expected_return_words; /* +16: required return-word count */
	uint32_t return_words;        /* +20: TXM-reported return-word count */
	uint8_t  fatal_flag;          /* +24: bit0 = panic on any TXM error */
	uint8_t  debug_flag;          /* +28: bit0 = suppress status diagnostics */
	uint8_t  pad2[3];             /* +29..+31 */
	uint64_t nret_words;          /* +32: full return-word count */
	uint64_t retword[6];          /* +40..+87: return words 0..5 */
};

/* ------------------------------------------------------------------ *
 * txm_enter (kernel-side TXM dispatcher).
 *
 * FUN_fffffe000bdbba20 @ 0xfffffe000bdbba20   (txm_enter)
 * Ghidra: undefined8 FUN_fffffe000bdbba20(int *param_1)
 * Validates the TXM argument count, rejects a second thread association,
 * packs the call arguments, and invokes the TXM genter core
 * (0xfffffe000c0d7970) with the selector and a packed sptm_call_regs_t,
 * then maps the TXM return status (CodeSignature / TrustCache / Errno
 * diagnostics) into a kernel error code. The kernel-side dispatcher behind
 * the public `txm_enter(endpoint_id, argsp)` wrapper.
 *
 * Confidence: high (name from map + SDK header; body from decompile)
 * Notes: callees are kernel machinery, externed here; GENTER is performed by
 *   the genter core. Panics: "attempted multiple TXM thread associations",
 *   "invalid number of arguments to TXM", "received excessive/fewer than
 *   expected return words from TXM", "received fatal error for a selector
 *   from TXM".
 * ------------------------------------------------------------------ */
uint64_t
txm_enter(struct txm_call_t *call, sptm_call_regs_t *args)
{
	uint64_t ret_status;
	uint64_t nret;
	uint32_t status;
	uint32_t error_code;
	uint64_t *ap;
	sptm_call_regs_t packed;
	uint64_t lock_owner;

	/* Per-CPU TXM locks / freelist globals (kernel-owned). */
	extern uint64_t txm_lock_owner;     /* DAT_fffffe000c72c140 */
	extern uint32_t txm_preemption_debug; /* DAT_fffffe000c62b3d0 */
	extern void *volatile txm_entry_freelist; /* DAT_fffffe000c64e598 */
	extern uint32_t per_cpu_self_id;    /* *(tpidr_el1 + 0x518) */
	extern char *txm_per_cpu_base;      /* tpidr_el1 (per-CPU struct base) */
	extern void *txm_lock;              /* DAT_fffffe000c72c138 */

	void *entry;       /* popped freelist entry (thread-association record) */
	void *ret_rec;     /* TXM return record */

	/* local_c0: the packed sptm_call_regs_t sent to TXM. */
	memset(&packed, 0, sizeof(packed));

retry:
	/* Serialize on the TXM lock (per-CPU owner + debug flag). */
	lock_owner = txm_lock_owner;
	if (txm_lock_owner == 0) {
		txm_lock_owner = (uint64_t)per_cpu_self_id;
	}
	if (lock_owner != 0 || txm_preemption_debug != 0) {
		lck_mtx_lock(txm_lock, (void *)0, lock_owner, 0); /* FUN_fffffe000b7f0afc */
	}

	/* Pop a thread-association entry from the freelist, waiting if empty. */
	while ((entry = (void *)txm_entry_freelist) == 0) {
		lck_mtx_lock_wait(txm_lock, 0, (void *)0, 0); /* FUN_fffffe000b7f9088 */
	}
	txm_entry_freelist = *(void *volatile *)((char *)entry + 0x18);

	/* Release the TXM lock if we acquired it. */
	if (txm_lock_owner == per_cpu_self_id) {
		txm_lock_owner = 0;
	}
	if (lock_owner != per_cpu_self_id || txm_preemption_debug != 0) {
		lck_mtx_unlock(txm_lock, (void *)0); /* FUN_fffffe000b7f1e80 */
	}

	/* Refuse a second TXM thread association on this CPU/thread. */
	if (*(void **)(txm_per_cpu_base + 0x5a8) != 0) { /* tpidr_el1+0x5a8 */
		kernel_panic_msg_fmt(
		    "attempted multiple TXM thread associations: %lu | %lu @%s:%d");
	}
	*(void **)(txm_per_cpu_base + 0x5a8) = *(void **)((char *)entry + 8);

	/* arg0 to the TXM call is the thread-association selector. */
	packed.x0 = *(uint64_t *)((char *)entry + 8);
	ret_rec = *(void **)((char *)entry + 0x10);

	/* Pack the call arguments (args->x0..x7) into packed.x1..xN. */
	ap = &args->x0;
	switch (call->nargs) {
	case 7: packed.x7 = *ap++;
	case 6: packed.x6 = *ap++;
	case 5: packed.x5 = *ap++;
	case 4: packed.x4 = *ap++;
	case 3: packed.x3 = *ap++;
	case 2: packed.x2 = *ap++;
	case 1: packed.x1 = *ap++;
	case 0: break;
	default:
		kernel_panic_msg_fmt(
		    "invalid number of arguments to TXM: selector: %u | %u @%s:%d");
	}

	/* Pre-entry: disable interrupts / account the guarded entry. */
	/* FUN_fffffe000b807db0 */
	extern void txm_pre_entry(void);
	txm_pre_entry();

	txm_enter_genter_core(call->selector, &packed);

	/* Post-exit: restore interrupt state / account the return. */
	/* FUN_fffffe000b807b10 */
	extern void txm_post_exit(void);
	txm_post_exit();

	/* Map the TXM return status. */
	ret_status = *(uint64_t *)((char *)ret_rec + 8);
	call->return_words = (uint32_t)ret_status;
	if ((ret_status & 0xffff) == 0) {
		nret = *(uint64_t *)((char *)ret_rec + 0x18);
		call->nret_words = nret;
		if (nret > 6) {
			kernel_panic_msg_fmt(
			    "received excessive return words from TXM: selector: %u | %llu @%s:%d");
		}
		if (nret > 0) call->retword[0] = *(uint64_t *)((char *)ret_rec + 0x20);
		if (nret > 1) call->retword[1] = *(uint64_t *)((char *)ret_rec + 0x28);
		if (nret > 2) call->retword[2] = *(uint64_t *)((char *)ret_rec + 0x30);
		if (nret > 3) call->retword[3] = *(uint64_t *)((char *)ret_rec + 0x38);
		if (nret > 4) call->retword[4] = *(uint64_t *)((char *)ret_rec + 0x40);
		if (nret > 5) call->retword[5] = *(uint64_t *)((char *)ret_rec + 0x48);
	}

	/* Disassociate the thread and recycle the freelist entry. */
	/* FUN_fffffe000b840b5c */
	extern void txm_thread_dissociate(void *assoc);
	txm_thread_dissociate(*(void **)((char *)entry + 8));

	/* Re-lock and push the entry back onto the freelist. */
	lock_owner = txm_lock_owner;
	if (txm_lock_owner == 0) {
		txm_lock_owner = (uint64_t)per_cpu_self_id;
	}
	if (lock_owner != 0 || txm_preemption_debug != 0) {
		lck_mtx_lock(txm_lock, (void *)0, lock_owner, 0);
	}
	*(void **)((char *)entry + 0x18) = (void *)txm_entry_freelist;
	txm_entry_freelist = entry;
	if (txm_lock_owner == per_cpu_self_id) {
		txm_lock_owner = 0;
	}
	if (lock_owner != per_cpu_self_id || txm_preemption_debug != 0) {
		lck_mtx_unlock(txm_lock, (void *)0);
	}

	/* Flush the TXM lock state. */
	hv_flush_lock_op((void *)0, (void *)0, 0, 0, 0xffffffff); /* FUN_fffffe000b8563f8 */

	/* Per-CPU TXM-in-flight counter. */
	extern uint64_t txm_inflight;      /* DAT_fffffe000c72c108 */
	extern uint32_t txm_inflight_owner; /* DAT_fffffe000c72c110 */

	/* Handle the TXM "out of memory" retry status (return status 7). */
	if ((ret_status & 0xffff) == 7) {
		if (call->selector == 10) {
			kernel_panic_msg_fmt(
			    "received out-of-memory error when adding a free page to TXM @%s:%d");
		}
		/* Allocate + retype a free page for TXM, then re-dispatch a
		 * "return free page" request (selector 10, no args — the page was
		 * already retyped). Mirrors the decompile's recursive
		 * txm_enter(local_c0) with local_c0[0]=0x100000000000a. */
		extern void txm_alloc_free_page(void); /* FUN_fffffe000b9552c4 */
		struct txm_call_t retry = { 0 };
		txm_alloc_free_page();
		retry.selector = 10;
		txm_enter(&retry, args);
		goto retry;
	}

	/* Diagnostic loop for TXM status (in-flight counter advance). */
	if (!(call->flag_byte2 & 1)) {
		extern uint32_t txm_boot_state;   /* DAT_fffffe0007e31d60 */
		extern uint32_t *txm_boot_count;  /* DAT_fffffe0007e31d58 */
		uint32_t old, new_;
		if (txm_boot_state != 0) {
			/* lock (DAT_fffffe000c72c100) around the counter update. */
			txm_inflight_owner = (*txm_boot_count & 0xff);
			new_ = txm_inflight_owner;
			/* FUN_fffffe000b7f1e80 unlock; loop over the count range. */
			do {
				/* FUN_fffffe000b801ce4(&DAT_fffffe00070e09c9) */
				extern void txm_trace_log(void);
				txm_trace_log();
				old = new_;
				new_ = (old + 1) & 0xff;
			} while (new_ != txm_inflight_owner);
		}
	}

	/* Map the TXM return status to a kernel error code. */
	status = (uint32_t)ret_status & 0xffff;

	/* Emit a TXM [Error] diagnostic unless the status matches the expected
	 * return code, or the caller suppressed diagnostics (debug_flag). */
	if (!(call->debug_flag & 1) &&
	    call->expected_rc_low != status) {
		if (status > 3) {
			if (status == 4) {
				kernel_printf("TXM [Error]: CodeSignature: selector: %u | 0x%02X | 0x%02X | %u\n");
			} else if (status == 5) {
				kernel_printf("TXM [Error]: Errno: selector: %u | %d\n");
			} else {
				kernel_printf("TXM [Error]: selector: %u | %u\n");
			}
		} else if (status != 0 && status == 3) {
			kernel_printf("TXM [Error]: TrustCache: selector: %u | 0x%02X | 0x%02X | %u\n");
		} else if (status != 0) {
			kernel_printf("TXM [Error]: selector: %u | %u\n");
		}
	}

	/* Determine the kernel error code from the TXM status. */
	if (status < 8) {
		if (status == 0) {
			if ((uint64_t)call->expected_return_words <= call->nret_words) {
				return 0; /* success */
			}
			kernel_panic_msg_fmt(
			    "received fewer than expected return words from TXM: selector: %u | %llu @%s:%d");
		}
		if (status == 7) {
			error_code = 6;
		} else {
			error_code = 5;
		}
	} else {
		switch (status) {
		case 0x2a: error_code = 0x31; break;
		case 0x29: error_code = 0x2e; break;
		case 0x08: error_code = 0x38; break;
		default:   error_code = 5; break;
		}
	}

	if (!(call->fatal_flag & 1)) {
		return error_code;
	}
	kernel_panic_msg_fmt(
	    "received fatal error for a selector from TXM: selector: %u | 0x%0llX @%s:%d");
	return error_code;
}

/* ------------------------------------------------------------------ *
 * Isolated GENTER site in the boot / exception path.
 *
 * Address 0xfffffe000c110088 is a single GENTER instruction embedded in the
 * CPU boot / exception-setup path (not a standalone client stub). It follows:
 *
 *   fffffe000c110084: mov  x16, #0xf      ; endpoint 15 = FIXUPS_COMPLETE
 *   fffffe000c110088: genter              ; 0x20 14 20 00
 *   fffffe000c11008c: mov  x0, x26
 *   fffffe000c110090: mov  x1, x27
 *   fffffe000c110094: b    0xfffffe000b958a18   ; shared return helper
 *
 * Dispatch id = BUILD_DISPATCH_ID(SPTM_DOMAIN, XNU_BOOTSTRAP, FIXUPS_COMPLETE)
 * = 0xf. Rendered here for completeness of the 151-site GENTER map.
 * Confidence: high (endpoint read from `mov x16,#0xf` @ 0xfffffe000c110084).
 * ------------------------------------------------------------------ */
void
sptm_isolated_boot_genter(void)
{
	__asm__ volatile("mov x16, #0xf" ::: "x16");
	GENTER(); /* boot-path GENTER; continuation at 0xfffffe000c11008c */
}

/* Build checks: the dispatch id for the XNU-table endpoints is exactly the
 * endpoint id (domain=0, table=0). */
_Static_assert(BUILD_DISPATCH_ID(SPTM_DOMAIN, SPTM_DISPATCH_TABLE_XNU_BOOTSTRAP,
    SPTM_FUNCTIONID_MAP_PAGE) == SPTM_FUNCTIONID_MAP_PAGE,
    "XNU-table endpoint dispatch id must equal the endpoint");
