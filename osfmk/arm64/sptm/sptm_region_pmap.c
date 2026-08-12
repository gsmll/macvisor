/* Recreated from sptm.t8142.release.im4p (SPTM, arm64e, image base 0) — the
 * Secure Page Table Monitor (GL2). Ground truth: Ghidra FUN_ names + addresses;
 * public API names from docs/sptm/headers/sptm_common.h. All names are
 * estimates unless header-matched.
 *
 * This file covers the SPTM pmap / guest-adjacent region
 * (0xeb000 - 0xf9000): the hibernation image restore path (sptm_hib_restore),
 * the page-table region update/restore helpers, and the SPTM panic printers.
 * Ghidra function names are in the per-function header comments; all body
 * identifiers are English reconstructions. */

#include "sptm_internal.h"

#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>

/* -------------------------------------------------------------------------
 * Shared extern contract for the SPTM recreation.  These are the canonical
 * signatures the whole region agrees on; each is defined in its own
 * reconstruction file (not here) unless noted "(defined in this file)".
 * ------------------------------------------------------------------------- */

/* Noreturn panic printers (defined in this file).  FUN_000f8804 is the core
 * printf-style panic; FUN_000f8844 prints with an explicit error code;
 * FUN_000f8824 / FUN_000f8834 are the shorter continuation variants. */
__attribute__((noreturn)) void sptm_panic(const char *fmt, ...);                 /* FUN_000f8804 */
__attribute__((noreturn)) void sptm_panic_code(unsigned int code, uintptr_t arg,
        const char *fmt, ...);                                                  /* FUN_000f8844 */
__attribute__((noreturn)) void sptm_panic_fmt(uint32_t code, ...);               /* FUN_000f8824 */
__attribute__((noreturn)) void sptm_panic_bad_dt(const char *fmt, ...);          /* FUN_000f8834 */

/* Formatting / console / panic-record helpers (defined elsewhere). */
extern uint32_t sptm_snprintf(char *dst, uint64_t dstsz, uint64_t n1, uint64_t n2,
        const char *fmt, ...);                                                  /* FUN_000ad278 */
extern void sptm_serial_str(const char *s);                                     /* FUN_000c15b4 */
extern void sptm_copy_format(void *dst, uint64_t dstsz, uint64_t n, const char *src); /* FUN_000c59b8 */
extern uint64_t sptm_strlcpy_chk(char *dst, const char *src, uint64_t dstsz,
        uint64_t max);                                                          /* FUN_000ae278 */
extern void sptm_bzero(void *dst, uint64_t n);                                  /* FUN_000abb60 */

/* Per-CPU / dispatch / guest-exit helpers. */
extern uint32_t sptm_get_panicking_cpu_id(void);                                /* FUN_000c5a18 */
extern const char *sptm_dispatch_name(uint64_t id);                             /* FUN_000e7678 */
extern void sptm_guest_exit_handoff(uint64_t buf, uint64_t a, uint64_t b,
        uint64_t c);                                                            /* FUN_000a1374 */
extern void sptm_record_panic_cpu(uint64_t cpu_id);                             /* FUN_000d6088 */

/* Panic-record / config globals (Ghidra DAT_000a5028 / DAT_000aa018 /
 * DAT_001012d8).  Declared here so this file is self-contained. */
extern uint64_t sptm_panic_record_base;       /* DAT_000a5028 — SPTM panic record */
extern uint64_t sptm_panic_record_alt;        /* DAT_000aa018 — alternate record base */
extern uint32_t sptm_panic_config_flags;      /* DAT_001012d8 — panic path config bits */
extern char sptm_panic_fallback_buf[];        /* DAT_00106183 — fallback panic buffer */

/* -------------------------------------------------------------------------
 * Hardware / intrinsic helpers.
 * ------------------------------------------------------------------------- */

/* SPTM per-CPU state pointer: EL2 system register (3,6,0xf,8,0) carries the
 * per-CPU state base; if 0, fall back to tpidr_el2; else the EL2 sysreg
 * (3,6,0xf,0xb,1).  Matches the pattern used throughout the decompile. */
static inline uint64_t sptm_per_cpu_base(void)
{
	uint64_t base;
	__asm__ volatile("mrs %0, s3_6_c15_c8_0" : "=r"(base));
	if (base == 0) {
		__asm__ volatile("mrs %0, tpidr_el2" : "=r"(base));
		return base;
	}
	__asm__ volatile("mrs %0, s3_6_c15_c11_1" : "=r"(base));
	return base;
}

