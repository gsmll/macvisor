/* Recreated from cl4_kernel.raw (cL4 Secure Kernel, arm64e, image base 0) —
 * the cL4 microkernel (GL1). Ground truth: Ghidra FUN_ names + addresses.
 * All names are estimates unless string/header matched.
 * Slice 19: 0x3517cc-0x352444 syscall/exception-entry region.
 * This region is a dense cluster of tiny out-of-line helper clones and
 * syscall/name-table setup stubs; most entries are no-op or single-return
 * leaf functions that access the caller's stack frame via the frame pointer
 * (Ghidra unaff_x29/x19..x28). Confidence is low unless a callee/pattern is
 * unambiguous. */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "sk_internal.h"

/* ------------------------------------------------------------------ *
 * Out-of-range cL4 helpers referenced by this region (FUN_ addr in
 * comment; reconstructed by sibling SK range workers).
 * ------------------------------------------------------------------ */
extern void sk_syscall_name_table_init(unsigned int tag, const void *table); /* FUN_00002534 */
extern void sk_helper_27754(void);   /* FUN_00027754 */
extern void sk_helper_2472e0(void);  /* FUN_002472e0 */
extern void sk_helper_8f6c0(void);   /* FUN_0008f6c0 */
extern void sk_helper_8f6f4(void);   /* FUN_0008f6f4 */
extern void sk_helper_277e8(void);   /* FUN_000277e8 */
extern void sk_helper_319628(void);  /* FUN_00319628 */
extern void sk_helper_310a74(word_t a); /* FUN_00310a74 */
extern void sk_helper_310b08(void);  /* FUN_00310b08 */
extern void sk_helper_1df60(void);   /* FUN_0001df60 */

/* FUN_00003517cc @ 0x00003517cc   (est. sk_sysc_noop_3517cc)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_3517cc(void)
{
        (void)0; /* no-op */
}

/* FUN_00003517d8 @ 0x00003517d8   (est. sk_sysc_read_local_3517d8)
 * Confidence: low
 * Notes: read caller-frame local at x29-0x68
 */
word_t sk_sysc_read_local_3517d8(word_t frame_ptr)
{
    uint8_t *frame = (uint8_t *)frame_ptr;  /* caller frame (Ghidra unaff_x29) */
    return *(word_t *)(frame - 0x68);
}

/* FUN_00003517e4 @ 0x00003517e4   (est. sk_sysc_result_3517e4)
 * Confidence: low
 * Notes: two pointer adds vs caller base (x28) and caller-frame locals (unaff_x28/x29)
 */
cl4_result_t sk_sysc_result_3517e4(word_t frame_ptr, word_t base_ptr)
{
    cl4_result_t r;
        uint8_t *frame = (uint8_t *)frame_ptr;
        uint8_t *base = (uint8_t *)base_ptr;  /* caller reg x28 */
    r.lo = (word_t)(base + *(long *)(frame - 0x148));
        r.hi = (word_t)(base + *(long *)(frame - 0x150));
        return r;
}

/* FUN_000035187c @ 0x000035187c   (est. sk_sysc_noop_35187c)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_35187c(void)
{
        (void)0; /* no-op */
}

/* FUN_0000351888 @ 0x0000351888   (est. sk_sysc_noop_351888)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_351888(void)
{
        (void)0; /* no-op */
}

/* FUN_0000351894 @ 0x0000351894   (est. sk_sysc_ret0_351894)
 * Confidence: low
 * Notes: return 0 (success) unconditionally
 */
word_t sk_sysc_ret0_351894(void)
{
    return 0;
}

/* FUN_00003518a0 @ 0x00003518a0   (est. sk_sysc_noop_3518a0)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_3518a0(void)
{
        (void)0; /* no-op */
}

/* FUN_00003518ac @ 0x00003518ac   (est. sk_sysc_noop_3518ac)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_3518ac(void)
{
        (void)0; /* no-op */
}

/* FUN_00003518b8 @ 0x00003518b8   (est. sk_sysc_noop_3518b8)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_3518b8(void)
{
        (void)0; /* no-op */
}

/* FUN_00003518c4 @ 0x00003518c4   (est. sk_sysc_noop_3518c4)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_3518c4(void)
{
        (void)0; /* no-op */
}

/* FUN_00003518d0 @ 0x00003518d0   (est. sk_sysc_noop_3518d0)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_3518d0(void)
{
        (void)0; /* no-op */
}

/* FUN_00003518dc @ 0x00003518dc   (est. sk_sysc_noop_3518dc)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_3518dc(void)
{
        (void)0; /* no-op */
}

/* FUN_00003518e8 @ 0x00003518e8   (est. sk_sysc_noop_3518e8)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_3518e8(void)
{
        (void)0; /* no-op */
}

/* FUN_00003518f4 @ 0x00003518f4   (est. sk_sysc_noop_3518f4)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_3518f4(void)
{
        (void)0; /* no-op */
}

/* FUN_0000351900 @ 0x0000351900   (est. sk_sysc_noop_351900)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_351900(void)
{
        (void)0; /* no-op */
}

/* FUN_000035190c @ 0x000035190c   (est. sk_sysc_noop_35190c)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_35190c(void)
{
        (void)0; /* no-op */
}

/* FUN_0000351918 @ 0x0000351918   (est. sk_sysc_noop_351918)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_351918(void)
{
        (void)0; /* no-op */
}

/* FUN_0000351924 @ 0x0000351924   (est. sk_sysc_noop_351924)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_351924(void)
{
        (void)0; /* no-op */
}

/* FUN_0000351930 @ 0x0000351930   (est. sk_sysc_retff_351930)
 * Confidence: low
 * Notes: return 0xff (invalid/error marker) unconditionally
 */
word_t sk_sysc_retff_351930(void)
{
    return 0xff;
}

