/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel, GL1,
 * arm64e, image base 0) — the cL4 microkernel. Ground truth: Ghidra FUN_ names +
 * addresses in cl4_kernel.raw. Version "cL4 microkernel (cL4 (679.100.61))".
 * All names are estimates unless string/header-matched.
 *
 * Region 0x10000-0x20000: early boot / initialization. cL4/seL4 vocabulary
 * (boot, TCB init, capability init, sched init, CNode, IPC, vspace).
 */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

typedef uint64_t word_t;
typedef uint64_t cap_t;
typedef uint64_t tcb_t;

/* Boot-time diagnostic logger (FUN_000117e8). */
extern void sk_log(unsigned int level, const char *fmt, ...); /* FUN_000117e8 */

/* Shared page/guard allocator primitives (region 0x36xxxx). */
extern void *sk_alloc(unsigned long size, unsigned long tag);        /* FUN_0036a908 */
extern void sk_free(void *ptr);                                      /* FUN_0036b118 */

/* Current TCB / CPU helpers. */
extern void *sk_current_tcb(void);  /* FUN_000867ec */
extern void *sk_cpu(void);          /* FUN_0008e518 */

/* Boot failure/panic handler (FUN_00011824). */
extern void sk_boot_fail(unsigned int level, unsigned long code, const char *fmt, ...); /* FUN_00011824 */

/*--------------------------------------------------------------------*/
/* FUN_0001003c @ 0x0001003c   (est. sk_guard_size_config)
 * Ghidra: void FUN_0001003c(long config, ulong size, int flag, undefined1 *out)
 * Computes allocator guard/slack sizes for a requested block size. For small
 * blocks (< 0x8001, flag set, guard-enable bit at config+0x260) it reads two
 * per-class guard byte fields (config+0x262/0x264 and config+0x263/0x265,
 * the latter chosen when size > 0x1000), rounds size up to a 16 KiB multiple,
 * and reports kind 1 with a page-count guard (size >> 14). For larger blocks
 * it checks a second guard-enable bit (config+0x266): multiplies size by the
 * guard multiplier (config+0x267) and, if the product exceeds 16 MiB, scales
 * down the three guard bytes by the top byte of the product, logging
 * "Reducing guards for block size". Writes a 5-byte record {kind, g1, g2, g3,
 * page_count} to out.
 * Confidence: medium
 * Notes: references string s_Reducing_guards_for_block_size___005aa72d via
 *   sk_log (FUN_000117e8). */
void sk_guard_size_config(void *config, unsigned long size, int flag, uint8_t *out)
{
    uint8_t g1, g2, g3, page_count;
    uint8_t kind;

    if ((size < 0x8001) && (flag != 0) &&
        ((*(uint8_t *)((char *)config + 0x260) & 1) != 0)) {
        unsigned long off_a = 0x262, off_b = 0x263;
        if (0x1000 < size) { off_a = 0x264; off_b = 0x265; }
        g3 = *(uint8_t *)((char *)config + off_a);
        if ((size & 0x3fff) != 0) size += 0x4000;
        page_count = (uint8_t)(size >> 0xe);
        g2 = *(uint8_t *)((char *)config + off_b);
        g1 = 0;
        kind = 1;
    } else {
        g3 = 0;
        page_count = 0;
        if ((size - 0x8001) >> 0xf < 0x3f) {
            kind = 0;
            g2 = g3;
            g1 = g3;
            if ((*(uint8_t *)((char *)config + 0x266) & 1) != 0) {
                g3 = *(uint8_t *)((char *)config + 0x267);
                g2 = *(uint8_t *)((char *)config + 0x268);
                g1 = *(uint8_t *)((char *)config + 0x26b);
                size = size * g3;
                if (size < 0x1000001) {
                    page_count = 0;
                    kind = 2;
                } else {
                    uint8_t top = (uint8_t)((size >> 0x18) & 0xff);
                    uint8_t zero = 0;
                    if ((size & 0xff000000) != 0) zero = (uint8_t)(g3 / top);
                    g3 = zero;
                    zero = 0;
                    if ((size & 0xff000000) != 0) zero = (uint8_t)(g2 / top);
                    g2 = zero;
                    zero = 0;
                    if ((size & 0xff000000) != 0) zero = (uint8_t)(g1 / top);
                    g1 = zero;
                    sk_log(4, "Reducing guards for block size %lx");
                    page_count = 0;
                    kind = 2;
                }
            }
        } else {
            g1 = 0; g2 = 0; g3 = 0;
            kind = 0;
        }
    }
    out[0] = kind;
    out[1] = g3;
    out[2] = g2;
    out[3] = g1;
    out[4] = page_count;
}

/*--------------------------------------------------------------------*/
/* FUN_0001018c @ 0x0001018c   (est. sk_lock_acquire_failed_panic)
 * Ghidra: void FUN_0001018c(void)
 * Panic wrapper: logs "Failed to acquire lock %p" at level 0x40 and invokes
 * the boot failure handler (FUN_00011824). Called when a lock cannot be
 * acquired during early boot.
 * Confidence: medium (string-matched "Failed to acquire lock").
 * Notes: string s_Failed_to_acquire_lock__p__005a9a23. */
void sk_lock_acquire_failed_panic(void)
{
    sk_boot_fail(0x40, 0, "Failed to acquire lock %p");  /* FUN_00011824 */
}

/*--------------------------------------------------------------------*/
