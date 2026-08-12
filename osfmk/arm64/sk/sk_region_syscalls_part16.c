/* Recreated from cl4_kernel.raw (cL4 Secure Kernel, arm64e, image base 0) —
 * the cL4 microkernel (GL1). Ground truth: Ghidra FUN_ names + addresses.
 * All names are estimates unless string/header matched.
 * Slice 16: 0x34efb8-0x350038 syscall/exception-entry region. */

#include <stdint.h>
#include <stddef.h>
#include "sk_internal.h"
#include "sk_region_syscalls.h"

/* 16-byte cL4/Swift "Any"-value pair: {value, type-metadata/flags}. */
typedef struct sk_any_pair {
    und8_t lo;
    und8_t hi;
} sk_any_pair_t;

/* Out-of-range cL4/Swift-runtime helpers referenced by this region
 * (FUN_ addr in comment; reconstructed by sibling SK range workers or the
 * Swift runtime layer). Names are estimates. */
extern long sk_obj_iv32_get(uint64_t obj);          /* FUN_00310a74 */
extern long sk_obj_iv40_get(uint64_t obj);          /* FUN_00310a44 */
extern long sk_obj_ivc_get(uint64_t obj);           /* FUN_00310e20 */
extern long sk_obj_iv4_get(uint64_t obj);           /* FUN_0014ae44 */
extern long sk_obj_iv20_get(uint64_t obj);          /* FUN_000277b8 */
extern long *sk_obj_method_dispatch(long *obj, long ctx); /* FUN_0006a4c0 */
extern void sk_teardown_a(void *a);              /* FUN_00376820 */
extern void sk_teardown_b(void *a);              /* FUN_00376838 */
extern uint64_t sk_runtime_boot(uint64_t v);           /* FUN_003246ec */
extern void sk_runtime_call(und8_t a, und8_t b, und8_t c); /* FUN_003722e4 */
extern void sk_obj_vtbl_call(und8_t a, und8_t b, und8_t c); /* FUN_000839f8 */
extern void sk_swift_fatal(und8_t *msg, long msg_len, long flags, uint64_t code,
                           uint64_t detail, und8_t *file, long file_len, long col); /* FUN_001afa84 */
extern void sk_runtime_ping(void);               /* FUN_0036986c */
extern void sk_runtime_req(uint64_t a, uint64_t b, und8_t c, und8_t d); /* FUN_002a4c98 */
extern void sk_runtime_fini(void);               /* FUN_0001df60 */
extern void sk_print_err(und8_t *msg, long len, long col); /* FUN_001a89a8 */
extern void *sk_alloc_tag(uint64_t meta, uint64_t size, uint64_t tag); /* FUN_0036a940 */
extern void sk_swift_grow(long n);               /* FUN_001fab14 */
extern void sk_boot_reg(und8_t *a, void *b);     /* FUN_00002534 */
extern uint64_t sk_runtime_cur(void);               /* FUN_0008f6f4 */


/*--------------------------------------------------------------------*/
/* FUN_0034efb8 @ 0x0034efb8   (est. sk_sys_stub_efb8)
 * Ghidra: void FUN_0034efb8(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_efb8(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034efc8 @ 0x0034efc8   (est. sk_sys_stub_efc8)
 * Ghidra: void FUN_0034efc8(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_efc8(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034efdc @ 0x0034efdc   (est. sk_obj_iv32_call)
 * Ghidra: 
 * Medium confidence. Notes: calls FUN_00310a74
 */
void sk_obj_iv32_call(void)
{
    sk_obj_iv32_get(0);  /* FUN_00310a74; result discarded */
}


/*--------------------------------------------------------------------*/
/* FUN_0034eff8 @ 0x0034eff8   (est. sk_obj_iv40_call)
 * Ghidra: 
 * Medium confidence. Notes: calls FUN_00310a44
 */
void sk_obj_iv40_call(void)
{
    sk_obj_iv40_get(0);  /* FUN_00310a44 */
}


/*--------------------------------------------------------------------*/
/* FUN_0034f014 @ 0x0034f014   (est. sk_obj_ivc_call)
 * Ghidra: 
 * Medium confidence. Notes: calls FUN_00310e20
 */
void sk_obj_ivc_call(void)
{
    sk_obj_ivc_get(0);  /* FUN_00310e20 */
}


/*--------------------------------------------------------------------*/
/* FUN_0034f030 @ 0x0034f030   (est. sk_print_err_dstr)
 * Ghidra: 
 * Low confidence. Notes: string DAT_005d021c
 */
void sk_print_err_dstr(void)
{
    sk_print_err((und8_t *)0x005d021c, 1, 1);  /* FUN_001a89a8(&DAT_005d021c,1,1) */
}


/*--------------------------------------------------------------------*/
/* FUN_0034f044 @ 0x0034f044   (est. sk_obj_flag_call)
 * Ghidra: 
 * Medium confidence. Notes: indirect jumptable call FUN_000839f8
 */
void sk_obj_flag_call(und4_t param_1)
{
    sk_obj_vtbl_call((und8_t)param_1, (und8_t)1, (und8_t)0);  /* FUN_000839f8(param_1,1) */
}


/*--------------------------------------------------------------------*/
/* FUN_0034f064 @ 0x0034f064   (est. sk_sys_stub_f064)
 * Ghidra: void FUN_0034f064(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_f064(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f078 @ 0x0034f078   (est. sk_sys_stub_f078)
 * Ghidra: void FUN_0034f078(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_f078(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f088 @ 0x0034f088   (est. sk_swift_err_build_2f)
 * Ghidra: 
 * Low confidence. Notes: DAT refs 0x6773c0/0x5cebd0, kind 0x2f
 */
void sk_swift_err_build_2f(und8_t param_1)
{
    /* Build a Swift error record at the frame register (unaff_x24). */
    und8_t *f = (und8_t *)0x0;   /* unaff_x24 */
    ((und8_t **)f)[0] = (und8_t *)0x6773c0;        /* type metadata */
    ((und8_t **)f)[1] = (und8_t *)param_1;                   /* payload */
    ((und8_t **)f)[2] = (und8_t *)0xd00000000000002f; /* error kind */
    ((und8_t **)f)[3] = (und8_t *)0x80000000005cebd0; /* string ref */
    ((und8_t **)f)[4] = (und8_t *)0;
    *(und1_t *)((und8_t *)f + 9 * 8) = 0;
    sk_runtime_ping();  /* FUN_0036986c */
}


/*--------------------------------------------------------------------*/
/* FUN_0034f0c0 @ 0x0034f0c0   (est. sk_swift_err_build_2e)
 * Ghidra: 
 * Low confidence. Notes: DAT refs 0x676ed0/0x5ceba0, kind 0x2e
 */