/* FUN_000035193c @ 0x000035193c   (est. sk_sysc_noop_35193c)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_35193c(void)
{
        (void)0; /* no-op */
}

/* FUN_0000351958 @ 0x0000351958   (est. sk_sysc_noop_351958)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_351958(void)
{
        (void)0; /* no-op */
}

/* FUN_000035196c @ 0x000035196c   (est. sk_sysc_noop_35196c)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_35196c(void)
{
        (void)0; /* no-op */
}

/* FUN_0000351978 @ 0x0000351978   (est. sk_sysc_noop_351978)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_351978(void)
{
        (void)0; /* no-op */
}

/* FUN_0000351984 @ 0x0000351984   (est. sk_sysc_noop_351984)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_351984(void)
{
        (void)0; /* no-op */
}

/* FUN_0000351990 @ 0x0000351990   (est. sk_sysc_noop_351990)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_351990(void)
{
        (void)0; /* no-op */
}

/* FUN_000035199c @ 0x000035199c   (est. sk_sysc_noop_35199c)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_35199c(void)
{
        (void)0; /* no-op */
}

/* FUN_00003519a8 @ 0x00003519a8   (est. sk_sysc_noop_3519a8)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_3519a8(void)
{
        (void)0; /* no-op */
}

/* FUN_00003519b4 @ 0x00003519b4   (est. sk_sysc_noop_3519b4)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_3519b4(void)
{
        (void)0; /* no-op */
}

/* FUN_00003519c0 @ 0x00003519c0   (est. sk_sysc_nametab_3519c0)
 * Confidence: medium
 * Notes: register name/error table, tag 0x657570 (table at DAT_004f1900); callee FUN_00002534
 */
void sk_sysc_nametab_3519c0(void)
{
    sk_syscall_name_table_init(0x657570, (const void *)0x004f1900);
}

/* FUN_00003519d4 @ 0x00003519d4   (est. sk_sysc_nametab_3519d4)
 * Confidence: medium
 * Notes: register name/error table, tag 0x656148 (table at DAT_004e7f98); callee FUN_00002534
 */
void sk_sysc_nametab_3519d4(void)
{
    sk_syscall_name_table_init(0x656148, (const void *)0x004e7f98);
}

/* FUN_00003519e8 @ 0x00003519e8   (est. sk_sysc_nametab_3519e8)
 * Confidence: medium
 * Notes: register name/error table, tag 0x656158 (table at DAT_004e7fa8); callee FUN_00002534
 */
void sk_sysc_nametab_3519e8(void)
{
    sk_syscall_name_table_init(0x656158, (const void *)0x004e7fa8);
}

/* FUN_00003519fc @ 0x00003519fc   (est. sk_sysc_retff_3519fc)
 * Confidence: low
 * Notes: return 0xff (invalid/error marker) unconditionally
 */
word_t sk_sysc_retff_3519fc(void)
{
    return 0xff;
}

/* FUN_0000351a08 @ 0x0000351a08   (est. sk_sysc_noop_351a08)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_351a08(void)
{
        (void)0; /* no-op */
}

/* FUN_0000351a14 @ 0x0000351a14   (est. sk_sysc_noop_351a14)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_351a14(void)
{
        (void)0; /* no-op */
}

/* FUN_0000351a20 @ 0x0000351a20   (est. sk_sysc_noop_351a20)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_351a20(void)
{
        (void)0; /* no-op */
}

/* FUN_0000351a2c @ 0x0000351a2c   (est. sk_sysc_noop_351a2c)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_351a2c(void)
{
        (void)0; /* no-op */
}

/* FUN_0000351a38 @ 0x0000351a38   (est. sk_sysc_noop_351a38)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_351a38(void)
{
        (void)0; /* no-op */
}

/* FUN_0000351a44 @ 0x0000351a44   (est. sk_sysc_noop_351a44)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_351a44(void)
{
        (void)0; /* no-op */
}

/* FUN_0000351a50 @ 0x0000351a50   (est. sk_sysc_noop_351a50)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_351a50(void)
{
        (void)0; /* no-op */
}

/* FUN_0000351a5c @ 0x0000351a5c   (est. sk_sysc_noop_351a5c)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_351a5c(void)
{
        (void)0; /* no-op */
}

/* FUN_0000351a68 @ 0x0000351a68   (est. sk_sysc_noop_351a68)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_351a68(void)
{
        (void)0; /* no-op */
}

/* FUN_0000351a74 @ 0x0000351a74   (est. sk_sysc_table_ptr_351a74)
 * Confidence: medium
 * Notes: returns pointer to table DAT_004e4980 (syscall/name lookup); many callers
 */
word_t sk_sysc_table_ptr_351a74(void)
{
    return (word_t)0x004e4980;
}

/* FUN_0000351a80 @ 0x0000351a80   (est. sk_sysc_noop_351a80)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_351a80(void)
{
        (void)0; /* no-op */
}

/* FUN_0000351a8c @ 0x0000351a8c   (est. sk_sysc_noop_351a8c)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_351a8c(void)
{
        (void)0; /* no-op */
}

/* FUN_0000351a98 @ 0x0000351a98   (est. sk_sysc_noop_351a98)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_351a98(void)
{
        (void)0; /* no-op */
}

/* FUN_0000351aa4 @ 0x0000351aa4   (est. sk_sysc_noop_351aa4)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_351aa4(void)
{
        (void)0; /* no-op */
}

/* FUN_0000351ab0 @ 0x0000351ab0   (est. sk_sysc_noop_351ab0)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_351ab0(void)
{
        (void)0; /* no-op */
}

/* FUN_0000351abc @ 0x0000351abc   (est. sk_sysc_noop_351abc)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_351abc(void)
{
        (void)0; /* no-op */
}

/* FUN_0000351ac8 @ 0x0000351ac8   (est. sk_sysc_noop_351ac8)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_351ac8(void)
{
        (void)0; /* no-op */
}

