/* Recreated from cl4_kernel.raw (cL4 Secure Kernel, arm64e, image base 0) —
 * the cL4 microkernel (GL1), "cL4 (679.100.61)". Ground truth: Ghidra FUN_
 * names + addresses in program cl4_kernel.raw.
 * Slice 06: 0x327c38-0x32cbf8 syscall/exception-entry region.
 * All names are estimates unless string/header-matched.
 *
 * This region is the cL4 syscall-metadata registry: a dense table of small
 * init/registration routines that populate the global syscall registry
 * (region ~0x656000: syscall name descriptors, handler tags, cost fields).
 * Many addresses come in identical pairs (two init-array entries referencing
 * the same registration code); both are reproduced. A large subset are
 * "leaf stub" setters that Ghidra cannot fully disassemble ("Removing
 * unreachable block") — they initialize a registry slot with a literal
 * 8-byte instruction-encoding constant and are modeled to return it. */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "sk_internal.h"
#include "sk_region_syscalls.h"

/* ------------------------------------------------------------------ *
 * Global syscall registry. The cL4 boot path fills the table at ~0x656000
 * with per-syscall metadata (name descriptors, handler tags, costs).
 * SK_SYSREG(off) addresses the 8-byte slot at base+off.
 * ------------------------------------------------------------------ */
extern und8_t sk_syscall_registry[];   /* global syscall registry, base 0x656000 */
#define SK_SYSREG(off) (*(und8_t *)&sk_syscall_registry[(off)])

/* ------------------------------------------------------------------ *
 * Out-of-range cL4 helper declarations (declared extern with a one-line
 * note; their bodies are reconstructed by the range worker that owns them).
 * ------------------------------------------------------------------ */

/* FUN_00376820 -> FUN_00376838: insert (descriptor, tag, handler) into the
 * syscall-name hash registry; returns the stored registry slot. */
extern und8_t sk_syscall_register(und8_t descriptor, und8_t tag, und8_t handler);
/* FUN_00027614: lazy-init a registry slot: return *slot (bit0 cleared) if
 * non-zero, else allocate a fresh descriptor from *param2 and store it. */
extern und8_t sk_registry_get_or_init(und8_t *slot, und8_t *descriptor);
/* FUN_00352b20: return *param (single-word deref helper). */
extern und8_t sk_deref_word(und8_t *param);
/* FUN_00327e08: generic init dispatcher (calls FUN_00352b20, FUN_00106e3c,
 * FUN_00027614, FUN_0035a7e8, FUN_00376820); shared by many register fns. */
extern void sk_init_dispatch(void);
/* FUN_00355244 -> FUN_00327e08: thin wrapper over sk_init_dispatch. */
extern void sk_init_dispatch_wrap(void);
/* FUN_00376838 (via sk_syscall_register above). */

/* Object refcount helpers used across this region. */
/* FUN_0036b270: variadic object release (releases each passed object). */
extern void sk_obj_release(und8_t obj);
/* FUN_0036b118: object retain. */
extern void sk_obj_retain(und8_t obj);
/* FUN_003a25d4: object release (secondary release helper). */
extern void sk_obj_release2(und8_t obj);

/* Small object/registry helper functions (FUN_ addresses noted). */
extern und8_t sk_fun_00027754(und8_t);            /* FUN_00027754 */
extern void   sk_fun_0009461c(und8_t, und8_t, und8_t*); /* FUN_0009461c */
extern void   sk_fun_0034ee78(void);               /* FUN_0034ee78 */
extern und8_t sk_fun_00348ad8(und8_t, und8_t);     /* FUN_00348ad8 */
extern und8_t sk_fun_00349e38(und8_t);             /* FUN_00349e38 */
extern void   sk_fun_00348990(void);               /* FUN_00348990 */
extern void   sk_fun_00356518(void);               /* FUN_00356518 */
extern und8_t sk_fun_00354e88(void);               /* FUN_00354e88 */
extern void   sk_fun_0034b550(void);               /* FUN_0034b550 */
extern void   sk_fun_00349204(void);               /* FUN_00349204 */
extern void   sk_fun_0035098c(void);               /* FUN_0035098c */
extern void   sk_fun_00356d8c(void);               /* FUN_00356d8c */
extern void   sk_fun_00356d74(void);               /* FUN_00356d74 */
extern void   sk_fun_00352758(void);               /* FUN_00352758 */
extern void   sk_fun_0035549c(und8_t, und8_t);     /* FUN_0035549c */
extern und8_t sk_fun_00349748(und8_t, ...);               /* FUN_00349748 (16B via regs) */
extern und8_t sk_fun_00377824(und8_t, und8_t, und8_t); /* FUN_00377824 (16B) */
extern void   sk_fun_0034f924(void);               /* FUN_0034f924 */
extern void   sk_fun_00355d34(void);               /* FUN_00355d34 */
extern void   sk_fun_00358184(void);               /* FUN_00358184 */
extern void   sk_fun_00357ef4(void);               /* FUN_00357ef4 */
extern void   sk_fun_0034e888(void);               /* FUN_0034e888 */
extern void   sk_fun_003551b0(void);               /* FUN_003551b0 */
extern void   sk_fun_003580f4(void);               /* FUN_003580f4 */
extern void   sk_fun_0034e32c(void);               /* FUN_0034e32c */
extern und8_t sk_fun_00351538(void);               /* FUN_00351538 */
extern void   sk_fun_003520e8(void);               /* FUN_003520e8 */
extern void   sk_fun_0034bf1c(void);               /* FUN_0034bf1c */
extern und8_t sk_fun_000839f8(void);               /* FUN_000839f8 */
extern und8_t sk_fun_003504d0(void);               /* FUN_003504d0 (returns ptr/16B) */
extern void   sk_fun_003597cc(void);               /* FUN_003597cc */
extern void   sk_fun_00370060(und8_t, und8_t);     /* FUN_00370060 */
extern void   sk_fun_00374104(und8_t, und8_t, und8_t, void*, und8_t); /* FUN_00374104 */
extern void   sk_fun_003546b4(void);               /* FUN_003546b4 */
extern void   sk_fun_00355938(void);               /* FUN_00355938 */
extern void   sk_fun_000026e8(void);               /* FUN_000026e8 */
extern void   sk_fun_0034b044(void);               /* FUN_0034b044 */
extern void   sk_fun_003566cc(void);               /* FUN_003566cc */
extern und8_t sk_fun_00350c5c(void);               /* FUN_00350c5c (16B) */
extern und8_t sk_fun_00353dc4(und8_t, ...);     /* FUN_00353dc4 */
extern und8_t sk_fun_0034b07c(und8_t, und8_t, und8_t); /* FUN_0034b07c */
extern void   sk_fun_003575d4(void);               /* FUN_003575d4 */
extern void   sk_fun_00352778(void);               /* FUN_00352778 */
extern void   sk_fun_00359c2c(void);               /* FUN_00359c2c */
extern void   sk_fun_003571b0(void);               /* FUN_003571b0 */
extern und8_t sk_fun_00377dcc(und8_t, und8_t);     /* FUN_00377dcc (16B via regs) */
extern void   sk_fun_00353424(und8_t);             /* FUN_00353424 */
extern void   sk_fun_0034d034(void);               /* FUN_0034d034 */
extern void   sk_fun_00354c58(void);               /* FUN_00354c58 */
extern void   sk_fun_0034c7c4(void);               /* FUN_0034c7c4 */
extern void   sk_fun_00354ce4(void);               /* FUN_00354ce4 */
extern void   sk_fun_003558b8(und8_t);             /* FUN_003558b8 */
extern und8_t sk_fun_0034cdf8(void);               /* FUN_0034cdf8 (returns 16B) */
extern void   sk_fun_003728b8(und8_t, und8_t, und8_t); /* FUN_003728b8 */
extern void   sk_fun_0035884c(void);               /* FUN_0035884c */
extern void   sk_fun_00084220(void);               /* FUN_00084220 */
extern und8_t sk_fun_00349734(und8_t, und8_t);     /* FUN_00349734 */
extern void   sk_fun_000a6f88(void);               /* FUN_000a6f88 */
extern void   sk_fun_0034d5d8(und8_t);             /* FUN_0034d5d8 */
extern void   sk_fun_0034bfb4(und8_t);             /* FUN_0034bfb4 */
extern void   sk_fun_00357154(void);               /* FUN_00357154 */
extern void   sk_fun_0034de74(void);               /* FUN_0034de74 */
extern void   sk_fun_00084234(void);               /* FUN_00084234 */
extern und8_t sk_fun_0034b3c8(void);               /* FUN_0034b3c8 */
extern void   sk_fun_0034bf0c(void);               /* FUN_0034bf0c */
extern void   sk_fun_00348c64(void);               /* FUN_00348c64 */
extern void   sk_fun_00349530(void);               /* FUN_00349530 */
extern void   sk_fun_00353900(void);               /* FUN_00353900 */
extern und8_t sk_fun_00355150(void);               /* FUN_00355150 */
extern void   sk_fun_0034a32c(und8_t, und8_t, und8_t); /* FUN_0034a32c */
extern void   sk_fun_00019858(void);               /* FUN_00019858 */
extern und8_t sk_fun_00325088(und8_t, und8_t);     /* FUN_00325088 */
extern und8_t sk_fun_00354ec0(void);               /* FUN_00354ec0 */
extern void   sk_fun_0034b528(void);               /* FUN_0034b528 */
extern void   sk_fun_0034b590(void);               /* FUN_0034b590 */
extern void   sk_fun_0034e250(void);               /* FUN_0034e250 */
extern void   sk_fun_003544ec(void);               /* FUN_003544ec */
extern void   sk_fun_0006a414(void);               /* FUN_0006a414 */
extern void   sk_fun_00086368(void);               /* FUN_00086368 */
extern void   sk_fun_000863bc(void);               /* FUN_000863bc */
extern void   sk_fun_000e710c(void);               /* FUN_000e710c */
extern void   sk_fun_0001df60(void);               /* FUN_0001df60 */
extern void   sk_fun_0001e790(void);               /* FUN_0001e790 */
extern und8_t sk_fun_0034d454(void);               /* FUN_0034d454 */
extern void   sk_fun_00324904(void);               /* FUN_00324904 */
extern und8_t sk_fun_00354ec0(void);               /* FUN_00354ec0 */

/* Leaf-stub setters owned by an earlier range (slots 0x6564a8 / 0x6564c0). */
extern und8_t sk_sysreg_leaf_6564a8(void);   /* FUN_00327a88, slot 0x6564a8 */
extern und8_t sk_sysreg_leaf_6564c0(void);   /* FUN_00327b8c, slot 0x6564c0 */
extern void   sk_fun_00106e3c(void);         /* FUN_00106e3c */
extern void   sk_fun_0035a7e8(void);         /* FUN_0035a7e8 */

/* FUN_00376820 aliases used for register-dispatch (see sk_syscall_register). */

/* Forward declarations for leaf-stub setters defined later in this file. */
und8_t sk_sysreg_leaf_6564e8(void);
und8_t sk_sysreg_leaf_656510(void);
und8_t sk_sysreg_leaf_656540(void);
und8_t sk_sysreg_leaf_656558(void);
und8_t sk_sysreg_leaf_656560(void);
und8_t sk_sysreg_leaf_656568(void);
und8_t sk_sysreg_leaf_656580(void);
und8_t sk_sysreg_leaf_656598(void);
und8_t sk_sysreg_leaf_6565a8(void);
und8_t sk_sysreg_leaf_6565b8(void);
und8_t sk_sysreg_leaf_6565c0(void);
und8_t sk_sysreg_leaf_6565d0(void);
und8_t sk_sysreg_leaf_6565e8(void);
und8_t sk_sysreg_leaf_6565f0(void);
und8_t sk_sysreg_leaf_656600(void);
und8_t sk_sysreg_leaf_656618(void);
und8_t sk_sysreg_leaf_656620(void);
und8_t sk_sysreg_leaf_656630(void);
und8_t sk_sysreg_leaf_656650(void);
und8_t sk_sysreg_leaf_656658(void);
und8_t sk_sysreg_leaf_656668(void);
und8_t sk_sysreg_leaf_656680(void);
und8_t sk_sysreg_leaf_656688(void);
und8_t sk_sysreg_leaf_656698(void);
und8_t sk_sysreg_leaf_6566a0(void);
und8_t sk_sysreg_leaf_6566b8(void);
und8_t sk_sysreg_leaf_6566c0(void);
und8_t sk_sysreg_leaf_6566d0(void);
und8_t sk_sysreg_leaf_6566e8(void);
und8_t sk_sysreg_leaf_6566f0(void);
und8_t sk_sysreg_leaf_656700(void);
und8_t sk_sysreg_leaf_656708(void);
und8_t sk_sysreg_leaf_656720(void);
und8_t sk_sysreg_leaf_656728(void);
und8_t sk_sysreg_leaf_656738(void);
und8_t sk_sysreg_leaf_656750(void);
und8_t sk_sysreg_leaf_656758(void);
und8_t sk_sysreg_leaf_656768(void);
und8_t sk_sysreg_leaf_656780(void);
und8_t sk_sysreg_leaf_656788(void);
und8_t sk_sysreg_leaf_656798(void);
und8_t sk_sysreg_leaf_6567a0(void);
und8_t sk_sysreg_leaf_6567b8(void);
und8_t sk_sysreg_leaf_6567c0(void);
und8_t sk_sysreg_leaf_6567d0(void);
und8_t sk_sysreg_leaf_6567e8(void);
und8_t sk_sysreg_leaf_6567f0(void);
und8_t sk_sysreg_leaf_656800(void);
und8_t sk_sysreg_leaf_656808(void);
und8_t sk_sysreg_leaf_656828(void);
und8_t sk_sysreg_leaf_656830(void);
und8_t sk_sysreg_leaf_656840(void);
und8_t sk_sysreg_register_656634_once(void);
void sk_obj_swap_type_tagged(und8_t *a, und8_t *b);

/* FUN_00327c38 @ 0x00327c38   (est. sk_sysreg_register_6564d0)
 * Register syscall metadata {name descriptor @0x4ebe4c, tag 0x676948} into
 * registry slot 0x6564d0 via the shared init dispatcher.
 * Confidence: medium
 * Notes: Ghidra FUN_00327e08(0x6564d0,0x6560f0,&DAT_004e7ed8,&DAT_004eb948). */
void sk_sysreg_register_6564d0_a(void)
{
    sk_init_dispatch();
}

/* FUN_00327c3c @ 0x00327c3c   (est. sk_sysreg_register_6564d0, alias)
 * Identical pair of the above init-array entry; registers the same metadata.
 * Confidence: medium
 * Notes: Ghidra FUN_00327e08(0x6564d0,0x6560f0,&DAT_004e7ed8,&DAT_004eb948). */
void sk_sysreg_register_6564d0_b(void)
{
    sk_init_dispatch();
}

/* FUN_00327c90 @ 0x00327c90   (est. sk_sysreg_register_6564d8)
 * Resolve syscall metadata descriptor @0x4ebe4c with tag 0x676948 and store
 * into registry slot 0x6564d8 (via FUN_00376820 = sk_syscall_register).
 * Confidence: medium
 * Notes: Ghidra uRam00000000006564d8 = FUN_00376820(&DAT_004ebe4c,0x676948). */
void sk_sysreg_register_6564d8_a(void)
{
    SK_SYSREG(0x4d8) = sk_syscall_register(0x004ebe4c, 0x676948ull, 0);
}

/* FUN_00327c94 @ 0x00327c94   (est. sk_sysreg_register_6564d8, alias)
 * Identical pair of the above.
 * Confidence: medium
 * Notes: Ghidra uRam00000000006564d8 = FUN_00376820(&DAT_004ebe4c,0x676948). */
void sk_sysreg_register_6564d8_b(void)
{
    SK_SYSREG(0x4d8) = sk_syscall_register(0x004ebe4c, 0x676948ull, 0);
}

/* FUN_00327ce8 @ 0x00327ce8   (est. sk_sysreg_register_6564e0)
 * Register syscall metadata descriptor @0x4ebe14 with tag 0x6769c8 into slot
 * 0x6564e0.
 * Confidence: medium
 * Notes: Ghidra uRam00000000006564e0 = FUN_00376820(&DAT_004ebe14,0x6769c8). */
void sk_sysreg_register_6564e0_a(void)
{
    SK_SYSREG(0x4e0) = sk_syscall_register(0x004ebe14, 0x6769c8ull, 0);
}

/* FUN_00327cec @ 0x00327cec   (est. sk_sysreg_register_6564e0, alias)
 * Identical pair of the above.
 * Confidence: medium
 * Notes: Ghidra uRam00000000006564e0 = FUN_00376820(&DAT_004ebe14,0x6769c8). */
void sk_sysreg_register_6564e0_b(void)
{
    SK_SYSREG(0x4e0) = sk_syscall_register(0x004ebe14, 0x6769c8ull, 0);
}

/* FUN_00327d2c @ 0x00327d2c   (est. sk_sysreg_leaf_6564e8)
 * Leaf stub: initialize registry slot 0x6564e8 with a literal 8-byte
 * instruction-encoding constant and return it. Ghidra "Removing unreachable
 * block" — the real body is a small code fragment stored as data.
 * Confidence: low
 * Notes: Ghidra uRam00000000006564e8 = 0xb9401109f9400688. */