void sk_swift_err_build_2e(und8_t param_1)
{
    und8_t *f = (und8_t *)0x0;   /* unaff_x24 */
    ((und8_t **)f)[0] = (und8_t *)0x676ed0;
    ((und8_t **)f)[1] = (und8_t *)param_1;
    ((und8_t **)f)[2] = (und8_t *)0xd00000000000002e;
    ((und8_t **)f)[3] = (und8_t *)0x80000000005ceba0;
    ((und8_t **)f)[4] = (und8_t *)0;
    *(und1_t *)((und8_t *)f + 9 * 8) = 0;
    sk_runtime_ping();  /* FUN_0036986c */
}


/*--------------------------------------------------------------------*/
/* FUN_0034f114 @ 0x0034f114   (est. sk_runtime_req_29)
 * Ghidra: 
 * Low confidence. Notes: calls FUN_002a4c98
 */
void sk_runtime_req_29(void)
{
    sk_runtime_req(0x29, 0xe100000000000000ULL, 0, 1);  /* FUN_002a4c98 */
}


/*--------------------------------------------------------------------*/
/* FUN_0034f138 @ 0x0034f138   (est. sk_obj_twin_call)
 * Ghidra: 
 * Low confidence. Notes: FUN_000839f8 x2; unaff regs
 */
void sk_obj_twin_call(long param_1)
{
    /* unaff_x19/x20 masked by ~unaff_x23: two indirect dispatches. */
    sk_obj_vtbl_call((und8_t)((param_1 + 0) & (0 ^ 0xffffffffffffffffULL)), (und8_t)1, (und8_t)0);
    sk_obj_vtbl_call((und8_t)((param_1 + 0) & (0 ^ 0xffffffffffffffffULL)), (und8_t)1, (und8_t)0);
}


/*--------------------------------------------------------------------*/
/* FUN_0034f174 @ 0x0034f174   (est. sk_obj_iv32_fini)
 * Ghidra: 
 * Low confidence. Notes: calls FUN_00310a74 + FUN_0001df60
 */
void sk_obj_iv32_fini(und8_t param_1)
{
    *(und8_t *)((long)0 - 0x60) = param_1;   /* unaff_x29 frame store */
    sk_obj_iv32_get(0);  /* FUN_00310a74 */
    sk_runtime_fini();   /* FUN_0001df60 */
}


/*--------------------------------------------------------------------*/
/* FUN_0034f198 @ 0x0034f198   (est. sk_sys_stub_f198)
 * Ghidra: void FUN_0034f198(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_f198(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f1a8 @ 0x0034f1a8   (est. sk_obj_method_dispatch_call)
 * Ghidra: 
 * Medium confidence. Notes: calls FUN_0006a4c0
 */
void sk_obj_method_dispatch_call(void)
{
    sk_obj_method_dispatch(0, 0);  /* FUN_0006a4c0 */
}


/*--------------------------------------------------------------------*/
/* FUN_0034f1c4 @ 0x0034f1c4   (est. sk_obj_iv4_call)
 * Ghidra: 
 * Medium confidence. Notes: calls FUN_0014ae44
 */
void sk_obj_iv4_call(void)
{
    sk_obj_iv4_get(0);  /* FUN_0014ae44 */
}


/*--------------------------------------------------------------------*/
/* FUN_0034f1e0 @ 0x0034f1e0   (est. sk_obj_iv20_call)
 * Ghidra: 
 * Medium confidence. Notes: calls FUN_000277b8
 */
void sk_obj_iv20_call(void)
{
    sk_obj_iv20_get(0);  /* FUN_000277b8 */
}


/*--------------------------------------------------------------------*/
/* FUN_0034f1fc @ 0x0034f1fc   (est. sk_sys_stub_f1fc)
 * Ghidra: void FUN_0034f1fc(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_f1fc(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f20c @ 0x0034f20c   (est. sk_store_short_byte)
 * Ghidra: 
 * Low confidence. Notes: unaff regs
 */
void sk_store_short_byte(und4_t field)
{
    *(volatile und2_t *)0 = (und2_t)(unsigned short)(unsigned)field;  /* unaff_x19 */
    *(volatile und1_t *)(0 + 1) = (und1_t)(((unsigned)field >> 0x10) & 0xff);
}


/*--------------------------------------------------------------------*/
/* FUN_0034f21c @ 0x0034f21c   (est. sk_sys_stub_f21c)
 * Ghidra: void FUN_0034f21c(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_f21c(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f22c @ 0x0034f22c   (est. sk_copy_pair_load)
 * Ghidra: 
 * Low confidence. Notes: copies 16B pair; in_x9
 */
