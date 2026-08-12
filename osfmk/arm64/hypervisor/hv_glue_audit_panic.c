/* Recreated from kernelcache.arm64.kc (xnu-12377.121.10 RELEASE_ARM64_T8142, image base fffffe0007004000). Ground truth: Ghidra FUN_ names + addresses; all names are estimates. */
/* hv_glue_audit_panic.c — kernel panic touch-set recreation (tree hv-deps, FULL-AUDIT). */

#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>

/*
 * Recreated kernel panic primitives the hypervisor calls directly. The XNU
 * kernel funnels every panic through the printf-style panic engine
 * FUN_fffffe000b7af85c; the small wrappers below are the per-site noreturn
 * entry points that (a) branch on a condition and (b) hand the panic message
 * to kernel_panic_msg_fmt (c0e11ec), which itself forwards to the engine.
 * The engine body is 2+ levels into XNU and remains a stubbed extern (the
 * FULL-AUDIT boundary); only the direct touch-set wrappers are recreated.
 *
 * Estimated names are guesses; the FUN_ + address are ground truth.
 */

/* ---- Local Ghidra-compat typedefs (file is self-contained; the shared
 *      headers declare these panics no-arg because the decompiler drops
 *      varargs on noreturn tails, so corrected arity is defined here). */
typedef unsigned long ulong;
typedef unsigned int  uint;
typedef unsigned char byte;

/* ======================================================================== *
 * Stubbed kernel callees (audit boundary — their internals are 2+ levels in).
 * ======================================================================== */

/* printf-style panic engine. kernel_panic_msg_fmt (c0e11ec) is a thin
 * variadic wrapper that forwards fmt + the saved vararg area to this. The
 * engine formats the message, spins up the panic/backtrace machinery and
 * does not return. Body not recreated (2+ levels into XNU). */
extern void kernel_panic_engine(uint64_t fmt, ulong *saved_args,
                                uint32_t p3, uint64_t p4, uint64_t p5,
                                uint64_t p6);            /* FUN_fffffe000b7af85c */

/* variadic printf-style panic; the other wrappers in this file all tail into
 * it. Defined below (FUN_fffffe000c0e11ec). */
void kernel_panic_msg_fmt(const char *fmt, ...);

/* os_refcnt overflow panic: reached from kernel_panic_a (c0f86a4) when the
 * refcount exceeds 0xffffffe. noreturn; body is a single kernel_panic_msg_fmt
 * call ("os_refcnt: overflow ..."), not recreated (2+ levels into XNU). */
extern void kernel_refcnt_overflow(void);                /* FUN_fffffe000c0f86e8 */

/* zone_require validation helper: called by kernel_zone_array_panic (c0eae24)
 * on the zone-array slot for a zone id. Validates the address lies in the
 * zone and panics on mismatch. Body not recreated (2+ levels into XNU). */
extern void kernel_zone_require(void *zone_slot);        /* FUN_fffffe000c0eacfc */

/* ======================================================================== *
 * Kernel globals (DAT_ addresses kept in comments).
 * ======================================================================== */
extern uint8_t hv_zone_array[];    /* DAT_fffffe000c608b80 kernel zone array (stride 0xc0) */

/* ======================================================================== *
 * Recreated bodies (each is a noreturn panic entry point of the kernel).
 * ======================================================================== */

/* FUN_fffffe000c0f1874 @ 0xfffffe000c0f1874   (est. kernel_panic)
 * Ghidra: void FUN_fffffe000c0f1874(void)
 * noreturn panic reached when the per-CPU preemption-counter at
 * tpidr_el1+0x1c0 underflows (hits zero on a -- where a live reference was
 * expected) on an EL2 nesting or per-CPU refcount path. Reports the
 * "Preemption count underflow" message via kernel_panic_msg_fmt and never
 * returns. This is the canonical panic the hypervisor calls from
 * hv_vcpu_destroy / hv_el2_pt_alloc / the nesting save paths.
 * Confidence: high
 * Notes: pure tail call to kernel_panic_msg_fmt (c0e11ec); the %s:%d expand
 *   to __FILE__/__LINE__ by the engine at runtime (Ghidra drops them on the
 *   noreturn tail). Kernel code recreated for audit (hv-deps). */
void
kernel_panic(void)
{
	kernel_panic_msg_fmt("Preemption count underflow @%s:%d");
}

