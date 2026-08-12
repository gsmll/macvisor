/* Recreated from kernelcache.arm64.kc (xnu-12377.121.10 RELEASE_ARM64_T8142, image base fffffe0007004000). Ground truth: Ghidra FUN_ names + addresses; all names are estimates. */
#include "hv_compat.h"

/*
 * hv_pmap.c — stage-2 MMU (guest -> host) map-layer helpers.
 *
 * Owned by the hv-pmap tree.
 *
 * The guest->host memory boundary is a two-part construction:
 *
 *   (1) A HOST vm_map per VM owner.  The map/unmap/region entry points
 *       (hv_vm_map b986898, hv_vm_unmap b986d94, hv_vm_map_region b986ff4,
 *       owned by trap-dispatch) funnel into the common map core
 *       hv_vm_map_core (hv_vm_map_core, also trap-dispatch), which
 *       copies the user arg block, resolves the target vm owner via
 *       hv_pmap_resolve_owner (below), validates the requested range against
 *       the owner's vm bounds (page-mask from owner+0x44, allowed window
 *       owner+0x28/+0x30), and drives kernel vm_map_enter/vm_map_protect/
 *       vm_map_remove (kernel_mem_validate b8b51c8, kernel_copyout b8b49e8,
 *       kernel_mem_release b8a8078 — shared deps, stubbed).
 *
 *   (2) The EL2 stage-2 translation table.  hv_el2_pt_alloc
 *       (hv_el2_pt_alloc, el2-state) allocates the 0x8000-byte EL2
 *       block (root L1 table at +0x0, L2 at +0x1000, L3 at +0x2000, EL2
 *       register state at +0x4000) and stores its base at vm+0x4150;
 *       hv_el2_state_build (hv_el2_state_build, el2-state) programs the
 *       HCR/SCTLR/TCR/VTCR/TTBR state and records the L2/L3 table pointers
 *       on the vm config (slots 0xd/0xe).  The page walk runs in hardware;
 *       the descriptor format is modelled (as an estimate) in hv_pmap.h.
 *
 * The functions decompiled here are the owner/map resolution and the
 * failure-unwind path shared by the map layer — the glue that binds a
 * guest-provided vm id to the host vm_map that implements its stage-2
 * translation.
 *
 * Stage-2 fault path (for context, owned by el2-vectors in hv_el2.c):
 *   guest abort -> hv_el2_guest_esr_classify (b96743c) ->
 *   hv_el2_guest_fault (b967768): synthesises the guest IPA from HPFAR_EL2
 *   (FAR[11:0] | HPFAR[31:4]<<12) and drives the kernel vm_fault family
 *   (hv_el2_guest_pte_check / b89988c / b9879b8, shared deps) on the vm that
 *   hv_pmap_resolve_owner returns.
 */

#include "hv_pmap.h"

/* ======================================================================== *
 * hv_pmap_resolve_owner @ 0xfffffe000b986b34   (est. hv_pmap_resolve_owner)
 * Ghidra: undefined8 hv_pmap_resolve_owner(ulong param_1, undefined8 *param_2)
 * Resolves a vm/owner handle to the underlying map pointer. With id==0 it
 * takes the current CPU's bound owner (per-cpu owner slot per_cpu_base+0x628,
 * or the bound vcpu's vm via tpidr_el1+0x4d8) under the shared owner lock
 * DAT_fffffe000c62c0b8, bumping the owner refcount around the read and
 * returning owner+0x2120 (the host map). With id==0xffffffffffffffff it
 * returns the bound vcpu's +0x88 slot. Otherwise it treats id as a low-32-bit
 * container id, looks it up via kernel_obj_lookup (kernel object lookup,
 * type 0x2d), validates the returned name ('-' prefix + flag byte bit 2), and
 * returns the name object's +0x50 map pointer, writing the name to *param_2.
 * Returns 0 when no owner is bound/resolvable.
 * Confidence: high (callers hv_vm_map_core b9868a8 and hv_vcpu_attach b986e50
 *   resolve the vm via this exact function; the lock + refcount + offset
 *   pattern is directly observed).
 * Notes: decompiler sign-extension quirk 0x2bad000000000000 on the low-32 id
 *   branch is elided (id >> 32 == 0 guard makes it clean). The
 *   `(lVar4 != 0) && (lVar4 != 0)` double test is a Ghidra artifact of the
 *   tagged-address check, collapsed to a single !=0 here. CONCAT44 low-half
 *   clear of DAT_fffffe000c62c0c0 is reproduced as a 32-bit clear.
 */