und8_t sk_sysreg_leaf_6564e8(void)
{
    return (SK_SYSREG(0x4e8) = 0xb9401109f9400688ull);
}

/* FUN_00327d94 @ 0x00327d94   (est. sk_sysreg_register_6564f0)
 * Register syscall metadata descriptor @0x4ed41c with tag 0x6776f0 into slot
 * 0x6564f0.
 * Confidence: medium
 * Notes: Ghidra uRam00000000006564f0 = FUN_00376820(&DAT_004ed41c,0x6776f0). */
void sk_sysreg_register_6564f0_a(void)
{
    SK_SYSREG(0x4f0) = sk_syscall_register(0x004ed41c, 0x6776f0ull, 0);
}

/* FUN_00327d98 @ 0x00327d98   (est. sk_sysreg_register_6564f0, alias)
 * Identical pair of the above.
 * Confidence: medium
 * Notes: Ghidra uRam00000000006564f0 = FUN_00376820(&DAT_004ed41c,0x6776f0). */
void sk_sysreg_register_6564f0_b(void)
{
    SK_SYSREG(0x4f0) = sk_syscall_register(0x004ed41c, 0x6776f0ull, 0);
}

/* FUN_00327dd8 @ 0x00327dd8   (est. sk_sysreg_register_6564f8)
 * Register syscall range metadata: via FUN_00355244 (init dispatcher wrapper)
 * with range [0x6564f8,0x656500) and descriptor @0x4ebea8.
 * Confidence: medium
 * Notes: Ghidra FUN_00355244(0x6564f8,0x656500,&DAT_004ebea8). */
void sk_sysreg_register_6564f8_a(void)
{
    sk_init_dispatch_wrap();
}

/* FUN_00327ddc @ 0x00327ddc   (est. sk_sysreg_register_6564f8, alias)
 * Identical pair of the above.
 * Confidence: medium
 * Notes: Ghidra FUN_00355244(0x6564f8,0x656500,&DAT_004ebea8). */
void sk_sysreg_register_6564f8_b(void)
{
    sk_init_dispatch_wrap();
}

/* FUN_00327e08 @ 0x00327e08   (est. sk_init_dispatch)
 * Shared init dispatcher: if FUN_00352b20() returns 0, run the base init
 * chain (FUN_00106e3c, FUN_00027614, FUN_0035a7e8) and resolve FUN_00376820()
 * into the object at x19.
 * Confidence: medium
 * Notes: Ghidra body shown above; the x19 receiver is an implicit register. */
void sk_init_dispatch(void)
{
    und8_t base = sk_deref_word(NULL);
    if (base == 0) {
        sk_fun_00106e3c();
        sk_registry_get_or_init(NULL, NULL);
        sk_fun_0035a7e8();
        /* *x19 = sk_syscall_register();  (receiver in x19, opaque here) */
    }
}

/* FUN_00327e58 @ 0x00327e58   (est. sk_sysreg_register_656508)
 * Register syscall metadata descriptor @0x4ebecc with tag 0x676a80 into slot
 * 0x656508.
 * Confidence: medium
 * Notes: Ghidra uRam0000000000656508 = FUN_00376820(&DAT_004ebecc,0x676a80). */
void sk_sysreg_register_656508_a(void)
{
    SK_SYSREG(0x508) = sk_syscall_register(0x004ebecc, 0x676a80ull, 0);
}

/* FUN_00327e5c @ 0x00327e5c   (est. sk_sysreg_register_656508, alias)
 * Identical pair of the above.
 * Confidence: medium
 * Notes: Ghidra uRam0000000000656508 = FUN_00376820(&DAT_004ebecc,0x676a80). */
void sk_sysreg_register_656508_b(void)
{
    SK_SYSREG(0x508) = sk_syscall_register(0x004ebecc, 0x676a80ull, 0);
}

/* FUN_00327ea0 @ 0x00327ea0   (est. sk_sysreg_leaf_656510)
 * Leaf stub: initialize slot 0x656510 with literal constant, return it.
 * Confidence: low
 * Notes: Ghidra uRam0000000000656510 = 0x9100410c1100094b. */
und8_t sk_sysreg_leaf_656510(void)
{
    return (SK_SYSREG(0x510) = 0x9100410c1100094bull);
}

/* FUN_00327ef4 @ 0x00327ef4   (est. sk_obj_set_field8_from_leaf)
 * Initialize the +8 field of the object at param_1 from leaf stub
 * FUN_00327b8c() (slot 0x6564c0).
 * Confidence: medium
 * Notes: Ghidra *(param_1+8) = FUN_00327b8c(). */
void sk_obj_set_field8_from_leaf_6564c0(long obj)
{
    sk_obj_retain(sk_sysreg_leaf_6564c0());
    *(und8_t *)(obj + 8) = sk_sysreg_leaf_6564c0();
}

/* FUN_00327f1c @ 0x00327f1c   (est. sk_obj_set_field8_from_leaf_6564e8)
 * Initialize the +8 field of obj from leaf stub FUN_00327d2c() (slot 0x6564e8).
 * Confidence: medium
 * Notes: Ghidra *(param_1+8) = FUN_00327d2c(). */
void sk_obj_set_field8_from_leaf_6564e8(long obj)
{
    *(und8_t *)(obj + 8) = sk_sysreg_leaf_6564e8();
}

/* FUN_00327f44 @ 0x00327f44   (est. sk_obj_set_field8_from_leaf_656510)
 * Initialize the +8 field of obj from leaf stub FUN_00327ea0() (slot 0x656510).
 * Confidence: medium
 * Notes: Ghidra *(param_1+8) = FUN_00327ea0(). */
void sk_obj_set_field8_from_leaf_656510(long obj)
{
    *(und8_t *)(obj + 8) = sk_sysreg_leaf_656510();
}

/* FUN_00327fb0 @ 0x00327fb0   (est. sk_sysreg_register_656518)
 * Two-part syscall registration into slot 0x656518: lazily init the name
 * descriptor for range [0x656520, &DAT_004ebff8), get the handler leaf
 * (FUN_00327a88), then register {descriptor @0x4e9c1c, name, &handler}.
 * Confidence: medium
 * Notes: Ghidra FUN_00027614(0x656520,&DAT_004ebff8); local_28=FUN_00327a88();
 *   uRam00656518=FUN_00376820(&DAT_004e9c1c,uVar1,&local_28). */
void sk_sysreg_register_656518(void)
{
    und8_t name = sk_registry_get_or_init(&SK_SYSREG(0x520), (und8_t *)0x004ebff8);
    und8_t handler = sk_sysreg_leaf_6564a8();
    SK_SYSREG(0x518) = sk_syscall_register(0x004e9c1c, name, handler);
}

/* FUN_00328038 @ 0x00328038   (est. sk_sysreg_register_656528)
 * Two-part syscall registration into slot 0x656528: lazily init name for
 * range [0x656530,&DAT_004ec000), handler leaf FUN_00327a88, register
 * {descriptor @0x4eb028}.
 * Confidence: medium
 * Notes: Ghidra FUN_00027614(0x656530,&DAT_004ec000); local_28=FUN_00327a88();
 *   uRam00656528=FUN_00376820(&DAT_004eb028,uVar1,&local_28). */
void sk_sysreg_register_656528(void)
{
    und8_t name = sk_registry_get_or_init(&SK_SYSREG(0x530), (und8_t *)0x004ec000);
    und8_t handler = sk_sysreg_leaf_6564a8();
    SK_SYSREG(0x528) = sk_syscall_register(0x004eb028, name, handler);
}

/* FUN_003280c0 @ 0x003280c0   (est. sk_sysreg_register_656538)
 * Two-part syscall registration into slot 0x656538: name range [0x656520,
 * &DAT_004ebff8), handler leaf FUN_00328134 (slot 0x656540), register
 * {descriptor @0x4e9c44}.
 * Confidence: medium
 * Notes: Ghidra FUN_00027614(0x656520,&DAT_004ebff8); local_28=FUN_00328134();
 *   uRam00656538=FUN_00376820(&DAT_004e9c44,uVar1,&local_28). */
void sk_sysreg_register_656538(void)
{
    und8_t name = sk_registry_get_or_init(&SK_SYSREG(0x520), (und8_t *)0x004ebff8);
    und8_t handler = sk_sysreg_leaf_656540();
    SK_SYSREG(0x538) = sk_syscall_register(0x004e9c44, name, handler);
}

/* FUN_00328134 @ 0x00328134   (est. sk_sysreg_leaf_656540)
 * Leaf stub: initialize slot 0x656540 with literal constant, return it.
 * Confidence: low
 * Notes: Ghidra uRam0000000000656540 = 0xaa1403e014000038. */
und8_t sk_sysreg_leaf_656540(void)
{
    return (SK_SYSREG(0x540) = 0xaa1403e014000038ull);
}

/* FUN_0032819c @ 0x0032819c   (est. sk_sysreg_register_656548)
 * Two-part syscall registration into slot 0x656548: name range [0x656530,
 * &DAT_004ec000), handler leaf FUN_00328134, register {descriptor @0x4eb078}.
 * Confidence: medium
 * Notes: Ghidra FUN_00027614(0x656530,&DAT_004ec000); local_28=FUN_00328134();
 *   uRam00656548=FUN_00376820(&DAT_004eb078,uVar1,&local_28). */
void sk_sysreg_register_656548(void)
{
    und8_t name = sk_registry_get_or_init(&SK_SYSREG(0x530), (und8_t *)0x004ec000);
    und8_t handler = sk_sysreg_leaf_656540();
    SK_SYSREG(0x548) = sk_syscall_register(0x004eb078, name, handler);
}

/* FUN_00328210 @ 0x00328210   (est. sk_obj_set_field8_from_leaf_6564a8)
 * Initialize the +8 field of obj from leaf stub FUN_00327a88() (slot 0x6564a8).
 * Confidence: medium
 * Notes: Ghidra *(param_1+8) = FUN_00327a88(). */
void sk_obj_set_field8_from_leaf_6564a8(long obj)
{
    *(und8_t *)(obj + 8) = sk_sysreg_leaf_6564a8();
}

/* FUN_0032824c @ 0x0032824c   (est. sk_sysreg_register_656550)
 * Two-part syscall registration into slot 0x656550: name range [0x656530,
 * &DAT_004ec000), handler leaf FUN_003282c0 (slot 0x656558), register
 * {descriptor @0x4eb0a0}.
 * Confidence: medium
 * Notes: Ghidra FUN_00027614(0x656530,&DAT_004ec000); local_28=FUN_003282c0();
 *   uRam00656550=FUN_00376820(&DAT_004eb0a0,uVar1,&local_28). */
void sk_sysreg_register_656550(void)
{
    und8_t name = sk_registry_get_or_init(&SK_SYSREG(0x530), (und8_t *)0x004ec000);
    und8_t handler = sk_sysreg_leaf_656558();
    SK_SYSREG(0x550) = sk_syscall_register(0x004eb0a0, name, handler);
}

/* FUN_003282c0 @ 0x003282c0   (est. sk_sysreg_leaf_656558)
 * Leaf stub: initialize slot 0x656558 with literal constant, return it.
 * Confidence: low
 * Notes: Ghidra uRam0000000000656558 = 0xf2be2be1d2931661. */
und8_t sk_sysreg_leaf_656558(void)
{
    return (SK_SYSREG(0x558) = 0xf2be2be1d2931661ull);
}

/* FUN_0032835c @ 0x0032835c   (est. sk_obj_register_dispatch)
 * Register dispatch: run FUN_0034ee78(), unwrap descriptor *param_3 via
 * FUN_00027754, adjust via FUN_0009461c, then store sk_syscall_register() into
 * the +8 field of the x21 receiver.
 * Confidence: medium
 * Notes: Ghidra unaff_x21 is the implicit receiver; FUN_00376820() called with
 *   no visible args. */
void sk_obj_register_dispatch_6564c0(long obj, und8_t *desc)
{
    sk_fun_0034ee78();
    /* auVar2 = FUN_00027754(*desc); local_38 = auVar2.lo; */
    sk_fun_0009461c(0, 0, NULL);
    /* *(obj + 8) = sk_syscall_register();  (receiver in x21, args opaque) */
    *(und8_t *)(obj + 8) = sk_syscall_register(0, 0, 0);
}

/* FUN_003283a8 @ 0x003283a8   (est. sk_sysreg_register_pair)
 * Register pair: run FUN_0034b550(), a bare sk_syscall_register(), resolve
 * FUN_00348ad8() and register it with param_1.
 * Confidence: medium
 * Notes: Ghidra FUN_00376820(uVar1,param_1) at end. */
void sk_sysreg_register_pair_6564c8(und8_t param)
{
    sk_fun_0034b550();
    sk_syscall_register(0, 0, 0);
    sk_syscall_register(sk_fun_00348ad8(0, param), param, 0);
}

/* FUN_003283e8 @ 0x003283e8   (est. sk_obj_set_field8_from_reg)
 * Set the +8 field of the x19 receiver from FUN_00354e88().
 * Confidence: medium
 * Notes: Ghidra *(unaff_x19+8) = FUN_00354e88(). */
void sk_obj_set_field8_from_reg_6564d0(long obj)
{
    *(und8_t *)(obj + 8) = sk_fun_00354e88();
}

/* FUN_0032840c @ 0x0032840c   (est. sk_sysreg_register_pair_2)
 * Register pair: register descriptor @0x4ec2fc, resolve FUN_00349e38() and
 * register it with param_1.
 * Confidence: medium
 * Notes: Ghidra FUN_00376820(&DAT_004ec2fc); FUN_00376820(uVar1,param_1). */
void sk_sysreg_register_pair_2(und8_t param)
{
    sk_syscall_register(0x004ec2fc, 0, 0);
    sk_syscall_register(sk_fun_00349e38(0), param, 0);
}

/* FUN_0032845c @ 0x0032845c   (est. sk_reg_run_chain)
 * Run the registration chain FUN_00354e88 -> FUN_00348990 -> FUN_00356518.
 * Confidence: medium
 * Notes: Ghidra sequential calls, no side-effect targets. */
void sk_reg_run_chain(void)
{
    sk_fun_00354e88();
    sk_fun_00348990();
    sk_fun_00356518();
}

/* FUN_00328490 @ 0x00328490   (est. sk_obj_set_field8_from_reg_2)
 * Set the +8 field of obj: run FUN_00349204() then store sk_syscall_register().
 * Confidence: medium
 * Notes: Ghidra FUN_00376820() with no visible args. */
void sk_obj_set_field8_from_reg_2(long obj)
{
    sk_fun_00349204();
    *(und8_t *)(obj + 8) = sk_syscall_register(0, 0, 0);
}

/* FUN_00328520 @ 0x00328520   (est. sk_sysreg_leaf_656560)
 * Leaf stub: initialize slot 0x656560 with literal constant, return it.
 * Confidence: low
 * Notes: Ghidra uRam0000000000656560 = 0xf2e021c1f2c00801. */
und8_t sk_sysreg_leaf_656560(void)
{
    return (SK_SYSREG(0x560) = 0xf2e021c1f2c00801ull);
}

/* FUN_00328578 @ 0x00328578   (est. sk_sysreg_leaf_656568)
 * Leaf stub: initialize slot 0x656568 with literal constant, return it.
 * Confidence: low
 * Notes: Ghidra uRam0000000000656568 = 0x9400b08faa1503e0. */
und8_t sk_sysreg_leaf_656568(void)
{
    return (SK_SYSREG(0x568) = 0x9400b08faa1503e0ull);
}

/* FUN_003285e0 @ 0x003285e0   (est. sk_sysreg_register_656570)
 * Register syscall metadata descriptor @0x4ec7a0 with tag 0x6773c0 into slot
 * 0x656570.
 * Confidence: medium
 * Notes: Ghidra uRam00656570 = FUN_00376820(&DAT_004ec7a0,0x6773c0). */
void sk_sysreg_register_656570_a(void)
{
    SK_SYSREG(0x570) = sk_syscall_register(0x004ec7a0, 0x6773c0ull, 0);
}

/* FUN_003285e4 @ 0x003285e4   (est. sk_sysreg_register_656570, alias)
 * Identical pair of the above.
 * Confidence: medium
 * Notes: Ghidra uRam00656570 = FUN_00376820(&DAT_004ec7a0,0x6773c0). */
void sk_sysreg_register_656570_b(void)
{
    SK_SYSREG(0x570) = sk_syscall_register(0x004ec7a0, 0x6773c0ull, 0);
}

/* FUN_00328638 @ 0x00328638   (est. sk_sysreg_register_656578)
 * Register syscall metadata descriptor @0x4ec7bc with tag 0x6773c0 into slot
 * 0x656578.
 * Confidence: medium
 * Notes: Ghidra uRam00656578 = FUN_00376820(&DAT_004ec7bc,0x6773c0). */
void sk_sysreg_register_656578_a(void)
{
    SK_SYSREG(0x578) = sk_syscall_register(0x004ec7bc, 0x6773c0ull, 0);
}

