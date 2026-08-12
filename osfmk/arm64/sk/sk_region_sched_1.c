/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel, GL1, arm64e, image
 * base 0) — the cL4 microkernel (cL4 (679.100.61)), seL4-derived. Ground truth: Ghidra FUN_ names
 * + addresses. All names are estimates unless string-matched.
 *
 * This file covers sub-range 0x190000-0x1a0000 (region 1). The region is the Swift runtime support
 * layer compiled into the kernel: collection / dictionary / string-interpolation helpers for the
 * "XnuUpcallsV2" Swift type (source file "XnuUpcallsV2/XnuUpcallsV2.swift"), with precondition
 * checks and fatal-error handling, plus a small number of lock / alloc / dispatch helpers. Names
 * use Swift-runtime and cL4 vocabulary; confidence low-medium unless a string matches.
 */

#include <stdbool.h>
#include <stdint.h>

/* Ghidra carry/borrow/concat idioms used in the decompiled bodies (kept faithful). */
#define SCARRY8(a, b)  (__builtin_add_overflow((a), (b), &(unsigned long){0}))
#define SBORROW8(a, b) (__builtin_sub_overflow((a), (b), &(unsigned long){0}))
#define CONCAT71(hi, lo) ((((unsigned long)(hi)) << 8) | ((unsigned long)(lo) & 0xff))
#define CONCAT44(hi, lo) ((((unsigned long)(hi)) << 32) | ((unsigned long)(lo) & 0xffffffff))
#define CONCAT31(hi, lo) ((((unsigned long)(hi)) << 8) | ((unsigned long)(lo) & 0xff))

/* ZEXT816 = zero-extend 16-bit to 64-bit */
#define ZEXT816(x) ((unsigned long)(unsigned short)(x))

/* Ghidra decompiler models indirect calls through a "code *" function pointer (returns x0). */
typedef unsigned long (*code)();
typedef uint64_t undefined;

/* Out-of-range kernel / Swift-runtime helpers referenced by this region (FUN_ addr in comment).
 * Names are estimates from repeated call patterns; reconstructed by sibling SK range workers. */
extern void *sk_swift_frame_init(void *out, unsigned long size, unsigned long a, void *err_out); /* FUN_00025ebc */
extern void *sk_swift_string_begin(void *out);                        /* thunk_FUN_00024068 -> FUN_00024068 */
extern unsigned long sk_swift_type_hash(unsigned long hash);          /* FUN_00023208 */
extern void sk_swift_type_arg();                                      /* FUN_000231f0 */
extern void sk_swift_type_arg2();                                     /* FUN_00023318 */
extern void sk_swift_elem_append(unsigned char v);                    /* FUN_000230f8 */
extern void sk_swift_buf_ctx(void *out);                              /* FUN_00022c48 */
extern void sk_swift_error_build(void *out, void *in, void *err);     /* FUN_00025f44 */
extern void sk_swift_string_build();              /* FUN_000214b0 */
extern char sk_swift_result_check(void);                              /* FUN_000217e4 */
extern unsigned long sk_swift_result_value(void);                     /* FUN_00021904 */
extern unsigned long sk_swift_result_value2(void);                    /* FUN_00021738 */
extern unsigned long sk_swift_collection_op();                        /* FUN_000268d0 */
extern void sk_swift_retain();                                        /* FUN_003698b0 */
extern void sk_swift_release();                                       /* FUN_0036993c */
extern unsigned long sk_swift_err_code(unsigned long a);              /* FUN_00019aac */
extern long sk_swift_collection_count();                              /* FUN_00026754 */
extern unsigned long sk_swift_collection_init();                               /* FUN_000267d4 */
extern void sk_swift_epilogue(void);                                  /* FUN_00025704 */
extern void sk_swift_precond_1(unsigned long a);                      /* FUN_002a4ab4 */
extern void sk_swift_precond_2();                                     /* thunk_FUN_002acbb8 -> FUN_002acbb8 */
extern void *sk_swift_meta(unsigned long a);                          /* FUN_00027724 */
extern void sk_swift_abort_tail(unsigned long a);                     /* FUN_003a25d4 */
extern void sk_swift_fatal_error();                                        /* FUN_001afa84 */
extern void sk_swift_fatal_error_2();                             /* FUN_001afe4c */
extern const char sk_fatal_error_str[];   /* s_Fatal_error_005accd0 */
extern const char sk_xnu_upcalls_swift[]; /* s_XnuUpcallsV2_XnuUpcallsV2_Swift__005ccbc0 */
extern const char sk_index_oob_str[];     /* s_Index_out_of_bounds_005cdab0 */
extern const char sk_collection_swift[];  /* s_Swift_Collection_swift_005cdad0 */
extern unsigned long DAT_0066a0b0;
extern unsigned long DAT_0066a140;
extern unsigned long DAT_0065a688;
extern unsigned long DAT_0065a5e8;
extern unsigned long DAT_0066a708;
extern unsigned long DAT_00669c50;
extern unsigned long DAT_00669c90;
extern unsigned long FUN_0065a550;
extern unsigned long FUN_0066a720;
extern unsigned long sk_alloc_pages();  /* FUN_0036b270 */
extern void sk_free(void *ptr);  /* FUN_0036b118 */
extern unsigned long FUN_0018cb24();
extern void sk_lock_acquire(void);        /* FUN_00354a34 */
extern void sk_lock_release_simple(void); /* FUN_00356940 */
extern void *sk_lock_owner(void);         /* FUN_00351dc0 */
extern void sk_lock_notify();      /* FUN_00354ef8 */
extern void sk_lock_wait(void);           /* FUN_0035a158 */
extern void sk_memzero_string();   /* FUN_0006f768 */
extern void sk_lock_enter(void);          /* FUN_00354318 */
extern void sk_lock_exit(void);           /* FUN_0035a134 */
extern unsigned long *DAT_004e7990;       /* dispatch table base (register-indexed) */
extern unsigned long *DAT_004e79a8;
extern unsigned int *DAT_004e79c0;
extern code DAT_00658c00;
extern unsigned char DAT_006575c0;
extern unsigned char DAT_004f1950;
extern unsigned char DAT_00657718;
extern unsigned char DAT_004f2228;
extern const char s_UnsafeMutablePointer_deinitializ_005cd730[];
extern const char s_Swift_UnsafePointer_swift_005cd770[];
extern const char s_UnsafeMutablePointer_moveInitial_005cd790[];
extern const char s_Unexpectedly_found_nil_while_unw_005cd7d0[];
extern const char s_Unexpectedly_found_nil_while_imp_005cd810[];
extern const char s_invalid_Collection__count_differ_005cd8e0[];
extern const char s_Swift_ArrayBufferProtocol_swift_005d3ec0[];
extern const char s_UnsafeMutablePointer_initialize_w_005cd860[];
extern const char s_UnsafeMutablePointer_initialize_o_005cd8a0[];
extern const char s_Swift_ArrayShared_swift_005cd920[];
extern const char s_Index_out_of_range_005cd940[];
extern const char s_Swift_ContiguousArrayBuffer_swif_005cd960[];
extern const char s_Array_index_is_out_of_range_005cd9b0[];
extern const char s_Negative_Array_index_is_out_of_r_005cd9d0[];
extern const char s_Swift_Array_swift_005cd990[];
extern const char s_Negative_value_is_not_representa_005ce190[];
extern const char s_Swift_Integers_swift_005cd680[];
extern unsigned char DAT_00657778;
extern unsigned char DAT_004e7f08;
extern unsigned char DAT_001a1630;
extern unsigned char DAT_00346bc8;
extern unsigned char DAT_003471a0;
extern unsigned char DAT_0019f098;
extern unsigned char DAT_004e824c;
extern unsigned long stack_slot_c0;
extern void FUN_00356d20();
extern void FUN_001a07bc();
extern void FUN_001a0908();
extern void FUN_001a0ef0();
extern void FUN_001a0fa4();
extern unsigned long stack0xffffffffffffffc8;
extern unsigned char DAT_00611b24;
extern unsigned long LAB_00611b34;


/* Out-of-range helpers (FUN_ addr in comment). */
extern unsigned long FUN_000218a4(void);
extern unsigned char FUN_0018200c(void);
extern unsigned long FUN_0018b1e4(unsigned long, unsigned long);
extern unsigned long FUN_0018dd04();
extern void FUN_0018ddd8();
extern long FUN_00023c78(unsigned long);
extern long FUN_00023d00(unsigned long);
extern long FUN_000bd0e4(unsigned long);
extern void FUN_0018e38c();
extern long FUN_001477c4(unsigned long);
extern void FUN_0036b118();
extern void FUN_003488bc();
extern void FUN_001dc56c();
extern void FUN_001dc620();
extern void FUN_001da01c();
extern void FUN_0019f1ec();
extern void FUN_00357874();
extern unsigned long FUN_0005b140();
extern void FUN_001150e0();
extern const char s_integer_overflow_005bb5bd[];
extern unsigned long FUN_00023f74();
extern unsigned long FUN_0018c594();
extern unsigned char DAT_0000118f;
extern unsigned char DAT_00001197;
extern unsigned long *DAT_004e7a18;
extern unsigned int *DAT_004e79c0;
extern code DAT_00658c00;
extern unsigned char DAT_006575c0;
extern unsigned char DAT_004f1950;
extern unsigned char DAT_00657718;
extern unsigned char DAT_004f2228;
extern const char s_UnsafeMutablePointer_deinitializ_005cd730[];
extern const char s_Swift_UnsafePointer_swift_005cd770[];
extern const char s_UnsafeMutablePointer_moveInitial_005cd790[];
extern const char s_Unexpectedly_found_nil_while_unw_005cd7d0[];
extern const char s_Unexpectedly_found_nil_while_imp_005cd810[];
extern const char s_invalid_Collection__count_differ_005cd8e0[];
extern const char s_Swift_ArrayBufferProtocol_swift_005d3ec0[];
extern const char s_UnsafeMutablePointer_initialize_w_005cd860[];
extern const char s_UnsafeMutablePointer_initialize_o_005cd8a0[];
extern const char s_Swift_ArrayShared_swift_005cd920[];
extern const char s_Index_out_of_range_005cd940[];
extern const char s_Swift_ContiguousArrayBuffer_swif_005cd960[];
extern const char s_Array_index_is_out_of_range_005cd9b0[];
extern const char s_Negative_Array_index_is_out_of_r_005cd9d0[];
extern const char s_Swift_Array_swift_005cd990[];
extern const char s_Negative_value_is_not_representa_005ce190[];
extern const char s_Swift_Integers_swift_005cd680[];
extern unsigned char DAT_00657778;
extern unsigned char DAT_004e7f08;
extern unsigned char DAT_001a1630;
extern unsigned char DAT_00346bc8;
extern unsigned char DAT_003471a0;
extern unsigned char DAT_0019f098;
extern unsigned char DAT_004e824c;
extern unsigned long stack_slot_c0;
extern unsigned long stack0xffffffffffffffc8;
extern unsigned char DAT_00611b24;
extern unsigned long LAB_00611b34;



/* Compile-fix externs (forward decls for file-local defs + undeclared helpers; FUN_ addr in comment). */
extern void FUN_0019ea20();                       /* defined in this file @ 0x0019ea20 */
extern void FUN_0019f658();                       /* defined in this file @ 0x0019f658 */
extern void FUN_0019f698();                       /* defined in this file @ 0x0019f698 */
extern unsigned long FUN_0019f8e4(long *, unsigned long, unsigned long, long); /* defined in this file @ 0x0019f8e4 */
extern void FUN_0019fa60();                       /* defined in this file @ 0x0019fa60 */
extern void FUN_0019ff50();                       /* defined in this file @ 0x0019ff50 */
extern long sk_collection_underflow();            /* FUN_0019f9c4 caller */
extern void FUN_003580e4();
extern void FUN_0034c434();
extern void FUN_00348384();
extern unsigned char DAT_003471a4;
extern unsigned char DAT_003471a8;
extern unsigned char DAT_004e8214;


/* Out-of-range helpers referenced by bodies (old-style externs). */
extern unsigned long FUN_00002534();
extern unsigned long FUN_00019aac();
extern unsigned long FUN_0001a1c8();
extern unsigned long FUN_000214b0();
extern unsigned long FUN_00021738();
extern unsigned long FUN_000217e4();
extern unsigned long FUN_00021904();
extern unsigned long FUN_00022c48();
extern unsigned long FUN_000230f8();
extern unsigned long FUN_000231f0();
extern unsigned long FUN_00023208();
extern unsigned long FUN_00023318();
extern unsigned long FUN_00024068();
extern unsigned long FUN_00025704();
extern unsigned long FUN_00025ebc();
extern unsigned long FUN_00025f44();
extern unsigned long FUN_000262fc();
extern unsigned long FUN_00026754();
extern unsigned long FUN_000267d4();
extern unsigned long FUN_000268d0();
extern unsigned long FUN_00027724();
extern unsigned long FUN_00027754();
extern unsigned long FUN_00027788();
extern unsigned long FUN_000277b8();
extern unsigned long FUN_000277e8();
extern unsigned long FUN_00027818();
extern unsigned long FUN_00041138();
extern unsigned long FUN_0006b3f4();
extern unsigned long FUN_0006b42c();
extern unsigned long FUN_0006b6f4();
extern unsigned long FUN_0006f768();
extern unsigned long FUN_00077630();
extern unsigned long FUN_0007766c();
extern unsigned long FUN_000776cc();
extern unsigned long FUN_000776d8();
extern unsigned long FUN_00077708();
extern unsigned long FUN_0007791c();
extern unsigned long FUN_0007c028();
extern unsigned long FUN_0007c1a4();
extern unsigned long FUN_000839d8();
extern unsigned long FUN_0008409c();
extern unsigned long FUN_0008412c();
extern unsigned long FUN_00084180();
extern unsigned long FUN_00084220();
extern unsigned long FUN_00084234();
extern unsigned long FUN_0008e500();
extern unsigned long FUN_0008e518();
extern unsigned long FUN_0009e234();
extern unsigned long FUN_000a6e14();
extern unsigned long FUN_000a6f68();
extern unsigned long FUN_000a6f88();
extern unsigned long FUN_000bd3a4();
extern unsigned long FUN_000dbe70();
extern unsigned long FUN_000dbf08();
extern unsigned long FUN_000e15d8();
extern unsigned long FUN_000e72b0();
extern unsigned long FUN_000feb10();
extern unsigned long FUN_00100c38();
extern unsigned long FUN_00100efc();
extern unsigned long FUN_00117cc4();
extern unsigned long FUN_00117d14();
extern unsigned long FUN_0011aa70();
extern unsigned long FUN_001a0734();
extern unsigned long FUN_001a0754();
extern unsigned long FUN_001a0774();
extern unsigned long FUN_001a16e8();
extern unsigned long FUN_001a1894();
extern unsigned long FUN_001a26e0();
extern unsigned long FUN_001a894c();
extern unsigned long FUN_001afa84();
extern unsigned long FUN_001afe4c();
extern unsigned long FUN_001b89a4();
extern unsigned long FUN_001b8cf4();
extern unsigned long FUN_001da1c0();
extern unsigned long FUN_001da324();
extern unsigned long FUN_001dd614();
extern unsigned long FUN_001dd6ac();
extern unsigned long FUN_001e5438();
extern unsigned long FUN_001e6608();
extern unsigned long FUN_00243c60();
extern unsigned long FUN_002a4ab4();
extern unsigned long FUN_002acbb8();
extern unsigned long FUN_0031090c();
extern unsigned long FUN_00310924();
extern unsigned long FUN_00310984();
extern unsigned long FUN_003109e4();
extern unsigned long FUN_00310a14();
extern unsigned long FUN_00310a44();
extern unsigned long FUN_00310aa4();
extern unsigned long FUN_00310ad4();
extern unsigned long FUN_00310b08();
extern unsigned long FUN_00310b38();
extern unsigned long FUN_00310b68();
extern unsigned long FUN_00310b98();
extern unsigned long FUN_00310bc8();
extern unsigned long FUN_00310bf8();
extern unsigned long FUN_00310c44();
extern unsigned long FUN_00310c74();
extern unsigned long FUN_00310ca4();
extern unsigned long FUN_00310cd4();
extern unsigned long FUN_00310d04();
extern unsigned long FUN_00310d1c();
extern unsigned long FUN_00310d34();
extern unsigned long FUN_00310d4c();
extern unsigned long FUN_00310d68();
extern unsigned long FUN_00310d80();
extern unsigned long FUN_00310d98();
extern unsigned long FUN_00310da8();
extern unsigned long FUN_00310dd8();
extern unsigned long FUN_00310e08();
extern unsigned long FUN_00310e20();
extern unsigned long FUN_00310e50();
extern unsigned long FUN_00310e74();
extern unsigned long FUN_00310ea4();
extern unsigned long FUN_00310ed4();
extern unsigned long FUN_00310f04();
extern unsigned long FUN_00320fc8();
extern unsigned long FUN_00344d4c();
extern unsigned long FUN_00347d60();
extern unsigned long FUN_00347fb4();
extern unsigned long FUN_00348074();
extern unsigned long FUN_003480e4();
extern unsigned long FUN_00348304();
extern unsigned long FUN_0034834c();
extern unsigned long FUN_003485b8();
extern unsigned long FUN_00348718();
extern unsigned long FUN_003488f4();
extern unsigned long FUN_003489c0();
extern unsigned long FUN_00348a80();
extern unsigned long FUN_00348abc();
extern unsigned long FUN_00348b5c();
extern unsigned long FUN_00348b94();
extern unsigned long FUN_00348bbc();
extern unsigned long FUN_00348bd8();
extern unsigned long FUN_00348ce8();
extern unsigned long FUN_00348d30();
extern unsigned long FUN_00348d4c();
extern unsigned long FUN_00348e00();
extern unsigned long FUN_00348e18();
extern unsigned long FUN_00348e78();
extern unsigned long FUN_00348fd8();
extern unsigned long FUN_00349068();
extern unsigned long FUN_00349370();
extern unsigned long FUN_003493c4();
extern unsigned long FUN_003494b4();
extern unsigned long FUN_003494e8();
extern unsigned long FUN_00349530();
extern unsigned long FUN_00349618();
extern unsigned long FUN_00349684();
extern unsigned long FUN_00349748();
extern unsigned long FUN_003498dc();
extern unsigned long FUN_0034998c();
extern unsigned long FUN_003499f0();
extern unsigned long FUN_00349a18();
extern unsigned long FUN_00349b3c();
extern unsigned long FUN_00349db0();
extern unsigned long FUN_00349f5c();
extern unsigned long FUN_00349fcc();
extern unsigned long FUN_0034a198();
extern unsigned long FUN_0034a210();
extern unsigned long FUN_0034a2ac();
extern unsigned long FUN_0034a2f8();
extern unsigned long FUN_0034a368();
extern unsigned long FUN_0034a3d8();
extern unsigned long FUN_0034a74c();
extern unsigned long FUN_0034a760();
extern unsigned long FUN_0034a774();
extern unsigned long FUN_0034a944();
extern unsigned long FUN_0034a958();
extern unsigned long FUN_0034aa28();
extern unsigned long FUN_0034ab20();
extern unsigned long FUN_0034acd0();
extern unsigned long FUN_0034ad00();
extern unsigned long FUN_0034ae94();
extern unsigned long FUN_0034aebc();
extern unsigned long FUN_0034aee4();
extern unsigned long FUN_0034b07c();
extern unsigned long FUN_0034b0b4();
extern unsigned long FUN_0034b0c4();
extern unsigned long FUN_0034b164();
extern unsigned long FUN_0034b288();
extern unsigned long FUN_0034b368();
extern unsigned long FUN_0034b3d8();
extern unsigned long FUN_0034b3e8();
extern unsigned long FUN_0034b430();
extern unsigned long FUN_0034b4c0();
extern unsigned long FUN_0034b690();
extern unsigned long FUN_0034b804();
extern unsigned long FUN_0034b85c();
extern unsigned long FUN_0034b87c();
extern unsigned long FUN_0034b8dc();
extern unsigned long FUN_0034ba98();
extern unsigned long FUN_0034bc94();
extern unsigned long FUN_0034bcf0();
extern unsigned long FUN_0034bddc();
extern unsigned long FUN_0034bdfc();
extern unsigned long FUN_0034bec4();
extern unsigned long FUN_0034bf2c();
extern unsigned long FUN_0034c044();
extern unsigned long FUN_0034c084();
extern unsigned long FUN_0034c0d0();
extern unsigned long FUN_0034c234();
extern unsigned long FUN_0034c3f4();
extern unsigned long FUN_0034c444();
extern unsigned long FUN_0034c4fc();
extern unsigned long FUN_0034c7d4();
extern unsigned long FUN_0034ce28();
extern unsigned long FUN_0034cee8();
extern unsigned long FUN_0034cf64();
extern unsigned long FUN_0034cf84();
extern unsigned long FUN_0034cfa4();
extern unsigned long FUN_0034d2e4();
extern unsigned long FUN_0034d334();
extern unsigned long FUN_0034d344();
extern unsigned long FUN_0034d354();
extern unsigned long FUN_0034d374();
extern unsigned long FUN_0034d53c();
extern unsigned long FUN_0034d778();
extern unsigned long FUN_0034d8d4();
extern unsigned long FUN_0034da58();
extern unsigned long FUN_0034db08();
extern unsigned long FUN_0034db38();
extern unsigned long FUN_0034dc20();
extern unsigned long FUN_0034de64();
extern unsigned long FUN_0034df34();
extern unsigned long FUN_0034dff4();
extern unsigned long FUN_0034e064();
extern unsigned long FUN_0034e0d4();
extern unsigned long FUN_0034e15c();
extern unsigned long FUN_0034e1d0();
extern unsigned long FUN_0034e384();
extern unsigned long FUN_0034e3ac();
extern unsigned long FUN_0034e4dc();
extern unsigned long FUN_0034e52c();
extern unsigned long FUN_0034e54c();
extern unsigned long FUN_0034e63c();
extern unsigned long FUN_0034e72c();
extern unsigned long FUN_0034e9e8();
extern unsigned long FUN_0034ede8();
extern unsigned long FUN_0034ee08();
extern unsigned long FUN_0034ee98();
extern unsigned long FUN_0034ef18();
extern unsigned long FUN_0034ef68();
extern unsigned long FUN_0034ef78();
extern unsigned long FUN_0034f064();
extern unsigned long FUN_0034f424();
extern unsigned long FUN_0034f4b4();
extern unsigned long FUN_0034f4f4();
extern unsigned long FUN_0034f644();
extern unsigned long FUN_0034f664();
extern unsigned long FUN_0034fc8c();
extern unsigned long FUN_0034fde0();
extern unsigned long FUN_0034fe64();
extern unsigned long FUN_0034feb0();
extern unsigned long FUN_0034fec0();
extern unsigned long FUN_0034fed0();
extern unsigned long FUN_003501fc();
extern unsigned long FUN_003502a8();
extern unsigned long FUN_003503f8();
extern unsigned long FUN_00350410();
extern unsigned long FUN_00350428();
extern unsigned long FUN_00350464();
extern unsigned long FUN_00350470();
extern unsigned long FUN_00350488();
extern unsigned long FUN_00350494();
extern unsigned long FUN_003504a0();
extern unsigned long FUN_003504b8();
extern unsigned long FUN_003504c4();
extern unsigned long FUN_003504d0();
extern unsigned long FUN_003504e8();
extern unsigned long FUN_00350518();
extern unsigned long FUN_00350530();
extern unsigned long FUN_00350548();
extern unsigned long FUN_00350560();
extern unsigned long FUN_003505e8();
extern unsigned long FUN_0035060c();
extern unsigned long FUN_00350618();
extern unsigned long FUN_00350624();
extern unsigned long FUN_00350630();
extern unsigned long FUN_0035063c();
extern unsigned long FUN_003506cc();
extern unsigned long FUN_00350704();
extern unsigned long FUN_00350780();
extern unsigned long FUN_003507d4();
extern unsigned long FUN_003507e0();
extern unsigned long FUN_00350810();
extern unsigned long FUN_003508c0();
extern unsigned long FUN_003508cc();
extern unsigned long FUN_003508fc();
extern unsigned long FUN_00350944();
extern unsigned long FUN_00350968();
extern unsigned long FUN_00350974();
extern unsigned long FUN_0035098c();
extern unsigned long FUN_003509bc();
extern unsigned long FUN_003509d4();
extern unsigned long FUN_003509e0();
extern unsigned long FUN_00350a10();
extern unsigned long FUN_00350a34();
extern unsigned long FUN_00350a64();
extern unsigned long FUN_00350a7c();
extern unsigned long FUN_00350aa0();
extern unsigned long FUN_00350adc();
extern unsigned long FUN_00350b00();
extern unsigned long FUN_00350b24();
extern unsigned long FUN_00350b48();
extern unsigned long FUN_00350b54();
extern unsigned long FUN_00350b90();
extern unsigned long FUN_00350b9c();
extern unsigned long FUN_00350bcc();
extern unsigned long FUN_00350bf0();
extern unsigned long FUN_00350c50();
extern unsigned long FUN_00350db4();
extern unsigned long FUN_00350ea4();
extern unsigned long FUN_00351048();
extern unsigned long FUN_003510c4();
extern unsigned long FUN_003510dc();
extern unsigned long FUN_00351100();
extern unsigned long FUN_00351118();
extern unsigned long FUN_00351124();
extern unsigned long FUN_0035113c();
extern unsigned long FUN_00351184();
extern unsigned long FUN_00351190();
extern unsigned long FUN_003511b4();
extern unsigned long FUN_003511c0();
extern unsigned long FUN_003511d8();
extern unsigned long FUN_003512c0();
extern unsigned long FUN_003512cc();
extern unsigned long FUN_0035130c();
extern unsigned long FUN_00351360();
extern unsigned long FUN_00351384();
extern unsigned long FUN_003513b4();
extern unsigned long FUN_003513fc();
extern unsigned long FUN_00351420();
extern unsigned long FUN_0035145c();
extern unsigned long FUN_003514b8();
extern unsigned long FUN_0035156c();
extern unsigned long FUN_00351584();
extern unsigned long FUN_003515a8();
extern unsigned long FUN_003515e4();
extern unsigned long FUN_0035169c();
extern unsigned long FUN_003516cc();
extern unsigned long FUN_003516e4();
extern unsigned long FUN_003516fc();
extern unsigned long FUN_003518f4();
extern unsigned long FUN_00351978();
extern unsigned long FUN_00351a38();
extern unsigned long FUN_00351a44();
extern unsigned long FUN_00351a8c();
extern unsigned long FUN_00351be0();
extern unsigned long FUN_00351bec();
extern unsigned long FUN_00351c28();
extern unsigned long FUN_00351c70();
extern unsigned long FUN_00351d0c();
extern unsigned long FUN_00351d30();
extern unsigned long FUN_00351dc0();
extern unsigned long FUN_00351e20();
extern unsigned long FUN_00351e84();
extern unsigned long FUN_00351eb4();
extern unsigned long FUN_00351ec0();
extern unsigned long FUN_00351ee0();
extern unsigned long FUN_00351ef8();
extern unsigned long FUN_003521d4();
extern unsigned long FUN_003522c8();
extern unsigned long FUN_00352314();
extern unsigned long FUN_00352360();
extern unsigned long FUN_003523f0();
extern unsigned long FUN_00352498();
extern unsigned long FUN_0035272c();
extern unsigned long FUN_00352920();
extern unsigned long FUN_003529a4();
extern unsigned long FUN_00352a4c();
extern unsigned long FUN_00352be0();
extern unsigned long FUN_00352bf8();
extern unsigned long FUN_00352c10();
extern unsigned long FUN_00352c34();
extern unsigned long FUN_00352e0c();
extern unsigned long FUN_00352e18();
extern unsigned long FUN_00352ecc();
extern unsigned long FUN_00352ee4();
extern unsigned long FUN_00352efc();
extern unsigned long FUN_0035308c();
extern unsigned long FUN_003531c0();
extern unsigned long FUN_003531f0();
extern unsigned long FUN_00353274();
extern unsigned long FUN_003534a4();
extern unsigned long FUN_003534bc();
extern unsigned long FUN_003534c8();
extern unsigned long FUN_003537fc();
extern unsigned long FUN_00353a0c();
extern unsigned long FUN_00353a18();
extern unsigned long FUN_00353a30();
extern unsigned long FUN_00353ac8();
extern unsigned long FUN_00353be8();
extern unsigned long FUN_00353c0c();
extern unsigned long FUN_00353c48();
extern unsigned long FUN_00353c54();
extern unsigned long FUN_00353efc();
extern unsigned long FUN_003542e8();
extern unsigned long FUN_0035430c();
extern unsigned long FUN_00354318();
extern unsigned long FUN_00354364();
extern unsigned long FUN_003543f8();
extern unsigned long FUN_00354708();
extern unsigned long FUN_00354714();
extern unsigned long FUN_00354828();
extern unsigned long FUN_003549c0();
extern unsigned long FUN_003549d8();
extern unsigned long FUN_00354a34();
extern unsigned long FUN_00354d20();
extern unsigned long FUN_00354db8();
extern unsigned long FUN_00354ef8();
extern unsigned long FUN_0035578c();
extern unsigned long FUN_00355a14();
extern unsigned long FUN_00355b68();
extern unsigned long FUN_00355cbc();
extern unsigned long FUN_00356140();
extern unsigned long FUN_003561ac();
extern unsigned long FUN_0035631c();
extern unsigned long FUN_0035687c();
extern unsigned long FUN_003568e8();
extern unsigned long FUN_00356940();
extern unsigned long FUN_00356964();
extern unsigned long FUN_00356988();
extern unsigned long FUN_003569d8();
extern unsigned long FUN_003569f0();
extern unsigned long FUN_00356ad0();
extern unsigned long FUN_00356b2c();
extern unsigned long FUN_00356c18();
extern unsigned long FUN_00357694();
extern unsigned long FUN_003577b4();
extern unsigned long FUN_00357a34();
extern unsigned long FUN_00357a9c();
extern unsigned long FUN_00357bc4();
extern unsigned long FUN_00357c44();
extern unsigned long FUN_00357c74();
extern unsigned long FUN_00357ca0();
extern unsigned long FUN_00357cb4();
extern unsigned long FUN_00358134();
extern unsigned long FUN_00358238();
extern unsigned long FUN_00358324();
extern unsigned long FUN_0035847c();
extern unsigned long FUN_00358bc0();
extern unsigned long FUN_00358d58();
extern unsigned long FUN_00358de8();
extern unsigned long FUN_00358eac();
extern unsigned long FUN_00358f90();
extern unsigned long FUN_003592f0();
extern unsigned long FUN_0035a028();
extern unsigned long FUN_0035a134();
extern unsigned long FUN_0035a158();
extern unsigned long FUN_0035a2b8();
extern unsigned long FUN_0035a360();
extern unsigned long FUN_0035a3ac();
extern unsigned long FUN_0035a3b8();
extern unsigned long FUN_0035a438();
extern unsigned long FUN_0035a4c8();
extern unsigned long FUN_0035a4e0();
extern unsigned long FUN_0035a640();
extern unsigned long FUN_0035a664();
extern unsigned long FUN_0035a738();
extern unsigned long FUN_0035ac40();
extern unsigned long FUN_0035b67c();
extern unsigned long FUN_0035b7ac();
extern unsigned long FUN_0035b898();
extern unsigned long FUN_0035bc70();
extern unsigned long FUN_00365b6c();
extern unsigned long FUN_003698b0();
extern unsigned long FUN_0036993c();
extern unsigned long FUN_0036a908();
extern unsigned long FUN_0036a940();
extern unsigned long FUN_0036b270();
extern unsigned long FUN_003722e4();
extern unsigned long FUN_00376820();
extern unsigned long FUN_00377824();
extern unsigned long FUN_00377bec();
extern unsigned long FUN_003a25d4();
extern unsigned long FUN_003a261c();
extern unsigned long thunk_FUN_000126e8();
extern unsigned long thunk_FUN_0001612c();
extern unsigned long thunk_FUN_00024068();
extern unsigned long thunk_FUN_002acbb8();



/* Forward declarations of functions reconstructed in this file. */
unsigned long FUN_001900d4();
unsigned long FUN_001904d8();
void FUN_001908f0();
unsigned long FUN_00190bbc();
void FUN_00190fd4();
void FUN_001913b8();
void FUN_0019179c();
void FUN_00191ba8();
unsigned long FUN_00191f84();
unsigned int FUN_0019225c();
unsigned int FUN_00192528();
void FUN_00192920();
void FUN_00192bec();
void FUN_00192eb8();
void FUN_00193184();
unsigned long FUN_00193450();
void FUN_00193718();
void FUN_001939e4();
void FUN_00193cb0();
unsigned int FUN_00193f7c();
void FUN_00194370();
void FUN_0019463c();
void FUN_001948f8();
void FUN_00194bb4();
void FUN_00194e80();
void FUN_0019514c();
unsigned int FUN_00195418();
unsigned int FUN_001956f4();
unsigned int FUN_001959e8();
void FUN_00195cc4();
void FUN_00195f6c();
unsigned long FUN_00196204();
unsigned long FUN_001964f4();
void FUN_0019661c();
void FUN_00196644();
void FUN_00196964();
void FUN_00196c20();
unsigned long FUN_00196fec();
unsigned long FUN_001972a4();
void FUN_00197594();
void FUN_00197850();
void FUN_00197be4();
unsigned long FUN_00197dd0();
void FUN_00197e48();
unsigned long FUN_00197e74();
void FUN_00197fec();
unsigned int FUN_00198024();
unsigned int FUN_00198028();
unsigned long FUN_0019804c();
void FUN_001980c4();
unsigned long FUN_001980f0();
void FUN_00198268();
unsigned int FUN_001982a0();
unsigned int FUN_001982a4();
unsigned long FUN_001982c8();
unsigned int FUN_00198300();
unsigned long FUN_00198370();
void FUN_001983d4();
unsigned long FUN_00198438();
void FUN_00198564();
unsigned int FUN_0019859c();
unsigned int FUN_001985a0();
unsigned long FUN_001985c4();
void FUN_00198658();
unsigned long FUN_00198684();
void FUN_001987dc();
unsigned int FUN_00198814();
unsigned int FUN_00198818();
unsigned long FUN_0019883c();
void FUN_001988b4();
void FUN_001988e0();
void FUN_00198a04();
unsigned int FUN_00198a3c();
unsigned int FUN_00198a40();
long FUN_00198a64();
unsigned int FUN_00198acc();
unsigned long FUN_00198b08();
void FUN_00198bac();
void FUN_00198c20();
void FUN_00198cf0();
unsigned int FUN_00198d28();
unsigned int FUN_00198d2c();
unsigned long FUN_00198d50();
void FUN_00198d68();
unsigned long FUN_00198d94();
void FUN_00198ecc();
unsigned int FUN_00198f04();
unsigned long FUN_00198f2c();
void FUN_00198f8c();
unsigned long FUN_00198fc8();
void FUN_001990ec();
unsigned int FUN_00199124();
unsigned int FUN_00199128();
void FUN_0019914c();
void FUN_001991c8();
void FUN_001991f4();
unsigned long FUN_00199254();
void FUN_0019938c();
unsigned int FUN_001993c4();
void FUN_00199438();
unsigned long FUN_0019957c();
unsigned int FUN_001996f0();
unsigned int FUN_001996f4();
unsigned int FUN_00199718();
void FUN_0019978c();
unsigned long FUN_001998c8();
unsigned int FUN_00199a34();
unsigned int FUN_00199a38();
unsigned long FUN_00199a5c();
void FUN_00199ad4();
void FUN_00199b00();
unsigned long FUN_00199b54();
void FUN_00199ccc();
unsigned int FUN_00199d04();
unsigned int FUN_00199d08();
unsigned long FUN_00199d2c();
void FUN_00199d8c();
unsigned long FUN_00199dc8();
void FUN_00199eec();
unsigned int FUN_00199f24();
unsigned int FUN_00199f28();
unsigned long FUN_00199f4c();
void FUN_00199fe4();
unsigned long FUN_0019a034();
void FUN_0019a180();
unsigned int FUN_0019a1b8();
unsigned int FUN_0019a1bc();
void FUN_0019a1e0();
void FUN_0019a30c();
unsigned long FUN_0019a424();
void FUN_0019a4dc();
void FUN_0019a594();
void FUN_0019a598();
void FUN_0019a5c0();
void FUN_0019a5c4();
void FUN_0019a5ec();
void FUN_0019a5f0();
void FUN_0019a618();
void FUN_0019a6e4();
void FUN_0019a6e8();
void FUN_0019a710();
void FUN_0019a7d8();
void FUN_0019a7dc();
void FUN_0019a804();
void FUN_0019a808();
unsigned long FUN_0019a830();
void FUN_0019ad48();
void FUN_0019ad4c();
void FUN_0019ad70();
void FUN_0019ad74();
void FUN_0019ada4();
void FUN_0019ada8();
void FUN_0019addc();
void FUN_0019ade0();
void FUN_0019adf4();
void FUN_0019adf8();
unsigned long FUN_0019ae0c();
void FUN_0019ae2c();
void FUN_0019ae60();
unsigned int FUN_0019af88();
unsigned long FUN_0019afb0();
unsigned int FUN_0019afbc();
void FUN_0019afd4();
void FUN_0019b018();
void FUN_0019b25c();
void FUN_0019b274();
void FUN_0019b318();
void FUN_0019b528();
void FUN_0019b66c();
void FUN_0019c03c();
void FUN_0019c078();
void FUN_0019c20c();
long FUN_0019c258();
void FUN_0019c2b0();
void FUN_0019c2fc();
void FUN_0019c348();
void FUN_0019c3a4();
void FUN_0019c3f0();
unsigned long FUN_0019c44c();
void FUN_0019c53c();
void FUN_0019c968();
unsigned long FUN_0019c9bc();
unsigned long FUN_0019c9c4();
void FUN_0019c9cc();
unsigned long FUN_0019cac8();
unsigned long FUN_0019cb68();
void FUN_0019cbd4();
void FUN_0019cc64();
void FUN_0019ccec();
void FUN_0019cd74();
void FUN_0019cdf8();
void FUN_0019ce60();
void FUN_0019cf3c();
void FUN_0019d060();
void FUN_0019d0d0();
void FUN_0019d15c();
void FUN_0019d234();
void FUN_0019d338();
void FUN_0019d40c();
void FUN_0019d498();
void FUN_0019d528();
void FUN_0019d600();
void FUN_0019d6d0();
void FUN_0019d7ac();
void FUN_0019d888();
void FUN_0019d960();
void FUN_0019da34();
void FUN_0019dadc();
void FUN_0019dbac();
void FUN_0019dc44();
void FUN_0019dca8();
void FUN_0019dd10();
void FUN_0019de24();
void FUN_0019dfc4();
void FUN_0019e058();
bool FUN_0019e128();
void FUN_0019e1b0();
void FUN_0019e3b0();
void FUN_0019e410();
void FUN_0019e434();
void FUN_0019e4bc();
void FUN_0019e538();
unsigned long FUN_0019e578();
void FUN_0019e5b4();
void thunk_FUN_001dc298();
unsigned long FUN_0019e5ec();
void FUN_0019e618();
void FUN_0019e630();
void FUN_0019e644();
void FUN_0019e658();
unsigned long FUN_0019e66c();
void FUN_0019e690();
void FUN_0019e6bc();
void FUN_0019e728();
void FUN_0019e760();
/*--------------------------------------------------------------------*/
/* FUN_0019e814 @ 0x0019e814   (est. sk_swift_helper)
 * Ghidra: void FUN_0019e814(long param_1,long param_2)
 * Bounds-check helper: if the collection count (param_2+0x10) is below the requested index,
 * raises a precondition error and falls into the noreturn fatal path.
 * Confidence: medium (templated Swift runtime body). */
void FUN_0019e814(long param_1,long param_2)
{
  if (*(long *)(param_2 + 0x10) < param_1) {
    FUN_003488bc(1);
    FUN_0034a3d8();
  }
  else {
    if (-1 < param_1) {
      return;
    }
    FUN_003488bc(1);
    FUN_0034a3d8();
  }
  FUN_003504b8();
  /* noreturn fatal */
  sk_swift_fatal_error_2();
}
/*--------------------------------------------------------------------*/
/* FUN_001900d4 @ 0x001900d4   (est. sk_swift_helper)
 * Ghidra: ulong FUN_001900d4(undefined8 param_1,long param_2)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

/* WARNING: Removing unreachable block (ram,0x001902e0) */

unsigned long FUN_001900d4(unsigned long param_1,long param_2)

{
  code *pcVar2;
  long next;
    bool overflow;
  char kind;
  unsigned long fatal_v;
  unsigned int *extraout_x1;
  unsigned char *extraout_x1_00;
  unsigned long extraout_x1_01;
  unsigned long fatal_a;
  long j;
  unsigned long count;
  long ctx_err;
  unsigned long result;
  unsigned long fatal_line;
  unsigned long local_260;
  unsigned long uStack_258;
  unsigned long uStack_250;
  unsigned long uStack_248;
  unsigned long local_240;
  unsigned long uStack_238;
  unsigned char local_230;
  unsigned long local_228;
  unsigned long local_220;
  unsigned long uStack_218;
  unsigned long uStack_210;
  unsigned long uStack_208;
  unsigned long local_200;
  unsigned long uStack_1f8;
  unsigned char local_1f0;
  unsigned int local_1ec;
  unsigned char auStack_1e8 [56];
  unsigned char auStack_1b0 [56];
  unsigned char auStack_178 [56];
  unsigned long local_140;
  unsigned long uStack_138;
  unsigned long uStack_130;
  unsigned long uStack_128;
  unsigned long local_120;
  unsigned long uStack_118;
  unsigned char local_110;
  unsigned long local_100;
  unsigned long uStack_f8;
  unsigned long uStack_f0;
  unsigned long uStack_e8;
  unsigned long local_e0;
  unsigned long uStack_d8;
  unsigned char local_d0;
  unsigned long local_80;
  unsigned long uStack_78;
  unsigned long uStack_70;
  unsigned long uStack_68;
  unsigned long local_60;
  unsigned long uStack_58;
  unsigned char local_50;
  
  count = 0;
  while ((count != 0x20 &&
         (overflow = *(unsigned long *)(param_2 + 0x10) <= count, count != *(unsigned long *)(param_2 + 0x10)))) {
    count = count + 1;
    if (overflow) {
                    /* WARNING: Does not return */
      __builtin_trap();
    }
  }
  sk_swift_frame_init(auStack_1e8,count + 0xc,0,&local_1ec);
  if (ctx_err == 0) {
    sk_swift_string_begin(&local_220);
    sk_swift_type_hash(0xed16852b145f5174);
    sk_swift_type_arg(param_1);
    count = *(unsigned long *)(param_2 + 0x10);
    if (count != 0x20) {
      local_260 = 0;
      uStack_258 = 0xe000000000000000;
      sk_swift_precond_1(0x3b);
      sk_swift_precond_2(0xd000000000000018,0x80000000005cd5b0);
      sk_swift_precond_2(0xd000000000000037,0x80000000005cc150);
      local_228 = count;
      pcVar2 = (code *)sk_swift_meta(0x6720e0);
      (*pcVar2)(0x677880,0x6720e0);
      sk_swift_precond_2();
      sk_swift_abort_tail(extraout_x1_01);
      fatal_line = 0x3f7;
      fatal_v = local_260;
      fatal_a = uStack_258;
LAB_00190488:
                    /* WARNING: Subroutine does not return */
      sk_swift_fatal_error(sk_fatal_error_str,0xb,2,fatal_v,fatal_a,
                   sk_xnu_upcalls_swift,0x25,2,fatal_line,0);
    }
    j = 0;
    do {
      next = j + 1;
      sk_swift_elem_append(*(unsigned char *)(param_2 + 0x20 + j));
      j = next;
    } while (next != 0x20);
    uStack_78 = uStack_218;
    local_80 = local_220;
    uStack_68 = uStack_208;
    uStack_70 = uStack_210;
    uStack_58 = uStack_1f8;
    local_60 = local_200;
    local_50 = local_1f0;
    sk_swift_buf_ctx(auStack_1b0);
    sk_swift_error_build(auStack_178,auStack_1b0,&local_1ec);
    sk_swift_string_build(&local_260,auStack_178);
    kind = sk_swift_result_check();
    if (kind == '\0') {
      result = sk_swift_result_value();
      uStack_138 = uStack_258;
      local_140 = local_260;
      uStack_128 = uStack_248;
      uStack_130 = uStack_250;
      uStack_118 = uStack_238;
      local_120 = local_240;
      local_110 = local_230;
      sk_swift_epilogue();
    }
    else {
      if (kind != '\x01') {
        fatal_line = 0xf5d;
        fatal_v = 0xd000000000000037;
        fatal_a = 0x80000000005cd5d0;
        goto LAB_00190488;
      }
      sk_swift_collection_op(&local_228,0x66a0b0,0x65a688,0x66a0b0,0x65a5e8,0x66a708,&local_1ec);
      sk_swift_retain(&local_228,0x66a0b0,0x669c50);
      result = local_228 & 0xff;
      sk_swift_release(0x66a0b0,0x669c50,0,0);
      *extraout_x1_00 = (unsigned char)local_228;
      uStack_f8 = uStack_258;
      local_100 = local_260;
      uStack_e8 = uStack_248;
      uStack_f0 = uStack_250;
      uStack_d8 = uStack_238;
      local_e0 = local_240;
      local_d0 = local_230;
      sk_swift_epilogue();
    }
  }
  else {
    fatal_v = sk_swift_err_code(0);
    sk_swift_release(fatal_v,FUN_0065a550,0,0);
    *extraout_x1 = local_1ec;
  }
  return result;
}





/*--------------------------------------------------------------------*/
/* FUN_001904d8 @ 0x001904d8   (est. sk_swift_helper)
 * Ghidra: ulong FUN_001904d8(undefined8 param_1,undefined8 param_2,long param_3)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

/* WARNING: Removing unreachable block (ram,0x001906fc) */

unsigned long FUN_001904d8(unsigned long param_1,unsigned long param_2,long param_3)

{
  code *pcVar2;
  long next;
    bool overflow;
  char kind;
  unsigned long fatal_v;
  unsigned int *extraout_x1;
  unsigned char *extraout_x1_00;
  unsigned long extraout_x1_01;
  unsigned long fatal_a;
  long j;
  unsigned long count;
  long ctx_err;
  unsigned long result;
  unsigned long fatal_line;
  unsigned long local_270;
  unsigned long uStack_268;
  unsigned long uStack_260;
  unsigned long uStack_258;
  unsigned long local_250;
  unsigned long uStack_248;
  unsigned char local_240;
  unsigned long local_238;
  unsigned long local_230;
  unsigned long uStack_228;
  unsigned long uStack_220;
  unsigned long uStack_218;
  unsigned long local_210;
  unsigned long uStack_208;
  unsigned char local_200;
  unsigned char auStack_1f8 [56];
  unsigned char auStack_1c0 [56];
  unsigned char auStack_188 [56];
  unsigned long local_150;
  unsigned long uStack_148;
  unsigned long uStack_140;
  unsigned long uStack_138;
  unsigned long local_130;
  unsigned long uStack_128;
  unsigned char local_120;
  unsigned long local_110;
  unsigned long uStack_108;
  unsigned long uStack_100;
  unsigned long uStack_f8;
  unsigned long local_f0;
  unsigned long uStack_e8;
  unsigned char local_e0;
  unsigned long local_90;
  unsigned long uStack_88;
  unsigned long uStack_80;
  unsigned long uStack_78;
  unsigned long local_70;
  unsigned long uStack_68;
  unsigned char local_60;
  unsigned int local_44;
  
  count = 0;
  while ((count != 0x100 &&
         (overflow = *(unsigned long *)(param_3 + 0x10) <= count, count != *(unsigned long *)(param_3 + 0x10)))) {
    count = count + 1;
    if (overflow) {
                    /* WARNING: Does not return */
      __builtin_trap();
    }
  }
  sk_swift_frame_init(auStack_1f8,count + 0x14,0,&local_44);
  if (ctx_err == 0) {
    sk_swift_string_begin(&local_230);
    sk_swift_type_hash(0x654c7887b46ed06);
    sk_swift_type_arg(param_1);
    sk_swift_type_hash(param_2);
    count = *(unsigned long *)(param_3 + 0x10);
    if (count != 0x100) {
      local_270 = 0;
      uStack_268 = 0xe000000000000000;
      sk_swift_precond_1(0x3c);
      sk_swift_precond_2(0xd000000000000018,0x80000000005cd590);
      sk_swift_precond_2(0xd000000000000038,0x80000000005cc940);
      local_238 = count;
      pcVar2 = (code *)sk_swift_meta(0x6720e0);
      (*pcVar2)(0x677880,0x6720e0);
      sk_swift_precond_2();
      sk_swift_abort_tail(extraout_x1_01);
      fatal_line = 0x40e;
      fatal_v = local_270;
      fatal_a = uStack_268;
LAB_0019089c:
                    /* WARNING: Subroutine does not return */
      sk_swift_fatal_error(sk_fatal_error_str,0xb,2,fatal_v,fatal_a,
                   sk_xnu_upcalls_swift,0x25,2,fatal_line,0);
    }
    j = 0;
    do {
      next = j + 1;
      sk_swift_elem_append(*(unsigned char *)(param_3 + 0x20 + j));
      j = next;
    } while (next != 0x100);
    uStack_88 = uStack_228;
    local_90 = local_230;
    uStack_78 = uStack_218;
    uStack_80 = uStack_220;
    uStack_68 = uStack_208;
    local_70 = local_210;
    local_60 = local_200;
    sk_swift_buf_ctx(auStack_1c0);
    sk_swift_error_build(auStack_188,auStack_1c0,&local_44);
    sk_swift_string_build(&local_270,auStack_188);
    kind = sk_swift_result_check();
    if (kind == '\0') {
      result = sk_swift_result_value();
      uStack_148 = uStack_268;
      local_150 = local_270;
      uStack_138 = uStack_258;
      uStack_140 = uStack_260;
      uStack_128 = uStack_248;
      local_130 = local_250;
      local_120 = local_240;
      sk_swift_epilogue();
    }
    else {
      if (kind != '\x01') {
        fatal_line = 0xf68;
        fatal_v = 0xd000000000000035;
        fatal_a = 0x80000000005ccb00;
        goto LAB_0019089c;
      }
      sk_swift_collection_op(&local_238,0x66a0b0,0x65a688,0x66a0b0,0x65a5e8,0x66a708,&local_44);
      sk_swift_retain(&local_238,0x66a0b0,0x669c50);
      result = local_238 & 0xff;
      sk_swift_release(0x66a0b0,0x669c50,0,0);
      *extraout_x1_00 = (unsigned char)local_238;
      uStack_108 = uStack_268;
      local_110 = local_270;
      uStack_f8 = uStack_258;
      uStack_100 = uStack_260;
      uStack_e8 = uStack_248;
      local_f0 = local_250;
      local_e0 = local_240;
      sk_swift_epilogue();
    }
  }
  else {
    fatal_v = sk_swift_err_code(0);
    sk_swift_release(fatal_v,FUN_0065a550,0,0);
    *extraout_x1 = local_44;
  }
  return result;
}





/*--------------------------------------------------------------------*/
/* FUN_001908f0 @ 0x001908f0   (est. sk_swift_helper)
 * Ghidra: void FUN_001908f0(undefined8 param_1,undefined8 param_2)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

/* WARNING: Removing unreachable block (ram,0x00190a64) */

void FUN_001908f0(unsigned long param_1,unsigned long param_2)

{
  char kind;
  unsigned long err;
  unsigned int *extraout_x1;
  char *extraout_x1_00;
  long ctx_err;
  char local_219;
  unsigned long local_218;
  unsigned long uStack_210;
  unsigned long local_208;
  unsigned long uStack_200;
  unsigned long local_1f8;
  unsigned long uStack_1f0;
  unsigned char local_1e8;
  unsigned char auStack_1e0 [52];
  unsigned int local_1ac;
  unsigned char auStack_1a8 [56];
  unsigned char auStack_170 [56];
  unsigned char auStack_138 [56];
  unsigned long local_100;
  unsigned long uStack_f8;
  unsigned long uStack_f0;
  unsigned long uStack_e8;
  unsigned long local_e0;
  unsigned long uStack_d8;
  unsigned char local_d0;
  
  sk_swift_frame_init(auStack_1a8,0x14,0,&local_1ac);
  if (ctx_err != 0) {
    err = sk_swift_err_code(0);
    sk_swift_release(err,FUN_0065a550,0,0);
    *extraout_x1 = local_1ac;
    return;
  }
  sk_swift_string_begin(auStack_1e0);
  sk_swift_type_hash(0xc55ed0c0604846a5);
  sk_swift_type_arg(param_1);
  sk_swift_type_hash(param_2);
  sk_swift_buf_ctx(auStack_170);
  sk_swift_error_build(auStack_138,auStack_170,&local_1ac);
  sk_swift_string_build(&local_218,auStack_138);
  kind = sk_swift_result_check();
  if (kind == '\x01') {
    sk_swift_collection_op(&local_219,0x66a0b0,0x65a688,0x66a0b0,0x65a5e8,0x66a708,&local_1ac);
    if (local_219 != '\x16') {
      sk_swift_retain(&local_219,0x66a0b0,0x669c50);
      sk_swift_release(0x66a0b0,0x669c50,0,0);
      *extraout_x1_00 = local_219;
      goto LAB_00190ae0;
    }
  }
  else if (kind != '\0') {
                    /* WARNING: Subroutine does not return */
    sk_swift_fatal_error(sk_fatal_error_str,0xb,2,0xd000000000000036,0x80000000005ccaa0,
                 sk_xnu_upcalls_swift,0x25,2,0xf73,0);
  }
  uStack_f8 = uStack_210;
  local_100 = local_218;
  uStack_e8 = uStack_200;
  uStack_f0 = local_208;
  uStack_d8 = uStack_1f0;
  local_e0 = local_1f8;
  local_d0 = local_1e8;
LAB_00190ae0:
  sk_swift_epilogue();
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_00190bbc @ 0x00190bbc   (est. sk_swift_helper)
 * Ghidra: ulong FUN_00190bbc(undefined8 param_1,undefined8 param_2,long param_3)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

/* WARNING: Removing unreachable block (ram,0x00190de0) */

unsigned long FUN_00190bbc(unsigned long param_1,unsigned long param_2,long param_3)

{
  code *pcVar2;
  long next;
    bool overflow;
  char kind;
  unsigned long fatal_v;
  unsigned int *extraout_x1;
  unsigned char *extraout_x1_00;
  unsigned long extraout_x1_01;
  unsigned long fatal_a;
  long j;
  unsigned long count;
  long ctx_err;
  unsigned long result;
  unsigned long fatal_line;
  unsigned long local_270;
  unsigned long uStack_268;
  unsigned long uStack_260;
  unsigned long uStack_258;
  unsigned long local_250;
  unsigned long uStack_248;
  unsigned char local_240;
  unsigned long local_238;
  unsigned long local_230;
  unsigned long uStack_228;
  unsigned long uStack_220;
  unsigned long uStack_218;
  unsigned long local_210;
  unsigned long uStack_208;
  unsigned char local_200;
  unsigned char auStack_1f8 [56];
  unsigned char auStack_1c0 [56];
  unsigned char auStack_188 [56];
  unsigned long local_150;
  unsigned long uStack_148;
  unsigned long uStack_140;
  unsigned long uStack_138;
  unsigned long local_130;
  unsigned long uStack_128;
  unsigned char local_120;
  unsigned long local_110;
  unsigned long uStack_108;
  unsigned long uStack_100;
  unsigned long uStack_f8;
  unsigned long local_f0;
  unsigned long uStack_e8;
  unsigned char local_e0;
  unsigned long local_90;
  unsigned long uStack_88;
  unsigned long uStack_80;
  unsigned long uStack_78;
  unsigned long local_70;
  unsigned long uStack_68;
  unsigned char local_60;
  unsigned int local_44;
  
  count = 0;
  while ((count != 0x100 &&
         (overflow = *(unsigned long *)(param_3 + 0x10) <= count, count != *(unsigned long *)(param_3 + 0x10)))) {
    count = count + 1;
    if (overflow) {
                    /* WARNING: Does not return */
      __builtin_trap();
    }
  }
  sk_swift_frame_init(auStack_1f8,count + 0x14,0,&local_44);
  if (ctx_err == 0) {
    sk_swift_string_begin(&local_230);
    sk_swift_type_hash(0x2d7170cc0f48d0d9);
    sk_swift_type_arg(param_1);
    sk_swift_type_hash(param_2);
    count = *(unsigned long *)(param_3 + 0x10);
    if (count != 0x100) {
      local_270 = 0;
      uStack_268 = 0xe000000000000000;
      sk_swift_precond_1(0x3c);
      sk_swift_precond_2(0xd00000000000001a,0x80000000005cd570);
      sk_swift_precond_2(0xd000000000000038,0x80000000005cc940);
      local_238 = count;
      pcVar2 = (code *)sk_swift_meta(0x6720e0);
      (*pcVar2)(0x677880,0x6720e0);
      sk_swift_precond_2();
      sk_swift_abort_tail(extraout_x1_01);
      fatal_line = 0x431;
      fatal_v = local_270;
      fatal_a = uStack_268;
LAB_00190f80:
                    /* WARNING: Subroutine does not return */
      sk_swift_fatal_error(sk_fatal_error_str,0xb,2,fatal_v,fatal_a,
                   sk_xnu_upcalls_swift,0x25,2,fatal_line,0);
    }
    j = 0;
    do {
      next = j + 1;
      sk_swift_elem_append(*(unsigned char *)(param_3 + 0x20 + j));
      j = next;
    } while (next != 0x100);
    uStack_88 = uStack_228;
    local_90 = local_230;
    uStack_78 = uStack_218;
    uStack_80 = uStack_220;
    uStack_68 = uStack_208;
    local_70 = local_210;
    local_60 = local_200;
    sk_swift_buf_ctx(auStack_1c0);
    sk_swift_error_build(auStack_188,auStack_1c0,&local_44);
    sk_swift_string_build(&local_270,auStack_188);
    kind = sk_swift_result_check();
    if (kind == '\0') {
      result = sk_swift_result_value();
      uStack_148 = uStack_268;
      local_150 = local_270;
      uStack_138 = uStack_258;
      uStack_140 = uStack_260;
      uStack_128 = uStack_248;
      local_130 = local_250;
      local_120 = local_240;
      sk_swift_epilogue();
    }
    else {
      if (kind != '\x01') {
        fatal_line = 0xf7e;
        fatal_v = 0xd000000000000037;
        fatal_a = 0x80000000005cca60;
        goto LAB_00190f80;
      }
      sk_swift_collection_op(&local_238,0x66a0b0,0x65a688,0x66a0b0,0x65a5e8,0x66a708,&local_44);
      sk_swift_retain(&local_238,0x66a0b0,0x669c50);
      result = local_238 & 0xff;
      sk_swift_release(0x66a0b0,0x669c50,0,0);
      *extraout_x1_00 = (unsigned char)local_238;
      uStack_108 = uStack_268;
      local_110 = local_270;
      uStack_f8 = uStack_258;
      uStack_100 = uStack_260;
      uStack_e8 = uStack_248;
      local_f0 = local_250;
      local_e0 = local_240;
      sk_swift_epilogue();
    }
  }
  else {
    fatal_v = sk_swift_err_code(0);
    sk_swift_release(fatal_v,FUN_0065a550,0,0);
    *extraout_x1 = local_44;
  }
  return result;
}





/*--------------------------------------------------------------------*/
/* FUN_00190fd4 @ 0x00190fd4   (est. sk_swift_helper)
 * Ghidra: void FUN_00190fd4(undefined8 param_1,undefined8 param_2,undefined8 *param_3)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

/* WARNING: Removing unreachable block (ram,0x00191264) */
/* WARNING: Removing unreachable block (ram,0x00191130) */

void FUN_00190fd4(unsigned long param_1,unsigned long param_2,unsigned long *param_3)

{
  unsigned long uVar1;
    char kind;
  long len;
  unsigned long fatal_v;
  unsigned int *extraout_x1;
  char *extraout_x1_00;
  long ctx_err;
  unsigned long fatal_a;
  char local_2c9;
  unsigned long local_2c8;
  unsigned long uStack_2c0;
  unsigned long local_2b8;
  unsigned long local_290;
  unsigned long uStack_288;
  unsigned long local_280;
  unsigned long uStack_278;
  unsigned long local_270;
  unsigned long uStack_268;
  unsigned char local_260;
  unsigned int local_25c;
  unsigned char auStack_258 [56];
  unsigned char auStack_220 [56];
  unsigned char auStack_1e8 [56];
  unsigned long local_1b0;
  unsigned long uStack_1a8;
  unsigned long uStack_1a0;
  unsigned long local_170;
  unsigned long uStack_168;
  unsigned long uStack_160;
  unsigned long local_f0;
  unsigned long uStack_e8;
  unsigned long uStack_e0;
  unsigned long uStack_d8;
  unsigned long local_d0;
  unsigned long uStack_c8;
  unsigned char local_c0;
  
  fatal_v = *param_3;
  uVar1 = param_3[1];
  fatal_a = param_3[2];
  local_290 = fatal_v;
  uStack_288 = uVar1;
  local_280 = fatal_a;
  len = sk_swift_collection_count(&local_290,0x669f88,0x66a6e0);
  if (SCARRY8(len,0x14)) {
                    /* WARNING: Does not return */
    __builtin_trap();
  }
  sk_swift_frame_init(auStack_258,len + 0x14,0,&local_25c);
  if (ctx_err != 0) {
    fatal_v = sk_swift_err_code(0);
    sk_swift_release(fatal_v,FUN_0065a550,0,0);
    *extraout_x1 = local_25c;
    return;
  }
  sk_swift_string_begin(&local_290);
  sk_swift_type_hash(0xf532d124b8ac6c75);
  sk_swift_type_arg(param_1);
  sk_swift_type_hash(param_2);
  local_2c8 = fatal_v;
  uStack_2c0 = uVar1;
  local_2b8 = fatal_a;
  sk_swift_collection_init(&local_2c8,0x65a870,0x669f88,0x65a798,0x66a6e0);
  uStack_e8 = uStack_288;
  local_f0 = local_290;
  uStack_d8 = uStack_278;
  uStack_e0 = local_280;
  uStack_c8 = uStack_268;
  local_d0 = local_270;
  local_c0 = local_260;
  sk_swift_buf_ctx(auStack_220);
  sk_swift_error_build(auStack_1e8,auStack_220,&local_25c);
  sk_swift_string_build(&local_2c8,auStack_1e8);
  kind = sk_swift_result_check();
  if (kind == '\x01') {
    sk_swift_collection_op(&local_2c9,0x66a0b0,0x65a688,0x66a0b0,0x65a5e8,0x66a708,&local_25c);
    if (local_2c9 != '\x16') {
      sk_swift_retain(&local_2c9,0x66a0b0,0x669c50);
      sk_swift_release(0x66a0b0,0x669c50,0,0);
      *extraout_x1_00 = local_2c9;
      uStack_168 = uStack_2c0;
      local_170 = local_2c8;
      uStack_160 = local_2b8;
      goto LAB_00191180;
    }
  }
  else if (kind != '\0') {
                    /* WARNING: Subroutine does not return */
    sk_swift_fatal_error(sk_fatal_error_str,0xb,2,0xd000000000000035,0x80000000005cca00,
                 sk_xnu_upcalls_swift,0x25,2,0xf89,0);
  }
  uStack_1a8 = uStack_2c0;
  local_1b0 = local_2c8;
  uStack_1a0 = local_2b8;
LAB_00191180:
  sk_swift_epilogue();
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_001913b8 @ 0x001913b8   (est. sk_swift_helper)
 * Ghidra: void FUN_001913b8(undefined8 param_1,undefined8 param_2,undefined8 *param_3)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

/* WARNING: Removing unreachable block (ram,0x00191648) */
/* WARNING: Removing unreachable block (ram,0x00191514) */

void FUN_001913b8(unsigned long param_1,unsigned long param_2,unsigned long *param_3)

{
  unsigned long uVar1;
    char kind;
  long len;
  unsigned long fatal_v;
  unsigned int *extraout_x1;
  char *extraout_x1_00;
  long ctx_err;
  unsigned long fatal_a;
  char local_2c9;
  unsigned long local_2c8;
  unsigned long uStack_2c0;
  unsigned long local_2b8;
  unsigned long local_290;
  unsigned long uStack_288;
  unsigned long local_280;
  unsigned long uStack_278;
  unsigned long local_270;
  unsigned long uStack_268;
  unsigned char local_260;
  unsigned int local_25c;
  unsigned char auStack_258 [56];
  unsigned char auStack_220 [56];
  unsigned char auStack_1e8 [56];
  unsigned long local_1b0;
  unsigned long uStack_1a8;
  unsigned long uStack_1a0;
  unsigned long local_170;
  unsigned long uStack_168;
  unsigned long uStack_160;
  unsigned long local_f0;
  unsigned long uStack_e8;
  unsigned long uStack_e0;
  unsigned long uStack_d8;
  unsigned long local_d0;
  unsigned long uStack_c8;
  unsigned char local_c0;
  
  fatal_v = *param_3;
  uVar1 = param_3[1];
  fatal_a = param_3[2];
  local_290 = fatal_v;
  uStack_288 = uVar1;
  local_280 = fatal_a;
  len = sk_swift_collection_count(&local_290,0x669f88,0x66a6e0);
  if (SCARRY8(len,0x14)) {
                    /* WARNING: Does not return */
    __builtin_trap();
  }
  sk_swift_frame_init(auStack_258,len + 0x14,0,&local_25c);
  if (ctx_err != 0) {
    fatal_v = sk_swift_err_code(0);
    sk_swift_release(fatal_v,FUN_0065a550,0,0);
    *extraout_x1 = local_25c;
    return;
  }
  sk_swift_string_begin(&local_290);
  sk_swift_type_hash(0x9aa74c5aaf52ce49);
  sk_swift_type_arg(param_1);
  sk_swift_type_hash(param_2);
  local_2c8 = fatal_v;
  uStack_2c0 = uVar1;
  local_2b8 = fatal_a;
  sk_swift_collection_init(&local_2c8,0x65a870,0x669f88,0x65a798,0x66a6e0);
  uStack_e8 = uStack_288;
  local_f0 = local_290;
  uStack_d8 = uStack_278;
  uStack_e0 = local_280;
  uStack_c8 = uStack_268;
  local_d0 = local_270;
  local_c0 = local_260;
  sk_swift_buf_ctx(auStack_220);
  sk_swift_error_build(auStack_1e8,auStack_220,&local_25c);
  sk_swift_string_build(&local_2c8,auStack_1e8);
  kind = sk_swift_result_check();
  if (kind == '\x01') {
    sk_swift_collection_op(&local_2c9,0x66a0b0,0x65a688,0x66a0b0,0x65a5e8,0x66a708,&local_25c);
    if (local_2c9 != '\x16') {
      sk_swift_retain(&local_2c9,0x66a0b0,0x669c50);
      sk_swift_release(0x66a0b0,0x669c50,0,0);
      *extraout_x1_00 = local_2c9;
      uStack_168 = uStack_2c0;
      local_170 = local_2c8;
      uStack_160 = local_2b8;
      goto LAB_00191564;
    }
  }
  else if (kind != '\0') {
                    /* WARNING: Subroutine does not return */
    sk_swift_fatal_error(sk_fatal_error_str,0xb,2,0xd000000000000036,0x80000000005cc9c0,
                 sk_xnu_upcalls_swift,0x25,2,0xf94,0);
  }
  uStack_1a8 = uStack_2c0;
  local_1b0 = local_2c8;
  uStack_1a0 = local_2b8;
LAB_00191564:
  sk_swift_epilogue();
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019179c @ 0x0019179c   (est. sk_swift_helper)
 * Ghidra: void FUN_0019179c(undefined8 param_1,undefined8 param_2,long param_3)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

/* WARNING: Removing unreachable block (ram,0x00191984) */

void FUN_0019179c(unsigned long param_1,unsigned long param_2,long param_3)

{
  code *pcVar2;
  long next;
    bool overflow;
  char kind;
  unsigned long fatal_v;
  unsigned int *extraout_x1;
  char *extraout_x1_00;
  unsigned long extraout_x1_01;
  unsigned long fatal_a;
  unsigned long count;
  long ctx_err;
  long j;
  unsigned long fatal_line;
  unsigned long local_270;
  unsigned long uStack_268;
  unsigned long uStack_260;
  unsigned long uStack_258;
  unsigned long local_250;
  unsigned long uStack_248;
  unsigned char local_240;
  long local_238;
  unsigned long local_230;
  unsigned long uStack_228;
  unsigned long uStack_220;
  unsigned long uStack_218;
  unsigned long local_210;
  unsigned long uStack_208;
  unsigned char local_200;
  unsigned char auStack_1f8 [56];
  unsigned char auStack_1c0 [56];
  unsigned char auStack_188 [56];
  unsigned long local_150;
  unsigned long uStack_148;
  unsigned long uStack_140;
  unsigned long uStack_138;
  unsigned long local_130;
  unsigned long uStack_128;
  unsigned char local_120;
  unsigned long local_90;
  unsigned long uStack_88;
  unsigned long uStack_80;
  unsigned long uStack_78;
  unsigned long local_70;
  unsigned long uStack_68;
  unsigned char local_60;
  unsigned int local_44;
  
  count = 0;
  while ((count != 0x100 &&
         (overflow = *(unsigned long *)(param_3 + 0x10) <= count, count != *(unsigned long *)(param_3 + 0x10)))) {
    count = count + 1;
    if (overflow) {
                    /* WARNING: Does not return */
      __builtin_trap();
    }
  }
  sk_swift_frame_init(auStack_1f8,count + 0x14,0,&local_44);
  if (ctx_err != 0) {
    fatal_v = sk_swift_err_code(0);
    sk_swift_release(fatal_v,FUN_0065a550,0,0);
    *extraout_x1 = local_44;
    return;
  }
  sk_swift_string_begin(&local_230);
  sk_swift_type_hash(0xc3a10bf3a0a45211);
  sk_swift_type_arg(param_1);
  sk_swift_type_hash(param_2);
  j = *(long *)(param_3 + 0x10);
  if (j != 0x100) {
    local_270 = 0;
    uStack_268 = 0xe000000000000000;
    sk_swift_precond_1(0x3c);
    sk_swift_precond_2(0xd00000000000001a,0x80000000005cd550);
    sk_swift_precond_2(0xd000000000000038,0x80000000005cc940);
    local_238 = j;
    pcVar2 = (code *)sk_swift_meta(0x6720e0);
    (*pcVar2)(0x677880,0x6720e0);
    sk_swift_precond_2();
    sk_swift_abort_tail(extraout_x1_01);
    fatal_line = 0x466;
    fatal_v = local_270;
    fatal_a = uStack_268;
LAB_00191b54:
                    /* WARNING: Subroutine does not return */
    sk_swift_fatal_error(sk_fatal_error_str,0xb,2,fatal_v,fatal_a,
                 sk_xnu_upcalls_swift,0x25,2,fatal_line,0);
  }
  j = 0;
  do {
    next = j + 1;
    sk_swift_elem_append(*(unsigned char *)(param_3 + 0x20 + j));
    j = next;
  } while (next != 0x100);
  uStack_88 = uStack_228;
  local_90 = local_230;
  uStack_78 = uStack_218;
  uStack_80 = uStack_220;
  uStack_68 = uStack_208;
  local_70 = local_210;
  local_60 = local_200;
  sk_swift_buf_ctx(auStack_1c0);
  sk_swift_error_build(auStack_188,auStack_1c0,&local_44);
  sk_swift_string_build(&local_270,auStack_188);
  kind = sk_swift_result_check();
  if (kind == '\x01') {
    sk_swift_collection_op(&local_238,0x66a0b0,0x65a688,0x66a0b0,0x65a5e8,0x66a708,&local_44);
    if ((char)local_238 != '\x16') {
      sk_swift_retain(&local_238,0x66a0b0,0x669c50);
      sk_swift_release(0x66a0b0,0x669c50,0,0);
      *extraout_x1_00 = (char)local_238;
      goto LAB_001919f8;
    }
  }
  else if (kind != '\0') {
    fatal_line = 3999;
    fatal_v = 0xd000000000000037;
    fatal_a = 0x80000000005cc980;
    goto LAB_00191b54;
  }
  uStack_148 = uStack_268;
  local_150 = local_270;
  uStack_138 = uStack_258;
  uStack_140 = uStack_260;
  uStack_128 = uStack_248;
  local_130 = local_250;
  local_120 = local_240;
LAB_001919f8:
  sk_swift_epilogue();
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_00191ba8 @ 0x00191ba8   (est. sk_swift_helper)
 * Ghidra: void FUN_00191ba8(undefined8 param_1,undefined1 *param_2,undefined8 param_3)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

/* WARNING: Removing unreachable block (ram,0x00191e2c) */
/* WARNING: Removing unreachable block (ram,0x00191cf0) */

void FUN_00191ba8(unsigned long param_1,unsigned char *param_2,unsigned long param_3)

{
  unsigned char uVar1;
    char kind;
  long len;
  unsigned long fatal_v;
  unsigned int *extraout_x1;
  char *extraout_x1_00;
  long ctx_err;
  char local_2a9;
  unsigned char local_2a8;
  unsigned long uStack_2a7;
  unsigned char local_270;
  unsigned long uStack_26f;
  unsigned long uStack_268;
  unsigned long uStack_260;
  unsigned long uStack_258;
  unsigned long local_250;
  unsigned long uStack_248;
  unsigned char local_240;
  unsigned int local_23c;
  unsigned char auStack_238 [56];
  unsigned char auStack_200 [56];
  unsigned char auStack_1c8 [56];
  unsigned long local_190;
  unsigned long local_150;
  unsigned long local_d0;
  unsigned long uStack_c8;
  unsigned long uStack_c0;
  unsigned long uStack_b8;
  unsigned long local_b0;
  unsigned long uStack_a8;
  unsigned char local_a0;
  
  uVar1 = *param_2;
  local_270 = uVar1;
  len = sk_swift_collection_count(&local_270,0x66a020,0x66a6f8);
  if (SCARRY8(len,0xc)) {
                    /* WARNING: Does not return */
    __builtin_trap();
  }
  if (SCARRY8(len + 0xc,8)) {
                    /* WARNING: Does not return */
    __builtin_trap();
  }
  sk_swift_frame_init(auStack_238,len + 0x14,0,&local_23c);
  if (ctx_err != 0) {
    fatal_v = sk_swift_err_code(0);
    sk_swift_release(fatal_v,FUN_0065a550,0,0);
    *extraout_x1 = local_23c;
    return;
  }
  sk_swift_string_begin(&local_270);
  sk_swift_type_hash(0x5e1ec2e31810acd2);
  sk_swift_type_arg(param_1);
  local_2a8 = uVar1;
  sk_swift_collection_init(&local_2a8,0x65a870,0x66a020,0x65a798,0x66a6f8);
  sk_swift_type_hash(param_3);
  local_d0 = CONCAT71(uStack_26f,local_270);
  uStack_c8 = uStack_268;
  uStack_b8 = uStack_258;
  uStack_c0 = uStack_260;
  uStack_a8 = uStack_248;
  local_b0 = local_250;
  local_a0 = local_240;
  sk_swift_buf_ctx(auStack_200);
  sk_swift_error_build(auStack_1c8,auStack_200,&local_23c);
  sk_swift_string_build(&local_2a8,auStack_1c8);
  kind = sk_swift_result_check();
  if (kind == '\x01') {
    sk_swift_collection_op(&local_2a9,0x66a0b0,0x65a688,0x66a0b0,0x65a5e8,0x66a708,&local_23c);
    if (local_2a9 != '\x16') {
      sk_swift_retain(&local_2a9,0x66a0b0,0x669c50);
      sk_swift_release(0x66a0b0,0x669c50,0,0);
      *extraout_x1_00 = local_2a9;
      local_150 = CONCAT71(uStack_2a7,local_2a8);
      goto LAB_00191d40;
    }
  }
  else if (kind != '\0') {
                    /* WARNING: Subroutine does not return */
    sk_swift_fatal_error(sk_fatal_error_str,0xb,2,0xd000000000000035,0x80000000005cc8e0,
                 sk_xnu_upcalls_swift,0x25,2,0xfaa,0);
  }
  local_190 = CONCAT71(uStack_2a7,local_2a8);
LAB_00191d40:
  sk_swift_epilogue();
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_00191f84 @ 0x00191f84   (est. sk_swift_helper)
 * Ghidra: ulong FUN_00191f84(undefined8 param_1,ulong param_2)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

/* WARNING: Removing unreachable block (ram,0x00192138) */

unsigned long FUN_00191f84(unsigned long param_1,unsigned long param_2)

{
  char kind;
  unsigned long err;
  unsigned int *extraout_x1;
  unsigned char *extraout_x1_00;
  long ctx_err;
  unsigned char local_219;
  unsigned long local_218;
  unsigned long uStack_210;
  unsigned long local_208;
  unsigned long uStack_200;
  unsigned long local_1f8;
  unsigned long uStack_1f0;
  unsigned char local_1e8;
  unsigned char auStack_1e0 [52];
  unsigned int local_1ac;
  unsigned char auStack_1a8 [56];
  unsigned char auStack_170 [56];
  unsigned char auStack_138 [56];
  unsigned long local_100;
  unsigned long uStack_f8;
  unsigned long uStack_f0;
  unsigned long uStack_e8;
  unsigned long local_e0;
  unsigned long uStack_d8;
  unsigned char local_d0;
  unsigned long local_c0;
  unsigned long uStack_b8;
  unsigned long uStack_b0;
  unsigned long uStack_a8;
  unsigned long local_a0;
  unsigned long uStack_98;
  unsigned char local_90;
  
  sk_swift_frame_init(auStack_1a8,0x14,0,&local_1ac);
  if (ctx_err == 0) {
    sk_swift_string_begin(auStack_1e0);
    sk_swift_type_hash(0x8c3b1ed8ac0ea38b);
    sk_swift_type_arg(param_1);
    sk_swift_type_hash(param_2);
    sk_swift_buf_ctx(auStack_170);
    sk_swift_error_build(auStack_138,auStack_170,&local_1ac);
    sk_swift_string_build(&local_218,auStack_138);
    kind = sk_swift_result_check();
    if (kind == '\0') {
      param_2 = sk_swift_result_value();
      uStack_f8 = uStack_210;
      local_100 = local_218;
      uStack_e8 = uStack_200;
      uStack_f0 = local_208;
      uStack_d8 = uStack_1f0;
      local_e0 = local_1f8;
      local_d0 = local_1e8;
      sk_swift_epilogue();
    }
    else {
      if (kind != '\x01') {
                    /* WARNING: Subroutine does not return */
        sk_swift_fatal_error(sk_fatal_error_str,0xb,2,0xd000000000000038,0x80000000005cd510,
                     sk_xnu_upcalls_swift,0x25,2,0xfc0,0);
      }
      sk_swift_collection_op(&local_219,0x66a0b0,0x65a688,0x66a0b0,0x65a5e8,0x66a708,&local_1ac);
      sk_swift_retain(&local_219,0x66a0b0,0x669c50);
      param_2 = (unsigned long)local_219;
      sk_swift_release(0x66a0b0,0x669c50,0,0);
      *extraout_x1_00 = local_219;
      uStack_b8 = uStack_210;
      local_c0 = local_218;
      uStack_a8 = uStack_200;
      uStack_b0 = local_208;
      uStack_98 = uStack_1f0;
      local_a0 = local_1f8;
      local_90 = local_1e8;
      sk_swift_epilogue();
    }
  }
  else {
    err = sk_swift_err_code(0);
    sk_swift_release(err,FUN_0065a550,0,0);
    *extraout_x1 = local_1ac;
  }
  return param_2;
}





/*--------------------------------------------------------------------*/
/* FUN_0019225c @ 0x0019225c   (est. sk_swift_helper)
 * Ghidra: uint FUN_0019225c(ulong param_1)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

/* WARNING: Removing unreachable block (ram,0x001923c4) */

unsigned int FUN_0019225c(unsigned long param_1)

{
  unsigned char bv;
  char kind;
  unsigned long res;
  unsigned int *extraout_x1;
  unsigned char *extraout_x1_00;
  long ctx_err;
  unsigned char local_219;
  unsigned long local_218;
  unsigned long uStack_210;
  unsigned long local_208;
  unsigned long uStack_200;
  unsigned long local_1f8;
  unsigned long uStack_1f0;
  unsigned char local_1e8;
  unsigned char auStack_1e0 [52];
  unsigned int local_1ac;
  unsigned char auStack_1a8 [56];
  unsigned char auStack_170 [56];
  unsigned char auStack_138 [56];
  unsigned long local_100;
  unsigned long uStack_f8;
  unsigned long uStack_f0;
  unsigned long uStack_e8;
  unsigned long local_e0;
  unsigned long uStack_d8;
  unsigned char local_d0;
  unsigned long local_c0;
  unsigned long uStack_b8;
  unsigned long uStack_b0;
  unsigned long uStack_a8;
  unsigned long local_a0;
  unsigned long uStack_98;
  unsigned char local_90;
  
  sk_swift_frame_init(auStack_1a8,0xc,0,&local_1ac);
  if (ctx_err == 0) {
    sk_swift_string_begin(auStack_1e0);
    sk_swift_type_hash(0xb703113e8f7e60c0);
    sk_swift_type_arg(param_1);
    sk_swift_buf_ctx(auStack_170);
    sk_swift_error_build(auStack_138,auStack_170,&local_1ac);
    sk_swift_string_build(&local_218,auStack_138);
    kind = sk_swift_result_check();
    if (kind == '\x01') {
      sk_swift_collection_op(&local_219,0x66a0b0,0x65a688,0x66a0b0,0x65a5e8,0x66a708,&local_1ac);
      local_219 = local_219 & 0x7f;
      sk_swift_retain(&local_219,0x66a0b0,0x669c50);
      bv = local_219;
      param_1 = (unsigned long)local_219;
      sk_swift_release(0x66a0b0,0x669c50,0,0);
      *extraout_x1_00 = bv;
      uStack_b8 = uStack_210;
      local_c0 = local_218;
      uStack_a8 = uStack_200;
      uStack_b0 = local_208;
      uStack_98 = uStack_1f0;
      local_a0 = local_1f8;
      local_90 = local_1e8;
      sk_swift_epilogue();
    }
    else {
      if (kind != '\0') {
                    /* WARNING: Subroutine does not return */
        sk_swift_fatal_error(sk_fatal_error_str,0xb,2,0xd00000000000003a,0x80000000005cd4d0,
                     sk_xnu_upcalls_swift,0x25,2,0xfcb,0);
      }
      param_1 = sk_swift_result_value2();
      uStack_f8 = uStack_210;
      local_100 = local_218;
      uStack_e8 = uStack_200;
      uStack_f0 = local_208;
      uStack_d8 = uStack_1f0;
      local_e0 = local_1f8;
      local_d0 = local_1e8;
      sk_swift_epilogue();
    }
  }
  else {
    res = sk_swift_err_code(0);
    sk_swift_release(res,FUN_0065a550,0,0);
    *extraout_x1 = local_1ac;
  }
  return (unsigned int)param_1 & 1;
}





/*--------------------------------------------------------------------*/
/* FUN_00192528 @ 0x00192528   (est. sk_swift_helper)
 * Ghidra: uint FUN_00192528(long param_1)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

/* WARNING: Removing unreachable block (ram,0x001926ec) */

unsigned int FUN_00192528(long param_1)

{
  code *pcVar3;
  long next;
  unsigned char err;
    char kind;
  long i;
  unsigned long fatal_a;
  unsigned int *extraout_x1;
  unsigned char *extraout_x1_00;
  unsigned long extraout_x1_01;
  unsigned long count;
  unsigned long count2;
  long ctx_err;
  unsigned int result;
  unsigned long fatal_line;
  unsigned long local_260;
  unsigned long uStack_258;
  unsigned long uStack_250;
  unsigned long uStack_248;
  unsigned long local_240;
  unsigned long uStack_238;
  unsigned char local_230;
  unsigned long local_228;
  unsigned long local_220;
  unsigned long uStack_218;
  unsigned long uStack_210;
  unsigned long uStack_208;
  unsigned long local_200;
  unsigned long uStack_1f8;
  unsigned char local_1f0;
  unsigned int local_1ec;
  unsigned char auStack_1e8 [56];
  unsigned char auStack_1b0 [56];
  unsigned char auStack_178 [56];
  unsigned long local_140;
  unsigned long uStack_138;
  unsigned long uStack_130;
  unsigned long uStack_128;
  unsigned long local_120;
  unsigned long uStack_118;
  unsigned char local_110;
  unsigned long local_100;
  unsigned long uStack_f8;
  unsigned long uStack_f0;
  unsigned long uStack_e8;
  unsigned long local_e0;
  unsigned long uStack_d8;
  unsigned char local_d0;
  unsigned long local_80;
  unsigned long uStack_78;
  unsigned long uStack_70;
  unsigned long uStack_68;
  unsigned long local_60;
  unsigned long uStack_58;
  unsigned char local_50;
  
  i = 8;
  while ((i != 0x2d && (count = i - 8, count != *(unsigned long *)(param_1 + 0x10)))) {
    i = i + 1;
    if (*(unsigned long *)(param_1 + 0x10) <= count) {
                    /* WARNING: Does not return */
      __builtin_trap();
    }
  }
  sk_swift_frame_init(auStack_1e8,i,0,&local_1ec);
  if (ctx_err == 0) {
    sk_swift_string_begin(&local_220);
    sk_swift_type_hash(0x354fbdd36ea90e15);
    count = *(unsigned long *)(param_1 + 0x10);
    if (count != 0x25) {
      local_260 = 0;
      uStack_258 = 0xe000000000000000;
      sk_swift_precond_1(0x3b);
      sk_swift_precond_2(0xd000000000000019,0x80000000005cd420);
      sk_swift_precond_2(0xd000000000000037,0x80000000005cd440);
      local_228 = count;
      pcVar3 = (code *)sk_swift_meta(0x6720e0);
      (*pcVar3)(0x677880,0x6720e0);
      sk_swift_precond_2();
      sk_swift_abort_tail(extraout_x1_01);
      fatal_line = 0x4ac;
      fatal_a = local_260;
      count = uStack_258;
LAB_001928cc:
                    /* WARNING: Subroutine does not return */
      sk_swift_fatal_error(sk_fatal_error_str,0xb,2,fatal_a,count,
                   sk_xnu_upcalls_swift,0x25,2,fatal_line,0);
    }
    i = 0;
    do {
      next = i + 1;
      sk_swift_elem_append(*(unsigned char *)(param_1 + 0x20 + i));
      i = next;
    } while (next != 0x25);
    uStack_78 = uStack_218;
    local_80 = local_220;
    uStack_68 = uStack_208;
    uStack_70 = uStack_210;
    uStack_58 = uStack_1f8;
    local_60 = local_200;
    local_50 = local_1f0;
    sk_swift_buf_ctx(auStack_1b0);
    sk_swift_error_build(auStack_178,auStack_1b0,&local_1ec);
    sk_swift_string_build(&local_260,auStack_178);
    kind = sk_swift_result_check();
    if (kind == '\x01') {
      sk_swift_collection_op(&local_228,0x66a0b0,0x65a688,0x66a0b0,0x65a5e8,0x66a708,&local_1ec);
      local_228 = local_228 & 0xffffffffffffff7f;
      sk_swift_retain(&local_228,0x66a0b0,0x669c50);
      err = (unsigned char)local_228;
      result = (unsigned int)local_228 & 0xff;
      sk_swift_release(0x66a0b0,0x669c50,0,0);
      *extraout_x1_00 = err;
      uStack_f8 = uStack_258;
      local_100 = local_260;
      uStack_e8 = uStack_248;
      uStack_f0 = uStack_250;
      uStack_d8 = uStack_238;
      local_e0 = local_240;
      local_d0 = local_230;
      sk_swift_epilogue();
    }
    else {
      if (kind != '\0') {
        fatal_line = 0xfd6;
        fatal_a = 0xd000000000000041;
        count = 0x80000000005cd480;
        goto LAB_001928cc;
      }
      result = sk_swift_result_value2();
      uStack_138 = uStack_258;
      local_140 = local_260;
      uStack_128 = uStack_248;
      uStack_130 = uStack_250;
      uStack_118 = uStack_238;
      local_120 = local_240;
      local_110 = local_230;
      sk_swift_epilogue();
    }
  }
  else {
    fatal_a = sk_swift_err_code(0);
    sk_swift_release(fatal_a,FUN_0065a550,0,0);
    *extraout_x1 = local_1ec;
  }
  return result & 1;
}





/*--------------------------------------------------------------------*/
/* FUN_00192920 @ 0x00192920   (est. sk_swift_helper)
 * Ghidra: void FUN_00192920(undefined8 param_1,undefined8 param_2)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

/* WARNING: Removing unreachable block (ram,0x00192a94) */

void FUN_00192920(unsigned long param_1,unsigned long param_2)

{
  char kind;
  unsigned long err;
  unsigned int *extraout_x1;
  char *extraout_x1_00;
  long ctx_err;
  char local_219;
  unsigned long local_218;
  unsigned long uStack_210;
  unsigned long local_208;
  unsigned long uStack_200;
  unsigned long local_1f8;
  unsigned long uStack_1f0;
  unsigned char local_1e8;
  unsigned char auStack_1e0 [52];
  unsigned int local_1ac;
  unsigned char auStack_1a8 [56];
  unsigned char auStack_170 [56];
  unsigned char auStack_138 [56];
  unsigned long local_100;
  unsigned long uStack_f8;
  unsigned long uStack_f0;
  unsigned long uStack_e8;
  unsigned long local_e0;
  unsigned long uStack_d8;
  unsigned char local_d0;
  
  sk_swift_frame_init(auStack_1a8,0x14,0,&local_1ac);
  if (ctx_err != 0) {
    err = sk_swift_err_code(0);
    sk_swift_release(err,FUN_0065a550,0,0);
    *extraout_x1 = local_1ac;
    return;
  }
  sk_swift_string_begin(auStack_1e0);
  sk_swift_type_hash(0x468f71bf1dc3389f);
  sk_swift_type_hash(param_1);
  sk_swift_type_arg2(param_2);
  sk_swift_buf_ctx(auStack_170);
  sk_swift_error_build(auStack_138,auStack_170,&local_1ac);
  sk_swift_string_build(&local_218,auStack_138);
  kind = sk_swift_result_check();
  if (kind == '\x01') {
    sk_swift_collection_op(&local_219,0x66a140,0x65a688,0x66a140,0x65a5e8,FUN_0066a720,&local_1ac);
    if (local_219 != '\x02') {
      sk_swift_retain(&local_219,0x66a140,0x669c90);
      sk_swift_release(0x66a140,0x669c90,0,0);
      *extraout_x1_00 = local_219;
      goto LAB_00192b10;
    }
  }
  else if (kind != '\0') {
                    /* WARNING: Subroutine does not return */
    sk_swift_fatal_error(sk_fatal_error_str,0xb,2,0xd00000000000003c,0x80000000005cd3e0,
                 sk_xnu_upcalls_swift,0x25,2,0xfe8,0);
  }
  uStack_f8 = uStack_210;
  local_100 = local_218;
  uStack_e8 = uStack_200;
  uStack_f0 = local_208;
  uStack_d8 = uStack_1f0;
  local_e0 = local_1f8;
  local_d0 = local_1e8;
LAB_00192b10:
  sk_swift_epilogue();
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_00192bec @ 0x00192bec   (est. sk_swift_helper)
 * Ghidra: void FUN_00192bec(undefined8 param_1,undefined8 param_2)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

/* WARNING: Removing unreachable block (ram,0x00192d60) */

void FUN_00192bec(unsigned long param_1,unsigned long param_2)

{
  char kind;
  unsigned long err;
  unsigned int *extraout_x1;
  char *extraout_x1_00;
  long ctx_err;
  char local_219;
  unsigned long local_218;
  unsigned long uStack_210;
  unsigned long local_208;
  unsigned long uStack_200;
  unsigned long local_1f8;
  unsigned long uStack_1f0;
  unsigned char local_1e8;
  unsigned char auStack_1e0 [52];
  unsigned int local_1ac;
  unsigned char auStack_1a8 [56];
  unsigned char auStack_170 [56];
  unsigned char auStack_138 [56];
  unsigned long local_100;
  unsigned long uStack_f8;
  unsigned long uStack_f0;
  unsigned long uStack_e8;
  unsigned long local_e0;
  unsigned long uStack_d8;
  unsigned char local_d0;
  
  sk_swift_frame_init(auStack_1a8,0x14,0,&local_1ac);
  if (ctx_err != 0) {
    err = sk_swift_err_code(0);
    sk_swift_release(err,FUN_0065a550,0,0);
    *extraout_x1 = local_1ac;
    return;
  }
  sk_swift_string_begin(auStack_1e0);
  sk_swift_type_hash(0xb3f78ae18e196479);
  sk_swift_type_hash(param_1);
  sk_swift_type_arg2(param_2);
  sk_swift_buf_ctx(auStack_170);
  sk_swift_error_build(auStack_138,auStack_170,&local_1ac);
  sk_swift_string_build(&local_218,auStack_138);
  kind = sk_swift_result_check();
  if (kind == '\x01') {
    sk_swift_collection_op(&local_219,0x66a140,0x65a688,0x66a140,0x65a5e8,FUN_0066a720,&local_1ac);
    if (local_219 != '\x02') {
      sk_swift_retain(&local_219,0x66a140,0x669c90);
      sk_swift_release(0x66a140,0x669c90,0,0);
      *extraout_x1_00 = local_219;
      goto LAB_00192ddc;
    }
  }
  else if (kind != '\0') {
                    /* WARNING: Subroutine does not return */
    sk_swift_fatal_error(sk_fatal_error_str,0xb,2,0xd00000000000003a,0x80000000005cd3a0,
                 sk_xnu_upcalls_swift,0x25,2,0xff3,0);
  }
  uStack_f8 = uStack_210;
  local_100 = local_218;
  uStack_e8 = uStack_200;
  uStack_f0 = local_208;
  uStack_d8 = uStack_1f0;
  local_e0 = local_1f8;
  local_d0 = local_1e8;
LAB_00192ddc:
  sk_swift_epilogue();
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_00192eb8 @ 0x00192eb8   (est. sk_swift_helper)
 * Ghidra: void FUN_00192eb8(undefined8 param_1,undefined8 param_2)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

/* WARNING: Removing unreachable block (ram,0x0019302c) */

void FUN_00192eb8(unsigned long param_1,unsigned long param_2)

{
  char kind;
  unsigned long err;
  unsigned int *extraout_x1;
  char *extraout_x1_00;
  long ctx_err;
  char local_219;
  unsigned long local_218;
  unsigned long uStack_210;
  unsigned long local_208;
  unsigned long uStack_200;
  unsigned long local_1f8;
  unsigned long uStack_1f0;
  unsigned char local_1e8;
  unsigned char auStack_1e0 [52];
  unsigned int local_1ac;
  unsigned char auStack_1a8 [56];
  unsigned char auStack_170 [56];
  unsigned char auStack_138 [56];
  unsigned long local_100;
  unsigned long uStack_f8;
  unsigned long uStack_f0;
  unsigned long uStack_e8;
  unsigned long local_e0;
  unsigned long uStack_d8;
  unsigned char local_d0;
  
  sk_swift_frame_init(auStack_1a8,0x14,0,&local_1ac);
  if (ctx_err != 0) {
    err = sk_swift_err_code(0);
    sk_swift_release(err,FUN_0065a550,0,0);
    *extraout_x1 = local_1ac;
    return;
  }
  sk_swift_string_begin(auStack_1e0);
  sk_swift_type_hash(0xea57b9000984e727);
  sk_swift_type_hash(param_1);
  sk_swift_type_arg2(param_2);
  sk_swift_buf_ctx(auStack_170);
  sk_swift_error_build(auStack_138,auStack_170,&local_1ac);
  sk_swift_string_build(&local_218,auStack_138);
  kind = sk_swift_result_check();
  if (kind == '\x01') {
    sk_swift_collection_op(&local_219,0x66a140,0x65a688,0x66a140,0x65a5e8,FUN_0066a720,&local_1ac);
    if (local_219 != '\x02') {
      sk_swift_retain(&local_219,0x66a140,0x669c90);
      sk_swift_release(0x66a140,0x669c90,0,0);
      *extraout_x1_00 = local_219;
      goto LAB_001930a8;
    }
  }
  else if (kind != '\0') {
                    /* WARNING: Subroutine does not return */
    sk_swift_fatal_error(sk_fatal_error_str,0xb,2,0xd00000000000003a,0x80000000005cd360,
                 sk_xnu_upcalls_swift,0x25,2,0xffe,0);
  }
  uStack_f8 = uStack_210;
  local_100 = local_218;
  uStack_e8 = uStack_200;
  uStack_f0 = local_208;
  uStack_d8 = uStack_1f0;
  local_e0 = local_1f8;
  local_d0 = local_1e8;
LAB_001930a8:
  sk_swift_epilogue();
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_00193184 @ 0x00193184   (est. sk_swift_helper)
 * Ghidra: void FUN_00193184(undefined8 param_1,undefined8 param_2)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

/* WARNING: Removing unreachable block (ram,0x001932f8) */

void FUN_00193184(unsigned long param_1,unsigned long param_2)

{
  char kind;
  unsigned long err;
  unsigned int *extraout_x1;
  char *extraout_x1_00;
  long ctx_err;
  char local_219;
  unsigned long local_218;
  unsigned long uStack_210;
  unsigned long local_208;
  unsigned long uStack_200;
  unsigned long local_1f8;
  unsigned long uStack_1f0;
  unsigned char local_1e8;
  unsigned char auStack_1e0 [52];
  unsigned int local_1ac;
  unsigned char auStack_1a8 [56];
  unsigned char auStack_170 [56];
  unsigned char auStack_138 [56];
  unsigned long local_100;
  unsigned long uStack_f8;
  unsigned long uStack_f0;
  unsigned long uStack_e8;
  unsigned long local_e0;
  unsigned long uStack_d8;
  unsigned char local_d0;
  
  sk_swift_frame_init(auStack_1a8,0x14,0,&local_1ac);
  if (ctx_err != 0) {
    err = sk_swift_err_code(0);
    sk_swift_release(err,FUN_0065a550,0,0);
    *extraout_x1 = local_1ac;
    return;
  }
  sk_swift_string_begin(auStack_1e0);
  sk_swift_type_hash(0xb23bbd335dd2ce8a);
  sk_swift_type_hash(param_1);
  sk_swift_type_arg2(param_2);
  sk_swift_buf_ctx(auStack_170);
  sk_swift_error_build(auStack_138,auStack_170,&local_1ac);
  sk_swift_string_build(&local_218,auStack_138);
  kind = sk_swift_result_check();
  if (kind == '\x01') {
    sk_swift_collection_op(&local_219,0x66a140,0x65a688,0x66a140,0x65a5e8,FUN_0066a720,&local_1ac);
    if (local_219 != '\x02') {
      sk_swift_retain(&local_219,0x66a140,0x669c90);
      sk_swift_release(0x66a140,0x669c90,0,0);
      *extraout_x1_00 = local_219;
      goto LAB_00193374;
    }
  }
  else if (kind != '\0') {
                    /* WARNING: Subroutine does not return */
    sk_swift_fatal_error(sk_fatal_error_str,0xb,2,0xd00000000000003b,0x80000000005cd320,
                 sk_xnu_upcalls_swift,0x25,2,0x1009,0);
  }
  uStack_f8 = uStack_210;
  local_100 = local_218;
  uStack_e8 = uStack_200;
  uStack_f0 = local_208;
  uStack_d8 = uStack_1f0;
  local_e0 = local_1f8;
  local_d0 = local_1e8;
LAB_00193374:
  sk_swift_epilogue();
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_00193450 @ 0x00193450   (est. sk_swift_helper)
 * Ghidra: ulong FUN_00193450(ulong param_1)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

/* WARNING: Removing unreachable block (ram,0x001935f4) */

unsigned long FUN_00193450(unsigned long param_1)

{
  char kind;
  unsigned long err;
  unsigned int *extraout_x1;
  unsigned char *extraout_x1_00;
  long ctx_err;
  unsigned char local_219;
  unsigned long local_218;
  unsigned long uStack_210;
  unsigned long local_208;
  unsigned long uStack_200;
  unsigned long local_1f8;
  unsigned long uStack_1f0;
  unsigned char local_1e8;
  unsigned char auStack_1e0 [52];
  unsigned int local_1ac;
  unsigned char auStack_1a8 [56];
  unsigned char auStack_170 [56];
  unsigned char auStack_138 [56];
  unsigned long local_100;
  unsigned long uStack_f8;
  unsigned long uStack_f0;
  unsigned long uStack_e8;
  unsigned long local_e0;
  unsigned long uStack_d8;
  unsigned char local_d0;
  unsigned long local_c0;
  unsigned long uStack_b8;
  unsigned long uStack_b0;
  unsigned long uStack_a8;
  unsigned long local_a0;
  unsigned long uStack_98;
  unsigned char local_90;
  
  sk_swift_frame_init(auStack_1a8,0x10,0,&local_1ac);
  if (ctx_err == 0) {
    sk_swift_string_begin(auStack_1e0);
    sk_swift_type_hash(0xd6ba7174c8c8484f);
    sk_swift_type_hash(param_1);
    sk_swift_buf_ctx(auStack_170);
    sk_swift_error_build(auStack_138,auStack_170,&local_1ac);
    sk_swift_string_build(&local_218,auStack_138);
    kind = sk_swift_result_check();
    if (kind == '\0') {
      param_1 = FUN_000218a4();
      uStack_f8 = uStack_210;
      local_100 = local_218;
      uStack_e8 = uStack_200;
      uStack_f0 = local_208;
      uStack_d8 = uStack_1f0;
      local_e0 = local_1f8;
      local_d0 = local_1e8;
      sk_swift_epilogue();
    }
    else {
      if (kind != '\x01') {
                    /* WARNING: Subroutine does not return */
        sk_swift_fatal_error(sk_fatal_error_str,0xb,2,0xd00000000000003e,0x80000000005cd2e0,
                     sk_xnu_upcalls_swift,0x25,2,0x1014,0);
      }
      sk_swift_collection_op(&local_219,0x66a140,0x65a688,0x66a140,0x65a5e8,FUN_0066a720,&local_1ac);
      sk_swift_retain(&local_219,0x66a140,0x669c90);
      param_1 = (unsigned long)local_219;
      sk_swift_release(0x66a140,0x669c90,0,0);
      *extraout_x1_00 = local_219;
      uStack_b8 = uStack_210;
      local_c0 = local_218;
      uStack_a8 = uStack_200;
      uStack_b0 = local_208;
      uStack_98 = uStack_1f0;
      local_a0 = local_1f8;
      local_90 = local_1e8;
      sk_swift_epilogue();
    }
  }
  else {
    err = sk_swift_err_code(0);
    sk_swift_release(err,FUN_0065a550,0,0);
    *extraout_x1 = local_1ac;
  }
  return param_1;
}





/*--------------------------------------------------------------------*/
/* FUN_00193718 @ 0x00193718   (est. sk_swift_helper)
 * Ghidra: void FUN_00193718(undefined8 param_1,undefined8 param_2)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

/* WARNING: Removing unreachable block (ram,0x0019388c) */

void FUN_00193718(unsigned long param_1,unsigned long param_2)

{
  char kind;
  unsigned long err;
  unsigned int *extraout_x1;
  char *extraout_x1_00;
  long ctx_err;
  char local_219;
  unsigned long local_218;
  unsigned long uStack_210;
  unsigned long local_208;
  unsigned long uStack_200;
  unsigned long local_1f8;
  unsigned long uStack_1f0;
  unsigned char local_1e8;
  unsigned char auStack_1e0 [52];
  unsigned int local_1ac;
  unsigned char auStack_1a8 [56];
  unsigned char auStack_170 [56];
  unsigned char auStack_138 [56];
  unsigned long local_100;
  unsigned long uStack_f8;
  unsigned long uStack_f0;
  unsigned long uStack_e8;
  unsigned long local_e0;
  unsigned long uStack_d8;
  unsigned char local_d0;
  
  sk_swift_frame_init(auStack_1a8,0x14,0,&local_1ac);
  if (ctx_err != 0) {
    err = sk_swift_err_code(0);
    sk_swift_release(err,FUN_0065a550,0,0);
    *extraout_x1 = local_1ac;
    return;
  }
  sk_swift_string_begin(auStack_1e0);
  sk_swift_type_hash(0xddc7d7362bd70ae2);
  sk_swift_type_hash(param_1);
  sk_swift_type_arg(param_2);
  sk_swift_buf_ctx(auStack_170);
  sk_swift_error_build(auStack_138,auStack_170,&local_1ac);
  sk_swift_string_build(&local_218,auStack_138);
  kind = sk_swift_result_check();
  if (kind == '\x01') {
    sk_swift_collection_op(&local_219,0x66a140,0x65a688,0x66a140,0x65a5e8,FUN_0066a720,&local_1ac);
    if (local_219 != '\x02') {
      sk_swift_retain(&local_219,0x66a140,0x669c90);
      sk_swift_release(0x66a140,0x669c90,0,0);
      *extraout_x1_00 = local_219;
      goto LAB_00193908;
    }
  }
  else if (kind != '\0') {
                    /* WARNING: Subroutine does not return */
    sk_swift_fatal_error(sk_fatal_error_str,0xb,2,0xd00000000000003c,0x80000000005cd2a0,
                 sk_xnu_upcalls_swift,0x25,2,0x101f,0);
  }
  uStack_f8 = uStack_210;
  local_100 = local_218;
  uStack_e8 = uStack_200;
  uStack_f0 = local_208;
  uStack_d8 = uStack_1f0;
  local_e0 = local_1f8;
  local_d0 = local_1e8;
LAB_00193908:
  sk_swift_epilogue();
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_001939e4 @ 0x001939e4   (est. sk_swift_helper)
 * Ghidra: void FUN_001939e4(undefined8 param_1,undefined8 param_2)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

/* WARNING: Removing unreachable block (ram,0x00193b58) */

void FUN_001939e4(unsigned long param_1,unsigned long param_2)

{
  char kind;
  unsigned long err;
  unsigned int *extraout_x1;
  char *extraout_x1_00;
  long ctx_err;
  char local_219;
  unsigned long local_218;
  unsigned long uStack_210;
  unsigned long local_208;
  unsigned long uStack_200;
  unsigned long local_1f8;
  unsigned long uStack_1f0;
  unsigned char local_1e8;
  unsigned char auStack_1e0 [52];
  unsigned int local_1ac;
  unsigned char auStack_1a8 [56];
  unsigned char auStack_170 [56];
  unsigned char auStack_138 [56];
  unsigned long local_100;
  unsigned long uStack_f8;
  unsigned long uStack_f0;
  unsigned long uStack_e8;
  unsigned long local_e0;
  unsigned long uStack_d8;
  unsigned char local_d0;
  
  sk_swift_frame_init(auStack_1a8,0x14,0,&local_1ac);
  if (ctx_err != 0) {
    err = sk_swift_err_code(0);
    sk_swift_release(err,FUN_0065a550,0,0);
    *extraout_x1 = local_1ac;
    return;
  }
  sk_swift_string_begin(auStack_1e0);
  sk_swift_type_hash(0x700b019333a9a603);
  sk_swift_type_hash(param_1);
  sk_swift_type_arg(param_2);
  sk_swift_buf_ctx(auStack_170);
  sk_swift_error_build(auStack_138,auStack_170,&local_1ac);
  sk_swift_string_build(&local_218,auStack_138);
  kind = sk_swift_result_check();
  if (kind == '\x01') {
    sk_swift_collection_op(&local_219,0x66a140,0x65a688,0x66a140,0x65a5e8,FUN_0066a720,&local_1ac);
    if (local_219 != '\x02') {
      sk_swift_retain(&local_219,0x66a140,0x669c90);
      sk_swift_release(0x66a140,0x669c90,0,0);
      *extraout_x1_00 = local_219;
      goto LAB_00193bd4;
    }
  }
  else if (kind != '\0') {
                    /* WARNING: Subroutine does not return */
    sk_swift_fatal_error(sk_fatal_error_str,0xb,2,0xd00000000000003c,0x80000000005cd260,
                 sk_xnu_upcalls_swift,0x25,2,0x102a,0);
  }
  uStack_f8 = uStack_210;
  local_100 = local_218;
  uStack_e8 = uStack_200;
  uStack_f0 = local_208;
  uStack_d8 = uStack_1f0;
  local_e0 = local_1f8;
  local_d0 = local_1e8;
LAB_00193bd4:
  sk_swift_epilogue();
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_00193cb0 @ 0x00193cb0   (est. sk_swift_helper)
 * Ghidra: void FUN_00193cb0(undefined8 param_1,undefined8 param_2)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

/* WARNING: Removing unreachable block (ram,0x00193e24) */

void FUN_00193cb0(unsigned long param_1,unsigned long param_2)

{
  char kind;
  unsigned long err;
  unsigned int *extraout_x1;
  char *extraout_x1_00;
  long ctx_err;
  char local_219;
  unsigned long local_218;
  unsigned long uStack_210;
  unsigned long local_208;
  unsigned long uStack_200;
  unsigned long local_1f8;
  unsigned long uStack_1f0;
  unsigned char local_1e8;
  unsigned char auStack_1e0 [52];
  unsigned int local_1ac;
  unsigned char auStack_1a8 [56];
  unsigned char auStack_170 [56];
  unsigned char auStack_138 [56];
  unsigned long local_100;
  unsigned long uStack_f8;
  unsigned long uStack_f0;
  unsigned long uStack_e8;
  unsigned long local_e0;
  unsigned long uStack_d8;
  unsigned char local_d0;
  
  sk_swift_frame_init(auStack_1a8,0x14,0,&local_1ac);
  if (ctx_err != 0) {
    err = sk_swift_err_code(0);
    sk_swift_release(err,FUN_0065a550,0,0);
    *extraout_x1 = local_1ac;
    return;
  }
  sk_swift_string_begin(auStack_1e0);
  sk_swift_type_hash(0x2e8fa16c3f4ec122);
  sk_swift_type_hash(param_1);
  sk_swift_type_arg(param_2);
  sk_swift_buf_ctx(auStack_170);
  sk_swift_error_build(auStack_138,auStack_170,&local_1ac);
  sk_swift_string_build(&local_218,auStack_138);
  kind = sk_swift_result_check();
  if (kind == '\x01') {
    sk_swift_collection_op(&local_219,0x66a140,0x65a688,0x66a140,0x65a5e8,FUN_0066a720,&local_1ac);
    if (local_219 != '\x02') {
      sk_swift_retain(&local_219,0x66a140,0x669c90);
      sk_swift_release(0x66a140,0x669c90,0,0);
      *extraout_x1_00 = local_219;
      goto LAB_00193ea0;
    }
  }
  else if (kind != '\0') {
                    /* WARNING: Subroutine does not return */
    sk_swift_fatal_error(sk_fatal_error_str,0xb,2,0xd00000000000003d,0x80000000005cd220,
                 sk_xnu_upcalls_swift,0x25,2,0x1035,0);
  }
  uStack_f8 = uStack_210;
  local_100 = local_218;
  uStack_e8 = uStack_200;
  uStack_f0 = local_208;
  uStack_d8 = uStack_1f0;
  local_e0 = local_1f8;
  local_d0 = local_1e8;
LAB_00193ea0:
  sk_swift_epilogue();
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_00193f7c @ 0x00193f7c   (est. sk_swift_helper)
 * Ghidra: uint FUN_00193f7c(undefined8 param_1,undefined8 param_2,undefined1 *param_3)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

/* WARNING: Removing unreachable block (ram,0x00194210) */
/* WARNING: Removing unreachable block (ram,0x001940d8) */

unsigned int FUN_00193f7c(unsigned long param_1,unsigned long param_2,unsigned char *param_3)

{
  unsigned int uVar1;
  unsigned int err;
  unsigned char res;
  unsigned char bVar4;
    char cVar6;
  unsigned int count;
  long j;
  unsigned long fatal_line;
  unsigned int *extraout_x1;
  unsigned char *extraout_x1_00;
  long ctx_err;
  unsigned char local_2c9;
  unsigned int local_2c8;
  unsigned int uStack_2c4;
  unsigned int uStack_2c0;
  unsigned int uStack_2bc;
  unsigned long local_2b8;
  unsigned long uStack_2b0;
  unsigned long local_2a8;
  unsigned long uStack_2a0;
  unsigned char local_298;
  unsigned int local_290;
  unsigned int uStack_28c;
  unsigned int uStack_288;
  unsigned int uStack_284;
  unsigned long uStack_280;
  unsigned long uStack_278;
  unsigned long local_270;
  unsigned long uStack_268;
  unsigned char local_260;
  unsigned int local_25c;
  unsigned char auStack_258 [56];
  unsigned char auStack_220 [56];
  unsigned char auStack_1e8 [56];
  unsigned long local_1b0;
  unsigned long uStack_1a8;
  unsigned long uStack_1a0;
  unsigned long uStack_198;
  unsigned long local_190;
  unsigned long uStack_188;
  unsigned char local_180;
  unsigned long local_170;
  unsigned long uStack_168;
  unsigned long local_f0;
  unsigned long uStack_e8;
  unsigned long uStack_e0;
  unsigned long uStack_d8;
  unsigned long local_d0;
  unsigned long uStack_c8;
  unsigned char local_c0;
  
  res = *param_3;
  uVar1 = *(unsigned int *)(param_3 + 4);
  err = *(unsigned int *)(param_3 + 8);
  local_290 = CONCAT31(local_290,res);
  uStack_28c = uVar1;
  uStack_288 = err;
  j = sk_swift_collection_count(&local_290,0x66a248,0x66a758);
  if (SCARRY8(j,0x14)) {
                    /* WARNING: Does not return */
    __builtin_trap();
  }
  sk_swift_frame_init(auStack_258,j + 0x14,0,&local_25c);
  if (ctx_err == 0) {
    sk_swift_string_begin(&local_290);
    sk_swift_type_hash(0xd94ea1976e2c6fe1);
    sk_swift_type_hash(param_1);
    sk_swift_type_arg(param_2);
    local_2c8 = CONCAT31(local_2c8,res);
    uStack_2c4 = uVar1;
    uStack_2c0 = err;
    sk_swift_collection_init(&local_2c8,0x65a870,0x66a248,0x65a798,0x66a758);
    uStack_e8 = CONCAT44(uStack_284,uStack_288);
    local_f0 = CONCAT44(uStack_28c,local_290);
    uStack_d8 = uStack_278;
    uStack_e0 = uStack_280;
    uStack_c8 = uStack_268;
    local_d0 = local_270;
    local_c0 = local_260;
    sk_swift_buf_ctx(auStack_220);
    sk_swift_error_build(auStack_1e8,auStack_220,&local_25c);
    sk_swift_string_build(&local_2c8,auStack_1e8);
    cVar6 = sk_swift_result_check();
    if (cVar6 == '\x01') {
      sk_swift_collection_op(&local_2c9,0x66a140,0x65a688,0x66a140,0x65a5e8,FUN_0066a720,&local_25c);
      local_2c9 = local_2c9 & 0x7f;
      sk_swift_retain(&local_2c9,0x66a140,0x669c90);
      bVar4 = local_2c9;
      sk_swift_release(0x66a140,0x669c90,0,0);
      *extraout_x1_00 = bVar4;
      uStack_168 = CONCAT44(uStack_2bc,uStack_2c0);
      local_170 = CONCAT44(uStack_2c4,local_2c8);
      count = (unsigned int)bVar4;
      sk_swift_epilogue();
    }
    else {
      if (cVar6 != '\0') {
                    /* WARNING: Subroutine does not return */
        sk_swift_fatal_error(sk_fatal_error_str,0xb,2,0xd000000000000040,0x80000000005cd1d0,
                     sk_xnu_upcalls_swift,0x25,2,0x1040,0);
      }
      count = sk_swift_result_value2();
      uStack_1a8 = CONCAT44(uStack_2bc,uStack_2c0);
      local_1b0 = CONCAT44(uStack_2c4,local_2c8);
      uStack_198 = uStack_2b0;
      uStack_1a0 = local_2b8;
      uStack_188 = uStack_2a0;
      local_190 = local_2a8;
      local_180 = local_298;
      sk_swift_epilogue();
    }
  }
  else {
    count = (unsigned int)param_2;
    fatal_line = sk_swift_err_code(0);
    sk_swift_release(fatal_line,FUN_0065a550,0,0);
    *extraout_x1 = local_25c;
  }
  return count & 1;
}





/*--------------------------------------------------------------------*/
/* FUN_00194370 @ 0x00194370   (est. sk_swift_helper)
 * Ghidra: void FUN_00194370(undefined8 param_1,undefined8 param_2)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

/* WARNING: Removing unreachable block (ram,0x001944e4) */

void FUN_00194370(unsigned long param_1,unsigned long param_2)

{
  char kind;
  unsigned long err;
  unsigned int *extraout_x1;
  char *extraout_x1_00;
  long ctx_err;
  char local_219;
  unsigned long local_218;
  unsigned long uStack_210;
  unsigned long local_208;
  unsigned long uStack_200;
  unsigned long local_1f8;
  unsigned long uStack_1f0;
  unsigned char local_1e8;
  unsigned char auStack_1e0 [52];
  unsigned int local_1ac;
  unsigned char auStack_1a8 [56];
  unsigned char auStack_170 [56];
  unsigned char auStack_138 [56];
  unsigned long local_100;
  unsigned long uStack_f8;
  unsigned long uStack_f0;
  unsigned long uStack_e8;
  unsigned long local_e0;
  unsigned long uStack_d8;
  unsigned char local_d0;
  
  sk_swift_frame_init(auStack_1a8,0x14,0,&local_1ac);
  if (ctx_err != 0) {
    err = sk_swift_err_code(0);
    sk_swift_release(err,FUN_0065a550,0,0);
    *extraout_x1 = local_1ac;
    return;
  }
  sk_swift_string_begin(auStack_1e0);
  sk_swift_type_hash(0x6f5e4451479a40dd);
  sk_swift_type_hash(param_1);
  sk_swift_type_arg(param_2);
  sk_swift_buf_ctx(auStack_170);
  sk_swift_error_build(auStack_138,auStack_170,&local_1ac);
  sk_swift_string_build(&local_218,auStack_138);
  kind = sk_swift_result_check();
  if (kind == '\x01') {
    sk_swift_collection_op(&local_219,0x66a140,0x65a688,0x66a140,0x65a5e8,FUN_0066a720,&local_1ac);
    if (local_219 != '\x02') {
      sk_swift_retain(&local_219,0x66a140,0x669c90);
      sk_swift_release(0x66a140,0x669c90,0,0);
      *extraout_x1_00 = local_219;
      goto LAB_00194560;
    }
  }
  else if (kind != '\0') {
                    /* WARNING: Subroutine does not return */
    sk_swift_fatal_error(sk_fatal_error_str,0xb,2,0xd000000000000043,0x80000000005cd180,
                 sk_xnu_upcalls_swift,0x25,2,0x104b,0);
  }
  uStack_f8 = uStack_210;
  local_100 = local_218;
  uStack_e8 = uStack_200;
  uStack_f0 = local_208;
  uStack_d8 = uStack_1f0;
  local_e0 = local_1f8;
  local_d0 = local_1e8;
LAB_00194560:
  sk_swift_epilogue();
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019463c @ 0x0019463c   (est. sk_swift_helper)
 * Ghidra: void FUN_0019463c(undefined8 param_1)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

/* WARNING: Removing unreachable block (ram,0x001947a0) */

void FUN_0019463c(unsigned long param_1)

{
  char kind;
  unsigned long err;
  unsigned int *extraout_x1;
  char *extraout_x1_00;
  long ctx_err;
  char local_219;
  unsigned long local_218;
  unsigned long uStack_210;
  unsigned long local_208;
  unsigned long uStack_200;
  unsigned long local_1f8;
  unsigned long uStack_1f0;
  unsigned char local_1e8;
  unsigned char auStack_1e0 [52];
  unsigned int local_1ac;
  unsigned char auStack_1a8 [56];
  unsigned char auStack_170 [56];
  unsigned char auStack_138 [56];
  unsigned long local_100;
  unsigned long uStack_f8;
  unsigned long uStack_f0;
  unsigned long uStack_e8;
  unsigned long local_e0;
  unsigned long uStack_d8;
  unsigned char local_d0;
  
  sk_swift_frame_init(auStack_1a8,0x10,0,&local_1ac);
  if (ctx_err != 0) {
    err = sk_swift_err_code(0);
    sk_swift_release(err,FUN_0065a550,0,0);
    *extraout_x1 = local_1ac;
    return;
  }
  sk_swift_string_begin(auStack_1e0);
  sk_swift_type_hash(0x9b4a0ff72a061617);
  sk_swift_type_hash(param_1);
  sk_swift_buf_ctx(auStack_170);
  sk_swift_error_build(auStack_138,auStack_170,&local_1ac);
  sk_swift_string_build(&local_218,auStack_138);
  kind = sk_swift_result_check();
  if (kind == '\x01') {
    sk_swift_collection_op(&local_219,0x66a140,0x65a688,0x66a140,0x65a5e8,FUN_0066a720,&local_1ac);
    if (local_219 != '\x02') {
      sk_swift_retain(&local_219,0x66a140,0x669c90);
      sk_swift_release(0x66a140,0x669c90,0,0);
      *extraout_x1_00 = local_219;
      goto LAB_0019481c;
    }
  }
  else if (kind != '\0') {
                    /* WARNING: Subroutine does not return */
    sk_swift_fatal_error(sk_fatal_error_str,0xb,2,0xd00000000000003d,0x80000000005cd140,
                 sk_xnu_upcalls_swift,0x25,2,0x1056,0);
  }
  uStack_f8 = uStack_210;
  local_100 = local_218;
  uStack_e8 = uStack_200;
  uStack_f0 = local_208;
  uStack_d8 = uStack_1f0;
  local_e0 = local_1f8;
  local_d0 = local_1e8;
LAB_0019481c:
  sk_swift_epilogue();
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_001948f8 @ 0x001948f8   (est. sk_swift_helper)
 * Ghidra: void FUN_001948f8(undefined8 param_1)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

/* WARNING: Removing unreachable block (ram,0x00194a5c) */

void FUN_001948f8(unsigned long param_1)

{
  char kind;
  unsigned long err;
  unsigned int *extraout_x1;
  char *extraout_x1_00;
  long ctx_err;
  char local_219;
  unsigned long local_218;
  unsigned long uStack_210;
  unsigned long local_208;
  unsigned long uStack_200;
  unsigned long local_1f8;
  unsigned long uStack_1f0;
  unsigned char local_1e8;
  unsigned char auStack_1e0 [52];
  unsigned int local_1ac;
  unsigned char auStack_1a8 [56];
  unsigned char auStack_170 [56];
  unsigned char auStack_138 [56];
  unsigned long local_100;
  unsigned long uStack_f8;
  unsigned long uStack_f0;
  unsigned long uStack_e8;
  unsigned long local_e0;
  unsigned long uStack_d8;
  unsigned char local_d0;
  
  sk_swift_frame_init(auStack_1a8,0x10,0,&local_1ac);
  if (ctx_err != 0) {
    err = sk_swift_err_code(0);
    sk_swift_release(err,FUN_0065a550,0,0);
    *extraout_x1 = local_1ac;
    return;
  }
  sk_swift_string_begin(auStack_1e0);
  sk_swift_type_hash(0xeeacfd4bde4eff8d);
  sk_swift_type_hash(param_1);
  sk_swift_buf_ctx(auStack_170);
  sk_swift_error_build(auStack_138,auStack_170,&local_1ac);
  sk_swift_string_build(&local_218,auStack_138);
  kind = sk_swift_result_check();
  if (kind == '\x01') {
    sk_swift_collection_op(&local_219,0x66a140,0x65a688,0x66a140,0x65a5e8,FUN_0066a720,&local_1ac);
    if (local_219 != '\x02') {
      sk_swift_retain(&local_219,0x66a140,0x669c90);
      sk_swift_release(0x66a140,0x669c90,0,0);
      *extraout_x1_00 = local_219;
      goto LAB_00194ad8;
    }
  }
  else if (kind != '\0') {
                    /* WARNING: Subroutine does not return */
    sk_swift_fatal_error(sk_fatal_error_str,0xb,2,0xd00000000000003f,0x80000000005cd100,
                 sk_xnu_upcalls_swift,0x25,2,0x1061,0);
  }
  uStack_f8 = uStack_210;
  local_100 = local_218;
  uStack_e8 = uStack_200;
  uStack_f0 = local_208;
  uStack_d8 = uStack_1f0;
  local_e0 = local_1f8;
  local_d0 = local_1e8;
LAB_00194ad8:
  sk_swift_epilogue();
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_00194bb4 @ 0x00194bb4   (est. sk_swift_helper)
 * Ghidra: void FUN_00194bb4(undefined8 param_1,undefined8 param_2)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

/* WARNING: Removing unreachable block (ram,0x00194d28) */

void FUN_00194bb4(unsigned long param_1,unsigned long param_2)

{
  char kind;
  unsigned long err;
  unsigned int *extraout_x1;
  char *extraout_x1_00;
  long ctx_err;
  char local_219;
  unsigned long local_218;
  unsigned long uStack_210;
  unsigned long local_208;
  unsigned long uStack_200;
  unsigned long local_1f8;
  unsigned long uStack_1f0;
  unsigned char local_1e8;
  unsigned char auStack_1e0 [52];
  unsigned int local_1ac;
  unsigned char auStack_1a8 [56];
  unsigned char auStack_170 [56];
  unsigned char auStack_138 [56];
  unsigned long local_100;
  unsigned long uStack_f8;
  unsigned long uStack_f0;
  unsigned long uStack_e8;
  unsigned long local_e0;
  unsigned long uStack_d8;
  unsigned char local_d0;
  
  sk_swift_frame_init(auStack_1a8,0x14,0,&local_1ac);
  if (ctx_err != 0) {
    err = sk_swift_err_code(0);
    sk_swift_release(err,FUN_0065a550,0,0);
    *extraout_x1 = local_1ac;
    return;
  }
  sk_swift_string_begin(auStack_1e0);
  sk_swift_type_hash(0x49835a57ff5c542b);
  sk_swift_type_hash(param_1);
  sk_swift_type_arg(param_2);
  sk_swift_buf_ctx(auStack_170);
  sk_swift_error_build(auStack_138,auStack_170,&local_1ac);
  sk_swift_string_build(&local_218,auStack_138);
  kind = sk_swift_result_check();
  if (kind == '\x01') {
    sk_swift_collection_op(&local_219,0x66a140,0x65a688,0x66a140,0x65a5e8,FUN_0066a720,&local_1ac);
    if (local_219 != '\x02') {
      sk_swift_retain(&local_219,0x66a140,0x669c90);
      sk_swift_release(0x66a140,0x669c90,0,0);
      *extraout_x1_00 = local_219;
      goto LAB_00194da4;
    }
  }
  else if (kind != '\0') {
                    /* WARNING: Subroutine does not return */
    sk_swift_fatal_error(sk_fatal_error_str,0xb,2,0xd000000000000048,0x80000000005cd0b0,
                 sk_xnu_upcalls_swift,0x25,2,0x106c,0);
  }
  uStack_f8 = uStack_210;
  local_100 = local_218;
  uStack_e8 = uStack_200;
  uStack_f0 = local_208;
  uStack_d8 = uStack_1f0;
  local_e0 = local_1f8;
  local_d0 = local_1e8;
LAB_00194da4:
  sk_swift_epilogue();
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_00194e80 @ 0x00194e80   (est. sk_swift_helper)
 * Ghidra: void FUN_00194e80(undefined8 param_1,undefined8 param_2)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

/* WARNING: Removing unreachable block (ram,0x00194ff4) */

void FUN_00194e80(unsigned long param_1,unsigned long param_2)

{
  char kind;
  unsigned long err;
  unsigned int *extraout_x1;
  char *extraout_x1_00;
  long ctx_err;
  char local_219;
  unsigned long local_218;
  unsigned long uStack_210;
  unsigned long local_208;
  unsigned long uStack_200;
  unsigned long local_1f8;
  unsigned long uStack_1f0;
  unsigned char local_1e8;
  unsigned char auStack_1e0 [52];
  unsigned int local_1ac;
  unsigned char auStack_1a8 [56];
  unsigned char auStack_170 [56];
  unsigned char auStack_138 [56];
  unsigned long local_100;
  unsigned long uStack_f8;
  unsigned long uStack_f0;
  unsigned long uStack_e8;
  unsigned long local_e0;
  unsigned long uStack_d8;
  unsigned char local_d0;
  
  sk_swift_frame_init(auStack_1a8,0x14,0,&local_1ac);
  if (ctx_err != 0) {
    err = sk_swift_err_code(0);
    sk_swift_release(err,FUN_0065a550,0,0);
    *extraout_x1 = local_1ac;
    return;
  }
  sk_swift_string_begin(auStack_1e0);
  sk_swift_type_hash(0x97ceaeb512ac6035);
  sk_swift_type_hash(param_1);
  sk_swift_type_arg(param_2);
  sk_swift_buf_ctx(auStack_170);
  sk_swift_error_build(auStack_138,auStack_170,&local_1ac);
  sk_swift_string_build(&local_218,auStack_138);
  kind = sk_swift_result_check();
  if (kind == '\x01') {
    sk_swift_collection_op(&local_219,0x66a140,0x65a688,0x66a140,0x65a5e8,FUN_0066a720,&local_1ac);
    if (local_219 != '\x02') {
      sk_swift_retain(&local_219,0x66a140,0x669c90);
      sk_swift_release(0x66a140,0x669c90,0,0);
      *extraout_x1_00 = local_219;
      goto LAB_00195070;
    }
  }
  else if (kind != '\0') {
                    /* WARNING: Subroutine does not return */
    sk_swift_fatal_error(sk_fatal_error_str,0xb,2,0xd00000000000003f,0x80000000005cd070,
                 sk_xnu_upcalls_swift,0x25,2,0x1077,0);
  }
  uStack_f8 = uStack_210;
  local_100 = local_218;
  uStack_e8 = uStack_200;
  uStack_f0 = local_208;
  uStack_d8 = uStack_1f0;
  local_e0 = local_1f8;
  local_d0 = local_1e8;
LAB_00195070:
  sk_swift_epilogue();
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019514c @ 0x0019514c   (est. sk_swift_helper)
 * Ghidra: void FUN_0019514c(undefined8 param_1,undefined8 param_2)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

/* WARNING: Removing unreachable block (ram,0x001952c0) */

void FUN_0019514c(unsigned long param_1,unsigned long param_2)

{
  char kind;
  unsigned long err;
  unsigned int *extraout_x1;
  char *extraout_x1_00;
  long ctx_err;
  char local_219;
  unsigned long local_218;
  unsigned long uStack_210;
  unsigned long local_208;
  unsigned long uStack_200;
  unsigned long local_1f8;
  unsigned long uStack_1f0;
  unsigned char local_1e8;
  unsigned char auStack_1e0 [52];
  unsigned int local_1ac;
  unsigned char auStack_1a8 [56];
  unsigned char auStack_170 [56];
  unsigned char auStack_138 [56];
  unsigned long local_100;
  unsigned long uStack_f8;
  unsigned long uStack_f0;
  unsigned long uStack_e8;
  unsigned long local_e0;
  unsigned long uStack_d8;
  unsigned char local_d0;
  
  sk_swift_frame_init(auStack_1a8,0x14,0,&local_1ac);
  if (ctx_err != 0) {
    err = sk_swift_err_code(0);
    sk_swift_release(err,FUN_0065a550,0,0);
    *extraout_x1 = local_1ac;
    return;
  }
  sk_swift_string_begin(auStack_1e0);
  sk_swift_type_hash(0x5c4cb5b5f38d7ba3);
  sk_swift_type_hash(param_1);
  sk_swift_type_arg(param_2);
  sk_swift_buf_ctx(auStack_170);
  sk_swift_error_build(auStack_138,auStack_170,&local_1ac);
  sk_swift_string_build(&local_218,auStack_138);
  kind = sk_swift_result_check();
  if (kind == '\x01') {
    sk_swift_collection_op(&local_219,0x66a140,0x65a688,0x66a140,0x65a5e8,FUN_0066a720,&local_1ac);
    if (local_219 != '\x02') {
      sk_swift_retain(&local_219,0x66a140,0x669c90);
      sk_swift_release(0x66a140,0x669c90,0,0);
      *extraout_x1_00 = local_219;
      goto LAB_0019533c;
    }
  }
  else if (kind != '\0') {
                    /* WARNING: Subroutine does not return */
    sk_swift_fatal_error(sk_fatal_error_str,0xb,2,0xd000000000000041,0x80000000005cd020,
                 sk_xnu_upcalls_swift,0x25,2,0x1082,0);
  }
  uStack_f8 = uStack_210;
  local_100 = local_218;
  uStack_e8 = uStack_200;
  uStack_f0 = local_208;
  uStack_d8 = uStack_1f0;
  local_e0 = local_1f8;
  local_d0 = local_1e8;
LAB_0019533c:
  sk_swift_epilogue();
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_00195418 @ 0x00195418   (est. sk_swift_helper)
 * Ghidra: uint FUN_00195418(undefined8 param_1,ulong param_2)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

/* WARNING: Removing unreachable block (ram,0x00195590) */

unsigned int FUN_00195418(unsigned long param_1,unsigned long param_2)

{
  unsigned char bv;
  char kind;
  unsigned long res;
  unsigned int *extraout_x1;
  unsigned char *extraout_x1_00;
  long ctx_err;
  unsigned char local_219;
  unsigned long local_218;
  unsigned long uStack_210;
  unsigned long local_208;
  unsigned long uStack_200;
  unsigned long local_1f8;
  unsigned long uStack_1f0;
  unsigned char local_1e8;
  unsigned char auStack_1e0 [52];
  unsigned int local_1ac;
  unsigned char auStack_1a8 [56];
  unsigned char auStack_170 [56];
  unsigned char auStack_138 [56];
  unsigned long local_100;
  unsigned long uStack_f8;
  unsigned long uStack_f0;
  unsigned long uStack_e8;
  unsigned long local_e0;
  unsigned long uStack_d8;
  unsigned char local_d0;
  unsigned long local_c0;
  unsigned long uStack_b8;
  unsigned long uStack_b0;
  unsigned long uStack_a8;
  unsigned long local_a0;
  unsigned long uStack_98;
  unsigned char local_90;
  
  sk_swift_frame_init(auStack_1a8,0x14,0,&local_1ac);
  if (ctx_err == 0) {
    sk_swift_string_begin(auStack_1e0);
    sk_swift_type_hash(0xbf47c794f2a3183f);
    sk_swift_type_hash(param_1);
    sk_swift_type_arg(param_2);
    sk_swift_buf_ctx(auStack_170);
    sk_swift_error_build(auStack_138,auStack_170,&local_1ac);
    sk_swift_string_build(&local_218,auStack_138);
    kind = sk_swift_result_check();
    if (kind == '\x01') {
      sk_swift_collection_op(&local_219,0x66a140,0x65a688,0x66a140,0x65a5e8,FUN_0066a720,&local_1ac);
      local_219 = local_219 & 0x7f;
      sk_swift_retain(&local_219,0x66a140,0x669c90);
      bv = local_219;
      param_2 = (unsigned long)local_219;
      sk_swift_release(0x66a140,0x669c90,0,0);
      *extraout_x1_00 = bv;
      uStack_b8 = uStack_210;
      local_c0 = local_218;
      uStack_a8 = uStack_200;
      uStack_b0 = local_208;
      uStack_98 = uStack_1f0;
      local_a0 = local_1f8;
      local_90 = local_1e8;
      sk_swift_epilogue();
    }
    else {
      if (kind != '\0') {
                    /* WARNING: Subroutine does not return */
        sk_swift_fatal_error(sk_fatal_error_str,0xb,2,0xd000000000000041,0x80000000005ccfd0,
                     sk_xnu_upcalls_swift,0x25,2,0x1094,0);
      }
      param_2 = sk_swift_result_value2();
      uStack_f8 = uStack_210;
      local_100 = local_218;
      uStack_e8 = uStack_200;
      uStack_f0 = local_208;
      uStack_d8 = uStack_1f0;
      local_e0 = local_1f8;
      local_d0 = local_1e8;
      sk_swift_epilogue();
    }
  }
  else {
    res = sk_swift_err_code(0);
    sk_swift_release(res,FUN_0065a550,0,0);
    *extraout_x1 = local_1ac;
  }
  return (unsigned int)param_2 & 1;
}





/*--------------------------------------------------------------------*/
/* FUN_001956f4 @ 0x001956f4   (est. sk_swift_helper)
 * Ghidra: uint FUN_001956f4(undefined8 param_1,undefined8 param_2,ulong param_3)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

/* WARNING: Removing unreachable block (ram,0x00195884) */

unsigned int FUN_001956f4(unsigned long param_1,unsigned long param_2,unsigned long param_3)

{
  unsigned char bv;
  char kind;
  unsigned long res;
  unsigned int *extraout_x1;
  unsigned char *extraout_x1_00;
  long ctx_err;
  unsigned char local_229;
  unsigned long local_228;
  unsigned long uStack_220;
  unsigned long local_218;
  unsigned long uStack_210;
  unsigned long local_208;
  unsigned long uStack_200;
  unsigned char local_1f8;
  unsigned char auStack_1f0 [52];
  unsigned int local_1bc;
  unsigned char auStack_1b8 [56];
  unsigned char auStack_180 [56];
  unsigned char auStack_148 [56];
  unsigned long local_110;
  unsigned long uStack_108;
  unsigned long uStack_100;
  unsigned long uStack_f8;
  unsigned long local_f0;
  unsigned long uStack_e8;
  unsigned char local_e0;
  unsigned long local_d0;
  unsigned long uStack_c8;
  unsigned long uStack_c0;
  unsigned long uStack_b8;
  unsigned long local_b0;
  unsigned long uStack_a8;
  unsigned char local_a0;
  
  sk_swift_frame_init(auStack_1b8,0x20,0,&local_1bc);
  if (ctx_err == 0) {
    sk_swift_string_begin(auStack_1f0);
    sk_swift_type_hash(0x9cf286378bc4568d);
    sk_swift_type_hash(param_1);
    sk_swift_type_hash(param_2);
    sk_swift_type_hash(param_3);
    sk_swift_buf_ctx(auStack_180);
    sk_swift_error_build(auStack_148,auStack_180,&local_1bc);
    sk_swift_string_build(&local_228,auStack_148);
    kind = sk_swift_result_check();
    if (kind == '\x01') {
      sk_swift_collection_op(&local_229,0x66a140,0x65a688,0x66a140,0x65a5e8,FUN_0066a720,&local_1bc);
      local_229 = local_229 & 0x7f;
      sk_swift_retain(&local_229,0x66a140,0x669c90);
      bv = local_229;
      param_3 = (unsigned long)local_229;
      sk_swift_release(0x66a140,0x669c90,0,0);
      *extraout_x1_00 = bv;
      uStack_c8 = uStack_220;
      local_d0 = local_228;
      uStack_b8 = uStack_210;
      uStack_c0 = local_218;
      uStack_a8 = uStack_200;
      local_b0 = local_208;
      local_a0 = local_1f8;
      sk_swift_epilogue();
    }
    else {
      if (kind != '\0') {
                    /* WARNING: Subroutine does not return */
        sk_swift_fatal_error(sk_fatal_error_str,0xb,2,0xd00000000000003d,0x80000000005ccf90,
                     sk_xnu_upcalls_swift,0x25,2,0x10aa,0);
      }
      param_3 = sk_swift_result_value2();
      uStack_108 = uStack_220;
      local_110 = local_228;
      uStack_f8 = uStack_210;
      uStack_100 = local_218;
      uStack_e8 = uStack_200;
      local_f0 = local_208;
      local_e0 = local_1f8;
      sk_swift_epilogue();
    }
  }
  else {
    res = sk_swift_err_code(0);
    sk_swift_release(res,FUN_0065a550,0,0);
    *extraout_x1 = local_1bc;
  }
  return (unsigned int)param_3 & 1;
}





/*--------------------------------------------------------------------*/
/* FUN_001959e8 @ 0x001959e8   (est. sk_swift_helper)
 * Ghidra: uint FUN_001959e8(undefined8 param_1,ulong param_2)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

/* WARNING: Removing unreachable block (ram,0x00195b60) */

unsigned int FUN_001959e8(unsigned long param_1,unsigned long param_2)

{
  unsigned char bv;
  char kind;
  unsigned long res;
  unsigned int *extraout_x1;
  unsigned char *extraout_x1_00;
  long ctx_err;
  unsigned char local_219;
  unsigned long local_218;
  unsigned long uStack_210;
  unsigned long local_208;
  unsigned long uStack_200;
  unsigned long local_1f8;
  unsigned long uStack_1f0;
  unsigned char local_1e8;
  unsigned char auStack_1e0 [52];
  unsigned int local_1ac;
  unsigned char auStack_1a8 [56];
  unsigned char auStack_170 [56];
  unsigned char auStack_138 [56];
  unsigned long local_100;
  unsigned long uStack_f8;
  unsigned long uStack_f0;
  unsigned long uStack_e8;
  unsigned long local_e0;
  unsigned long uStack_d8;
  unsigned char local_d0;
  unsigned long local_c0;
  unsigned long uStack_b8;
  unsigned long uStack_b0;
  unsigned long uStack_a8;
  unsigned long local_a0;
  unsigned long uStack_98;
  unsigned char local_90;
  
  sk_swift_frame_init(auStack_1a8,0x18,0,&local_1ac);
  if (ctx_err == 0) {
    sk_swift_string_begin(auStack_1e0);
    sk_swift_type_hash(0x297503a088d23fa7);
    sk_swift_type_hash(param_1);
    sk_swift_type_hash(param_2);
    sk_swift_buf_ctx(auStack_170);
    sk_swift_error_build(auStack_138,auStack_170,&local_1ac);
    sk_swift_string_build(&local_218,auStack_138);
    kind = sk_swift_result_check();
    if (kind == '\x01') {
      sk_swift_collection_op(&local_219,0x66a140,0x65a688,0x66a140,0x65a5e8,FUN_0066a720,&local_1ac);
      local_219 = local_219 & 0x7f;
      sk_swift_retain(&local_219,0x66a140,0x669c90);
      bv = local_219;
      param_2 = (unsigned long)local_219;
      sk_swift_release(0x66a140,0x669c90,0,0);
      *extraout_x1_00 = bv;
      uStack_b8 = uStack_210;
      local_c0 = local_218;
      uStack_a8 = uStack_200;
      uStack_b0 = local_208;
      uStack_98 = uStack_1f0;
      local_a0 = local_1f8;
      local_90 = local_1e8;
      sk_swift_epilogue();
    }
    else {
      if (kind != '\0') {
                    /* WARNING: Subroutine does not return */
        sk_swift_fatal_error(sk_fatal_error_str,0xb,2,0xd00000000000003b,0x80000000005ccf50,
                     sk_xnu_upcalls_swift,0x25,2,0x10b5,0);
      }
      param_2 = sk_swift_result_value2();
      uStack_f8 = uStack_210;
      local_100 = local_218;
      uStack_e8 = uStack_200;
      uStack_f0 = local_208;
      uStack_d8 = uStack_1f0;
      local_e0 = local_1f8;
      local_d0 = local_1e8;
      sk_swift_epilogue();
    }
  }
  else {
    res = sk_swift_err_code(0);
    sk_swift_release(res,FUN_0065a550,0,0);
    *extraout_x1 = local_1ac;
  }
  return (unsigned int)param_2 & 1;
}





/*--------------------------------------------------------------------*/
/* FUN_00195cc4 @ 0x00195cc4   (est. sk_swift_helper)
 * Ghidra: void FUN_00195cc4(undefined8 param_1,undefined8 param_2)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

/* WARNING: Removing unreachable block (ram,0x00195e5c) */

void FUN_00195cc4(unsigned long param_1,unsigned long param_2)

{
  char kind;
  unsigned long err;
  unsigned int *extraout_x1;
  long ctx_err;
  unsigned long local_218;
  unsigned long uStack_210;
  unsigned long local_208;
  unsigned long uStack_200;
  unsigned long local_1f8;
  unsigned long uStack_1f0;
  unsigned char local_1e8;
  unsigned char auStack_1e0 [52];
  unsigned int local_1ac;
  unsigned char auStack_1a8 [56];
  unsigned char auStack_170 [56];
  unsigned char auStack_138 [56];
  unsigned long local_100;
  unsigned long uStack_f8;
  unsigned long uStack_f0;
  unsigned long uStack_e8;
  unsigned long local_e0;
  unsigned long uStack_d8;
  unsigned char local_d0;
  unsigned long local_c0;
  unsigned long uStack_b8;
  unsigned long uStack_b0;
  unsigned long uStack_a8;
  unsigned long local_a0;
  unsigned long uStack_98;
  unsigned char local_90;
  
  sk_swift_frame_init(auStack_1a8,0x14,0,&local_1ac);
  if (ctx_err == 0) {
    sk_swift_string_begin(auStack_1e0);
    sk_swift_type_hash(0xb6f6a879c3ba828c);
    sk_swift_type_hash(param_1);
    sk_swift_type_arg(param_2);
    sk_swift_buf_ctx(auStack_170);
    sk_swift_error_build(auStack_138,auStack_170,&local_1ac);
    sk_swift_string_build(&local_218,auStack_138);
    kind = sk_swift_result_check();
    if (kind == '\0') {
      uStack_f8 = uStack_210;
      local_100 = local_218;
      uStack_e8 = uStack_200;
      uStack_f0 = local_208;
      uStack_d8 = uStack_1f0;
      local_e0 = local_1f8;
      local_d0 = local_1e8;
    }
    else {
      if (kind != '\x01') {
                    /* WARNING: Subroutine does not return */
        sk_swift_fatal_error(sk_fatal_error_str,0xb,2,0xd000000000000043,0x80000000005ccf00,
                     sk_xnu_upcalls_swift,0x25,2,0x10c7,0);
      }
      err = sk_swift_collection_op(0x66a370,0x65a688,0x66a370,0x65a5e8,0x66a780,&local_1ac);
      sk_swift_retain(err,0x66a370,0x669d70);
      sk_swift_release(0x66a370,0x669d70,0,0);
      uStack_b8 = uStack_210;
      local_c0 = local_218;
      uStack_a8 = uStack_200;
      uStack_b0 = local_208;
      uStack_98 = uStack_1f0;
      local_a0 = local_1f8;
      local_90 = local_1e8;
    }
    sk_swift_epilogue();
  }
  else {
    err = sk_swift_err_code(0);
    sk_swift_release(err,FUN_0065a550,0,0);
    *extraout_x1 = local_1ac;
  }
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_00195f6c @ 0x00195f6c   (est. sk_swift_helper)
 * Ghidra: void FUN_00195f6c(undefined8 param_1)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

/* WARNING: Removing unreachable block (ram,0x001960f4) */

void FUN_00195f6c(unsigned long param_1)

{
  char kind;
  unsigned long err;
  unsigned int *extraout_x1;
  long ctx_err;
  unsigned long local_218;
  unsigned long uStack_210;
  unsigned long local_208;
  unsigned long uStack_200;
  unsigned long local_1f8;
  unsigned long uStack_1f0;
  unsigned char local_1e8;
  unsigned char auStack_1e0 [52];
  unsigned int local_1ac;
  unsigned char auStack_1a8 [56];
  unsigned char auStack_170 [56];
  unsigned char auStack_138 [56];
  unsigned long local_100;
  unsigned long uStack_f8;
  unsigned long uStack_f0;
  unsigned long uStack_e8;
  unsigned long local_e0;
  unsigned long uStack_d8;
  unsigned char local_d0;
  unsigned long local_c0;
  unsigned long uStack_b8;
  unsigned long uStack_b0;
  unsigned long uStack_a8;
  unsigned long local_a0;
  unsigned long uStack_98;
  unsigned char local_90;
  
  sk_swift_frame_init(auStack_1a8,0x10,0,&local_1ac);
  if (ctx_err == 0) {
    sk_swift_string_begin(auStack_1e0);
    sk_swift_type_hash(0xa2a4d1e2132b2686);
    sk_swift_type_hash(param_1);
    sk_swift_buf_ctx(auStack_170);
    sk_swift_error_build(auStack_138,auStack_170,&local_1ac);
    sk_swift_string_build(&local_218,auStack_138);
    kind = sk_swift_result_check();
    if (kind == '\0') {
      uStack_f8 = uStack_210;
      local_100 = local_218;
      uStack_e8 = uStack_200;
      uStack_f0 = local_208;
      uStack_d8 = uStack_1f0;
      local_e0 = local_1f8;
      local_d0 = local_1e8;
    }
    else {
      if (kind != '\x01') {
                    /* WARNING: Subroutine does not return */
        sk_swift_fatal_error(sk_fatal_error_str,0xb,2,0xd000000000000049,0x80000000005cceb0,
                     sk_xnu_upcalls_swift,0x25,2,0x10d2,0);
      }
      err = sk_swift_collection_op(0x66a370,0x65a688,0x66a370,0x65a5e8,0x66a780,&local_1ac);
      sk_swift_retain(err,0x66a370,0x669d70);
      sk_swift_release(0x66a370,0x669d70,0,0);
      uStack_b8 = uStack_210;
      local_c0 = local_218;
      uStack_a8 = uStack_200;
      uStack_b0 = local_208;
      uStack_98 = uStack_1f0;
      local_a0 = local_1f8;
      local_90 = local_1e8;
    }
    sk_swift_epilogue();
  }
  else {
    err = sk_swift_err_code(0);
    sk_swift_release(err,FUN_0065a550,0,0);
    *extraout_x1 = local_1ac;
  }
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_00196204 @ 0x00196204   (est. sk_swift_helper)
 * Ghidra: ulong FUN_00196204(long param_1)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

unsigned long FUN_00196204(long param_1)

{
  code *pcVar2;
  unsigned long uVar1;
    unsigned int *extraout_x1;
  unsigned long extraout_x1_00;
  unsigned long res;
  long ctx_err;
  unsigned char auStack_1b0 [56];
  long local_178;
  unsigned long local_170;
  unsigned long uStack_168;
  unsigned long local_160;
  unsigned long uStack_158;
  unsigned long uStack_150;
  unsigned long uStack_148;
  unsigned long local_140;
  unsigned long uStack_138;
  unsigned char local_130;
  unsigned char auStack_128 [56];
  unsigned char auStack_f0 [56];
  unsigned char auStack_b8 [56];
  unsigned long local_80;
  unsigned long uStack_78;
  unsigned long uStack_70;
  unsigned long uStack_68;
  unsigned long local_60;
  unsigned long uStack_58;
  unsigned char local_50;
  unsigned int local_34;
  
  res = *(unsigned long *)(param_1 + 0x10);
  if (0xf < res) {
    res = 0x10;
  }
  sk_swift_frame_init(auStack_128,res + 8,0,&local_34);
  if (ctx_err == 0) {
    sk_swift_string_begin(&local_160);
    sk_swift_type_hash(0xcfadb651d44886e2);
    local_178 = *(long *)(param_1 + 0x10);
    if (local_178 != 0x10) {
      local_170 = 0;
      uStack_168 = 0xe000000000000000;
      sk_swift_precond_1(0x3b);
      sk_swift_precond_2(0xd000000000000011,0x80000000005cce90);
      sk_swift_precond_2(0xd000000000000037,0x80000000005c9400);
      pcVar2 = (code *)sk_swift_meta(0x6720e0);
      (*pcVar2)(0x677880,0x6720e0);
      sk_swift_precond_2();
      sk_swift_abort_tail(extraout_x1_00);
                    /* WARNING: Subroutine does not return */
      sk_swift_fatal_error(sk_fatal_error_str,0xb,2,local_170,uStack_168,
                   sk_xnu_upcalls_swift,0x25,2,0xc0e,0);
    }
    sk_swift_elem_append(*(unsigned char *)(param_1 + 0x20));
    sk_swift_elem_append(*(unsigned char *)(param_1 + 0x21));
    sk_swift_elem_append(*(unsigned char *)(param_1 + 0x22));
    sk_swift_elem_append(*(unsigned char *)(param_1 + 0x23));
    sk_swift_elem_append(*(unsigned char *)(param_1 + 0x24));
    sk_swift_elem_append(*(unsigned char *)(param_1 + 0x25));
    sk_swift_elem_append(*(unsigned char *)(param_1 + 0x26));
    sk_swift_elem_append(*(unsigned char *)(param_1 + 0x27));
    sk_swift_elem_append(*(unsigned char *)(param_1 + 0x28));
    sk_swift_elem_append(*(unsigned char *)(param_1 + 0x29));
    sk_swift_elem_append(*(unsigned char *)(param_1 + 0x2a));
    sk_swift_elem_append(*(unsigned char *)(param_1 + 0x2b));
    sk_swift_elem_append(*(unsigned char *)(param_1 + 0x2c));
    sk_swift_elem_append(*(unsigned char *)(param_1 + 0x2d));
    sk_swift_elem_append(*(unsigned char *)(param_1 + 0x2e));
    sk_swift_elem_append(*(unsigned char *)(param_1 + 0x2f));
    uStack_78 = uStack_158;
    local_80 = local_160;
    uStack_68 = uStack_148;
    uStack_70 = uStack_150;
    uStack_58 = uStack_138;
    local_60 = local_140;
    local_50 = local_130;
    sk_swift_buf_ctx(auStack_f0);
    sk_swift_error_build(auStack_b8,auStack_f0,&local_34);
    sk_swift_string_build(auStack_1b0,auStack_b8);
    res = sk_swift_result_value();
    sk_swift_epilogue();
  }
  else {
    res = (unsigned long)local_34;
    uVar1 = sk_swift_err_code(0);
    sk_swift_release(uVar1,FUN_0065a550,0,0);
    *extraout_x1 = local_34;
  }
  return res;
}





/*--------------------------------------------------------------------*/
/* FUN_001964f4 @ 0x001964f4   (est. sk_swift_helper)
 * Ghidra: ulong FUN_001964f4(undefined8 param_1,undefined8 param_2)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

unsigned long FUN_001964f4(unsigned long param_1,unsigned long param_2)

{
  unsigned long uVar1;
  unsigned int *extraout_x1;
  unsigned long err;
  long ctx_err;
  unsigned char auStack_158 [56];
  unsigned char auStack_120 [52];
  unsigned int local_ec;
  unsigned char auStack_e8 [56];
  unsigned char auStack_b0 [56];
  unsigned char auStack_78 [56];
  
  sk_swift_frame_init(auStack_e8,0x14,0,&local_ec);
  if (ctx_err == 0) {
    sk_swift_string_begin(auStack_120);
    sk_swift_type_hash(0x87dcfd91b4bef573);
    sk_swift_type_hash(param_1);
    sk_swift_type_arg(param_2);
    sk_swift_buf_ctx(auStack_b0);
    sk_swift_error_build(auStack_78,auStack_b0,&local_ec);
    sk_swift_string_build(auStack_158,auStack_78);
    err = sk_swift_result_value();
    sk_swift_epilogue();
  }
  else {
    err = (unsigned long)local_ec;
    uVar1 = sk_swift_err_code(0);
    sk_swift_release(uVar1,FUN_0065a550,0,0);
    *extraout_x1 = local_ec;
  }
  return err;
}





/*--------------------------------------------------------------------*/
/* FUN_0019661c @ 0x0019661c   (est. sk_swift_helper)
 * Ghidra: void FUN_0019661c(undefined8 param_1)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019661c(unsigned long param_1)

{
  FUN_0018b1e4(param_1,0x16f2b4d08b00dc82);
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_00196644 @ 0x00196644   (est. sk_swift_helper)
 * Ghidra: void FUN_00196644(ulong *param_1,undefined8 param_2)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

/* WARNING: Removing unreachable block (ram,0x00196808) */

void FUN_00196644(unsigned long *param_1,unsigned long param_2)

{
  unsigned char bv;
  char kind;
  unsigned long res;
  unsigned int *extraout_x1;
  unsigned char *extraout_x1_00;
  unsigned long uVar4;
  long ctx_err;
  unsigned char local_230;
  unsigned long uStack_22f;
  unsigned long uStack_228;
  unsigned long local_218;
  unsigned long uStack_210;
  unsigned long local_208;
  unsigned long uStack_200;
  unsigned long local_1f8;
  unsigned long uStack_1f0;
  unsigned char local_1e8;
  unsigned char auStack_1e0 [52];
  unsigned int local_1ac;
  unsigned char auStack_1a8 [56];
  unsigned char auStack_170 [56];
  unsigned char auStack_138 [56];
  unsigned long local_100;
  unsigned long uStack_f8;
  unsigned long uStack_f0;
  unsigned long uStack_e8;
  unsigned long local_e0;
  unsigned long uStack_d8;
  unsigned char local_d0;
  unsigned long local_c0;
  unsigned long uStack_b8;
  unsigned long uStack_b0;
  unsigned long uStack_a8;
  unsigned long local_a0;
  unsigned long uStack_98;
  unsigned char local_90;
  
  sk_swift_frame_init(auStack_1a8,0xc,0,&local_1ac);
  if (ctx_err != 0) {
    res = sk_swift_err_code(0);
    sk_swift_release(res,FUN_0065a550,0,0);
    *extraout_x1 = local_1ac;
    return;
  }
  sk_swift_string_begin(auStack_1e0);
  sk_swift_type_hash(0x7f4c14f4c44e6763);
  sk_swift_type_arg(param_2);
  sk_swift_buf_ctx(auStack_170);
  sk_swift_error_build(auStack_138,auStack_170,&local_1ac);
  sk_swift_string_build(&local_218,auStack_138);
  kind = sk_swift_result_check();
  if (kind == '\x01') {
    sk_swift_collection_op(&local_230,0x66a400,0x65a688,0x66a400,0x65a5e8,0x66a798,&local_1ac);
    uVar4 = (unsigned long)local_230;
  }
  else {
    if (kind != '\0') {
                    /* WARNING: Subroutine does not return */
      sk_swift_fatal_error(sk_fatal_error_str,0xb,2,0xd000000000000038,0x80000000005cce50,
                   sk_xnu_upcalls_swift,0x25,2,0x10eb,0);
    }
    sk_swift_collection_op(&local_230,0x66a478,0x65a688,0x66a478,0x65a5e8,0x66a7b0,&local_1ac);
    uVar4 = CONCAT71(uStack_22f,local_230);
    if (-1 < (long)uStack_228) {
      param_1[1] = uStack_228;
      *param_1 = uVar4;
      uStack_f8 = uStack_210;
      local_100 = local_218;
      uStack_e8 = uStack_200;
      uStack_f0 = local_208;
      uStack_d8 = uStack_1f0;
      local_e0 = local_1f8;
      local_d0 = local_1e8;
      goto LAB_0019690c;
    }
  }
  local_230 = (unsigned char)uVar4;
  sk_swift_retain(&local_230,0x66a400,0x669dc0);
  bv = local_230;
  sk_swift_release(0x66a400,0x669dc0,0,0);
  *extraout_x1_00 = bv;
  uStack_b8 = uStack_210;
  local_c0 = local_218;
  uStack_a8 = uStack_200;
  uStack_b0 = local_208;
  uStack_98 = uStack_1f0;
  local_a0 = local_1f8;
  local_90 = local_1e8;
LAB_0019690c:
  sk_swift_epilogue();
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_00196964 @ 0x00196964   (est. sk_swift_helper)
 * Ghidra: void FUN_00196964(undefined8 param_1)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

/* WARNING: Removing unreachable block (ram,0x00196ac8) */

void FUN_00196964(unsigned long param_1)

{
  char kind;
  unsigned long err;
  unsigned int *extraout_x1;
  char *extraout_x1_00;
  long ctx_err;
  char local_219;
  unsigned long local_218;
  unsigned long uStack_210;
  unsigned long local_208;
  unsigned long uStack_200;
  unsigned long local_1f8;
  unsigned long uStack_1f0;
  unsigned char local_1e8;
  unsigned char auStack_1e0 [52];
  unsigned int local_1ac;
  unsigned char auStack_1a8 [56];
  unsigned char auStack_170 [56];
  unsigned char auStack_138 [56];
  unsigned long local_100;
  unsigned long uStack_f8;
  unsigned long uStack_f0;
  unsigned long uStack_e8;
  unsigned long local_e0;
  unsigned long uStack_d8;
  unsigned char local_d0;
  
  sk_swift_frame_init(auStack_1a8,0xc,0,&local_1ac);
  if (ctx_err != 0) {
    err = sk_swift_err_code(0);
    sk_swift_release(err,FUN_0065a550,0,0);
    *extraout_x1 = local_1ac;
    return;
  }
  sk_swift_string_begin(auStack_1e0);
  sk_swift_type_hash(0x2ee46abe01738a5);
  sk_swift_type_arg(param_1);
  sk_swift_buf_ctx(auStack_170);
  sk_swift_error_build(auStack_138,auStack_170,&local_1ac);
  sk_swift_string_build(&local_218,auStack_138);
  kind = sk_swift_result_check();
  if (kind == '\x01') {
    sk_swift_collection_op(&local_219,0x66a400,0x65a688,0x66a400,0x65a5e8,0x66a798,&local_1ac);
    if (local_219 != '\x02') {
      sk_swift_retain(&local_219,0x66a400,0x669dc0);
      sk_swift_release(0x66a400,0x669dc0,0,0);
      *extraout_x1_00 = local_219;
      goto LAB_00196b44;
    }
  }
  else if (kind != '\0') {
                    /* WARNING: Subroutine does not return */
    sk_swift_fatal_error(sk_fatal_error_str,0xb,2,0xd000000000000035,0x80000000005cce10,
                 sk_xnu_upcalls_swift,0x25,2,0x10f6,0);
  }
  uStack_f8 = uStack_210;
  local_100 = local_218;
  uStack_e8 = uStack_200;
  uStack_f0 = local_208;
  uStack_d8 = uStack_1f0;
  local_e0 = local_1f8;
  local_d0 = local_1e8;
LAB_00196b44:
  sk_swift_epilogue();
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_00196c20 @ 0x00196c20   (est. sk_swift_helper)
 * Ghidra: void FUN_00196c20(undefined8 *param_1,undefined8 param_2)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

/* WARNING: Removing unreachable block (ram,0x00196e94) */
/* WARNING: Removing unreachable block (ram,0x00196d58) */

void FUN_00196c20(unsigned long *param_1,unsigned long param_2)

{
    char kind;
  long lVar3;
  unsigned int *extraout_x1;
  char *extraout_x1_00;
  long ctx_err;
  unsigned long uVar4;
  char local_2a9;
  unsigned long local_2a8 [7];
  unsigned long local_270;
  unsigned long uStack_268;
  unsigned long uStack_260;
  unsigned long uStack_258;
  unsigned long local_250;
  unsigned long uStack_248;
  unsigned char local_240;
  unsigned int local_23c;
  unsigned char auStack_238 [56];
  unsigned char auStack_200 [56];
  unsigned char auStack_1c8 [56];
  unsigned long local_190;
  unsigned long local_150;
  unsigned long local_d0;
  unsigned long uStack_c8;
  unsigned long uStack_c0;
  unsigned long uStack_b8;
  unsigned long local_b0;
  unsigned long uStack_a8;
  unsigned char local_a0;
  
  uVar4 = *param_1;
  local_270 = uVar4;
  lVar3 = sk_swift_collection_count(&local_270,0x66a4f8,0x66a7d0);
  if (SCARRY8(lVar3,8)) {
                    /* WARNING: Does not return */
    __builtin_trap();
  }
  if (SCARRY8(lVar3 + 8,4)) {
                    /* WARNING: Does not return */
    __builtin_trap();
  }
  sk_swift_frame_init(auStack_238,lVar3 + 0xc,0,&local_23c);
  if (ctx_err != 0) {
    uVar4 = sk_swift_err_code(0);
    sk_swift_release(uVar4,FUN_0065a550,0,0);
    *extraout_x1 = local_23c;
    return;
  }
  sk_swift_string_begin(&local_270);
  sk_swift_type_hash(0x45890560261c55c4);
  local_2a8[0] = uVar4;
  sk_swift_collection_init(local_2a8,0x65a870,0x66a4f8,0x65a798,0x66a7d0);
  sk_swift_type_arg(param_2);
  uStack_c8 = uStack_268;
  local_d0 = local_270;
  uStack_b8 = uStack_258;
  uStack_c0 = uStack_260;
  uStack_a8 = uStack_248;
  local_b0 = local_250;
  local_a0 = local_240;
  sk_swift_buf_ctx(auStack_200);
  sk_swift_error_build(auStack_1c8,auStack_200,&local_23c);
  sk_swift_string_build(local_2a8,auStack_1c8);
  kind = sk_swift_result_check();
  if (kind == '\x01') {
    sk_swift_collection_op(&local_2a9,0x66a400,0x65a688,0x66a400,0x65a5e8,0x66a798,&local_23c);
    if (local_2a9 != '\x02') {
      sk_swift_retain(&local_2a9,0x66a400,0x669dc0);
      sk_swift_release(0x66a400,0x669dc0,0,0);
      *extraout_x1_00 = local_2a9;
      local_150 = local_2a8[0];
      goto LAB_00196da8;
    }
  }
  else if (kind != '\0') {
                    /* WARNING: Subroutine does not return */
    sk_swift_fatal_error(sk_fatal_error_str,0xb,2,0xd00000000000003a,0x80000000005ccdd0,
                 sk_xnu_upcalls_swift,0x25,2,0x1101,0);
  }
  local_190 = local_2a8[0];
LAB_00196da8:
  sk_swift_epilogue();
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_00196fec @ 0x00196fec   (est. sk_swift_helper)
 * Ghidra: ulong FUN_00196fec(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

/* WARNING: Removing unreachable block (ram,0x00197180) */

unsigned long FUN_00196fec(void)

{
  char kind;
  unsigned long err;
  unsigned int *extraout_x1;
  unsigned char *extraout_x1_00;
  long ctx_err;
  unsigned long result;
  unsigned char local_219;
  unsigned long local_218;
  unsigned long uStack_210;
  unsigned long local_208;
  unsigned long uStack_200;
  unsigned long local_1f8;
  unsigned long uStack_1f0;
  unsigned char local_1e8;
  unsigned char auStack_1e0 [52];
  unsigned int local_1ac;
  unsigned char auStack_1a8 [56];
  unsigned char auStack_170 [56];
  unsigned char auStack_138 [56];
  unsigned long local_100;
  unsigned long uStack_f8;
  unsigned long uStack_f0;
  unsigned long uStack_e8;
  unsigned long local_e0;
  unsigned long uStack_d8;
  unsigned char local_d0;
  unsigned long local_c0;
  unsigned long uStack_b8;
  unsigned long uStack_b0;
  unsigned long uStack_a8;
  unsigned long local_a0;
  unsigned long uStack_98;
  unsigned char local_90;
  
  sk_swift_frame_init(auStack_1a8,8,0,&local_1ac);
  if (ctx_err == 0) {
    sk_swift_string_begin(auStack_1e0);
    sk_swift_type_hash(0x66c01ea3e50ca12);
    sk_swift_buf_ctx(auStack_170);
    sk_swift_error_build(auStack_138,auStack_170,&local_1ac);
    sk_swift_string_build(&local_218,auStack_138);
    kind = sk_swift_result_check();
    if (kind == '\0') {
      result = sk_swift_result_value();
      uStack_f8 = uStack_210;
      local_100 = local_218;
      uStack_e8 = uStack_200;
      uStack_f0 = local_208;
      uStack_d8 = uStack_1f0;
      local_e0 = local_1f8;
      local_d0 = local_1e8;
      sk_swift_epilogue();
    }
    else {
      if (kind != '\x01') {
                    /* WARNING: Subroutine does not return */
        sk_swift_fatal_error(sk_fatal_error_str,0xb,2,0xd000000000000045,0x80000000005ccd80,
                     sk_xnu_upcalls_swift,0x25,2,0x1113,0);
      }
      sk_swift_collection_op(&local_219,0x66a590,0x65a688,0x66a590,0x65a5e8,0x66a7e0,&local_1ac);
      sk_swift_retain(&local_219,0x66a590,0x669e20);
      result = (unsigned long)local_219;
      sk_swift_release(0x66a590,0x669e20,0,0);
      *extraout_x1_00 = local_219;
      uStack_b8 = uStack_210;
      local_c0 = local_218;
      uStack_a8 = uStack_200;
      uStack_b0 = local_208;
      uStack_98 = uStack_1f0;
      local_a0 = local_1f8;
      local_90 = local_1e8;
      sk_swift_epilogue();
    }
  }
  else {
    err = sk_swift_err_code(0);
    sk_swift_release(err,FUN_0065a550,0,0);
    *extraout_x1 = local_1ac;
  }
  return result;
}





/*--------------------------------------------------------------------*/
/* FUN_001972a4 @ 0x001972a4   (est. sk_swift_helper)
 * Ghidra: ulong FUN_001972a4(undefined8 param_1,undefined8 param_2,ulong param_3)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

/* WARNING: Removing unreachable block (ram,0x00197470) */

unsigned long FUN_001972a4(unsigned long param_1,unsigned long param_2,unsigned long param_3)

{
  char kind;
  unsigned long err;
  unsigned int *extraout_x1;
  unsigned char *extraout_x1_00;
  long ctx_err;
  unsigned char local_229;
  unsigned long local_228;
  unsigned long uStack_220;
  unsigned long local_218;
  unsigned long uStack_210;
  unsigned long local_208;
  unsigned long uStack_200;
  unsigned char local_1f8;
  unsigned char auStack_1f0 [52];
  unsigned int local_1bc;
  unsigned char auStack_1b8 [56];
  unsigned char auStack_180 [56];
  unsigned char auStack_148 [56];
  unsigned long local_110;
  unsigned long uStack_108;
  unsigned long uStack_100;
  unsigned long uStack_f8;
  unsigned long local_f0;
  unsigned long uStack_e8;
  unsigned char local_e0;
  unsigned long local_d0;
  unsigned long uStack_c8;
  unsigned long uStack_c0;
  unsigned long uStack_b8;
  unsigned long local_b0;
  unsigned long uStack_a8;
  unsigned char local_a0;
  
  sk_swift_frame_init(auStack_1b8,0x20,0,&local_1bc);
  if (ctx_err == 0) {
    sk_swift_string_begin(auStack_1f0);
    sk_swift_type_hash(0x5db1272313e51e1d);
    sk_swift_type_hash(param_1);
    sk_swift_type_hash(param_2);
    sk_swift_type_hash(param_3);
    sk_swift_buf_ctx(auStack_180);
    sk_swift_error_build(auStack_148,auStack_180,&local_1bc);
    sk_swift_string_build(&local_228,auStack_148);
    kind = sk_swift_result_check();
    if (kind == '\0') {
      param_3 = sk_swift_result_value();
      uStack_108 = uStack_220;
      local_110 = local_228;
      uStack_f8 = uStack_210;
      uStack_100 = local_218;
      uStack_e8 = uStack_200;
      local_f0 = local_208;
      local_e0 = local_1f8;
      sk_swift_epilogue();
    }
    else {
      if (kind != '\x01') {
                    /* WARNING: Subroutine does not return */
        sk_swift_fatal_error(sk_fatal_error_str,0xb,2,0xd00000000000004a,0x80000000005ccd30,
                     sk_xnu_upcalls_swift,0x25,2,0x111e,0);
      }
      sk_swift_collection_op(&local_229,0x66a590,0x65a688,0x66a590,0x65a5e8,0x66a7e0,&local_1bc);
      sk_swift_retain(&local_229,0x66a590,0x669e20);
      param_3 = (unsigned long)local_229;
      sk_swift_release(0x66a590,0x669e20,0,0);
      *extraout_x1_00 = local_229;
      uStack_c8 = uStack_220;
      local_d0 = local_228;
      uStack_b8 = uStack_210;
      uStack_c0 = local_218;
      uStack_a8 = uStack_200;
      local_b0 = local_208;
      local_a0 = local_1f8;
      sk_swift_epilogue();
    }
  }
  else {
    err = sk_swift_err_code(0);
    sk_swift_release(err,FUN_0065a550,0,0);
    *extraout_x1 = local_1bc;
  }
  return param_3;
}





/*--------------------------------------------------------------------*/
/* FUN_00197594 @ 0x00197594   (est. sk_swift_helper)
 * Ghidra: void FUN_00197594(undefined8 param_1)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

/* WARNING: Removing unreachable block (ram,0x001976f8) */

void FUN_00197594(unsigned long param_1)

{
  char kind;
  unsigned long err;
  unsigned int *extraout_x1;
  char *extraout_x1_00;
  long ctx_err;
  char local_219;
  unsigned long local_218;
  unsigned long uStack_210;
  unsigned long local_208;
  unsigned long uStack_200;
  unsigned long local_1f8;
  unsigned long uStack_1f0;
  unsigned char local_1e8;
  unsigned char auStack_1e0 [52];
  unsigned int local_1ac;
  unsigned char auStack_1a8 [56];
  unsigned char auStack_170 [56];
  unsigned char auStack_138 [56];
  unsigned long local_100;
  unsigned long uStack_f8;
  unsigned long uStack_f0;
  unsigned long uStack_e8;
  unsigned long local_e0;
  unsigned long uStack_d8;
  unsigned char local_d0;
  
  sk_swift_frame_init(auStack_1a8,0x10,0,&local_1ac);
  if (ctx_err != 0) {
    err = sk_swift_err_code(0);
    sk_swift_release(err,FUN_0065a550,0,0);
    *extraout_x1 = local_1ac;
    return;
  }
  sk_swift_string_begin(auStack_1e0);
  sk_swift_type_hash(0xc95a118f9fc956ac);
  sk_swift_type_hash(param_1);
  sk_swift_buf_ctx(auStack_170);
  sk_swift_error_build(auStack_138,auStack_170,&local_1ac);
  sk_swift_string_build(&local_218,auStack_138);
  kind = sk_swift_result_check();
  if (kind == '\x01') {
    sk_swift_collection_op(&local_219,0x66a590,0x65a688,0x66a590,0x65a5e8,0x66a7e0,&local_1ac);
    if (local_219 != '\x03') {
      sk_swift_retain(&local_219,0x66a590,0x669e20);
      sk_swift_release(0x66a590,0x669e20,0,0);
      *extraout_x1_00 = local_219;
      goto LAB_00197774;
    }
  }
  else if (kind != '\0') {
                    /* WARNING: Subroutine does not return */
    sk_swift_fatal_error(sk_fatal_error_str,0xb,2,0xd000000000000046,0x80000000005ccce0,
                 sk_xnu_upcalls_swift,0x25,2,0x1129,0);
  }
  uStack_f8 = uStack_210;
  local_100 = local_218;
  uStack_e8 = uStack_200;
  uStack_f0 = local_208;
  uStack_d8 = uStack_1f0;
  local_e0 = local_1f8;
  local_d0 = local_1e8;
LAB_00197774:
  sk_swift_epilogue();
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_00197850 @ 0x00197850   (est. sk_swift_helper)
 * Ghidra: void FUN_00197850(undefined8 param_1)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

/* WARNING: Removing unreachable block (ram,0x00197a90) */
/* WARNING: Removing unreachable block (ram,0x00197964) */

void FUN_00197850(unsigned long param_1)

{
    char kind;
  long lVar3;
  unsigned long uVar4;
  unsigned int *extraout_x1;
  char *extraout_x1_00;
  long ctx_err;
  char local_299;
  unsigned char local_298 [56];
  unsigned long local_260;
  unsigned long uStack_258;
  unsigned long uStack_250;
  unsigned long uStack_248;
  unsigned long local_240;
  unsigned long uStack_238;
  unsigned char local_230;
  unsigned int local_22c;
  unsigned char auStack_228 [56];
  unsigned char auStack_1f0 [56];
  unsigned char auStack_1b8 [248];
  unsigned long local_c0;
  unsigned long uStack_b8;
  unsigned long uStack_b0;
  unsigned long uStack_a8;
  unsigned long local_a0;
  unsigned long uStack_98;
  unsigned char local_90;
  
  lVar3 = sk_swift_collection_count(param_1,0x66a620,0x66a800);
  if (SCARRY8(lVar3,8)) {
                    /* WARNING: Does not return */
    __builtin_trap();
  }
  sk_swift_frame_init(auStack_228,lVar3 + 8,0,&local_22c);
  if (ctx_err == 0) {
    sk_swift_string_begin(&local_260);
    uVar4 = sk_swift_type_hash(0xf8597abcb89539fe);
    sk_swift_collection_init(uVar4,0x65a870,0x66a620,0x65a798,0x66a800);
    uStack_b8 = uStack_258;
    local_c0 = local_260;
    uStack_a8 = uStack_248;
    uStack_b0 = uStack_250;
    uStack_98 = uStack_238;
    local_a0 = local_240;
    local_90 = local_230;
    sk_swift_buf_ctx(auStack_1f0);
    sk_swift_error_build(auStack_1b8,auStack_1f0,&local_22c);
    sk_swift_string_build(local_298,auStack_1b8);
    kind = sk_swift_result_check();
    if (kind == '\x01') {
      sk_swift_collection_op(&local_299,0x66a590,0x65a688,0x66a590,0x65a5e8,0x66a7e0,&local_22c);
      if (local_299 != '\x03') {
        sk_swift_retain(&local_299,0x66a590,0x669e20);
        sk_swift_release(0x66a590,0x669e20,0,0);
        *extraout_x1_00 = local_299;
      }
    }
    else if (kind != '\0') {
                    /* WARNING: Subroutine does not return */
      sk_swift_fatal_error(sk_fatal_error_str,0xb,2,0xd00000000000003f,0x80000000005ccca0,
                   sk_xnu_upcalls_swift,0x25,2,0x1134,0);
    }
    sk_swift_epilogue();
  }
  else {
    uVar4 = sk_swift_err_code(0);
    sk_swift_release(uVar4,FUN_0065a550,0,0);
    *extraout_x1 = local_22c;
  }
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_00197be4 @ 0x00197be4   (est. sk_swift_helper)
 * Ghidra: void FUN_00197be4(undefined8 *param_1)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

/* WARNING: Removing unreachable block (ram,0x00197d0c) */

void FUN_00197be4(unsigned long *param_1)

{
    long lVar2;
  unsigned int *extraout_x1;
  long ctx_err;
  unsigned long res;
  unsigned long local_1a8;
  unsigned long local_1a0;
  unsigned long uStack_198;
  unsigned long uStack_190;
  unsigned long uStack_188;
  unsigned long local_180;
  unsigned long uStack_178;
  unsigned char local_170;
  unsigned int local_16c;
  unsigned char auStack_168 [56];
  unsigned char auStack_130 [56];
  unsigned char auStack_f8 [56];
  unsigned long local_c0;
  unsigned long uStack_b8;
  unsigned long uStack_b0;
  unsigned long uStack_a8;
  unsigned long local_a0;
  unsigned long uStack_98;
  unsigned char local_90;
  
  res = *param_1;
  local_1a0 = res;
  lVar2 = sk_swift_collection_count(&local_1a0,0x66a6b0,0x66a818);
  if (!SCARRY8(lVar2,8)) {
    sk_swift_frame_init(auStack_168,lVar2 + 8,0,&local_16c);
    if (ctx_err == 0) {
      sk_swift_string_begin(&local_1a0);
      sk_swift_type_hash(0xba2c4cb972f116aa);
      local_1a8 = res;
      sk_swift_collection_init(&local_1a8,0x65a870,0x66a6b0,0x65a798,0x66a818);
      uStack_b8 = uStack_198;
      local_c0 = local_1a0;
      uStack_a8 = uStack_188;
      uStack_b0 = uStack_190;
      uStack_98 = uStack_178;
      local_a0 = local_180;
      local_90 = local_170;
      sk_swift_buf_ctx(auStack_130);
      sk_swift_error_build(auStack_f8,auStack_130,&local_16c);
      sk_swift_epilogue();
    }
    else {
      res = sk_swift_err_code(0);
      sk_swift_release(res,FUN_0065a550,0,0);
      *extraout_x1 = local_16c;
    }
    return;
  }
                    /* WARNING: Does not return */
  __builtin_trap();
}





/*--------------------------------------------------------------------*/
/* FUN_00197dd0 @ 0x00197dd0   (est. sk_swift_helper)
 * Ghidra: void FUN_00197dd0(undefined8 param_1,undefined8 param_2,undefined8 param_3)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

unsigned long FUN_00197dd0(param_1, param_2, param_3)
  unsigned long param_1;
  unsigned long param_2;
  unsigned long param_3;

{
  code *pcVar2;
  unsigned char bv;
    unsigned char *unaff_x20;
  
  bv = *unaff_x20;
  pcVar2 = (code *)FUN_00023c78(param_3);
  (*pcVar2)(*(unsigned long *)(&DAT_004e7990 + (unsigned long)bv * 8),param_2,param_3);
  return 0;
}





/*--------------------------------------------------------------------*/
/* FUN_00197e48 @ 0x00197e48   (est. sk_swift_helper)
 * Ghidra: void FUN_00197e48(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_00197e48(void)
{
  FUN_00199b00();
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_00197e74 @ 0x00197e74   (est. sk_swift_helper)
 * Ghidra: undefined8 FUN_00197e74(undefined8 param_1,undefined8 param_2)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

unsigned long FUN_00197e74(unsigned long param_1,unsigned long param_2)

{
  code *pcVar1;
    long lVar2;
  unsigned long res;
  unsigned long extraout_x1;
  
  pcVar1 = (code *)FUN_00023d00(param_2);
  lVar2 = (*pcVar1)(param_1,param_2);
  if (lVar2 == 0x651eb370b558b85d) {
    res = 0;
  }
  else if (lVar2 == -0x541f50aee235204d) {
    res = 1;
  }
  else {
    if (lVar2 != -0x74a15ab3e083be3a) {
      sk_swift_precond_1(0x1c);
      sk_swift_abort_tail(0xe000000000000000);
      pcVar1 = (code *)sk_swift_meta(0x671848);
      (*pcVar1)(0x677790,0x671848);
      sk_swift_precond_2();
      sk_swift_abort_tail(extraout_x1);
                    /* WARNING: Subroutine does not return */
      sk_swift_fatal_error(sk_fatal_error_str,0xb,2,0xd00000000000001a,0x80000000005c9590,
                   sk_xnu_upcalls_swift,0x25,2,0xea9,0);
    }
    res = 2;
  }
  return res;
}





/*--------------------------------------------------------------------*/
/* FUN_00197fec @ 0x00197fec   (est. sk_swift_helper)
 * Ghidra: void FUN_00197fec(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_00197fec(void)

{
  unsigned int *in_x3;
  long ctx_err;
  unsigned int local_14;
  
  FUN_00197e48();
  if (ctx_err != 0) {
    *in_x3 = local_14;
  }
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_00198024 @ 0x00198024   (est. sk_swift_helper)
 * Ghidra: undefined4 FUN_00198024(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

unsigned int FUN_00198024(void)

{
  unsigned int uVar1;
  long ctx_err;
  
  uVar1 = FUN_00197dd0();
  if (ctx_err == 0) {
    uVar1 = 1;
  }
  return uVar1;
}





/*--------------------------------------------------------------------*/
/* FUN_00198028 @ 0x00198028   (est. sk_swift_helper)
 * Ghidra: undefined4 FUN_00198028(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

unsigned int FUN_00198028(void)

{
  unsigned int uVar1;
  long ctx_err;
  
  uVar1 = FUN_00197dd0();
  if (ctx_err == 0) {
    uVar1 = 1;
  }
  return uVar1;
}





/*--------------------------------------------------------------------*/
/* FUN_0019804c @ 0x0019804c   (est. sk_swift_helper)
 * Ghidra: void FUN_0019804c(undefined8 param_1,undefined8 param_2,undefined8 param_3)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

unsigned long FUN_0019804c(param_1, param_2, param_3)
  unsigned long param_1;
  unsigned long param_2;
  unsigned long param_3;

{
  code *pcVar2;
  unsigned char bv;
    unsigned char *unaff_x20;
  
  bv = *unaff_x20;
  pcVar2 = (code *)FUN_00023c78(param_3);
  (*pcVar2)(*(unsigned long *)(&DAT_004e79a8 + (unsigned long)bv * 8),param_2,param_3);
  return 0;
}





/*--------------------------------------------------------------------*/
/* FUN_001980c4 @ 0x001980c4   (est. sk_swift_helper)
 * Ghidra: void FUN_001980c4(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_001980c4(void)
{
  FUN_00199b00();
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_001980f0 @ 0x001980f0   (est. sk_swift_helper)
 * Ghidra: undefined8 FUN_001980f0(undefined8 param_1,undefined8 param_2)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

unsigned long FUN_001980f0(unsigned long param_1,unsigned long param_2)

{
  code *pcVar1;
    long lVar2;
  unsigned long res;
  unsigned long extraout_x1;
  
  pcVar1 = (code *)FUN_00023d00(param_2);
  lVar2 = (*pcVar1)(param_1,param_2);
  if (lVar2 == 0x26d51f659e0784ca) {
    res = 1;
  }
  else if (lVar2 == -0x41c0e5098faf722e) {
    res = 0;
  }
  else {
    if (lVar2 != -0x63a75e4db258e3ce) {
      sk_swift_precond_1(0x1c);
      sk_swift_abort_tail(0xe000000000000000);
      pcVar1 = (code *)sk_swift_meta(0x671848);
      (*pcVar1)(0x677790,0x671848);
      sk_swift_precond_2();
      sk_swift_abort_tail(extraout_x1);
                    /* WARNING: Subroutine does not return */
      sk_swift_fatal_error(sk_fatal_error_str,0xb,2,0xd00000000000001a,0x80000000005c9590,
                   sk_xnu_upcalls_swift,0x25,2,0xebe,0);
    }
    res = 2;
  }
  return res;
}





/*--------------------------------------------------------------------*/
/* FUN_00198268 @ 0x00198268   (est. sk_swift_helper)
 * Ghidra: void FUN_00198268(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_00198268(void)

{
  unsigned int *in_x3;
  long ctx_err;
  unsigned int local_14;
  
  FUN_001980c4();
  if (ctx_err != 0) {
    *in_x3 = local_14;
  }
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_001982a0 @ 0x001982a0   (est. sk_swift_helper)
 * Ghidra: undefined4 FUN_001982a0(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

unsigned int FUN_001982a0(void)

{
  unsigned int uVar1;
  long ctx_err;
  
  uVar1 = FUN_0019804c();
  if (ctx_err == 0) {
    uVar1 = 1;
  }
  return uVar1;
}





/*--------------------------------------------------------------------*/
/* FUN_001982a4 @ 0x001982a4   (est. sk_swift_helper)
 * Ghidra: undefined4 FUN_001982a4(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

unsigned int FUN_001982a4(void)

{
  unsigned int uVar1;
  long ctx_err;
  
  uVar1 = FUN_0019804c();
  if (ctx_err == 0) {
    uVar1 = 1;
  }
  return uVar1;
}





/*--------------------------------------------------------------------*/
/* FUN_001982c8 @ 0x001982c8   (est. sk_swift_helper)
 * Ghidra: undefined8 FUN_001982c8(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

unsigned long FUN_001982c8(void)

{
  FUN_0018200c();
  return 4;
}





/*--------------------------------------------------------------------*/
/* FUN_00198300 @ 0x00198300   (est. sk_swift_helper)
 * Ghidra: undefined4 FUN_00198300(undefined8 param_1,undefined8 param_2,undefined8 param_3)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

unsigned int FUN_00198300(param_1, param_2, param_3)
  unsigned long param_1;
  unsigned long param_2;
  unsigned long param_3;

{
  unsigned int uVar1;
  unsigned long err;
  long ctx_err;
  
  err = FUN_0018200c();
  uVar1 = FUN_00198370(err,param_2,param_3);
  if (ctx_err == 0) {
    uVar1 = 1;
  }
  return uVar1;
}





/*--------------------------------------------------------------------*/
/* FUN_00198370 @ 0x00198370   (est. sk_swift_helper)
 * Ghidra: void FUN_00198370(ulong param_1,undefined8 param_2,undefined8 param_3)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

unsigned long FUN_00198370(unsigned long param_1,unsigned long param_2,unsigned long param_3)

{
  code *pcVar2;
  unsigned int uVar1;
    
  uVar1 = *(unsigned int *)(&DAT_004e79c0 + (param_1 & 0xff) * 4);
  pcVar2 = (code *)FUN_000bd0e4(param_3);
  (*pcVar2)(uVar1,param_2,param_3);
  return 0;
}





/*--------------------------------------------------------------------*/
/* FUN_001983d4 @ 0x001983d4   (est. sk_swift_helper)
 * Ghidra: void FUN_001983d4(undefined1 *param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_001983d4(param_1, param_2, param_3, param_4, param_5)
  unsigned char * param_1;
  unsigned long param_2;
  unsigned long param_3;
  unsigned long param_4;
  unsigned int * param_5;

{
  unsigned int uVar1;
  long ctx_err;
  unsigned char local_21;
  
  uVar1 = FUN_00198438(param_3,param_4);
  if (ctx_err == 0) {
    FUN_0018e38c(&local_21);
    *param_1 = local_21;
  }
  else {
    *param_5 = uVar1;
  }
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_00198438 @ 0x00198438   (est. sk_swift_helper)
 * Ghidra: void FUN_00198438(undefined8 param_1,undefined8 param_2)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

unsigned long FUN_00198438(unsigned long param_1,unsigned long param_2)

{
  code *pcVar2;
  char kind;
    unsigned long extraout_x1;
  
  pcVar2 = (code *)FUN_001477c4(param_2);
  (*pcVar2)(param_1,param_2);
  kind = FUN_0019a830();
  if (kind != '\x16') {
  return 0;
  }
  sk_swift_precond_1(0x2c);
  sk_swift_abort_tail(0xe000000000000000);
  pcVar2 = (code *)sk_swift_meta(0x671298);
  (*pcVar2)(0x6776f0,0x671298);
  sk_swift_precond_2();
  sk_swift_abort_tail(extraout_x1);
                    /* WARNING: Subroutine does not return */
  sk_swift_fatal_error(sk_fatal_error_str,0xb,2,0xd00000000000002a,0x80000000005cc0b0,
               sk_xnu_upcalls_swift,0x25,2,0xecc,0);
}





/*--------------------------------------------------------------------*/
/* FUN_00198564 @ 0x00198564   (est. sk_swift_helper)
 * Ghidra: void FUN_00198564(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_00198564(void)

{
  unsigned int *in_x3;
  long ctx_err;
  unsigned int local_14;
  
  FUN_001983d4();
  if (ctx_err != 0) {
    *in_x3 = local_14;
  }
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019859c @ 0x0019859c   (est. sk_swift_helper)
 * Ghidra: undefined4 FUN_0019859c(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

unsigned int FUN_0019859c(void)

{
  unsigned int uVar1;
  long ctx_err;
  
  uVar1 = FUN_00198300();
  if (ctx_err == 0) {
    uVar1 = 1;
  }
  return uVar1;
}





/*--------------------------------------------------------------------*/
/* FUN_001985a0 @ 0x001985a0   (est. sk_swift_helper)
 * Ghidra: undefined4 FUN_001985a0(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

unsigned int FUN_001985a0(void)

{
  unsigned int uVar1;
  long ctx_err;
  
  uVar1 = FUN_00198300();
  if (ctx_err == 0) {
    uVar1 = 1;
  }
  return uVar1;
}





/*--------------------------------------------------------------------*/
/* FUN_001985c4 @ 0x001985c4   (est. sk_swift_helper)
 * Ghidra: void FUN_001985c4(undefined8 param_1,undefined8 param_2,undefined8 param_3)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

unsigned long FUN_001985c4(param_1, param_2, param_3)
  unsigned long param_1;
  unsigned long param_2;
  unsigned long param_3;

{
  code *pcVar3;
  unsigned long uVar1;
  char kind;
    char *unaff_x20;
  
  kind = *unaff_x20;
  pcVar3 = (code *)FUN_00023c78(param_3);
  uVar1 = 0x87b520134b24938;
  if (kind != '\x01') {
    uVar1 = 0x10ba472b336e7a50;
  }
  (*pcVar3)(uVar1,param_2,param_3);
  return 0;
}





/*--------------------------------------------------------------------*/
/* FUN_00198658 @ 0x00198658   (est. sk_swift_helper)
 * Ghidra: void FUN_00198658(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_00198658(void)
{
  FUN_001991f4();
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_00198684 @ 0x00198684   (est. sk_swift_helper)
 * Ghidra: undefined8 FUN_00198684(undefined8 param_1,undefined8 param_2)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

unsigned long FUN_00198684(unsigned long param_1,unsigned long param_2)

{
  code *pcVar1;
    long lVar2;
  unsigned long res;
  unsigned long extraout_x1;
  
  pcVar1 = (code *)FUN_00023d00(param_2);
  lVar2 = (*pcVar1)(param_1,param_2);
  if (lVar2 == 0x87b520134b24938) {
    res = 1;
  }
  else {
    if (lVar2 != 0x10ba472b336e7a50) {
      sk_swift_precond_1(0x1c);
      sk_swift_abort_tail(0xe000000000000000);
      pcVar1 = (code *)sk_swift_meta(0x671848);
      (*pcVar1)(0x677790,0x671848);
      sk_swift_precond_2();
      sk_swift_abort_tail(extraout_x1);
                    /* WARNING: Subroutine does not return */
      sk_swift_fatal_error(sk_fatal_error_str,0xb,2,0xd00000000000001a,0x80000000005c9590,
                   sk_xnu_upcalls_swift,0x25,2,0xed4,0);
    }
    res = 0;
  }
  return res;
}





/*--------------------------------------------------------------------*/
/* FUN_001987dc @ 0x001987dc   (est. sk_swift_helper)
 * Ghidra: void FUN_001987dc(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_001987dc(void)

{
  unsigned int *in_x3;
  long ctx_err;
  unsigned int local_14;
  
  FUN_00198658();
  if (ctx_err != 0) {
    *in_x3 = local_14;
  }
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_00198814 @ 0x00198814   (est. sk_swift_helper)
 * Ghidra: undefined4 FUN_00198814(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

unsigned int FUN_00198814(void)

{
  unsigned int uVar1;
  long ctx_err;
  
  uVar1 = FUN_001985c4();
  if (ctx_err == 0) {
    uVar1 = 1;
  }
  return uVar1;
}





/*--------------------------------------------------------------------*/
/* FUN_00198818 @ 0x00198818   (est. sk_swift_helper)
 * Ghidra: undefined4 FUN_00198818(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

unsigned int FUN_00198818(void)

{
  unsigned int uVar1;
  long ctx_err;
  
  uVar1 = FUN_001985c4();
  if (ctx_err == 0) {
    uVar1 = 1;
  }
  return uVar1;
}





/*--------------------------------------------------------------------*/
/* FUN_0019883c @ 0x0019883c   (est. sk_swift_helper)
 * Ghidra: void FUN_0019883c(undefined8 param_1,undefined8 param_2,undefined8 param_3)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

unsigned long FUN_0019883c(param_1, param_2, param_3)
  unsigned long param_1;
  unsigned long param_2;
  unsigned long param_3;

{
  code *pcVar2;
  char kind;
    char *unaff_x20;
  
  kind = *unaff_x20;
  pcVar2 = (code *)FUN_000bd0e4(param_3);
  (*pcVar2)(kind == '\x01',param_2,param_3);
  return 0;
}





/*--------------------------------------------------------------------*/
/* FUN_001988b4 @ 0x001988b4   (est. sk_swift_helper)
 * Ghidra: void FUN_001988b4(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_001988b4(void)
{
  FUN_001991f4();
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_001988e0 @ 0x001988e0   (est. sk_swift_helper)
 * Ghidra: void FUN_001988e0(undefined8 param_1,undefined8 param_2)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_001988e0(unsigned long param_1,unsigned long param_2)

{
  code *pcVar2;
  unsigned int uVar1;
    unsigned long extraout_x1;
  
  pcVar2 = (code *)FUN_001477c4(param_2);
  uVar1 = (*pcVar2)(param_1,param_2);
  if (uVar1 < 2) {
    return;
  }
  sk_swift_precond_1(0x28);
  sk_swift_abort_tail(0xe000000000000000);
  pcVar2 = (code *)sk_swift_meta(0x671298);
  (*pcVar2)(0x6776f0,0x671298);
  sk_swift_precond_2();
  sk_swift_abort_tail(extraout_x1);
                    /* WARNING: Subroutine does not return */
  sk_swift_fatal_error(sk_fatal_error_str,0xb,2,0xd000000000000026,0x80000000005cc0e0,
               sk_xnu_upcalls_swift,0x25,2,0xee0,0);
}





/*--------------------------------------------------------------------*/
/* FUN_00198a04 @ 0x00198a04   (est. sk_swift_helper)
 * Ghidra: void FUN_00198a04(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_00198a04(void)

{
  unsigned int *in_x3;
  long ctx_err;
  unsigned int local_14;
  
  FUN_001988b4();
  if (ctx_err != 0) {
    *in_x3 = local_14;
  }
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_00198a3c @ 0x00198a3c   (est. sk_swift_helper)
 * Ghidra: undefined4 FUN_00198a3c(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

unsigned int FUN_00198a3c(void)

{
  unsigned int uVar1;
  long ctx_err;
  
  uVar1 = FUN_0019883c();
  if (ctx_err == 0) {
    uVar1 = 1;
  }
  return uVar1;
}





/*--------------------------------------------------------------------*/
/* FUN_00198a40 @ 0x00198a40   (est. sk_swift_helper)
 * Ghidra: undefined4 FUN_00198a40(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

unsigned int FUN_00198a40(void)

{
  unsigned int uVar1;
  long ctx_err;
  
  uVar1 = FUN_0019883c();
  if (ctx_err == 0) {
    uVar1 = 1;
  }
  return uVar1;
}





/*--------------------------------------------------------------------*/
/* FUN_00198a64 @ 0x00198a64   (est. sk_swift_helper)
 * Ghidra: long FUN_00198a64(undefined1 *param_1)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

long FUN_00198a64(unsigned char *param_1)

{
    long lVar2;
  unsigned char local_1c [4];
  unsigned long local_18;
  
  local_1c[0] = *param_1;
  local_18 = *(unsigned long *)(param_1 + 4);
  lVar2 = sk_swift_collection_count(local_1c,0x66a1d0,0x66a740);
  if (SCARRY8(lVar2,4)) {
                    /* WARNING: Does not return */
    __builtin_trap();
  }
  if (!SCARRY8(lVar2 + 4,4)) {
    return lVar2 + 8;
  }
                    /* WARNING: Does not return */
  __builtin_trap();
}





/*--------------------------------------------------------------------*/
/* FUN_00198acc @ 0x00198acc   (est. sk_swift_helper)
 * Ghidra: undefined4 FUN_00198acc(undefined8 param_1)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

unsigned int FUN_00198acc(param_1)
  unsigned long param_1;

{
  unsigned int uVar1;
  long ctx_err;
  
  uVar1 = FUN_00198b08(param_1);
  if (ctx_err == 0) {
    uVar1 = 1;
  }
  return uVar1;
}





/*--------------------------------------------------------------------*/
/* FUN_00198b08 @ 0x00198b08   (est. sk_swift_helper)
 * Ghidra: void FUN_00198b08(long param_1,undefined8 param_2,undefined8 param_3)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

unsigned long FUN_00198b08(long param_1,unsigned long param_2,unsigned long param_3)

{
  code *pcVar3;
  unsigned int uVar1;
  unsigned int err;
    long ctx_err;
  
  uVar1 = *(unsigned int *)(param_1 + 4);
  err = *(unsigned int *)(param_1 + 8);
  sk_swift_collection_init(param_1,param_2,0x66a1d0,param_3,0x66a740);
  if (ctx_err == 0) {
    pcVar3 = (code *)FUN_000bd0e4(param_3);
    (*pcVar3)(uVar1,param_2,param_3);
    (*pcVar3)(err,param_2,param_3);
  }
  return 0;
}





/*--------------------------------------------------------------------*/
/* FUN_00198bac @ 0x00198bac   (est. sk_swift_helper)
 * Ghidra: void FUN_00198bac(undefined1 *param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_00198bac(param_1, param_2, param_3, param_4, param_5)
  unsigned char * param_1;
  unsigned long param_2;
  unsigned long param_3;
  unsigned long param_4;
  unsigned int * param_5;

{
  long ctx_err;
  unsigned char local_3c [4];
  unsigned long local_38;
  unsigned int local_24;
  
  FUN_00198c20(local_3c,param_3,param_4,&local_24);
  if (ctx_err == 0) {
    *param_1 = local_3c[0];
    *(unsigned long *)(param_1 + 4) = local_38;
  }
  else {
    *param_5 = local_24;
  }
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_00198c20 @ 0x00198c20   (est. sk_swift_helper)
 * Ghidra: void FUN_00198c20(undefined1 *param_1,undefined8 param_2,undefined8 param_3,undefined4 *param_4)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_00198c20(unsigned char *param_1,unsigned long param_2,unsigned long param_3,unsigned int *param_4)

{
  code *pcVar3;
  unsigned int uVar1;
  unsigned int err;
    long ctx_err;
  unsigned int local_48;
  unsigned char local_41;
  
  sk_swift_collection_op(&local_41,0x66a1d0,param_2,0x66a1d0,param_3,0x66a738,&local_48);
  if (ctx_err == 0) {
    *param_1 = local_41;
    pcVar3 = (code *)FUN_001477c4(param_3);
    uVar1 = (*pcVar3)(param_2,param_3);
    err = (*pcVar3)(param_2,param_3);
    *(unsigned int *)(param_1 + 4) = uVar1;
    *(unsigned int *)(param_1 + 8) = err;
  }
  else {
    *param_4 = local_48;
  }
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_00198cf0 @ 0x00198cf0   (est. sk_swift_helper)
 * Ghidra: void FUN_00198cf0(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_00198cf0(void)

{
  unsigned int *in_x3;
  long ctx_err;
  unsigned int local_14;
  
  FUN_00198bac();
  if (ctx_err != 0) {
    *in_x3 = local_14;
  }
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_00198d28 @ 0x00198d28   (est. sk_swift_helper)
 * Ghidra: undefined4 FUN_00198d28(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

unsigned int FUN_00198d28(void)

{
  unsigned int uVar1;
  long ctx_err;
  
  uVar1 = FUN_00198acc();
  if (ctx_err == 0) {
    uVar1 = 1;
  }
  return uVar1;
}





/*--------------------------------------------------------------------*/
/* FUN_00198d2c @ 0x00198d2c   (est. sk_swift_helper)
 * Ghidra: undefined4 FUN_00198d2c(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

unsigned int FUN_00198d2c(void)

{
  unsigned int uVar1;
  long ctx_err;
  
  uVar1 = FUN_00198acc();
  if (ctx_err == 0) {
    uVar1 = 1;
  }
  return uVar1;
}





/*--------------------------------------------------------------------*/
/* FUN_00198d50 @ 0x00198d50   (est. sk_swift_helper)
 * Ghidra: void FUN_00198d50(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

unsigned long FUN_00198d50(void)
{
  FUN_0019914c();
  return 0;
}





/*--------------------------------------------------------------------*/
/* FUN_00198d68 @ 0x00198d68   (est. sk_swift_helper)
 * Ghidra: void FUN_00198d68(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_00198d68(void)
{
  FUN_001991f4();
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_00198d94 @ 0x00198d94   (est. sk_swift_helper)
 * Ghidra: undefined8 FUN_00198d94(undefined8 param_1,undefined8 param_2)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

unsigned long FUN_00198d94(unsigned long param_1,unsigned long param_2)

{
  code *pcVar2;
  int iVar1;
    unsigned long res;
  unsigned long extraout_x1;
  
  pcVar2 = (code *)FUN_001477c4(param_2);
  iVar1 = (*pcVar2)(param_1,param_2);
  if (iVar1 == 1) {
    res = 0;
  }
  else {
    if (iVar1 != 2) {
      sk_swift_precond_1(0x21);
      sk_swift_abort_tail(0xe000000000000000);
      pcVar2 = (code *)sk_swift_meta(0x671298);
      (*pcVar2)(0x6776f0,0x671298);
      sk_swift_precond_2();
      sk_swift_abort_tail(extraout_x1);
                    /* WARNING: Subroutine does not return */
      sk_swift_fatal_error(sk_fatal_error_str,0xb,2,0xd00000000000001f,0x80000000005ccc80,
                   sk_xnu_upcalls_swift,0x25,2,0xeef,0);
    }
    res = 1;
  }
  return res;
}





/*--------------------------------------------------------------------*/
/* FUN_00198ecc @ 0x00198ecc   (est. sk_swift_helper)
 * Ghidra: void FUN_00198ecc(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_00198ecc(void)

{
  unsigned int *in_x3;
  long ctx_err;
  unsigned int local_14;
  
  FUN_00198d68();
  if (ctx_err != 0) {
    *in_x3 = local_14;
  }
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_00198f04 @ 0x00198f04   (est. sk_swift_helper)
 * Ghidra: undefined4 FUN_00198f04(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

unsigned int FUN_00198f04(void)
{
  unsigned int uVar1;
  long ctx_err;
  
  uVar1 = FUN_00198d50();
  if (ctx_err == 0) {
    uVar1 = 1;
  }
  return uVar1;
}





/*--------------------------------------------------------------------*/
/* FUN_00198f2c @ 0x00198f2c   (est. sk_swift_helper)
 * Ghidra: void FUN_00198f2c(undefined8 param_1,undefined8 param_2,undefined8 param_3)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

unsigned long FUN_00198f2c(param_1, param_2, param_3)
  unsigned long param_1;
  unsigned long param_2;
  unsigned long param_3;

{
  code *pcVar1;
    
  pcVar1 = (code *)FUN_000bd0e4(param_3);
  (*pcVar1)(1,param_2,param_3);
  return 0;
}





/*--------------------------------------------------------------------*/
/* FUN_00198f8c @ 0x00198f8c   (est. sk_swift_helper)
 * Ghidra: void FUN_00198f8c(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined4 *param_4)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_00198f8c(param_1, param_2, param_3, param_4)
  unsigned long param_1;
  unsigned long param_2;
  unsigned long param_3;
  unsigned int * param_4;

{
  unsigned int uVar1;
  long ctx_err;
  
  uVar1 = FUN_00198fc8(param_2,param_3);
  if (ctx_err != 0) {
    *param_4 = uVar1;
  }
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_00198fc8 @ 0x00198fc8   (est. sk_swift_helper)
 * Ghidra: void FUN_00198fc8(undefined8 param_1,undefined8 param_2)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

unsigned long FUN_00198fc8(unsigned long param_1,unsigned long param_2)

{
  code *pcVar2;
  int iVar1;
    unsigned long extraout_x1;
  
  pcVar2 = (code *)FUN_001477c4(param_2);
  iVar1 = (*pcVar2)(param_1,param_2);
  if (iVar1 == 1) {
  return 0;
  }
  sk_swift_precond_1(0x2a);
  sk_swift_abort_tail(0xe000000000000000);
  pcVar2 = (code *)sk_swift_meta(0x671298);
  (*pcVar2)(0x6776f0,0x671298);
  sk_swift_precond_2();
  sk_swift_abort_tail(extraout_x1);
                    /* WARNING: Subroutine does not return */
  sk_swift_fatal_error(sk_fatal_error_str,0xb,2,0xd000000000000028,0x80000000005cc350,
               sk_xnu_upcalls_swift,0x25,2,0xf09,0);
}





/*--------------------------------------------------------------------*/
/* FUN_001990ec @ 0x001990ec   (est. sk_swift_helper)
 * Ghidra: void FUN_001990ec(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_001990ec(void)

{
  unsigned int *in_x3;
  long ctx_err;
  unsigned int local_14;
  
  FUN_00198f8c();
  if (ctx_err != 0) {
    *in_x3 = local_14;
  }
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_00199124 @ 0x00199124   (est. sk_swift_helper)
 * Ghidra: undefined4 FUN_00199124(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

unsigned int FUN_00199124(void)

{
  unsigned int uVar1;
  long ctx_err;
  
  uVar1 = FUN_00198f2c();
  if (ctx_err == 0) {
    uVar1 = 1;
  }
  return uVar1;
}





/*--------------------------------------------------------------------*/
/* FUN_00199128 @ 0x00199128   (est. sk_swift_helper)
 * Ghidra: undefined4 FUN_00199128(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

unsigned int FUN_00199128(void)

{
  unsigned int uVar1;
  long ctx_err;
  
  uVar1 = FUN_00198f2c();
  if (ctx_err == 0) {
    uVar1 = 1;
  }
  return uVar1;
}





/*--------------------------------------------------------------------*/
/* FUN_0019914c @ 0x0019914c   (est. sk_swift_helper)
 * Ghidra: void FUN_0019914c(undefined8 param_1,undefined8 param_2,undefined8 param_3)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019914c(param_1, param_2, param_3)
  unsigned long param_1;
  unsigned long param_2;
  unsigned long param_3;

{
  code *pcVar1;
    unsigned int err;
  char *unaff_x20;
  
  err = 1;
  if (*unaff_x20 == '\x01') {
    err = 2;
  }
  pcVar1 = (code *)FUN_000bd0e4(param_3);
  (*pcVar1)(err,param_2,param_3);
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_001991c8 @ 0x001991c8   (est. sk_swift_helper)
 * Ghidra: void FUN_001991c8(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_001991c8(void)
{
  FUN_001991f4();
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_001991f4 @ 0x001991f4   (est. sk_swift_helper)
 * Ghidra: void FUN_001991f4(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_001991f4(param_1, param_2, param_3, param_4, param_5, param_6)
  unsigned long param_1;
  unsigned long param_2;
  unsigned long param_3;
  unsigned long param_4;
  unsigned int * param_5;
  code * param_6;

{
  unsigned int uVar1;
  long ctx_err;
  
  uVar1 = (*param_6)(param_3,param_4);
  if (ctx_err == 0) {
    *(bool *)param_1 = (uVar1 & 0xff) == 1;
  }
  else {
    *param_5 = uVar1;
  }
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_00199254 @ 0x00199254   (est. sk_swift_helper)
 * Ghidra: undefined8 FUN_00199254(undefined8 param_1,undefined8 param_2)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

unsigned long FUN_00199254(unsigned long param_1,unsigned long param_2)

{
  code *pcVar2;
  int iVar1;
    unsigned long res;
  unsigned long extraout_x1;
  
  pcVar2 = (code *)FUN_001477c4(param_2);
  iVar1 = (*pcVar2)(param_1,param_2);
  if (iVar1 == 1) {
    res = 0;
  }
  else {
    if (iVar1 != 2) {
      sk_swift_precond_1(0x27);
      sk_swift_abort_tail(0xe000000000000000);
      pcVar2 = (code *)sk_swift_meta(0x671298);
      (*pcVar2)(0x6776f0,0x671298);
      sk_swift_precond_2();
      sk_swift_abort_tail(extraout_x1);
                    /* WARNING: Subroutine does not return */
      sk_swift_fatal_error(sk_fatal_error_str,0xb,2,0xd000000000000025,0x80000000005cc220,
                   sk_xnu_upcalls_swift,0x25,2,0xf11,0);
    }
    res = 1;
  }
  return res;
}





/*--------------------------------------------------------------------*/
/* FUN_0019938c @ 0x0019938c   (est. sk_swift_helper)
 * Ghidra: void FUN_0019938c(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019938c(void)

{
  unsigned int *in_x3;
  long ctx_err;
  unsigned int local_14;
  
  FUN_001991c8();
  if (ctx_err != 0) {
    *in_x3 = local_14;
  }
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_001993c4 @ 0x001993c4   (est. sk_swift_helper)
 * Ghidra: undefined4 FUN_001993c4(undefined8 param_1,undefined8 param_2,undefined8 param_3)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

unsigned int FUN_001993c4(param_1, param_2, param_3)
  unsigned long param_1;
  unsigned long param_2;
  unsigned long param_3;

{
  unsigned int uVar1;
  unsigned long err;
  unsigned long *unaff_x20;
  long ctx_err;
  unsigned long res;
  
  res = *unaff_x20;
  err = sk_alloc_pages(res);
  uVar1 = FUN_0019957c(err,param_2,param_3);
  FUN_0036b118(res);
  if (ctx_err == 0) {
    uVar1 = 1;
  }
  return uVar1;
}





/*--------------------------------------------------------------------*/
/* FUN_00199438 @ 0x00199438   (est. sk_swift_helper)
 * Ghidra: void FUN_00199438(long param_1)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_00199438(long param_1)

{
  code *pcVar1;
    unsigned long extraout_x1;
  long lVar2;
  
  if (*(long *)(param_1 + 0x10) == 0x20) {
    lVar2 = 0;
    do {
      sk_swift_type_hash(*(unsigned long *)(param_1 + 0x20 + lVar2));
      lVar2 = lVar2 + 8;
    } while (lVar2 != 0x100);
    return;
  }
  sk_swift_precond_1(0x3b);
  sk_swift_precond_2(0x5f2865646f636e65,0xea0000000000293a);
  sk_swift_precond_2(0xd000000000000037,0x80000000005cc150);
  pcVar1 = (code *)sk_swift_meta(0x6720e0);
  (*pcVar1)(0x677880,0x6720e0);
  sk_swift_precond_2();
  sk_swift_abort_tail(extraout_x1);
                    /* WARNING: Subroutine does not return */
  sk_swift_fatal_error(sk_fatal_error_str,0xb,2,0,0xe000000000000000,
               sk_xnu_upcalls_swift,0x25,2,DAT_0000118f,0);
}





/*--------------------------------------------------------------------*/
/* FUN_0019957c @ 0x0019957c   (est. sk_swift_helper)
 * Ghidra: void FUN_0019957c(long param_1,undefined8 param_2,undefined8 param_3)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

unsigned long FUN_0019957c(long param_1,unsigned long param_2,unsigned long param_3)

{
  code *pcVar1;
    unsigned long extraout_x1;
  long lVar2;
  
  if (*(long *)(param_1 + 0x10) == 0x20) {
    pcVar1 = (code *)FUN_00023c78(param_3);
    lVar2 = 0;
    do {
      (*pcVar1)(*(unsigned long *)(param_1 + 0x20 + lVar2),param_2,param_3);
      lVar2 = lVar2 + 8;
    } while (lVar2 != 0x100);
  return 0;
  }
  sk_swift_precond_1(0x3b);
  sk_swift_precond_2(0x5f2865646f636e65,0xea0000000000293a);
  sk_swift_precond_2(0xd000000000000037,0x80000000005cc150);
  pcVar1 = (code *)sk_swift_meta(0x6720e0);
  (*pcVar1)(0x677880,0x6720e0);
  sk_swift_precond_2();
  sk_swift_abort_tail(extraout_x1);
                    /* WARNING: Subroutine does not return */
  sk_swift_fatal_error(sk_fatal_error_str,0xb,2,0,0xe000000000000000,
               sk_xnu_upcalls_swift,0x25,2,DAT_0000118f,0);
}





/*--------------------------------------------------------------------*/
/* FUN_001996f0 @ 0x001996f0   (est. sk_swift_helper)
 * Ghidra: undefined4 FUN_001996f0(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

unsigned int FUN_001996f0(void)

{
  unsigned int uVar1;
  long ctx_err;
  
  uVar1 = FUN_001993c4();
  if (ctx_err == 0) {
    uVar1 = 1;
  }
  return uVar1;
}





/*--------------------------------------------------------------------*/
/* FUN_001996f4 @ 0x001996f4   (est. sk_swift_helper)
 * Ghidra: undefined4 FUN_001996f4(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

unsigned int FUN_001996f4(void)

{
  unsigned int uVar1;
  long ctx_err;
  
  uVar1 = FUN_001993c4();
  if (ctx_err == 0) {
    uVar1 = 1;
  }
  return uVar1;
}





/*--------------------------------------------------------------------*/
/* FUN_00199718 @ 0x00199718   (est. sk_swift_helper)
 * Ghidra: undefined4 FUN_00199718(undefined8 param_1,undefined8 param_2,undefined8 param_3)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

unsigned int FUN_00199718(param_1, param_2, param_3)
  unsigned long param_1;
  unsigned long param_2;
  unsigned long param_3;

{
  unsigned int uVar1;
  unsigned long err;
  unsigned long *unaff_x20;
  long ctx_err;
  unsigned long res;
  
  res = *unaff_x20;
  err = sk_alloc_pages(res);
  uVar1 = FUN_001998c8(err,param_2,param_3);
  FUN_0036b118(res);
  if (ctx_err == 0) {
    uVar1 = 1;
  }
  return uVar1;
}





/*--------------------------------------------------------------------*/
/* FUN_0019978c @ 0x0019978c   (est. sk_swift_helper)
 * Ghidra: void FUN_0019978c(long param_1)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019978c(long param_1)

{
  code *pcVar1;
    unsigned long extraout_x1;
  
  if (*(long *)(param_1 + 0x10) == 2) {
    sk_swift_type_hash(*(unsigned long *)(param_1 + 0x20));
    sk_swift_type_hash(*(unsigned long *)(param_1 + 0x28));
    return;
  }
  sk_swift_precond_1(0x3a);
  sk_swift_precond_2(0x5f2865646f636e65,0xea0000000000293a);
  sk_swift_precond_2(0xd000000000000036,0x80000000005cc190);
  pcVar1 = (code *)sk_swift_meta(0x6720e0);
  (*pcVar1)(0x677880,0x6720e0);
  sk_swift_precond_2();
  sk_swift_abort_tail(extraout_x1);
                    /* WARNING: Subroutine does not return */
  sk_swift_fatal_error(sk_fatal_error_str,0xb,2,0,0xe000000000000000,
               sk_xnu_upcalls_swift,0x25,2,DAT_00001197,0);
}





/*--------------------------------------------------------------------*/
/* FUN_001998c8 @ 0x001998c8   (est. sk_swift_helper)
 * Ghidra: void FUN_001998c8(long param_1,undefined8 param_2,undefined8 param_3)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

unsigned long FUN_001998c8(long param_1,unsigned long param_2,unsigned long param_3)

{
  code *pcVar1;
    unsigned long extraout_x1;
  
  if (*(long *)(param_1 + 0x10) == 2) {
    pcVar1 = (code *)FUN_00023c78(param_3);
    (*pcVar1)(*(unsigned long *)(param_1 + 0x20),param_2,param_3);
    (*pcVar1)(*(unsigned long *)(param_1 + 0x28),param_2,param_3);
  return 0;
  }
  sk_swift_precond_1(0x3a);
  sk_swift_precond_2(0x5f2865646f636e65,0xea0000000000293a);
  sk_swift_precond_2(0xd000000000000036,0x80000000005cc190);
  pcVar1 = (code *)sk_swift_meta(0x6720e0);
  (*pcVar1)(0x677880,0x6720e0);
  sk_swift_precond_2();
  sk_swift_abort_tail(extraout_x1);
                    /* WARNING: Subroutine does not return */
  sk_swift_fatal_error(sk_fatal_error_str,0xb,2,0,0xe000000000000000,
               sk_xnu_upcalls_swift,0x25,2,DAT_00001197,0);
}





/*--------------------------------------------------------------------*/
/* FUN_00199a34 @ 0x00199a34   (est. sk_swift_helper)
 * Ghidra: undefined4 FUN_00199a34(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

unsigned int FUN_00199a34(void)

{
  unsigned int uVar1;
  long ctx_err;
  
  uVar1 = FUN_00199718();
  if (ctx_err == 0) {
    uVar1 = 1;
  }
  return uVar1;
}





/*--------------------------------------------------------------------*/
/* FUN_00199a38 @ 0x00199a38   (est. sk_swift_helper)
 * Ghidra: undefined4 FUN_00199a38(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

unsigned int FUN_00199a38(void)

{
  unsigned int uVar1;
  long ctx_err;
  
  uVar1 = FUN_00199718();
  if (ctx_err == 0) {
    uVar1 = 1;
  }
  return uVar1;
}





/*--------------------------------------------------------------------*/
/* FUN_00199a5c @ 0x00199a5c   (est. sk_swift_helper)
 * Ghidra: void FUN_00199a5c(undefined8 param_1,undefined8 param_2,undefined8 param_3)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

unsigned long FUN_00199a5c(param_1, param_2, param_3)
  unsigned long param_1;
  unsigned long param_2;
  unsigned long param_3;

{
  code *pcVar2;
  unsigned char bv;
    unsigned char *unaff_x20;
  
  bv = *unaff_x20;
  pcVar2 = (code *)FUN_00023c78(param_3);
  (*pcVar2)(*(unsigned long *)(&DAT_004e7a18 + (unsigned long)bv * 8),param_2,param_3);
  return 0;
}





/*--------------------------------------------------------------------*/
/* FUN_00199ad4 @ 0x00199ad4   (est. sk_swift_helper)
 * Ghidra: void FUN_00199ad4(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_00199ad4(void)
{
  FUN_00199b00();
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_00199b00 @ 0x00199b00   (est. sk_swift_helper)
 * Ghidra: void FUN_00199b00(undefined1 *param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_00199b00(param_1, param_2, param_3, param_4, param_5, param_6)
  unsigned char * param_1;
  unsigned long param_2;
  unsigned long param_3;
  unsigned long param_4;
  unsigned int * param_5;
  code * param_6;

{
  unsigned int uVar1;
  long ctx_err;
  
  uVar1 = (*param_6)(param_3,param_4);
  if (ctx_err == 0) {
    *param_1 = (char)uVar1;
  }
  else {
    *param_5 = uVar1;
  }
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_00199b54 @ 0x00199b54   (est. sk_swift_helper)
 * Ghidra: undefined8 FUN_00199b54(undefined8 param_1,undefined8 param_2)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

unsigned long FUN_00199b54(unsigned long param_1,unsigned long param_2)

{
  code *pcVar1;
    long lVar2;
  unsigned long res;
  unsigned long extraout_x1;
  
  pcVar1 = (code *)FUN_00023d00(param_2);
  lVar2 = (*pcVar1)(param_1,param_2);
  if (lVar2 == 0x674d5d542b7e619f) {
    res = 1;
  }
  else if (lVar2 == 0x1b94bb5431fde496) {
    res = 0;
  }
  else {
    if (lVar2 != -0x589d4972ef0ef1dc) {
      sk_swift_precond_1(0x1c);
      sk_swift_abort_tail(0xe000000000000000);
      pcVar1 = (code *)sk_swift_meta(0x671848);
      (*pcVar1)(0x677790,0x671848);
      sk_swift_precond_2();
      sk_swift_abort_tail(extraout_x1);
                    /* WARNING: Subroutine does not return */
      sk_swift_fatal_error(sk_fatal_error_str,0xb,2,0xd00000000000001a,0x80000000005c9590,
                   sk_xnu_upcalls_swift,0x25,2,0xf1f,0);
    }
    res = 2;
  }
  return res;
}





/*--------------------------------------------------------------------*/
/* FUN_00199ccc @ 0x00199ccc   (est. sk_swift_helper)
 * Ghidra: void FUN_00199ccc(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_00199ccc(void)

{
  unsigned int *in_x3;
  long ctx_err;
  unsigned int local_14;
  
  FUN_00199ad4();
  if (ctx_err != 0) {
    *in_x3 = local_14;
  }
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_00199d04 @ 0x00199d04   (est. sk_swift_helper)
 * Ghidra: undefined4 FUN_00199d04(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

unsigned int FUN_00199d04(void)

{
  unsigned int uVar1;
  long ctx_err;
  
  uVar1 = FUN_00199a5c();
  if (ctx_err == 0) {
    uVar1 = 1;
  }
  return uVar1;
}





/*--------------------------------------------------------------------*/
/* FUN_00199d08 @ 0x00199d08   (est. sk_swift_helper)
 * Ghidra: undefined4 FUN_00199d08(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

unsigned int FUN_00199d08(void)

{
  unsigned int uVar1;
  long ctx_err;
  
  uVar1 = FUN_00199a5c();
  if (ctx_err == 0) {
    uVar1 = 1;
  }
  return uVar1;
}





/*--------------------------------------------------------------------*/
/* FUN_00199d2c @ 0x00199d2c   (est. sk_swift_helper)
 * Ghidra: void FUN_00199d2c(undefined8 param_1,undefined8 param_2,undefined8 param_3)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

unsigned long FUN_00199d2c(param_1, param_2, param_3)
  unsigned long param_1;
  unsigned long param_2;
  unsigned long param_3;

{
  code *pcVar1;
    
  pcVar1 = (code *)FUN_00023c78(param_3);
  (*pcVar1)(0xffffffffffffffff,param_2,param_3);
  return 0;
}





/*--------------------------------------------------------------------*/
/* FUN_00199d8c @ 0x00199d8c   (est. sk_swift_helper)
 * Ghidra: void FUN_00199d8c(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined4 *param_4)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_00199d8c(param_1, param_2, param_3, param_4)
  unsigned long param_1;
  unsigned long param_2;
  unsigned long param_3;
  unsigned int * param_4;

{
  unsigned int uVar1;
  long ctx_err;
  
  uVar1 = FUN_00199dc8(param_2,param_3);
  if (ctx_err != 0) {
    *param_4 = uVar1;
  }
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_00199dc8 @ 0x00199dc8   (est. sk_swift_helper)
 * Ghidra: void FUN_00199dc8(undefined8 param_1,undefined8 param_2)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

unsigned long FUN_00199dc8(unsigned long param_1,unsigned long param_2)

{
  code *pcVar1;
    long lVar2;
  unsigned long extraout_x1;
  
  pcVar1 = (code *)FUN_00023d00(param_2);
  lVar2 = (*pcVar1)(param_1,param_2);
  if (lVar2 == -1) {
  return 0;
  }
  sk_swift_precond_1(0x23);
  sk_swift_abort_tail(0xe000000000000000);
  pcVar1 = (code *)sk_swift_meta(0x671848);
  (*pcVar1)(0x677790,0x671848);
  sk_swift_precond_2();
  sk_swift_abort_tail(extraout_x1);
                    /* WARNING: Subroutine does not return */
  sk_swift_fatal_error(sk_fatal_error_str,0xb,2,0xd000000000000021,0x80000000005ccc50,
               sk_xnu_upcalls_swift,0x25,2,0xf2d,0);
}





/*--------------------------------------------------------------------*/
/* FUN_00199eec @ 0x00199eec   (est. sk_swift_helper)
 * Ghidra: void FUN_00199eec(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_00199eec(void)

{
  unsigned int *in_x3;
  long ctx_err;
  unsigned int local_14;
  
  FUN_00199d8c();
  if (ctx_err != 0) {
    *in_x3 = local_14;
  }
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_00199f24 @ 0x00199f24   (est. sk_swift_helper)
 * Ghidra: undefined4 FUN_00199f24(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

unsigned int FUN_00199f24(void)

{
  unsigned int uVar1;
  long ctx_err;
  
  uVar1 = FUN_00199d2c();
  if (ctx_err == 0) {
    uVar1 = 1;
  }
  return uVar1;
}





/*--------------------------------------------------------------------*/
/* FUN_00199f28 @ 0x00199f28   (est. sk_swift_helper)
 * Ghidra: undefined4 FUN_00199f28(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

unsigned int FUN_00199f28(void)

{
  unsigned int uVar1;
  long ctx_err;
  
  uVar1 = FUN_00199d2c();
  if (ctx_err == 0) {
    uVar1 = 1;
  }
  return uVar1;
}





/*--------------------------------------------------------------------*/
/* FUN_00199f4c @ 0x00199f4c   (est. sk_swift_helper)
 * Ghidra: void FUN_00199f4c(undefined8 param_1,undefined8 param_2,undefined8 param_3)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

unsigned long FUN_00199f4c(param_1, param_2, param_3)
  unsigned long param_1;
  unsigned long param_2;
  unsigned long param_3;

{
  code *pcVar1;
    unsigned long *unaff_x20;
  unsigned long err;
  
  err = *unaff_x20;
  pcVar1 = (code *)FUN_00023c78(param_3);
  (*pcVar1)(0x94a50a26e372d0f7,param_2,param_3);
  (*pcVar1)(err,param_2,param_3);
  return 0;
}





/*--------------------------------------------------------------------*/
/* FUN_00199fe4 @ 0x00199fe4   (est. sk_swift_helper)
 * Ghidra: void FUN_00199fe4(undefined8 *param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_00199fe4(param_1, param_2, param_3, param_4, param_5)
  unsigned long * param_1;
  unsigned long param_2;
  unsigned long param_3;
  unsigned long param_4;
  unsigned int * param_5;

{
  unsigned long uVar1;
  long ctx_err;
  
  uVar1 = FUN_0019a034(param_3,param_4);
  if (ctx_err == 0) {
    *param_1 = uVar1;
  }
  else {
    *param_5 = (int)uVar1;
  }
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019a034 @ 0x0019a034   (est. sk_swift_helper)
 * Ghidra: void FUN_0019a034(undefined8 param_1,undefined8 param_2)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

unsigned long FUN_0019a034(unsigned long param_1,unsigned long param_2)

{
  code *pcVar1;
    long lVar2;
  unsigned long extraout_x1;
  
  pcVar1 = (code *)FUN_00023d00(param_2);
  lVar2 = (*pcVar1)(param_1,param_2);
  if (lVar2 == -0x6b5af5d91c8d2f09) {
    (*pcVar1)(param_1,param_2);
  return 0;
  }
  sk_swift_precond_1(0x1c);
  sk_swift_abort_tail(0xe000000000000000);
  pcVar1 = (code *)sk_swift_meta(0x671848);
  (*pcVar1)(0x677790,0x671848);
  sk_swift_precond_2();
  sk_swift_abort_tail(extraout_x1);
                    /* WARNING: Subroutine does not return */
  sk_swift_fatal_error(sk_fatal_error_str,0xb,2,0xd00000000000001a,0x80000000005c9590,
               sk_xnu_upcalls_swift,0x25,2,0xf35,0);
}





/*--------------------------------------------------------------------*/
/* FUN_0019a180 @ 0x0019a180   (est. sk_swift_helper)
 * Ghidra: void FUN_0019a180(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019a180(void)

{
  unsigned int *in_x3;
  long ctx_err;
  unsigned int local_14;
  
  FUN_00199fe4();
  if (ctx_err != 0) {
    *in_x3 = local_14;
  }
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019a1b8 @ 0x0019a1b8   (est. sk_swift_helper)
 * Ghidra: undefined4 FUN_0019a1b8(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

unsigned int FUN_0019a1b8(void)

{
  unsigned int uVar1;
  long ctx_err;
  
  uVar1 = FUN_00199f4c();
  if (ctx_err == 0) {
    uVar1 = 1;
  }
  return uVar1;
}





/*--------------------------------------------------------------------*/
/* FUN_0019a1bc @ 0x0019a1bc   (est. sk_swift_helper)
 * Ghidra: undefined4 FUN_0019a1bc(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

unsigned int FUN_0019a1bc(void)

{
  unsigned int uVar1;
  long ctx_err;
  
  uVar1 = FUN_00199f4c();
  if (ctx_err == 0) {
    uVar1 = 1;
  }
  return uVar1;
}





/*--------------------------------------------------------------------*/
/* FUN_0019a1e0 @ 0x0019a1e0   (est. sk_swift_helper)
 * Ghidra: void FUN_0019a1e0(undefined8 param_1,ulong param_2,undefined8 param_3,undefined4 *param_4)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019a1e0(unsigned long param_1,unsigned long param_2,unsigned long param_3,unsigned int *param_4)

{
  unsigned int uVar1;
  long ctx_err;
  unsigned char local_114 [4];
  unsigned int local_110;
  unsigned int uStack_10c;
  unsigned long local_108;
  unsigned long uStack_100;
  unsigned long local_f8;
  unsigned long uStack_f0;
  unsigned long local_e8;
  unsigned long uStack_e0;
  unsigned char local_d8;
  unsigned long local_d0;
  unsigned long uStack_c8;
  unsigned long uStack_c0;
  unsigned long uStack_b8;
  unsigned long local_b0;
  unsigned long uStack_a8;
  unsigned char local_a0;
  unsigned long local_90;
  unsigned long uStack_88;
  unsigned long uStack_80;
  unsigned long uStack_78;
  unsigned long local_70;
  unsigned long uStack_68;
  unsigned char local_60;
  
  sk_swift_string_begin(&local_108);
  local_114[0] = (unsigned char)param_2;
  local_110 = (unsigned int)(param_2 >> 0x20);
  uStack_10c = (unsigned int)param_3;
  uVar1 = sk_swift_collection_init(local_114,0x65a870,0x66a1d0,0x65a798,0x66a740);
  if (ctx_err == 0) {
    sk_swift_type_arg(param_2 >> 0x20);
    sk_swift_type_arg(param_3);
    uStack_c8 = uStack_100;
    local_d0 = local_108;
    uStack_b8 = uStack_f0;
    uStack_c0 = local_f8;
    uStack_a8 = uStack_e0;
    local_b0 = local_e8;
    local_a0 = local_d8;
    sk_swift_epilogue();
  }
  else {
    uStack_88 = uStack_100;
    local_90 = local_108;
    uStack_78 = uStack_f0;
    uStack_80 = local_f8;
    uStack_68 = uStack_e0;
    local_70 = local_e8;
    local_60 = local_d8;
    sk_swift_epilogue();
    *param_4 = uVar1;
  }
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019a30c @ 0x0019a30c   (est. sk_swift_helper)
 * Ghidra: void FUN_0019a30c(undefined1 *param_1,undefined8 param_2,undefined4 *param_3)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019a30c(unsigned char *param_1,unsigned long param_2,unsigned int *param_3)

{
  unsigned int uVar1;
  unsigned int err;
  long ctx_err;
  unsigned int local_f0;
  unsigned char local_e9;
  unsigned long local_e8;
  unsigned long uStack_e0;
  unsigned long local_d8;
  unsigned long uStack_d0;
  unsigned long local_c8;
  unsigned long uStack_c0;
  unsigned char local_b8;
  unsigned long local_b0;
  unsigned long uStack_a8;
  unsigned long uStack_a0;
  unsigned long uStack_98;
  unsigned long local_90;
  unsigned long uStack_88;
  unsigned char local_80;
  unsigned long local_70;
  unsigned long uStack_68;
  unsigned long uStack_60;
  unsigned long uStack_58;
  unsigned long local_50;
  unsigned long uStack_48;
  unsigned char local_40;
  
  sk_swift_string_build(&local_e8);
  sk_swift_collection_op(&local_e9,0x66a1d0,0x65a688,0x66a1d0,0x65a5e8,0x66a738,&local_f0);
  if (ctx_err == 0) {
    *param_1 = local_e9;
    uVar1 = FUN_000218a4();
    err = FUN_000218a4();
    *(unsigned int *)(param_1 + 4) = uVar1;
    *(unsigned int *)(param_1 + 8) = err;
    uStack_a8 = uStack_e0;
    local_b0 = local_e8;
    uStack_98 = uStack_d0;
    uStack_a0 = local_d8;
    uStack_88 = uStack_c0;
    local_90 = local_c8;
    local_80 = local_b8;
    sk_swift_epilogue();
  }
  else {
    uStack_68 = uStack_e0;
    local_70 = local_e8;
    uStack_58 = uStack_d0;
    uStack_60 = local_d8;
    uStack_48 = uStack_c0;
    local_50 = local_c8;
    local_40 = local_b8;
    sk_swift_epilogue();
    *param_3 = local_f0;
  }
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019a424 @ 0x0019a424   (est. sk_swift_helper)
 * Ghidra: ulong FUN_0019a424(undefined8 param_1,undefined8 param_2)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

unsigned long FUN_0019a424(unsigned long param_1,unsigned long param_2)

{
  unsigned long uVar1;
  unsigned long err;
  unsigned char *unaff_x20;
  long ctx_err;
  unsigned char auStack_50 [16];
  unsigned char local_40;
  unsigned long local_3c;
  unsigned int local_24;
  
  local_40 = *unaff_x20;
  local_3c = *(unsigned long *)(unaff_x20 + 4);
  uVar1 = sk_swift_err_code(0);
  err = FUN_00023f74(0,param_1,param_2,FUN_0019ad48,auStack_50,0x67b148,uVar1,FUN_0065a550,
                       &local_24);
  if (ctx_err != 0) {
    err = (unsigned long)local_24;
  }
  return err;
}





/*--------------------------------------------------------------------*/
/* FUN_0019a4dc @ 0x0019a4dc   (est. sk_swift_helper)
 * Ghidra: void FUN_0019a4dc(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined4 *param_4,
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019a4dc(unsigned long param_1,unsigned long param_2,unsigned long param_3,unsigned int *param_4,
                 unsigned long param_5)

{
  unsigned long uVar1;
  long ctx_err;
  unsigned int local_44;
  
  uVar1 = sk_swift_err_code(0);
  FUN_00023f74(param_1,1,param_2,param_3,FUN_0019a30c,0,param_5,uVar1,FUN_0065a550,&local_44);
  if (ctx_err != 0) {
    *param_4 = local_44;
  }
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019a594 @ 0x0019a594   (est. sk_swift_helper)
 * Ghidra: void FUN_0019a594(undefined8 param_1,undefined8 param_2)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019a594(unsigned long param_1,unsigned long param_2)

{
  FUN_0019a710(param_1,param_2,FUN_0018c594);
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019a598 @ 0x0019a598   (est. sk_swift_helper)
 * Ghidra: void FUN_0019a598(undefined8 param_1,undefined8 param_2)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019a598(unsigned long param_1,unsigned long param_2)

{
  FUN_0019a710(param_1,param_2,FUN_0018c594);
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019a5c0 @ 0x0019a5c0   (est. sk_swift_helper)
 * Ghidra: void FUN_0019a5c0(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019a5c0(void)

{
  FUN_0018dd04();
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019a5c4 @ 0x0019a5c4   (est. sk_swift_helper)
 * Ghidra: void FUN_0019a5c4(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019a5c4(void)

{
  FUN_0018dd04();
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019a5ec @ 0x0019a5ec   (est. sk_swift_helper)
 * Ghidra: void FUN_0019a5ec(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019a5ec(void)

{
  FUN_0018ddd8();
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019a5f0 @ 0x0019a5f0   (est. sk_swift_helper)
 * Ghidra: void FUN_0019a5f0(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019a5f0(void)

{
  FUN_0018ddd8();
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019a618 @ 0x0019a618   (est. sk_swift_helper)
 * Ghidra: void FUN_0019a618(undefined8 param_1,undefined8 param_2,undefined4 *param_3,code *param_4)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019a618(param_1, param_2, param_3, param_4)
  unsigned long param_1;
  unsigned long param_2;
  unsigned int * param_3;
  code * param_4;

{
  unsigned int uVar1;
  long ctx_err;
  unsigned long local_f8;
  unsigned long uStack_f0;
  unsigned long local_e8;
  unsigned long uStack_e0;
  unsigned long local_d8;
  unsigned long uStack_d0;
  unsigned char local_c8;
  unsigned long local_c0;
  unsigned long uStack_b8;
  unsigned long uStack_b0;
  unsigned long uStack_a8;
  unsigned long local_a0;
  unsigned long uStack_98;
  unsigned char local_90;
  unsigned long local_80;
  unsigned long uStack_78;
  unsigned long local_70;
  unsigned long uStack_68;
  unsigned long uStack_60;
  unsigned long uStack_58;
  unsigned char local_50;
  
  sk_swift_string_begin(&local_f8);
  uVar1 = (*param_4)(param_2);
  if (ctx_err == 0) {
    uStack_b8 = uStack_f0;
    local_c0 = local_f8;
    uStack_a8 = uStack_e0;
    uStack_b0 = local_e8;
    uStack_98 = uStack_d0;
    local_a0 = local_d8;
    local_90 = local_c8;
    sk_swift_epilogue();
  }
  else {
    uStack_78 = uStack_f0;
    local_80 = local_f8;
    uStack_68 = uStack_e0;
    local_70 = local_e8;
    uStack_58 = uStack_d0;
    uStack_60 = local_d8;
    local_50 = local_c8;
    sk_swift_epilogue();
    *param_3 = uVar1;
  }
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019a6e4 @ 0x0019a6e4   (est. sk_swift_helper)
 * Ghidra: void FUN_0019a6e4(undefined8 param_1,undefined8 param_2)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019a6e4(unsigned long param_1,unsigned long param_2)

{
  FUN_0019a710(param_1,param_2,FUN_0018cb24);
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019a6e8 @ 0x0019a6e8   (est. sk_swift_helper)
 * Ghidra: void FUN_0019a6e8(undefined8 param_1,undefined8 param_2)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019a6e8(unsigned long param_1,unsigned long param_2)

{
  FUN_0019a710(param_1,param_2,FUN_0018cb24);
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019a710 @ 0x0019a710   (est. sk_swift_helper)
 * Ghidra: void FUN_0019a710(undefined8 *param_1,undefined8 param_2,undefined4 *param_3,code *param_4)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019a710(unsigned long *param_1,unsigned long param_2,unsigned int *param_3,code *param_4)

{
  unsigned long uVar1;
  long ctx_err;
  unsigned long local_f8;
  unsigned long uStack_f0;
  unsigned long local_e8;
  unsigned long uStack_e0;
  unsigned long local_d8;
  unsigned long uStack_d0;
  unsigned char local_c8;
  unsigned long local_c0;
  unsigned long uStack_b8;
  unsigned long uStack_b0;
  unsigned long uStack_a8;
  unsigned long local_a0;
  unsigned long uStack_98;
  unsigned char local_90;
  unsigned long local_80;
  unsigned long uStack_78;
  unsigned long local_70;
  unsigned long uStack_68;
  unsigned long uStack_60;
  unsigned long uStack_58;
  unsigned char local_50;
  
  sk_swift_string_build(&local_f8);
  uVar1 = (*param_4)();
  if (ctx_err == 0) {
    *param_1 = uVar1;
    uStack_b8 = uStack_f0;
    local_c0 = local_f8;
    uStack_a8 = uStack_e0;
    uStack_b0 = local_e8;
    uStack_98 = uStack_d0;
    local_a0 = local_d8;
    local_90 = local_c8;
    sk_swift_epilogue();
  }
  else {
    uStack_78 = uStack_f0;
    local_80 = local_f8;
    uStack_68 = uStack_e0;
    local_70 = local_e8;
    uStack_58 = uStack_d0;
    uStack_60 = local_d8;
    local_50 = local_c8;
    sk_swift_epilogue();
    *param_3 = (int)uVar1;
  }
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019a7d8 @ 0x0019a7d8   (est. sk_swift_helper)
 * Ghidra: void FUN_0019a7d8(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019a7d8(void)

{
  FUN_0018dd04();
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019a7dc @ 0x0019a7dc   (est. sk_swift_helper)
 * Ghidra: void FUN_0019a7dc(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019a7dc(void)

{
  FUN_0018dd04();
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019a804 @ 0x0019a804   (est. sk_swift_helper)
 * Ghidra: void FUN_0019a804(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019a804(void)

{
  FUN_0018ddd8();
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019a808 @ 0x0019a808   (est. sk_swift_helper)
 * Ghidra: void FUN_0019a808(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019a808(void)

{
  FUN_0018ddd8();
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019a830 @ 0x0019a830   (est. sk_swift_helper)
 * Ghidra: undefined8 FUN_0019a830(uint param_1)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

unsigned long FUN_0019a830(param_1)
  unsigned int param_1;

{
  unsigned long uVar1;
  
  if (param_1 < 0x82) {
    uVar1 = 1;
    switch(param_1) {
    default:
      uVar1 = 0;
    case 1:
      return uVar1;
    case 2:
      return 2;
    case 3:
    case 4:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 0xb:
    case 0xe:
    case 0xf:
    case 0x10:
    case 0x12:
    case 0x13:
    case 0x17:
    case 0x18:
    case 0x19:
    case 0x1a:
    case 0x1b:
    case 0x1d:
    case 0x1f:
    case 0x20:
    case 0x21:
    case 0x24:
    case 0x25:
    case 0x26:
    case 0x27:
    case 0x28:
    case 0x29:
    case 0x2a:
    case 0x2b:
    case 0x2c:
    case 0x2e:
    case 0x2f:
    case 0x30:
    case 0x31:
    case 0x32:
    case 0x33:
    case 0x34:
    case 0x35:
    case 0x36:
    case 0x38:
    case 0x39:
    case 0x3a:
    case 0x3b:
    case 0x3c:
    case 0x3d:
    case 0x3e:
    case 0x40:
    case 0x41:
    case 0x42:
    case 0x43:
    case 0x44:
    case 0x45:
    case 0x47:
    case 0x48:
    case 0x49:
    case 0x4a:
    case 0x4b:
    case 0x4c:
    case 0x4d:
    case 0x4e:
    case 0x4f:
    case 0x51:
    case 0x52:
    case 0x53:
    case 0x54:
    case 0x55:
    case 0x56:
    case 0x57:
    case 0x58:
    case 0x59:
    case 0x5a:
    case 0x5b:
    case 0x5c:
    case 0x5d:
    case 0x5e:
    case 0x5f:
    case 0x60:
    case 0x61:
    case 0x62:
    case 99:
    case 100:
    case 0x65:
    case 0x66:
    case 0x67:
    case 0x68:
    case 0x69:
    case 0x6a:
    case 0x6b:
    case 0x6c:
    case 0x6d:
    case 0x6e:
    case 0x6f:
    case 0x70:
    case 0x71:
    case 0x72:
    case 0x73:
    case 0x74:
    case 0x75:
    case 0x76:
    case 0x77:
    case 0x78:
    case 0x79:
    case 0x7a:
    case 0x7b:
    case 0x7c:
    case 0x7d:
    case 0x7e:
    case 0x7f:
      goto switchD_0019a860_caseD_3;
    case 5:
      return 3;
    case 0xc:
      return 4;
    case 0xd:
      return 5;
    case 0x11:
      return 6;
    case 0x14:
      return 7;
    case 0x15:
      return 8;
    case 0x16:
      return 9;
    case 0x1c:
      return 10;
    case 0x1e:
      return 0xb;
    case 0x22:
      return 0xc;
    case 0x23:
      return 0xd;
    case 0x2d:
      return 0xe;
    case 0x37:
      return 0xf;
    case 0x3f:
      return 0x10;
    case 0x46:
      return 0x11;
    case 0x50:
      return 0x12;
    case 0x80:
      return 0x13;
    case 0x81:
      return 0x14;
    }
  }
  if (param_1 == 9999) {
    return 0x15;
  }
switchD_0019a860_caseD_3:
  return 0x16;
}





/*--------------------------------------------------------------------*/
/* FUN_0019ad48 @ 0x0019ad48   (est. sk_swift_helper)
 * Ghidra: void FUN_0019ad48(undefined8 param_1,undefined8 param_2)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019ad48(unsigned long param_1,unsigned long param_2)

{
  long unaff_x20;
  
  FUN_0019a1e0(param_1,(unsigned long)*(unsigned char *)(unaff_x20 + 0x10) |
                       (unsigned long)*(unsigned int *)(unaff_x20 + 0x14) << 0x20,*(unsigned int *)(unaff_x20 + 0x18),
               (unsigned int *)param_2);
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019ad4c @ 0x0019ad4c   (est. sk_swift_helper)
 * Ghidra: void FUN_0019ad4c(undefined8 param_1,undefined8 param_2)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019ad4c(unsigned long param_1,unsigned long param_2)

{
  long unaff_x20;
  
  FUN_0019a1e0(param_1,(unsigned long)*(unsigned char *)(unaff_x20 + 0x10) |
                       (unsigned long)*(unsigned int *)(unaff_x20 + 0x14) << 0x20,*(unsigned int *)(unaff_x20 + 0x18),
               (unsigned int *)param_2);
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019ad70 @ 0x0019ad70   (est. sk_swift_helper)
 * Ghidra: void FUN_0019ad70(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019ad70(void)

{
  FUN_0019a618();
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019ad74 @ 0x0019ad74   (est. sk_swift_helper)
 * Ghidra: void FUN_0019ad74(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019ad74(void)

{
  FUN_0019a618();
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019ada4 @ 0x0019ada4   (est. sk_swift_helper)
 * Ghidra: void FUN_0019ada4(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019ada4(void)

{
  FUN_0019a618();
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019ada8 @ 0x0019ada8   (est. sk_swift_helper)
 * Ghidra: void FUN_0019ada8(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019ada8(void)

{
  FUN_0019a618();
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019addc @ 0x0019addc   (est. sk_swift_helper)
 * Ghidra: void FUN_0019addc(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019addc(void)

{
  FUN_00198d50();
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019ade0 @ 0x0019ade0   (est. sk_swift_helper)
 * Ghidra: void FUN_0019ade0(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019ade0(void)

{
  FUN_00198d50();
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019adf4 @ 0x0019adf4   (est. sk_swift_helper)
 * Ghidra: void FUN_0019adf4(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019adf4(void)

{
  FUN_00198f04();
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019adf8 @ 0x0019adf8   (est. sk_swift_helper)
 * Ghidra: void FUN_0019adf8(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019adf8(void)

{
  FUN_00198f04();
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019ae0c @ 0x0019ae0c   (est. sk_swift_helper)
 * Ghidra: ulong FUN_0019ae0c(long param_1)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

unsigned long FUN_0019ae0c(long param_1)

{
  return (param_1 + 0x9aU) / 0x71;
}





/*--------------------------------------------------------------------*/
/* FUN_0019ae2c @ 0x0019ae2c   (est. sk_swift_helper)
 * Ghidra: void FUN_0019ae2c(undefined8 param_1)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019ae2c(unsigned long param_1)

{
  unsigned long *puVar1;
  
  puVar1 = (unsigned long *)FUN_0005b140();
                    /* WARNING: Could not recover jumptable at 0x0019ae5c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)*puVar1)(param_1);
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019ae60 @ 0x0019ae60   (est. sk_swift_helper)
 * Ghidra: void FUN_0019ae60(undefined8 param_1,undefined8 param_2)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019ae60(unsigned long param_1,unsigned long param_2)

{
  long next;
  
  next = FUN_0005b140();
                    /* WARNING: Could not recover jumptable at 0x0019ae98. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(next + 8))(param_1,param_2);
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019ae9c @ 0x0019ae9c   (est. sk_swift_helper)
 * Ghidra: FUN_001150e0(s_integer_overflow_005bb5bd);
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

unsigned long FUN_0019ae9c(long param_1,long param_2,long param_3,long param_4)

{
  unsigned long uVar1;
  unsigned long err;
  unsigned long auVar3;
  
  if (SCARRY8(param_2,param_4)) {
                    /* WARNING: Subroutine does not return */
    FUN_001150e0(s_integer_overflow_005bb5bd);
  }
  if (!SCARRY8(param_1,param_3)) {
    err = (unsigned long)(param_2 + param_4) >> 9;
    uVar1 = err / 0x1dcd65;
    if (!SCARRY8(param_1 + param_3,uVar1)) {
      auVar3 = param_2 + param_4 + (err / 0x1dcd65) * -1000000000;
      auVar3 = param_1 + param_3 + uVar1;
      return (unsigned long)auVar3;
    }
                    /* WARNING: Subroutine does not return */
    FUN_001150e0(s_integer_overflow_005bb5bd);
  }
                    /* WARNING: Subroutine does not return */
  FUN_001150e0(s_integer_overflow_005bb5bd);
}





/*--------------------------------------------------------------------*/
/* FUN_0019af14 @ 0x0019af14   (est. sk_swift_helper)
 * Ghidra: FUN_001150e0(s_integer_overflow_005bb5bd);
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

unsigned long FUN_0019af14(long param_1,long param_2,long param_3,long param_4)

{
  bool bv;
  unsigned long auVar2;
  
  while( true ) {
    if (param_4 <= param_2) {
      if (SBORROW8(param_1,param_3)) {
                    /* WARNING: Subroutine does not return */
        FUN_001150e0(s_integer_overflow_005bb5bd);
      }
      auVar2 = param_2 - param_4;
      auVar2 = param_1 - param_3;
      return auVar2;
    }
    bv = SCARRY8(param_2,1000000000);
    param_2 = param_2 + 1000000000;
    if (bv) break;
    bv = SBORROW8(param_1,1);
    param_1 = param_1 + -1;
    if (bv) {
                    /* WARNING: Subroutine does not return */
      FUN_001150e0(s_integer_overflow_005bb5bd);
    }
  }
                    /* WARNING: Subroutine does not return */
  FUN_001150e0(s_integer_overflow_005bb5bd);
}





/*--------------------------------------------------------------------*/
/* FUN_0019af88 @ 0x0019af88   (est. sk_swift_helper)
 * Ghidra: uint FUN_0019af88(long param_1,long param_2,long param_3,long param_4)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

unsigned int FUN_0019af88(long param_1,long param_2,long param_3,long param_4)

{
  unsigned int uVar1;
  unsigned int err;
  
  err = 0xffffffff;
  if (param_4 <= param_2) {
    err = (unsigned int)(param_4 < param_2);
  }
  uVar1 = 1;
  if (param_1 <= param_3) {
    uVar1 = err;
  }
  err = 0xffffffff;
  if (param_3 <= param_1) {
    err = uVar1;
  }
  return err;
}





/*--------------------------------------------------------------------*/
/* FUN_0019afb0 @ 0x0019afb0   (est. sk_swift_helper)
 * Ghidra: undefined8 FUN_0019afb0(long param_1)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

unsigned long FUN_0019afb0(long param_1)

{
  unsigned long uVar1;
  
  uVar1 = 0;
  if (param_1 != 0) {
    uVar1 = *(unsigned long *)(param_1 + 0x10);
  }
  return uVar1;
}





/*--------------------------------------------------------------------*/
/* FUN_0019afbc @ 0x0019afbc   (est. sk_swift_helper)
 * Ghidra: undefined4 FUN_0019afbc(long param_1)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

unsigned int FUN_0019afbc(long param_1)

{
  if (param_1 != 0) {
    return *(unsigned int *)(param_1 + 0x18);
  }
  return 0x4e4f4350;
}





/*--------------------------------------------------------------------*/
/* FUN_0019afd4 @ 0x0019afd4   (est. sk_swift_helper)
 * Ghidra: void FUN_0019afd4(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019afd4(void)

{
  FUN_0019b274();
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019b018 @ 0x0019b018   (est. sk_swift_helper)
 * Ghidra: void FUN_0019b018(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019b018(void)

{
  code *pcVar1;
    long extraout_x8;
  code *UNRECOVERED_JUMPTABLE;
  
  FUN_00357cb4();
  FUN_0034c084();
  FUN_000a6f88();
  (**(code **)(extraout_x8 + 0x10))();
  pcVar1 = (code *)FUN_000277b8();
  FUN_0034bec4();
  FUN_0031090c();
  FUN_0035a738();
  FUN_00084180();
  __builtin_trap();
  FUN_0035631c();
  FUN_0006b6f4();
  FUN_00357c74();
                    /* WARNING: Could not recover jumptable at 0x0019b0b4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*UNRECOVERED_JUMPTABLE)();
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019b25c @ 0x0019b25c   (est. sk_swift_helper)
 * Ghidra: void FUN_0019b25c(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019b25c(void)

{
  FUN_0019b274();
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019b274 @ 0x0019b274   (est. sk_swift_helper)
 * Ghidra: void FUN_0019b274(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019b274(void)
{
  unsigned long uVar1;
  code *in_x4;
  code *extraout_x8;
  long extraout_x16;
  
  FUN_00349fcc();
  FUN_00354db8();
  uVar1 = (*in_x4)();
  FUN_0034aebc(uVar1);
  (*extraout_x8)();
  FUN_003511b4();
                    /* WARNING: Could not recover jumptable at 0x0019b2e8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(extraout_x16 + 0x10))();
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019b318 @ 0x0019b318   (est. sk_swift_helper)
 * Ghidra: void FUN_0019b318(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019b318(void)

{
  code *pcVar2;
  code *pcVar4;
  long next;
    unsigned long res;
  code *in_x6;
  code *in_x7;
  unsigned long extraout_x8;
  long extraout_x8_00;
  code *extraout_x8_01;
  unsigned long extraout_x9;
  long extraout_x16;
  unsigned long unaff_x19;
  long ctx_err;
    long i;
  
  FUN_0008e518();
  pcVar2 = in_x6;
  FUN_0034dff4();
  FUN_0007c028();
  (*DAT_00658c00)(*(unsigned long *)(extraout_x8_00 + 0x40));
  FUN_00348bbc();
  (*DAT_00658c00)();
  FUN_0034ae94();
  (*DAT_00658c00)();
  FUN_0034b3d8();
  FUN_00354828();
  __builtin_trap();
  FUN_003510dc(extraout_x8);
  (*in_x6)();
  FUN_003512c0(*(unsigned long *)(extraout_x16 + 8));
  (*extraout_x8_01)();
  if (*(long *)(ctx_err + 0x10) != 0) {
    pcVar2 = (code *)(*in_x7)(unaff_x19);
    i = 0;
    do {
      FUN_0035308c();
      FUN_00350548();
      FUN_0019ea20();
      next = i + 1;
      if (SCARRY8(i,1)) {
                    /* WARNING: Does not return */
        __builtin_trap();
      }
      pcVar4 = *(code **)(extraout_x16 + 0x20U);
      FUN_00350470();
      __builtin_trap();
      FUN_0034cf84();
      __builtin_trap();
      if ((res & 1) == 0) {
        FUN_00350aa0();
        (*extraout_x8_01)();
      }
      else {
        FUN_003509bc();
        (*extraout_x8_01)();
        FUN_000e15d8();
        (*pcVar4)(extraout_x16 + 0x20U & 0xffffffffffff | 0x48d8000000000000);
      }
      i = i + 1;
    } while (next != *(long *)(ctx_err + 0x10));
  }
  FUN_0008e500(extraout_x9);
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019b528 @ 0x0019b528   (est. sk_swift_helper)
 * Ghidra: void FUN_0019b528(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019b528(void)

{
  long next;
  unsigned long err;
  unsigned long in_x3;
  unsigned long in_x4;
  unsigned long extraout_x8;
  code *extraout_x8_00;
  code *extraout_x8_01;
  code *extraout_x9;
  long extraout_x16;
  long result;
  unsigned long unaff_x30;
  
  FUN_00084220();
  FUN_00352c34();
  FUN_00353a0c();
  FUN_003534a4(in_x3);
  FUN_0034d354();
  next = (*extraout_x8_00)();
  if (next < 0x41) {
    FUN_0034bf2c(in_x4);
    FUN_0009e234();
    err = (*extraout_x8_01)();
    FUN_0034b804();
    (**(code **)(extraout_x16 + 8))();
    FUN_003109e4();
    FUN_00350c50();
    FUN_0034d334(err);
    (*extraout_x9)();
    FUN_00084234(unaff_x30);
    return;
  }
  FUN_0034e52c(extraout_x8);
  FUN_003534c8();
  FUN_00243c60();
                    /* WARNING: Could not recover jumptable at 0x0019b624. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(long *)(result + -8) + 8))();
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019b66c @ 0x0019b66c   (est. sk_swift_helper)
 * Ghidra: void FUN_0019b66c(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019b66c(void)

{
  code *pcVar6;
  code *pcVar12;
  code *pcVar13;
  unsigned int uVar1;
  unsigned int err;
  unsigned long res;
  unsigned long uVar4;
  unsigned long fatal_v;
    unsigned long count;
  long j;
  unsigned long fatal_line;
  long lVar10;
  unsigned long uVar11;
      unsigned long *puVar14;
  long extraout_x1;
  unsigned long extraout_x1_00;
  unsigned long in_x3;
  unsigned long in_x5;
  unsigned long extraout_x8;
  long extraout_x8_00;
  long extraout_x8_01;
  code *extraout_x8_02;
  code *extraout_x8_03;
  code *extraout_x8_04;
  code *extraout_x8_05;
  unsigned long extraout_x8_06;
  code *extraout_x8_07;
  code *extraout_x8_08;
  code *extraout_x8_09;
  unsigned long extraout_x8_10;
  code *extraout_x8_11;
  code *extraout_x8_12;
  code *extraout_x8_13;
  code *extraout_x8_14;
  code *extraout_x8_15;
  code *extraout_x8_16;
  code *extraout_x8_17;
  code *extraout_x8_18;
  code *extraout_x8_19;
  code *extraout_x8_20;
  code *extraout_x8_21;
  code *extraout_x8_22;
  code *extraout_x8_23;
  code *extraout_x9;
  code *extraout_x9_00;
  code *extraout_x9_01;
  code *extraout_x9_02;
  code *extraout_x9_03;
  code *extraout_x9_04;
  code *extraout_x9_05;
  code *extraout_x9_06;
  code *extraout_x9_07;
  code *extraout_x9_08;
  code *extraout_x9_09;
  code *extraout_x9_10;
  code *extraout_x9_11;
  code *extraout_x9_12;
  code *extraout_x9_13;
  code *extraout_x9_14;
  code *extraout_x9_15;
  code *extraout_x9_16;
  code *extraout_x9_17;
  code *extraout_x9_18;
  code *extraout_x9_19;
  code *extraout_x9_20;
  code *extraout_x9_21;
  code *extraout_x9_22;
  long extraout_x16;
  code *ctx_err;
  unsigned long unaff_x26;
  unsigned long unaff_x28;
  unsigned long unaff_x30;
  unsigned long auVar15;
  unsigned long local_30;
  
  FUN_0008e518();
  fatal_line = in_x3;
  res = FUN_00352c10();
  uVar4 = FUN_00027754(fatal_line);
  FUN_00349684();
  FUN_003513fc();
  fatal_v = FUN_00377824();
  FUN_0034ab20();
  FUN_0007c1a4();
  (*DAT_00658c00)();
  FUN_0034a2ac();
  FUN_0034a774(in_x5);
  FUN_003522c8();
  FUN_00377824();
  FUN_0034ab20();
  FUN_0007c1a4();
  (*DAT_00658c00)();
  FUN_00350428();
  FUN_00349618();
  (*DAT_00658c00)(*(unsigned long *)(extraout_x8_00 + 0x40));
  FUN_00349068();
  FUN_003494e8();
  (*DAT_00658c00)(*(unsigned long *)(extraout_x8_01 + 0x40));
  FUN_00348bd8();
  (*DAT_00658c00)();
  FUN_00349f5c();
  (*DAT_00658c00)();
  FUN_0034b4c0();
  pcVar6 = (code *)FUN_00310a14(in_x5);
  FUN_0034ef18();
  __builtin_trap();
  if ((count & 1) != 0) {
    FUN_00358d58(in_x5);
    FUN_003504c4();
    j = (*ctx_err)();
    FUN_00310984(in_x3);
    fatal_line = FUN_0034b8dc();
    lVar10 = (*extraout_x8_02)(fatal_line,in_x3);
    if (lVar10 < j) {
      FUN_00310b38(in_x3);
      FUN_00351184();
      FUN_0034db08();
      (*extraout_x9)();
      FUN_0034ef18();
      __builtin_trap();
      fatal_line = FUN_0034acd0(uVar4);
      err = (*extraout_x8_03)(fatal_line,uVar4);
      count = unaff_x26;
      if (((uVar1 ^ err) & 1) == 0) {
        FUN_003504c4();
        j = (*ctx_err)();
        FUN_0034e15c();
        FUN_003508fc();
        lVar10 = (*extraout_x8_05)();
        if (lVar10 <= j) {
          FUN_0034e1d0();
          auVar15 = FUN_003509d4(unaff_x26);
          FUN_003518f4(auVar15,auVar15,uVar4);
          (*extraout_x9_03)();
          FUN_00348e78(in_x5);
          unaff_x26 = extraout_x8_06;
          goto LAB_0019bb34;
        }
        FUN_0035a3b8();
        FUN_00350b48(unaff_x26);
        (*extraout_x9_00)();
        FUN_0034d53c();
        FUN_0035a3ac();
        FUN_0034ef78();
        FUN_0034ce28();
        (*extraout_x9_01)();
LAB_0019ba44:
        FUN_00348e78(uVar4);
        FUN_00350944();
        FUN_00350974();
        (*extraout_x8_08)();
        FUN_00358eac();
        pcVar12 = *(code **)(unaff_x26 + 8);
        FUN_003508cc();
        __builtin_trap();
        FUN_003509d4();
        __builtin_trap();
        unaff_x26 = count;
joined_r0x0019ba84:
        if ((unaff_x28 & 1) == 0) goto LAB_0019bb64;
      }
      else {
        FUN_0034ef18();
        __builtin_trap();
        FUN_003504c4();
        j = (*ctx_err)();
        FUN_0034e15c();
        FUN_003508fc();
        lVar10 = (*extraout_x8_04)();
        if ((uVar11 & 1) == 0) {
          if (j < lVar10) {
            FUN_0035a3b8();
            fatal_line = FUN_00355a14();
            auVar15 = res;
            auVar15 = fatal_line;
            pcVar12 = extraout_x9_02;
            count = uVar4;
LAB_0019ba14:
            (*pcVar12)(auVar15,auVar15);
            FUN_003506cc();
            FUN_0035a3ac();
            FUN_0034fed0();
            FUN_0034cf64();
            (*extraout_x9_08)();
            unaff_x26 = uVar4;
            goto LAB_0019ba44;
          }
          FUN_0034ad00();
          FUN_00350968(extraout_x1);
          FUN_00377bec();
          FUN_00349370();
          FUN_0035a360();
          FUN_0034c234();
          (*extraout_x9_09)();
          FUN_0034c7d4();
          FUN_0035a3ac();
          auVar15 = FUN_0034d374();
          (*extraout_x9_10)(auVar15,auVar15,extraout_x1);
          FUN_0034b288();
          FUN_00310b08();
          FUN_0034f4f4();
          FUN_00350974();
          (*extraout_x8_09)();
          FUN_00358eac();
          pcVar12 = *(code **)(j + 8);
          FUN_003508cc();
          __builtin_trap();
          if ((fatal_v & 1) == 0) {
            FUN_003509d4();
            __builtin_trap();
            goto LAB_0019bb64;
          }
          FUN_0034e1d0();
          auVar15 = FUN_003509d4(unaff_x26);
          unaff_x26 = extraout_x8_10;
LAB_0019bb18:
          FUN_003518f4(auVar15,auVar15,uVar4);
          (*extraout_x9_11)();
          FUN_00348e78(in_x5);
LAB_0019bb34:
          FUN_00351360();
          FUN_00351584();
          unaff_x28 = (*extraout_x8_11)();
          FUN_000e72b0();
          (*extraout_x9_12)();
          goto joined_r0x0019ba84;
        }
        if (lVar10 < j) {
          FUN_0034e1d0();
          auVar15 = FUN_003509d4(unaff_x26);
          goto LAB_0019bb18;
        }
        FUN_0034ad00();
        FUN_0034d2e4();
        FUN_00377bec();
        FUN_00349370();
        FUN_0034ba98();
        (*extraout_x9_04)();
        FUN_0034c7d4();
        auVar15 = FUN_0034f4b4(unaff_x26);
        (*extraout_x9_05)(auVar15,auVar15,extraout_x1_00);
        FUN_00348e78(in_x5);
        FUN_00351360();
        FUN_00351584();
        unaff_x28 = (*extraout_x8_07)();
        FUN_00353c0c();
        FUN_000e72b0();
        (*extraout_x9_06)();
        if ((unaff_x28 & 1) == 0) {
          FUN_00351e84();
          auVar15 = FUN_00100c38();
          pcVar12 = extraout_x9_07;
          goto LAB_0019ba14;
        }
        FUN_00354364();
        FUN_003509d4();
        (*extraout_x8_23)();
      }
      FUN_003480e4();
      goto LAB_0019bf9c;
    }
  }
LAB_0019bb64:
  pcVar12 = (code *)FUN_00310a44(in_x5);
  FUN_003504c4();
  __builtin_trap();
  pcVar13 = (code *)FUN_00310984(in_x3);
  FUN_0034db08();
  __builtin_trap();
  if (j <= lVar10) {
    FUN_003504c4();
    __builtin_trap();
    FUN_0034db08();
    __builtin_trap();
    if (j != lVar10) goto LAB_0019be24;
    FUN_0034ef18();
    __builtin_trap();
    if ((count & 1) != 0) goto LAB_0019be24;
  }
  FUN_00310aa4(in_x3);
  FUN_0034db08(local_30);
  (*extraout_x9_13)();
  FUN_0035ac40(uVar4);
  FUN_003509e0();
  __builtin_trap();
  FUN_0034ef18();
  __builtin_trap();
  if ((((unsigned int)puVar14 ^ uVar1) & 1) == 0) {
    FUN_0034c0d0();
    FUN_003509e0();
    j = (*extraout_x8_14)();
    FUN_003504c4();
    __builtin_trap();
    if (j < lVar10) goto LAB_0019bdcc;
LAB_0019bd3c:
    FUN_003511c0(*(unsigned long *)(extraout_x16 + 0x10),unaff_x26);
    (*extraout_x8_15)();
    FUN_0034cee8();
    FUN_00352bf8();
    FUN_000bd3a4(unaff_x26);
    FUN_0034e4dc();
    (*extraout_x9_16)();
    FUN_00348e78(uVar4);
    FUN_00350ea4();
    FUN_00350974();
    (*extraout_x8_16)();
    FUN_0035a664();
    pcVar6 = (code *)puVar14[1];
    FUN_003509d4();
    __builtin_trap();
    fatal_v = unaff_x26;
LAB_0019bdac:
    (*pcVar6)(local_30);
joined_r0x0019bdbc:
    if ((fatal_v & 1) == 0) {
LAB_0019be24:
      FUN_003506cc();
      FUN_0034f424(extraout_x8,res);
      (*extraout_x9_18)();
      FUN_0008e500(unaff_x30);
      return;
    }
  }
  else {
    FUN_0034db08();
    __builtin_trap();
    FUN_0034c0d0();
    FUN_003509e0();
    j = (*extraout_x8_12)();
    FUN_003504c4();
    __builtin_trap();
    if (((unsigned long)puVar14 & 1) == 0) {
      if (lVar10 <= j) {
        FUN_0034ad00();
        FUN_0034feb0();
        FUN_00377bec();
        FUN_00349370();
        FUN_0034c044();
        (*extraout_x9_19)();
        FUN_0034dc20();
        FUN_003531c0();
        FUN_003515e4();
        (*extraout_x9_20)();
        FUN_0034b368(in_x5);
        FUN_00351ee0();
        FUN_00350a34();
        FUN_00351584();
        fatal_v = (*extraout_x8_19)();
        FUN_00353c0c();
        FUN_00350518();
        (*extraout_x9_21)();
        if ((fatal_v & 1) == 0) {
          FUN_00354364();
          FUN_003569d8();
          (*extraout_x8_22)();
          goto LAB_0019be24;
        }
        FUN_003511c0(*(unsigned long *)(extraout_x16 + 0x10),unaff_x26);
        (*extraout_x8_20)();
        FUN_0034cee8();
        FUN_00352bf8();
        FUN_00077708();
        FUN_0034e4dc();
        (*extraout_x9_22)();
        FUN_00348e78(uVar4);
        FUN_003510dc();
        FUN_00350974();
        (*extraout_x8_21)();
        FUN_0035a664();
        pcVar6 = *(code **)(unaff_x26 + 8);
        FUN_003509d4();
        __builtin_trap();
        goto LAB_0019bdac;
      }
LAB_0019bdcc:
      FUN_0034e1d0();
      FUN_003569f0();
      auVar15 = FUN_003505e8();
      FUN_003518f4(auVar15,auVar15,uVar4);
      (*extraout_x9_17)();
      FUN_00348e78(in_x5);
      FUN_003511c0(puVar14);
      fatal_v = (*extraout_x8_17)();
      FUN_003529a4();
      FUN_00350518();
      (*extraout_x8_18)();
      goto joined_r0x0019bdbc;
    }
    if (lVar10 < j) goto LAB_0019bd3c;
    FUN_0034ad00();
    FUN_00350968(extraout_x1);
    FUN_00377bec();
    FUN_00349370();
    FUN_0035a360();
    FUN_0034c234();
    (*extraout_x9_14)();
    FUN_0034c7d4();
    FUN_00352bf8();
    FUN_0034d778(local_30);
    (*extraout_x9_15)();
    FUN_00348e78(uVar4);
    FUN_00350ea4();
    FUN_00350974();
    (*extraout_x8_13)();
    FUN_0035a664();
    puVar14 = (unsigned long *)(extraout_x1 + 8);
    pcVar6 = (code *)*puVar14;
    FUN_003509d4();
    __builtin_trap();
    if ((fatal_v & 1) == 0) goto LAB_0019bdcc;
    FUN_003505e8();
    __builtin_trap();
  }
  FUN_00347fb4();
LAB_0019bf9c:
  FUN_003523f0();
                    /* WARNING: Subroutine does not return */
  sk_swift_fatal_error_2();
}





/*--------------------------------------------------------------------*/
/* FUN_0019c03c @ 0x0019c03c   (est. sk_swift_helper)
 * Ghidra: void FUN_0019c03c(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019c03c(void)

{
  code *UNRECOVERED_JUMPTABLE;
  
  FUN_0034f664();
  UNRECOVERED_JUMPTABLE = (code *)FUN_00310b68();
  FUN_00084180();
                    /* WARNING: Could not recover jumptable at 0x0019c074. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*UNRECOVERED_JUMPTABLE)();
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019c078 @ 0x0019c078   (est. sk_swift_helper)
 * Ghidra: void FUN_0019c078(undefined8 param_1,undefined8 param_2,undefined8 param_3)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019c078(unsigned long param_1,unsigned long param_2,unsigned long param_3)

{
  code *pcVar1;
    unsigned long err;
  long lVar3;
  long len;
  unsigned long extraout_x8;
  long extraout_x8_00;
  unsigned long fatal_v;
  code *extraout_x8_01;
  code *extraout_x8_02;
  code *extraout_x9;
  code *extraout_x9_00;
  code *extraout_x9_01;
  code *extraout_x9_02;
  long extraout_x16;
  unsigned long unaff_x30;
  unsigned long auVar6;
  unsigned char local_10 [16];
  
  FUN_0008e518();
  FUN_00350b54();
  FUN_00349b3c();
  (*DAT_00658c00)(*(unsigned long *)(extraout_x8_00 + 0x40));
  FUN_00349068();
  FUN_00027754(param_3);
  FUN_00351bec();
  pcVar1 = (code *)FUN_00027788();
  FUN_0034e064();
  __builtin_trap();
  FUN_00350494();
  __builtin_trap();
  FUN_003515a8();
  FUN_00348b94();
  lVar3 = FUN_00377824();
  FUN_000dbe70(err);
  len = FUN_0019c44c();
  FUN_003534bc();
  FUN_0034ee08();
  (*extraout_x9)();
  FUN_00310b98();
  FUN_0034e064(local_10);
  (*extraout_x9_00)();
  fatal_v = (unsigned long)*(unsigned char *)(*(long *)(lVar3 + -8) + 0x50);
  auVar6 = FUN_00310bc8();
  FUN_00352498(auVar6,auVar6,auVar6,
               len + (fatal_v + 0x20 & (fatal_v ^ 0xffffffffffffffff)));
  FUN_00352920();
  (*extraout_x8_01)();
  FUN_0035156c();
  FUN_0034e064(local_10);
  (*extraout_x9_01)();
  FUN_00350560(*(unsigned long *)(extraout_x16 + 8));
  (*extraout_x8_02)();
  FUN_00310bf8();
  FUN_00351ec0(extraout_x8);
  FUN_0034d344();
  (*extraout_x9_02)();
  FUN_0008e500(unaff_x30);
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019c20c @ 0x0019c20c   (est. sk_swift_helper)
 * Ghidra: void FUN_0019c20c(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019c20c(void)

{
  long unaff_x20;
  
  FUN_000776d8();
  if (unaff_x20 == 0) {
    FUN_000776cc();
  }
  else {
    FUN_0034fc8c();
    FUN_00002534();
    FUN_0007791c(unaff_x20 << 2);
    FUN_00077630();
    FUN_0007766c();
  }
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019c258 @ 0x0019c258   (est. sk_swift_helper)
 * Ghidra: long FUN_0019c258(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

long FUN_0019c258(void)

{
  unsigned long uVar1;
  long lVar2;
  long lVar3;
  unsigned long unaff_x19;
  long unaff_x20;
  
  FUN_000776d8();
  if (unaff_x20 == 0) {
    FUN_000776cc();
    lVar2 = 0;
  }
  else {
    FUN_0034fc8c();
    uVar1 = FUN_00002534();
    lVar2 = FUN_0036a940(uVar1,unaff_x20 + 0x20,7);
    lVar3 = thunk_FUN_000126e8();
    *(unsigned long *)(lVar2 + 0x10) = unaff_x19;
    *(long *)(lVar2 + 0x18) = lVar3 * 2 + -0x40;
  }
  return lVar2;
}





/*--------------------------------------------------------------------*/
/* FUN_0019c2b0 @ 0x0019c2b0   (est. sk_swift_helper)
 * Ghidra: void FUN_0019c2b0(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019c2b0(void)

{
  long unaff_x20;
  
  FUN_000776d8();
  if (unaff_x20 == 0) {
    FUN_000776cc();
  }
  else {
    FUN_0034fc8c();
    FUN_00002534();
    FUN_0007791c(unaff_x20 << 3);
    FUN_00077630();
    FUN_0007766c();
  }
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019c2fc @ 0x0019c2fc   (est. sk_swift_helper)
 * Ghidra: void FUN_0019c2fc(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019c2fc(void)

{
  long unaff_x20;
  
  FUN_000776d8();
  if (unaff_x20 == 0) {
    FUN_000776cc();
  }
  else {
    FUN_0034fc8c();
    FUN_00002534();
    FUN_0007791c(unaff_x20 << 4);
    FUN_00077630();
    FUN_0007766c();
  }
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019c348 @ 0x0019c348   (est. sk_swift_helper)
 * Ghidra: void FUN_0019c348(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019c348(void)

{
  unsigned long uVar1;
  long unaff_x20;
  
  FUN_000776d8();
  if (unaff_x20 == 0) {
    FUN_000776cc();
  }
  else {
    FUN_0034fc8c();
    uVar1 = FUN_00002534();
    FUN_0036a940(uVar1,unaff_x20 * 0x18 + 0x20,7);
    FUN_00077630();
    FUN_00358134();
  }
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019c3a4 @ 0x0019c3a4   (est. sk_swift_helper)
 * Ghidra: void FUN_0019c3a4(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019c3a4(void)

{
  long unaff_x20;
  
  FUN_000776d8();
  if (unaff_x20 == 0) {
    FUN_000776cc();
  }
  else {
    FUN_0034fc8c();
    FUN_00002534();
    FUN_0007791c(unaff_x20 << 5);
    FUN_00077630();
    FUN_0007766c();
  }
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019c3f0 @ 0x0019c3f0   (est. sk_swift_helper)
 * Ghidra: void FUN_0019c3f0(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019c3f0(void)

{
  unsigned long uVar1;
  long unaff_x20;
  
  FUN_000776d8();
  if (unaff_x20 == 0) {
    FUN_000776cc();
  }
  else {
    FUN_0034fc8c();
    uVar1 = FUN_00002534();
    FUN_0036a940(uVar1,unaff_x20 * 0x28 + 0x20,7);
    FUN_00077630();
    FUN_00358134();
  }
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019c44c @ 0x0019c44c   (est. sk_swift_helper)
 * Ghidra: void FUN_0019c44c(undefined8 param_1,undefined8 param_2,undefined8 param_3)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

unsigned long FUN_0019c44c(param_1, param_2, param_3)
  unsigned long param_1;
  unsigned long param_2;
  unsigned long param_3;

{
  unsigned long uVar1;
  long lVar2;
  long extraout_x8;
  long extraout_x10;
  unsigned long extraout_x11;
  long extraout_x16;
  long unaff_x20;
  long lVar3;
  unsigned long uVar4;
  unsigned long unaff_x30;
  unsigned long auVar5;
  
  auVar5 = FUN_00357ca0();
  lVar2 = auVar5;
  if (auVar5 <= auVar5) {
    lVar2 = auVar5;
  }
  if (lVar2 == 0) {
    FUN_000776cc();
LAB_0019c500:
    FUN_00357c44(unaff_x20,unaff_x30);
  return 0;
  }
  FUN_00357a34();
  FUN_001a894c(param_3,param_3);
  uVar1 = FUN_003549d8(*(unsigned long *)(unaff_x20 + -8));
  lVar3 = *(long *)(extraout_x8 + 0x48);
  uVar4 = (unsigned long)*(unsigned char *)(extraout_x16 + 0x50);
  unaff_x20 = FUN_0036a940(uVar1,(uVar4 + extraout_x10 & (uVar4 ^ 0xffffffffffffffff)) +
                                 lVar3 * lVar2,uVar4 | extraout_x11);
  lVar2 = thunk_FUN_000126e8();
  if (lVar3 == 0) {
    FUN_00348074(1);
  }
  else {
    if (lVar2 - (uVar4 + 0x20 & ~uVar4) != -0x8000000000000000 || lVar3 != -1) {
      FUN_00358134();
      goto LAB_0019c500;
    }
    FUN_0034834c(1);
  }
  FUN_00351be0();
                    /* WARNING: Subroutine does not return */
  sk_swift_fatal_error_2();
}





/*--------------------------------------------------------------------*/
/* FUN_0019c53c @ 0x0019c53c   (est. sk_swift_helper)
 * Ghidra: void FUN_0019c53c(undefined8 param_1,undefined8 param_2,long param_3,undefined8 param_4,
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019c53c(param_1, param_2, param_3, param_4, param_5, param_6, param_7, param_8)
  unsigned long param_1;
  unsigned long param_2;
  long param_3;
  unsigned long param_4;
  unsigned long param_5;
  long param_6;
  unsigned long param_7;
  unsigned long param_8;

{
  code *pcVar6;
  code *pcVar8;
  code *pcVar9;
  unsigned long *puVar1;
  unsigned long err;
  long lVar3;
  long len;
  unsigned long fatal_v;
    long j;
      long lVar10;
  unsigned long extraout_x1;
  unsigned long extraout_x8;
  code *extraout_x8_00;
  code *extraout_x8_01;
  long extraout_x8_02;
  code *extraout_x8_03;
  code *extraout_x8_04;
  code *extraout_x8_05;
  code *extraout_x9;
  code *extraout_x9_00;
  long extraout_x10;
  long extraout_x16;
  unsigned long unaff_x19;
  long lVar11;
  long lVar12;
  unsigned long uVar13;
  unsigned long auVar14;
  long local_a0;
  long local_98;
  unsigned long uStack_88;
  unsigned long local_40;
  char local_30 [48];
  
  auVar14 = FUN_0008e518();
  lVar10 = auVar14;
  lVar3 = auVar14;
  FUN_00027754(param_7);
  FUN_00027754();
  auVar14 = FUN_00348b94();
  len = FUN_00377824(auVar14,auVar14,param_5);
  lVar12 = *(long *)(len + -8);
  local_a0 = lVar12;
  FUN_0007c1a4();
  (*DAT_00658c00)();
  FUN_0034bdfc();
  fatal_v = FUN_00349748();
  FUN_00377824(fatal_v,param_8,param_6);
  uStack_88 = FUN_000a6f88();
  FUN_0007c1a4();
  (*DAT_00658c00)();
  FUN_0034a760();
  pcVar6 = (code *)FUN_00310b68(param_7);
  j = (*pcVar6)(param_5,param_7);
  lVar11 = *(long *)(lVar12 + 0x48);
  lVar12 = lVar10 - lVar3;
  if (SBORROW8(lVar10,lVar3)) {
                    /* WARNING: Does not return */
    __builtin_trap();
  }
  uVar13 = j + lVar11 * lVar3;
  FUN_00351118(lVar12);
  FUN_0019cb68();
  lVar3 = param_3 - lVar12;
  if (SBORROW8(param_3,lVar12)) {
                    /* WARNING: Does not return */
    __builtin_trap();
  }
  local_98 = lVar11 * param_3;
  err = uVar13 + local_98;
  if (lVar3 != 0) {
    FUN_00356964();
    FUN_00353efc();
    FUN_00350518();
    lVar12 = (*extraout_x8_00)();
    if (SBORROW8(lVar12,lVar10)) {
                    /* WARNING: Does not return */
      __builtin_trap();
    }
    FUN_0019ce60(j + lVar11 * lVar10,lVar12 - lVar10,err,len);
    fatal_v = FUN_00310c74(param_7);
    FUN_00352314(fatal_v,local_30);
    auVar14 = (*extraout_x8_01)();
    lVar12 = *(unsigned long *)auVar14;
    if (SCARRY8(lVar12,lVar3)) {
                    /* WARNING: Does not return */
      __builtin_trap();
    }
    auVar14 = lVar12 + lVar3;
    ((code)auVar14)(local_30,0);
  }
  if (param_3 < 1) {
    pcVar6 = *(code **)(*(long *)(param_6 + -8) + 8);
  }
  else {
    (*DAT_00658c00)();
    FUN_00358238();
    *(unsigned long *)(extraout_x8_02 + -0x30) = param_5;
    *(long *)(extraout_x8_02 + -0x28) = param_6;
    *(unsigned long *)(extraout_x8_02 + -0x20) = param_7;
    *(unsigned long *)(extraout_x8_02 + -0x18) = param_8;
    *(long *)(extraout_x8_02 + -0x10) = param_3;
    *(unsigned long *)(extraout_x8_02 + -8) = uVar13;
    FUN_00351bec(param_8);
    FUN_00310c44();
    FUN_00358324();
    auVar14 = FUN_0035a4e0();
    FUN_00356ad0(auVar14,auVar14,extraout_x10 + 8);
    FUN_00351c70();
    (*extraout_x9)();
    if (local_30[0] == '\x01') {
      FUN_0035156c(param_8);
      FUN_00350bf0(local_40);
      (*extraout_x9_00)();
      if (0 < local_98) {
        FUN_00358bc0();
        pcVar6 = (code *)FUN_000277e8();
        pcVar8 = (code *)FUN_00027818(&local_a0);
        puVar1 = (unsigned long *)(local_a0 + 0x20);
        do {
          FUN_0035169c(local_30);
          __builtin_trap();
          FUN_003561ac();
          (*extraout_x8_03)(unaff_x19,extraout_x1,len);
          (*pcVar9)(local_30,local_30,0);
          auVar14 = FUN_003507d4(*puVar1);
          (*extraout_x8_04)(auVar14,auVar14,len);
          uVar13 = uVar13 + lVar11;
          auVar14 = FUN_00350b00();
          (*pcVar8)(auVar14,auVar14,param_8);
        } while (uVar13 < err);
      }
      FUN_00351190(param_4);
      FUN_0019dd10();
      FUN_0034b804();
      fatal_v = (**(code **)(extraout_x16 + 8))(param_4,param_6);
      FUN_00352e18(fatal_v,uStack_88);
      (*extraout_x8_05)();
      goto LAB_0019c940;
    }
    pcVar6 = *(code **)(*(long *)(param_6 + -8) + 8);
  }
  (*pcVar6)(param_4,param_6);
LAB_0019c940:
  FUN_0008e500(extraout_x8);
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019c968 @ 0x0019c968   (est. sk_swift_helper)
 * Ghidra: void FUN_0019c968(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019c968(void)

{
  code *extraout_x9;
  
  FUN_0034b430();
  FUN_00357bc4();
  FUN_00310ad4();
  FUN_00310ca4();
  FUN_00351048();
  FUN_00350810();
  (*extraout_x9)();
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019c9bc @ 0x0019c9bc   (est. sk_swift_helper)
 * Ghidra: ulong FUN_0019c9bc(ulong param_1)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

unsigned long FUN_0019c9bc(unsigned long param_1)

{
  return param_1 >> 0x24 & 0xf;
}





/*--------------------------------------------------------------------*/
/* FUN_0019c9c4 @ 0x0019c9c4   (est. sk_swift_helper)
 * Ghidra: ulong FUN_0019c9c4(ulong param_1)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

unsigned long FUN_0019c9c4(unsigned long param_1)

{
  return param_1 >> 0x23 & 0x1f;
}





/*--------------------------------------------------------------------*/
/* FUN_0019c9cc @ 0x0019c9cc   (est. sk_swift_helper)
 * Ghidra: void FUN_0019c9cc(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019c9cc(void)

{
  code *pcVar2;
  unsigned long uVar1;
  long extraout_x8;
  code *extraout_x8_00;
  code *extraout_x9;
  code *extraout_x9_00;
  long extraout_x16;
    unsigned long unaff_x30;
  
  FUN_00084220();
  FUN_0008409c();
  FUN_00349748();
  FUN_00377824();
  FUN_00348ce8();
  (*DAT_00658c00)(*(unsigned long *)(extraout_x8 + 0x40));
  FUN_00348a80();
  (*DAT_00658c00)();
  FUN_0034b3d8();
  FUN_000277b8();
  FUN_0034e72c();
  (*extraout_x9)();
  FUN_00350704();
  FUN_00084180();
  (*extraout_x9_00)();
  FUN_00310cd4();
  FUN_0034bddc();
  FUN_0035063c();
  (*extraout_x8_00)();
  pcVar2 = *(code **)(extraout_x16 + 8);
  FUN_00351384();
  __builtin_trap();
  FUN_00350630();
  __builtin_trap();
  uVar1 = FUN_00358f90();
  FUN_00084234(uVar1,unaff_x30);
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019cac8 @ 0x0019cac8   (est. sk_swift_helper)
 * Ghidra: undefined8 FUN_0019cac8(long param_1,undefined8 param_2)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

unsigned long FUN_0019cac8(long param_1,unsigned long param_2)

{
  unsigned long uVar1;
  
  if (-1 < param_1) {
    uVar1 = FUN_00002534(&DAT_006575c0,&DAT_004f1950);
    FUN_0035bc70(param_2,param_1,uVar1);
    return param_2;
  }
                    /* WARNING: Subroutine does not return */
  sk_swift_fatal_error_2(sk_fatal_error_str,0xb,2,s_UnsafeMutablePointer_deinitializ_005cd730,0x35,2,
               s_Swift_UnsafePointer_swift_005cd770,0x19,2,0x4a3,1);
}





/*--------------------------------------------------------------------*/
/* FUN_0019cb68 @ 0x0019cb68   (est. sk_swift_helper)
 * Ghidra: undefined8 FUN_0019cb68(long param_1,undefined8 param_2)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

unsigned long FUN_0019cb68(param_1, param_2)
  long param_1;
  unsigned long param_2;

{
  if (-1 < param_1) {
    FUN_00353a30();
    FUN_0035bc70();
    return param_2;
  }
  FUN_003488bc(1);
  FUN_0034a368();
  FUN_00352e0c();
                    /* WARNING: Subroutine does not return */
  sk_swift_fatal_error_2();
}





/*--------------------------------------------------------------------*/
/* FUN_0019cbd4 @ 0x0019cbd4   (est. sk_swift_helper)
 * Ghidra: void FUN_0019cbd4(ulong param_1,long param_2,ulong param_3)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019cbd4(unsigned long param_1,long param_2,unsigned long param_3)

{
  if (param_2 < 0) {
                    /* WARNING: Subroutine does not return */
    sk_swift_fatal_error_2(sk_fatal_error_str,0xb,2,s_UnsafeMutablePointer_moveInitial_005cd790,0x37,2,
                 s_Swift_UnsafePointer_swift_005cd770,0x19,2,0x426,1);
  }
  if (param_3 != param_1 || param_1 + param_2 * 0x18 <= param_3) {
    FUN_00117d14(param_3,param_1,param_2 * 0x18);
    return;
  }
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019cc64 @ 0x0019cc64   (est. sk_swift_helper)
 * Ghidra: void FUN_0019cc64(ulong param_1,long param_2,ulong param_3)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019cc64(unsigned long param_1,long param_2,unsigned long param_3)

{
  if (param_2 < 0) {
                    /* WARNING: Subroutine does not return */
    sk_swift_fatal_error_2(sk_fatal_error_str,0xb,2,s_UnsafeMutablePointer_moveInitial_005cd790,0x37,2,
                 s_Swift_UnsafePointer_swift_005cd770,0x19,2,0x426,1);
  }
  if (param_3 != param_1 || param_1 + param_2 * 8 <= param_3) {
    FUN_00117d14(param_3,param_1,param_2 << 3);
    return;
  }
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019ccec @ 0x0019ccec   (est. sk_swift_helper)
 * Ghidra: void FUN_0019ccec(ulong param_1,long param_2,ulong param_3)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019ccec(unsigned long param_1,long param_2,unsigned long param_3)

{
  if (param_2 < 0) {
                    /* WARNING: Subroutine does not return */
    sk_swift_fatal_error_2(sk_fatal_error_str,0xb,2,s_UnsafeMutablePointer_moveInitial_005cd790,0x37,2,
                 s_Swift_UnsafePointer_swift_005cd770,0x19,2,0x426,1);
  }
  if (param_3 != param_1 || param_1 + param_2 * 0x20 <= param_3) {
    FUN_00117d14(param_3,param_1,param_2 << 5);
    return;
  }
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019cd74 @ 0x0019cd74   (est. sk_swift_helper)
 * Ghidra: void FUN_0019cd74(ulong param_1,long param_2,ulong param_3)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019cd74(unsigned long param_1,long param_2,unsigned long param_3)

{
  if (param_2 < 0) {
                    /* WARNING: Subroutine does not return */
    sk_swift_fatal_error_2(sk_fatal_error_str,0xb,2,s_UnsafeMutablePointer_moveInitial_005cd790,0x37,2,
                 s_Swift_UnsafePointer_swift_005cd770,0x19,2,0x426,1);
  }
  if (param_3 != param_1 || param_1 + param_2 <= param_3) {
    FUN_00117d14(param_3,param_1,param_2);
    return;
  }
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019cdf8 @ 0x0019cdf8   (est. sk_swift_helper)
 * Ghidra: void FUN_0019cdf8(ulong param_1,long param_2,ulong param_3)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019cdf8(unsigned long param_1,long param_2,unsigned long param_3)

{
  if (param_2 < 0) {
    FUN_003488bc(1);
    FUN_003577b4();
    FUN_0034a368();
    FUN_00352e0c();
                    /* WARNING: Subroutine does not return */
    sk_swift_fatal_error_2();
  }
  if (param_3 != param_1 || param_1 + param_2 * 0x28 <= param_3) {
    FUN_00117d14(param_3,param_1,param_2 * 0x28);
    return;
  }
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019ce60 @ 0x0019ce60   (est. sk_swift_helper)
 * Ghidra: void FUN_0019ce60(undefined8 param_1,long param_2,ulong param_3)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019ce60(unsigned long param_1,long param_2,unsigned long param_3)

{
  unsigned long uVar1;
  long extraout_x16;
  long unaff_x20;
  long ctx_err;
  long result;
  unsigned long auVar2;
  long local_40;
  
  if (param_2 < 0) {
    FUN_003488bc(1);
    FUN_003577b4();
    FUN_0034a368();
    FUN_00352e0c();
                    /* WARNING: Subroutine does not return */
    sk_swift_fatal_error_2();
  }
  FUN_00352c34();
  uVar1 = FUN_0035098c();
  if (uVar1 <= param_3) {
    FUN_003504e8();
    auVar2 = FUN_00310d04();
    FUN_0034b3e8(auVar2,auVar2,auVar2);
    local_40 = ctx_err + *(long *)(extraout_x16 + 0x48) * unaff_x20;
    FUN_0034a198();
    uVar1 = FUN_001b8cf4(&stack0xffffffffffffffc8,&local_40);
    if ((uVar1 & 1) == 0) {
      if (result == ctx_err) {
        return;
      }
      FUN_0008412c();
      FUN_0035b898();
      return;
    }
  }
  FUN_0008412c();
  FUN_0035b7ac();
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019cf3c @ 0x0019cf3c   (est. sk_swift_helper)
 * Ghidra: void FUN_0019cf3c(long param_1,long param_2,long param_3,undefined8 param_4,undefined8 param_5,
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019cf3c(long param_1,long param_2,long param_3,unsigned long param_4,unsigned long param_5,
                 unsigned long param_6,unsigned long param_7)

{
  unsigned long uVar1;
  char *pcVar2;
  unsigned long res;
  
  if (param_2 == param_3) {
    if (param_1 != 0) {
      FUN_00027754(param_7);
      FUN_00027754();
      uVar1 = FUN_00027754();
      uVar1 = FUN_00377824(0,uVar1,param_5,&DAT_00611b24,&LAB_00611b34);
      FUN_0019dadc();
      return;
    }
    res = 0xc5;
    pcVar2 = s_Unexpectedly_found_nil_while_unw_005cd7d0;
    uVar1 = 0x39;
  }
  else {
    res = 0xc1;
    pcVar2 = s_invalid_Collection__count_differ_005cd8e0;
    uVar1 = 0x3b;
  }
                    /* WARNING: Subroutine does not return */
  sk_swift_fatal_error_2(sk_fatal_error_str,0xb,2,pcVar2,uVar1,2,
               s_Swift_ArrayBufferProtocol_swift_005d3ec0,0x1f,2,res,1);
}





/*--------------------------------------------------------------------*/
/* FUN_0019d060 @ 0x0019d060   (est. sk_swift_helper)
 * Ghidra: void FUN_0019d060(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019d060(void)

{
  code *pcVar1;
    unsigned long err;
  unsigned long extraout_x8;
  
  sk_lock_acquire();
  sk_lock_release_simple();
  pcVar1 = (code *)sk_lock_owner();
  __builtin_trap();
  if ((err & 1) != 0) {
    sk_lock_notify(extraout_x8);
    return;
  }
  sk_lock_wait();
  sk_memzero_string(sk_fatal_error_str);
  sk_lock_enter();
  sk_lock_exit();
                    /* WARNING: Subroutine does not return */
  sk_swift_fatal_error_2();
}





/*--------------------------------------------------------------------*/
/* FUN_0019d0d0 @ 0x0019d0d0   (est. sk_swift_helper)
 * Ghidra: void FUN_0019d0d0(undefined8 param_1,undefined8 param_2,uint param_3,undefined8 param_4,
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019d0d0(unsigned long param_1,unsigned long param_2,unsigned int param_3,unsigned long param_4,
                 unsigned long param_5,unsigned long param_6)

{
  unsigned char uVar1;
  
  uVar1 = 2;
  if ((param_3 & 1) == 0) {
    uVar1 = 0;
  }
  if ((param_5 & 1) != 0) {
    sk_memzero_string(sk_fatal_error_str,param_2,param_3,s_Unexpectedly_found_nil_while_imp_005cd810)
    ;
                    /* WARNING: Subroutine does not return */
    sk_swift_fatal_error_2();
  }
  FUN_0034a2f8(sk_fatal_error_str,param_2,param_3,s_Unexpectedly_found_nil_while_unw_005cd7d0,
               param_5,param_6,param_1,param_2,uVar1,param_4,1);
                    /* WARNING: Subroutine does not return */
  sk_swift_fatal_error_2();
}





/*--------------------------------------------------------------------*/
/* FUN_0019d15c @ 0x0019d15c   (est. sk_swift_helper)
 * Ghidra: void FUN_0019d15c(ulong param_1,long param_2,ulong param_3)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019d15c(unsigned long param_1,long param_2,unsigned long param_3)

{
  char *pcVar1;
  unsigned long err;
  unsigned long res;
  
  if (param_2 < 0) {
    res = 0x452;
    pcVar1 = s_UnsafeMutablePointer_initialize_w_005cd860;
    err = 0x33;
  }
  else {
    if (param_3 + param_2 * 0x10 <= param_1 || param_1 + param_2 * 0x10 <= param_3) {
      FUN_0035b67c(param_3,param_1,param_2,0x6753a0);
      return;
    }
    res = 0x454;
    pcVar1 = s_UnsafeMutablePointer_initialize_o_005cd8a0;
    err = 0x31;
  }
                    /* WARNING: Subroutine does not return */
  sk_swift_fatal_error_2(sk_fatal_error_str,0xb,2,pcVar1,err,2,s_Swift_UnsafePointer_swift_005cd770,0x19
               ,2,res,1);
}





/*--------------------------------------------------------------------*/
/* FUN_0019d234 @ 0x0019d234   (est. sk_swift_helper)
 * Ghidra: void FUN_0019d234(ulong param_1,long param_2,ulong param_3)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019d234(unsigned long param_1,long param_2,unsigned long param_3)

{
  unsigned long uVar1;
  char *pcVar2;
  unsigned long res;
  
  if (param_2 < 0) {
    res = 0x452;
    pcVar2 = s_UnsafeMutablePointer_initialize_w_005cd860;
    uVar1 = 0x33;
  }
  else {
    if (param_3 + param_2 * 0x18 <= param_1 || param_1 + param_2 * 0x18 <= param_3) {
      uVar1 = FUN_00002534(&DAT_00657718,&DAT_004f2228);
      FUN_0035b67c(param_3,param_1,param_2,uVar1);
      return;
    }
    res = 0x454;
    pcVar2 = s_UnsafeMutablePointer_initialize_o_005cd8a0;
    uVar1 = 0x31;
  }
                    /* WARNING: Subroutine does not return */
  sk_swift_fatal_error_2(sk_fatal_error_str,0xb,2,pcVar2,uVar1,2,s_Swift_UnsafePointer_swift_005cd770,0x19
               ,2,res,1);
}





/*--------------------------------------------------------------------*/
/* FUN_0019d338 @ 0x0019d338   (est. sk_swift_helper)
 * Ghidra: void FUN_0019d338(ulong param_1,long param_2,ulong param_3)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019d338(unsigned long param_1,long param_2,unsigned long param_3)

{
  char *pcVar1;
  unsigned long err;
  unsigned long res;
  
  if (param_2 < 0) {
    res = 0x452;
    pcVar1 = s_UnsafeMutablePointer_initialize_w_005cd860;
    err = 0x33;
  }
  else {
    if (param_3 + param_2 * 8 <= param_1 || param_1 + param_2 * 8 <= param_3) {
      FUN_00117cc4(param_3,param_1,param_2 << 3);
      return;
    }
    res = 0x454;
    pcVar1 = s_UnsafeMutablePointer_initialize_o_005cd8a0;
    err = 0x31;
  }
                    /* WARNING: Subroutine does not return */
  sk_swift_fatal_error_2(sk_fatal_error_str,0xb,2,pcVar1,err,2,s_Swift_UnsafePointer_swift_005cd770,0x19
               ,2,res,1);
}





/*--------------------------------------------------------------------*/
/* FUN_0019d40c @ 0x0019d40c   (est. sk_swift_helper)
 * Ghidra: void FUN_0019d40c(ulong param_1,long param_2,ulong param_3)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019d40c(unsigned long param_1,long param_2,unsigned long param_3)

{
  if (param_2 < 0) {
    FUN_003488bc(1);
    FUN_0034a368();
  }
  else {
    if (param_3 + param_2 <= param_1 || param_1 + param_2 <= param_3) {
      FUN_00117cc4(param_3,param_1,param_2);
      return;
    }
    FUN_003488bc(1,param_1,param_1);
    FUN_0034a368();
  }
  FUN_00352e0c();
                    /* WARNING: Subroutine does not return */
  sk_swift_fatal_error_2();
}





/*--------------------------------------------------------------------*/
/* FUN_0019d498 @ 0x0019d498   (est. sk_swift_helper)
 * Ghidra: void FUN_0019d498(ulong param_1,long param_2,ulong param_3)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019d498(unsigned long param_1,long param_2,unsigned long param_3)

{
  if (param_2 < 0) {
    FUN_003488bc(1);
    FUN_0034a368();
  }
  else {
    if (param_3 + param_2 * 8 <= param_1 || param_1 + param_2 * 8 <= param_3) {
      FUN_00117cc4(param_3,param_1,param_2 << 3);
      return;
    }
    FUN_003488bc(1);
    FUN_0034a368();
  }
  FUN_00352e0c();
                    /* WARNING: Subroutine does not return */
  sk_swift_fatal_error_2();
}





/*--------------------------------------------------------------------*/
/* FUN_0019d528 @ 0x0019d528   (est. sk_swift_helper)
 * Ghidra: void FUN_0019d528(ulong param_1,long param_2,ulong param_3)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019d528(unsigned long param_1,long param_2,unsigned long param_3)

{
  char *pcVar1;
  unsigned long err;
  unsigned long res;
  
  if (param_2 < 0) {
    res = 0x452;
    pcVar1 = s_UnsafeMutablePointer_initialize_w_005cd860;
    err = 0x33;
  }
  else {
    if (param_3 + param_2 * 0x20 <= param_1 || param_1 + param_2 * 0x20 <= param_3) {
      FUN_0035b67c(param_3,param_1,param_2,0x678560);
      return;
    }
    res = 0x454;
    pcVar1 = s_UnsafeMutablePointer_initialize_o_005cd8a0;
    err = 0x31;
  }
                    /* WARNING: Subroutine does not return */
  sk_swift_fatal_error_2(sk_fatal_error_str,0xb,2,pcVar1,err,2,s_Swift_UnsafePointer_swift_005cd770,0x19
               ,2,res,1);
}





/*--------------------------------------------------------------------*/
/* FUN_0019d600 @ 0x0019d600   (est. sk_swift_helper)
 * Ghidra: void FUN_0019d600(ulong param_1,long param_2,ulong param_3)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019d600(unsigned long param_1,long param_2,unsigned long param_3)

{
  char *pcVar1;
  unsigned long err;
  unsigned long res;
  
  if (param_2 < 0) {
    res = 0x452;
    pcVar1 = s_UnsafeMutablePointer_initialize_w_005cd860;
    err = 0x33;
  }
  else {
    if (param_3 + param_2 <= param_1 || param_1 + param_2 <= param_3) {
      FUN_00117cc4(param_3,param_1,param_2);
      return;
    }
    res = 0x454;
    pcVar1 = s_UnsafeMutablePointer_initialize_o_005cd8a0;
    err = 0x31;
  }
                    /* WARNING: Subroutine does not return */
  sk_swift_fatal_error_2(sk_fatal_error_str,0xb,2,pcVar1,err,2,s_Swift_UnsafePointer_swift_005cd770,0x19
               ,2,res,1);
}





/*--------------------------------------------------------------------*/
/* FUN_0019d6d0 @ 0x0019d6d0   (est. sk_swift_helper)
 * Ghidra: void FUN_0019d6d0(ulong param_1,long param_2,ulong param_3)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019d6d0(unsigned long param_1,long param_2,unsigned long param_3)

{
  char *pcVar1;
  unsigned long err;
  unsigned long res;
  
  if (param_2 < 0) {
    res = 0x452;
    pcVar1 = s_UnsafeMutablePointer_initialize_w_005cd860;
    err = 0x33;
  }
  else {
    if (param_3 + param_2 * 0x20 <= param_1 || param_1 + param_2 * 0x20 <= param_3) {
      FUN_0035b67c(param_3,param_1,param_2,0x67b1e8);
      return;
    }
    res = 0x454;
    pcVar1 = s_UnsafeMutablePointer_initialize_o_005cd8a0;
    err = 0x31;
  }
                    /* WARNING: Subroutine does not return */
  sk_swift_fatal_error_2(sk_fatal_error_str,0xb,2,pcVar1,err,2,s_Swift_UnsafePointer_swift_005cd770,0x19
               ,2,res,1);
}





/*--------------------------------------------------------------------*/
/* FUN_0019d7ac @ 0x0019d7ac   (est. sk_swift_helper)
 * Ghidra: void FUN_0019d7ac(ulong param_1,long param_2,ulong param_3)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019d7ac(unsigned long param_1,long param_2,unsigned long param_3)

{
  char *pcVar1;
  unsigned long err;
  unsigned long res;
  
  if (param_2 < 0) {
    res = 0x452;
    pcVar1 = s_UnsafeMutablePointer_initialize_w_005cd860;
    err = 0x33;
  }
  else {
    if (param_3 + param_2 * 8 <= param_1 || param_1 + param_2 * 8 <= param_3) {
      FUN_0035b67c(param_3,param_1,param_2,0x67b200);
      return;
    }
    res = 0x454;
    pcVar1 = s_UnsafeMutablePointer_initialize_o_005cd8a0;
    err = 0x31;
  }
                    /* WARNING: Subroutine does not return */
  sk_swift_fatal_error_2(sk_fatal_error_str,0xb,2,pcVar1,err,2,s_Swift_UnsafePointer_swift_005cd770,0x19
               ,2,res,1);
}





/*--------------------------------------------------------------------*/
/* FUN_0019d888 @ 0x0019d888   (est. sk_swift_helper)
 * Ghidra: void FUN_0019d888(ulong param_1,long param_2,ulong param_3)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019d888(unsigned long param_1,long param_2,unsigned long param_3)

{
  char *pcVar1;
  unsigned long err;
  unsigned long res;
  
  if (param_2 < 0) {
    res = 0x452;
    pcVar1 = s_UnsafeMutablePointer_initialize_w_005cd860;
    err = 0x33;
  }
  else {
    if (param_3 + param_2 * 0x18 <= param_1 || param_1 + param_2 * 0x18 <= param_3) {
      FUN_00117cc4(param_3,param_1,param_2 * 0x18);
      return;
    }
    res = 0x454;
    pcVar1 = s_UnsafeMutablePointer_initialize_o_005cd8a0;
    err = 0x31;
  }
                    /* WARNING: Subroutine does not return */
  sk_swift_fatal_error_2(sk_fatal_error_str,0xb,2,pcVar1,err,2,s_Swift_UnsafePointer_swift_005cd770,0x19
               ,2,res,1);
}





/*--------------------------------------------------------------------*/
/* FUN_0019d960 @ 0x0019d960   (est. sk_swift_helper)
 * Ghidra: void FUN_0019d960(ulong param_1,long param_2,ulong param_3)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019d960(unsigned long param_1,long param_2,unsigned long param_3)

{
  char *pcVar1;
  unsigned long err;
  unsigned long res;
  
  if (param_2 < 0) {
    res = 0x452;
    pcVar1 = s_UnsafeMutablePointer_initialize_w_005cd860;
    err = 0x33;
  }
  else {
    if (param_3 + param_2 * 0x20 <= param_1 || param_1 + param_2 * 0x20 <= param_3) {
      FUN_00117cc4(param_3,param_1,param_2 << 5);
      return;
    }
    res = 0x454;
    pcVar1 = s_UnsafeMutablePointer_initialize_o_005cd8a0;
    err = 0x31;
  }
                    /* WARNING: Subroutine does not return */
  sk_swift_fatal_error_2(sk_fatal_error_str,0xb,2,pcVar1,err,2,s_Swift_UnsafePointer_swift_005cd770,0x19
               ,2,res,1);
}





/*--------------------------------------------------------------------*/
/* FUN_0019da34 @ 0x0019da34   (est. sk_swift_helper)
 * Ghidra: void FUN_0019da34(undefined8 param_1,long param_2,ulong param_3)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019da34(unsigned long param_1,long param_2,unsigned long param_3)

{
  unsigned long auVar1;
  
  if (param_2 < 0) {
    FUN_003488bc(1);
    FUN_0034a368();
  }
  else {
    auVar1 = FUN_0008409c();
    if (param_3 + auVar1 * 0x28 <= auVar1 ||
        auVar1 + auVar1 * 0x28 <= param_3) {
      FUN_00355b68();
      FUN_00002534();
      FUN_0034ef68();
      FUN_0035b67c();
      return;
    }
    FUN_003488bc(1);
    FUN_0034a368();
  }
  FUN_00352e0c();
                    /* WARNING: Subroutine does not return */
  sk_swift_fatal_error_2();
}





/*--------------------------------------------------------------------*/
/* FUN_0019dadc @ 0x0019dadc   (est. sk_swift_helper)
 * Ghidra: void FUN_0019dadc(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019dadc(void)

{
  unsigned long uVar1;
  unsigned int err;
  unsigned int res;
  long extraout_x1;
  unsigned long extraout_x1_00;
  unsigned long extraout_x1_01;
  
  FUN_00041138();
  if (extraout_x1 < 0) {
    FUN_003488bc(1);
    FUN_0034a368();
LAB_0019dba4:
    FUN_00352e0c();
                    /* WARNING: Subroutine does not return */
    sk_swift_fatal_error_2();
  }
  FUN_0034a74c();
  FUN_003516cc();
  uVar1 = FUN_00310d1c();
  FUN_0034b3e8();
  err = FUN_0034da58();
  res = FUN_001b89a4(err,extraout_x1_00,uVar1);
  if ((res & 1) == 0) {
    err = FUN_0034da58();
    res = FUN_001b89a4(err,extraout_x1_01,uVar1);
    if ((res & 1) == 0) {
      FUN_003488bc(1);
      FUN_0034a368();
      goto LAB_0019dba4;
    }
  }
  FUN_0034aebc();
  FUN_0035b67c();
  FUN_0035847c();
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019dbac @ 0x0019dbac   (est. sk_swift_helper)
 * Ghidra: void FUN_0019dbac(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019dbac(void)

{
  code *extraout_x9;
  
  FUN_0034a74c();
  FUN_0034b07c();
  (*DAT_00658c00)();
  FUN_003504c4();
  FUN_00117cc4();
  FUN_00310ad4();
  FUN_00310ca4();
  FUN_00351048();
  FUN_003504a0();
  (*extraout_x9)();
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019dc44 @ 0x0019dc44   (est. sk_swift_helper)
 * Ghidra: void FUN_0019dc44(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019dc44(void)

{
  unsigned long in_x3;
  unsigned long in_x4;
  
  if (in_x4 == in_x3 >> 1) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  sk_swift_fatal_error_2(sk_fatal_error_str,0xb,2,s_invalid_Collection__count_differ_005cd8e0,0x3b,2,
               s_Swift_ArrayShared_swift_005cd920,0x17,2,0xad,1);
}





/*--------------------------------------------------------------------*/
/* FUN_0019dca8 @ 0x0019dca8   (est. sk_swift_helper)
 * Ghidra: void FUN_0019dca8(long param_1,long param_2)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019dca8(long param_1,long param_2)

{
  if (param_2 == *(long *)(param_1 + 0x10)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  sk_swift_fatal_error_2(sk_fatal_error_str,0xb,2,s_invalid_Collection__count_differ_005cd8e0,0x3b,2,
               s_Swift_ArrayShared_swift_005cd920,0x17,2,0xad,1);
}





/*--------------------------------------------------------------------*/
/* FUN_0019dd10 @ 0x0019dd10   (est. sk_swift_helper)
 * Ghidra: void FUN_0019dd10(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019dd10(void)
{
  unsigned long uVar1;
  code *extraout_x8;
  code *extraout_x8_00;
  code *extraout_x9;
  long extraout_x16;
  unsigned long unaff_x30;
  
  FUN_00084220();
  sk_lock_owner();
  FUN_003504d0();
  FUN_003521d4();
  FUN_003516cc();
  FUN_00377824();
  FUN_00348e00();
  FUN_0007c1a4();
  (*DAT_00658c00)();
  FUN_0034aee4();
  FUN_00310924();
  FUN_00350b24();
  FUN_00350518();
  (*extraout_x9)();
  FUN_0034ede8();
  FUN_00377bec();
  FUN_003514b8();
  FUN_00350adc();
  FUN_003508fc();
  FUN_0035130c();
  uVar1 = (*extraout_x8)();
  FUN_003507d4(*(unsigned long *)(extraout_x16 + 8));
  (*extraout_x8_00)();
  if ((uVar1 & 1) != 0) {
    FUN_00084234(unaff_x30);
    return;
  }
  FUN_00350410();
  FUN_003488bc();
  sk_memzero_string();
  FUN_00352be0();
                    /* WARNING: Subroutine does not return */
  sk_swift_fatal_error_2();
}





/*--------------------------------------------------------------------*/
/* FUN_0019de24 @ 0x0019de24   (est. sk_swift_helper)
 * Ghidra: void FUN_0019de24(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019de24(void)

{
  unsigned long *puVar1;
  long extraout_x16;
  
  puVar1 = (unsigned long *)FUN_0034b85c();
  sk_alloc_pages(*puVar1);
  FUN_00350624();
  FUN_0019dfc4();
  FUN_00351a44();
  FUN_0036b118();
  FUN_003504e8();
  FUN_00310d34();
  FUN_00349530();
  (**(code **)(extraout_x16 + 0x20))();
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019de9c @ 0x0019de9c   (est. sk_swift_helper)
 * Ghidra: FUN_001dd6ac(0,lVar6,0);
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

unsigned long *FUN_0019de9c(long param_1)

{
  unsigned long uVar1;
  unsigned long err;
  unsigned long res;
  unsigned char uVar4;
  unsigned long fatal_v;
  long lVar6;
  unsigned long *puVar7;
  long j;
  long lVar9;
  unsigned char auStack_b0 [40];
  unsigned long local_88;
  unsigned long uStack_80;
  unsigned long local_78;
  unsigned char local_70;
  unsigned long *local_68;
  
  lVar6 = *(long *)(param_1 + 0x10);
  puVar7 = &DAT_00657778;
  if (lVar6 != 0) {
    local_68 = &DAT_00657778;
    FUN_001dd6ac(0,lVar6,0);
    j = param_1 + 0x20;
    lVar9 = lVar6;
    do {
      puVar7 = local_68;
      FUN_00344d4c(j,auStack_b0);
      fatal_v = FUN_00002534(0x656118,&DAT_004e7f08);
      FUN_00365b6c(&local_88,auStack_b0,fatal_v,0x678560,7);
      uVar4 = local_70;
      res = local_78;
      err = uStack_80;
      fatal_v = local_88;
      uVar1 = *(unsigned long *)(puVar7 + 0x10);
      local_68 = puVar7;
      if (*(unsigned long *)(puVar7 + 0x18) >> 1 <= uVar1) {
        FUN_001dd6ac(1 < *(unsigned long *)(puVar7 + 0x18),uVar1 + 1,1);
      }
      puVar7 = local_68;
      *(unsigned long *)(local_68 + 0x10) = uVar1 + 1;
      *(unsigned long *)(local_68 + uVar1 * 0x20 + 0x20) = fatal_v;
      *(unsigned long *)(local_68 + uVar1 * 0x20 + 0x28) = err;
      *(unsigned long *)(local_68 + uVar1 * 0x20 + 0x30) = res;
      local_68[uVar1 * 0x20 + 0x38] = uVar4;
      j = j + 0x28;
      lVar9 = lVar9 + -1;
    } while (lVar9 != 0);
    FUN_0019dca8(param_1,lVar6);
  }
  return puVar7;
}





/*--------------------------------------------------------------------*/
/* FUN_0019dfc4 @ 0x0019dfc4   (est. sk_swift_helper)
 * Ghidra: void FUN_0019dfc4(undefined8 param_1,undefined8 param_2,undefined8 param_3)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019dfc4(param_1, param_2, param_3)
  unsigned long param_1;
  unsigned long param_2;
  unsigned long param_3;

{
  unsigned long uVar1;
  unsigned long err;
  unsigned char auStack_60 [16];
  unsigned long local_50;
  unsigned long uStack_48;
  unsigned long local_38;
  
  local_50 = param_2;
  uStack_48 = param_3;
  local_38 = param_1;
  uVar1 = FUN_00310d34(0);
  err = FUN_00348718();
  FUN_00376820(err,uVar1);
  FUN_00354714();
  FUN_0035063c(FUN_00310d4c,auStack_60);
  FUN_000262fc();
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019e058 @ 0x0019e058   (est. sk_swift_helper)
 * Ghidra: void FUN_0019e058(undefined8 param_1,undefined8 param_2,long param_3,undefined8 param_4)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019e058(unsigned long param_1,unsigned long param_2,long param_3,unsigned long param_4)

{
  unsigned long extraout_x1;
  long extraout_x8;
  long extraout_x12;
  
  (*DAT_00658c00)(*(unsigned long *)(*(long *)(param_3 + -8) + 0x40),param_2,param_2);
  (**(code **)(extraout_x12 + 0x10))
            (&stack_slot_c0 + -(extraout_x8 + 0xfU & 0xfffffffffffffff0),extraout_x1,
             param_3);
  FUN_00365b6c(param_1,&stack_slot_c0 + -(extraout_x8 + 0xfU & 0xfffffffffffffff0),param_3
               ,param_4,7);
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019e128 @ 0x0019e128   (est. sk_swift_helper)
 * Ghidra: bool FUN_0019e128(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

bool FUN_0019e128(void)

{
  unsigned long *puVar1;
  long extraout_x16;
  long unaff_x20;
  
  puVar1 = (unsigned long *)FUN_003531f0();
  sk_alloc_pages(*puVar1);
  FUN_003510c4();
  FUN_0019e1b0();
  FUN_00351a44();
  FUN_0036b118();
  if (unaff_x20 != 0) {
    FUN_00350530();
    FUN_00310d34();
    FUN_00349530();
    (**(code **)(extraout_x16 + 0x20))();
  }
  return unaff_x20 != 0;
}





/*--------------------------------------------------------------------*/
/* FUN_0019e1b0 @ 0x0019e1b0   (est. sk_swift_helper)
 * Ghidra: void FUN_0019e1b0(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019e1b0(void)
{

    unsigned long err;
  unsigned long res;
  unsigned long extraout_x1;
  unsigned long extraout_x1_00;
  long extraout_x8;
  long extraout_x8_00;
  unsigned long extraout_x8_01;
  code *extraout_x8_02;
  code *extraout_x8_03;
  code *extraout_x8_04;
  long extraout_x16;
  long extraout_x16_00;
  unsigned long uVar4;
  long i;
  unsigned long unaff_x30;
  unsigned long auVar6;
  unsigned long auVar7;
  unsigned long local_8;
  
  auVar6 = FUN_0008e518();
  FUN_00350a64();
  FUN_00310d68();
  err = FUN_000a6f88();
  FUN_0007c1a4();
  (*DAT_00658c00)();
  FUN_003494b4();
  (*DAT_00658c00)(*(unsigned long *)(extraout_x8 + 0x40));
  FUN_00349068();
  FUN_0034998c();
  (*DAT_00658c00)(*(unsigned long *)(extraout_x8_00 + 0x40));
  FUN_003489c0();
  (*DAT_00658c00)();
  FUN_0034b4c0();
  FUN_000a6f68();
  uVar4 = *(unsigned long *)(auVar6 + 0x10);
  local_8 = extraout_x8_01;
  FUN_003504e8();
  FUN_00310d80();
  FUN_00357a9c();
  FUN_0019e410(uVar4);
  i = 0;
  do {
    if (i == *(long *)(auVar6 + 0x10)) {
      FUN_003488f4();
      err = FUN_0019e578(&local_8,extraout_x1_00,extraout_x1);
LAB_0019e394:
      FUN_0008e500(err,unaff_x30);
      return;
    }
    auVar7 = FUN_00354d20();
    FUN_0019ea20(auVar7,auVar7,auVar6);
    if (SCARRY8(i,1)) {
                    /* WARNING: Does not return */
      __builtin_trap();
    }
    auVar7 = FUN_00350944(*(unsigned long *)(extraout_x16_00 + 0x20));
    (*extraout_x8_02)(auVar7,auVar7,auVar6);
    FUN_0034e54c();
    res = FUN_00356b2c();
    if ((res & 1) == 0) {
      FUN_0036b118(local_8);
      FUN_0034c3f4();
      uVar4 = FUN_000839d8();
      FUN_00351c28(uVar4,err);
      (*extraout_x8_04)();
      err = 0;
      goto LAB_0019e394;
    }
    FUN_0034bc94();
    FUN_000839d8();
    FUN_003508c0(*(unsigned long *)(extraout_x16 + 0x20));
    (*extraout_x8_03)();
    FUN_00358de8();
    FUN_0019e538();
    i = i + 1;
  } while( true );
}





/*--------------------------------------------------------------------*/
/* FUN_0019e3b0 @ 0x0019e3b0   (est. sk_swift_helper)
 * Ghidra: void FUN_0019e3b0(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019e3b0(void)

{
  long next;
  int iVar2;
  long unaff_x19;
  long *unaff_x20;
  long ctx_err;
  
  iVar2 = FUN_003592f0();
  *unaff_x20 = ctx_err;
  if ((iVar2 != 0) && (unaff_x19 <= (long)(*(unsigned long *)(ctx_err + 0x18) >> 1))) {
    return;
  }
  next = *(long *)(ctx_err + 0x10);
  if (*(long *)(ctx_err + 0x10) <= unaff_x19) {
    next = unaff_x19;
  }
  FUN_001a0774(iVar2,next,0);
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019e410 @ 0x0019e410   (est. sk_swift_helper)
 * Ghidra: void FUN_0019e410(undefined8 param_1,undefined8 param_2)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019e410(unsigned long param_1,unsigned long param_2)

{
  unsigned long uVar1;
  
  uVar1 = FUN_0034e384(param_1,param_2,param_2);
  FUN_001dd614(uVar1,0);
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019e434 @ 0x0019e434   (est. sk_swift_helper)
 * Ghidra: void FUN_0019e434(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019e434(void)

{
  long next;
  unsigned long err;
  unsigned long res;
  unsigned long unaff_x19;
  long *unaff_x20;
  unsigned long ctx_err;
  long len;
  
  FUN_0008409c();
  len = *unaff_x20;
  err = FUN_003a261c(len);
  *unaff_x20 = len;
  if ((err & 1) == 0) {
    FUN_0006b3f4(*(unsigned long *)(len + 0x10));
    FUN_001a0734();
    len = *unaff_x20;
  }
  err = *(unsigned long *)(len + 0x10);
  if (*(unsigned long *)(len + 0x18) >> 1 <= err) {
    res = FUN_0006b42c();
    FUN_001a0734(res,err + 1,1);
    len = *unaff_x20;
  }
  *(unsigned long *)(len + 0x10) = err + 1;
  next = len + err * 0x10;
  *(unsigned long *)(next + 0x20) = ctx_err;
  *(unsigned long *)(next + 0x28) = unaff_x19;
  *unaff_x20 = len;
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019e4bc @ 0x0019e4bc   (est. sk_swift_helper)
 * Ghidra: void FUN_0019e4bc(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019e4bc(void)

{
  unsigned long uVar1;
  long *unaff_x20;
  long ctx_err;
  
  uVar1 = FUN_003592f0();
  *unaff_x20 = ctx_err;
  if ((uVar1 & 1) == 0) {
    FUN_0006b3f4(*(unsigned long *)(ctx_err + 0x10));
    FUN_001a0754();
    ctx_err = *unaff_x20;
  }
  uVar1 = *(unsigned long *)(ctx_err + 0x10);
  if (*(unsigned long *)(ctx_err + 0x18) >> 1 <= uVar1) {
    FUN_0034e9e8();
    FUN_001a0754();
    ctx_err = *unaff_x20;
  }
  *(unsigned long *)(ctx_err + 0x10) = uVar1 + 1;
  FUN_00310d98();
  *unaff_x20 = ctx_err;
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019e538 @ 0x0019e538   (est. sk_swift_helper)
 * Ghidra: void FUN_0019e538(undefined8 param_1,undefined8 param_2)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019e538(param_1, param_2)
  unsigned long param_1;
  unsigned long param_2;

{
  FUN_001a1894(param_1,param_2,&DAT_001a1630,FUN_001a16e8,&DAT_00346bc8);
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019e578 @ 0x0019e578   (est. sk_swift_helper)
 * Ghidra: void FUN_0019e578(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

unsigned long FUN_0019e578(void)

{
  code *extraout_x8;
  
  FUN_00350a10();
  FUN_00355cbc();
  FUN_00310da8();
  FUN_0034bcf0();
  (*extraout_x8)();
  return 0;
}





/*--------------------------------------------------------------------*/
/* FUN_0019e5b4 @ 0x0019e5b4   (est. sk_swift_helper)
 * Ghidra: void FUN_0019e5b4(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019e5b4(void)

{
  unsigned long unaff_x19;
  unsigned long *unaff_x20;
  
  FUN_00356988();
  FUN_0036b118();
  *unaff_x20 = unaff_x19;
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019e5e8 @ 0x0019e5e8   (est. sk_swift_helper)
 * Ghidra: void thunk_FUN_001dc298(long param_1)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void thunk_FUN_001dc298(param_1)
  long param_1;

{
  unsigned long uVar1;
  unsigned long err;
  unsigned long *unaff_x20;
  
  err = *(unsigned long *)(param_1 + 0x10);
  FUN_003504e8();
  FUN_00310dd8();
  uVar1 = FUN_0019e5ec();
  if ((uVar1 & 1) == 0) {
    err = FUN_0019e66c(*unaff_x20,err);
    *unaff_x20 = err;
  }
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019e5ec @ 0x0019e5ec   (est. sk_swift_helper)
 * Ghidra: void FUN_0019e5ec(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

unsigned long FUN_0019e5ec(void)
{
  unsigned long uVar1;
  unsigned long *unaff_x20;
  
  uVar1 = *unaff_x20;
  FUN_003a261c(uVar1);
  *unaff_x20 = uVar1;
  return 0;
}





/*--------------------------------------------------------------------*/
/* FUN_0019e618 @ 0x0019e618   (est. sk_swift_helper)
 * Ghidra: void FUN_0019e618(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019e618(void)

{
  FUN_00356d20();
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019e630 @ 0x0019e630   (est. sk_swift_helper)
 * Ghidra: void FUN_0019e630(long param_1)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019e630(long param_1)

{
  FUN_001a07bc(0,*(unsigned long *)(param_1 + 0x10),0,param_1);
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019e644 @ 0x0019e644   (est. sk_swift_helper)
 * Ghidra: void FUN_0019e644(long param_1)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019e644(long param_1)

{
  FUN_001a0908(0,*(unsigned long *)(param_1 + 0x10),0,param_1);
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019e658 @ 0x0019e658   (est. sk_swift_helper)
 * Ghidra: void FUN_0019e658(long param_1)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019e658(long param_1)

{
  FUN_001a0ef0(0,*(unsigned long *)(param_1 + 0x10),0,param_1);
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019e66c @ 0x0019e66c   (est. sk_swift_helper)
 * Ghidra: void FUN_0019e66c(long param_1,undefined8 param_2)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

unsigned long FUN_0019e66c(long param_1,unsigned long param_2)

{
  FUN_001a0fa4(0,*(unsigned long *)(param_1 + 0x10),0,param_1,param_2);
  return 0;
}





/*--------------------------------------------------------------------*/
/* FUN_0019e690 @ 0x0019e690   (est. sk_swift_helper)
 * Ghidra: void FUN_0019e690(ulong param_1,undefined8 param_2,long param_3)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019e690(unsigned long param_1,unsigned long param_2,long param_3)

{
  if ((-1 < (long)param_1) && (param_1 < *(unsigned long *)(param_3 + 0x10))) {
    return;
  }
  FUN_00348304();
                    /* WARNING: Subroutine does not return */
  sk_swift_fatal_error_2();
}





/*--------------------------------------------------------------------*/
/* FUN_0019e6bc @ 0x0019e6bc   (est. sk_swift_helper)
 * Ghidra: void FUN_0019e6bc(ulong param_1,long param_2)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019e6bc(unsigned long param_1,long param_2)

{
  if ((-1 < (long)param_1) && (param_1 < *(unsigned long *)(param_2 + 0x10))) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  sk_swift_fatal_error_2(sk_fatal_error_str,0xb,2,s_Index_out_of_range_005cd940,0x12,2,
               s_Swift_ContiguousArrayBuffer_swif_005cd960,0x21,2,0x2c1,1);
}





/*--------------------------------------------------------------------*/
/* FUN_0019e728 @ 0x0019e728   (est. sk_swift_helper)
 * Ghidra: void FUN_0019e728(ulong param_1,long param_2)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019e728(param_1, param_2)
  unsigned long param_1;
  long param_2;

{
  if ((-1 < (long)param_1) && (param_1 < *(unsigned long *)(param_2 + 0x10))) {
    return;
  }
  FUN_003485b8(1);
  FUN_00351a8c();
                    /* WARNING: Subroutine does not return */
  sk_swift_fatal_error_2();
}





/*--------------------------------------------------------------------*/
/* FUN_0019e760 @ 0x0019e760   (est. sk_swift_helper)
 * Ghidra: void FUN_0019e760(long param_1,long param_2)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019e760(long param_1,long param_2)

{
  char *pcVar1;
  unsigned long err;
  unsigned long res;
  
  if (*(long *)(param_2 + 0x10) < param_1) {
    res = 0x1ae;
    pcVar1 = s_Array_index_is_out_of_range_005cd9b0;
    err = 0x1b;
  }
  else {
    if (-1 < param_1) {
      return;
    }
    res = 0x1af;
    pcVar1 = s_Negative_Array_index_is_out_of_r_005cd9d0;
    err = 0x24;
  }
                    /* WARNING: Subroutine does not return */
  sk_swift_fatal_error_2(sk_fatal_error_str,0xb,2,pcVar1,err,2,s_Swift_Array_swift_005cd990,0x11,2,res
               ,1);
}





/*--------------------------------------------------------------------*/
/* FUN_0019e8d8 @ 0x0019e8d8   (est. sk_swift_helper)
 * Ghidra: void thunk_FUN_001dc3b8(undefined8 param_1,long param_2)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void thunk_FUN_001dc3b8(unsigned long param_1,long param_2)

{
  FUN_00357874(*(unsigned char *)(*(long *)(param_2 + -8) + 0x50));
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019e914 @ 0x0019e914   (est. sk_swift_helper)
 * Ghidra: long FUN_0019e914(long param_1,long param_2)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

long FUN_0019e914(param_1, param_2)
  long param_1;
  long param_2;

{
    
  if (!SCARRY8(param_1,param_2)) {
    return param_1 + param_2;
  }
                    /* WARNING: Does not return */
  __builtin_trap();
}





/*--------------------------------------------------------------------*/
/* FUN_0019e924 @ 0x0019e924   (est. sk_swift_helper)
 * Ghidra: void FUN_0019e924(long *param_1)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019e924(long *param_1)

{
    
  if (!SCARRY8(*param_1,1)) {
    *param_1 = *param_1 + 1;
    return;
  }
                    /* WARNING: Does not return */
  __builtin_trap();
}





/*--------------------------------------------------------------------*/
/* FUN_0019e93c @ 0x0019e93c   (est. sk_swift_helper)
 * Ghidra: long FUN_0019e93c(long param_1)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

long FUN_0019e93c(param_1)
  long param_1;

{
    
  if (!SBORROW8(param_1,1)) {
    return param_1 + -1;
  }
                    /* WARNING: Does not return */
  __builtin_trap();
}





/*--------------------------------------------------------------------*/
/* FUN_0019e97c @ 0x0019e97c   (est. sk_swift_helper)
 * Ghidra: unknown signature
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

unsigned long FUN_0019e97c(long param_1,unsigned long param_2,long param_3)

{
  unsigned long uVar1;
    unsigned long auVar3;
  
  uVar1 = param_3 - param_1;
  if (SBORROW8(param_3,param_1)) {
                    /* WARNING: Does not return */
    __builtin_trap();
  }
  if ((long)param_2 < 1) {
    if (0 < (long)uVar1 || (long)uVar1 <= (long)param_2) goto LAB_0019e9b0;
  }
  else if (((long)uVar1 < 0) || (param_2 <= uVar1)) {
LAB_0019e9b0:
    if (!SCARRY8(param_1,param_2)) {
      auVar3 = 0;
      auVar3 = param_1 + param_2;
      return (unsigned long)auVar3;
    }
                    /* WARNING: Does not return */
    __builtin_trap();
  }
  return ZEXT816(1) << 0x40;
}





/*--------------------------------------------------------------------*/
/* FUN_0019e9c8 @ 0x0019e9c8   (est. sk_swift_helper)
 * Ghidra: long thunk_FUN_001a9a84(long param_1,ulong param_2,long param_3)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

long thunk_FUN_001a9a84(param_1, param_2, param_3)
  long param_1;
  unsigned long param_2;
  long param_3;

{
  unsigned long uVar1;
    long lVar3;
  
  uVar1 = param_3 - param_1;
  if (SBORROW8(param_3,param_1)) {
                    /* WARNING: Does not return */
    __builtin_trap();
  }
  if ((long)param_2 < 1) {
    if (0 < (long)uVar1 || (long)uVar1 <= (long)param_2) goto LAB_001a9ab0;
  }
  else if (((long)uVar1 < 0) || (param_2 <= uVar1)) {
LAB_001a9ab0:
    if (!SCARRY8(param_1,param_2)) {
      return param_1 + param_2;
    }
                    /* WARNING: Does not return */
    __builtin_trap();
  }
  lVar3 = sk_collection_underflow();
  return lVar3;
}





/*--------------------------------------------------------------------*/
/* FUN_0019ea20 @ 0x0019ea20   (est. sk_swift_helper)
 * Ghidra: void FUN_0019ea20(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019ea20(param_1, param_2, param_3)
  unsigned long param_1;
  unsigned long param_2;
  unsigned long param_3;
{
  unsigned long uVar1;
  unsigned long extraout_x8;
  long extraout_x16;
  long unaff_x20;
  long ctx_err;
  
  uVar1 = FUN_0034b430();
  FUN_0019e690(uVar1,0);
  FUN_00350bcc();
                    /* WARNING: Could not recover jumptable at 0x0019ea90. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(extraout_x16 + 0x10))
            (extraout_x8,
             unaff_x20 +
             ((unsigned long)*(unsigned char *)(extraout_x16 + 0x50) + 0x20 &
             ((unsigned long)*(unsigned char *)(extraout_x16 + 0x50) ^ 0xffffffffffffffff)) +
             *(long *)(extraout_x16 + 0x48) * ctx_err);
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019ea94 @ 0x0019ea94   (est. sk_swift_helper)
 * Ghidra: FUN_0034a958();
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

unsigned long FUN_0019ea94(void)

{
  long extraout_x8;
  long extraout_x16;
  long *unaff_x20;
  long next;
  long ctx_err;
  unsigned long auVar2;
  
  FUN_0034a958();
  thunk_FUN_001dc298();
  next = *unaff_x20;
  FUN_0011aa70();
  FUN_0019e728();
  FUN_0034e3ac();
  auVar2 = next + ((unsigned long)*(unsigned char *)(extraout_x16 + 0x50) + 0x20 &
                         ((unsigned long)*(unsigned char *)(extraout_x16 + 0x50) ^ 0xffffffffffffffff)) +
                 *(long *)(extraout_x8 + 0x48) * ctx_err;
  auVar2 = (unsigned long)FUN_0001a1c8;
  return auVar2;
}





/*--------------------------------------------------------------------*/
/* FUN_0019eb20 @ 0x0019eb20   (est. sk_swift_helper)
 * Ghidra: long FUN_0019eb20(long param_1,long param_2)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

long FUN_0019eb20(long param_1,long param_2)

{
  unsigned long uVar1;
  
  uVar1 = (unsigned long)*(unsigned char *)(*(long *)(param_2 + -8) + 0x50);
  return param_1 + (uVar1 + 0x20 & (uVar1 ^ 0xffffffffffffffff));
}





/*--------------------------------------------------------------------*/
/* FUN_0019eb70 @ 0x0019eb70   (est. sk_swift_helper)
 * Ghidra: void FUN_0019eb70(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

unsigned long FUN_0019eb70(void)
{
  FUN_001dc56c();
  return 0;
}





/*--------------------------------------------------------------------*/
/* FUN_0019eb88 @ 0x0019eb88   (est. sk_swift_helper)
 * Ghidra: void FUN_0019eb88(undefined8 param_1,long param_2,undefined8 param_3)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019eb88(unsigned long param_1,long param_2,unsigned long param_3)

{
  if (-1 < param_2) {
    sk_alloc_pages(1,param_3);
    return;
  }
                    /* WARNING: Subroutine does not return */
  sk_swift_fatal_error_2(sk_fatal_error_str,0xb,2,s_Negative_value_is_not_representa_005ce190,0x23,2,
               s_Swift_Integers_swift_005cd680,0x14,2,0xcf8,1);
}





/*--------------------------------------------------------------------*/
/* FUN_0019ec24 @ 0x0019ec24   (est. sk_swift_helper)
 * Ghidra: void FUN_0019ec24(undefined8 param_1,undefined8 param_2,long param_3)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019ec24(unsigned long param_1,unsigned long param_2,long param_3)

{
  long extraout_x16;
  
  FUN_0035a028(param_2,param_1,param_2,param_1);
  FUN_001e5438(param_3,param_3 + ((unsigned long)*(unsigned char *)(extraout_x16 + 0x50) + 0x20 &
                                 ((unsigned long)*(unsigned char *)(extraout_x16 + 0x50) ^ 0xffffffffffffffff)));
  FUN_00350b90();
  FUN_0035a4c8();
  sk_alloc_pages(param_3);
  FUN_0034c444();
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019eca0 @ 0x0019eca0   (est. sk_swift_helper)
 * Ghidra: void FUN_0019eca0(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019eca0(void)

{
  FUN_001dc620();
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019ecfc @ 0x0019ecfc   (est. sk_swift_helper)
 * Ghidra: void FUN_0019ecfc(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019ecfc(void)

{
  unsigned long in_x3;
  code *extraout_x8;
  
  FUN_00349fcc();
  FUN_00350adc(in_x3);
  FUN_0008412c();
  (*extraout_x8)();
  FUN_00356d20();
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019ed3c @ 0x0019ed3c   (est. sk_swift_helper)
 * Ghidra: ulong FUN_0019ed3c(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

unsigned long FUN_0019ed3c(void)

{
  unsigned long in_x3;
  
  return in_x3 >> 1;
}





/*--------------------------------------------------------------------*/
/* FUN_0019ed78 @ 0x0019ed78   (est. sk_swift_helper)
 * Ghidra: uint FUN_0019ed78(undefined8 param_1,code *param_2)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

unsigned int FUN_0019ed78(unsigned long param_1,code *param_2)

{
  unsigned int uVar1;
  
  uVar1 = (*param_2)();
  return uVar1 & 1;
}





/*--------------------------------------------------------------------*/
/* FUN_0019eda4 @ 0x0019eda4   (est. sk_swift_helper)
 * Ghidra: void FUN_0019eda4(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019eda4(void)

{
  long next;
    bool overflow;
  long len;
  unsigned long fatal_v;
  unsigned long fatal_a;
  unsigned long in_x3;
  unsigned long in_x5;
  long extraout_x8;
  code *extraout_x8_00;
  unsigned long unaff_x30;
  unsigned long auVar7;
  unsigned long auVar8;
  
  auVar7 = FUN_00351e20();
  if (auVar7 < 0) {
    FUN_003488bc(1);
    FUN_0034a3d8();
  }
  else {
    auVar8 = FUN_00353c48();
    if (auVar8 <= extraout_x8) {
      next = auVar7 - auVar8;
      if (SBORROW8(auVar7,auVar8)) {
                    /* WARNING: Does not return */
        __builtin_trap();
      }
      FUN_003542e8();
      FUN_00027788(in_x5);
      FUN_0034e63c();
      len = (*extraout_x8_00)();
      overflow = SBORROW8(len,next);
      if (!overflow) {
        FUN_0035a438(len - next);
        if (!overflow) {
          fatal_v = FUN_0034e384();
          FUN_001dd614(fatal_v,1,in_x3);
          FUN_0035113c();
          fatal_v = FUN_00310dd8();
          fatal_a = FUN_003498dc();
          FUN_00376820(fatal_a,fatal_v);
          FUN_00350618();
          FUN_0035430c();
          FUN_00356140();
          FUN_00351d30(unaff_x30);
          FUN_0019c53c();
          return;
        }
                    /* WARNING: Does not return */
        __builtin_trap();
      }
                    /* WARNING: Does not return */
      __builtin_trap();
    }
    FUN_003488bc(1);
    FUN_0034a3d8();
  }
  FUN_003504b8();
                    /* WARNING: Subroutine does not return */
  sk_swift_fatal_error_2();
}





/*--------------------------------------------------------------------*/
/* FUN_0019eec0 @ 0x0019eec0   (est. sk_swift_helper)
 * Ghidra: void FUN_0019eec0(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019eec0(void)

{
  long unaff_x19;
  unsigned long *unaff_x20;
  unsigned long auVar1;
  
  FUN_00349a18();
  FUN_0036a908(0x40,0xfada);
  auVar1 = FUN_003501fc();
  FUN_00100efc(auVar1,auVar1,*unaff_x20,*(unsigned long *)(unaff_x19 + 0x10));
  FUN_0019eb70();
  FUN_00357694();
  FUN_00353c54();
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019ef84 @ 0x0019ef84   (est. sk_swift_helper)
 * Ghidra: unknown signature
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

unsigned long *FUN_0019ef84(long *param_1,unsigned long *param_2,unsigned long param_3)

{
  long next;
  unsigned long err;
  
  next = FUN_0036a908(0x28,0xdb1);
  *param_1 = next;
  err = FUN_0019ea94();
  *(unsigned long *)(next + 0x20) = err;
  return &DAT_003471a0;
}





/*--------------------------------------------------------------------*/
/* FUN_0019f010 @ 0x0019f010   (est. sk_swift_helper)
 * Ghidra: unknown signature
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

unsigned long FUN_0019f010(long *param_1,unsigned long *param_2,long param_3)

{
  unsigned char (*pauVar1) [16];
  unsigned long err;
  unsigned long res;
  unsigned long *unaff_x20;
  unsigned long auVar4;
  
  pauVar1 = (unsigned char (*) [16])FUN_0036a908(0x40,0x5976);
  *param_1 = (long)pauVar1;
  *(unsigned long **)pauVar1[2] = unaff_x20;
  *(long *)(pauVar1[2] + 8) = param_3;
  err = param_2[1];
  *(unsigned long *)pauVar1[3] = *param_2;
  *(unsigned long *)(pauVar1[3] + 8) = err;
  err = *unaff_x20;
  res = *(unsigned long *)(param_3 + 0x10);
  auVar4 = FUN_0019eb70();
  *pauVar1 = auVar4;
  *(unsigned long *)pauVar1[1] = err;
  *(unsigned long *)(pauVar1[1] + 8) = res;
  auVar4 = (unsigned long)pauVar1;
  auVar4 = (unsigned long)&DAT_0019f098;
  return auVar4;
}





/*--------------------------------------------------------------------*/
/* FUN_0019f0b0 @ 0x0019f0b0   (est. sk_swift_helper)
 * Ghidra: void FUN_0019f0b0(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019f0b0(unsigned long param_1,unsigned long param_2,unsigned long param_3,unsigned long param_4,
                 unsigned long param_5)

{
  unsigned long uVar1;
  
  uVar1 = FUN_00376820(&DAT_004e824c,param_4);
  FUN_0019f1ec(param_1,param_2,param_3,param_4,uVar1,param_5);
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019f130 @ 0x0019f130   (est. sk_swift_helper)
 * Ghidra: void FUN_0019f130(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019f130(void)

{
  FUN_001da01c();
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019f134 @ 0x0019f134   (est. sk_swift_helper)
 * Ghidra: void FUN_0019f134(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019f134(void)

{
  FUN_001da01c();
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019f148 @ 0x0019f148   (est. sk_swift_helper)
 * Ghidra: void FUN_0019f148(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019f148(void)

{
  long next;
  long lVar2;
  unsigned long res;
  long *unaff_x20;
  long ctx_err;
  long len;
  long local_50;
  long lStack_48;
  
  next = *unaff_x20;
  lVar2 = unaff_x20[1];
  if (next == 0) {
    res = 0;
  }
  else {
    len = lVar2 - next;
    local_50 = next;
    lStack_48 = len;
    res = FUN_001da1c0();
    if (ctx_err != 0) {
      FUN_00320fc8(next,len,&local_50);
      return;
    }
    FUN_00320fc8(next,len,&local_50);
  }
  FUN_001e6608(0,res,next,lVar2);
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019f1ec @ 0x0019f1ec   (est. sk_swift_helper)
 * Ghidra: void FUN_0019f1ec(undefined8 param_1)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019f1ec(unsigned long param_1)

{
  unsigned long uVar1;
  unsigned long in_x3;
  unsigned long in_x4;
  code *extraout_x8;
  code *extraout_x9;
  code *extraout_x9_00;
  code *extraout_x9_01;
  long ctx_err;
  unsigned long unaff_x27;
  unsigned char auStack_a0 [16];
  unsigned char local_60 [8];
  char local_58;
  
  FUN_00352c34();
  FUN_003537fc();
  uVar1 = FUN_00027754(in_x3);
  FUN_00349748();
  FUN_000bd3a4();
  FUN_00377824();
  FUN_00348fd8();
  FUN_0007c1a4();
  (*DAT_00658c00)();
  FUN_0034b0c4();
  FUN_00310e74(in_x4);
  FUN_003516fc();
  FUN_00351c70(local_60,FUN_00310e50,auStack_a0);
  (*extraout_x9)();
  if (ctx_err == 0) {
    if (local_58 == '\x01') {
      FUN_000dbf08(param_1,unaff_x27);
      FUN_003534c8();
      FUN_001da324();
    }
    else {
      FUN_000277b8(uVar1);
      FUN_00350c50();
      FUN_0009e234();
      (*extraout_x9_00)();
      FUN_00310ea4();
      FUN_00077708(param_1);
      (*extraout_x9_01)();
      FUN_00353be8();
      FUN_003516e4();
      (*extraout_x8)();
    }
  }
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019f370 @ 0x0019f370   (est. sk_swift_helper)
 * Ghidra: void FUN_0019f370(ulong param_1,ulong param_2)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019f370(unsigned long param_1,unsigned long param_2)

{
  long next;
  long lVar2;
  unsigned long res;
  unsigned long uVar4;
  unsigned long fatal_v;
  unsigned long fatal_a;
  unsigned long count;
  unsigned long *unaff_x20;
  
  if (param_1 != param_2) {
    res = *unaff_x20;
    uVar4 = unaff_x20[1];
    next = (param_1 & 7) << 3;
    fatal_v = res;
    if (7 < (long)param_1) {
      fatal_v = uVar4;
    }
    count = res;
    if (7 < (long)param_2) {
      count = uVar4;
    }
    lVar2 = (param_2 & 7) << 3;
    fatal_a = (-0xffL << next) - 1;
    count = (count >> lVar2 & 0xff) << next;
    if ((long)param_1 < 8) {
      res = count | res & fatal_a;
      *unaff_x20 = res;
    }
    else {
      uVar4 = count | uVar4 & fatal_a;
      unaff_x20[1] = uVar4;
    }
    count = (-0xffL << lVar2) - 1;
    fatal_v = (fatal_v >> next & 0xff) << lVar2;
    if ((long)param_2 < 8) {
      *unaff_x20 = res & count | fatal_v;
      return;
    }
    unaff_x20[1] = uVar4 & count | fatal_v;
  }
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019f410 @ 0x0019f410   (est. sk_swift_helper)
 * Ghidra: void FUN_0019f410(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019f410(unsigned long param_1,unsigned long param_2,unsigned long param_3,unsigned long param_4)

{
  code *pcVar3;
  code *pcVar4;
  code *pcVar5;
  unsigned long uVar1;
  unsigned long err;
    long extraout_x8;
  code *extraout_x8_00;
  code *extraout_x8_01;
      code *extraout_x8_02;
  code *extraout_x8_03;
  long extraout_x16;
  long extraout_x16_00;
  unsigned long unaff_x30;
  unsigned long auVar6;
  unsigned long local_30;
  unsigned char auStack_20 [32];
  
  FUN_0008e518();
  FUN_00351a38();
  FUN_00351ef8(param_4);
  FUN_0034de64();
  FUN_0034d8d4();
  FUN_00377824();
  FUN_00348d4c();
  FUN_0007c1a4();
  (*DAT_00658c00)();
  FUN_0034aee4();
  auVar6 = FUN_00348b94();
  uVar1 = FUN_00377824(auVar6,auVar6,param_3);
  FUN_000a6f88();
  (*DAT_00658c00)(*(unsigned long *)(extraout_x8 + 0x40));
  FUN_00348b5c();
  (*DAT_00658c00)();
  FUN_0034aa28();
  FUN_0034fde0();
  FUN_00377bec();
  FUN_00352ee4();
  FUN_00350adc();
  FUN_003507e0();
  FUN_003512cc();
  err = (*extraout_x8_00)();
  if ((err & 1) == 0) {
    pcVar3 = (code *)FUN_00352ecc();
    FUN_00351eb4(auStack_20);
    auVar6 = (*extraout_x8_01)();
    pcVar4 = *(code **)(extraout_x16_00 + 0x10);
    (*pcVar4)(local_30,auVar6,uVar1);
    FUN_0034cfa4();
    (*auVar6)();
    pcVar5 = *(code **)(extraout_x16 + 0x10);
    FUN_0034fec0();
    (*extraout_x8_02)();
    FUN_00351eb4(auStack_20);
    __builtin_trap();
    FUN_003543f8(pcVar4);
    (*extraout_x8_03)();
    FUN_0034cfa4();
    __builtin_trap();
    FUN_003568e8();
    pcVar3 = (code *)FUN_00310ed4();
    FUN_0034ee98();
    __builtin_trap();
    FUN_003507d4();
    __builtin_trap();
    FUN_00351420(local_30);
    __builtin_trap();
  }
  FUN_0008e500(unaff_x30);
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019f63c @ 0x0019f63c   (est. sk_swift_helper)
 * Ghidra: void FUN_0019f63c(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019f63c(void)

{
  FUN_003580e4();
  FUN_0019f658();
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019f658 @ 0x0019f658   (est. sk_swift_helper)
 * Ghidra: void FUN_0019f658(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019f658(void)
{
  FUN_0019f698();
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019f698 @ 0x0019f698   (est. sk_swift_helper)
 * Ghidra: void FUN_0019f698(undefined8 param_1,code *param_2,undefined8 param_3,long param_4,
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019f698(param_1, param_2, param_3, param_4, param_5, param_6, param_7)
  unsigned long param_1;
  code * param_2;
  unsigned long param_3;
  long param_4;
  unsigned long param_5;
  code * param_6;
  code * param_7;

{
  unsigned long uVar1;
  long lVar2;
  long *unaff_x20;
  long ctx_err;
  unsigned long res;
  unsigned long unaff_x30;
  unsigned char local_70 [16];
  
  (*param_6)(param_4);
  lVar2 = *unaff_x20;
  res = *(unsigned long *)(lVar2 + 0x10);
  uVar1 = (unsigned long)*(unsigned char *)(*(long *)(*(long *)(param_4 + 0x10) + -8) + 0x50);
  uVar1 = uVar1 + 0x20 & (uVar1 ^ 0xffffffffffffffff);
  local_70 = FUN_001a26e0(lVar2 + uVar1,res);
  (*param_2)(param_1,local_70);
  FUN_0034a210();
  if (ctx_err == 0) {
    FUN_00002534();
    FUN_00348d30();
    FUN_00351978(local_70,lVar2 + uVar1,res);
    (*param_7)();
    FUN_0034bc94(param_1);
    FUN_000839d8();
  }
  else {
    FUN_00002534();
    FUN_00348d30();
    FUN_00351978(local_70,lVar2 + uVar1,res);
    (*param_7)();
  }
  FUN_0035578c(unaff_x30);
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019f7bc @ 0x0019f7bc   (est. sk_swift_helper)
 * Ghidra: void FUN_0019f7bc(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019f7bc(void)

{
  unsigned long uVar1;
  unsigned long *unaff_x19;
  
  FUN_00351124();
  uVar1 = FUN_0019e93c();
  *unaff_x19 = uVar1;
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019f7e8 @ 0x0019f7e8   (est. sk_swift_helper)
 * Ghidra: void FUN_0019f7e8(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019f7e8(void)

{
  unsigned long uVar1;
  unsigned long *unaff_x19;
  
  FUN_00351124();
  uVar1 = FUN_0019e914();
  *unaff_x19 = uVar1;
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019f810 @ 0x0019f810   (est. sk_swift_helper)
 * Ghidra: void FUN_0019f810(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019f810(void)

{
  FUN_0034c434();
  thunk_FUN_001a9a84();
  FUN_0035272c();
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019f844 @ 0x0019f844   (est. sk_swift_helper)
 * Ghidra: void FUN_0019f844(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019f844(void)

{
  unsigned long uVar1;
  unsigned long *unaff_x19;
  
  FUN_00356c18();
  uVar1 = thunk_FUN_0001612c();
  *unaff_x19 = uVar1;
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019f86c @ 0x0019f86c   (est. sk_swift_helper)
 * Ghidra: unknown signature
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

undefined * FUN_0019f86c(long *param_1,unsigned long *param_2,long param_3)

{
  long next;
  unsigned long err;
  unsigned long *unaff_x20;
  
  next = FUN_0036a908(0x28,0xbc95);
  *param_1 = next;
  err = FUN_0019f8e4(next,*param_2,*unaff_x20,*(unsigned long *)(param_3 + 0x10));
  *(unsigned long *)(next + 0x20) = err;
  return &DAT_003471a4;
}





/*--------------------------------------------------------------------*/
/* FUN_0019f8e4 @ 0x0019f8e4   (est. sk_swift_helper)
 * Ghidra: FUN_0019ea20(lVar1,param_2,param_3,param_4);
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

unsigned long FUN_0019f8e4(long *param_1,unsigned long param_2,unsigned long param_3,long param_4)

{
  long next;
  unsigned long auVar2;
  
  next = *(long *)(param_4 + -8);
  *param_1 = param_4;
  param_1[1] = next;
  next = FUN_0036a908(*(unsigned long *)(next + 0x40),0x68ba);
  param_1[2] = next;
  FUN_0019ea20(next,param_2,param_3,param_4);
  auVar2 = next;
  auVar2 = &DAT_003471a8;
  return auVar2;
}





/*--------------------------------------------------------------------*/
/* FUN_0019f9a8 @ 0x0019f9a8   (est. sk_swift_helper)
 * Ghidra: void FUN_0019f9a8(undefined8 param_1,undefined8 param_2)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019f9a8(unsigned long param_1,unsigned long param_2)

{
  unsigned long uVar1;
  
  uVar1 = FUN_00376820(&DAT_004e8214,param_2);
  FUN_0019fa60(param_1,param_2,uVar1,0x6720e8);
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019fa14 @ 0x0019fa14   (est. sk_swift_helper)
 * Ghidra: unknown signature
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

unsigned long FUN_0019fa14(unsigned int param_1)

{
  unsigned long uVar1;
  unsigned long auVar2;
  
  uVar1 = 1;
  if (0xffff < param_1) {
    uVar1 = 2;
  }
  auVar2 = 0;
  auVar2 = uVar1;
  return auVar2 << 0x40;
}





/*--------------------------------------------------------------------*/
/* FUN_0019fa28 @ 0x0019fa28   (est. sk_swift_helper)
 * Ghidra: unknown signature
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

unsigned long FUN_0019fa28(unsigned int param_1)

{
  unsigned long uVar1;
  unsigned long err;
  unsigned long auVar3;
  
  uVar1 = 3;
  if (0xffff < param_1) {
    uVar1 = 4;
  }
  err = 2;
  if (0x7ff < param_1) {
    err = uVar1;
  }
  uVar1 = 1;
  if (0x7f < param_1) {
    uVar1 = err;
  }
  auVar3 = 0;
  auVar3 = uVar1;
  return auVar3 << 0x40;
}





/*--------------------------------------------------------------------*/
/* FUN_0019fa54 @ 0x0019fa54   (est. sk_swift_helper)
 * Ghidra: unknown signature
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

unsigned long FUN_0019fa54(unsigned long param_1,unsigned long param_2)

{
  unsigned long auVar1;
  
  auVar1 = 0;
  auVar1 = param_2 >> 0x38 & 0xf;
  return auVar1 << 0x40;
}





/*--------------------------------------------------------------------*/
/* FUN_0019fa60 @ 0x0019fa60   (est. sk_swift_helper)
 * Ghidra: void FUN_0019fa60(undefined8 param_1,undefined8 param_2,undefined8 param_3)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019fa60(unsigned long param_1,unsigned long param_2,unsigned long param_3)

{
  code *pcVar5;
  code *pcVar6;
  int iVar1;
  unsigned long err;
  unsigned long res;
  unsigned long uVar4;
  unsigned long extraout_x1;
  unsigned long extraout_x8;
  long extraout_x8_00;
  long extraout_x8_01;
  code *extraout_x8_02;
  code *extraout_x8_03;
  long extraout_x9;
  code *extraout_x9_00;
  code *extraout_x9_01;
  code *extraout_x9_02;
  long extraout_x16;
  long extraout_x16_00;
    long unaff_x24;
    unsigned long unaff_x30;
  unsigned long auVar7;
  unsigned long local_18;
  
  FUN_0008e518();
  FUN_00027754(extraout_x1);
  FUN_00350780();
  FUN_0034a944();
  FUN_00350b9c();
  err = FUN_00377824();
  FUN_0034b0b4();
  FUN_00352360();
  FUN_003722e4();
  FUN_00348d4c();
  (*DAT_00658c00)(*(unsigned long *)(extraout_x8_00 + 0x40));
  FUN_003493c4();
  FUN_003503f8();
  (*DAT_00658c00)();
  FUN_00350464();
  FUN_0035a2b8();
  FUN_003499f0();
  (*DAT_00658c00)(*(unsigned long *)(extraout_x8_01 + 0x40));
  FUN_00349db0();
  (*DAT_00658c00)();
  FUN_0034b4c0();
  FUN_000277b8();
  FUN_00351184();
  FUN_003505e8();
  (*extraout_x9_00)();
  FUN_00350704();
  FUN_003505e8();
  (*extraout_x9_01)();
  FUN_00350780(param_3);
  FUN_00310e20();
  FUN_00350a7c();
  FUN_00350db4();
  res = (*extraout_x8_02)();
  if ((res & 1) != 0) {
    pcVar5 = *(code **)(extraout_x16_00 + 0x20);
    auVar7 = FUN_0035145c();
    (*pcVar5)(auVar7,auVar7,err);
    FUN_003511d8(local_18 + *(int *)(unaff_x24 + 0x30));
    __builtin_trap();
    FUN_00351d0c();
    FUN_003513b4(extraout_x9);
    (*extraout_x9_02)();
    iVar1 = *(int *)(unaff_x24 + 0x30);
    FUN_0035169c(extraout_x8);
    __builtin_trap();
    pcVar6 = *(code **)(extraout_x16_00 + 8);
    (*pcVar6)(extraout_x9 + iVar1,err);
    FUN_003513b4(*(unsigned long *)(extraout_x16 + 0x20),extraout_x9);
    (*extraout_x8_03)();
    iVar1 = *(int *)(unaff_x24 + 0x30);
    FUN_003549c0(param_3);
    FUN_00350488();
    FUN_00310e08();
    uVar4 = FUN_00353ac8();
    (*pcVar5)(uVar4,extraout_x9 + iVar1,err);
    FUN_00350b00();
    __builtin_trap();
    FUN_0008e500(unaff_x30);
    return;
  }
  FUN_00347d60();
                    /* WARNING: Subroutine does not return */
  sk_swift_fatal_error_2();
}





/*--------------------------------------------------------------------*/
/* FUN_0019fcc8 @ 0x0019fcc8   (est. sk_swift_helper)
 * Ghidra: bool FUN_0019fcc8(ulong param_1)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

bool FUN_0019fcc8(unsigned long param_1)

{
  return (param_1 & 0xff00000000) == 0;
}





/*--------------------------------------------------------------------*/
/* FUN_0019fcd4 @ 0x0019fcd4   (est. sk_swift_helper)
 * Ghidra: bool FUN_0019fcd4(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

bool FUN_0019fcd4(void)

{
  long extraout_x8;
  
  FUN_0034f064();
  return extraout_x8 == 0;
}





/*--------------------------------------------------------------------*/
/* FUN_0019fd10 @ 0x0019fd10   (est. sk_swift_helper)
 * Ghidra: void FUN_0019fd10(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019fd10(void)

{
  unsigned long uVar1;
  long extraout_x8;
  code *extraout_x8_00;
  code *extraout_x9;
  code *extraout_x9_00;
  code *result;
  unsigned long unaff_x30;
  
  FUN_00084220();
  FUN_00354708();
  FUN_0034b164();
  FUN_00353a18();
  FUN_00377824();
  FUN_00348e18();
  (*DAT_00658c00)(*(unsigned long *)(extraout_x8 + 0x40));
  FUN_00348abc();
  (*DAT_00658c00)();
  FUN_0034b87c();
  FUN_0034fe64();
  FUN_000e15d8();
  (*extraout_x9)();
  FUN_00310924();
  FUN_0034f644();
  (*extraout_x9_00)();
  FUN_0034db38();
  FUN_00377bec();
  FUN_0034c4fc();
  FUN_000a6e14();
  FUN_0034df34();
  (*extraout_x8_00)();
  FUN_0035a640();
  FUN_0035060c();
  (*result)();
  FUN_003505e8();
  (*result)();
  uVar1 = FUN_0035687c();
  FUN_00084234(uVar1,unaff_x30);
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019fe20 @ 0x0019fe20   (est. sk_swift_helper)
 * Ghidra: void FUN_0019fe20(undefined8 param_1,undefined8 param_2,undefined8 param_3)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019fe20(unsigned long param_1,unsigned long param_2,unsigned long param_3)

{
  unsigned long uVar1;
  unsigned long extraout_x9;
  
  uVar1 = FUN_0034a944();
  FUN_00377824(uVar1,param_3,extraout_x9);
  FUN_00352efc();
  FUN_00310d68();
  FUN_0034b690();
  FUN_000839d8();
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019fe64 @ 0x0019fe64   (est. sk_swift_helper)
 * Ghidra: void FUN_0019fe64(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019fe64(void)

{
  FUN_0019ff50();
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019fe68 @ 0x0019fe68   (est. sk_swift_helper)
 * Ghidra: void FUN_0019fe68(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019fe68(void)

{
  FUN_0019ff50();
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019fe7c @ 0x0019fe7c   (est. sk_swift_helper)
 * Ghidra: void FUN_0019fe7c(long param_1,long param_2,long param_3)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019fe7c(long param_1,long param_2,long param_3)

{
  if (param_1 < param_2 || param_3 < param_1) {
    FUN_00348384(1);
                    /* WARNING: Subroutine does not return */
    sk_swift_fatal_error_2();
  }
  return;
}





/*--------------------------------------------------------------------*/
/* FUN_0019febc @ 0x0019febc   (est. sk_swift_helper)
 * Ghidra: void FUN_0019febc(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019febc(void)

{
                    /* WARNING: Subroutine does not return */
  sk_swift_fatal_error_2(sk_fatal_error_str,0xb,2,sk_index_oob_str,0x13,2,
               sk_collection_swift,0x16,2,0x2d2,1);
}





/*--------------------------------------------------------------------*/
/* FUN_0019ff2c @ 0x0019ff2c   (est. sk_swift_helper)
 * Ghidra: void FUN_0019ff2c(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019ff2c(void)

{
  FUN_00348384(1);
                    /* WARNING: Subroutine does not return */
  sk_swift_fatal_error_2();
}





/*--------------------------------------------------------------------*/
/* FUN_0019ff50 @ 0x0019ff50   (est. sk_swift_helper)
 * Ghidra: void FUN_0019ff50(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019ff50(void)
{
  unsigned long uVar1;
    unsigned long res;
  unsigned long in_x3;
  unsigned long unaff_x30;
  
  FUN_00357ca0();
  FUN_00353274();
  FUN_00351a38();
  uVar1 = FUN_0034b164();
  FUN_00377824(uVar1,in_x3);
  FUN_000e15d8();
  FUN_00352a4c();
  FUN_00377bec();
  pcVar2 = (code *)FUN_00310e20();
  FUN_003502a8();
  __builtin_trap();
  if ((res & 1) != 0) {
  code *pcVar2;
    FUN_0034e0d4();
    FUN_00310f04();
    FUN_00351100();
    __builtin_trap();
    if ((res & 1) != 0) {
      FUN_00357c44(unaff_x30);
      return;
    }
  }
  FUN_00348384(1);
                    /* WARNING: Subroutine does not return */
  sk_swift_fatal_error_2();
}





/*--------------------------------------------------------------------*/
/* FUN_0019fffc @ 0x0019fffc   (est. sk_swift_helper)
 * Ghidra: void FUN_0019fffc(void)
 * Swift-runtime helper for the XnuUpcallsV2 type: collection / string-interpolation
 * operation with precondition bounds checks and fatal-error handling.
 * Confidence: medium (templated Swift runtime body).
 * Notes: source file XnuUpcallsV2/XnuUpcallsV2.swift; see extern table for helper addrs. */

void FUN_0019fffc(void)

{
  unsigned long uVar1;
  unsigned long *unaff_x19;
  
  FUN_00351124();
  uVar1 = FUN_000feb10();
  *unaff_x19 = uVar1;
  return;
}