/* FUN_0000351ad4 @ 0x0000351ad4   (est. sk_sysc_dispatch_351ad4)
 * Confidence: low
 * Notes: tail-call FUN_00027754
 */
void sk_sysc_dispatch_351ad4(void)
{
    sk_helper_27754();
}

/* FUN_0000351aec @ 0x0000351aec   (est. sk_sysc_noop_351aec)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_351aec(void)
{
        (void)0; /* no-op */
}

/* FUN_0000351af8 @ 0x0000351af8   (est. sk_sysc_noop_351af8)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_351af8(void)
{
        (void)0; /* no-op */
}

/* FUN_0000351b04 @ 0x0000351b04   (est. sk_sysc_dispatch_351b04)
 * Confidence: low
 * Notes: tail-call FUN_002472e0
 */
void sk_sysc_dispatch_351b04(void)
{
    sk_helper_2472e0();
}

/* FUN_0000351b20 @ 0x0000351b20   (est. sk_sysc_noop_351b20)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_351b20(void)
{
        (void)0; /* no-op */
}

/* FUN_0000351b2c @ 0x0000351b2c   (est. sk_sysc_noop_351b2c)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_351b2c(void)
{
        (void)0; /* no-op */
}

/* FUN_0000351b38 @ 0x0000351b38   (est. sk_sysc_noop_351b38)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_351b38(void)
{
        (void)0; /* no-op */
}

/* FUN_0000351b44 @ 0x0000351b44   (est. sk_sysc_dispatch_351b44)
 * Confidence: low
 * Notes: call FUN_0008f6c0 / FUN_0008f6f4
 */
void sk_sysc_dispatch_351b44(void)
{
    sk_helper_8f6c0();
        sk_helper_8f6f4();
}

/* FUN_0000351b60 @ 0x0000351b60   (est. sk_sysc_noop_351b60)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_351b60(void)
{
        (void)0; /* no-op */
}

/* FUN_0000351b6c @ 0x0000351b6c   (est. sk_sysc_noop_351b6c)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_351b6c(void)
{
        (void)0; /* no-op */
}

/* FUN_0000351b78 @ 0x0000351b78   (est. sk_sysc_noop_351b78)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_351b78(void)
{
        (void)0; /* no-op */
}

/* FUN_0000351b84 @ 0x0000351b84   (est. sk_sysc_dispatch_351b84)
 * Confidence: low
 * Notes: call FUN_000277e8 then return caller-frame-relative pointer (unaff_x29)
 */
word_t sk_sysc_dispatch_351b84(word_t frame_ptr)
{
    uint8_t *frame = (uint8_t *)frame_ptr;
    sk_helper_277e8();
        return (word_t)(frame - 0x70);
}

/* FUN_0000351ba0 @ 0x0000351ba0   (est. sk_sysc_noop_351ba0)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_351ba0(void)
{
        (void)0; /* no-op */
}

/* FUN_0000351bac @ 0x0000351bac   (est. sk_sysc_noop_351bac)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_351bac(void)
{
        (void)0; /* no-op */
}

/* FUN_0000351bb8 @ 0x0000351bb8   (est. sk_sysc_dispatch_351bb8)
 * Confidence: low
 * Notes: tail-call FUN_00319628
 */
void sk_sysc_dispatch_351bb8(void)
{
    sk_helper_319628();
}

/* FUN_0000351bd4 @ 0x0000351bd4   (est. sk_sysc_noop_351bd4)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_351bd4(void)
{
        (void)0; /* no-op */
}

/* FUN_0000351be0 @ 0x0000351be0   (est. sk_sysc_noop_351be0)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_351be0(void)
{
        (void)0; /* no-op */
}

/* FUN_0000351bec @ 0x0000351bec   (est. sk_sysc_dispatch_351bec)
 * Confidence: low
 * Notes: tail-call FUN_00027754
 */
void sk_sysc_dispatch_351bec(void)
{
    sk_helper_27754();
}

/* FUN_0000351c04 @ 0x0000351c04   (est. sk_sysc_noop_351c04)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_351c04(void)
{
        (void)0; /* no-op */
}

/* FUN_0000351c10 @ 0x0000351c10   (est. sk_sysc_store_local_351c10)
 * Confidence: low
 * Notes: store arg to caller-frame local x29-0x70
 */
void sk_sysc_store_local_351c10(word_t v, word_t frame_ptr)
{
    uint8_t *frame = (uint8_t *)frame_ptr;  /* caller frame (Ghidra unaff_x29) */
    *(word_t *)(frame - 0x70) = v;
}

/* FUN_0000351c1c @ 0x0000351c1c   (est. sk_sysc_noop_351c1c)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_351c1c(void)
{
        (void)0; /* no-op */
}

/* FUN_0000351c28 @ 0x0000351c28   (est. sk_sysc_noop_351c28)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_351c28(void)
{
        (void)0; /* no-op */
}

/* FUN_0000351c34 @ 0x0000351c34   (est. sk_sysc_dispatch_351c34)
 * Confidence: low
 * Notes: tail-call FUN_00310a74
 */
void sk_sysc_dispatch_351c34(void)
{
    sk_helper_310a74(0);
}

/* FUN_0000351c4c @ 0x0000351c4c   (est. sk_sysc_noop_351c4c)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_351c4c(void)
{
        (void)0; /* no-op */
}

/* FUN_0000351c58 @ 0x0000351c58   (est. sk_sysc_noop_351c58)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_351c58(void)
{
        (void)0; /* no-op */
}

/* FUN_0000351c64 @ 0x0000351c64   (est. sk_sysc_noop_351c64)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_351c64(void)
{
        (void)0; /* no-op */
}

/* FUN_0000351c70 @ 0x0000351c70   (est. sk_sysc_noop_351c70)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_351c70(void)
{
        (void)0; /* no-op */
}