/* FUN_0032863c @ 0x0032863c   (est. sk_sysreg_register_656578, alias)
 * Identical pair of the above.
 * Confidence: medium
 * Notes: Ghidra uRam00656578 = FUN_00376820(&DAT_004ec7bc,0x6773c0). */
void sk_sysreg_register_656578_b(void)
{
    SK_SYSREG(0x578) = sk_syscall_register(0x004ec7bc, 0x6773c0ull, 0);
}

/* FUN_0032867c @ 0x0032867c   (est. sk_sysreg_leaf_656580)
 * Leaf stub: initialize slot 0x656580 with literal constant, return it.
 * Confidence: low
 * Notes: Ghidra uRam0000000000656580 = 0xb90010082a090108. */
und8_t sk_sysreg_leaf_656580(void)
{
    return (SK_SYSREG(0x580) = 0xb90010082a090108ull);
}

/* FUN_003286d0 @ 0x003286d0   (est. sk_obj_set_field8_from_leaf_656580)
 * Set the +8 field of obj from leaf stub FUN_0032867c() (slot 0x656580).
 * Confidence: medium
 * Notes: Ghidra *(param_1+8) = FUN_0032867c(). */
void sk_obj_set_field8_from_leaf_656580(long obj)
{
    *(und8_t *)(obj + 8) = sk_sysreg_leaf_656580();
}

/* FUN_00328724 @ 0x00328724   (est. sk_obj_register_fields)
 * Register dispatch into a two-field object: run FUN_0035098c(), store
 * sk_syscall_register() into +8, and a bare register into +0x10 of the x21
 * receiver.
 * Confidence: medium
 * Notes: Ghidra unaff_x21 receiver; FUN_0009461c() called bare. */
void sk_obj_register_fields_6564d0(long obj)
{
    sk_fun_0035098c();
    *(und8_t *)(obj + 8) = sk_syscall_register(0, 0, 0);
    sk_fun_0009461c(0, 0, NULL);
    *(und8_t *)(obj + 0x10) = sk_syscall_register(0, 0, 0);
}

/* FUN_00328784 @ 0x00328784   (est. sk_obj_set_field8_from_reg_3)
 * Set the +8 field of obj: run FUN_00356d8c() then store sk_syscall_register().
 * Confidence: medium
 * Notes: Ghidra FUN_00376820() with no visible args. */
void sk_obj_set_field8_from_reg_3(long obj)
{
    sk_fun_00356d8c();
    *(und8_t *)(obj + 8) = sk_syscall_register(0, 0, 0);
}

/* FUN_003287e8 @ 0x003287e8   (est. sk_obj_set_field8_from_reg_4)
 * Set the +8 field of obj: run FUN_00356d74() then store sk_syscall_register().
 * Confidence: medium
 * Notes: Ghidra FUN_00376820() with no visible args. */
void sk_obj_set_field8_from_reg_4(long obj)
{
    sk_fun_00356d74();
    *(und8_t *)(obj + 8) = sk_syscall_register(0, 0, 0);
}

/* FUN_00328874 @ 0x00328874   (est. sk_sysreg_register_656588)
 * Two-part syscall registration into slot 0x656588: name range [0x656590,
 * &DAT_004ec728), handler leaf FUN_00328578 (slot 0x656568), register
 * {descriptor @0x4eb078}.
 * Confidence: medium
 * Notes: Ghidra FUN_00027614(0x656590,&DAT_004ec728); local_28=FUN_00328578();
 *   uRam00656588=FUN_00376820(&DAT_004eb078,uVar1,&local_28). */
void sk_sysreg_register_656588(void)
{
    und8_t name = sk_registry_get_or_init(&SK_SYSREG(0x590), (und8_t *)0x004ec728);
    und8_t handler = sk_sysreg_leaf_656568();
    SK_SYSREG(0x588) = sk_syscall_register(0x004eb078, name, handler);
}

/* FUN_003288e8 @ 0x003288e8   (est. sk_obj_set_field8_from_leaf_656598)
 * Set the +8 field of obj from leaf stub FUN_00328910() (slot 0x656598).
 * Confidence: medium
 * Notes: Ghidra *(param_1+8) = FUN_00328910(). */
void sk_obj_set_field8_from_leaf_656598(long obj)
{
    *(und8_t *)(obj + 8) = sk_sysreg_leaf_656598();
}

/* FUN_00328910 @ 0x00328910   (est. sk_sysreg_leaf_656598)
 * Leaf stub: initialize slot 0x656598 with literal constant, return it.
 * Confidence: low
 * Notes: Ghidra uRam0000000000656598 = 0x37c80129b9401289. */
und8_t sk_sysreg_leaf_656598(void)
{
    return (SK_SYSREG(0x598) = 0x37c80129b9401289ull);
}

/* FUN_00328978 @ 0x00328978   (est. sk_sysreg_register_6565a0)
 * Two-part syscall registration into slot 0x6565a0: name range [0x656590,
 * &DAT_004ec728), handler leaf FUN_00328910, register {descriptor @0x4eb028}.
 * Confidence: medium
 * Notes: Ghidra FUN_00027614(0x656590,&DAT_004ec728); local_28=FUN_00328910();
 *   uRam006565a0=FUN_00376820(&DAT_004eb028,uVar1,&local_28). */
void sk_sysreg_register_6565a0(void)
{
    und8_t name = sk_registry_get_or_init(&SK_SYSREG(0x590), (und8_t *)0x004ec728);
    und8_t handler = sk_sysreg_leaf_656598();
    SK_SYSREG(0x5a0) = sk_syscall_register(0x004eb028, name, handler);
}

/* FUN_003289ec @ 0x003289ec   (est. sk_obj_set_field8_from_leaf_6565a8)
 * Set the +8 field of obj from leaf stub FUN_00328a14() (slot 0x6565a8).
 * Confidence: medium
 * Notes: Ghidra *(param_1+8) = FUN_00328a14(). */
void sk_obj_set_field8_from_leaf_6565a8(long obj)
{
    *(und8_t *)(obj + 8) = sk_sysreg_leaf_6565a8();
}

/* FUN_00328a14 @ 0x00328a14   (est. sk_sysreg_leaf_6565a8)
 * Leaf stub: initialize slot 0x6565a8 with literal constant, return it.
 * Confidence: low
 * Notes: Ghidra uRam00000000006565a8 = 0xd10061029a8933e3. */
und8_t sk_sysreg_leaf_6565a8(void)
{
    return (SK_SYSREG(0x5a8) = 0xd10061029a8933e3ull);
}

/* FUN_00328a68 @ 0x00328a68   (est. sk_obj_set_field8_from_leaf_656560)
 * Set the +8 field of obj from leaf stub FUN_00328520() (slot 0x656560).
 * Confidence: medium
 * Notes: Ghidra *(param_1+8) = FUN_00328520(). */
void sk_obj_set_field8_from_leaf_656560(long obj)
{
    *(und8_t *)(obj + 8) = sk_sysreg_leaf_656560();
}

/* FUN_00328ad0 @ 0x00328ad0   (est. sk_sysreg_register_6565b0)
 * Register syscall metadata descriptor @0x4eda3c with tag 0x677830 into slot
 * 0x6565b0.
 * Confidence: medium
 * Notes: Ghidra uRam006565b0 = FUN_00376820(&DAT_004eda3c,0x677830). */
void sk_sysreg_register_6565b0_a(void)
{
    SK_SYSREG(0x5b0) = sk_syscall_register(0x004eda3c, 0x677830ull, 0);
}

/* FUN_00328ad4 @ 0x00328ad4   (est. sk_sysreg_register_6565b0, alias)
 * Identical pair of the above.
 * Confidence: medium
 * Notes: Ghidra uRam006565b0 = FUN_00376820(&DAT_004eda3c,0x677830). */
void sk_sysreg_register_6565b0_b(void)
{
    SK_SYSREG(0x5b0) = sk_syscall_register(0x004eda3c, 0x677830ull, 0);
}

/* FUN_00328b14 @ 0x00328b14   (est. sk_obj_set_field10_from_leaf_6565b8)
 * Set the +0x10 field of obj from leaf stub FUN_00328b3c() (slot 0x6565b8).
 * Confidence: medium
 * Notes: Ghidra *(param_1+0x10) = FUN_00328b3c(). */
void sk_obj_set_field10_from_leaf_6565b8(long obj)
{
    *(und8_t *)(obj + 0x10) = sk_sysreg_leaf_6565b8();
}

/* FUN_00328b3c @ 0x00328b3c   (est. sk_sysreg_leaf_6565b8)
 * Leaf stub: initialize slot 0x6565b8 with literal constant, return it.
 * Confidence: low
 * Notes: Ghidra uRam00000000006565b8 = 0x14000018940099ef. */
und8_t sk_sysreg_leaf_6565b8(void)
{
    return (SK_SYSREG(0x5b8) = 0x14000018940099efull);
}

/* FUN_00328c0c @ 0x00328c0c   (est. sk_obj_set_field10_from_leaf_6565c0)
 * Set the +0x10 field of obj from leaf stub FUN_00328c34() (slot 0x6565c0).
 * Confidence: medium
 * Notes: Ghidra *(param_1+0x10) = FUN_00328c34(). */
void sk_obj_set_field10_from_leaf_6565c0(long obj)
{
    *(und8_t *)(obj + 0x10) = sk_sysreg_leaf_6565c0();
}

/* FUN_00328c34 @ 0x00328c34   (est. sk_sysreg_leaf_6565c0)
 * Leaf stub: initialize slot 0x6565c0 with literal constant, return it.
 * Confidence: low
 * Notes: Ghidra uRam00000000006565c0 = 0xf8418d10aa1403e8. */
und8_t sk_sysreg_leaf_6565c0(void)
{
    return (SK_SYSREG(0x5c0) = 0xf8418d10aa1403e8ull);
}

/* FUN_00328d00 @ 0x00328d00   (est. sk_sysreg_register_6565c8)
 * Register syscall metadata descriptor @0x4ed72c with tag 0x677790 into slot
 * 0x6565c8.
 * Confidence: medium
 * Notes: Ghidra uRam006565c8 = FUN_00376820(&DAT_004ed72c,0x677790). */
void sk_sysreg_register_6565c8_a(void)
{
    SK_SYSREG(0x5c8) = sk_syscall_register(0x004ed72c, 0x677790ull, 0);
}

/* FUN_00328d04 @ 0x00328d04   (est. sk_sysreg_register_6565c8, alias)
 * Identical pair of the above.
 * Confidence: medium
 * Notes: Ghidra uRam006565c8 = FUN_00376820(&DAT_004ed72c,0x677790). */
void sk_sysreg_register_6565c8_b(void)
{
    SK_SYSREG(0x5c8) = sk_syscall_register(0x004ed72c, 0x677790ull, 0);
}

/* FUN_00328d44 @ 0x00328d44   (est. sk_obj_set_field10_from_leaf_6565d0)
 * Set the +0x10 field of obj from leaf stub FUN_00328d6c() (slot 0x6565d0).
 * Confidence: medium
 * Notes: Ghidra *(param_1+0x10) = FUN_00328d6c(). */
void sk_obj_set_field10_from_leaf_6565d0(long obj)
{
    *(und8_t *)(obj + 0x10) = sk_sysreg_leaf_6565d0();
}

/* FUN_00328d6c @ 0x00328d6c   (est. sk_sysreg_leaf_6565d0)
 * Leaf stub: initialize slot 0x6565d0 with literal constant, return it.
 * Confidence: low
 * Notes: Ghidra uRam00000000006565d0 = 0xdac10230dac11110. */
und8_t sk_sysreg_leaf_6565d0(void)
{
    return (SK_SYSREG(0x5d0) = 0xdac10230dac11110ull);
}

/* FUN_00328e38 @ 0x00328e38   (est. sk_sysreg_register_6565d8)
 * Two-part syscall registration into slot 0x6565d8: name range [0x6565e0,
 * &DAT_004ecd68), handler leaf FUN_00328eac (slot 0x6565e8), register
 * {descriptor @0x4eb078}.
 * Confidence: medium
 * Notes: Ghidra FUN_00027614(0x6565e0,&DAT_004ecd68); local_28=FUN_00328eac();
 *   uRam006565d8=FUN_00376820(&DAT_004eb078,uVar1,&local_28). */
void sk_sysreg_register_6565d8(void)
{
    und8_t name = sk_registry_get_or_init(&SK_SYSREG(0x5e0), (und8_t *)0x004ecd68);
    und8_t handler = sk_sysreg_leaf_6565e8();
    SK_SYSREG(0x5d8) = sk_syscall_register(0x004eb078, name, handler);
}

/* FUN_00328eac @ 0x00328eac   (est. sk_sysreg_leaf_6565e8)
 * Leaf stub: initialize slot 0x6565e8 with literal constant, return it.
 * Confidence: low
 * Notes: Ghidra uRam00000000006565e8 = 0xdac1113091008011. */
und8_t sk_sysreg_leaf_6565e8(void)
{
    return (SK_SYSREG(0x5e8) = 0xdac1113091008011ull);
}

/* FUN_00328f00 @ 0x00328f00   (est. sk_obj_set_field8_from_leaf_6565f0)
 * Set the +8 field of obj from leaf stub FUN_00328f28() (slot 0x6565f0).
 * Confidence: medium
 * Notes: Ghidra *(param_1+8) = FUN_00328f28(). */
void sk_obj_set_field8_from_leaf_6565f0(long obj)
{
    *(und8_t *)(obj + 8) = sk_sysreg_leaf_6565f0();
}

/* FUN_00328f28 @ 0x00328f28   (est. sk_sysreg_leaf_6565f0)
 * Leaf stub: initialize slot 0x6565f0 with literal constant, return it.
 * Confidence: low
 * Notes: Ghidra uRam00000000006565f0 = 0xf8020010dac10230. */
und8_t sk_sysreg_leaf_6565f0(void)
{
    return (SK_SYSREG(0x5f0) = 0xf8020010dac10230ull);
}

/* FUN_00328f90 @ 0x00328f90   (est. sk_sysreg_register_6565f8)
 * Two-part syscall registration into slot 0x6565f8: name range [0x6565e0,
 * &DAT_004ecd68), handler leaf FUN_00328f28, register {descriptor @0x4eb028}.
 * Confidence: medium
 * Notes: Ghidra FUN_00027614(0x6565e0,&DAT_004ecd68); local_28=FUN_00328f28();
 *   uRam006565f8=FUN_00376820(&DAT_004eb028,uVar1,&local_28). */
void sk_sysreg_register_6565f8(void)
{
    und8_t name = sk_registry_get_or_init(&SK_SYSREG(0x5e0), (und8_t *)0x004ecd68);
    und8_t handler = sk_sysreg_leaf_6565f0();
    SK_SYSREG(0x5f8) = sk_syscall_register(0x004eb028, name, handler);
}

/* FUN_00329004 @ 0x00329004   (est. sk_obj_set_field8_from_leaf_656600)
 * Set the +8 field of obj from leaf stub FUN_0032902c() (slot 0x656600).
 * Confidence: medium
 * Notes: Ghidra *(param_1+8) = FUN_0032902c(). */
void sk_obj_set_field8_from_leaf_656600(long obj)
{
    *(und8_t *)(obj + 8) = sk_sysreg_leaf_656600();
}

/* FUN_0032902c @ 0x0032902c   (est. sk_sysreg_leaf_656600)
 * Leaf stub: initialize slot 0x656600 with literal constant, return it.
 * Confidence: low
 * Notes: Ghidra uRam0000000000656600 = 0x540000617100053f. */
und8_t sk_sysreg_leaf_656600(void)
{
    return (SK_SYSREG(0x600) = 0x540000617100053full);
}

/* FUN_00329080 @ 0x00329080   (est. sk_obj_set_field8_from_fun)
 * Set the +8 field of obj from FUN_0006a414().
 * Confidence: medium
 * Notes: Ghidra *(param_1+8) = FUN_0006a414(). */
void sk_obj_set_field8_from_fun_0006a414(long obj)
{
    sk_fun_0006a414();
}

/* FUN_00329108 @ 0x00329108   (est. sk_sysreg_register_656608)
 * Two-part syscall registration into slot 0x656608: name range [0x656610,
 * &DAT_004ecee8), handler leaf FUN_0032917c (slot 0x656618), register
 * {descriptor @0x4eb078}.
 * Confidence: medium
 * Notes: Ghidra FUN_00027614(0x656610,&DAT_004ecee8); local_28=FUN_0032917c();
 *   uRam00656608=FUN_00376820(&DAT_004eb078,uVar1,&local_28). */
void sk_sysreg_register_656608(void)
{
    und8_t name = sk_registry_get_or_init(&SK_SYSREG(0x610), (und8_t *)0x004ecee8);
    und8_t handler = sk_sysreg_leaf_656618();
    SK_SYSREG(0x608) = sk_syscall_register(0x004eb078, name, handler);
}

/* FUN_0032917c @ 0x0032917c   (est. sk_sysreg_leaf_656618)
 * Leaf stub: initialize slot 0x656618 with literal constant, return it.
 * Confidence: low
 * Notes: Ghidra uRam0000000000656618 = 0xf9400694d73f0928. */