static inline uint32_t sptm_spsel(void)
{
	uint64_t spsel;
	__asm__ volatile("mrs %0, spsel" : "=r"(spsel));
	return (uint32_t)spsel;
}

static inline uint64_t sptm_read_sctlr_el2(void)
{
	uint64_t v;
	__asm__ volatile("mrs %0, sctlr_el2" : "=r"(v));
	return v;
}

static inline void sptm_wfe(void)
{
	__asm__ volatile("wfe" ::: "memory");
}

/* SoftwareBreakpoint(op, addr): the SPTM debug/panic breakpoint primitive. */
static inline __attribute__((noreturn)) void sptm_sw_breakpoint(uint32_t op, uintptr_t addr)
{
	(void)op; (void)addr;
	__builtin_trap();
}

/* Per-CPU panic message buffer size (the 0xa28-byte region at cpu+3). */
#define SPTM_PANIC_BUF_SIZE   0xa28

/* -------------------------------------------------------------------------
 * SPTM panic printers (region 0xf8 - 0xf9).
 * ------------------------------------------------------------------------- */

/* FUN_000f84e4 @ 0x000f84e4   (est. sptm_panic_format)
 * Ghidra: void FUN_000f84e4(undefined8 fmt, undefined8 args)
 * Formats the panic message into the per-CPU panic buffer (0xa28 bytes at
 * cpu+3), announces it on the console, flags the panic record, then halts the
 * CPU in an unbounded WFE spin.  On a format overflow it emits the
 * "PANIC_BUF_SIZE ..." truncation message instead of the banner.
 * Confidence: medium
 * Notes: helper calls FUN_000ad278 (sptm_snprintf), FUN_000c15b4 (serial),
 *   FUN_000c59b8 (copy), FUN_000ae278 (strlcpy_chk), FUN_000a1374
 *   (sptm_guest_exit_handoff), SoftwareBreakpoint(1,0xf8714); config bits
 *   DAT_001012d8 0x12/0x17; SCTLR==0x2f selects the alternate record base
 *   DAT_000aa018 vs the primary DAT_000a5028. */
static void sptm_panic_format(const char *fmt, ...)
{
	uint64_t cpu = sptm_per_cpu_base();
	char *pbuf = (char *)(cpu ? (uintptr_t)(cpu + 3) : (uintptr_t)sptm_panic_fallback_buf);
	uint32_t n;
	uint64_t record;
	va_list args;

	/* Format the message into the per-CPU 0xa28-byte panic buffer. */
	va_start(args, fmt);
	n = sptm_snprintf(pbuf, SPTM_PANIC_BUF_SIZE, 0, (uint64_t)-1, fmt, args);
	va_end(args);
	if (n < SPTM_PANIC_BUF_SIZE) {
		sptm_serial_str("\nSPTM PANIC:\n");                 /* 0x54bd */
	} else {
		/* Overflow: report the truncation instead of the banner. */
		char trunc[0x80];
		sptm_copy_format(trunc, sizeof trunc, sizeof trunc,
		    "PANIC_BUF_SIZE %u > %u" /* 0x5432 */);
		sptm_serial_str("PANIC_BUF_SIZE");                   /* 0x549e prefix */
		sptm_serial_str("TRUNCATED ORIGINAL PANIC");         /* 0x54a1 */
	}

	/* On the guarded-dispatch / guest-exit violating path, hand off first. */
	if ((sptm_panic_config_flags & (1U << 0x12)) &&
	    (sptm_spsel() != 1 || (sptm_panic_config_flags & (1U << 0x17)))) {
		sptm_guest_exit_handoff((uintptr_t)pbuf, 0, 0, 0);
		sptm_sw_breakpoint(1, 0xf8714);
	}

	/* Record the panic and copy the formatted message into the record. */
	record = (sptm_panic_record_alt == 0 || sptm_read_sctlr_el2() == 0x2f)
	    ? sptm_panic_record_base : sptm_panic_record_alt;
	if (record != 0) {
		uint64_t count = *(uint64_t *)(record + 0x40);
		if (1 < (count - 1))          /* count==0 or count>=3 */
			sptm_bzero((void *)(record + 0x40), 8);
		*(uint8_t *)(record + 0x10) = 1;
		sptm_bzero((void *)(record + 0x11), 7);
		sptm_strlcpy_chk((char *)(record + 0x48), pbuf,
		    SPTM_PANIC_BUF_SIZE, (uint64_t)-1);
		sptm_bzero((void *)(record + 0x38), 8);
	}

	/* Panic is terminal: halt this CPU. */
	for (;;)
		sptm_wfe();
}