und8_t sk_copy_pair_load(und8_t *param_1)
{
    und8_t hi = param_1[1];
    und8_t lo = param_1[0];
    ((und8_t **)0)[1] = (und8_t *)param_1[1];  /* in_x9 */
    ((und8_t **)0)[0] = (und8_t *)lo;
    return hi;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f23c @ 0x0034f23c   (est. sk_save_args)
 * Ghidra: 
 * Low confidence. Notes: in_x5 / unaff_x21 / unaff_x29
 */
void sk_save_args(und4_t param_1)
{
    *(und8_t *)((long)0 - 0x48) = (und8_t)0;   /* in_x5 */
    *(und8_t *)((long)0 - 0x58) = (und8_t)0;   /* unaff_x21 */
    *(und4_t *)((long)0 - 0x5c) = param_1;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f264 @ 0x0034f264   (est. sk_sys_stub_f264)
 * Ghidra: void FUN_0034f264(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_f264(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f274 @ 0x0034f274   (est. sk_sys_stub_f274)
 * Ghidra: void FUN_0034f274(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_f274(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f284 @ 0x0034f284   (est. sk_sys_stub_f284)
 * Ghidra: void FUN_0034f284(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_f284(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f294 @ 0x0034f294   (est. sk_sys_stub_f294)
 * Ghidra: void FUN_0034f294(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_f294(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f2a4 @ 0x0034f2a4   (est. sk_sys_stub_f2a4)
 * Ghidra: void FUN_0034f2a4(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_f2a4(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f2b4 @ 0x0034f2b4   (est. sk_sys_stub_f2b4)
 * Ghidra: void FUN_0034f2b4(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_f2b4(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f2c4 @ 0x0034f2c4   (est. sk_sys_stub_f2c4)
 * Ghidra: void FUN_0034f2c4(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_f2c4(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f2d4 @ 0x0034f2d4   (est. sk_sys_stub_f2d4)
 * Ghidra: void FUN_0034f2d4(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_f2d4(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f2e4 @ 0x0034f2e4   (est. sk_set_msb_flag)
 * Ghidra: 
 * Low confidence. Notes: unaff_x19
 */
void sk_set_msb_flag(void)
{
    *(volatile und8_t *)0 = 0x8000000000000000ULL;  /* unaff_x19 */
}


/*--------------------------------------------------------------------*/
/* FUN_0034f2f4 @ 0x0034f2f4   (est. sk_copy_word)
 * Ghidra: 
 * High confidence. Notes: 
 */
void sk_copy_word(und8_t *param_1, und8_t *param_2)
{
    *param_1 = *param_2;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f304 @ 0x0034f304   (est. sk_sys_stub_f304)
 * Ghidra: void FUN_0034f304(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_f304(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f314 @ 0x0034f314   (est. sk_sys_stub_f314)
 * Ghidra: void FUN_0034f314(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_f314(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f324 @ 0x0034f324   (est. sk_sys_stub_f324)
 * Ghidra: void FUN_0034f324(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_f324(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f334 @ 0x0034f334   (est. sk_sys_stub_f334)
 * Ghidra: void FUN_0034f334(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_f334(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f344 @ 0x0034f344   (est. sk_sys_stub_f344)
 * Ghidra: void FUN_0034f344(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_f344(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f354 @ 0x0034f354   (est. sk_sys_stub_f354)
 * Ghidra: void FUN_0034f354(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_f354(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f364 @ 0x0034f364   (est. sk_sys_stub_f364)
 * Ghidra: void FUN_0034f364(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_f364(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f374 @ 0x0034f374   (est. sk_sys_stub_f374)
 * Ghidra: void FUN_0034f374(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_f374(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f384 @ 0x0034f384   (est. sk_sys_stub_f384)
 * Ghidra: void FUN_0034f384(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_f384(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f394 @ 0x0034f394   (est. sk_sys_stub_f394)
 * Ghidra: void FUN_0034f394(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_f394(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f3a4 @ 0x0034f3a4   (est. sk_sys_stub_f3a4)
 * Ghidra: void FUN_0034f3a4(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_f3a4(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f3b4 @ 0x0034f3b4   (est. sk_sys_stub_f3b4)
 * Ghidra: void FUN_0034f3b4(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_f3b4(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f3c4 @ 0x0034f3c4   (est. sk_sub_ptr_58)
 * Ghidra: 
 * Low confidence. Notes: in_x9
 */
void sk_sub_ptr_58(long param_1)
{
    *(long *)((long)0 - 0x58) = (long)0 - param_1;  /* in_x9 - param_1 */
}


/*--------------------------------------------------------------------*/
/* FUN_0034f3d4 @ 0x0034f3d4   (est. sk_sub_ptr_a8)
 * Ghidra: 
 * Low confidence. Notes: in_x9
 */
void sk_sub_ptr_a8(long param_1)
{
    *(long *)((long)0 - 0xa8) = (long)0 - param_1;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f3e4 @ 0x0034f3e4   (est. sk_sys_stub_f3e4)
 * Ghidra: void FUN_0034f3e4(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_f3e4(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f3f4 @ 0x0034f3f4   (est. sk_sys_stub_f3f4)
 * Ghidra: void FUN_0034f3f4(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_f3f4(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f404 @ 0x0034f404   (est. sk_sys_stub_f404)
 * Ghidra: void FUN_0034f404(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_f404(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f414 @ 0x0034f414   (est. sk_sys_stub_f414)
 * Ghidra: void FUN_0034f414(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_f414(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f424 @ 0x0034f424   (est. sk_sys_stub_f424)
 * Ghidra: void FUN_0034f424(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_f424(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f434 @ 0x0034f434   (est. sk_sys_stub_f434)
 * Ghidra: void FUN_0034f434(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_f434(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f444 @ 0x0034f444   (est. sk_sys_stub_f444)
 * Ghidra: void FUN_0034f444(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_f444(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f454 @ 0x0034f454   (est. sk_sys_stub_f454)
 * Ghidra: void FUN_0034f454(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_f454(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f464 @ 0x0034f464   (est. sk_sys_stub_f464)
 * Ghidra: void FUN_0034f464(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_f464(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f474 @ 0x0034f474   (est. sk_sys_stub_f474)
 * Ghidra: void FUN_0034f474(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_f474(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f484 @ 0x0034f484   (est. sk_sys_stub_f484)
 * Ghidra: void FUN_0034f484(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_f484(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f494 @ 0x0034f494   (est. sk_sys_stub_f494)
 * Ghidra: void FUN_0034f494(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_f494(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f4a4 @ 0x0034f4a4   (est. sk_sys_stub_f4a4)
 * Ghidra: void FUN_0034f4a4(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_f4a4(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f4b4 @ 0x0034f4b4   (est. sk_sys_stub_f4b4)
 * Ghidra: void FUN_0034f4b4(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_f4b4(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f4c4 @ 0x0034f4c4   (est. sk_sys_stub_f4c4)
 * Ghidra: void FUN_0034f4c4(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_f4c4(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f4d4 @ 0x0034f4d4   (est. sk_sys_stub_f4d4)
 * Ghidra: void FUN_0034f4d4(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_f4d4(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f4e4 @ 0x0034f4e4   (est. sk_sys_stub_f4e4)
 * Ghidra: void FUN_0034f4e4(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_f4e4(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f4f4 @ 0x0034f4f4   (est. sk_sys_stub_f4f4)
 * Ghidra: void FUN_0034f4f4(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_f4f4(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f504 @ 0x0034f504   (est. sk_sys_stub_f504)
 * Ghidra: void FUN_0034f504(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_f504(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f514 @ 0x0034f514   (est. sk_sys_stub_f514)
 * Ghidra: void FUN_0034f514(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_f514(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f524 @ 0x0034f524   (est. sk_sys_stub_f524)
 * Ghidra: void FUN_0034f524(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_f524(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f534 @ 0x0034f534   (est. sk_sys_stub_f534)
 * Ghidra: void FUN_0034f534(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_f534(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f544 @ 0x0034f544   (est. sk_sys_stub_f544)
 * Ghidra: void FUN_0034f544(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_f544(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f554 @ 0x0034f554   (est. sk_any_pair_word)
 * Ghidra: undefined1 [16]
 * Medium confidence. Notes: 16B pair {param_1,0}
 */
sk_any_pair_t sk_any_pair_word(uint64_t param_1)
{
    sk_any_pair_t r;
    r.lo = (und8_t)param_1;
    r.hi = 0;
    return r;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f564 @ 0x0034f564   (est. sk_sys_stub_f564)
 * Ghidra: void FUN_0034f564(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_f564(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f574 @ 0x0034f574   (est. sk_sys_stub_f574)
 * Ghidra: void FUN_0034f574(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_f574(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f584 @ 0x0034f584   (est. sk_sys_stub_f584)
 * Ghidra: void FUN_0034f584(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_f584(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f594 @ 0x0034f594   (est. sk_sys_stub_f594)
 * Ghidra: void FUN_0034f594(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_f594(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f5a4 @ 0x0034f5a4   (est. sk_sys_stub_f5a4)
 * Ghidra: void FUN_0034f5a4(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_f5a4(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f5b4 @ 0x0034f5b4   (est. sk_sys_stub_f5b4)
 * Ghidra: void FUN_0034f5b4(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_f5b4(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f5c4 @ 0x0034f5c4   (est. sk_ret0_77)
 * Ghidra: 
 * High confidence. Notes: 
 */
und8_t sk_ret0_77(void)
{
    return 0;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f5d4 @ 0x0034f5d4   (est. sk_sys_stub_f5d4)
 * Ghidra: void FUN_0034f5d4(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_f5d4(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f5e4 @ 0x0034f5e4   (est. sk_ret0_79)
 * Ghidra: 
 * High confidence. Notes: 
 */
und8_t sk_ret0_79(void)
{
    return 0;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f5f4 @ 0x0034f5f4   (est. sk_ret0_80)
 * Ghidra: 
 * High confidence. Notes: 
 */
und8_t sk_ret0_80(void)
{
    return 0;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f604 @ 0x0034f604   (est. sk_ret0_81)
 * Ghidra: 
 * High confidence. Notes: 
 */
und8_t sk_ret0_81(void)
{
    return 0;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f614 @ 0x0034f614   (est. sk_ret0_82)
 * Ghidra: 
 * High confidence. Notes: 
 */
und8_t sk_ret0_82(void)
{
    return 0;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f624 @ 0x0034f624   (est. sk_any_pair_word_83)
 * Ghidra: undefined1 [16]
 * Medium confidence. Notes: 16B pair {param_1,0}
 */
sk_any_pair_t sk_any_pair_word_83(uint64_t param_1)
{
    sk_any_pair_t r;
    r.lo = (und8_t)param_1;
    r.hi = 0;
    return r;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f634 @ 0x0034f634   (est. sk_sys_stub_f634)
 * Ghidra: void FUN_0034f634(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_f634(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f644 @ 0x0034f644   (est. sk_sys_stub_f644)
 * Ghidra: void FUN_0034f644(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_f644(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f654 @ 0x0034f654   (est. sk_sys_stub_f654)
 * Ghidra: void FUN_0034f654(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_f654(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f664 @ 0x0034f664   (est. sk_return_second)
 * Ghidra: 
 * High confidence. Notes: 
 */
und8_t sk_return_second(und8_t param_1, und8_t param_2)
{
    (void)param_1;
    return param_2;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f674 @ 0x0034f674   (est. sk_sys_stub_f674)
 * Ghidra: void FUN_0034f674(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_f674(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f688 @ 0x0034f688   (est. sk_sys_stub_f688)
 * Ghidra: void FUN_0034f688(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_f688(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f6a8 @ 0x0034f6a8   (est. sk_swift_fatal_grapheme)
 * Ghidra: 
 * Low confidence. Notes: strings 005accd0/005d3570; FUN_001afa84
 */
void sk_swift_fatal_grapheme(uint64_t param_1)
{
    /* noreturn Swift "Fatal error" (StringGraphemeBreaking). */
    sk_swift_fatal((und8_t *)0x005accd0, 0xb, 2, 0xd000000000000034ULL,
                   param_1 | 0x8000000000000000ULL,
                   (und8_t *)0x005d3570, 0x22, 2);
    for (;;) {}
}


/*--------------------------------------------------------------------*/
/* FUN_0034f6dc @ 0x0034f6dc   (est. sk_teardown_dat4eb948)
 * Ghidra: 
 * Low confidence. Notes: DAT_004eb948
 */
void sk_teardown_dat4eb948(void)
{
    sk_teardown_a((void *)0x004eb948);  /* FUN_00376820(&DAT_004eb948) */
}


/*--------------------------------------------------------------------*/
/* FUN_0034f6f8 @ 0x0034f6f8   (est. sk_teardown_dat4ead58)
 * Ghidra: 
 * Low confidence. Notes: DAT_004ead58
 */
void sk_teardown_dat4ead58(void)
{
    sk_teardown_a((void *)0x004ead58);  /* FUN_00376820(&DAT_004ead58) */
}


/*--------------------------------------------------------------------*/
/* FUN_0034f714 @ 0x0034f714   (est. sk_obj_method_dispatch_call2)
 * Ghidra: 
 * Medium confidence. Notes: 
 */
void sk_obj_method_dispatch_call2(void)
{
    sk_obj_method_dispatch(0, 0);  /* FUN_0006a4c0 */
}


/*--------------------------------------------------------------------*/
/* FUN_0034f730 @ 0x0034f730   (est. sk_sys_stub_f730)
 * Ghidra: void FUN_0034f730(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_f730(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f740 @ 0x0034f740   (est. sk_pair_ptr_flags)
 * Ghidra: undefined1 [16]
 * Low confidence. Notes: unaff_x19
 */
sk_any_pair_t sk_pair_ptr_flags(void)
{
    sk_any_pair_t r;
    r.lo = (und8_t)0;   /* &stack frame */
    r.hi = (und8_t)((uint64_t)0 >> 0x38 & 0xf);  /* unaff_x19 high nibble */
    return r;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f754 @ 0x0034f754   (est. sk_sys_stub_f754)
 * Ghidra: void FUN_0034f754(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_f754(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f764 @ 0x0034f764   (est. sk_ret0_97)
 * Ghidra: 
 * High confidence. Notes: 
 */
und8_t sk_ret0_97(void)
{
    return 0;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f778 @ 0x0034f778   (est. sk_sys_stub_f778)
 * Ghidra: void FUN_0034f778(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_f778(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f788 @ 0x0034f788   (est. sk_sys_stub_f788)
 * Ghidra: void FUN_0034f788(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_f788(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f798 @ 0x0034f798   (est. sk_sys_stub_f798)
 * Ghidra: void FUN_0034f798(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_f798(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f7b0 @ 0x0034f7b0   (est. sk_sys_stub_f7b0)
 * Ghidra: void FUN_0034f7b0(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_f7b0(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f7c0 @ 0x0034f7c0   (est. sk_sys_stub_f7c0)
 * Ghidra: void FUN_0034f7c0(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_f7c0(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f7d8 @ 0x0034f7d8   (est. sk_copy_pair_8)
 * Ghidra: 
 * High confidence. Notes: 
 */
void sk_copy_pair_8(long param_1, long param_2)
{
    *(und8_t *)(param_1 + 8) = *(und8_t *)(param_2 + 8);
    *(und8_t *)(param_1 + 0x10) = *(und8_t *)(param_2 + 0x10);
}


/*--------------------------------------------------------------------*/
/* FUN_0034f7ec @ 0x0034f7ec   (est. sk_store_alloc)
 * Ghidra: 
 * Low confidence. Notes: DAT_0x66aa10
 */
void sk_store_alloc(und8_t param_1, und8_t param_2, long param_3)
{
    *(und8_t *)(param_3 + 0x18) = param_1;
    (void)param_2;
    sk_alloc_tag(0x66aa10, 0x20, 0xf);  /* FUN_0036a940 */
}


/*--------------------------------------------------------------------*/
/* FUN_0034f804 @ 0x0034f804   (est. sk_sys_stub_f804)
 * Ghidra: void FUN_0034f804(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_f804(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f818 @ 0x0034f818   (est. sk_sys_stub_f818)
 * Ghidra: void FUN_0034f818(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_f818(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f828 @ 0x0034f828   (est. sk_pair_masked)
 * Ghidra: undefined1 [16]
 * Low confidence. Notes: unaff regs
 */
sk_any_pair_t sk_pair_masked(void)
{
    sk_any_pair_t r;
    r.lo = (und8_t)((uint64_t)0 & (0 ^ 0xffffffffffffffffULL));  /* unaff_x24 & ~x23 */
    r.hi = (und8_t)((uint64_t)0 & (0 ^ 0xffffffffffffffffULL));  /* unaff_x25 & ~x23 */
    return r;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f838 @ 0x0034f838   (est. sk_sys_stub_f838)
 * Ghidra: void FUN_0034f838(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_f838(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f84c @ 0x0034f84c   (est. sk_sys_stub_f84c)
 * Ghidra: void FUN_0034f84c(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_f84c(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f860 @ 0x0034f860   (est. sk_ret0_110)
 * Ghidra: 
 * High confidence. Notes: 
 */
und8_t sk_ret0_110(void)
{
    return 0;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f874 @ 0x0034f874   (est. sk_sys_stub_f874)
 * Ghidra: void FUN_0034f874(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_f874(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f884 @ 0x0034f884   (est. sk_sys_stub_f884)
 * Ghidra: void FUN_0034f884(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_f884(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f8a8 @ 0x0034f8a8   (est. sk_const_66a9e8)
 * Ghidra: undefined1 [16]
 * Medium confidence. Notes: const pair
 */
sk_any_pair_t sk_const_66a9e8(void)
{
    sk_any_pair_t r;
    r.lo = (und8_t)0x66a9e8;
    r.hi = (und8_t)0x29;
    return r;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f8bc @ 0x0034f8bc   (est. sk_const_656250)
 * Ghidra: undefined1 [16]
 * Medium confidence. Notes: const pair
 */
sk_any_pair_t sk_const_656250(void)
{
    sk_any_pair_t r;
    r.lo = (und8_t)0x656250;
    r.hi = (und8_t)0x4e80a8;
    return r;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f8d0 @ 0x0034f8d0   (est. sk_ret0_115)
 * Ghidra: 
 * High confidence. Notes: 
 */
und8_t sk_ret0_115(void)
{
    return 0;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f8e4 @ 0x0034f8e4   (est. sk_sys_stub_f8e4)
 * Ghidra: void FUN_0034f8e4(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_f8e4(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f8f4 @ 0x0034f8f4   (est. sk_copy_byte_masked)
 * Ghidra: 
 * Low confidence. Notes: unaff regs
 */
void sk_copy_byte_masked(void)
{
    long off = ((uint64_t)0 & (0 ^ 0xffffffffffffffffULL)) + 0;  /* unaff regs */
    *(und1_t *)(0 + off) = *(und1_t *)(0 + off);  /* x22 <- x23 */
}


/*--------------------------------------------------------------------*/
/* FUN_0034f90c @ 0x0034f90c   (est. sk_return_stack16)
 * Ghidra: 
 * Low confidence. Notes: unaff_x29
 */
und8_t * sk_return_stack16(void)
{
    return (und8_t *)((long)0 + 0x10);  /* unaff_x29 + 0x10 */
}


/*--------------------------------------------------------------------*/
/* FUN_0034f924 @ 0x0034f924   (est. sk_sys_stub_f924)
 * Ghidra: void FUN_0034f924(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_f924(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f938 @ 0x0034f938   (est. sk_save_2regs)
 * Ghidra: 
 * Low confidence. Notes: unaff regs
 */
void sk_save_2regs(void)
{
    *(und8_t *)((long)0 - 0x78) = (und8_t)0;  /* unaff_x19 */
    *(und8_t *)((long)0 - 0x70) = (und8_t)0;  /* unaff_x20 */
}


/*--------------------------------------------------------------------*/
/* FUN_0034f948 @ 0x0034f948   (est. sk_init_slot)
 * Ghidra: 
 * Low confidence. Notes: unaff regs
 */
void sk_init_slot(void)
{
    *(und8_t *)(0 + 0x10) = (und8_t)0;  /* unaff_x23+0x10 = x19 */
    *(und8_t *)(0 + 0x18) = 0;
    *(und1_t *)(0 + 0x48) = 3;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f958 @ 0x0034f958   (est. sk_print_cannot_init)
 * Ghidra: 
 * Low confidence. Notes: string 005ce9b0
 */
void sk_print_cannot_init(void)
{
    sk_print_err((und8_t *)0x005ce9b0, 0x12, 1);  /* FUN_001a89a8 "Cannot initialize" */
}


/*--------------------------------------------------------------------*/
/* FUN_0034f96c @ 0x0034f96c   (est. sk_pair_stack)
 * Ghidra: undefined1 [16]
 * Low confidence. Notes: in_stack_00000020
 */
sk_any_pair_t sk_pair_stack(void)
{
    sk_any_pair_t r;
    r.lo = (und8_t)0;             /* &stack frame */
    r.hi = (und8_t)0;             /* in_stack_00000020 */
    return r;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f97c @ 0x0034f97c   (est. sk_sys_stub_f97c)
 * Ghidra: void FUN_0034f97c(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_f97c(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f98c @ 0x0034f98c   (est. sk_sys_stub_f98c)
 * Ghidra: void FUN_0034f98c(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_f98c(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f99c @ 0x0034f99c   (est. sk_sys_stub_f99c)
 * Ghidra: void FUN_0034f99c(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_f99c(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f9b4 @ 0x0034f9b4   (est. sk_boot_reg_call)
 * Ghidra: 
 * Low confidence. Notes: DAT_004e7ed0
 */
void sk_boot_reg_call(void)
{
    sk_boot_reg((und8_t *)0x6560e8, (void *)0x004e7ed0);  /* FUN_00002534 */
}


/*--------------------------------------------------------------------*/
/* FUN_0034f9c8 @ 0x0034f9c8   (est. sk_sys_stub_f9c8)
 * Ghidra: void FUN_0034f9c8(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_f9c8(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f9d8 @ 0x0034f9d8   (est. sk_load_frame_118)
 * Ghidra: 
 * Low confidence. Notes: 
 */
und8_t sk_load_frame_118(void)
{
    return *(und8_t *)((long)0 - 0x118);  /* unaff_x29 */
}


/*--------------------------------------------------------------------*/
/* FUN_0034f9ec @ 0x0034f9ec   (est. sk_sys_stub_f9ec)
 * Ghidra: void FUN_0034f9ec(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_f9ec(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034f9fc @ 0x0034f9fc   (est. sk_sys_stub_f9fc)
 * Ghidra: void FUN_0034f9fc(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_f9fc(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034fa0c @ 0x0034fa0c   (est. sk_copy_word_to_x9)
 * Ghidra: 
 * Low confidence. Notes: in_x9
 */
void sk_copy_word_to_x9(und8_t *param_1)
{
    *(volatile und8_t *)0 = *param_1;  /* in_x9 */
}


/*--------------------------------------------------------------------*/
/* FUN_0034fa1c @ 0x0034fa1c   (est. sk_load_frame_a8)
 * Ghidra: 
 * Low confidence. Notes: 
 */
und8_t sk_load_frame_a8(void)
{
    return *(und8_t *)((long)0 - 0xa8);
}


/*--------------------------------------------------------------------*/
/* FUN_0034fa34 @ 0x0034fa34   (est. sk_ret0_134)
 * Ghidra: 
 * High confidence. Notes: 
 */
und8_t sk_ret0_134(void)
{
    return 0;
}


/*--------------------------------------------------------------------*/
/* FUN_0034fa4c @ 0x0034fa4c   (est. sk_sys_stub_fa4c)
 * Ghidra: void FUN_0034fa4c(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_fa4c(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034fa78 @ 0x0034fa78   (est. sk_bit_clear_indexed)
 * Ghidra: 
 * Low confidence. Notes: bit clear
 */
void sk_bit_clear_indexed(void)
{
    uint64_t off = (uint64_t)0 >> 3 & 0x1ffffffffffffff8ULL;  /* unaff_x21 */
    *(uint64_t *)(0 + off) &= ~((1UL << ((uint64_t)0 & 0x3f)) - 1);  /* unaff_x19 */
}


/*--------------------------------------------------------------------*/
/* FUN_0034fa9c @ 0x0034fa9c   (est. sk_swift_precondition)
 * Ghidra: 
 * Low confidence. Notes: strings 005ce2d0/005d33c0
 */
void sk_swift_precondition(und8_t param_1)
{
    (void)param_1;
    /* noreturn Swift precondition failure. */
    sk_swift_fatal((und8_t *)0x005ce2d0, 0x13, 2, 0, 0xe000000000000000ULL,
                   (und8_t *)0x005d33c0, 0x21, 2);
    for (;;) {}
}


/*--------------------------------------------------------------------*/
/* FUN_0034facc @ 0x0034facc   (est. sk_sys_stub_facc)
 * Ghidra: void FUN_0034facc(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_facc(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034fadc @ 0x0034fadc   (est. sk_runtime_log)
 * Ghidra: 
 * Low confidence. Notes: DAT_0x678ff0
 */
void sk_runtime_log(void)
{
    uint64_t v = (uint64_t)sk_runtime_boot;  /* FUN_003246ec returns void; keep result as value */
    (void)v;
    sk_runtime_boot(0xff);
    sk_runtime_call(0, (und8_t)0, (und8_t)0);  /* FUN_003722e4(0, v, 0x678ff0, 0, 0) */
}


/*--------------------------------------------------------------------*/
/* FUN_0034fb14 @ 0x0034fb14   (est. sk_grow_capacity)
 * Ghidra: 
 * Low confidence. Notes: unaff_x20
 */
void sk_grow_capacity(long param_1)
{
    long n = *(long *)(*(volatile long *)0 + 0x18);  /* unaff_x20 capacity */
    if (n <= param_1) n = param_1;
    sk_swift_grow(n);  /* FUN_001fab14 */
}


/*--------------------------------------------------------------------*/
/* FUN_0034fb28 @ 0x0034fb28   (est. sk_const_5d0ce6)
 * Ghidra: undefined1 [16]
 * Medium confidence. Notes: string ref DAT_005d0ce6
 */
sk_any_pair_t sk_const_5d0ce6(void)
{
    sk_any_pair_t r;
    r.lo = (und8_t)0x005d0ce6;
    r.hi = (und8_t)1;
    return r;
}


/*--------------------------------------------------------------------*/
/* FUN_0034fb3c @ 0x0034fb3c   (est. sk_sys_stub_fb3c)
 * Ghidra: void FUN_0034fb3c(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_fb3c(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034fb60 @ 0x0034fb60   (est. sk_sys_stub_fb60)
 * Ghidra: void FUN_0034fb60(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_fb60(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034fb74 @ 0x0034fb74   (est. sk_sys_stub_fb74)
 * Ghidra: void FUN_0034fb74(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_fb74(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034fb88 @ 0x0034fb88   (est. sk_sys_stub_fb88)
 * Ghidra: void FUN_0034fb88(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_fb88(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034fb9c @ 0x0034fb9c   (est. sk_sys_stub_fb9c)
 * Ghidra: void FUN_0034fb9c(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_fb9c(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034fbb0 @ 0x0034fbb0   (est. sk_pack_field)
 * Ghidra: 
 * Medium confidence. Notes: pack 6-bit + 5-bit
 */
und4_t sk_pack_field(long param_1, und4_t param_2)
{
    return (und4_t)(*(und1_t *)(param_1 + 1) & 0x3f) | (param_2 & 0x1f) << 6;
}


/*--------------------------------------------------------------------*/
/* FUN_0034fbc4 @ 0x0034fbc4   (est. sk_sys_stub_fbc4)
 * Ghidra: void FUN_0034fbc4(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_fbc4(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034fbd4 @ 0x0034fbd4   (est. sk_sys_stub_fbd4)
 * Ghidra: void FUN_0034fbd4(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_fbd4(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034fbe4 @ 0x0034fbe4   (est. sk_sys_stub_fbe4)
 * Ghidra: void FUN_0034fbe4(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_fbe4(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034fbf4 @ 0x0034fbf4   (est. sk_sys_stub_fbf4)
 * Ghidra: void FUN_0034fbf4(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_fbf4(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034fc34 @ 0x0034fc34   (est. sk_sys_stub_fc34)
 * Ghidra: void FUN_0034fc34(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_fc34(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034fc44 @ 0x0034fc44   (est. sk_const_656358)
 * Ghidra: undefined1 [16]
 * Medium confidence. Notes: const pair
 */
sk_any_pair_t sk_const_656358(void)
{
    sk_any_pair_t r;
    r.lo = (und8_t)0x656358;
    r.hi = (und8_t)0x4e8150;
    return r;
}


/*--------------------------------------------------------------------*/
/* FUN_0034fc58 @ 0x0034fc58   (est. sk_const_656360)
 * Ghidra: undefined1 [16]
 * Medium confidence. Notes: const pair
 */
sk_any_pair_t sk_const_656360(void)
{
    sk_any_pair_t r;
    r.lo = (und8_t)0x656360;
    r.hi = (und8_t)0x4e8158;
    return r;
}


/*--------------------------------------------------------------------*/
/* FUN_0034fc6c @ 0x0034fc6c   (est. sk_sys_stub_fc6c)
 * Ghidra: void FUN_0034fc6c(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_fc6c(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034fc7c @ 0x0034fc7c   (est. sk_sys_stub_fc7c)
 * Ghidra: void FUN_0034fc7c(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_fc7c(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034fc8c @ 0x0034fc8c   (est. sk_pair_3_4)
 * Ghidra: undefined1 [16]
 * High confidence. Notes: 
 */
sk_any_pair_t sk_pair_3_4(und8_t p1, und8_t p2, und8_t p3, und8_t p4)
{
    sk_any_pair_t r;
    r.lo = p3;
    r.hi = p4;
    (void)p1; (void)p2;
    return r;
}


/*--------------------------------------------------------------------*/
/* FUN_0034fc9c @ 0x0034fc9c   (est. sk_sys_stub_fc9c)
 * Ghidra: void FUN_0034fc9c(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_fc9c(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034fcac @ 0x0034fcac   (est. sk_sys_stub_fcac)
 * Ghidra: void FUN_0034fcac(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_fcac(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034fcc0 @ 0x0034fcc0   (est. sk_pair_677650)
 * Ghidra: undefined1 [16]
 * Low confidence. Notes: DAT_0x677650
 */
sk_any_pair_t sk_pair_677650(void)
{
    sk_any_pair_t r;
    r.lo = (und8_t)((long)0 - 0x5a);  /* unaff_x29 - 0x5a */
    r.hi = (und8_t)0x677650;
    return r;
}


/*--------------------------------------------------------------------*/
/* FUN_0034fce4 @ 0x0034fce4   (est. sk_ret0_161)
 * Ghidra: 
 * High confidence. Notes: 
 */
und8_t sk_ret0_161(void)
{
    return 0;
}


/*--------------------------------------------------------------------*/
/* FUN_0034fcf4 @ 0x0034fcf4   (est. sk_ret0_162)
 * Ghidra: 
 * High confidence. Notes: 
 */
und8_t sk_ret0_162(void)
{
    return 0;
}


/*--------------------------------------------------------------------*/
/* FUN_0034fd04 @ 0x0034fd04   (est. sk_sys_stub_fd04)
 * Ghidra: void FUN_0034fd04(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_fd04(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034fd14 @ 0x0034fd14   (est. sk_sys_stub_fd14)
 * Ghidra: void FUN_0034fd14(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_fd14(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034fd24 @ 0x0034fd24   (est. sk_sys_stub_fd24)
 * Ghidra: void FUN_0034fd24(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_fd24(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034fd3c @ 0x0034fd3c   (est. sk_sys_stub_fd3c)
 * Ghidra: void FUN_0034fd3c(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_fd3c(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034fd4c @ 0x0034fd4c   (est. sk_sys_stub_fd4c)
 * Ghidra: void FUN_0034fd4c(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_fd4c(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034fd5c @ 0x0034fd5c   (est. sk_sys_stub_fd5c)
 * Ghidra: void FUN_0034fd5c(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_fd5c(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034fd6c @ 0x0034fd6c   (est. sk_zero_frame)
 * Ghidra: 
 * Low confidence. Notes: zeroes 5 frame slots
 */
void sk_zero_frame(void)
{
    *(und8_t *)((long)0 - 0x90) = 0;
    *(und8_t *)((long)0 - 0xa8) = 0;
    *(und8_t *)((long)0 - 0xb0) = 0;
    *(und8_t *)((long)0 - 0x98) = 0;
    *(und8_t *)((long)0 - 0xa0) = 0;
}


/*--------------------------------------------------------------------*/
/* FUN_0034fd7c @ 0x0034fd7c   (est. sk_sys_stub_fd7c)
 * Ghidra: void FUN_0034fd7c(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_fd7c(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034fd8c @ 0x0034fd8c   (est. sk_sys_stub_fd8c)
 * Ghidra: void FUN_0034fd8c(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_fd8c(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034fd9c @ 0x0034fd9c   (est. sk_sys_stub_fd9c)
 * Ghidra: void FUN_0034fd9c(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_fd9c(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034fdac @ 0x0034fdac   (est. sk_sys_stub_fdac)
 * Ghidra: void FUN_0034fdac(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_fdac(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034fdbc @ 0x0034fdbc   (est. sk_sys_stub_fdbc)
 * Ghidra: void FUN_0034fdbc(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_fdbc(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034fdcc @ 0x0034fdcc   (est. sk_sub_ptr_138)
 * Ghidra: 
 * Low confidence. Notes: in_x9
 */
void sk_sub_ptr_138(long param_1)
{
    *(long *)((long)0 - 0x138) = (long)0 - param_1;  /* in_x9 */
}


/*--------------------------------------------------------------------*/
/* FUN_0034fde0 @ 0x0034fde0   (est. sk_sys_stub_fde0)
 * Ghidra: void FUN_0034fde0(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_fde0(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034fdf8 @ 0x0034fdf8   (est. sk_ret0_177)
 * Ghidra: 
 * High confidence. Notes: 
 */
und8_t sk_ret0_177(void)
{
    return 0;
}


/*--------------------------------------------------------------------*/
/* FUN_0034fe08 @ 0x0034fe08   (est. sk_pair_runtime_cur)
 * Ghidra: undefined1 [16]
 * Medium confidence. Notes: calls FUN_0008f6f4
 */
sk_any_pair_t sk_pair_runtime_cur(void)
{
    sk_any_pair_t r;
    uint64_t v = sk_runtime_cur();  /* FUN_0008f6f4 */
    r.lo = (und8_t)v;
    r.hi = 0;
    return r;
}


/*--------------------------------------------------------------------*/
/* FUN_0034fe28 @ 0x0034fe28   (est. sk_sys_stub_fe28)
 * Ghidra: void FUN_0034fe28(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_fe28(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034fe38 @ 0x0034fe38   (est. sk_sys_stub_fe38)
 * Ghidra: void FUN_0034fe38(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_fe38(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034fe48 @ 0x0034fe48   (est. sk_obj_iv40_call2)
 * Ghidra: 
 * Medium confidence. Notes: 
 */
void sk_obj_iv40_call2(void)
{
    sk_obj_iv40_get(0);  /* FUN_00310a44 */
}


/*--------------------------------------------------------------------*/
/* FUN_0034fe64 @ 0x0034fe64   (est. sk_obj_iv20_call2)
 * Ghidra: 
 * Medium confidence. Notes: 
 */
void sk_obj_iv20_call2(void)
{
    sk_obj_iv20_get(0);  /* FUN_000277b8 */
}


/*--------------------------------------------------------------------*/
/* FUN_0034fe80 @ 0x0034fe80   (est. sk_sys_stub_fe80)
 * Ghidra: void FUN_0034fe80(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_fe80(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034fe90 @ 0x0034fe90   (est. sk_sys_stub_fe90)
 * Ghidra: void FUN_0034fe90(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_fe90(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034fea0 @ 0x0034fea0   (est. sk_sys_stub_fea0)
 * Ghidra: void FUN_0034fea0(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_fea0(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034feb0 @ 0x0034feb0   (est. sk_sys_stub_feb0)
 * Ghidra: void FUN_0034feb0(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_feb0(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034fec0 @ 0x0034fec0   (est. sk_sys_stub_fec0)
 * Ghidra: void FUN_0034fec0(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_fec0(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034fed0 @ 0x0034fed0   (est. sk_sys_stub_fed0)
 * Ghidra: void FUN_0034fed0(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_fed0(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034fee0 @ 0x0034fee0   (est. sk_sys_stub_fee0)
 * Ghidra: void FUN_0034fee0(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_fee0(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034fef4 @ 0x0034fef4   (est. sk_store_frame_38)
 * Ghidra: 
 * Low confidence. Notes: 
 */
void sk_store_frame_38(und8_t param_1)
{
    *(und8_t *)((long)0 - 0x38) = param_1;
}


/*--------------------------------------------------------------------*/
/* FUN_0034ff18 @ 0x0034ff18   (est. sk_store_ret_stack20)
 * Ghidra: 
 * Low confidence. Notes: 
 */
und8_t * sk_store_ret_stack20(und8_t param_1)
{
    *(und8_t *)((long)0 - 0x18) = param_1;
    return (und8_t *)0x20;  /* &stack0x20 */
}


/*--------------------------------------------------------------------*/
/* FUN_0034ff3c @ 0x0034ff3c   (est. sk_sys_stub_ff3c)
 * Ghidra: void FUN_0034ff3c(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_ff3c(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034ff4c @ 0x0034ff4c   (est. sk_obj_iv32_fini2)
 * Ghidra: 
 * Low confidence. Notes: 
 */
void sk_obj_iv32_fini2(void)
{
    *(und8_t *)((long)0 - 0x58) = (und8_t)0;  /* unaff_x19 */
    sk_obj_iv32_get(0);  /* FUN_00310a74 */
    *(und8_t *)((long)0 - 0x78) = (und8_t)0;  /* unaff_x22 */
    sk_runtime_fini();   /* FUN_0001df60 */
}


/*--------------------------------------------------------------------*/
/* FUN_0034ff78 @ 0x0034ff78   (est. sk_sys_stub_ff78)
 * Ghidra: void FUN_0034ff78(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_ff78(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034ff88 @ 0x0034ff88   (est. sk_sys_stub_ff88)
 * Ghidra: void FUN_0034ff88(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_ff88(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034ff98 @ 0x0034ff98   (est. sk_sys_stub_ff98)
 * Ghidra: void FUN_0034ff98(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_ff98(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034ffa8 @ 0x0034ffa8   (est. sk_sys_stub_ffa8)
 * Ghidra: void FUN_0034ffa8(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_ffa8(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034ffb8 @ 0x0034ffb8   (est. sk_sys_stub_ffb8)
 * Ghidra: void FUN_0034ffb8(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_ffb8(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_0034ffc8 @ 0x0034ffc8   (est. sk_stack_diff_d0)
 * Ghidra: 
 * Low confidence. Notes: in_x12
 */
void sk_stack_diff_d0(void)
{
    *(long *)((long)0 - 0xd0) = (long)0 - (long)0;  /* &stack - in_x12 */
}


/*--------------------------------------------------------------------*/
/* FUN_0034ffdc @ 0x0034ffdc   (est. sk_stack_diff_c0)
 * Ghidra: 
 * Low confidence. Notes: in_x12
 */
void sk_stack_diff_c0(void)
{
    *(long *)((long)0 - 0xc0) = (long)0 - (long)0;  /* &stack - in_x12 */
}


/*--------------------------------------------------------------------*/
/* FUN_0034fff0 @ 0x0034fff0   (est. sk_sys_stub_fff0)
 * Ghidra: void FUN_0034fff0(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_fff0(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_00350000 @ 0x00350000   (est. sk_sys_stub_0000)
 * Ghidra: void FUN_00350000(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_0000(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_00350018 @ 0x00350018   (est. sk_sys_stub_0018)
 * Ghidra: void FUN_00350018(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_0018(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_00350028 @ 0x00350028   (est. sk_sys_stub_0028)
 * Ghidra: void FUN_00350028(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_0028(void)
{
    return;
}


/*--------------------------------------------------------------------*/
/* FUN_00350038 @ 0x00350038   (est. sk_sys_stub_0038)
 * Ghidra: void FUN_00350038(void)
 * Empty syscall/exception-entry stub: does nothing and returns.
 * Confidence: high (decompiles to bare `return`).
 */
void sk_sys_stub_0038(void)
{
    return;
}