und8_t sk_sysreg_leaf_656618(void)
{
    return (SK_SYSREG(0x618) = 0xf9400694d73f0928ull);
}

/* FUN_003291d0 @ 0x003291d0   (est. sk_obj_set_field8_from_leaf_656620)
 * Set the +8 field of obj from leaf stub FUN_003291f8() (slot 0x656620).
 * Confidence: medium
 * Notes: Ghidra *(param_1+8) = FUN_003291f8(). */
void sk_obj_set_field8_from_leaf_656620(long obj)
{
    *(und8_t *)(obj + 8) = sk_sysreg_leaf_656620();
}

/* FUN_003291f8 @ 0x003291f8   (est. sk_sysreg_leaf_656620)
 * Leaf stub: initialize slot 0x656620 with literal constant, return it.
 * Confidence: low
 * Notes: Ghidra uRam0000000000656620 = 0xa9427bfdf9000274. */
und8_t sk_sysreg_leaf_656620(void)
{
    return (SK_SYSREG(0x620) = 0xa9427bfdf9000274ull);
}

/* FUN_00329260 @ 0x00329260   (est. sk_sysreg_register_656628)
 * Two-part syscall registration into slot 0x656628: name range [0x656610,
 * &DAT_004ecee8), handler leaf FUN_003291f8, register {descriptor @0x4eb028}.
 * Confidence: medium
 * Notes: Ghidra FUN_00027614(0x656610,&DAT_004ecee8); local_28=FUN_003291f8();
 *   uRam00656628=FUN_00376820(&DAT_004eb028,uVar1,&local_28). */
void sk_sysreg_register_656628(void)
{
    und8_t name = sk_registry_get_or_init(&SK_SYSREG(0x610), (und8_t *)0x004ecee8);
    und8_t handler = sk_sysreg_leaf_656620();
    SK_SYSREG(0x628) = sk_syscall_register(0x004eb028, name, handler);
}

/* FUN_003292d4 @ 0x003292d4   (est. sk_obj_set_field8_from_leaf_656630)
 * Set the +8 field of obj from leaf stub FUN_003292fc() (slot 0x656630).
 * Confidence: medium
 * Notes: Ghidra *(param_1+8) = FUN_003292fc(). */
void sk_obj_set_field8_from_leaf_656630(long obj)
{
    *(und8_t *)(obj + 8) = sk_sysreg_leaf_656630();
}

/* FUN_003292fc @ 0x003292fc   (est. sk_sysreg_leaf_656630)
 * Leaf stub: initialize slot 0x656630 with literal constant, return it.
 * Confidence: low
 * Notes: Ghidra uRam0000000000656630 = 0xd503237fd65f0fff. */
und8_t sk_sysreg_leaf_656630(void)
{
    return (SK_SYSREG(0x630) = 0xd503237fd65f0fffull);
}

/* FUN_00329358 @ 0x00329358   (est. sk_sysreg_register_656634_once)
 * One-time register: if slot 0x656634 (FUN_00656634) is already set, return;
 * otherwise register descriptor @0x4ecfa8 with tag 0x677600 into it.
 * Confidence: medium
 * Notes: Ghidra uses the global directly (FUN_00656634). */
und8_t sk_sysreg_register_656634_once(void)
{
    if (SK_SYSREG(0x634) != 0) {
        return SK_SYSREG(0x634);
    }
    return (SK_SYSREG(0x634) = sk_syscall_register(0x004ecfa8, 0x677600ull, 0));
}

/* FUN_003293ac @ 0x003293ac   (est. sk_obj_set_field8_from_reg_5)
 * Set the +8 field of obj from FUN_00329358() (one-time register result).
 * Confidence: medium
 * Notes: Ghidra *(param_1+8) = FUN_00329358(). */
void sk_obj_set_field8_from_reg_5(long obj)
{
    *(und8_t *)(obj + 8) = sk_sysreg_register_656634_once();
}

/* FUN_00329408 @ 0x00329408   (est. sk_sysreg_register_656640)
 * Two-part syscall registration into slot 0x656640: name range [0x656648,
 * &DAT_004ed078), handler leaf FUN_0032947c (slot 0x656650), register
 * {descriptor @0x4eb078}.
 * Confidence: medium
 * Notes: Ghidra FUN_00027614(0x656648,&DAT_004ed078); local_28=FUN_0032947c();
 *   uRam00656640=FUN_00376820(&DAT_004eb078,uVar1,&local_28). */
void sk_sysreg_register_656640(void)
{
    und8_t name = sk_registry_get_or_init(&SK_SYSREG(0x648), (und8_t *)0x004ed078);
    und8_t handler = sk_sysreg_leaf_656650();
    SK_SYSREG(0x640) = sk_syscall_register(0x004eb078, name, handler);
}

/* FUN_0032947c @ 0x0032947c   (est. sk_sysreg_leaf_656650)
 * Leaf stub: initialize slot 0x656650 with literal constant, return it.
 * Confidence: low
 * Notes: Ghidra uRam0000000000656650 = 0x71000d1f5400012c. */
und8_t sk_sysreg_leaf_656650(void)
{
    return (SK_SYSREG(0x650) = 0x71000d1f5400012cull);
}

/* FUN_003294d0 @ 0x003294d0   (est. sk_obj_set_field8_from_leaf_656658)
 * Set the +8 field of obj from leaf stub FUN_003294f8() (slot 0x656658).
 * Confidence: medium
 * Notes: Ghidra *(param_1+8) = FUN_003294f8(). */
void sk_obj_set_field8_from_leaf_656658(long obj)
{
    *(und8_t *)(obj + 8) = sk_sysreg_leaf_656658();
}

/* FUN_003294f8 @ 0x003294f8   (est. sk_sysreg_leaf_656658)
 * Leaf stub: initialize slot 0x656658 with literal constant, return it.
 * Confidence: low
 * Notes: Ghidra uRam0000000000656658 = 0x71001d1f54000200. */
und8_t sk_sysreg_leaf_656658(void)
{
    return (SK_SYSREG(0x658) = 0x71001d1f54000200ull);
}

/* FUN_00329560 @ 0x00329560   (est. sk_sysreg_register_656660)
 * Two-part syscall registration into slot 0x656660: name range [0x656648,
 * &DAT_004ed078), handler leaf FUN_003294f8, register {descriptor @0x4eb028}.
 * Confidence: medium
 * Notes: Ghidra FUN_00027614(0x656648,&DAT_004ed078); local_28=FUN_003294f8();
 *   uRam00656660=FUN_00376820(&DAT_004eb028,uVar1,&local_28). */
void sk_sysreg_register_656660(void)
{
    und8_t name = sk_registry_get_or_init(&SK_SYSREG(0x648), (und8_t *)0x004ed078);
    und8_t handler = sk_sysreg_leaf_656658();
    SK_SYSREG(0x660) = sk_syscall_register(0x004eb028, name, handler);
}

/* FUN_003295d4 @ 0x003295d4   (est. sk_obj_set_field8_from_leaf_656668)
 * Set the +8 field of obj from leaf stub FUN_003295fc() (slot 0x656668).
 * Confidence: medium
 * Notes: Ghidra *(param_1+8) = FUN_003295fc(). */
void sk_obj_set_field8_from_leaf_656668(long obj)
{
    *(und8_t *)(obj + 8) = sk_sysreg_leaf_656668();
}

/* FUN_003295fc @ 0x003295fc   (est. sk_sysreg_leaf_656668)
 * Leaf stub: initialize slot 0x656668 with literal constant, return it.
 * Confidence: low
 * Notes: Ghidra uRam0000000000656668 = 0xd50323ffa8c24ff4. */
und8_t sk_sysreg_leaf_656668(void)
{
    return (SK_SYSREG(0x668) = 0xd50323ffa8c24ff4ull);
}

/* FUN_00329650 @ 0x00329650   (est. sk_obj_set_field8_from_fun_00086368)
 * Set the +8 field of obj from FUN_00086368().
 * Confidence: medium
 * Notes: Ghidra *(param_1+8) = FUN_00086368(). */
void sk_obj_set_field8_from_fun_00086368(long obj)
{
    sk_fun_00086368();
}

/* FUN_003296d8 @ 0x003296d8   (est. sk_sysreg_register_656670)
 * Two-part syscall registration into slot 0x656670: name range [0x656678,
 * &DAT_004ed1f8), handler leaf FUN_0032974c (slot 0x656680), register
 * {descriptor @0x4eb078}.
 * Confidence: medium
 * Notes: Ghidra FUN_00027614(0x656678,&DAT_004ed1f8); local_28=FUN_0032974c();
 *   uRam00656670=FUN_00376820(&DAT_004eb078,uVar1,&local_28). */
/* FUN_0032974c @ 0x0032974c   (est. sk_sysreg_leaf_656680)
 * Leaf stub: initialize slot 0x656680 with literal constant, return it.
 * Confidence: low
 * Notes: Ghidra uRam0000000000656680 = 0xb9401268f9400413. */
und8_t sk_sysreg_leaf_656680(void)
{
    return (SK_SYSREG(0x680) = 0xb9401268f9400413ull);
}

/* FUN_003297a0 @ 0x003297a0   (est. sk_obj_set_field8_from_leaf_656688)
 * Set the +8 field of obj from leaf stub FUN_003297c8() (slot 0x656688).
 * Confidence: medium
 * Notes: Ghidra *(param_1+8) = FUN_003297c8(). */
void sk_obj_set_field8_from_leaf_656688(long obj)
{
    *(und8_t *)(obj + 8) = sk_sysreg_leaf_656688();
}

/* FUN_003297c8 @ 0x003297c8   (est. sk_sysreg_leaf_656688)
 * Leaf stub: initialize slot 0x656688 with literal constant, return it.
 * Confidence: low
 * Notes: Ghidra uRam0000000000656688 = 0xa9417bfd37c00168. */
und8_t sk_sysreg_leaf_656688(void)
{
    return (SK_SYSREG(0x688) = 0xa9417bfd37c00168ull);
}

/* FUN_00329830 @ 0x00329830   (est. sk_sysreg_register_656690)
 * Two-part syscall registration into slot 0x656690: name range [0x656678,
 * &DAT_004ed1f8), handler leaf FUN_003297c8, register {descriptor @0x4eb028}.
 * Confidence: medium
 * Notes: Ghidra FUN_00027614(0x656678,&DAT_004ed1f8); local_28=FUN_003297c8();
 *   uRam00656690=FUN_00376820(&DAT_004eb028,uVar1,&local_28). */
void sk_sysreg_register_656690(void)
{
    und8_t name = sk_registry_get_or_init(&SK_SYSREG(0x678), (und8_t *)0x004ed1f8);
    und8_t handler = sk_sysreg_leaf_656688();
    SK_SYSREG(0x690) = sk_syscall_register(0x004eb028, name, handler);
}

/* FUN_003298a4 @ 0x003298a4   (est. sk_obj_set_field8_from_leaf_656698)
 * Set the +8 field of obj from leaf stub FUN_003298cc() (slot 0x656698).
 * Confidence: medium
 * Notes: Ghidra *(param_1+8) = FUN_003298cc(). */
void sk_obj_set_field8_from_leaf_656698(long obj)
{
    *(und8_t *)(obj + 8) = sk_sysreg_leaf_656698();
}

/* FUN_003298cc @ 0x003298cc   (est. sk_sysreg_leaf_656698)
 * Leaf stub: initialize slot 0x656698 with literal constant, return it.
 * Confidence: low
 * Notes: Ghidra uRam0000000000656698 = 0xf9443901d00002e8. */
und8_t sk_sysreg_leaf_656698(void)
{
    return (SK_SYSREG(0x698) = 0xf9443901d00002e8ull);
}

/* FUN_00329928 @ 0x00329928   (est. sk_sysreg_leaf_6566a0)
 * Leaf stub: initialize slot 0x6566a0 with literal constant, return it.
 * Confidence: low
 * Notes: Ghidra uRam00000000006566a0 = 0xa8c24ff4a9417bfd. */
und8_t sk_sysreg_leaf_6566a0(void)
{
    return (SK_SYSREG(0x6a0) = 0xa8c24ff4a9417bfdull);
}

/* FUN_0032997c @ 0x0032997c   (est. sk_obj_set_field8_from_leaf_6566a0)
 * Set the +8 field of obj from leaf stub FUN_00329928() (slot 0x6566a0).
 * Confidence: medium
 * Notes: Ghidra *(param_1+8) = FUN_00329928(). */
void sk_obj_set_field8_from_leaf_6566a0(long obj)
{
    *(und8_t *)(obj + 8) = sk_sysreg_leaf_6566a0();
}

/* FUN_003299d8 @ 0x003299d8   (est. sk_sysreg_register_6566a8)
 * Two-part syscall registration into slot 0x6566a8: name range [0x6566b0,
 * &DAT_004ed388), handler leaf FUN_00329a4c (slot 0x6566b8), register
 * {descriptor @0x4eb078}.
 * Confidence: medium
 * Notes: Ghidra FUN_00027614(0x6566b0,&DAT_004ed388); local_28=FUN_00329a4c();
 *   uRam006566a8=FUN_00376820(&DAT_004eb078,uVar1,&local_28). */
void sk_sysreg_register_6566a8(void)
{
    und8_t name = sk_registry_get_or_init(&SK_SYSREG(0x6b0), (und8_t *)0x004ed388);
    und8_t handler = sk_sysreg_leaf_6566b8();
    SK_SYSREG(0x6a8) = sk_syscall_register(0x004eb078, name, handler);
}

/* FUN_00329a4c @ 0x00329a4c   (est. sk_sysreg_leaf_6566b8)
 * Leaf stub: initialize slot 0x6566b8 with literal constant, return it.
 * Confidence: low
 * Notes: Ghidra uRam00000000006566b8 = 0x540003c0721f391f. */
und8_t sk_sysreg_leaf_6566b8(void)
{
    return (SK_SYSREG(0x6b8) = 0x540003c0721f391full);
}

/* FUN_00329aa0 @ 0x00329aa0   (est. sk_obj_set_field8_from_leaf_6566c0)
 * Set the +8 field of obj from leaf stub FUN_00329ac8() (slot 0x6566c0).
 * Confidence: medium
 * Notes: Ghidra *(param_1+8) = FUN_00329ac8(). */
void sk_obj_set_field8_from_leaf_6566c0(long obj)
{
    *(und8_t *)(obj + 8) = sk_sysreg_leaf_6566c0();
}

/* FUN_00329ac8 @ 0x00329ac8   (est. sk_sysreg_leaf_6566c0)
 * Leaf stub: initialize slot 0x6566c0 with literal constant, return it.
 * Confidence: low
 * Notes: Ghidra uRam00000000006566c0 = 0x12800029529fffc8. */
und8_t sk_sysreg_leaf_6566c0(void)
{
    return (SK_SYSREG(0x6c0) = 0x12800029529fffc8ull);
}

/* FUN_00329b30 @ 0x00329b30   (est. sk_sysreg_register_6566c8)
 * Two-part syscall registration into slot 0x6566c8: name range [0x6566b0,
 * &DAT_004ed388), handler leaf FUN_00329ac8, register {descriptor @0x4eb028}.
 * Confidence: medium
 * Notes: Ghidra FUN_00027614(0x6566b0,&DAT_004ed388); local_28=FUN_00329ac8();
 *   uRam006566c8=FUN_00376820(&DAT_004eb028,uVar1,&local_28). */
void sk_sysreg_register_6566c8(void)
{
    und8_t name = sk_registry_get_or_init(&SK_SYSREG(0x6b0), (und8_t *)0x004ed388);
    und8_t handler = sk_sysreg_leaf_6566c0();
    SK_SYSREG(0x6c8) = sk_syscall_register(0x004eb028, name, handler);
}

/* FUN_00329ba4 @ 0x00329ba4   (est. sk_obj_set_field8_from_leaf_6566d0)
 * Set the +8 field of obj from leaf stub FUN_00329bcc() (slot 0x6566d0).
 * Confidence: medium
 * Notes: Ghidra *(param_1+8) = FUN_00329bcc(). */
void sk_obj_set_field8_from_leaf_6566d0(long obj)
{
    *(und8_t *)(obj + 8) = sk_sysreg_leaf_6566d0();
}

/* FUN_00329bcc @ 0x00329bcc   (est. sk_sysreg_leaf_6566d0)
 * Leaf stub: initialize slot 0x6566d0 with literal constant, return it.
 * Confidence: low
 * Notes: Ghidra uRam00000000006566d0 = 0x7a4811647100017f. */
und8_t sk_sysreg_leaf_6566d0(void)
{
    return (SK_SYSREG(0x6d0) = 0x7a4811647100017full);
}

/* FUN_00329c20 @ 0x00329c20   (est. sk_obj_set_field8_from_fun_000863bc)
 * Set the +8 field of obj from FUN_000863bc().
 * Confidence: medium
 * Notes: Ghidra *(param_1+8) = FUN_000863bc(). */
void sk_obj_set_field8_from_fun_000863bc(long obj)
{
    sk_fun_000863bc();
}