/* FUN_0000351c7c @ 0x0000351c7c   (est. sk_sysc_noop_351c7c)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_351c7c(void)
{
        (void)0; /* no-op */
}

/* FUN_0000351c88 @ 0x0000351c88   (est. sk_sysc_noop_351c88)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_351c88(void)
{
        (void)0; /* no-op */
}

/* FUN_0000351c94 @ 0x0000351c94   (est. sk_sysc_noop_351c94)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_351c94(void)
{
        (void)0; /* no-op */
}

/* FUN_0000351ca0 @ 0x0000351ca0   (est. sk_sysc_noop_351ca0)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_351ca0(void)
{
        (void)0; /* no-op */
}

/* FUN_0000351cac @ 0x0000351cac   (est. sk_sysc_result_351cac)
 * Confidence: low
 * Notes: {ptr,0} result; ptr is caller-frame local (unaff_x29)
 */
cl4_result_t sk_sysc_result_351cac(word_t frame_ptr)
{
    cl4_result_t r;
        uint8_t *frame = (uint8_t *)frame_ptr;
    r.lo = (word_t)(frame - 0x78);
        r.hi = 0;
        return r;
}

/* FUN_0000351cb8 @ 0x0000351cb8   (est. sk_sysc_noop_351cb8)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_351cb8(void)
{
        (void)0; /* no-op */
}

/* FUN_0000351cc4 @ 0x0000351cc4   (est. sk_sysc_noop_351cc4)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_351cc4(void)
{
        (void)0; /* no-op */
}

/* FUN_0000351cd0 @ 0x0000351cd0   (est. sk_sysc_noop_351cd0)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_351cd0(void)
{
        (void)0; /* no-op */
}

/* FUN_0000351cdc @ 0x0000351cdc   (est. sk_sysc_noop_351cdc)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_351cdc(void)
{
        (void)0; /* no-op */
}

/* FUN_0000351ce8 @ 0x0000351ce8   (est. sk_sysc_store_local_351ce8)
 * Confidence: low
 * Notes: store arg to caller-frame local x29-0xb8
 */
void sk_sysc_store_local_351ce8(word_t v, word_t frame_ptr)
{
    uint8_t *frame = (uint8_t *)frame_ptr;
    *(word_t *)(frame - 0xb8) = v;
}

/* FUN_0000351cf4 @ 0x0000351cf4   (est. sk_sysc_noop_351cf4)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_351cf4(void)
{
        (void)0; /* no-op */
}

/* FUN_0000351d00 @ 0x0000351d00   (est. sk_sysc_result_351d00)
 * Confidence: low
 * Notes: {ptr,0} result; ptr is caller-frame local (unaff_x29)
 */
cl4_result_t sk_sysc_result_351d00(word_t frame_ptr)
{
    cl4_result_t r;
        uint8_t *frame = (uint8_t *)frame_ptr;
    r.lo = (word_t)(frame - 0x70);
        r.hi = 0;
        return r;
}

/* FUN_0000351d0c @ 0x0000351d0c   (est. sk_sysc_noop_351d0c)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_351d0c(void)
{
        (void)0; /* no-op */
}

/* FUN_0000351d18 @ 0x0000351d18   (est. sk_sysc_noop_351d18)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_351d18(void)
{
        (void)0; /* no-op */
}

/* FUN_0000351d24 @ 0x0000351d24   (est. sk_sysc_noop_351d24)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_351d24(void)
{
        (void)0; /* no-op */
}

/* FUN_0000351d30 @ 0x0000351d30   (est. sk_sysc_noop_351d30)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_351d30(void)
{
        (void)0; /* no-op */
}

/* FUN_0000351d4c @ 0x0000351d4c   (est. sk_sysc_mix_351d4c)
 * Confidence: medium
 * Notes: word-mixing hash (rotate/xor/add avalanche of four 64-bit inputs); callers FUN_001a842c, FUN_00229ebc
 */
word_t sk_sysc_mix_351d4c(word_t p0, word_t w0, word_t w1, word_t w2)
{
    word_t x = w0, y = w1, z = w2;   /* caller regs x10,x11,x12 */
        word_t f, b, a, d, c;
    f = y ^ (x >> 0x33 | x << 0xd);
        b = (z >> 0x20 | z << 0x20) + p0;
        a = f + b;
        b = b ^ (p0 >> 0x30 | p0 << 0x10);
        d = a ^ (f >> 0x2f | f << 0x11);
        f = (y >> 0x20 | y << 0x20) + b;
        c = f ^ (b >> 0x2b | b << 0x15);
        f = d + f ^ (d >> 0x33 | d << 0xd);
        b = (a >> 0x20 | a << 0x20) + c;
        a = f + b;
        b = b ^ (c >> 0x30 | c << 0x10);
        return (b >> 0x2b | b << 0x15) ^ (f >> 0x2f | f << 0x11) ^
               (a >> 0x20 | a << 0x20) ^ a;
}

/* FUN_0000351d9c @ 0x0000351d9c   (est. sk_sysc_noop_351d9c)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_351d9c(void)
{
        (void)0; /* no-op */
}

/* FUN_0000351da8 @ 0x0000351da8   (est. sk_sysc_noop_351da8)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_351da8(void)
{
        (void)0; /* no-op */
}

/* FUN_0000351db4 @ 0x0000351db4   (est. sk_sysc_noop_351db4)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_351db4(void)
{
        (void)0; /* no-op */
}

/* FUN_0000351dc0 @ 0x0000351dc0   (est. sk_sysc_noop_351dc0)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_351dc0(void)
{
        (void)0; /* no-op */
}

/* FUN_0000351dcc @ 0x0000351dcc   (est. sk_sysc_noop_351dcc)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_351dcc(void)
{
        (void)0; /* no-op */
}

/* FUN_0000351dd8 @ 0x0000351dd8   (est. sk_sysc_noop_351dd8)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_351dd8(void)
{
        (void)0; /* no-op */
}