/* FUN_fffffe000c0f86a4 @ 0xfffffe000c0f86a4   (est. kernel_panic_a)
 * Ghidra: void FUN_fffffe000c0f86a4(uint *param_1)
 * noreturn refcount panic: takes a pointer to the refcount. If the count is
 * already above 0xffffffe it is an os_refcnt overflow (forwarded to
 * kernel_refcnt_overflow, c0f86e8); otherwise it is an attempted resurrection
 * of a dead object (count wrapped back up past a zeroed slot) and reports the
 * "os_refcnt: attempted resurrection" message. Never returns.
 * NOTE: the fresh decompile shows ONE real argument (uint *refcount); the
 *   existing no-arg prototypes in hv_internal.h / hv_kernel_glue.h /
 *   hv_el2.h / hv_compat.h drop it because the caller tails into it. That
 *   prototype should be corrected to `kernel_panic_a(uint *)`.
 * Confidence: high
 * Notes: the `0xffffffe < *refcount` branch is the os_refcnt overflow test;
 *   the fall-through message carries the refcount pointer. The value is only
 *   consumed by the condition / passed into the panic text. Kernel code
 *   recreated for audit (hv-deps). */
void
kernel_panic_a(uint *refcount)
{
	if (0xffffffe < *refcount) {
		kernel_refcnt_overflow();          /* FUN_fffffe000c0f86e8, noreturn */
	}
	kernel_panic_msg_fmt("os_refcnt: attempted resurrection (rc=%p) @%s:%d");
}

/* FUN_fffffe000c0f8674 @ 0xfffffe000c0f8674   (est. kernel_panic_b)
 * Ghidra: void FUN_fffffe000c0f8674(void)
 * noreturn refcount-underflow panic: reached when an os_ref/refcount decrement
 * hit zero where the object was still expected to be live (the refcount was
 * already 0 before the --). Reports "os_refcnt: underflow" via
 * kernel_panic_msg_fmt and never returns. Called by the hypervisor from
 * hv_vmapple / hv_vmm refcount release paths.
 * Confidence: high
 * Notes: pure tail call to kernel_panic_msg_fmt (c0e11ec); the rc=%p arg is
 *   dropped by the decompiler on the noreturn tail. Kernel code recreated for
 *   audit (hv-deps). */
void
kernel_panic_b(void)
{
	kernel_panic_msg_fmt("os_refcnt: underflow (rc=%p) @%s:%d");
}

/* FUN_fffffe000c0e1c3c @ 0xfffffe000c0e1c3c   (est. kernel_panic_c == kernel_panic_msg)
 * Ghidra: void FUN_fffffe000c0e1c3c(byte *param_1, undefined8 param_2, uint param_3)
 * noreturn kobject/port panic with two extra args. param_1 is a message /
 * kobject pointer, param_2 a second pointer, param_3 a wanted value. If
 * *param_1 == param_3 it reports "port %p: invalid kobject, got %p wanted %p"
 * (the object was recognised as a kobject but failed a further check);
 * otherwise "port %p: invalid kobject type, got %d wanted %d" (not a kobject
 * at all). The hypervisor calls this as kernel_panic_msg(name, 0, 0x2d) on a
 * container/region name whose first byte is not '-'.
 * NOTE: the fresh decompile shows THREE real arguments; the hv_pmap.h
 *   prototype `kernel_panic_msg(void*, uint64_t, uint64_t)` is already
 *   correct, while the no-arg kernel_panic_c in hv_internal.h /
 *   hv_kernel_glue.h drops them and should be corrected to the 3-arg form.
 * Confidence: high
 * Notes: the `*param_1 == param_3` test distinguishes the two messages; the
 *   %p/%d args are dropped by the decompiler on the noreturn tails. Kernel
 *   code recreated for audit (hv-deps). */
void
kernel_panic_c(byte *name, uint64_t kobj, uint32_t wanted)
{
	if (*name == wanted) {
		kernel_panic_msg_fmt("port %p: invalid kobject, got %p wanted %p @%s:%d");
	}
	kernel_panic_msg_fmt("port %p: invalid kobject type, got %d wanted %d @%s:%d");
}