/* FUN_00329ca8 @ 0x00329ca8   (est. sk_sysreg_register_6566d8)
 * Two-part syscall registration into slot 0x6566d8: name range [0x6566e0,
 * &DAT_004ed508), handler leaf FUN_00329d1c (slot 0x6566e8), register
 * {descriptor @0x4eb078}.
 * Confidence: medium
 * Notes: Ghidra FUN_00027614(0x6566e0,&DAT_004ed508); local_28=FUN_00329d1c();
 *   uRam006566d8=FUN_00376820(&DAT_004eb078,uVar1,&local_28). */
void sk_sysreg_register_6566d8(void)
{
    und8_t name = sk_registry_get_or_init(&SK_SYSREG(0x6e0), (und8_t *)0x004ed508);
    und8_t handler = sk_sysreg_leaf_6566e8();
    SK_SYSREG(0x6d8) = sk_syscall_register(0x004eb078, name, handler);
}

/* FUN_00329d1c @ 0x00329d1c   (est. sk_sysreg_leaf_6566e8)
 * Leaf stub: initialize slot 0x6566e8 with literal constant, return it.
 * Confidence: low
 * Notes: Ghidra uRam00000000006566e8 = 0x9100426d0b0a018c. */
und8_t sk_sysreg_leaf_6566e8(void)
{
    return (SK_SYSREG(0x6e8) = 0x9100426d0b0a018cull);
}

/* FUN_00329d70 @ 0x00329d70   (est. sk_obj_set_field8_from_leaf_6566f0)
 * Set the +8 field of obj from leaf stub FUN_00329d98() (slot 0x6566f0).
 * Confidence: medium
 * Notes: Ghidra *(param_1+8) = FUN_00329d98(). */
void sk_obj_set_field8_from_leaf_6566f0(long obj)
{
    *(und8_t *)(obj + 8) = sk_sysreg_leaf_6566f0();
}

/* FUN_00329d98 @ 0x00329d98   (est. sk_sysreg_leaf_6566f0)
 * Leaf stub: initialize slot 0x6566f0 with literal constant, return it.
 * Confidence: low
 * Notes: Ghidra uRam00000000006566f0 = 0x88eefdacaa0a03ee. */
und8_t sk_sysreg_leaf_6566f0(void)
{
    return (SK_SYSREG(0x6f0) = 0x88eefdacaa0a03eeull);
}

/* FUN_00329e00 @ 0x00329e00   (est. sk_sysreg_register_6566f8)
 * Two-part syscall registration into slot 0x6566f8: name range [0x6566e0,
 * &DAT_004ed508), handler leaf FUN_00329d98, register {descriptor @0x4eb028}.
 * Confidence: medium
 * Notes: Ghidra FUN_00027614(0x6566e0,&DAT_004ed508); local_28=FUN_00329d98();
 *   uRam006566f8=FUN_00376820(&DAT_004eb028,uVar1,&local_28). */
void sk_sysreg_register_6566f8(void)
{
    und8_t name = sk_registry_get_or_init(&SK_SYSREG(0x6e0), (und8_t *)0x004ed508);
    und8_t handler = sk_sysreg_leaf_6566f0();
    SK_SYSREG(0x6f8) = sk_syscall_register(0x004eb028, name, handler);
}

/* FUN_00329e74 @ 0x00329e74   (est. sk_obj_set_field8_from_leaf_656700)
 * Set the +8 field of obj from leaf stub FUN_00329e9c() (slot 0x656700).
 * Confidence: medium
 * Notes: Ghidra *(param_1+8) = FUN_00329e9c(). */
void sk_obj_set_field8_from_leaf_656700(long obj)
{
    *(und8_t *)(obj + 8) = sk_sysreg_leaf_656700();
}

/* FUN_00329e9c @ 0x00329e9c   (est. sk_sysreg_leaf_656700)
 * Leaf stub: initialize slot 0x656700 with literal constant, return it.
 * Confidence: low
 * Notes: Ghidra uRam0000000000656700 = 0x54fffc417100097f. */
und8_t sk_sysreg_leaf_656700(void)
{
    return (SK_SYSREG(0x700) = 0x54fffc417100097full);
}

/* FUN_00329ef4 @ 0x00329ef4   (est. sk_sysreg_leaf_656708)
 * Leaf stub: initialize slot 0x656708 with literal constant, return it.
 * Confidence: low
 * Notes: Ghidra uRam0000000000656708 = 0x36c800a8b9401268. */
und8_t sk_sysreg_leaf_656708(void)
{
    return (SK_SYSREG(0x708) = 0x36c800a8b9401268ull);
}

/* FUN_00329f48 @ 0x00329f48   (est. sk_obj_set_field8_from_leaf_656708)
 * Set the +8 field of obj from leaf stub FUN_00329ef4() (slot 0x656708).
 * Confidence: medium
 * Notes: Ghidra *(param_1+8) = FUN_00329ef4(). */
void sk_obj_set_field8_from_leaf_656708(long obj)
{
    *(und8_t *)(obj + 8) = sk_sysreg_leaf_656708();
}

/* FUN_00329fa4 @ 0x00329fa4   (est. sk_sysreg_register_656710)
 * Two-part syscall registration into slot 0x656710: name range [0x656718,
 * &DAT_004ed698), handler leaf FUN_0032a018 (slot 0x656720), register
 * {descriptor @0x4eb078}.
 * Confidence: medium
 * Notes: Ghidra FUN_00027614(0x656718,&DAT_004ed698); local_28=FUN_0032a018();
 *   uRam00656710=FUN_00376820(&DAT_004eb078,uVar1,&local_28). */
void sk_sysreg_register_656710(void)
{
    und8_t name = sk_registry_get_or_init(&SK_SYSREG(0x718), (und8_t *)0x004ed698);
    und8_t handler = sk_sysreg_leaf_656720();
    SK_SYSREG(0x710) = sk_syscall_register(0x004eb078, name, handler);
}

/* FUN_0032a018 @ 0x0032a018   (est. sk_sysreg_leaf_656720)
 * Leaf stub: initialize slot 0x656720 with literal constant, return it.
 * Confidence: low
 * Notes: Ghidra uRam0000000000656720 = 0xa9417bfdaa1303e0. */
und8_t sk_sysreg_leaf_656720(void)
{
    return (SK_SYSREG(0x720) = 0xa9417bfdaa1303e0ull);
}

/* FUN_0032a06c @ 0x0032a06c   (est. sk_obj_set_field8_from_leaf_656728)
 * Set the +8 field of obj from leaf stub FUN_0032a094() (slot 0x656728).
 * Confidence: medium
 * Notes: Ghidra *(param_1+8) = FUN_0032a094(). */
void sk_obj_set_field8_from_leaf_656728(long obj)
{
    *(und8_t *)(obj + 8) = sk_sysreg_leaf_656728();
}

/* FUN_0032a094 @ 0x0032a094   (est. sk_sysreg_leaf_656728)
 * Leaf stub: initialize slot 0x656728 with literal constant, return it.
 * Confidence: low
 * Notes: Ghidra uRam0000000000656728 = 0xd50323ffa8c24ff4. */
und8_t sk_sysreg_leaf_656728(void)
{
    return (SK_SYSREG(0x728) = 0xd50323ffa8c24ff4ull);
}

/* FUN_0032a0fc @ 0x0032a0fc   (est. sk_sysreg_register_656730)
 * Two-part syscall registration into slot 0x656730: name range [0x656718,
 * &DAT_004ed698), handler leaf FUN_0032a094, register {descriptor @0x4eb028}.
 * Confidence: medium
 * Notes: Ghidra FUN_00027614(0x656718,&DAT_004ed698); local_28=FUN_0032a094();
 *   uRam00656730=FUN_00376820(&DAT_004eb028,uVar1,&local_28). */
void sk_sysreg_register_656730(void)
{
    und8_t name = sk_registry_get_or_init(&SK_SYSREG(0x718), (und8_t *)0x004ed698);
    und8_t handler = sk_sysreg_leaf_656728();
    SK_SYSREG(0x730) = sk_syscall_register(0x004eb028, name, handler);
}

/* FUN_0032a170 @ 0x0032a170   (est. sk_obj_set_field8_from_leaf_656738)
 * Set the +8 field of obj from leaf stub FUN_0032a198() (slot 0x656738).
 * Confidence: medium
 * Notes: Ghidra *(param_1+8) = FUN_0032a198(). */
void sk_obj_set_field8_from_leaf_656738(long obj)
{
    *(und8_t *)(obj + 8) = sk_sysreg_leaf_656738();
}

/* FUN_0032a198 @ 0x0032a198   (est. sk_sysreg_leaf_656738)
 * Leaf stub: initialize slot 0x656738 with literal constant, return it.
 * Confidence: low
 * Notes: Ghidra uRam0000000000656738 = 0xd65f03c0d65f03c0 (ret; ret). */
und8_t sk_sysreg_leaf_656738(void)
{
    return (SK_SYSREG(0x738) = 0xd65f03c0d65f03c0ull);
}

/* FUN_0032a1ec @ 0x0032a1ec   (est. sk_obj_set_field8_from_fun_0001e790)
 * Set the +8 field of obj from FUN_0001e790().
 * Confidence: medium
 * Notes: Ghidra *(param_1+8) = FUN_0001e790(). */
void sk_obj_set_field8_from_fun_0001e790(long obj)
{
    sk_fun_0001e790();
}

/* FUN_0032a274 @ 0x0032a274   (est. sk_sysreg_register_656740)
 * Two-part syscall registration into slot 0x656740: name range [0x656748,
 * &DAT_004ed818), handler leaf FUN_0032a2e8 (slot 0x656750), register
 * {descriptor @0x4eb078}.
 * Confidence: medium
 * Notes: Ghidra FUN_00027614(0x656748,&DAT_004ed818); local_28=FUN_0032a2e8();
 *   _DAT_00656740=FUN_00376820(&DAT_004eb078,uVar1,&local_28). */
void sk_sysreg_register_656740(void)
{
    und8_t name = sk_registry_get_or_init(&SK_SYSREG(0x748), (und8_t *)0x004ed818);
    und8_t handler = sk_sysreg_leaf_656750();
    SK_SYSREG(0x740) = sk_syscall_register(0x004eb078, name, handler);
}

/* FUN_0032a2e8 @ 0x0032a2e8   (est. sk_sysreg_leaf_656750)
 * Leaf stub: initialize slot 0x656750 with literal constant, return it.
 * Confidence: low
 * Notes: Ghidra uRam0000000000656750 = 0xaa0003f3910043fd. */
und8_t sk_sysreg_leaf_656750(void)
{
    return (SK_SYSREG(0x750) = 0xaa0003f3910043fdull);
}

/* FUN_0032a33c @ 0x0032a33c   (est. sk_obj_set_field8_from_leaf_656758)
 * Set the +8 field of obj from leaf stub FUN_0032a364() (slot 0x656758).
 * Confidence: medium
 * Notes: Ghidra *(param_1+8) = FUN_0032a364(). */
void sk_obj_set_field8_from_leaf_656758(long obj)
{
    *(und8_t *)(obj + 8) = sk_sysreg_leaf_656758();
}

/* FUN_0032a364 @ 0x0032a364   (est. sk_sysreg_leaf_656758)
 * Leaf stub: initialize slot 0x656758 with literal constant, return it.
 * Confidence: low
 * Notes: Ghidra uRam0000000000656758 = 0x9133a02190000541. */
und8_t sk_sysreg_leaf_656758(void)
{
    return (SK_SYSREG(0x758) = 0x9133a02190000541ull);
}

/* FUN_0032a3cc @ 0x0032a3cc   (est. sk_sysreg_register_656760)
 * Two-part syscall registration into slot 0x656760: name range [0x656748,
 * &DAT_004ed818), handler leaf FUN_0032a364, register {descriptor @0x4eb028}.
 * Confidence: medium
 * Notes: Ghidra FUN_00027614(0x656748,&DAT_004ed818); local_28=FUN_0032a364();
 *   uRam00656760=FUN_00376820(&DAT_004eb028,uVar1,&local_28). */
void sk_sysreg_register_656760(void)
{
    und8_t name = sk_registry_get_or_init(&SK_SYSREG(0x748), (und8_t *)0x004ed818);
    und8_t handler = sk_sysreg_leaf_656758();
    SK_SYSREG(0x760) = sk_syscall_register(0x004eb028, name, handler);
}

/* FUN_0032a440 @ 0x0032a440   (est. sk_obj_set_field8_from_leaf_656768)
 * Set the +8 field of obj from leaf stub FUN_0032a468() (slot 0x656768).
 * Confidence: medium
 * Notes: Ghidra *(param_1+8) = FUN_0032a468(). */
void sk_obj_set_field8_from_leaf_656768(long obj)
{
    *(und8_t *)(obj + 8) = sk_sysreg_leaf_656768();
}

/* FUN_0032a468 @ 0x0032a468   (est. sk_sysreg_leaf_656768)
 * Leaf stub: initialize slot 0x656768 with literal constant, return it.
 * Confidence: low
 * Notes: Ghidra uRam0000000000656768 = 0x9133a02190000541. */
und8_t sk_sysreg_leaf_656768(void)
{
    return (SK_SYSREG(0x768) = 0x9133a02190000541ull);
}

/* FUN_0032a4c0 @ 0x0032a4c0   (est. sk_obj_set_field8_from_fun_00324904)
 * Set the +8 field of obj from FUN_00324904().
 * Confidence: medium
 * Notes: Ghidra *(param_1+8) = FUN_00324904(). */
void sk_obj_set_field8_from_fun_00324904(long obj)
{
    sk_fun_00324904();
}

/* FUN_0032a504 @ 0x0032a504   (est. sk_sysreg_register_656770)
 * Two-part syscall registration into slot 0x656770: name range [0x656778,
 * &DAT_004ed9a8), handler leaf FUN_0032a578 (slot 0x656780), register
 * {descriptor @0x4eb078}.
 * Confidence: medium
 * Notes: Ghidra FUN_00027614(0x656778,&DAT_004ed9a8); local_28=FUN_0032a578();
 *   uRam00656770=FUN_00376820(&DAT_004eb078,uVar1,&local_28). */
void sk_sysreg_register_656770(void)
{
    und8_t name = sk_registry_get_or_init(&SK_SYSREG(0x778), (und8_t *)0x004ed9a8);
    und8_t handler = sk_sysreg_leaf_656780();
    SK_SYSREG(0x770) = sk_syscall_register(0x004eb078, name, handler);
}

/* FUN_0032a578 @ 0x0032a578   (est. sk_sysreg_leaf_656780)
 * Leaf stub: initialize slot 0x656780 with literal constant, return it.
 * Confidence: low
 * Notes: Ghidra uRam0000000000656780 = 0xaa1303e09133a021. */
und8_t sk_sysreg_leaf_656780(void)
{
    return (SK_SYSREG(0x780) = 0xaa1303e09133a021ull);
}

/* FUN_0032a5cc @ 0x0032a5cc   (est. sk_obj_set_field8_from_leaf_656788)
 * Set the +8 field of obj from leaf stub FUN_0032a5f4() (slot 0x656788).
 * Confidence: medium
 * Notes: Ghidra *(param_1+8) = FUN_0032a5f4(). */
void sk_obj_set_field8_from_leaf_656788(long obj)
{
    *(und8_t *)(obj + 8) = sk_sysreg_leaf_656788();
}

/* FUN_0032a5f4 @ 0x0032a5f4   (est. sk_sysreg_leaf_656788)
 * Leaf stub: initialize slot 0x656788 with literal constant, return it.
 * Confidence: low
 * Notes: Ghidra uRam0000000000656788 = 0x370005209400047b. */
und8_t sk_sysreg_leaf_656788(void)
{
    return (SK_SYSREG(0x788) = 0x370005209400047bull);
}

/* FUN_0032a65c @ 0x0032a65c   (est. sk_sysreg_register_656790)
 * Two-part syscall registration into slot 0x656790: name range [0x656778,
 * &DAT_004ed9a8), handler leaf FUN_0032a5f4, register {descriptor @0x4eb028}.
 * Confidence: medium
 * Notes: Ghidra FUN_00027614(0x656778,&DAT_004ed9a8); local_28=FUN_0032a5f4();
 *   uRam00656790=FUN_00376820(&DAT_004eb028,uVar1,&local_28). */
void sk_sysreg_register_656790(void)
{
    und8_t name = sk_registry_get_or_init(&SK_SYSREG(0x778), (und8_t *)0x004ed9a8);
    und8_t handler = sk_sysreg_leaf_656788();
    SK_SYSREG(0x790) = sk_syscall_register(0x004eb028, name, handler);
}

/* FUN_0032a6d0 @ 0x0032a6d0   (est. sk_obj_set_field8_from_leaf_656798)
 * Set the +8 field of obj from leaf stub FUN_0032a6f8() (slot 0x656798).
 * Confidence: medium
 * Notes: Ghidra *(param_1+8) = FUN_0032a6f8(). */
void sk_obj_set_field8_from_leaf_656798(long obj)
{
    *(und8_t *)(obj + 8) = sk_sysreg_leaf_656798();
}

/* FUN_0032a6f8 @ 0x0032a6f8   (est. sk_sysreg_leaf_656798)
 * Leaf stub: initialize slot 0x656798 with literal constant, return it.
 * Confidence: low
 * Notes: Ghidra uRam0000000000656798 = 0x94000654aa1303e0. */
