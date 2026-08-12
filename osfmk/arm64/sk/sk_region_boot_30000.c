/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel, GL1,
 * arm64e, image base 0) — the cL4 microkernel. Ground truth: Ghidra FUN_ names +
 * addresses in cl4_kernel.raw. Version "cL4 microkernel (cL4 (679.100.61))".
 * All names are estimates unless string/header-matched.
 *
 * This region (0x30000-0x40000) is the boot / early-init region: TCB & cap
 * init, scheduling init, CNode/object init, early boot handoff.
 */

#include <stdint.h>
#include <stddef.h>

#include "sk_internal.h"

/* ------------------------------------------------------------------ *
 * Out-of-range cL4 helper declarations (extern; bodies reconstructed by
 * the sibling range worker that owns them). Names are estimates.
 * ------------------------------------------------------------------ */

/* Core lock/refcount/allocator primitives (region 0x34xxxx-0x37xxxx). */
extern void *sk_alloc(unsigned long size, unsigned long tag);        /* FUN_0036a908 */
extern void *sk_alloc_pages(unsigned long size, unsigned long tag);  /* FUN_0036b270 */
extern void sk_free(void *ptr);                                      /* FUN_0036b118 */

/* Object method-dispatch table base used by object constructors. */
extern unsigned char sk_obj_methods_0[];  /* DAT_00611b24 */
extern unsigned char sk_obj_methods_1[];  /* DAT_00611b34 / DAT_00611b3c / LAB_00611b2c */

/* Boot handoff helper owned by the earlier range (0x2xxxx). */
extern void sk_boot_handoff_stage(void);   /* FUN_0002ff48 */

/*--------------------------------------------------------------------*/
/* FUN_000304c4 @ 0x000304c4   (est. sk_boot_cpu_trampoline)
 * Ghidra: undefined FUN_000304c4(void)
 * Thin forwarder: unconditionally jumps into the earlier-stage boot
 * handoff routine FUN_0002ff48. Used during the secondary-CPU bring-up
 * trampoline to re-enter the shared boot path.
 * Confidence: medium (trivial wrapper).
 */
void sk_boot_cpu_trampoline(void)
{
    sk_boot_handoff_stage();   /* FUN_0002ff48 */
}