/* FUN_0000351de4 @ 0x0000351de4   (est. sk_sysc_noop_351de4)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_351de4(void)
{
        (void)0; /* no-op */
}

/* FUN_0000351df0 @ 0x0000351df0   (est. sk_sysc_noop_351df0)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_351df0(void)
{
        (void)0; /* no-op */
}

/* FUN_0000351dfc @ 0x0000351dfc   (est. sk_sysc_noop_351dfc)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_351dfc(void)
{
        (void)0; /* no-op */
}

/* FUN_0000351e08 @ 0x0000351e08   (est. sk_sysc_noop_351e08)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_351e08(void)
{
        (void)0; /* no-op */
}

/* FUN_0000351e14 @ 0x0000351e14   (est. sk_sysc_noop_351e14)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_351e14(void)
{
        (void)0; /* no-op */
}

/* FUN_0000351e20 @ 0x0000351e20   (est. sk_sysc_noop_351e20)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_351e20(void)
{
        (void)0; /* no-op */
}

/* FUN_0000351e3c @ 0x0000351e3c   (est. sk_sysc_noop_351e3c)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_351e3c(void)
{
        (void)0; /* no-op */
}

/* FUN_0000351e48 @ 0x0000351e48   (est. sk_sysc_noop_351e48)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_351e48(void)
{
        (void)0; /* no-op */
}

/* FUN_0000351e54 @ 0x0000351e54   (est. sk_sysc_noop_351e54)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_351e54(void)
{
        (void)0; /* no-op */
}

/* FUN_0000351e60 @ 0x0000351e60   (est. sk_sysc_noop_351e60)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_351e60(void)
{
        (void)0; /* no-op */
}

/* FUN_0000351e6c @ 0x0000351e6c   (est. sk_sysc_noop_351e6c)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_351e6c(void)
{
        (void)0; /* no-op */
}

/* FUN_0000351e78 @ 0x0000351e78   (est. sk_sysc_noop_351e78)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_351e78(void)
{
        (void)0; /* no-op */
}

/* FUN_0000351e84 @ 0x0000351e84   (est. sk_sysc_noop_351e84)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_351e84(void)
{
        (void)0; /* no-op */
}

/* FUN_0000351e90 @ 0x0000351e90   (est. sk_sysc_noop_351e90)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_351e90(void)
{
        (void)0; /* no-op */
}

/* FUN_0000351e9c @ 0x0000351e9c   (est. sk_sysc_noop_351e9c)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_351e9c(void)
{
        (void)0; /* no-op */
}

/* FUN_0000351ea8 @ 0x0000351ea8   (est. sk_sysc_noop_351ea8)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_351ea8(void)
{
        (void)0; /* no-op */
}

/* FUN_0000351eb4 @ 0x0000351eb4   (est. sk_sysc_noop_351eb4)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_351eb4(void)
{
        (void)0; /* no-op */
}

/* FUN_0000351ec0 @ 0x0000351ec0   (est. sk_sysc_noop_351ec0)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_351ec0(void)
{
        (void)0; /* no-op */
}

/* FUN_0000351ecc @ 0x0000351ecc   (est. sk_sysc_ret0_351ecc)
 * Confidence: low
 * Notes: return 0 (success) unconditionally
 */
word_t sk_sysc_ret0_351ecc(void)
{
    return 0;
}

/* FUN_0000351ee0 @ 0x0000351ee0   (est. sk_sysc_dispatch_351ee0)
 * Confidence: low
 * Notes: tail-call FUN_00310b08
 */
void sk_sysc_dispatch_351ee0(void)
{
    sk_helper_310b08();
}

/* FUN_0000351ef8 @ 0x0000351ef8   (est. sk_sysc_dispatch_351ef8)
 * Confidence: low
 * Notes: tail-call FUN_00027754
 */
void sk_sysc_dispatch_351ef8(void)
{
    sk_helper_27754();
}

/* FUN_0000351f10 @ 0x0000351f10   (est. sk_sysc_noop_351f10)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_351f10(void)
{
        (void)0; /* no-op */
}

/* FUN_0000351f1c @ 0x0000351f1c   (est. sk_sysc_noop_351f1c)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_351f1c(void)
{
        (void)0; /* no-op */
}

/* FUN_0000351f28 @ 0x0000351f28   (est. sk_sysc_noop_351f28)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_351f28(void)
{
        (void)0; /* no-op */
}

/* FUN_0000351f34 @ 0x0000351f34   (est. sk_sysc_noop_351f34)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_351f34(void)
{
        (void)0; /* no-op */
}

/* FUN_0000351f40 @ 0x0000351f40   (est. sk_sysc_noop_351f40)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_351f40(void)
{
        (void)0; /* no-op */
}

/* FUN_0000351f4c @ 0x0000351f4c   (est. sk_sysc_noop_351f4c)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_351f4c(void)
{
        (void)0; /* no-op */
}

/* FUN_0000351f58 @ 0x0000351f58   (est. sk_sysc_noop_351f58)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_351f58(void)
{
        (void)0; /* no-op */
}

/* FUN_0000351f64 @ 0x0000351f64   (est. sk_sysc_noop_351f64)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_351f64(void)
{
        (void)0; /* no-op */
}

/* FUN_0000351f70 @ 0x0000351f70   (est. sk_sysc_noop_351f70)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_351f70(void)
{
        (void)0; /* no-op */
}

/* FUN_0000351f7c @ 0x0000351f7c   (est. sk_sysc_noop_351f7c)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_351f7c(void)
{
        (void)0; /* no-op */
}

/* FUN_0000351f88 @ 0x0000351f88   (est. sk_sysc_noop_351f88)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_351f88(void)
{
        (void)0; /* no-op */
}