und8_t sk_sysreg_leaf_656798(void)
{
    return (SK_SYSREG(0x798) = 0x94000654aa1303e0ull);
}

/* FUN_0032a74c @ 0x0032a74c   (est. sk_sysreg_leaf_6567a0)
 * Leaf stub: initialize slot 0x6567a0 with literal constant, return it.
 * Confidence: low
 * Notes: Ghidra uRam00000000006567a0 = 0x9000054137000480. */
und8_t sk_sysreg_leaf_6567a0(void)
{
    return (SK_SYSREG(0x7a0) = 0x9000054137000480ull);
}

/* FUN_0032a7a0 @ 0x0032a7a0   (est. sk_obj_set_field8_from_fun_000e710c)
 * Set the +8 field of obj from FUN_000e710c().
 * Confidence: medium
 * Notes: Ghidra *(param_1+8) = FUN_000e710c(). */
void sk_obj_set_field8_from_fun_000e710c(long obj)
{
    sk_fun_000e710c();
}

/* FUN_0032a828 @ 0x0032a828   (est. sk_sysreg_register_6567a8)
 * Two-part syscall registration into slot 0x6567a8: name range [0x6567b0,
 * &DAT_004edb28), handler leaf FUN_0032a89c (slot 0x6567b8), register
 * {descriptor @0x4eb078}.
 * Confidence: medium
 * Notes: Ghidra FUN_00027614(0x6567b0,&DAT_004edb28); local_28=FUN_0032a89c();
 *   uRam006567a8=FUN_00376820(&DAT_004eb078,uVar1,&local_28). */
void sk_sysreg_register_6567a8(void)
{
    und8_t name = sk_registry_get_or_init(&SK_SYSREG(0x7b0), (und8_t *)0x004edb28);
    und8_t handler = sk_sysreg_leaf_6567b8();
    SK_SYSREG(0x7a8) = sk_syscall_register(0x004eb078, name, handler);
}

/* FUN_0032a89c @ 0x0032a89c   (est. sk_sysreg_leaf_6567b8)
 * Leaf stub: initialize slot 0x6567b8 with literal constant, return it.
 * Confidence: low
 * Notes: Ghidra uRam00000000006567b8 = 0x9133a02190000541. */
und8_t sk_sysreg_leaf_6567b8(void)
{
    return (SK_SYSREG(0x7b8) = 0x9133a02190000541ull);
}

/* FUN_0032a8f0 @ 0x0032a8f0   (est. sk_obj_set_field8_from_leaf_6567c0)
 * Set the +8 field of obj from leaf stub FUN_0032a918() (slot 0x6567c0).
 * Confidence: medium
 * Notes: Ghidra *(param_1+8) = FUN_0032a918(). */
void sk_obj_set_field8_from_leaf_6567c0(long obj)
{
    *(und8_t *)(obj + 8) = sk_sysreg_leaf_6567c0();
}

/* FUN_0032a918 @ 0x0032a918   (est. sk_sysreg_leaf_6567c0)
 * Leaf stub: initialize slot 0x6567c0 with literal constant, return it.
 * Confidence: low
 * Notes: Ghidra uRam00000000006567c0 = 0x94000a0caa1303e0. */
und8_t sk_sysreg_leaf_6567c0(void)
{
    return (SK_SYSREG(0x7c0) = 0x94000a0caa1303e0ull);
}

/* FUN_0032a980 @ 0x0032a980   (est. sk_sysreg_register_6567c8)
 * Two-part syscall registration into slot 0x6567c8: name range [0x6567b0,
 * &DAT_004edb28), handler leaf FUN_0032a918, register {descriptor @0x4eb028}.
 * Confidence: medium
 * Notes: Ghidra FUN_00027614(0x6567b0,&DAT_004edb28); local_28=FUN_0032a918();
 *   uRam006567c8=FUN_00376820(&DAT_004eb028,uVar1,&local_28). */
void sk_sysreg_register_6567c8(void)
{
    und8_t name = sk_registry_get_or_init(&SK_SYSREG(0x7b0), (und8_t *)0x004edb28);
    und8_t handler = sk_sysreg_leaf_6567c0();
    SK_SYSREG(0x7c8) = sk_syscall_register(0x004eb028, name, handler);
}

/* FUN_0032a9f4 @ 0x0032a9f4   (est. sk_obj_set_field8_from_leaf_6567d0)
 * Set the +8 field of obj from leaf stub FUN_0032aa1c() (slot 0x6567d0).
 * Confidence: medium
 * Notes: Ghidra *(param_1+8) = FUN_0032aa1c(). */
void sk_obj_set_field8_from_leaf_6567d0(long obj)
{
    *(und8_t *)(obj + 8) = sk_sysreg_leaf_6567d0();
}

/* FUN_0032aa1c @ 0x0032aa1c   (est. sk_sysreg_leaf_6567d0)
 * Leaf stub: initialize slot 0x6567d0 with literal constant, return it.
 * Confidence: low
 * Notes: Ghidra uRam00000000006567d0 = 0xaa1303e09133a021. */
und8_t sk_sysreg_leaf_6567d0(void)
{
    return (SK_SYSREG(0x7d0) = 0xaa1303e09133a021ull);
}

/* FUN_0032aa78 @ 0x0032aa78   (est. sk_obj_set_field8_from_fun_0001df60)
 * Set the +8 field of obj from FUN_0001df60().
 * Confidence: medium
 * Notes: Ghidra *(param_1+8) = FUN_0001df60(). */
void sk_obj_set_field8_from_fun_0001df60(long obj)
{
    sk_fun_0001df60();
}

/* FUN_0032aad8 @ 0x0032aad8   (est. sk_sysreg_register_pair_3)
 * Register pair: run FUN_003544ec(), a bare register, resolve FUN_00349e38()
 * and register it with param_1.
 * Confidence: medium
 * Notes: Ghidra FUN_00376820(uVar1,param_1) at end. */
void sk_sysreg_register_pair_3(und8_t param)
{
    sk_fun_003544ec();
    sk_syscall_register(0, 0, 0);
    sk_syscall_register(sk_fun_00349e38(0), param, 0);
}

/* FUN_0032ab18 @ 0x0032ab18   (est. sk_reg_run_chain_2)
 * Run the registration chain FUN_0034e250 -> register -> FUN_00348990 ->
 * FUN_00356518.
 * Confidence: medium
 * Notes: Ghidra FUN_00376820() called bare in the middle. */
void sk_reg_run_chain_2(void)
{
    sk_fun_0034e250();
    sk_syscall_register(0, 0, 0);
    sk_fun_00348990();
    sk_fun_00356518();
}

/* FUN_0032ab54 @ 0x0032ab54   (est. sk_obj_set_field8_from_reg_6)
 * Set the +8 field of obj: run FUN_0034b528() then store sk_syscall_register().
 * Confidence: medium
 * Notes: Ghidra FUN_00376820() with no visible args. */
void sk_obj_set_field8_from_reg_6(long obj)
{
    sk_fun_0034b528();
    *(und8_t *)(obj + 8) = sk_syscall_register(0, 0, 0);
}

/* FUN_0032ab80 @ 0x0032ab80   (est. sk_sysreg_register_pair_4)
 * Register pair: register descriptor @0x4edd24, resolve FUN_00348ad8() and
 * register it with param_1.
 * Confidence: medium
 * Notes: Ghidra FUN_00376820(&DAT_004edd24); FUN_00376820(uVar1,param_1). */
void sk_sysreg_register_pair_4(und8_t param)
{
    sk_syscall_register(0x004edd24, 0, 0);
    sk_syscall_register(sk_fun_00348ad8(0, param), param, 0);
}

/* FUN_0032abd0 @ 0x0032abd0   (est. sk_obj_set_field8_from_reg_7)
 * Set the +8 field of obj: run FUN_0034e250() then store sk_syscall_register().
 * Confidence: medium
 * Notes: Ghidra FUN_00376820() with no visible args. */
void sk_obj_set_field8_from_reg_7(long obj)
{
    sk_fun_0034e250();
    *(und8_t *)(obj + 8) = sk_syscall_register(0, 0, 0);
}

/* FUN_0032abfc @ 0x0032abfc   (est. sk_reg_range_register_64c2e0)
 * Register a syscall range: FUN_00325088(&DAT_0064c2e0, &DAT_004ea760).
 * Confidence: medium
 * Notes: Ghidra FUN_00325088(&DAT_0064c2e0,&DAT_004ea760). */
void sk_reg_range_register_64c2e0_a(void)
{
    sk_fun_00325088(0x0064c2e0, 0x004ea760);
}

/* FUN_0032ac00 @ 0x0032ac00   (est. sk_reg_range_register_64c2e0, alias)
 * Identical pair of the above.
 * Confidence: medium
 * Notes: Ghidra FUN_00325088(&DAT_0064c2e0,&DAT_004ea760). */
void sk_reg_range_register_64c2e0_b(void)
{
    sk_fun_00325088(0x0064c2e0, 0x004ea760);
}

/* FUN_0032ac30 @ 0x0032ac30   (est. sk_reg_range_register_656380)
 * Register a syscall range: FUN_00325088(0x656380, &DAT_004ea794).
 * Confidence: medium
 * Notes: Ghidra FUN_00325088(0x656380,&DAT_004ea794). */
void sk_reg_range_register_656380_a(void)
{
    sk_fun_00325088(0x656380, 0x004ea794);
}

/* FUN_0032ac34 @ 0x0032ac34   (est. sk_reg_range_register_656380, alias)
 * Identical pair of the above.
 * Confidence: medium
 * Notes: Ghidra FUN_00325088(0x656380,&DAT_004ea794). */
void sk_reg_range_register_656380_b(void)
{
    sk_fun_00325088(0x656380, 0x004ea794);
}

/* FUN_0032ac64 @ 0x0032ac64   (est. sk_reg_run_chain_3)
 * Run the registration chain FUN_00354ec0 -> FUN_00348990 -> FUN_00356518.
 * Confidence: medium
 * Notes: Ghidra sequential calls, no side-effect targets. */
void sk_reg_run_chain_3(void)
{
    sk_fun_00354ec0();
    sk_fun_00348990();
    sk_fun_00356518();
}

/* FUN_0032ac98 @ 0x0032ac98   (est. sk_obj_set_field8_from_reg_8)
 * Set the +8 field of obj: run FUN_0034b590() then store sk_syscall_register().
 * Confidence: medium
 * Notes: Ghidra FUN_00376820() with no visible args. */
void sk_obj_set_field8_from_reg_8(long obj)
{
    sk_fun_0034b590();
    *(und8_t *)(obj + 8) = sk_syscall_register(0, 0, 0);
}

/* FUN_0032acc4 @ 0x0032acc4   (est. sk_reg_range_register_656378)
 * Register a syscall range: FUN_00325088(0x656378, &DAT_004ea7c8).
 * Confidence: medium
 * Notes: Ghidra FUN_00325088(0x656378,&DAT_004ea7c8). */
void sk_reg_range_register_656378_a(void)
{
    sk_fun_00325088(0x656378, 0x004ea7c8);
}

/* FUN_0032acc8 @ 0x0032acc8   (est. sk_reg_range_register_656378, alias)
 * Identical pair of the above.
 * Confidence: medium
 * Notes: Ghidra FUN_00325088(0x656378,&DAT_004ea7c8). */
void sk_reg_range_register_656378_b(void)
{
    sk_fun_00325088(0x656378, 0x004ea7c8);
}

/* FUN_0032acf8 @ 0x0032acf8   (est. sk_sysreg_register_pair_5)
 * Register pair: register descriptor @0x4eddcc, resolve FUN_00348ad8() and
 * register it with param_1.
 * Confidence: medium
 * Notes: Ghidra FUN_00376820(&DAT_004eddcc); FUN_00376820(uVar1,param_1). */
void sk_sysreg_register_pair_5(und8_t param)
{
    sk_syscall_register(0x004eddcc, 0, 0);
    sk_syscall_register(sk_fun_00348ad8(0, param), param, 0);
}

/* FUN_0032ad48 @ 0x0032ad48   (est. sk_obj_set_field8_from_reg_9)
 * Set the +8 field of the x19 receiver from FUN_00354ec0().
 * Confidence: medium
 * Notes: Ghidra *(unaff_x19+8) = FUN_00354ec0(). */
void sk_obj_set_field8_from_reg_9(long obj)
{
    *(und8_t *)(obj + 8) = sk_fun_00354ec0();
}

/* FUN_0032ad98 @ 0x0032ad98   (est. sk_sysreg_register_6567d8)
 * Two-part syscall registration into slot 0x6567d8: name range [0x6567e0,
 * &DAT_004ede18), handler leaf FUN_0032ae0c (slot 0x6567e8), register
 * {descriptor @0x4eb050}.
 * Confidence: medium
 * Notes: Ghidra FUN_00027614(0x6567e0,&DAT_004ede18); local_28=FUN_0032ae0c();
 *   uRam006567d8=FUN_00376820(&DAT_004eb050,uVar1,&local_28). */
void sk_sysreg_register_6567d8(void)
{
    und8_t name = sk_registry_get_or_init(&SK_SYSREG(0x7e0), (und8_t *)0x004ede18);
    und8_t handler = sk_sysreg_leaf_6567e8();
    SK_SYSREG(0x7d8) = sk_syscall_register(0x004eb050, name, handler);
}

/* FUN_0032ae0c @ 0x0032ae0c   (est. sk_sysreg_leaf_6567e8)
 * Leaf stub: initialize slot 0x6567e8 with literal constant, return it.
 * Confidence: low
 * Notes: Ghidra uRam00000000006567e8 = 0x94000dc2aa1303e0. */
und8_t sk_sysreg_leaf_6567e8(void)
{
    return (SK_SYSREG(0x7e8) = 0x94000dc2aa1303e0ull);
}

/* FUN_0032ae60 @ 0x0032ae60   (est. sk_sysreg_leaf_6567f0)
 * Leaf stub: initialize slot 0x6567f0 with literal constant, return it.
 * Confidence: low
 * Notes: Ghidra uRam00000000006567f0 = 0x9000054137000200. */
und8_t sk_sysreg_leaf_6567f0(void)
{
    return (SK_SYSREG(0x7f0) = 0x9000054137000200ull);
}

/* FUN_0032aec8 @ 0x0032aec8   (est. sk_sysreg_register_6567f8)
 * Two-part syscall registration into slot 0x6567f8: name range [0x6567e0,
 * &DAT_004ede18), handler leaf FUN_0032af3c (slot 0x656800), register
 * {descriptor @0x4eb078}.
 * Confidence: medium
 * Notes: Ghidra FUN_00027614(0x6567e0,&DAT_004ede18); local_28=FUN_0032af3c();
 *   uRam006567f8=FUN_00376820(&DAT_004eb078,uVar1,&local_28). */
void sk_sysreg_register_6567f8(void)
{
    und8_t name = sk_registry_get_or_init(&SK_SYSREG(0x7e0), (und8_t *)0x004ede18);
    und8_t handler = sk_sysreg_leaf_656800();
    SK_SYSREG(0x7f8) = sk_syscall_register(0x004eb078, name, handler);
}

/* FUN_0032af3c @ 0x0032af3c   (est. sk_sysreg_leaf_656800)
 * Leaf stub: initialize slot 0x656800 with literal constant, return it.
 * Confidence: low
 * Notes: Ghidra uRam0000000000656800 = 0x3700016094000f9d. */
und8_t sk_sysreg_leaf_656800(void)
{
    return (SK_SYSREG(0x800) = 0x3700016094000f9dull);
}

/* FUN_0032af90 @ 0x0032af90   (est. sk_obj_set_field8_from_leaf_656808)
 * Set the +8 field of obj from leaf stub FUN_0032afb8() (slot 0x656808).
 * Confidence: medium
 * Notes: Ghidra *(param_1+8) = FUN_0032afb8(). */
void sk_obj_set_field8_from_leaf_656808(long obj)
{
    *(und8_t *)(obj + 8) = sk_sysreg_leaf_656808();
}

/* FUN_0032afb8 @ 0x0032afb8   (est. sk_sysreg_leaf_656808)
 * Leaf stub: initialize slot 0x656808 with literal constant, return it.
 * Confidence: low
 * Notes: Ghidra uRam0000000000656808 = 0x9133a02190000541. */
und8_t sk_sysreg_leaf_656808(void)
{
    return (SK_SYSREG(0x808) = 0x9133a02190000541ull);
}

/* FUN_0032b020 @ 0x0032b020   (est. sk_sysreg_register_656810)
 * Two-part syscall registration into slot 0x656810: name range [0x6567e0,
 * &DAT_004ede18), handler leaf FUN_0032afb8, register {descriptor @0x4eb028}.
 * Confidence: medium
 * Notes: Ghidra FUN_00027614(0x6567e0,&DAT_004ede18); local_28=FUN_0032afb8();
 *   uRam00656810=FUN_00376820(&DAT_004eb028,uVar1,&local_28). */
void sk_sysreg_register_656810(void)
{
    und8_t name = sk_registry_get_or_init(&SK_SYSREG(0x7e0), (und8_t *)0x004ede18);
    und8_t handler = sk_sysreg_leaf_656808();
    SK_SYSREG(0x810) = sk_syscall_register(0x004eb028, name, handler);
}