/* FUN_fffffe000c0e11ec @ 0xfffffe000c0e11ec   (est. kernel_panic_msg_fmt)
 * Ghidra: void FUN_fffffe000c0e11ec(undefined8 param_1)
 * The universal variadic printf-style panic the hypervisor (and every other
 * wrapper in this file) calls with a format string and optional args. It is a
 * thin variadic wrapper: it captures the caller's format + saved vararg area
 * and forwards them to the printf-style panic engine kernel_panic_engine
 * (b7af85c), which formats the message, dumps the backtrace/registers, and
 * does not return. The unreachable tail (kept faithfully) re-panics with the
 * "Assertion failed" fallback should the engine somehow return.
 * The actual (huge) printf formatting body lives in b7af85c, which is 2+
 * levels into XNU and stays a stubbed extern (FULL-AUDIT boundary). The
 * "compressed PTE ... corrupted" panic in hv_el2_guest_pte_check and the
 * "Unrecognized guest trap exception" panic in hv_el2_guest_esr_classify both
 * tail straight into this function, so the recreated `kernel_panic_assert`
 * and `kernel_panic_msg2` names are ALIASES of this address (c0e11ec).
 * Confidence: high
 * Notes: `&stack0xffffffffffffffe8` in the decompile is Ghidra's rendering of
 *   the saved incoming vararg area, modelled here as a va_list handed to the
 *   engine. The recursive `"%s:%d Assertion failed: %s"` tail is unreachable
 *   (the engine is noreturn). Kernel code recreated for audit (hv-deps). */
void
kernel_panic_msg_fmt(const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	/* forward fmt + the saved vararg area to the panic engine (b7af85c) */
	kernel_panic_engine((uint64_t)fmt, (ulong *)ap, 0, 0, 0, 0);
	va_end(ap);
	/* unreachable: engine does not return; decompiler shows this fallback */
	kernel_panic_msg_fmt("%s:%d Assertion failed: %s");  /* unreachable */
}

/* FUN_fffffe000c0eae24 @ 0xfffffe000c0eae24   (est. kernel_zone_array_panic)
 * Ghidra: void FUN_fffffe000c0eae24(ulong param_1)
 * noreturn zone validation panic. param_1 is a zone id/tag (e.g. 0xf for the
 * OSObject zone, 0x15 for a waitq/zone tag). It first runs the zone_require
 * validation on the zone-array slot for that id (kernel_zone_require,
 * c0eacfc), then reports "zone_require_ro failed: address not in a ro zone".
 * Called by zfree_waitq / kernel_refcount_inc with a zone tag as the single
 * argument. Note c0eae44 (zone_require_ro_panic, already recreated in
 * hv_helpers.c) is a DIFFERENT function — the bare message with no slot
 * validation — even though it uses the same panic string.
 * Confidence: high
 * Notes: the slot index is `param_1 & 0xffffffff` scaled by the 0xc0 zone-array
 *   stride; the `(zone_require_ro failed ...)` string is shared with c0eae44.
 *   Ghidra removes several unreachable blocks (0xfffffe000c0eaea0 etc.) in
 *   this body. Kernel code recreated for audit (hv-deps). */
void
kernel_zone_array_panic(ulong zone_index)
{
	kernel_zone_require(hv_zone_array + (zone_index & 0xffffffff) * 0xc0);
	kernel_panic_msg_fmt("zone_require_ro failed: address not in a ro zone (addr: %p) @%s:%d");
}

/* FUN_fffffe000c0e0620 @ 0xfffffe000c0e0620   (est. kernel_stack_check_panic)
 * Ghidra: void FUN_fffffe000c0e0620(void)
 * noreturn stack-protector panic: reached when the boot/kernel stack guard
 * marker (kernel_stack_check_panic, called from kernel_bootstrap_thread and
 * the boot-finalize paths) detects stack corruption. Reports "Kernel stack
 * memory corruption detected" via kernel_panic_msg_fmt and never returns.
 * The only xref to the string at ffffffe0007045a4a is this function.
 * Confidence: high
 * Notes: pure tail call to kernel_panic_msg_fmt (c0e11ec); the %s:%d expand
 *   to __FILE__/__LINE__ by the engine. Kernel code recreated for audit
 *   (hv-deps). */
void
kernel_stack_check_panic(void)
{
	kernel_panic_msg_fmt("Kernel stack memory corruption detected @%s:%d");
}