/* FUN_000f8714 @ 0x000f8714   (est. sptm_panic_record)
 * Ghidra: void FUN_000f8714(undefined8 cpu_id, undefined8 arg, undefined8 fp)
 * Formats a secondary panic frame into a 0xa28-byte stack buffer, then copies
 * it into the per-CPU panic buffer and hands off / breaks.  Also records the
 * panicking CPU and panics if the violation flag is not yet set.
 * Confidence: low
 * Notes: helper calls FUN_000abb60 (sptm_bzero), FUN_000ad278 (snprintf),
 *   FUN_000d6088 (record panic cpu), FUN_000c59b8 (copy), FUN_000a1374
 *   (sptm_guest_exit_handoff), SoftwareBreakpoint(1,0xf8804); the 0x54cb
 *   string reads "%s: [SPTM]: somehow a violation ...". */
static void sptm_panic_record(uint64_t cpu_id, uint64_t arg, uintptr_t fp)
{
	char stack[SPTM_PANIC_BUF_SIZE];   /* auStack_a68[2600] */
	uint64_t cpu;

	sptm_bzero(stack, SPTM_PANIC_BUF_SIZE);
	sptm_snprintf(stack, SPTM_PANIC_BUF_SIZE, 0, SPTM_PANIC_BUF_SIZE,
	    (const char *)arg, fp);
	if ((sptm_panic_config_flags & (1U << 0x12)) == 0) {
		sptm_record_panic_cpu(cpu_id);
		sptm_panic("%s: [SPTM]: somehow a violation with panic state", "sptm");
	}
	cpu = sptm_per_cpu_base();
	sptm_record_panic_cpu(cpu_id);
	sptm_copy_format((char *)(cpu + 3), SPTM_PANIC_BUF_SIZE,
	    SPTM_PANIC_BUF_SIZE, stack);
	cpu = sptm_per_cpu_base();
	sptm_guest_exit_handoff((uintptr_t)(cpu + 3), 0, 0, 0);
	sptm_sw_breakpoint(1, 0xf8804);
}

/* FUN_000f8804 @ 0x000f8804   (est. sptm_panic)
 * Ghidra: void FUN_000f8804(undefined8 fmt, undefined8 arg2, undefined8 arg3)
 * Noreturn printf-style SPTM panic.  Formats the message via
 * sptm_panic_format, records the panicking-cpu dispatch name, and prints the
 * final "%s: [%s] %s at pc 0x%016llx lr 0x%016llx" line before halting.
 * Confidence: medium
 * Notes: the two continuation printers FUN_000f8824 / FUN_000f8834 are
 *   installed as a follow-up frame; helper calls FUN_000c5a18 (panicking
 *   cpu), FUN_000f8714, FUN_000e7678 (dispatch name); the recursive format
 *   string at 0xf0b7. */
void sptm_panic(const char *fmt, ...)
{
	uintptr_t fp = (uintptr_t)__builtin_frame_address(0);
	uint32_t pcpu;
	uint64_t cpu;

	/* Format the primary message (sptm_panic_format halts in the common
	 * path; the continuation printers below record CPU + dispatch name). */
	sptm_panic_format(fmt, (uintptr_t)&fmt);
	pcpu = sptm_get_panicking_cpu_id();
	sptm_panic_record(pcpu, 0, fp);
	cpu = sptm_per_cpu_base();
	(void)sptm_dispatch_name(*(uint64_t *)(cpu + 0xa38));
	/* Terminal tail print (only reachable if the format path did not halt). */
	sptm_panic("%s: [%s] %s at pc 0x%016llx lr 0x%016llx",
	    "sptm", "panic", "panic", 0ULL, 0ULL);
}

/* FUN_000f8824 @ 0x000f8824   (est. sptm_panic_fmt)
 * Ghidra: void FUN_000f8824(undefined8 fmt, undefined8 arg2, undefined8 arg3)
 * Noreturn panic continuation: records the panicking-cpu dispatch name and
 * prints the same "%s: [%s] %s at pc ..." tail.  Smaller variant of
 * sptm_panic used as the first continuation printer.
 * Confidence: low
 * Notes: helper calls FUN_000f84e4, FUN_000c5a18, FUN_000f8714, FUN_000e7678;
 *   recurses into FUN_000f8804 with the 0xf0b7 format string. */