uint64_t
hv_pmap_resolve_owner(uint64_t id, char **name_out)
{
	uint64_t old_cpu;
	uint64_t map_ptr;
	int      rc;
	uint8_t *p;
	long     owner;
	char    *obj_name;

	*name_out = 0;
	old_cpu = hv_cached_cpu_id;                    /* DAT_fffffe000c62c0c0 */

	if (id == 0) {
		p = (uint8_t *)tpidr_el1;
		if (*(uint64_t *)(p + 0x4d8) == 0) {
			/* No vcpu bound to this CPU: take the shared owner lock and
			 * read the per-CPU owner slot. */
			if (hv_cached_cpu_id == 0)
				hv_cached_cpu_id = *(uint32_t *)(p + 0x518);
			if (old_cpu != 0 || hv_debug_flag != 0)
				kernel_lock_acquire((uint64_t)&hv_lock, p, old_cpu, 0);
			owner = *(long *)((uint8_t *)per_cpu_base((uint64_t)p) + 0x628);
			if (owner != 0) {
				rc = *(int *)(owner + 8);
				*(int *)(owner + 8) = rc + 1;          /* owner refcount++ */
				if ((uint32_t)(rc + 0xf0000001U) < 0xf0000002)
					kernel_panic_c();                    /* overflow, noreturn */
				rc = (int)hv_cached_cpu_id;
				if ((int)hv_cached_cpu_id == *(int *)(p + 0x518))
					hv_cached_cpu_id &= 0xffffffff00000000ULL; /* clear low 32 */
				if (rc != *(int *)(p + 0x518) ||
				    hv_debug_flag != 0)
					kernel_lock_release2((uint64_t)&hv_lock, p);
				map_ptr = *(uint64_t *)(owner + 0x2120);  /* host map ptr */
				kernel_refcount_inc(0);                  /* b8af98c (arg 0) */
				rc = *(int *)(owner + 8);
				*(int *)(owner + 8) = rc - 1;          /* owner refcount-- */
				LORelease();
				if (rc != 0) {
					if (rc == 1)
						hv_vcpu_object_release((void *)owner); /* b98533c, vcpu-core */
					return map_ptr;
				}
				kernel_panic_b();                        /* c0f8674, noreturn */
			}
			kernel_lock_release((uint64_t)&hv_lock);     /* b7f1e4c */
		} else {
			uint64_t vm = **(uint64_t **)(p + 0x4d8);  /* *(*bound_vcpu) */
			if (vm != 0)
				return *(uint64_t *)(vm + 0x2120);
		}
	} else if (id == 0xffffffffffffffffULL) {
		p = (uint8_t *)tpidr_el1;
		if (*(long *)(p + 0x4d8) != 0)
			return *(uint64_t *)(*(long *)(p + 0x4d8) + 0x88);
	} else if (id >> 0x20 == 0) {
		/* Low-32-bit container id: kernel object lookup (type 0x2d). */
		obj_name = 0;
		p = (uint8_t *)per_cpu_base((uint64_t)tpidr_el1);
		p = *(uint8_t **)(p + 0x318);            /* obj-lookup base */
		rc = kernel_obj_lookup((uint64_t)p, id, 0x2d, &obj_name);
		if (((rc == 0) && (1 < (uintptr_t)obj_name + 1)) &&
		    (*name_out = obj_name,
		     (obj_name[1] & 7U) != 0) &&
		    (*obj_name == '-')) {
			return *(uint64_t *)(obj_name + 0x50);
		}
	}
	return 0;
}

/* ------------------------------------------------------------------ */
/* FUN_fffffe000b986d34 @ 0xfffffe000b986d34   (est. hv_pmap_unwind)
 * Ghidra: void hv_pmap_unwind(char *param_1, undefined8 param_2)
 * Failure-unwind for the map layer. If the caller's container name is the
 * -1 sentinel, or names an object, the current vcpu is detached via
 * zfree_waitq (kernel). If the name is NULL and no vcpu is bound to
 * this CPU (tpidr_el1+0x4d8 == 0), the owner reference (param_2) is released
 * via os_release (os_release). A non-'-'-prefixed name triggers the
 * kernel_panic_c panic (invalid container name).
 * Confidence: high (called by hv_vm_map_core b9868a8 and hv_vm_map_region
 *   b986ff4 on every failed/unwind path; the release/detach split is directly
 *   observed).
 * Notes: noreturn panic on a bad name; param_2 is released only when no vcpu
 *   is bound (so a live vcpu keeps the owner alive).
 */
void
hv_pmap_unwind(char *name, uint64_t owner)
{
	uint8_t *p;

	if (name != (char *)0xffffffffffffffffULL) {
		if (name == 0) {
			p = (uint8_t *)tpidr_el1;
			if (*(long *)(p + 0x4d8) != 0)
				return;                       /* a vcpu is bound: keep owner */
			os_release(owner);                 /* b8afa78 */
			return;
		}
		if (*name != '-')
			kernel_panic_msg(name, 0, 0x2d);   /* c0e1c3c, noreturn */
	}
	kernel_vcpu_detach(name);                  /* b793cf4 */
}