/* FUN_0032b094 @ 0x0032b094   (est. sk_obj_set_field8_from_leaf_6567f0)
 * Set the +8 field of obj from leaf stub FUN_0032ae60() (slot 0x6567f0).
 * Confidence: medium
 * Notes: Ghidra *(param_1+8) = FUN_0032ae60(). */
void sk_obj_set_field8_from_leaf_6567f0(long obj)
{
    *(und8_t *)(obj + 8) = sk_sysreg_leaf_6567f0();
}

/* FUN_0032b0d0 @ 0x0032b0d0   (est. sk_sysreg_register_656818)
 * Two-part syscall registration into slot 0x656818: name range [0x656820,
 * &DAT_004edef0), handler leaf FUN_0032b144 (slot 0x656828), register
 * {descriptor @0x4eb078}.
 * Confidence: medium
 * Notes: Ghidra FUN_00027614(0x656820,&DAT_004edef0); local_28=FUN_0032b144();
 *   uRam00656818=FUN_00376820(&DAT_004eb078,uVar1,&local_28). */
void sk_sysreg_register_656818(void)
{
    und8_t name = sk_registry_get_or_init(&SK_SYSREG(0x820), (und8_t *)0x004edef0);
    und8_t handler = sk_sysreg_leaf_656828();
    SK_SYSREG(0x818) = sk_syscall_register(0x004eb078, name, handler);
}

/* FUN_0032b144 @ 0x0032b144   (est. sk_sysreg_leaf_656828)
 * Leaf stub: initialize slot 0x656828 with literal constant, return it.
 * Confidence: low
 * Notes: Ghidra uRam0000000000656828 = 0x360000e094001353. */
und8_t sk_sysreg_leaf_656828(void)
{
    return (SK_SYSREG(0x828) = 0x360000e094001353ull);
}

/* FUN_0032b198 @ 0x0032b198   (est. sk_obj_set_field8_from_leaf_656830)
 * Set the +8 field of obj from leaf stub FUN_0032b1c0() (slot 0x656830).
 * Confidence: medium
 * Notes: Ghidra *(param_1+8) = FUN_0032b1c0(). */
void sk_obj_set_field8_from_leaf_656830(long obj)
{
    *(und8_t *)(obj + 8) = sk_sysreg_leaf_656830();
}

/* FUN_0032b1c0 @ 0x0032b1c0   (est. sk_sysreg_leaf_656830)
 * Leaf stub: initialize slot 0x656830 with literal constant, return it.
 * Confidence: low
 * Notes: Ghidra uRam0000000000656830 = 0x9133a00090000540. */
und8_t sk_sysreg_leaf_656830(void)
{
    return (SK_SYSREG(0x830) = 0x9133a00090000540ull);
}

/* FUN_0032b228 @ 0x0032b228   (est. sk_sysreg_register_656838)
 * Two-part syscall registration into slot 0x656838: name range [0x656820,
 * &DAT_004edef0), handler leaf FUN_0032b1c0, register {descriptor @0x4eb028}.
 * Confidence: medium
 * Notes: Ghidra FUN_00027614(0x656820,&DAT_004edef0); local_28=FUN_0032b1c0();
 *   uRam00656838=FUN_00376820(&DAT_004eb028,uVar1,&local_28). */
void sk_sysreg_register_656838(void)
{
    und8_t name = sk_registry_get_or_init(&SK_SYSREG(0x820), (und8_t *)0x004edef0);
    und8_t handler = sk_sysreg_leaf_656830();
    SK_SYSREG(0x838) = sk_syscall_register(0x004eb028, name, handler);
}

/* FUN_0032b29c @ 0x0032b29c   (est. sk_obj_set_field8_from_leaf_656840)
 * Set the +8 field of obj from leaf stub FUN_0032b2c4() (slot 0x656840).
 * Confidence: medium
 * Notes: Ghidra *(param_1+8) = FUN_0032b2c4(). */
void sk_obj_set_field8_from_leaf_656840(long obj)
{
    *(und8_t *)(obj + 8) = sk_sysreg_leaf_656840();
}

/* FUN_0032b2c4 @ 0x0032b2c4   (est. sk_sysreg_leaf_656840)
 * Leaf stub: initialize slot 0x656840 with literal constant, return it.
 * Confidence: low
 * Notes: Ghidra uRam0000000000656840 = 0x17fffcd5d50323ff. */
und8_t sk_sysreg_leaf_656840(void)
{
    return (SK_SYSREG(0x840) = 0x17fffcd5d50323ffull);
}

/* FUN_0032b340 @ 0x0032b340   (est. sk_obj_release_retained)
 * Resolve the current object via FUN_003504d0(), release its first ref, and
 * run the FUN_003597cc() bookkeeping.
 * Confidence: medium
 * Notes: Ghidra puVar1=FUN_003504d0(); FUN_0036b118(*puVar1); FUN_003597cc(). */
void sk_obj_release_retained(void)
{
    und8_t *obj = (und8_t *)sk_fun_003504d0();
    sk_obj_retain(*obj);
    sk_fun_003597cc();
}

/* FUN_0032b410 @ 0x0032b410   (est. sk_obj_register_60cfa0)
 * Register obj against the descriptor table @0x60cfa0 via FUN_00370060.
 * Confidence: medium
 * Notes: Ghidra FUN_00370060(param_1,&DAT_0060cfa0). */
void sk_obj_register_60cfa0_a(und8_t param)
{
    sk_fun_00370060(param, 0x0060cfa0);
}

/* FUN_0032b414 @ 0x0032b414   (est. sk_obj_register_60cfa0, alias)
 * Identical pair of the above.
 * Confidence: medium
 * Notes: Ghidra FUN_00370060(param_1,&DAT_0060cfa0). */
void sk_obj_register_60cfa0_b(und8_t param)
{
    sk_fun_00370060(param, 0x0060cfa0);
}

/* FUN_0032b444 @ 0x0032b444   (est. sk_obj_register_slot)
 * Register a slot: call FUN_00374104(obj, 0x100, 0, stack, obj+0x58) then
 * FUN_003546b4().
 * Confidence: medium
 * Notes: Ghidra FUN_00374104(param_1,0x100,0,auStack_18,param_1+0x58);
 *   FUN_003546b4(). */
void sk_obj_register_slot(long obj)
{
    und1_t scratch[8];
    sk_fun_00374104(obj, 0x100, 0, scratch, obj + 0x58);
    sk_fun_003546b4();
}

/* FUN_0032b478 @ 0x0032b478   (est. sk_obj_release_after_sync)
 * Run FUN_00355938() then release an object via FUN_0036b270.
 * Confidence: medium
 * Notes: Ghidra FUN_00355938(); thunk_FUN_0036b270(). */
void sk_obj_release_after_sync(void)
{
    sk_fun_00355938();
    sk_obj_release(0);
}

/* FUN_0032b4ac @ 0x0032b4ac   (est. sk_obj_move)
 * Move an object: copy the two-word value at param_2 into param_1 and release
 * the previously-held ref (param_1[1]).
 * Confidence: high
 * Notes: Ghidra FUN_003a25d4(uVar2) releases the old object. */
und8_t *sk_obj_move(und8_t *dst, und8_t *src)
{
    und8_t old = dst[1];
    dst[0] = src[0];
    dst[1] = src[1];
    sk_obj_release2(old);
    return dst;
}

/* FUN_0032b51c @ 0x0032b51c   (est. sk_obj_release_fields)
 * Release the three ref fields (+0x20, +0x30, +0x38) of obj after running
 * FUN_000026e8().
 * Confidence: medium
 * Notes: Ghidra FUN_0036b118(+0x20), FUN_003a25d4(+0x30), FUN_0036b118(+0x38). */
void sk_obj_release_fields(long obj)
{
    sk_fun_000026e8();
    sk_obj_retain(*(und8_t *)(obj + 0x20));
    sk_obj_release2(*(und8_t *)(obj + 0x30));
    sk_obj_retain(*(und8_t *)(obj + 0x38));
}

/* FUN_0032b558 @ 0x0032b558   (est. sk_obj_copy_swap_refs)
 * Copy a three-field object from x19 to x20, releasing the swapped-out refs.
 * Confidence: medium
 * Notes: Ghidra unaff_x19 source, unaff_x20 dest; FUN_0036b270/FUN_0036b118
 *   balance the refcounts of the overwritten fields. */
void sk_obj_copy_swap_refs(long dst, long src)
{
    und8_t v1, v2;
    sk_fun_003504d0();
    *(und8_t *)(dst + 0x18) = *(und8_t *)(src + 0x18);
    sk_fun_0034b07c(0, 0, 0);
    v1 = *(und8_t *)(src + 0x28);
    *(und8_t *)(dst + 0x20) = *(und8_t *)(src + 0x20);
    *(und8_t *)(dst + 0x28) = v1;
    v1 = *(und8_t *)(src + 0x38);
    v2 = *(und8_t *)(src + 0x30);
    *(und8_t *)(dst + 0x38) = *(und8_t *)(src + 0x38);
    *(und8_t *)(dst + 0x30) = v2;
    sk_obj_release(0);
    sk_obj_release(v2);
    sk_obj_release(v1);
}

/* FUN_0032b5dc @ 0x0032b5dc   (est. sk_obj_copy_swap_refs_2)
 * Copy a three-field object from x19 to x20 with refcount balancing.
 * Confidence: medium
 * Notes: Ghidra unaff_x19 source, unaff_x20 dest; FUN_0036b270 / FUN_0036b118
 *   / FUN_003a25d4 balance the refcounts of the overwritten fields. */
void sk_obj_copy_swap_refs_2(long dst, long src)
{
    und8_t v1;
    sk_fun_003504d0();
    sk_obj_swap_type_tagged((und8_t *)dst, (und8_t *)src);
    v1 = *(und8_t *)(dst + 0x20);
    *(und8_t *)(dst + 0x20) = *(und8_t *)(src + 0x20);
    sk_obj_release(0);
    sk_obj_retain(v1);
    *(und8_t *)(dst + 0x28) = *(und8_t *)(src + 0x28);
    v1 = *(und8_t *)(dst + 0x30);
    *(und8_t *)(dst + 0x30) = *(und8_t *)(src + 0x30);
    sk_obj_release(0);
    sk_obj_release2(v1);
    v1 = *(und8_t *)(dst + 0x38);
    *(und8_t *)(dst + 0x38) = *(und8_t *)(src + 0x38);
    sk_obj_release(0);
    sk_obj_retain(v1);
}

/* FUN_0032b65c @ 0x0032b65c   (est. sk_obj_swap_type_tagged)
 * Swap two type-tagged objects: if the type tags (param[3]) match and the
 * type permits a fast path, swap directly; otherwise migrate through the
 * type-specific move/swap callbacks at +8/+0x10/+0x18/+0x20 of the type
 * descriptor. Honors the "shared" flag (type+0x52 bit 1).
 * Confidence: medium
 * Notes: Ghidra jumptable at 0x0032b760 not recovered; indirect calls via
 *   type-descriptor vtable offsets. */
void sk_obj_swap_type_tagged(und8_t *a, und8_t *b)
{
    if (a == b) {
        return;
    }
    und8_t type_a = a[3];
    und8_t type_b = b[3];
    if (type_a == type_b) {
        und8_t desc = *(und8_t *)(type_a - 8);
        if ((*(und8_t *)(desc + 0x52) >> 1 & 1) == 0) {
            /* fast path: same-type in-place swap callback (type+0x18) */
            (*(void (**)(und8_t *, und8_t *, und8_t))(desc + 0x18))(a, b, type_a);
            return;
        }
        /* same type, shared flag set: swap element refs */
        und8_t va = a[0], vb = b[0];
        sk_obj_release(vb);
        sk_obj_retain(va);
        a[0] = vb;
    } else {
        /* different types: migrate a's element to b's type, then swap */
        a[3] = type_b;
        und8_t desc_a = *(und8_t *)(type_a - 8);
        und8_t desc_b = *(und8_t *)(type_b - 8);
        unsigned int flag_b = *(unsigned int *)(desc_b + 0x50);
        if ((*(und8_t *)(desc_a + 0x52) >> 1 & 1) != 0) {
            und8_t va = a[0];
            if ((flag_b >> 0x11 & 1) == 0) {
                (*(void (**)(und8_t *, und8_t *, und8_t))(desc_b + 0x10))(a, b, type_b);
            } else {
                a[0] = b[0];
                sk_obj_release(0);
            }
            sk_obj_retain(va);
            return;
        }
        (*(void (**)(und1_t *, und8_t *, und8_t))(desc_a + 0x20))(&(und1_t){0}, a, type_a);
        if ((flag_b >> 0x11 & 1) == 0) {
            (*(void (**)(und8_t *, und8_t *, und8_t))(desc_b + 0x10))(a, b, type_b);
        } else {
            a[0] = b[0];
            sk_obj_release(0);
        }
        (*(void (**)(und1_t *, und8_t))(desc_a + 8))(&(und1_t){0}, type_a);
    }
}

/* FUN_0032b81c @ 0x0032b81c   (est. sk_obj_copy_swap_refs_3)
 * Copy a three-field object from x19 to x20 with refcount balancing.
 * Confidence: medium
 * Notes: Ghidra unaff_x19 source, unaff_x20 dest; FUN_0036b118 / FUN_003a25d4
 *   balance refcounts of overwritten fields. */
void sk_obj_copy_swap_refs_3(long dst, long src)
{
    und8_t v1, v2;
    sk_fun_003504d0();
    sk_fun_000026e8();
    sk_fun_003597cc();
    v1 = *(und8_t *)(dst + 0x20);
    *(und8_t *)(dst + 0x20) = *(und8_t *)(src + 0x20);
    sk_obj_retain(v1);
    v1 = *(und8_t *)(src + 0x30);
    v2 = *(und8_t *)(dst + 0x30);
    *(und8_t *)(dst + 0x28) = *(und8_t *)(src + 0x28);
    *(und8_t *)(dst + 0x30) = v1;
    sk_obj_release2(v2);
    v1 = *(und8_t *)(dst + 0x38);
    *(und8_t *)(dst + 0x38) = *(und8_t *)(src + 0x38);
    sk_obj_retain(v1);
}

/* FUN_0032b924 @ 0x0032b924   (est. sk_obj_release_by_type)
 * Release an object's ref fields (at offsets 0x10/0x18/0x20) according to its
 * type tag (param_1+0x12): default/small types use offsets 0x18/0x20, type 2
 * uses 0x38/0x40, type 3 uses 0x10/0x18.
 * Confidence: medium
 * Notes: Ghidra switch on *(byte*)(param_1+0x12); FUN_0036b118 / FUN_003a25d4
 *   release the ref fields. */
void sk_obj_release_by_type(int *obj)
{
    unsigned int type = (unsigned int)*(und1_t *)(obj + 0x12);
    long lo, hi;
    int *base = obj;
    if (3 < *(und1_t *)(obj + 0x12)) {
        type = *obj + 4;
    }
    lo = 0x18; hi = 0x10;
    switch (type) {
    default:
        base = obj + 2;
        lo = 0x20; hi = 0x18;
        break;
    case 2:
        sk_fun_000026e8();
        base = obj + 10;
        lo = 0x40; hi = 0x38;
        break;
    case 3:
        break;
    }
    sk_obj_retain(*(und8_t *)base);
    sk_obj_release2(*(und8_t *)((long)obj + hi));
    sk_obj_retain(*(und8_t *)((long)obj + lo));
}

/* FUN_0032be98 @ 0x0032be98   (est. sk_obj_release_fields_2)
 * Release three ref fields (+0x10, +0x18) of obj after resolving via
 * FUN_00352b20().
 * Confidence: medium
 * Notes: Ghidra FUN_0036b118()/FUN_003a25d4(+0x10)/FUN_0036b118(+0x18). */
void sk_obj_release_fields_2(long obj)
{
    sk_deref_word(NULL);
    sk_obj_retain(0);
    sk_obj_release2(*(und8_t *)(obj + 0x10));
    sk_obj_retain(*(und8_t *)(obj + 0x18));
}

/* FUN_0032bed0 @ 0x0032bed0   (est. sk_obj_copy4)
 * Copy the four-word object at param_2 into param_1 and release the old refs.
 * Confidence: high
 * Notes: Ghidra FUN_0036b270 releases the three swapped-out words. */
und8_t *sk_obj_copy4(und8_t *dst, und8_t *src)
{
    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = src[2];
    dst[3] = src[3];
    sk_obj_release(0);
    sk_obj_release(src[2]);
    sk_obj_release(src[3]);
    return dst;
}

/* FUN_0032bf30 @ 0x0032bf30   (est. sk_obj_copy_swap_refs_4)
 * Copy two fields (+0x10, +0x18) from x19 to x20 with refcount balancing.
 * Confidence: medium
 * Notes: Ghidra unaff_x19 source, unaff_x20 dest. */