void sptm_panic_fmt(uint32_t code, ...)
{
	uintptr_t fp = (uintptr_t)__builtin_frame_address(0);
	uint32_t pcpu;
	uint64_t cpu;

	(void)code;
	sptm_panic_format(0, 0);
	pcpu = sptm_get_panicking_cpu_id();
	sptm_panic_record(pcpu, 0, fp);
	cpu = sptm_per_cpu_base();
	(void)sptm_dispatch_name(*(uint64_t *)(cpu + 0xa38));
	sptm_panic("%s: [%s] %s at pc 0x%016llx lr 0x%016llx",
	    "sptm", "panic", "panic", 0ULL, 0ULL);
}

/* FUN_000f8834 @ 0x000f8834   (est. sptm_panic_bad_dt)
 * Ghidra: void FUN_000f8834(undefined8 fmt, undefined8 arg2, undefined8 arg3)
 * Noreturn panic continuation used for a bad device-tree panic: records the
 * panicking-cpu dispatch name then prints the panic tail.  Second
 * continuation printer.
 * Confidence: low
 * Notes: helper calls FUN_000c5a18, FUN_000f8714, FUN_000e7678; recurses into
 *   FUN_000f8804 with the 0xf0b7 format string.  sptm_init.c declares this as
 *   "void sptm_panic_bad_dt(void)" — a signature guess to reconcile. */
void sptm_panic_bad_dt(const char *fmt, ...)
{
	uintptr_t fp = (uintptr_t)__builtin_frame_address(0);
	uint32_t pcpu;
	uint64_t cpu;

	(void)fmt;
	pcpu = sptm_get_panicking_cpu_id();
	sptm_panic_record(pcpu, 0, fp);
	cpu = sptm_per_cpu_base();
	(void)sptm_dispatch_name(*(uint64_t *)(cpu + 0xa38));
	sptm_panic("%s: [%s] %s at pc 0x%016llx lr 0x%016llx",
	    "sptm", "panic", "panic", 0ULL, 0ULL);
}

/* FUN_000f8844 @ 0x000f8844   (est. sptm_panic_code)
 * Ghidra: void FUN_000f8844(undefined8 code, undefined8 arg, undefined8 fmt)
 * Noreturn SPTM panic with an explicit error code: records the panicking-cpu
 * dispatch name then prints the panic tail.  The code and arg are carried
 * into the record path.
 * Confidence: medium
 * Notes: helper calls FUN_000f8714 (which receives code+fmt), FUN_000e7678;
 *   recurses into FUN_000f8804 with the 0xf0b7 format string. */
void sptm_panic_code(unsigned int code, uintptr_t arg, const char *fmt, ...)
{
	uintptr_t fp = (uintptr_t)__builtin_frame_address(0);
	uint64_t cpu;

	sptm_panic_record(code, arg, fp);
	(void)fmt;
	cpu = sptm_per_cpu_base();
	(void)sptm_dispatch_name(*(uint64_t *)(cpu + 0xa38));
	sptm_panic("%s: [%s] %s at pc 0x%016llx lr 0x%016llx",
	    "sptm", "panic", "panic", 0ULL, 0ULL);
}

/* FUN_000f89b4 @ 0x000f89b4   (est. sptm_invalid_genter)
 * Ghidra: void FUN_000f89b4(void)
 * Noreturn handler for an invalid guarded (GENTER) entry into SPTM: calls the
 * aux routine FUN_000c59f4 then panics with the "SPTM_Dispatch: Invalid
 * GENTER" message.  This is the ring-1 gate's hard rejection path.
 * Confidence: high
 * Notes: body is `FUN_000c59f4(); sptm_panic("%s: [SPTM Dispatch] Invalid
 *   GENTER");` — the 0xf352 string reads "%s: [SPTM Dispatch] Invalid
 *   GENTER". */
void sptm_invalid_genter(void)
{
	sptm_guest_exit_handoff(0, 0, 0, 0);   /* FUN_000c59f4 (aux) */
	sptm_panic("%s: [SPTM Dispatch] Invalid GENTER", "sptm");
}