/* FUN_0000351f94 @ 0x0000351f94   (est. sk_sysc_noop_351f94)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_351f94(void)
{
        (void)0; /* no-op */
}

/* FUN_0000351fb0 @ 0x0000351fb0   (est. sk_sysc_noop_351fb0)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_351fb0(void)
{
        (void)0; /* no-op */
}

/* FUN_0000351fc0 @ 0x0000351fc0   (est. sk_sysc_pack_word_351fc0)
 * Confidence: low
 * Notes: write low 32 bits + byte4 of arg through caller pointer (unaff_x19)
 */
void sk_sysc_pack_word_351fc0(word_t v, word_t base_ptr)
{
    unsigned char *p = (unsigned char *)base_ptr;  /* caller reg x19 */
    *(uint32_t *)p = (uint32_t)v;
        p[4] = (uint8_t)(v >> 32);
}

/* FUN_0000351fd0 @ 0x0000351fd0   (est. sk_sysc_result_351fd0)
 * Confidence: low
 * Notes: masked base+0x20 (x19) and masked reg (x22)
 */
cl4_result_t sk_sysc_result_351fd0(word_t base_ptr, word_t reg_ptr)
{
    cl4_result_t r;
    r.lo = ((word_t)base_ptr & 0xfffffffffffffff) + 0x20;
        r.hi = ((word_t)reg_ptr & 0xffffffffffff);
        return r;
}

/* FUN_0000351fe0 @ 0x0000351fe0   (est. sk_sysc_dispatch_351fe0)
 * Confidence: low
 * Notes: call FUN_00310a74(caller-frame local x29-0x78) then FUN_0001df60
 */
void sk_sysc_dispatch_351fe0(word_t frame_ptr)
{
    uint8_t *frame = (uint8_t *)frame_ptr;
    sk_helper_310a74(*(word_t *)(frame - 0x78));
        sk_helper_1df60();
}

/* FUN_0000352008 @ 0x0000352008   (est. sk_sysc_noop_352008)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_352008(void)
{
        (void)0; /* no-op */
}

/* FUN_0000352018 @ 0x0000352018   (est. sk_sysc_noop_352018)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_352018(void)
{
        (void)0; /* no-op */
}

/* FUN_0000352028 @ 0x0000352028   (est. sk_sysc_copy_field_352028)
 * Confidence: low
 * Notes: copy word at param_2+8 into caller slot base+8 (unaff_x20); param_1 unused
 */
void sk_sysc_copy_field_352028(word_t unused, const void *src, word_t base_ptr)
{
    word_t *dst = (word_t *)base_ptr;  /* caller reg x20 */
        (void)unused;
    dst[1] = ((word_t *)src)[1];
}

/* FUN_0000352038 @ 0x0000352038   (est. sk_sysc_noop_352038)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_352038(void)
{
        (void)0; /* no-op */
}

/* FUN_0000352048 @ 0x0000352048   (est. sk_sysc_ret0_352048)
 * Confidence: low
 * Notes: return 0 (success) unconditionally
 */
word_t sk_sysc_ret0_352048(void)
{
    return 0;
}

/* FUN_0000352058 @ 0x0000352058   (est. sk_sysc_result_352058)
 * Confidence: low
 * Notes: {1, &stack-local} count-of-one view (Ghidra &stack0x20)
 */
cl4_result_t sk_sysc_result_352058(void)
{
    cl4_result_t r;
        word_t slot = 0;
    r.lo = 1;
        r.hi = (word_t)(void *)&slot;
        return r;
}

/* FUN_0000352068 @ 0x0000352068   (est. sk_sysc_noop_352068)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_352068(void)
{
        (void)0; /* no-op */
}

/* FUN_0000352078 @ 0x0000352078   (est. sk_sysc_noop_352078)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_352078(void)
{
        (void)0; /* no-op */
}

/* FUN_0000352088 @ 0x0000352088   (est. sk_sysc_noop_352088)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_352088(void)
{
        (void)0; /* no-op */
}

/* FUN_0000352098 @ 0x0000352098   (est. sk_sysc_noop_352098)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_352098(void)
{
        (void)0; /* no-op */
}

/* FUN_00003520a4 @ 0x00003520a4   (est. sk_sysc_result_3520a4)
 * Confidence: low
 * Notes: {1, param_1} count-of-one view
 */
cl4_result_t sk_sysc_result_3520a4(word_t p)
{
    cl4_result_t r;
    r.lo = 1;
        r.hi = p;
        return r;
}

/* FUN_00003520b4 @ 0x00003520b4   (est. sk_sysc_read_argfield_3520b4)
 * Confidence: low
 * Notes: read word at param_1-0x100
 */
word_t sk_sysc_read_argfield_3520b4(const void *p)
{
    return *(word_t *)((uint8_t *)p - 0x100);
}

/* FUN_00003520c0 @ 0x00003520c0   (est. sk_sysc_noop_3520c0)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_3520c0(void)
{
        (void)0; /* no-op */
}

/* FUN_00003520d0 @ 0x00003520d0   (est. sk_sysc_store_sentinel_3520d0)
 * Confidence: low
 * Notes: store 0x8000000000000000 sentinel to caller-frame local x29-0x58
 */
void sk_sysc_store_sentinel_3520d0(word_t frame_ptr)
{
    uint8_t *frame = (uint8_t *)frame_ptr;
    *(word_t *)(frame - 0x58) = 0x8000000000000000;
}

/* FUN_00003520dc @ 0x00003520dc   (est. sk_sysc_noop_3520dc)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_3520dc(void)
{
        (void)0; /* no-op */
}

/* FUN_00003520e8 @ 0x00003520e8   (est. sk_sysc_align_3520e8)
 * Confidence: low
 * Notes: align-down of (v + x19) to ~x9 (page/alignment helper)
 */