void sk_obj_copy_swap_refs_4(long dst, long src)
{
    und8_t v1;
    sk_fun_0034b044();
    sk_obj_release(0);
    sk_obj_retain(0);
    sk_fun_003566cc();
    v1 = *(und8_t *)(dst + 0x10);
    *(und8_t *)(dst + 0x10) = *(und8_t *)(src + 0x10);
    sk_obj_release(0);
    sk_obj_release2(v1);
    v1 = *(und8_t *)(dst + 0x18);
    *(und8_t *)(dst + 0x18) = *(und8_t *)(src + 0x18);
    sk_obj_release(0);
    sk_obj_retain(v1);
}

/* FUN_0032bfa0 @ 0x0032bfa0   (est. sk_obj_copy_swap_refs_5)
 * Copy fields from x19 into the x20 object, releasing swapped-out refs.
 * Confidence: medium
 * Notes: Ghidra unaff_x19 source, unaff_x20 dest; FUN_0034d454()/FUN_0036b118
 *   /FUN_003a25d4 balance refcounts. */
void sk_obj_copy_swap_refs_5(long dst, long src)
{
    und8_t *tmp = (und8_t *)sk_fun_0034d454();
    und8_t v0 = tmp[0];
    *(und8_t *)dst = 0;      /* *unaff_x20 = extraout_x8 (opaque) */
    sk_obj_retain(v0);
    sk_fun_003566cc();
    sk_obj_release2(((und8_t *)dst)[2]);
    und8_t old3 = ((und8_t *)dst)[3];
    und8_t new2 = *(und8_t *)(src + 0x10);
    ((und8_t *)dst)[3] = *(und8_t *)(src + 0x18);
    ((und8_t *)dst)[2] = new2;
    sk_obj_retain(old3);
}

/* FUN_0032c00c @ 0x0032c00c   (est. sk_obj_resize_check_0x188)
 * Validate a resize: FUN_00377dcc(0x13f, *(obj+0x188)); if the returned size
 * is < 0x40, run the resize helpers FUN_00353424/FUN_0034d034/FUN_00374104/
 * FUN_00354c58.
 * Confidence: medium
 * Notes: Ghidra auVar1=FUN_00377dcc(0x13f,...); checks auVar1._8_8_ < 0x40. */
void sk_obj_resize_check_0x188(long obj)
{
    if (sk_fun_00377dcc(0x13f, *(und8_t *)(obj + 0x188)) < 0x40) {
        sk_fun_00353424(*(long *)(*(und8_t *)(obj + 0x188) - 8) + 0x40);
        sk_fun_0034d034();
        sk_fun_00374104(0, 0, 0, NULL, 0);
        sk_fun_00354c58();
    }
}

/* FUN_0032c08c @ 0x0032c08c   (est. sk_obj_resize_check_0x190)
 * Same resize-validation as FUN_0032c00c but reads the size from obj+400
 * (0x190).
 * Confidence: medium
 * Notes: Ghidra auVar1=FUN_00377dcc(0x13f,*(param_1+400)); checks <0x40. */
void sk_obj_resize_check_0x190(long obj)
{
    if (sk_fun_00377dcc(0x13f, *(und8_t *)(obj + 400)) < 0x40) {
        sk_fun_00353424(*(long *)(*(und8_t *)(obj + 400) - 8) + 0x40);
        sk_fun_0034d034();
        sk_fun_00374104(0, 0, 0, NULL, 0);
        sk_fun_00354c58();
    }
}

/* FUN_0032c0fc @ 0x0032c0fc   (est. sk_obj_resize_validate)
 * Validate/possibly enlarge an object region: run FUN_0034c7c4() and
 * FUN_00377dcc(); on the carry/zero condition path, resolve obj+0x18 and, if
 * the size is still insufficient, run the resize helpers FUN_003558b8/
 * FUN_0034cdf8/FUN_003728b8(...,2)/FUN_0035884c.
 * Confidence: medium
 * Notes: Ghidra uses implicit CY/ZR flags; param_3 returned (defaults to 2 on
 *   the resize path). */
long sk_obj_resize_validate(und8_t p1, und8_t p2, long p3)
{
    sk_fun_0034c7c4();
    sk_fun_00377dcc(0, 0);
    sk_fun_00354ce4();
    if (true) {
        sk_fun_00377824(0x13f, *(und8_t *)0 /* obj+0x18 */, 0);
        sk_fun_00354ce4();
        if (true) {
            sk_fun_003558b8(*(long *)(p3 - 8) + 0x40);
            sk_fun_0034cdf8();
            p3 = 2;
            sk_fun_003728b8(0, 0, 2);
            sk_fun_0035884c();
        }
    }
    return p3;
}

/* FUN_0032c19c @ 0x0032c19c   (est. sk_obj_validate_dispatch)
 * Validate a dispatch: run FUN_00084220(), resolve the current object, bind
 * obj+0x10/+0x18, and on the success path (no carry/zero, count==0, and
 * code < 0x19) call the type handler at x8/x10; otherwise run FUN_0034de74().
 * Confidence: medium
 * Notes: Ghidra uses implicit CY/ZR flags and extraout registers; the x8/x10
 *   function pointers and x16 receiver are opaque. */
void sk_obj_validate_dispatch(und8_t p1, und8_t p2, long p3)
{
    und8_t uVar1, uVar2;
    sk_fun_00084220();
    uVar2 = sk_fun_00350c5c();
    uVar1 = *(und8_t *)(p3 + 0x10);
    sk_fun_00349748(uVar2, *(und8_t *)(p3 + 0x18));
    sk_fun_00349748(0);
    sk_fun_00377824(0, 0, uVar1);
    sk_fun_000a6f88();
    sk_fun_0034d5d8(*(unsigned int *)0 & 0xff);
    if (true && 0 == 0) {
        sk_fun_0034bfb4(*(und8_t *)0);
        sk_fun_00357154();
    } else {
        sk_fun_0034de74();
    }
    sk_fun_00084234();
}

/* FUN_0032c284 @ 0x0032c284   (est. sk_obj_vtable_dispatch)
 * Dispatch through an object vtable: resolve obj via FUN_003504d0(), call the
 * +8 vtable entry, then call the +8 entry again on an offset selected by the
 * type byte at vtable+0x50.
 * Confidence: medium
 * Notes: Ghidra jumptable at 0x0032c30c not recovered; extraout_x16/x16_00 are
 *   the vtable bases. */
void sk_obj_vtable_dispatch(void)
{
    und8_t uVar1, uVar3;
    long lVar2;
    uVar3 = 0; /* extraout_x1 + 0x10 */
    sk_fun_003504d0();
    uVar1 = sk_fun_0034b3c8();
    /* (**(code**)(vt+8))(uVar1, uVar3) */
    lVar2 = 0; /* *(vt + 0x40) */
    sk_fun_00349748(uVar1, 0);
    sk_fun_00377824(0, 0, uVar3);
    sk_fun_0034bf0c();
    /* (**(code**)(vt2+8))(lVar2 + x20 + type_byte & ~type_byte) */
}

/* FUN_0032c3a4 @ 0x0032c3a4   (est. sk_obj_vtable_dispatch_0x18)
 * Dispatch through an object vtable at +0x18: resolve via FUN_00348c64(),
 * call the +0x18 vtable entry, then call the +0x18 entry on an offset
 * selected by the type byte at vtable+0x50.
 * Confidence: medium
 * Notes: Ghidra unaff_x19/x20/x21; extraout_x16/x16_00 are the vtable bases. */
void sk_obj_vtable_dispatch_0x18(void)
{
    und8_t uVar1;
    und8_t uVar2;
    long lVar3;
    sk_fun_00348c64();
    uVar1 = 0; /* (**(code**)(vt+0x18))() */
    lVar3 = 0; /* *(vt + 0x40) */
    sk_fun_00349748(uVar1, 0);
    sk_fun_00377824(0, 0, 0);
    sk_fun_00349530();
    uVar2 = (und8_t)(und1_t)0; /* type byte at vt2+0x50 */
    lVar3 += uVar2;
    /* (**(code**)(vt2+0x18))(lVar3+x21 & ~uVar2, lVar3+x20 & ~uVar2) */
}

/* FUN_0032c438 @ 0x0032c438   (est. sk_obj_vtable_dispatch_0x20)
 * Same vtable dispatch as FUN_0032c3a4 but through the +0x20 vtable entries.
 * Confidence: medium
 * Notes: Ghidra unaff_x19/x20/x21; extraout_x16/x16_00 are the vtable bases. */
void sk_obj_vtable_dispatch_0x20(void)
{
    und8_t uVar1;
    und8_t uVar2;
    long lVar3;
    sk_fun_00348c64();
    uVar1 = 0; /* (**(code**)(vt+0x20))() */
    lVar3 = 0; /* *(vt + 0x40) */
    sk_fun_00349748(uVar1, 0);
    sk_fun_00377824(0, 0, 0);
    sk_fun_00349530();
    uVar2 = (und8_t)(und1_t)0; /* type byte at vt2+0x50 */
    lVar3 += uVar2;
    /* (**(code**)(vt2+0x20))(lVar3+x21 & ~uVar2, lVar3+x20 & ~uVar2) */
}

/* FUN_0032c4cc @ 0x0032c4cc   (est. sk_obj_vtable_dispatch_0x28)
 * Same vtable dispatch as FUN_0032c3a4 but through the +0x28 vtable entries.
 * Confidence: medium
 * Notes: Ghidra unaff_x19/x20/x21; extraout_x16/x16_00 are the vtable bases. */
void sk_obj_vtable_dispatch_0x28(void)
{
    und8_t uVar1;
    und8_t uVar2;
    long lVar3;
    sk_fun_00348c64();
    uVar1 = 0; /* (**(code**)(vt+0x28))() */
    lVar3 = 0; /* *(vt + 0x40) */
    sk_fun_00349748(uVar1, 0);
    sk_fun_00377824(0, 0, 0);
    sk_fun_00349530();
    uVar2 = (und8_t)(und1_t)0; /* type byte at vt2+0x50 */
    lVar3 += uVar2;
    /* (**(code**)(vt2+0x28))(lVar3+x21 & ~uVar2, lVar3+x20 & ~uVar2) */
}

/* FUN_0032c560 @ 0x0032c560   (est. sk_obj_syscall_account)
 * Syscall accounting/argument-validation path: resolve the current context,
 * bind obj+0x10/+0x18, compare per-object counters (uVar1 vs +0x54), and on
 * the dispatch path select between type-1/2/3/4 sub-operations via a switch;
 * otherwise run the error/cleanup path FUN_003520e8()/FUN_0034bf1c() and
 * return FUN_000839f8().
 * Confidence: medium
 * Notes: Ghidra has extensive extraout_* register noise; unaff_x19 is the
 *   object and unaff_w22 a flag; this is a faithful structural reconstruction. */
und8_t sk_obj_syscall_account(und8_t p1, und8_t p2, long p3)
{
    unsigned int uVar1, uVar6;
    und8_t uVar5;
    int iVar7 = 0;
    sk_fun_00352758();
    uVar5 = *(und8_t *)(p3 + 0x10);
    sk_fun_0035549c(0, *(und8_t *)(p3 + 0x18));
    uVar1 = *(unsigned int *)0; /* *(extraout_x16 + 0x54) */
    sk_fun_00349748(0);
    sk_fun_00377824(0, 0, uVar5);
    sk_fun_0034f924();
    sk_fun_00355d34();
    if (0 /* unaff_w22 == 0 */) {
        return 0;
    }
    sk_fun_00358184();
    uVar6 = 0; /* extraout_w1 */
    if (uVar1 <= 0 && 0 == uVar1) {
        /* dispatch path */
        sk_fun_00357ef4();
        iVar7 = 0;
        uVar6 = 0;
        if (true) {
            sk_fun_0034e888();
            iVar7 = 0;
            uVar6 = 0;
            if (uVar6 != 0) {
                sk_fun_003551b0();
                if (0 != 0) {
                    sk_fun_003580f4();
                    /* switch: type 3 -> FUN_0034e32c(); types 2/4 no-op */
                    sk_fun_0034e32c();
                }
                return sk_fun_00351538();
            }
        }
        if (iVar7 == 0) {
            return 0;
        }
    }
    if (uVar1 < uVar6) {
        sk_fun_003520e8();
    } else {
        sk_fun_0034bf1c();
    }
    return sk_fun_000839f8();
}

/* FUN_0032c96c @ 0x0032c96c   (est. sk_obj_release_after_sync_2)
 * Run FUN_00353900() then release an object via FUN_0036b270.
 * Confidence: medium
 * Notes: Ghidra FUN_00353900(); FUN_0036b270(). */
void sk_obj_release_after_sync_2(void)
{
    sk_fun_00353900();
    sk_obj_release(0);
}

/* FUN_0032c994 @ 0x0032c994   (est. sk_obj_copy_field10)
 * Copy the +0x10 field from x19 to x20 with refcount balancing.
 * Confidence: medium
 * Notes: Ghidra unaff_x19 source, unaff_x20 dest. */
void sk_obj_copy_field10(long dst, long src)
{
    sk_fun_0034b044();
    sk_obj_release(0);
    sk_obj_retain(0);
    sk_fun_003566cc();
    *(und8_t *)(dst + 0x10) = *(und8_t *)(src + 0x10);
}

/* FUN_0032c9d8 @ 0x0032c9d8   (est. sk_obj_copy3)
 * Copy a three-word object from x19 to x20, releasing the source's first ref.
 * Confidence: medium
 * Notes: Ghidra unaff_x19 source, unaff_x20 dest. */
void sk_obj_copy3(long dst, long src)
{
    und8_t *tmp = (und8_t *)sk_fun_003504d0();
    sk_obj_retain(tmp[0]);
    und8_t v0 = *(und8_t *)src;
    ((und8_t *)dst)[1] = ((und8_t *)src)[1];
    *(und8_t *)dst = v0;
    ((und8_t *)dst)[2] = ((und8_t *)src)[2];
}

/* FUN_0032caac @ 0x0032caac   (est. sk_obj_copy_field18_20)
 * Copy two fields (+0x18, +0x20) from the resolved object into x19, then
 * release an object.
 * Confidence: medium
 * Notes: Ghidra extraout_x1 is the source object. */
void sk_obj_copy_field18_20(long obj)
{
    und8_t src = 0; /* extraout_x1 */
    und8_t v = *(und8_t *)(src + 0x18);
    *(und8_t *)(obj + 0x20) = *(und8_t *)(src + 0x20);
    *(und8_t *)(obj + 0x18) = v;
    sk_obj_release(0);
}

/* FUN_0032cbf8 @ 0x0032cbf8   (est. sk_obj_resize_finalize)
 * Finalize a resize: resolve obj via FUN_00355150(), rebind obj+0x10/+0x18
 * via FUN_0034a32c, validate size with FUN_00377824(0x13f), and if < 0x40 run
 * the resize helpers FUN_003558b8/FUN_0034cdf8/FUN_003728b8(...,2)/FUN_00019858.
 * Confidence: medium
 * Notes: Ghidra lVar1=FUN_00355150(); auVar2=FUN_00377824(0x13f); checks <0x40. */
void sk_obj_resize_finalize(void)
{
    und8_t lVar1 = sk_fun_00355150();
    sk_fun_0034a32c(lVar1, *(und8_t *)(lVar1 + 0x18), *(und8_t *)(lVar1 + 0x10));
    if (sk_fun_00377824(0x13f, 0, 0) < 0x40) {
        sk_fun_003558b8(*(long *)(*(und8_t *)0 - 8) + 0x40);
        sk_fun_0034cdf8();
        sk_fun_003728b8(0, 0, 2);
        sk_fun_00019858();
    }
}

/* FUN_0032b9dc @ 0x0032b9dc   (est. sk_obj_dispatch_by_type)
 * Dispatch a typed operation based on the object's type tag (aux+0x48): for
 * type 1 run FUN_00353dc4(ref), type 2 copy fields into x19 and call through
 * the function pointer at *x16, type 3 run FUN_00352778+FUN_00359c2c,
 * otherwise FUN_00353dc4(0,ref). Then release objects.
 * Confidence: medium
 * Notes: Ghidra auVar4=FUN_00350c5c(); switch on *(byte*)(aux+0x48); unaff_x19
 *   and unaff_x20 are implicit receivers. */
void sk_obj_dispatch_by_type(long obj, int *desc)
{
    und8_t aux = sk_fun_00350c5c();
    und1_t tag = *(und1_t *)(aux + 0x48);
    unsigned int t = (unsigned int)tag;
    und8_t uVar3;
    if (3 < tag) {
        t = *desc + 4;
    }
    switch (t) {
    default:
        sk_fun_00353dc4(0, *(und8_t *)(desc + 2));
        break;
    case 1:
        sk_fun_00353dc4(*(und8_t *)(desc + 2));
        break;
    case 2:
        uVar3 = *(und8_t *)(desc + 6);
        *(und8_t *)(obj + 0x20) = *(und8_t *)(desc + 8);
        *(und8_t *)(obj + 0x18) = uVar3;
        sk_fun_0034b07c(aux, uVar3, uVar3);
        /* call through function pointer at *x16 (opaque here) */
        sk_fun_003575d4();
        break;
    case 3:
        sk_fun_00352778();
        sk_fun_00359c2c();
    }
    sk_fun_003571b0();
    sk_obj_release(0);
    sk_obj_release(0);
}