word_t sk_sysc_align_3520e8(word_t v, word_t base_ptr, word_t mask_ptr)
{
    word_t base = (word_t)base_ptr;  /* caller reg x19 */
        word_t mask = (word_t)mask_ptr;      /* caller reg x9 */
    return (v + base) & ~mask;
}

/* FUN_00003520f8 @ 0x00003520f8   (est. sk_sysc_noop_3520f8)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_3520f8(void)
{
        (void)0; /* no-op */
}

/* FUN_0000352108 @ 0x0000352108   (est. sk_sysc_noop_352108)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_352108(void)
{
        (void)0; /* no-op */
}

/* FUN_0000352118 @ 0x0000352118   (est. sk_sysc_noop_352118)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_352118(void)
{
        (void)0; /* no-op */
}

/* FUN_0000352128 @ 0x0000352128   (est. sk_sysc_store_local_352128)
 * Confidence: low
 * Notes: store arg to caller-frame local x29-0x78
 */
void sk_sysc_store_local_352128(word_t v, word_t frame_ptr)
{
    uint8_t *frame = (uint8_t *)frame_ptr;
    *(word_t *)(frame - 0x78) = v;
}

/* FUN_0000352134 @ 0x0000352134   (est. sk_sysc_noop_352134)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_352134(void)
{
        (void)0; /* no-op */
}

/* FUN_0000352140 @ 0x0000352140   (est. sk_sysc_read_local_352140)
 * Confidence: low
 * Notes: read caller-frame local at x29-0x2b0
 */
word_t sk_sysc_read_local_352140(word_t frame_ptr)
{
    uint8_t *frame = (uint8_t *)frame_ptr;  /* caller frame (Ghidra unaff_x29) */
    return *(word_t *)(frame - 0x2b0);
}

/* FUN_000035215c @ 0x000035215c   (est. sk_sysc_noop_35215c)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_35215c(void)
{
        (void)0; /* no-op */
}

/* FUN_000035216c @ 0x000035216c   (est. sk_sysc_noop_35216c)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_35216c(void)
{
        (void)0; /* no-op */
}

/* FUN_000035217c @ 0x000035217c   (est. sk_sysc_store_local_35217c)
 * Confidence: low
 * Notes: store arg to caller-frame local x29-0x58
 */
void sk_sysc_store_local_35217c(word_t v, word_t frame_ptr)
{
    uint8_t *frame = (uint8_t *)frame_ptr;
    *(word_t *)(frame - 0x58) = v;
}

/* FUN_0000352188 @ 0x0000352188   (est. sk_sysc_noop_352188)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_352188(void)
{
        (void)0; /* no-op */
}

/* FUN_0000352194 @ 0x0000352194   (est. sk_sysc_load_word_352194)
 * Confidence: low
 * Notes: return *param_1
 */
word_t sk_sysc_load_word_352194(const word_t *p)
{
    return *p;
}

/* FUN_00003521a4 @ 0x00003521a4   (est. sk_sysc_store_ptrconst_3521a4)
 * Confidence: low
 * Notes: store pointer constant DAT_00657778 to caller-frame local x29-0x48
 */
void sk_sysc_store_ptrconst_3521a4(word_t frame_ptr)
{
    uint8_t *frame = (uint8_t *)frame_ptr;
    *(void **)(frame - 0x48) = (void *)0x00657778;
}

/* FUN_00003521b4 @ 0x00003521b4   (est. sk_sysc_noop_3521b4)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_3521b4(void)
{
        (void)0; /* no-op */
}

/* FUN_00003521c4 @ 0x00003521c4   (est. sk_sysc_noop_3521c4)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_3521c4(void)
{
        (void)0; /* no-op */
}

/* FUN_00003521d4 @ 0x00003521d4   (est. sk_sysc_noop_3521d4)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_3521d4(void)
{
        (void)0; /* no-op */
}

/* FUN_00003521e4 @ 0x00003521e4   (est. sk_sysc_noop_3521e4)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_3521e4(void)
{
        (void)0; /* no-op */
}

/* FUN_0000352200 @ 0x0000352200   (est. sk_sysc_noop_352200)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_352200(void)
{
        (void)0; /* no-op */
}

/* FUN_0000352210 @ 0x0000352210   (est. sk_sysc_noop_352210)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_352210(void)
{
        (void)0; /* no-op */
}

/* FUN_0000352220 @ 0x0000352220   (est. sk_sysc_noop_352220)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_352220(void)
{
        (void)0; /* no-op */
}

/* FUN_0000352230 @ 0x0000352230   (est. sk_sysc_noop_352230)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_352230(void)
{
        (void)0; /* no-op */
}

/* FUN_0000352240 @ 0x0000352240   (est. sk_sysc_noop_352240)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_352240(void)
{
        (void)0; /* no-op */
}

/* FUN_0000352250 @ 0x0000352250   (est. sk_sysc_noop_352250)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_352250(void)
{
        (void)0; /* no-op */
}

/* FUN_0000352260 @ 0x0000352260   (est. sk_sysc_result_352260)
 * Confidence: low
 * Notes: read 16-byte result from caller-frame local (unaff_x29)
 */
cl4_result_t sk_sysc_result_352260(word_t frame_ptr)
{
    uint8_t *frame = (uint8_t *)frame_ptr;
    return *(cl4_result_t *)(frame - 0x60);
}

/* FUN_0000352270 @ 0x0000352270   (est. sk_sysc_noop_352270)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_352270(void)
{
        (void)0; /* no-op */
}

/* FUN_0000352280 @ 0x0000352280   (est. sk_sysc_noop_352280)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_352280(void)
{
        (void)0; /* no-op */
}

/* FUN_0000352290 @ 0x0000352290   (est. sk_sysc_noop_352290)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_352290(void)
{
        (void)0; /* no-op */
}

/* FUN_000035229c @ 0x000035229c   (est. sk_sysc_round_pow2_35229c)
 * Confidence: low
 * Notes: store (v-1)&v (power-of-two round-down) into caller slot base+0x20 (unaff_x20)
 */
void sk_sysc_round_pow2_35229c(word_t v, word_t base_ptr)
{
    word_t *slot = (word_t *)base_ptr;  /* caller reg x20 */
    slot[4] = (v - 1) & v;
}

/* FUN_00003522b8 @ 0x00003522b8   (est. sk_sysc_noop_3522b8)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_3522b8(void)
{
        (void)0; /* no-op */
}

/* FUN_00003522c8 @ 0x00003522c8   (est. sk_sysc_noop_3522c8)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_3522c8(void)
{
        (void)0; /* no-op */
}

/* FUN_00003522d4 @ 0x00003522d4   (est. sk_sysc_noop_3522d4)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_3522d4(void)
{
        (void)0; /* no-op */
}

/* FUN_00003522e4 @ 0x00003522e4   (est. sk_sysc_dispatch_3522e4)
 * Confidence: low
 * Notes: call FUN_00310a74 then FUN_0001df60
 */
void sk_sysc_dispatch_3522e4(void)
{
    sk_helper_310a74(0);
        sk_helper_1df60();
}

/* FUN_0000352304 @ 0x0000352304   (est. sk_sysc_retff_352304)
 * Confidence: low
 * Notes: return 0xff (invalid/error marker) unconditionally
 */
word_t sk_sysc_retff_352304(void)
{
    return 0xff;
}

/* FUN_0000352314 @ 0x0000352314   (est. sk_sysc_noop_352314)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_352314(void)
{
        (void)0; /* no-op */
}

/* FUN_0000352320 @ 0x0000352320   (est. sk_sysc_noop_352320)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_352320(void)
{
        (void)0; /* no-op */
}

/* FUN_0000352330 @ 0x0000352330   (est. sk_sysc_noop_352330)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_352330(void)
{
        (void)0; /* no-op */
}

/* FUN_0000352340 @ 0x0000352340   (est. sk_sysc_noop_352340)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_352340(void)
{
        (void)0; /* no-op */
}

/* FUN_0000352350 @ 0x0000352350   (est. sk_sysc_noop_352350)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_352350(void)
{
        (void)0; /* no-op */
}

/* FUN_0000352360 @ 0x0000352360   (est. sk_sysc_noop_352360)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_352360(void)
{
        (void)0; /* no-op */
}

/* FUN_0000352370 @ 0x0000352370   (est. sk_sysc_noop_352370)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_352370(void)
{
        (void)0; /* no-op */
}

/* FUN_000035237c @ 0x000035237c   (est. sk_sysc_result_35237c)
 * Confidence: low
 * Notes: deref a 16-byte cl4_result_t
 */
cl4_result_t sk_sysc_result_35237c(const cl4_result_t *r)
{
    return *r;
}

/* FUN_000035238c @ 0x000035238c   (est. sk_sysc_noop_35238c)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_35238c(void)
{
        (void)0; /* no-op */
}

/* FUN_000035239c @ 0x000035239c   (est. sk_sysc_result_35239c)
 * Confidence: low
 * Notes: pack {param_2,param_3}
 */
cl4_result_t sk_sysc_result_35239c(word_t a, word_t b, word_t c)
{
    cl4_result_t r;
    r.lo = b;
        r.hi = c;
        return r;
}

/* FUN_00003523ac @ 0x00003523ac   (est. sk_sysc_noop_3523ac)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_3523ac(void)
{
        (void)0; /* no-op */
}

/* FUN_00003523bc @ 0x00003523bc   (est. sk_sysc_dispatch_3523bc)
 * Confidence: low
 * Notes: store caller x28 into caller-frame local, then FUN_00310a74 + FUN_0001df60
 */
void sk_sysc_dispatch_3523bc(word_t frame_ptr, word_t reg_ptr)
{
    uint8_t *frame = (uint8_t *)frame_ptr;
        word_t reg = (word_t)reg_ptr;  /* caller x28 */
    *(word_t *)(frame - 0x60) = reg;
        sk_helper_310a74(0);
        sk_helper_1df60();
}

/* FUN_00003523e0 @ 0x00003523e0   (est. sk_sysc_noop_3523e0)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_3523e0(void)
{
        (void)0; /* no-op */
}

/* FUN_00003523f0 @ 0x00003523f0   (est. sk_sysc_noop_3523f0)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_3523f0(void)
{
        (void)0; /* no-op */
}

/* FUN_00003523fc @ 0x00003523fc   (est. sk_sysc_noop_3523fc)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_3523fc(void)
{
        (void)0; /* no-op */
}

/* FUN_0000352408 @ 0x0000352408   (est. sk_sysc_noop_352408)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_352408(void)
{
        (void)0; /* no-op */
}

/* FUN_0000352414 @ 0x0000352414   (est. sk_sysc_store_sentinel_352414)
 * Confidence: low
 * Notes: store 0x8000000000000000 through caller pointer (unaff_x19)
 */
void sk_sysc_store_sentinel_352414(word_t base_ptr)
{
    word_t *base = (word_t *)base_ptr;  /* caller reg x19 */
    *base = 0x8000000000000000;
}

/* FUN_0000352420 @ 0x0000352420   (est. sk_sysc_noop_352420)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_352420(void)
{
        (void)0; /* no-op */
}

/* FUN_000035242c @ 0x000035242c   (est. sk_sysc_noop_35242c)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_35242c(void)
{
        (void)0; /* no-op */
}

/* FUN_0000352438 @ 0x0000352438   (est. sk_sysc_noop_352438)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_352438(void)
{
        (void)0; /* no-op */
}

/* FUN_0000352444 @ 0x0000352444   (est. sk_sysc_noop_352444)
 * Confidence: low
 * Notes: no-op stub
 */
void sk_sysc_noop_352444(void)
{
        (void)0; /* no-op */
}

