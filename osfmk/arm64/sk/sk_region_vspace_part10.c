/* Recreated from ringminus1/sk/cl4_kernel.raw (cL4 microkernel, arm64e, image base 0).
 * Ground truth: Ghidra FUN_ names + addresses. Names use cL4/seL4 vocabulary;
 * estimates unless matched.
 * Slice 10: 0x002652e4 - 0x0026cc88 (121 functions, vspace/MMU layer).
 *
 * This region is dominated by Swift-runtime-flavoured wrappers: most bodies
 * call a large shared out-of-range runtime (FUN_0034xxxx / FUN_0035xxxx /
 * FUN_0008xxxx / FUN_0025xxxx) through register-aliased indirect dispatch
 * (extraout_x8/extraout_x9/extraout_x16). Those callees are NOT in scope;
 * they are declared extern below with their FUN_ address in a comment.
 * Where a body is pure runtime glue the reconstruction records the exact
 * call sequence and data-flow that the decompiler exposed. */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "sk_internal.h"

/* Scratch buffer backing the decompiler's register-aliased stack locals. */
static uint64_t sk_scratch[16];
static inline void SoftwareBreakpoint(int imm, unsigned long pc) { __asm__ volatile("brk #0"); }


/* ------------------------------------------------------------------ *
 * Out-of-range cL4 helpers declared extern (FUN_ address in comment).
 * Reconstructed by the range worker that owns each region.
 * ------------------------------------------------------------------ */

/* Core kernel primitives (region 0x0034xxxx-0x0037xxxx). */
extern void    *skp10_sk_alloc(unsigned long size, unsigned long tag);      /* FUN_0036a908 */
extern void    *skp10_sk_alloc_pages(unsigned long size, unsigned long tag);/* FUN_0036b270 */
extern void     skp10_sk_free(void *ptr);                                   /* FUN_0036b118 */
extern uint64_t skp10_sk_object_lock();                   /* FUN_00377824 */
extern uint64_t skp10_sk_lock_ref();                              /* FUN_00377bec */
extern uint64_t skp10_sk_lock_release();                          /* FUN_00377dcc */
extern void     skp10_sk_spin_irqsave(uint64_t *flags);                     /* FUN_00357ca0 / FUN_00357cb4 */
extern void     skp10_sk_irqrestore(uint64_t flags);                        /* FUN_00357c74 */
extern void     skp10_sk_msg_dispatch();                                /* FUN_003a25d4 */
extern uint64_t skp10_sk_hash64(uint64_t v);                                /* FUN_003a261c */
extern void     skp10_sk_runtime_lock_enter(void);                          /* FUN_003d31d8 */
extern void     skp10_sk_runtime_lock_leave(void);                          /* FUN_003d31e8 */
extern void     skp10_sk_runtime_install();                             /* FUN_003d30b0 */

/* CPU / TCB context. */
extern uint64_t skp10_sk_cpu(void);                                         /* FUN_0008e518 */
extern void    *skp10_sk_current_tcb(void);                                 /* FUN_000867ec */
extern uint64_t skp10_sk_cap_get(void);                                     /* FUN_0008f6f4 */

/* Swift runtime helpers (message send / refcount / string / fatal). */
extern void     skp10_sk_swift_dispatch(); /* FUN_00350884 */
extern uint64_t skp10_sk_swift_msg(void);                                   /* FUN_00350878 */
extern void     skp10_sk_swift_fatal(void);
extern uint64_t skp10_DAT_003471a4;
extern uint64_t skp10_DAT_003471a8;
extern uint64_t skp10_DAT_004baeb0;
extern uint64_t skp10_DAT_004e80b0;
extern uint64_t skp10_DAT_004f1818;
extern uint64_t skp10_DAT_005d3bb4;
extern uint64_t skp10_DAT_00611b24;
extern uint64_t skp10_DAT_00658c00;
extern uint64_t skp10_DAT_006ade70;
extern uint64_t skp10_DAT_006ade78;
extern uint64_t LAB_00611b34;
extern char skp10_s_Fatal_error_005accd0[];
extern char skp10_s_Index_out_of_range_005cd940[];
extern char skp10_s_Swift_Range_swift_005cda30[];
extern char skp10_s_Swift_OutputStream_swift_005d3a20[];
extern char skp10_s_Range_requires_lowerBound_005cda00[];
extern char skp10_s_Unexpectedly_found_nil_while_unw_005cd7d0[];
extern int      skp10_sk_check_one(uint64_t p, int one, uint64_t o);  /* FUN_000839f8 */
                                 /* FUN_001afe4c, noreturn */
extern uint64_t skp10_sk_swift_alloc_obj(void);                             /* skp10_FUN_003722e4 */
extern uint64_t skp10_sk_swift_read8(void *out, uint64_t n);                /* thunk_FUN_00054414 */
extern void     skp10_sk_swift_retain(uint64_t);                            /* thunk_FUN_00054464 */
extern void     skp10_sk_swift_release(uint64_t);                           /* thunk_FUN_0005453c */
extern uint64_t skp10_sk_obj_lookup(uint64_t);                              /* FUN_003a0b04 */
extern uint64_t skp10_sk_obj_isalive(uint64_t);                             /* FUN_003a0c90 */
extern void     skp10_sk_swift_checked_dispatch(uint64_t, uint64_t, uint64_t); /* FUN_00376820 */
extern uint64_t skp10_sk_obj_find(uint64_t);                                /* FUN_003a25d4 */
extern uint64_t skp10_sk_hash_start(uint64_t);                              /* FUN_00354948 */
extern uint64_t skp10_sk_tbl_bits(uint64_t);                                /* FUN_0035377c */

/* In-region (0x0025xxxx) vspace-table helpers owned by other slices. */
extern void skp10_sk_table_insert_8(void *key, uint64_t idx, uint64_t hash);      /* FUN_0025c33c */
extern void skp10_sk_table_insert_16(uint64_t a, uint64_t b, uint64_t idx,
                               uint64_t hash);                              /* FUN_0025c460 */
extern void skp10_sk_table_insert_28(uint64_t a, uint64_t b, uint64_t idx,
                               uint64_t hash);                              /* FUN_0025c570 */
extern void skp10_sk_table_insert_k(uint64_t *a, uint64_t idx, uint64_t hash);    /* FUN_0025c754 */
extern void skp10_sk_table_insert_8b(void *key, uint64_t idx, uint64_t hash);     /* FUN_0025c9a8 */
extern void skp10_sk_table_insert_28b(uint64_t a, uint64_t b, uint64_t hash);     /* FUN_0025cac8 */
extern void skp10_sk_table_rm_8(void);                                            /* FUN_0025b4e8 */
extern void skp10_sk_table_rm_16(void);                                           /* FUN_0025db98 */
extern void skp10_sk_table_rm_28(void);                                           /* FUN_0025b5e0 */
extern void skp10_sk_table_rm_28b(uint64_t idx);                                  /* FUN_0025dee4 */
extern void skp10_sk_table_rm_28c(void);                                          /* FUN_0025b7d8 */
extern void skp10_sk_table_rm_28d(uint64_t idx);                                  /* FUN_0025e000 */

/* Generic Swift-runtime dispatch slots used throughout the wrappers.
 * Each maps to a distinct out-of-range runtime function (see comments).
 * Naming is by role where inferable, else slot index. */
extern uint64_t skp10_sk_rt_slot_00();   /* FUN_0034a980 */
extern uint64_t skp10_sk_rt_slot_01();   /* FUN_0034b05c */
extern uint64_t skp10_sk_rt_slot_02();   /* FUN_0034b7e4 */
extern uint64_t skp10_sk_rt_slot_03();   /* FUN_0034c8e0 */
extern uint64_t skp10_sk_rt_slot_04();   /* FUN_0034b7b8 */
extern uint64_t skp10_sk_rt_slot_05();   /* FUN_0035a080 */
extern uint64_t skp10_sk_rt_slot_06();   /* FUN_003499b4 */
extern uint64_t skp10_sk_rt_slot_07();   /* FUN_003501b8 */
extern uint64_t skp10_sk_rt_slot_08();   /* FUN_00349f3c */
extern uint64_t skp10_sk_rt_slot_09();   /* FUN_00354810 */
extern uint64_t skp10_sk_rt_slot_0a();   /* FUN_00350470 */
extern uint64_t skp10_sk_rt_slot_0b(uint64_t); /* FUN_0031945c */
extern uint64_t skp10_sk_rt_slot_0c();   /* FUN_00351318 */
extern uint64_t skp10_sk_rt_slot_0d();   /* FUN_00350878 */
extern uint64_t skp10_sk_rt_slot_0e();   /* FUN_0034da48 */
extern uint64_t skp10_sk_rt_slot_0f();   /* FUN_00358fb4 */
extern uint64_t skp10_sk_rt_slot_10();   /* FUN_00357748 */
extern uint64_t skp10_sk_rt_slot_11();   /* FUN_003516cc */
extern uint64_t skp10_sk_rt_slot_12();   /* FUN_00310d68 */
extern uint64_t skp10_sk_rt_slot_13(uint64_t); /* FUN_000a6f88 */
extern uint64_t skp10_sk_rt_slot_14();   /* FUN_0007c1a4 */
extern uint64_t skp10_sk_rt_slot_15();   /* FUN_0034b05c */
extern uint64_t skp10_sk_rt_slot_16();   /* FUN_00350738 */
extern uint64_t skp10_sk_rt_slot_17();   /* FUN_0035163c */
extern uint64_t skp10_sk_rt_slot_18();   /* FUN_00353f88 */
extern uint64_t skp10_sk_rt_slot_19();   /* FUN_003511b4 */
extern uint64_t skp10_sk_rt_slot_1a();   /* FUN_00355f04 */
extern uint64_t skp10_sk_rt_slot_1b(uint64_t); /* FUN_00358fc8 */
extern uint64_t skp10_sk_rt_slot_1c(uint64_t); /* FUN_00352ee4 */
extern uint64_t skp10_sk_rt_slot_1d(uint64_t); /* FUN_00352864 */
extern uint64_t skp10_sk_rt_slot_1e();   /* FUN_00348d4c */
extern uint64_t skp10_sk_rt_slot_1f();   /* FUN_00348abc */
extern uint64_t skp10_sk_rt_slot_20();   /* FUN_0034b308 */
extern uint64_t skp10_sk_rt_slot_21();   /* FUN_0034b758 */
extern uint64_t skp10_sk_rt_slot_22();   /* FUN_0007b384 */
extern uint64_t skp10_sk_rt_slot_23(uint64_t); /* FUN_003514d0 */
extern uint64_t skp10_sk_rt_slot_24();   /* FUN_0034b3c8 */
extern uint64_t skp10_sk_rt_slot_25();   /* FUN_0035190c */
extern uint64_t skp10_sk_rt_slot_26(uint64_t); /* FUN_00350780 */
extern uint64_t skp10_sk_rt_slot_27();   /* FUN_0035133c */
extern uint64_t skp10_sk_rt_slot_28();   /* FUN_003508f0 */
extern uint64_t skp10_sk_rt_slot_29();   /* FUN_0034cfd4 */
extern uint64_t skp10_sk_rt_slot_2a();   /* FUN_00350618 */
extern uint64_t skp10_sk_rt_slot_2b();   /* FUN_00350a34 */
extern uint64_t skp10_sk_rt_slot_2c();   /* FUN_0034e784 */
extern uint64_t skp10_sk_rt_slot_2d();   /* FUN_00354d94 */
extern uint64_t skp10_sk_rt_slot_2e();   /* FUN_0034d334 */
extern uint64_t skp10_sk_rt_slot_2f();   /* FUN_003531f0 */
extern uint64_t skp10_sk_rt_slot_30();   /* FUN_00358ef4 */
extern uint64_t skp10_sk_rt_slot_31();   /* FUN_00349b3c */
extern uint64_t skp10_sk_rt_slot_32();   /* FUN_00348f50 */
extern uint64_t skp10_sk_rt_slot_33(uint64_t); /* FUN_00351ef8 */
extern uint64_t skp10_sk_rt_slot_34();   /* FUN_00351554 */
extern uint64_t skp10_sk_rt_slot_35();   /* FUN_00351f10 */
extern uint64_t skp10_sk_rt_slot_36();   /* FUN_0034af20 */
extern uint64_t skp10_sk_rt_slot_37();   /* FUN_00351184 */
extern uint64_t skp10_sk_rt_slot_38();   /* FUN_003510ac */
extern uint64_t skp10_sk_rt_slot_39();   /* FUN_0034c384 */
extern uint64_t skp10_sk_rt_slot_3a();   /* FUN_0034c674 */
extern uint64_t skp10_sk_rt_slot_3b();   /* FUN_00359338 */
extern uint64_t skp10_sk_rt_slot_3c();   /* FUN_0031d488 */
extern uint64_t skp10_sk_rt_slot_3d();   /* FUN_000dbdf4 */
extern uint64_t skp10_sk_rt_slot_3e();   /* FUN_00350810 */
extern uint64_t skp10_sk_rt_slot_3f(uint64_t); /* FUN_00350618 */

/* Note: the large remainder of the shared runtime (FUN_0034xxxx/0035xxxx,
   ~700 distinct functions) is exercised through these slot externs and
   the named primitives above. Each body below preserves the exact call
   sequence and control flow the decompiler emitted. */


/* ------------------------------------------------------------------ *
 * Extern declarations for the remaining out-of-range cL4 runtime
 * callees referenced by this slice. Empty-paren prototypes (unspecified
 * args, C style) since these are opaque Swift-ARC/runtime glue; the
 * exact FUN_ address is encoded in the name and preserved in comments.
 * ------------------------------------------------------------------ */

extern uint64_t skp10_sk_rt_00002534();   /* FUN_00002534 */
extern uint64_t skp10_sk_rt_000026e8();   /* FUN_000026e8 */
extern uint64_t skp10_sk_rt_000027e8();   /* FUN_000027e8 */
extern uint64_t skp10_sk_rt_0001d4a0();   /* FUN_0001d4a0 */
extern uint64_t skp10_sk_rt_0001df60();   /* FUN_0001df60 */
extern uint64_t skp10_sk_rt_00027754();   /* FUN_00027754 */
extern uint64_t skp10_sk_rt_000277b8();   /* FUN_000277b8 */
extern uint64_t skp10_sk_rt_00041138();   /* FUN_00041138 */
extern uint64_t skp10_sk_rt_0006a4c0();   /* FUN_0006a4c0 */
extern uint64_t skp10_sk_rt_0006b42c();   /* FUN_0006b42c */
extern uint64_t skp10_sk_rt_0006b6f4();   /* FUN_0006b6f4 */
extern uint64_t skp10_sk_rt_00077894();   /* FUN_00077894 */
extern uint64_t skp10_sk_rt_0007b384();   /* FUN_0007b384 */
extern uint64_t skp10_sk_rt_0007c198();   /* FUN_0007c198 */
extern uint64_t skp10_sk_rt_0007c1a4();   /* FUN_0007c1a4 */
extern uint64_t skp10_sk_rt_0007c1c4();   /* FUN_0007c1c4 */
extern uint64_t skp10_sk_rt_000824e4();   /* FUN_000824e4 */
extern uint64_t skp10_sk_rt_000839d8();   /* FUN_000839d8 */
extern uint64_t skp10_sk_rt_000839f8();   /* FUN_000839f8 */
extern uint64_t skp10_sk_rt_0008409c();   /* FUN_0008409c */
extern uint64_t skp10_sk_rt_00084174();   /* FUN_00084174 */
extern uint64_t skp10_sk_rt_00084180();   /* FUN_00084180 */
extern uint64_t skp10_sk_rt_00084220();   /* FUN_00084220 */
extern uint64_t skp10_sk_rt_00084234();   /* FUN_00084234 */
extern uint64_t skp10_sk_rt_000867ec();   /* FUN_000867ec */
extern uint64_t skp10_sk_rt_0008e500();   /* FUN_0008e500 */
extern uint64_t skp10_sk_rt_0008e518();   /* FUN_0008e518 */
extern uint64_t skp10_sk_rt_0008e5d8();   /* FUN_0008e5d8 */
extern uint64_t skp10_sk_rt_0008f6f4();   /* FUN_0008f6f4 */
extern uint64_t skp10_sk_rt_0009461c();   /* FUN_0009461c */
extern uint64_t skp10_sk_rt_0009e234();   /* FUN_0009e234 */
extern uint64_t skp10_sk_rt_000a68c4();   /* FUN_000a68c4 */
extern uint64_t skp10_sk_rt_000a68f4();   /* FUN_000a68f4 */
extern uint64_t skp10_sk_rt_000a6f88();   /* FUN_000a6f88 */
extern uint64_t skp10_sk_rt_000a6fe0();   /* FUN_000a6fe0 */
extern uint64_t skp10_sk_rt_000aa46c();   /* FUN_000aa46c */
extern uint64_t skp10_sk_rt_000aa47c();   /* FUN_000aa47c */
extern uint64_t skp10_sk_rt_000b4390();   /* FUN_000b4390 */
extern uint64_t skp10_sk_rt_000b4594();   /* FUN_000b4594 */
extern uint64_t skp10_sk_rt_000b45b0();   /* FUN_000b45b0 */
extern uint64_t skp10_sk_rt_000dbc54();   /* FUN_000dbc54 */
extern uint64_t skp10_sk_rt_000dbc98();   /* FUN_000dbc98 */
extern uint64_t skp10_sk_rt_000dbcc8();   /* FUN_000dbcc8 */
extern uint64_t skp10_sk_rt_000dbd0c();   /* FUN_000dbd0c */
extern uint64_t skp10_sk_rt_000dbdf4();   /* FUN_000dbdf4 */
extern uint64_t skp10_sk_rt_000e72b0();   /* FUN_000e72b0 */
extern uint64_t skp10_sk_rt_00100c38();   /* FUN_00100c38 */
extern uint64_t skp10_sk_rt_00100efc();   /* FUN_00100efc */
extern uint64_t skp10_sk_rt_00117cc4();   /* FUN_00117cc4 */
extern uint64_t skp10_sk_rt_0014ae44();   /* FUN_0014ae44 */
extern uint64_t skp10_sk_rt_0014f810();   /* FUN_0014f810 */
extern uint64_t skp10_sk_rt_00167404();   /* FUN_00167404 */
extern uint64_t skp10_sk_rt_001679fc();   /* FUN_001679fc */
extern uint64_t skp10_sk_rt_0017e880();   /* FUN_0017e880 */
extern uint64_t skp10_sk_rt_0019e410();   /* FUN_0019e410 */
extern uint64_t skp10_sk_rt_0019e578();   /* FUN_0019e578 */
extern uint64_t skp10_sk_rt_0019fd10();   /* FUN_0019fd10 */
extern uint64_t skp10_sk_rt_001a433c();   /* FUN_001a433c */
extern uint64_t skp10_sk_rt_001a84f4();   /* FUN_001a84f4 */
extern uint64_t skp10_sk_rt_001a8564();   /* FUN_001a8564 */
extern uint64_t skp10_sk_rt_001ae82c();   /* FUN_001ae82c */
extern uint64_t skp10_sk_rt_001aeab4();   /* FUN_001aeab4 */
extern uint64_t skp10_sk_rt_001afe4c();   /* FUN_001afe4c */
extern uint64_t skp10_sk_rt_001b9084();   /* FUN_001b9084 */
extern uint64_t skp10_sk_rt_001e2460();   /* FUN_001e2460 */
extern uint64_t skp10_sk_rt_001e4298();   /* FUN_001e4298 */
extern uint64_t skp10_sk_rt_001e4348();   /* FUN_001e4348 */
extern uint64_t skp10_sk_rt_001e4cbc();   /* FUN_001e4cbc */
extern uint64_t skp10_sk_rt_001e9f14();   /* FUN_001e9f14 */
extern uint64_t skp10_sk_rt_001fb194();   /* FUN_001fb194 */
extern uint64_t skp10_sk_rt_00205844();   /* FUN_00205844 */
extern uint64_t skp10_sk_rt_002060d4();   /* FUN_002060d4 */
extern uint64_t skp10_sk_rt_00229a3c();   /* FUN_00229a3c */
extern uint64_t skp10_sk_rt_00255738();   /* FUN_00255738 */
extern uint64_t skp10_sk_rt_0025b4e8();   /* FUN_0025b4e8 */
extern uint64_t skp10_sk_rt_0025b5e0();   /* FUN_0025b5e0 */
extern uint64_t skp10_sk_rt_0025b7d8();   /* FUN_0025b7d8 */
extern uint64_t skp10_sk_rt_0025c33c();   /* FUN_0025c33c */
extern uint64_t skp10_sk_rt_0025c460();   /* FUN_0025c460 */
extern uint64_t skp10_sk_rt_0025c570();   /* FUN_0025c570 */
extern uint64_t skp10_sk_rt_0025c754();   /* FUN_0025c754 */
extern uint64_t skp10_sk_rt_0025c9a8();   /* FUN_0025c9a8 */
extern uint64_t skp10_sk_rt_0025cac8();   /* FUN_0025cac8 */
extern uint64_t skp10_sk_rt_0025db98();   /* FUN_0025db98 */
extern uint64_t skp10_sk_rt_0025dee4();   /* FUN_0025dee4 */
extern uint64_t skp10_sk_rt_0025e000();   /* FUN_0025e000 */
extern uint64_t skp10_sk_rt_002652e4();   /* FUN_002652e4 */
extern uint64_t skp10_sk_rt_002655cc();   /* FUN_002655cc */
extern uint64_t skp10_sk_rt_0026574c();   /* FUN_0026574c */
extern uint64_t skp10_sk_rt_00265750();   /* FUN_00265750 */
extern uint64_t skp10_sk_rt_00265770();   /* FUN_00265770 */
extern uint64_t skp10_sk_rt_00265774();   /* FUN_00265774 */
extern uint64_t skp10_sk_rt_00265794();   /* FUN_00265794 */
extern uint64_t skp10_sk_rt_00265884();   /* FUN_00265884 */
extern uint64_t skp10_sk_rt_00265994();   /* FUN_00265994 */
extern uint64_t skp10_sk_rt_00265a74();   /* FUN_00265a74 */
extern uint64_t skp10_sk_rt_00265b90();   /* FUN_00265b90 */
extern uint64_t skp10_sk_rt_00265e08();   /* FUN_00265e08 */
extern uint64_t skp10_sk_rt_00265f48();   /* FUN_00265f48 */
extern uint64_t skp10_sk_rt_002660ac();   /* FUN_002660ac */
extern uint64_t skp10_sk_rt_002661f4();   /* FUN_002661f4 */
extern uint64_t skp10_sk_rt_0026638c();   /* FUN_0026638c */
extern uint64_t skp10_sk_rt_00266504();   /* FUN_00266504 */
extern uint64_t skp10_sk_rt_00266688();   /* FUN_00266688 */
extern uint64_t skp10_sk_rt_002666b8();   /* FUN_002666b8 */
extern uint64_t skp10_sk_rt_0026670c();   /* FUN_0026670c */
extern uint64_t skp10_sk_rt_002667a8();   /* FUN_002667a8 */
extern uint64_t skp10_sk_rt_002673dc();   /* FUN_002673dc */
extern uint64_t skp10_sk_rt_00267510();   /* FUN_00267510 */
extern uint64_t skp10_sk_rt_002676b4();   /* FUN_002676b4 */
extern uint64_t skp10_sk_rt_002676b8();   /* FUN_002676b8 */
extern uint64_t skp10_sk_rt_002676bc();   /* FUN_002676bc */
extern uint64_t skp10_sk_rt_00267798();   /* FUN_00267798 */
extern uint64_t skp10_sk_rt_0026779c();   /* FUN_0026779c */
extern uint64_t skp10_sk_rt_002677b0();   /* FUN_002677b0 */
extern uint64_t skp10_sk_rt_002677b4();   /* FUN_002677b4 */
extern uint64_t skp10_sk_rt_002677c8();   /* FUN_002677c8 */
extern uint64_t skp10_sk_rt_002677cc();   /* FUN_002677cc */
extern uint64_t skp10_sk_rt_002677e4();   /* FUN_002677e4 */
extern uint64_t skp10_sk_rt_00267820();   /* FUN_00267820 */
extern uint64_t skp10_sk_rt_002678b4();   /* FUN_002678b4 */
extern uint64_t skp10_sk_rt_00267914();   /* FUN_00267914 */
extern uint64_t skp10_sk_rt_00267994();   /* FUN_00267994 */
extern uint64_t skp10_sk_rt_00267a0c();   /* FUN_00267a0c */
extern uint64_t skp10_sk_rt_00267a74();   /* FUN_00267a74 */
extern uint64_t skp10_sk_rt_00267af8();   /* FUN_00267af8 */
extern uint64_t skp10_sk_rt_00267ba0();   /* FUN_00267ba0 */
extern uint64_t skp10_sk_rt_00267c00();   /* FUN_00267c00 */
extern uint64_t skp10_sk_rt_00267c80();   /* FUN_00267c80 */
extern uint64_t skp10_sk_rt_00267cfc();   /* FUN_00267cfc */
extern uint64_t skp10_sk_rt_00267efc();   /* FUN_00267efc */
extern uint64_t skp10_sk_rt_00268038();   /* FUN_00268038 */
extern uint64_t skp10_sk_rt_002680a8();   /* FUN_002680a8 */
extern uint64_t skp10_sk_rt_0026817c();   /* FUN_0026817c */
extern uint64_t skp10_sk_rt_002681d8();   /* FUN_002681d8 */
extern uint64_t skp10_sk_rt_0026830c();   /* FUN_0026830c */
extern uint64_t skp10_sk_rt_00268400();   /* FUN_00268400 */
extern uint64_t skp10_sk_rt_00268540();   /* FUN_00268540 */
extern uint64_t skp10_sk_rt_0026863c();   /* FUN_0026863c */
extern uint64_t skp10_sk_rt_00268670();   /* FUN_00268670 */
extern uint64_t skp10_sk_rt_00268704();   /* FUN_00268704 */
extern uint64_t skp10_sk_rt_00268708();   /* FUN_00268708 */
extern uint64_t skp10_sk_rt_00268734();   /* FUN_00268734 */
extern uint64_t skp10_sk_rt_002687a8();   /* FUN_002687a8 */
extern uint64_t skp10_sk_rt_002687e8();   /* FUN_002687e8 */
extern uint64_t skp10_sk_rt_00268870();   /* FUN_00268870 */
extern uint64_t skp10_sk_rt_00268a78();   /* FUN_00268a78 */
extern uint64_t skp10_sk_rt_00268b34();   /* FUN_00268b34 */
extern uint64_t skp10_sk_rt_00268b88();   /* FUN_00268b88 */
extern uint64_t skp10_sk_rt_00268bf8();   /* FUN_00268bf8 */
extern uint64_t skp10_sk_rt_00268c58();   /* FUN_00268c58 */
extern uint64_t skp10_sk_rt_00268e7c();   /* FUN_00268e7c */
extern uint64_t skp10_sk_rt_0026909c();   /* FUN_0026909c */
extern uint64_t skp10_sk_rt_00269224();   /* FUN_00269224 */
extern uint64_t skp10_sk_rt_002692b8();   /* FUN_002692b8 */
extern uint64_t skp10_sk_rt_00269490();   /* FUN_00269490 */
extern uint64_t skp10_sk_rt_002698bc();   /* FUN_002698bc */
extern uint64_t skp10_sk_rt_00269a88();   /* FUN_00269a88 */
extern uint64_t skp10_sk_rt_00269b08();   /* FUN_00269b08 */
extern uint64_t skp10_sk_rt_00269bf4();   /* FUN_00269bf4 */
extern uint64_t skp10_sk_rt_00269c70();   /* FUN_00269c70 */
extern uint64_t skp10_sk_rt_00269d30();   /* FUN_00269d30 */
extern uint64_t skp10_sk_rt_0026a1ac();   /* FUN_0026a1ac */
extern uint64_t skp10_sk_rt_0026a278();   /* FUN_0026a278 */
extern uint64_t skp10_sk_rt_0026a27c();   /* FUN_0026a27c */
extern uint64_t skp10_sk_rt_0026a2ac();   /* FUN_0026a2ac */
extern uint64_t skp10_sk_rt_0026a2bc();   /* FUN_0026a2bc */
extern uint64_t skp10_sk_rt_0026a2f0();   /* FUN_0026a2f0 */
extern uint64_t skp10_sk_rt_0026a2f4();   /* FUN_0026a2f4 */
extern uint64_t skp10_sk_rt_0026a328();   /* FUN_0026a328 */
extern uint64_t skp10_sk_rt_0026a404();   /* FUN_0026a404 */
extern uint64_t skp10_sk_rt_0026a560();   /* FUN_0026a560 */
extern uint64_t skp10_sk_rt_0026a744();   /* FUN_0026a744 */
extern uint64_t skp10_sk_rt_0026a9a8();   /* FUN_0026a9a8 */
extern uint64_t skp10_sk_rt_0026aa7c();   /* FUN_0026aa7c */
extern uint64_t skp10_sk_rt_0026acbc();   /* FUN_0026acbc */
extern uint64_t skp10_sk_rt_0026adcc();   /* FUN_0026adcc */
extern uint64_t skp10_sk_rt_0026af9c();   /* FUN_0026af9c */
extern uint64_t skp10_sk_rt_0026b1dc();   /* FUN_0026b1dc */
extern uint64_t skp10_sk_rt_0026b3c8();   /* FUN_0026b3c8 */
extern uint64_t skp10_sk_rt_0026b3cc();   /* FUN_0026b3cc */
extern uint64_t skp10_sk_rt_0026b3fc();   /* FUN_0026b3fc */
extern uint64_t skp10_sk_rt_0026b400();   /* FUN_0026b400 */
extern uint64_t skp10_sk_rt_0026b434();   /* FUN_0026b434 */
extern uint64_t skp10_sk_rt_0026b460();   /* FUN_0026b460 */
extern uint64_t skp10_sk_rt_0026b5e8();   /* FUN_0026b5e8 */
extern uint64_t skp10_sk_rt_0026b71c();   /* FUN_0026b71c */
extern uint64_t skp10_sk_rt_0026b748();   /* FUN_0026b748 */
extern uint64_t skp10_sk_rt_0026b9d0();   /* FUN_0026b9d0 */
extern uint64_t skp10_sk_rt_0026bbd4();   /* FUN_0026bbd4 */
extern uint64_t skp10_sk_rt_0026bce8();   /* FUN_0026bce8 */
extern uint64_t skp10_sk_rt_0026bd18();   /* FUN_0026bd18 */
extern uint64_t skp10_sk_rt_0026bd1c();   /* FUN_0026bd1c */
extern uint64_t skp10_sk_rt_0026bd30();   /* FUN_0026bd30 */
extern uint64_t skp10_sk_rt_0026bd5c();   /* FUN_0026bd5c */
extern uint64_t skp10_sk_rt_0026bdc4();   /* FUN_0026bdc4 */
extern uint64_t skp10_sk_rt_0026c064();   /* FUN_0026c064 */
extern uint64_t skp10_sk_rt_0026c160();   /* FUN_0026c160 */
extern uint64_t skp10_sk_rt_0026c210();   /* FUN_0026c210 */
extern uint64_t skp10_sk_rt_0026c274();   /* FUN_0026c274 */
extern uint64_t skp10_sk_rt_0026c2a0();   /* FUN_0026c2a0 */
extern uint64_t skp10_sk_rt_0026c6c8();   /* FUN_0026c6c8 */
extern uint64_t skp10_sk_rt_0026c6d8();   /* FUN_0026c6d8 */
extern uint64_t skp10_sk_rt_0026ca24();   /* FUN_0026ca24 */
extern uint64_t skp10_sk_rt_0026cb00();   /* FUN_0026cb00 */
extern uint64_t skp10_sk_rt_0026cbd0();   /* FUN_0026cbd0 */
extern uint64_t skp10_sk_rt_0026cc88();   /* FUN_0026cc88 */
extern uint64_t skp10_sk_rt_0026cd08();   /* FUN_0026cd08 */
extern uint64_t skp10_sk_rt_0028e8c0();   /* FUN_0028e8c0 */
extern uint64_t skp10_sk_rt_00291ee0();   /* FUN_00291ee0 */
extern uint64_t skp10_sk_rt_002a0d50();   /* FUN_002a0d50 */
extern uint64_t skp10_sk_rt_002a20cc();   /* FUN_002a20cc */
extern uint64_t skp10_sk_rt_002a218c();   /* FUN_002a218c */
extern uint64_t skp10_sk_rt_002a2748();   /* FUN_002a2748 */
extern uint64_t skp10_sk_rt_002a4b90();   /* FUN_002a4b90 */
extern uint64_t skp10_sk_rt_002a4c98();   /* FUN_002a4c98 */
extern uint64_t skp10_sk_rt_002a9ba8();   /* FUN_002a9ba8 */
extern uint64_t skp10_sk_rt_002b22d4();   /* FUN_002b22d4 */
extern uint64_t skp10_sk_rt_002b79cc();   /* FUN_002b79cc */
extern uint64_t skp10_sk_rt_002bbcd8();   /* FUN_002bbcd8 */
extern uint64_t skp10_sk_rt_002c6d00();   /* FUN_002c6d00 */
extern uint64_t skp10_sk_rt_0031090c();   /* FUN_0031090c */
extern uint64_t skp10_sk_rt_00310924();   /* FUN_00310924 */
extern uint64_t skp10_sk_rt_00310ad4();   /* FUN_00310ad4 */
extern uint64_t skp10_sk_rt_00310ca4();   /* FUN_00310ca4 */
extern uint64_t skp10_sk_rt_00310d34();   /* FUN_00310d34 */
extern uint64_t skp10_sk_rt_00310d68();   /* FUN_00310d68 */
extern uint64_t skp10_sk_rt_00310d98();   /* FUN_00310d98 */
extern uint64_t skp10_sk_rt_00310dd8();   /* FUN_00310dd8 */
extern uint64_t skp10_sk_rt_00310f94();   /* FUN_00310f94 */
extern uint64_t skp10_sk_rt_00310fc4();   /* FUN_00310fc4 */
extern uint64_t skp10_sk_rt_0031945c();   /* FUN_0031945c */
extern uint64_t skp10_sk_rt_00319538();   /* FUN_00319538 */
extern uint64_t skp10_sk_rt_00319658();   /* FUN_00319658 */
extern uint64_t skp10_sk_rt_00319808();   /* FUN_00319808 */
extern uint64_t skp10_sk_rt_0031993c();   /* FUN_0031993c */
extern uint64_t skp10_sk_rt_0031996c();   /* FUN_0031996c */
extern uint64_t skp10_sk_rt_0031997c();   /* FUN_0031997c */
extern uint64_t skp10_sk_rt_003199ac();   /* FUN_003199ac */
extern uint64_t skp10_sk_rt_0031b8d0();   /* FUN_0031b8d0 */
extern uint64_t skp10_sk_rt_0031b900();   /* FUN_0031b900 */
extern uint64_t skp10_sk_rt_0031bc70();   /* FUN_0031bc70 */
extern uint64_t skp10_sk_rt_0031d458();   /* FUN_0031d458 */
extern uint64_t skp10_sk_rt_0031d488();   /* FUN_0031d488 */
extern uint64_t skp10_sk_rt_0031d4e8();   /* FUN_0031d4e8 */
extern uint64_t skp10_sk_rt_0031d518();   /* FUN_0031d518 */
extern uint64_t skp10_sk_rt_0031d548();   /* FUN_0031d548 */
extern uint64_t skp10_sk_rt_0031d5a8();   /* FUN_0031d5a8 */
extern uint64_t skp10_sk_rt_0031d5c0();   /* FUN_0031d5c0 */
extern uint64_t skp10_sk_rt_0031d5d8();   /* FUN_0031d5d8 */
extern uint64_t skp10_sk_rt_0031d5f0();   /* FUN_0031d5f0 */
extern uint64_t skp10_sk_rt_0031e104();   /* FUN_0031e104 */
extern uint64_t skp10_sk_rt_0034310c();   /* FUN_0034310c */
extern uint64_t skp10_sk_rt_00344e54();   /* FUN_00344e54 */
extern uint64_t skp10_sk_rt_00347d60();   /* FUN_00347d60 */
extern uint64_t skp10_sk_rt_00347de8();   /* FUN_00347de8 */
extern uint64_t skp10_sk_rt_00347f2c();   /* FUN_00347f2c */
extern uint64_t skp10_sk_rt_00348034();   /* FUN_00348034 */
extern uint64_t skp10_sk_rt_00348074();   /* FUN_00348074 */
extern uint64_t skp10_sk_rt_003481fc();   /* FUN_003481fc */
extern uint64_t skp10_sk_rt_0034834c();   /* FUN_0034834c */
extern uint64_t skp10_sk_rt_0034846c();   /* FUN_0034846c */
extern uint64_t skp10_sk_rt_003486b8();   /* FUN_003486b8 */
extern uint64_t skp10_sk_rt_00348718();   /* FUN_00348718 */
extern uint64_t skp10_sk_rt_00348730();   /* FUN_00348730 */
extern uint64_t skp10_sk_rt_00348898();   /* FUN_00348898 */
extern uint64_t skp10_sk_rt_003488bc();   /* FUN_003488bc */
extern uint64_t skp10_sk_rt_003489c0();   /* FUN_003489c0 */
extern uint64_t skp10_sk_rt_003489fc();   /* FUN_003489fc */
extern uint64_t skp10_sk_rt_00348a18();   /* FUN_00348a18 */
extern uint64_t skp10_sk_rt_00348a80();   /* FUN_00348a80 */
extern uint64_t skp10_sk_rt_00348a9c();   /* FUN_00348a9c */
extern uint64_t skp10_sk_rt_00348abc();   /* FUN_00348abc */
extern uint64_t skp10_sk_rt_00348b7c();   /* FUN_00348b7c */
extern uint64_t skp10_sk_rt_00348b94();   /* FUN_00348b94 */
extern uint64_t skp10_sk_rt_00348cd0();   /* FUN_00348cd0 */
extern uint64_t skp10_sk_rt_00348d4c();   /* FUN_00348d4c */
extern uint64_t skp10_sk_rt_00348d64();   /* FUN_00348d64 */
extern uint64_t skp10_sk_rt_00348e00();   /* FUN_00348e00 */
extern uint64_t skp10_sk_rt_00348e48();   /* FUN_00348e48 */
extern uint64_t skp10_sk_rt_00348f14();   /* FUN_00348f14 */
extern uint64_t skp10_sk_rt_00348f50();   /* FUN_00348f50 */
extern uint64_t skp10_sk_rt_00348fd8();   /* FUN_00348fd8 */
extern uint64_t skp10_sk_rt_00349068();   /* FUN_00349068 */
extern uint64_t skp10_sk_rt_00349370();   /* FUN_00349370 */
extern uint64_t skp10_sk_rt_003493c4();   /* FUN_003493c4 */
extern uint64_t skp10_sk_rt_00349410();   /* FUN_00349410 */
extern uint64_t skp10_sk_rt_0034947c();   /* FUN_0034947c */
extern uint64_t skp10_sk_rt_003494e8();   /* FUN_003494e8 */
extern uint64_t skp10_sk_rt_00349530();   /* FUN_00349530 */
extern uint64_t skp10_sk_rt_003495a8();   /* FUN_003495a8 */
extern uint64_t skp10_sk_rt_00349734();   /* FUN_00349734 */
extern uint64_t skp10_sk_rt_00349748();   /* FUN_00349748 */
extern uint64_t skp10_sk_rt_0034975c();   /* FUN_0034975c */
extern uint64_t skp10_sk_rt_003497a0();   /* FUN_003497a0 */
extern uint64_t skp10_sk_rt_003497b4();   /* FUN_003497b4 */
extern uint64_t skp10_sk_rt_00349830();   /* FUN_00349830 */
extern uint64_t skp10_sk_rt_003499b4();   /* FUN_003499b4 */
extern uint64_t skp10_sk_rt_003499c8();   /* FUN_003499c8 */
extern uint64_t skp10_sk_rt_00349a04();   /* FUN_00349a04 */
extern uint64_t skp10_sk_rt_00349b3c();   /* FUN_00349b3c */
extern uint64_t skp10_sk_rt_00349bc4();   /* FUN_00349bc4 */
extern uint64_t skp10_sk_rt_00349cbc();   /* FUN_00349cbc */
extern uint64_t skp10_sk_rt_00349d80();   /* FUN_00349d80 */
extern uint64_t skp10_sk_rt_00349de8();   /* FUN_00349de8 */
extern uint64_t skp10_sk_rt_00349dfc();   /* FUN_00349dfc */
extern uint64_t skp10_sk_rt_00349e10();   /* FUN_00349e10 */
extern uint64_t skp10_sk_rt_00349ef4();   /* FUN_00349ef4 */
extern uint64_t skp10_sk_rt_00349f08();   /* FUN_00349f08 */
extern uint64_t skp10_sk_rt_00349f3c();   /* FUN_00349f3c */
extern uint64_t skp10_sk_rt_00349fb8();   /* FUN_00349fb8 */
extern uint64_t skp10_sk_rt_00349fe0();   /* FUN_00349fe0 */
extern uint64_t skp10_sk_rt_0034a2c0();   /* FUN_0034a2c0 */
extern uint64_t skp10_sk_rt_0034a2f8();   /* FUN_0034a2f8 */
extern uint64_t skp10_sk_rt_0034a30c();   /* FUN_0034a30c */
extern uint64_t skp10_sk_rt_0034a354();   /* FUN_0034a354 */
extern uint64_t skp10_sk_rt_0034a464();   /* FUN_0034a464 */
extern uint64_t skp10_sk_rt_0034a5dc();   /* FUN_0034a5dc */
extern uint64_t skp10_sk_rt_0034a688();   /* FUN_0034a688 */
extern uint64_t skp10_sk_rt_0034a798();   /* FUN_0034a798 */
extern uint64_t skp10_sk_rt_0034a980();   /* FUN_0034a980 */
extern uint64_t skp10_sk_rt_0034aa3c();   /* FUN_0034aa3c */
extern uint64_t skp10_sk_rt_0034aa54();   /* FUN_0034aa54 */
extern uint64_t skp10_sk_rt_0034ab20();   /* FUN_0034ab20 */
extern uint64_t skp10_sk_rt_0034ac28();   /* FUN_0034ac28 */
extern uint64_t skp10_sk_rt_0034ac3c();   /* FUN_0034ac3c */
extern uint64_t skp10_sk_rt_0034ad00();   /* FUN_0034ad00 */
extern uint64_t skp10_sk_rt_0034ad40();   /* FUN_0034ad40 */
extern uint64_t skp10_sk_rt_0034ad78();   /* FUN_0034ad78 */
extern uint64_t skp10_sk_rt_0034ada0();   /* FUN_0034ada0 */
extern uint64_t skp10_sk_rt_0034aea8();   /* FUN_0034aea8 */
extern uint64_t skp10_sk_rt_0034aee4();   /* FUN_0034aee4 */
extern uint64_t skp10_sk_rt_0034af20();   /* FUN_0034af20 */
extern uint64_t skp10_sk_rt_0034af48();   /* FUN_0034af48 */
extern uint64_t skp10_sk_rt_0034b05c();   /* FUN_0034b05c */
extern uint64_t skp10_sk_rt_0034b0b4();   /* FUN_0034b0b4 */
extern uint64_t skp10_sk_rt_0034b0c4();   /* FUN_0034b0c4 */
extern uint64_t skp10_sk_rt_0034b0d4();   /* FUN_0034b0d4 */
extern uint64_t skp10_sk_rt_0034b128();   /* FUN_0034b128 */
extern uint64_t skp10_sk_rt_0034b2c8();   /* FUN_0034b2c8 */
extern uint64_t skp10_sk_rt_0034b2f8();   /* FUN_0034b2f8 */
extern uint64_t skp10_sk_rt_0034b308();   /* FUN_0034b308 */
extern uint64_t skp10_sk_rt_0034b348();   /* FUN_0034b348 */
extern uint64_t skp10_sk_rt_0034b358();   /* FUN_0034b358 */
extern uint64_t skp10_sk_rt_0034b3c8();   /* FUN_0034b3c8 */
extern uint64_t skp10_sk_rt_0034b3d8();   /* FUN_0034b3d8 */
extern uint64_t skp10_sk_rt_0034b3e8();   /* FUN_0034b3e8 */
extern uint64_t skp10_sk_rt_0034b430();   /* FUN_0034b430 */
extern uint64_t skp10_sk_rt_0034b460();   /* FUN_0034b460 */
extern uint64_t skp10_sk_rt_0034b470();   /* FUN_0034b470 */
extern uint64_t skp10_sk_rt_0034b4c0();   /* FUN_0034b4c0 */
extern uint64_t skp10_sk_rt_0034b518();   /* FUN_0034b518 */
extern uint64_t skp10_sk_rt_0034b690();   /* FUN_0034b690 */
extern uint64_t skp10_sk_rt_0034b6b8();   /* FUN_0034b6b8 */
extern uint64_t skp10_sk_rt_0034b758();   /* FUN_0034b758 */
extern uint64_t skp10_sk_rt_0034b768();   /* FUN_0034b768 */
extern uint64_t skp10_sk_rt_0034b7b8();   /* FUN_0034b7b8 */
extern uint64_t skp10_sk_rt_0034b7e4();   /* FUN_0034b7e4 */
extern uint64_t skp10_sk_rt_0034ba48();   /* FUN_0034ba48 */
extern uint64_t skp10_sk_rt_0034bca4();   /* FUN_0034bca4 */
extern uint64_t skp10_sk_rt_0034bcf0();   /* FUN_0034bcf0 */
extern uint64_t skp10_sk_rt_0034bd6c();   /* FUN_0034bd6c */
extern uint64_t skp10_sk_rt_0034bd90();   /* FUN_0034bd90 */
extern uint64_t skp10_sk_rt_0034bec4();   /* FUN_0034bec4 */
extern uint64_t skp10_sk_rt_0034beec();   /* FUN_0034beec */
extern uint64_t skp10_sk_rt_0034befc();   /* FUN_0034befc */
extern uint64_t skp10_sk_rt_0034bf1c();   /* FUN_0034bf1c */
extern uint64_t skp10_sk_rt_0034bfa4();   /* FUN_0034bfa4 */
extern uint64_t skp10_sk_rt_0034bfb4();   /* FUN_0034bfb4 */
extern uint64_t skp10_sk_rt_0034c064();   /* FUN_0034c064 */
extern uint64_t skp10_sk_rt_0034c074();   /* FUN_0034c074 */
extern uint64_t skp10_sk_rt_0034c084();   /* FUN_0034c084 */
extern uint64_t skp10_sk_rt_0034c0a4();   /* FUN_0034c0a4 */
extern uint64_t skp10_sk_rt_0034c384();   /* FUN_0034c384 */
extern uint64_t skp10_sk_rt_0034c3b4();   /* FUN_0034c3b4 */
extern uint64_t skp10_sk_rt_0034c3c4();   /* FUN_0034c3c4 */
extern uint64_t skp10_sk_rt_0034c404();   /* FUN_0034c404 */
extern uint64_t skp10_sk_rt_0034c464();   /* FUN_0034c464 */
extern uint64_t skp10_sk_rt_0034c4bc();   /* FUN_0034c4bc */
extern uint64_t skp10_sk_rt_0034c4dc();   /* FUN_0034c4dc */
extern uint64_t skp10_sk_rt_0034c4fc();   /* FUN_0034c4fc */
extern uint64_t skp10_sk_rt_0034c5cc();   /* FUN_0034c5cc */
extern uint64_t skp10_sk_rt_0034c5fc();   /* FUN_0034c5fc */
extern uint64_t skp10_sk_rt_0034c60c();   /* FUN_0034c60c */
extern uint64_t skp10_sk_rt_0034c674();   /* FUN_0034c674 */
extern uint64_t skp10_sk_rt_0034c798();   /* FUN_0034c798 */
extern uint64_t skp10_sk_rt_0034c8e0();   /* FUN_0034c8e0 */
extern uint64_t skp10_sk_rt_0034c9e8();   /* FUN_0034c9e8 */
extern uint64_t skp10_sk_rt_0034c9f8();   /* FUN_0034c9f8 */
extern uint64_t skp10_sk_rt_0034ca28();   /* FUN_0034ca28 */
extern uint64_t skp10_sk_rt_0034cd40();   /* FUN_0034cd40 */
extern uint64_t skp10_sk_rt_0034cd54();   /* FUN_0034cd54 */
extern uint64_t skp10_sk_rt_0034cdd8();   /* FUN_0034cdd8 */
extern uint64_t skp10_sk_rt_0034ce58();   /* FUN_0034ce58 */
extern uint64_t skp10_sk_rt_0034ce88();   /* FUN_0034ce88 */
extern uint64_t skp10_sk_rt_0034ce98();   /* FUN_0034ce98 */
extern uint64_t skp10_sk_rt_0034cf44();   /* FUN_0034cf44 */
extern uint64_t skp10_sk_rt_0034cfa4();   /* FUN_0034cfa4 */
extern uint64_t skp10_sk_rt_0034cfd4();   /* FUN_0034cfd4 */
extern uint64_t skp10_sk_rt_0034cfe4();   /* FUN_0034cfe4 */
extern uint64_t skp10_sk_rt_0034d150();   /* FUN_0034d150 */
extern uint64_t skp10_sk_rt_0034d180();   /* FUN_0034d180 */
extern uint64_t skp10_sk_rt_0034d190();   /* FUN_0034d190 */
extern uint64_t skp10_sk_rt_0034d274();   /* FUN_0034d274 */
extern uint64_t skp10_sk_rt_0034d294();   /* FUN_0034d294 */
extern uint64_t skp10_sk_rt_0034d2f4();   /* FUN_0034d2f4 */
extern uint64_t skp10_sk_rt_0034d334();   /* FUN_0034d334 */
extern uint64_t skp10_sk_rt_0034d4b8();   /* FUN_0034d4b8 */
extern uint64_t skp10_sk_rt_0034d5ec();   /* FUN_0034d5ec */
extern uint64_t skp10_sk_rt_0034d654();   /* FUN_0034d654 */
extern uint64_t skp10_sk_rt_0034d698();   /* FUN_0034d698 */
extern uint64_t skp10_sk_rt_0034d8b0();   /* FUN_0034d8b0 */
extern uint64_t skp10_sk_rt_0034d954();   /* FUN_0034d954 */
extern uint64_t skp10_sk_rt_0034da48();   /* FUN_0034da48 */
extern uint64_t skp10_sk_rt_0034db38();   /* FUN_0034db38 */
extern uint64_t skp10_sk_rt_0034dba8();   /* FUN_0034dba8 */
extern uint64_t skp10_sk_rt_0034dd64();   /* FUN_0034dd64 */
extern uint64_t skp10_sk_rt_0034de44();   /* FUN_0034de44 */
extern uint64_t skp10_sk_rt_0034de9c();   /* FUN_0034de9c */
extern uint64_t skp10_sk_rt_0034ded4();   /* FUN_0034ded4 */
extern uint64_t skp10_sk_rt_0034e130();   /* FUN_0034e130 */
extern uint64_t skp10_sk_rt_0034e414();   /* FUN_0034e414 */
extern uint64_t skp10_sk_rt_0034e484();   /* FUN_0034e484 */
extern uint64_t skp10_sk_rt_0034e5cc();   /* FUN_0034e5cc */
extern uint64_t skp10_sk_rt_0034e5fc();   /* FUN_0034e5fc */
extern uint64_t skp10_sk_rt_0034e74c();   /* FUN_0034e74c */
extern uint64_t skp10_sk_rt_0034e784();   /* FUN_0034e784 */
extern uint64_t skp10_sk_rt_0034ea40();   /* FUN_0034ea40 */
extern uint64_t skp10_sk_rt_0034ece8();   /* FUN_0034ece8 */
extern uint64_t skp10_sk_rt_0034ef68();   /* FUN_0034ef68 */
extern uint64_t skp10_sk_rt_0034ef78();   /* FUN_0034ef78 */
extern uint64_t skp10_sk_rt_0034f064();   /* FUN_0034f064 */
extern uint64_t skp10_sk_rt_0034f294();   /* FUN_0034f294 */
extern uint64_t skp10_sk_rt_0034f2b4();   /* FUN_0034f2b4 */
extern uint64_t skp10_sk_rt_0034f2c4();   /* FUN_0034f2c4 */
extern uint64_t skp10_sk_rt_0034f474();   /* FUN_0034f474 */
extern uint64_t skp10_sk_rt_0034f554();   /* FUN_0034f554 */
extern uint64_t skp10_sk_rt_0034f594();   /* FUN_0034f594 */
extern uint64_t skp10_sk_rt_0034f654();   /* FUN_0034f654 */
extern uint64_t skp10_sk_rt_0034f730();   /* FUN_0034f730 */
extern uint64_t skp10_sk_rt_0034fb28();   /* FUN_0034fb28 */
extern uint64_t skp10_sk_rt_0034fd4c();   /* FUN_0034fd4c */
extern uint64_t skp10_sk_rt_0034fd7c();   /* FUN_0034fd7c */
extern uint64_t skp10_sk_rt_0034fe64();   /* FUN_0034fe64 */
extern uint64_t skp10_sk_rt_0034ff78();   /* FUN_0034ff78 */
extern uint64_t skp10_sk_rt_00350088();   /* FUN_00350088 */
extern uint64_t skp10_sk_rt_003501b8();   /* FUN_003501b8 */
extern uint64_t skp10_sk_rt_00350318();   /* FUN_00350318 */
extern uint64_t skp10_sk_rt_0035036c();   /* FUN_0035036c */
extern uint64_t skp10_sk_rt_00350390();   /* FUN_00350390 */
extern uint64_t skp10_sk_rt_003503c0();   /* FUN_003503c0 */
extern uint64_t skp10_sk_rt_003503d0();   /* FUN_003503d0 */
extern uint64_t skp10_sk_rt_003503f8();   /* FUN_003503f8 */
extern uint64_t skp10_sk_rt_00350404();   /* FUN_00350404 */
extern uint64_t skp10_sk_rt_00350410();   /* FUN_00350410 */
extern uint64_t skp10_sk_rt_00350434();   /* FUN_00350434 */
extern uint64_t skp10_sk_rt_0035044c();   /* FUN_0035044c */
extern uint64_t skp10_sk_rt_00350464();   /* FUN_00350464 */
extern uint64_t skp10_sk_rt_00350470();   /* FUN_00350470 */
extern uint64_t skp10_sk_rt_0035047c();   /* FUN_0035047c */
extern uint64_t skp10_sk_rt_00350488();   /* FUN_00350488 */
extern uint64_t skp10_sk_rt_00350494();   /* FUN_00350494 */
extern uint64_t skp10_sk_rt_003504a0();   /* FUN_003504a0 */
extern uint64_t skp10_sk_rt_003504ac();   /* FUN_003504ac */
extern uint64_t skp10_sk_rt_003504b8();   /* FUN_003504b8 */
extern uint64_t skp10_sk_rt_003504c4();   /* FUN_003504c4 */
extern uint64_t skp10_sk_rt_003504e8();   /* FUN_003504e8 */
extern uint64_t skp10_sk_rt_003504f4();   /* FUN_003504f4 */
extern uint64_t skp10_sk_rt_00350500();   /* FUN_00350500 */
extern uint64_t skp10_sk_rt_00350518();   /* FUN_00350518 */
extern uint64_t skp10_sk_rt_00350530();   /* FUN_00350530 */
extern uint64_t skp10_sk_rt_0035053c();   /* FUN_0035053c */
extern uint64_t skp10_sk_rt_00350560();   /* FUN_00350560 */
extern uint64_t skp10_sk_rt_0035056c();   /* FUN_0035056c */
extern uint64_t skp10_sk_rt_003505e8();   /* FUN_003505e8 */
extern uint64_t skp10_sk_rt_003505f4();   /* FUN_003505f4 */
extern uint64_t skp10_sk_rt_00350600();   /* FUN_00350600 */
extern uint64_t skp10_sk_rt_0035060c();   /* FUN_0035060c */
extern uint64_t skp10_sk_rt_00350618();   /* FUN_00350618 */
extern uint64_t skp10_sk_rt_00350624();   /* FUN_00350624 */
extern uint64_t skp10_sk_rt_0035063c();   /* FUN_0035063c */
extern uint64_t skp10_sk_rt_00350648();   /* FUN_00350648 */
extern uint64_t skp10_sk_rt_0035066c();   /* FUN_0035066c */
extern uint64_t skp10_sk_rt_00350678();   /* FUN_00350678 */
extern uint64_t skp10_sk_rt_00350704();   /* FUN_00350704 */
extern uint64_t skp10_sk_rt_0035072c();   /* FUN_0035072c */
extern uint64_t skp10_sk_rt_00350738();   /* FUN_00350738 */
extern uint64_t skp10_sk_rt_00350744();   /* FUN_00350744 */
extern uint64_t skp10_sk_rt_00350768();   /* FUN_00350768 */
extern uint64_t skp10_sk_rt_00350774();   /* FUN_00350774 */
extern uint64_t skp10_sk_rt_00350780();   /* FUN_00350780 */
extern uint64_t skp10_sk_rt_00350798();   /* FUN_00350798 */
extern uint64_t skp10_sk_rt_003507bc();   /* FUN_003507bc */
extern uint64_t skp10_sk_rt_003507d4();   /* FUN_003507d4 */
extern uint64_t skp10_sk_rt_003507e0();   /* FUN_003507e0 */
extern uint64_t skp10_sk_rt_00350810();   /* FUN_00350810 */
extern uint64_t skp10_sk_rt_0035084c();   /* FUN_0035084c */
extern uint64_t skp10_sk_rt_00350878();   /* FUN_00350878 */
extern uint64_t skp10_sk_rt_00350884();   /* FUN_00350884 */
extern uint64_t skp10_sk_rt_0035089c();   /* FUN_0035089c */
extern uint64_t skp10_sk_rt_003508a8();   /* FUN_003508a8 */
extern uint64_t skp10_sk_rt_003508c0();   /* FUN_003508c0 */
extern uint64_t skp10_sk_rt_003508d8();   /* FUN_003508d8 */
extern uint64_t skp10_sk_rt_003508e4();   /* FUN_003508e4 */
extern uint64_t skp10_sk_rt_003508f0();   /* FUN_003508f0 */
extern uint64_t skp10_sk_rt_00350908();   /* FUN_00350908 */
extern uint64_t skp10_sk_rt_00350914();   /* FUN_00350914 */
extern uint64_t skp10_sk_rt_00350920();   /* FUN_00350920 */
extern uint64_t skp10_sk_rt_00350944();   /* FUN_00350944 */
extern uint64_t skp10_sk_rt_00350968();   /* FUN_00350968 */
extern uint64_t skp10_sk_rt_00350980();   /* FUN_00350980 */
extern uint64_t skp10_sk_rt_003509c8();   /* FUN_003509c8 */
extern uint64_t skp10_sk_rt_003509d4();   /* FUN_003509d4 */
extern uint64_t skp10_sk_rt_003509ec();   /* FUN_003509ec */
extern uint64_t skp10_sk_rt_00350a04();   /* FUN_00350a04 */
extern uint64_t skp10_sk_rt_00350a10();   /* FUN_00350a10 */
extern uint64_t skp10_sk_rt_00350a1c();   /* FUN_00350a1c */
extern uint64_t skp10_sk_rt_00350a28();   /* FUN_00350a28 */
extern uint64_t skp10_sk_rt_00350a34();   /* FUN_00350a34 */
extern uint64_t skp10_sk_rt_00350a40();   /* FUN_00350a40 */
extern uint64_t skp10_sk_rt_00350a64();   /* FUN_00350a64 */
extern uint64_t skp10_sk_rt_00350a70();   /* FUN_00350a70 */
extern uint64_t skp10_sk_rt_00350ab8();   /* FUN_00350ab8 */
extern uint64_t skp10_sk_rt_00350ac4();   /* FUN_00350ac4 */
extern uint64_t skp10_sk_rt_00350ad0();   /* FUN_00350ad0 */
extern uint64_t skp10_sk_rt_00350af4();   /* FUN_00350af4 */
extern uint64_t skp10_sk_rt_00350b00();   /* FUN_00350b00 */
extern uint64_t skp10_sk_rt_00350b18();   /* FUN_00350b18 */
extern uint64_t skp10_sk_rt_00350b24();   /* FUN_00350b24 */
extern uint64_t skp10_sk_rt_00350b30();   /* FUN_00350b30 */
extern uint64_t skp10_sk_rt_00350b48();   /* FUN_00350b48 */
extern uint64_t skp10_sk_rt_00350b84();   /* FUN_00350b84 */
extern uint64_t skp10_sk_rt_00350b9c();   /* FUN_00350b9c */
extern uint64_t skp10_sk_rt_00350ba8();   /* FUN_00350ba8 */
extern uint64_t skp10_sk_rt_00350bd8();   /* FUN_00350bd8 */
extern uint64_t skp10_sk_rt_00350c38();   /* FUN_00350c38 */
extern uint64_t skp10_sk_rt_00350c80();   /* FUN_00350c80 */
extern uint64_t skp10_sk_rt_00350ea4();   /* FUN_00350ea4 */
extern uint64_t skp10_sk_rt_00350f0c();   /* FUN_00350f0c */
extern uint64_t skp10_sk_rt_00351048();   /* FUN_00351048 */
extern uint64_t skp10_sk_rt_003510ac();   /* FUN_003510ac */
extern uint64_t skp10_sk_rt_003510dc();   /* FUN_003510dc */
extern uint64_t skp10_sk_rt_00351100();   /* FUN_00351100 */
extern uint64_t skp10_sk_rt_00351118();   /* FUN_00351118 */
extern uint64_t skp10_sk_rt_00351130();   /* FUN_00351130 */
extern uint64_t skp10_sk_rt_00351184();   /* FUN_00351184 */
extern uint64_t skp10_sk_rt_00351190();   /* FUN_00351190 */
extern uint64_t skp10_sk_rt_003511a8();   /* FUN_003511a8 */
extern uint64_t skp10_sk_rt_003511b4();   /* FUN_003511b4 */
extern uint64_t skp10_sk_rt_00351214();   /* FUN_00351214 */
extern uint64_t skp10_sk_rt_0035125c();   /* FUN_0035125c */
extern uint64_t skp10_sk_rt_00351274();   /* FUN_00351274 */
extern uint64_t skp10_sk_rt_00351280();   /* FUN_00351280 */
extern uint64_t skp10_sk_rt_0035128c();   /* FUN_0035128c */
extern uint64_t skp10_sk_rt_003512cc();   /* FUN_003512cc */
extern uint64_t skp10_sk_rt_0035130c();   /* FUN_0035130c */
extern uint64_t skp10_sk_rt_00351318();   /* FUN_00351318 */
extern uint64_t skp10_sk_rt_0035133c();   /* FUN_0035133c */
extern uint64_t skp10_sk_rt_00351354();   /* FUN_00351354 */
extern uint64_t skp10_sk_rt_00351378();   /* FUN_00351378 */
extern uint64_t skp10_sk_rt_00351384();   /* FUN_00351384 */
extern uint64_t skp10_sk_rt_003513a8();   /* FUN_003513a8 */
extern uint64_t skp10_sk_rt_003513b4();   /* FUN_003513b4 */
extern uint64_t skp10_sk_rt_003513d8();   /* FUN_003513d8 */
extern uint64_t skp10_sk_rt_00351414();   /* FUN_00351414 */
extern uint64_t skp10_sk_rt_00351450();   /* FUN_00351450 */
extern uint64_t skp10_sk_rt_0035145c();   /* FUN_0035145c */
extern uint64_t skp10_sk_rt_00351468();   /* FUN_00351468 */
extern uint64_t skp10_sk_rt_003514a0();   /* FUN_003514a0 */
extern uint64_t skp10_sk_rt_003514b8();   /* FUN_003514b8 */
extern uint64_t skp10_sk_rt_003514d0();   /* FUN_003514d0 */
extern uint64_t skp10_sk_rt_00351548();   /* FUN_00351548 */
extern uint64_t skp10_sk_rt_00351554();   /* FUN_00351554 */
extern uint64_t skp10_sk_rt_00351560();   /* FUN_00351560 */
extern uint64_t skp10_sk_rt_00351584();   /* FUN_00351584 */
extern uint64_t skp10_sk_rt_003515b4();   /* FUN_003515b4 */
extern uint64_t skp10_sk_rt_003515e4();   /* FUN_003515e4 */
extern uint64_t skp10_sk_rt_003515fc();   /* FUN_003515fc */
extern uint64_t skp10_sk_rt_00351624();   /* FUN_00351624 */
extern uint64_t skp10_sk_rt_0035163c();   /* FUN_0035163c */
extern uint64_t skp10_sk_rt_0035166c();   /* FUN_0035166c */
extern uint64_t skp10_sk_rt_003516a8();   /* FUN_003516a8 */
extern uint64_t skp10_sk_rt_003516cc();   /* FUN_003516cc */
extern uint64_t skp10_sk_rt_003516f0();   /* FUN_003516f0 */
extern uint64_t skp10_sk_rt_003516fc();   /* FUN_003516fc */
extern uint64_t skp10_sk_rt_00351708();   /* FUN_00351708 */
extern uint64_t skp10_sk_rt_00351714();   /* FUN_00351714 */
extern uint64_t skp10_sk_rt_00351738();   /* FUN_00351738 */
extern uint64_t skp10_sk_rt_00351744();   /* FUN_00351744 */
extern uint64_t skp10_sk_rt_00351790();   /* FUN_00351790 */
extern uint64_t skp10_sk_rt_003517c0();   /* FUN_003517c0 */
extern uint64_t skp10_sk_rt_003518b8();   /* FUN_003518b8 */
extern uint64_t skp10_sk_rt_0035190c();   /* FUN_0035190c */
extern uint64_t skp10_sk_rt_00351924();   /* FUN_00351924 */
extern uint64_t skp10_sk_rt_00351990();   /* FUN_00351990 */
extern uint64_t skp10_sk_rt_003519d4();   /* FUN_003519d4 */
extern uint64_t skp10_sk_rt_00351a80();   /* FUN_00351a80 */
extern uint64_t skp10_sk_rt_00351b78();   /* FUN_00351b78 */
extern uint64_t skp10_sk_rt_00351b84();   /* FUN_00351b84 */
extern uint64_t skp10_sk_rt_00351bac();   /* FUN_00351bac */
extern uint64_t skp10_sk_rt_00351be0();   /* FUN_00351be0 */
extern uint64_t skp10_sk_rt_00351bec();   /* FUN_00351bec */
extern uint64_t skp10_sk_rt_00351c10();   /* FUN_00351c10 */
extern uint64_t skp10_sk_rt_00351c7c();   /* FUN_00351c7c */
extern uint64_t skp10_sk_rt_00351cc4();   /* FUN_00351cc4 */
extern uint64_t skp10_sk_rt_00351d00();   /* FUN_00351d00 */
extern uint64_t skp10_sk_rt_00351d24();   /* FUN_00351d24 */
extern uint64_t skp10_sk_rt_00351d30();   /* FUN_00351d30 */
extern uint64_t skp10_sk_rt_00351da8();   /* FUN_00351da8 */
extern uint64_t skp10_sk_rt_00351db4();   /* FUN_00351db4 */
extern uint64_t skp10_sk_rt_00351df0();   /* FUN_00351df0 */
extern uint64_t skp10_sk_rt_00351dfc();   /* FUN_00351dfc */
extern uint64_t skp10_sk_rt_00351e20();   /* FUN_00351e20 */
extern uint64_t skp10_sk_rt_00351e90();   /* FUN_00351e90 */
extern uint64_t skp10_sk_rt_00351ea8();   /* FUN_00351ea8 */
extern uint64_t skp10_sk_rt_00351ec0();   /* FUN_00351ec0 */
extern uint64_t skp10_sk_rt_00351ecc();   /* FUN_00351ecc */
extern uint64_t skp10_sk_rt_00351ee0();   /* FUN_00351ee0 */
extern uint64_t skp10_sk_rt_00351ef8();   /* FUN_00351ef8 */
extern uint64_t skp10_sk_rt_00351f10();   /* FUN_00351f10 */
extern uint64_t skp10_sk_rt_00351f28();   /* FUN_00351f28 */
extern uint64_t skp10_sk_rt_00351f7c();   /* FUN_00351f7c */
extern uint64_t skp10_sk_rt_00351f88();   /* FUN_00351f88 */
extern uint64_t skp10_sk_rt_003520dc();   /* FUN_003520dc */
extern uint64_t skp10_sk_rt_0035215c();   /* FUN_0035215c */
extern uint64_t skp10_sk_rt_0035216c();   /* FUN_0035216c */
extern uint64_t skp10_sk_rt_00352314();   /* FUN_00352314 */
extern uint64_t skp10_sk_rt_00352414();   /* FUN_00352414 */
extern uint64_t skp10_sk_rt_00352420();   /* FUN_00352420 */
extern uint64_t skp10_sk_rt_00352468();   /* FUN_00352468 */
extern uint64_t skp10_sk_rt_00352480();   /* FUN_00352480 */
extern uint64_t skp10_sk_rt_0035248c();   /* FUN_0035248c */
extern uint64_t skp10_sk_rt_00352498();   /* FUN_00352498 */
extern uint64_t skp10_sk_rt_003524a4();   /* FUN_003524a4 */
extern uint64_t skp10_sk_rt_003524c8();   /* FUN_003524c8 */
extern uint64_t skp10_sk_rt_00352578();   /* FUN_00352578 */
extern uint64_t skp10_sk_rt_00352590();   /* FUN_00352590 */
extern uint64_t skp10_sk_rt_003526a4();   /* FUN_003526a4 */
extern uint64_t skp10_sk_rt_003526ec();   /* FUN_003526ec */
extern uint64_t skp10_sk_rt_00352700();   /* FUN_00352700 */
extern uint64_t skp10_sk_rt_00352800();   /* FUN_00352800 */
extern uint64_t skp10_sk_rt_00352864();   /* FUN_00352864 */
extern uint64_t skp10_sk_rt_00352894();   /* FUN_00352894 */
extern uint64_t skp10_sk_rt_003528ac();   /* FUN_003528ac */
extern uint64_t skp10_sk_rt_003528cc();   /* FUN_003528cc */
extern uint64_t skp10_sk_rt_00352914();   /* FUN_00352914 */
extern uint64_t skp10_sk_rt_00352920();   /* FUN_00352920 */
extern uint64_t skp10_sk_rt_00352a40();   /* FUN_00352a40 */
extern uint64_t skp10_sk_rt_00352b50();   /* FUN_00352b50 */
extern uint64_t skp10_sk_rt_00352be0();   /* FUN_00352be0 */
extern uint64_t skp10_sk_rt_00352c34();   /* FUN_00352c34 */
extern uint64_t skp10_sk_rt_00352dd0();   /* FUN_00352dd0 */
extern uint64_t skp10_sk_rt_00352ea8();   /* FUN_00352ea8 */
extern uint64_t skp10_sk_rt_00352ecc();   /* FUN_00352ecc */
extern uint64_t skp10_sk_rt_00352ee4();   /* FUN_00352ee4 */
extern uint64_t skp10_sk_rt_00352efc();   /* FUN_00352efc */
extern uint64_t skp10_sk_rt_0035300c();   /* FUN_0035300c */
extern uint64_t skp10_sk_rt_00353034();   /* FUN_00353034 */
extern uint64_t skp10_sk_rt_003530a4();   /* FUN_003530a4 */
extern uint64_t skp10_sk_rt_0035316c();   /* FUN_0035316c */
extern uint64_t skp10_sk_rt_003531a8();   /* FUN_003531a8 */
extern uint64_t skp10_sk_rt_003531cc();   /* FUN_003531cc */
extern uint64_t skp10_sk_rt_003531f0();   /* FUN_003531f0 */
extern uint64_t skp10_sk_rt_00353238();   /* FUN_00353238 */
extern uint64_t skp10_sk_rt_00353300();   /* FUN_00353300 */
extern uint64_t skp10_sk_rt_00353480();   /* FUN_00353480 */
extern uint64_t skp10_sk_rt_00353504();   /* FUN_00353504 */
extern uint64_t skp10_sk_rt_0035351c();   /* FUN_0035351c */
extern uint64_t skp10_sk_rt_0035377c();   /* FUN_0035377c */
extern uint64_t skp10_sk_rt_00353830();   /* FUN_00353830 */
extern uint64_t skp10_sk_rt_00353b10();   /* FUN_00353b10 */
extern uint64_t skp10_sk_rt_00353b1c();   /* FUN_00353b1c */
extern uint64_t skp10_sk_rt_00353b4c();   /* FUN_00353b4c */
extern uint64_t skp10_sk_rt_00353cd8();   /* FUN_00353cd8 */
extern uint64_t skp10_sk_rt_00353f88();   /* FUN_00353f88 */
extern uint64_t skp10_sk_rt_00353fa0();   /* FUN_00353fa0 */
extern uint64_t skp10_sk_rt_003540ac();   /* FUN_003540ac */
extern uint64_t skp10_sk_rt_003540f4();   /* FUN_003540f4 */
extern uint64_t skp10_sk_rt_00354318();   /* FUN_00354318 */
extern uint64_t skp10_sk_rt_00354458();   /* FUN_00354458 */
extern uint64_t skp10_sk_rt_003544c8();   /* FUN_003544c8 */
extern uint64_t skp10_sk_rt_00354744();   /* FUN_00354744 */
extern uint64_t skp10_sk_rt_0035478c();   /* FUN_0035478c */
extern uint64_t skp10_sk_rt_00354810();   /* FUN_00354810 */
extern uint64_t skp10_sk_rt_003548c4();   /* FUN_003548c4 */
extern uint64_t skp10_sk_rt_00354948();   /* FUN_00354948 */
extern uint64_t skp10_sk_rt_00354abc();   /* FUN_00354abc */
extern uint64_t skp10_sk_rt_00354d80();   /* FUN_00354d80 */
extern uint64_t skp10_sk_rt_00354d94();   /* FUN_00354d94 */
extern uint64_t skp10_sk_rt_00354da0();   /* FUN_00354da0 */
extern uint64_t skp10_sk_rt_00354db8();   /* FUN_00354db8 */
extern uint64_t skp10_sk_rt_00354f1c();   /* FUN_00354f1c */
extern uint64_t skp10_sk_rt_00354f4c();   /* FUN_00354f4c */
extern uint64_t skp10_sk_rt_00354f80();   /* FUN_00354f80 */
extern uint64_t skp10_sk_rt_00355224();   /* FUN_00355224 */
extern uint64_t skp10_sk_rt_00355300();   /* FUN_00355300 */
extern uint64_t skp10_sk_rt_00355334();   /* FUN_00355334 */
extern uint64_t skp10_sk_rt_00355578();   /* FUN_00355578 */
extern uint64_t skp10_sk_rt_0035583c();   /* FUN_0035583c */
extern uint64_t skp10_sk_rt_00355908();   /* FUN_00355908 */
extern uint64_t skp10_sk_rt_00355ab4();   /* FUN_00355ab4 */
extern uint64_t skp10_sk_rt_00355b28();   /* FUN_00355b28 */
extern uint64_t skp10_sk_rt_00355bf4();   /* FUN_00355bf4 */
extern uint64_t skp10_sk_rt_00355c28();   /* FUN_00355c28 */
extern uint64_t skp10_sk_rt_00355cbc();   /* FUN_00355cbc */
extern uint64_t skp10_sk_rt_00355d78();   /* FUN_00355d78 */
extern uint64_t skp10_sk_rt_00355f04();   /* FUN_00355f04 */
extern uint64_t skp10_sk_rt_00355fa0();   /* FUN_00355fa0 */
extern uint64_t skp10_sk_rt_00356030();   /* FUN_00356030 */
extern uint64_t skp10_sk_rt_00356200();   /* FUN_00356200 */
extern uint64_t skp10_sk_rt_003562d4();   /* FUN_003562d4 */
extern uint64_t skp10_sk_rt_00356364();   /* FUN_00356364 */
extern uint64_t skp10_sk_rt_003564d0();   /* FUN_003564d0 */
extern uint64_t skp10_sk_rt_003567b0();   /* FUN_003567b0 */
extern uint64_t skp10_sk_rt_003567f8();   /* FUN_003567f8 */
extern uint64_t skp10_sk_rt_0035684c();   /* FUN_0035684c */
extern uint64_t skp10_sk_rt_00356ad0();   /* FUN_00356ad0 */
extern uint64_t skp10_sk_rt_00356b98();   /* FUN_00356b98 */
extern uint64_t skp10_sk_rt_00356e28();   /* FUN_00356e28 */
extern uint64_t skp10_sk_rt_00356e34();   /* FUN_00356e34 */
extern uint64_t skp10_sk_rt_003573f4();   /* FUN_003573f4 */
extern uint64_t skp10_sk_rt_00357748();   /* FUN_00357748 */
extern uint64_t skp10_sk_rt_00357754();   /* FUN_00357754 */
extern uint64_t skp10_sk_rt_00357a9c();   /* FUN_00357a9c */
extern uint64_t skp10_sk_rt_00357ab4();   /* FUN_00357ab4 */
extern uint64_t skp10_sk_rt_00357af8();   /* FUN_00357af8 */
extern uint64_t skp10_sk_rt_00357b04();   /* FUN_00357b04 */
extern uint64_t skp10_sk_rt_00357b7c();   /* FUN_00357b7c */
extern uint64_t skp10_sk_rt_00357c44();   /* FUN_00357c44 */
extern uint64_t skp10_sk_rt_00357c74();   /* FUN_00357c74 */
extern uint64_t skp10_sk_rt_00357ca0();   /* FUN_00357ca0 */
extern uint64_t skp10_sk_rt_00357cb4();   /* FUN_00357cb4 */
extern uint64_t skp10_sk_rt_00358124();   /* FUN_00358124 */
extern uint64_t skp10_sk_rt_00358144();   /* FUN_00358144 */
extern uint64_t skp10_sk_rt_003583e8();   /* FUN_003583e8 */
extern uint64_t skp10_sk_rt_00358454();   /* FUN_00358454 */
extern uint64_t skp10_sk_rt_0035847c();   /* FUN_0035847c */
extern uint64_t skp10_sk_rt_003584f8();   /* FUN_003584f8 */
extern uint64_t skp10_sk_rt_00358870();   /* FUN_00358870 */
extern uint64_t skp10_sk_rt_003588a0();   /* FUN_003588a0 */
extern uint64_t skp10_sk_rt_00358dac();   /* FUN_00358dac */
extern uint64_t skp10_sk_rt_00358e88();   /* FUN_00358e88 */
extern uint64_t skp10_sk_rt_00358ef4();   /* FUN_00358ef4 */
extern uint64_t skp10_sk_rt_00358fb4();   /* FUN_00358fb4 */
extern uint64_t skp10_sk_rt_00358fc8();   /* FUN_00358fc8 */
extern uint64_t skp10_sk_rt_00358fe8();   /* FUN_00358fe8 */
extern uint64_t skp10_sk_rt_00358ff4();   /* FUN_00358ff4 */
extern uint64_t skp10_sk_rt_00359000();   /* FUN_00359000 */
extern uint64_t skp10_sk_rt_003591d0();   /* FUN_003591d0 */
extern uint64_t skp10_sk_rt_00359338();   /* FUN_00359338 */
extern uint64_t skp10_sk_rt_00359530();   /* FUN_00359530 */
extern uint64_t skp10_sk_rt_00359704();   /* FUN_00359704 */
extern uint64_t skp10_sk_rt_003598a0();   /* FUN_003598a0 */
extern uint64_t skp10_sk_rt_00359ac8();   /* FUN_00359ac8 */
extern uint64_t skp10_sk_rt_00359d70();   /* FUN_00359d70 */
extern uint64_t skp10_sk_rt_00359d9c();   /* FUN_00359d9c */
extern uint64_t skp10_sk_rt_00359e14();   /* FUN_00359e14 */
extern uint64_t skp10_sk_rt_00359ec0();   /* FUN_00359ec0 */
extern uint64_t skp10_sk_rt_0035a080();   /* FUN_0035a080 */
extern uint64_t skp10_sk_rt_0035a1b4();   /* FUN_0035a1b4 */
extern uint64_t skp10_sk_rt_0035a1c0();   /* FUN_0035a1c0 */
extern uint64_t skp10_sk_rt_0035a28c();   /* FUN_0035a28c */
extern uint64_t skp10_sk_rt_0035a3ac();   /* FUN_0035a3ac */
extern uint64_t skp10_sk_rt_0035a3c4();   /* FUN_0035a3c4 */
extern uint64_t skp10_sk_rt_0035a6a8();   /* FUN_0035a6a8 */
extern uint64_t skp10_sk_rt_0035a76c();   /* FUN_0035a76c */
extern uint64_t skp10_sk_rt_00361528();   /* FUN_00361528 */
extern uint64_t skp10_sk_rt_00365b6c();   /* FUN_00365b6c */
extern uint64_t skp10_sk_rt_0036986c();   /* FUN_0036986c */
extern uint64_t skp10_sk_rt_0036a908();   /* FUN_0036a908 */
extern uint64_t skp10_sk_rt_0036b118();   /* FUN_0036b118 */
extern uint64_t skp10_sk_rt_0036b270();   /* FUN_0036b270 */
extern uint64_t skp10_sk_rt_003722e4();   /* skp10_FUN_003722e4 */
extern uint64_t skp10_sk_rt_00376820();   /* FUN_00376820 */
extern uint64_t skp10_sk_rt_00377824();   /* FUN_00377824 */
extern uint64_t skp10_sk_rt_00377bec();   /* FUN_00377bec */
extern uint64_t skp10_sk_rt_00377dcc();   /* FUN_00377dcc */
extern uint64_t skp10_sk_rt_003a0b04();   /* FUN_003a0b04 */
extern uint64_t skp10_sk_rt_003a0c90();   /* FUN_003a0c90 */
extern uint64_t skp10_sk_rt_003a25d4();   /* FUN_003a25d4 */
extern uint64_t skp10_sk_rt_003a261c();   /* FUN_003a261c */
extern uint64_t skp10_sk_rt_003d30b0();   /* FUN_003d30b0 */
extern uint64_t skp10_sk_rt_003d31d8();   /* FUN_003d31d8 */
extern uint64_t skp10_sk_rt_003d31e8();   /* FUN_003d31e8 */
extern uint64_t skp10_sk_rtt_00054414();   /* thunk_FUN_00054414 */
extern uint64_t skp10_sk_rtt_00054464();   /* thunk_FUN_00054464 */
extern uint64_t skp10_sk_rtt_0005453c();   /* thunk_FUN_0005453c */
extern uint64_t skp10_sk_rtt_002298d4();   /* thunk_FUN_002298d4 */
extern uint64_t skp10_sk_rtt_00229ebc();   /* thunk_FUN_00229ebc */
extern uint64_t skp10_sk_rtt_002a2698();   /* thunk_FUN_002a2698 */
extern uint64_t skp10_sk_rtt_002acbb8();   /* thunk_FUN_002acbb8 */
extern uint64_t skp10_sk_rtt_0036b270();   /* thunk_FUN_0036b270 */
extern uint64_t skp10_sk_rtt_003d31d8();   /* thunk_FUN_003d31d8 */
extern uint64_t skp10_sk_rtt_003d31e8();   /* thunk_FUN_003d31e8 */

/* ------------------------------------------------------------------ *
 * Forward declarations for functions reconstructed in this file.
 * ------------------------------------------------------------------ */
uint8_t sk_vspace_dispatch_a(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4); /* 002652e4 */
void    sk_vspace_boot_enter(uint64_t p1, uint64_t p2, uint64_t p3);              /* 002655cc */
void    sk_vspace_msg_dispatch(uint64_t p1, uint64_t p2);                         /* 0026574c */
void    sk_vspace_msg_dispatch_b(uint64_t p1, uint64_t p2);                       /* 00265750 */
bool    sk_vspace_msg_check(uint64_t p1, uint64_t p2);                            /* 00265770 */
bool    sk_vspace_msg_check_b(uint64_t p1, uint64_t p2);                          /* 00265774 */
void    sk_vspace_run_loop_a(void);                                               /* 00265794 */
void    sk_vspace_run_loop_b(void);                                               /* 00265884 */
void    sk_vspace_release_op(uint64_t p1, uint64_t p2, uint64_t p3);              /* 00265994 */
void    sk_vspace_release_op_b(uint64_t p1, uint64_t p2, uint64_t p3);            /* 00265a74 */
void    skp10_sk_vspace_dispatch_table(uint64_t p1, uint64_t p2, uint64_t p3);          /* 00265b90 */
void    skp10_sk_vspace_claim_region(void);                                             /* 00265e08 */
void    sk_vspace_claim_region_b(void);                                           /* 00265f48 */
void    sk_vspace_trap_alloc(void);                                               /* 002660ac */
void    sk_vspace_cap_ops(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4);    /* 002661f4 */
void    skp10_sk_vspace_cap_ops_b(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4,
                            void (*fn)(void));                                    /* 0026638c */
void    skp10_sk_vspace_range_load(uint8_t *bytes, long n);                             /* 00266504 */
void    sk_vspace_init_a(void);                                                   /* 00266688 */
void    sk_vspace_init_b(void);                                                   /* 002666b8 */
uint64_t sk_vspace_load_int(uint64_t *src, long type_info);                       /* 0026670c */
void    sk_vspace_entry_dispatch(uint64_t p1, uint64_t p2, uint64_t p3,
                                 uint64_t p4, uint64_t *p5, uint64_t p6,
                                 uint64_t p7);                                    /* 002667a8 */
void    sk_vspace_commit(uint64_t p1, uint64_t p2, uint64_t p3);                  /* 002673dc */
void    sk_vspace_region_check(void);                                             /* 00267510 */
void    skp10_sk_vspace_lock_enter(void);                                               /* 002676b4 */
void    skp10_sk_vspace_lock_leave(void);                                               /* 002676b8 */
void    sk_vspace_object_create();                                            /* 002676bc */
void    sk_vspace_lock_enter_fwd(void);                                           /* 00267798 */
void    sk_vspace_lock_enter_fwd2(void);                                          /* 0026779c */
void    sk_vspace_lock_leave_fwd(void);                                           /* 002677b0 */
void    sk_vspace_lock_leave_fwd2(void);                                          /* 002677b4 */
void    sk_vspace_object_create_fwd(void);                                        /* 002677c8 */
void    sk_vspace_object_create_fwd2(void);                                       /* 002677cc */
void    skp10_sk_vspace_ipc_transition();                                           /* 002677e4 */
void    skp10_sk_vspace_ipc_transition_slow(void);                                      /* 00267820 */
void    sk_vspace_teardown_a(void);                                               /* 002678b4 */
void    sk_vspace_irq_sync(void);                                                 /* 00267914 */
void    sk_vspace_tcb_swap(uint64_t p1, uint64_t p2, long p3);                    /* 00267994 */
void    sk_vspace_tcb_swap_b(void);                                               /* 00267a0c */
void    sk_vspace_obj_dispatch(long p1);                                          /* 00267a74 */
void    sk_vspace_svc_call(uint64_t p1, uint64_t p2, uint64_t p3);                /* 00267af8 */
bool    skp10_sk_vspace_region_compare(void);                                           /* 00267ba0 */
void    sk_vspace_region_cursor(void);                                            /* 00267c00 */
void    sk_vspace_region_cursor_b(void);                                          /* 00267c80 */
void    skp10_sk_vspace_region_divide(void);                                            /* 00267cfc */
void    sk_vspace_dispatch_ret(void);                                             /* 00267efc */
void    sk_vspace_state_push(void);                                               /* 00268038 */
void    sk_vspace_state_push_b(void);                                             /* 002680a8 */
void    sk_vspace_obj_ref(uint64_t p1);                                           /* 0026817c */
void    sk_vspace_obj_unref(uint64_t p1);                                         /* 002681d8 */
void    sk_vspace_alloc_block(uint64_t p1, uint64_t p2, long p3);                 /* 0026830c */
void    sk_vspace_alloc_block_b(void);                                            /* 00268400 */
long    sk_vspace_string_append(uint64_t value, uint64_t storage);                /* 00268540 */
void    sk_vspace_key_init(void);                                                 /* 0026863c */
void    sk_vspace_key_destroy(long p1);                                           /* 00268670 */
void    sk_vspace_key_destroy_fwd(void);                                          /* 00268704 */
void    sk_vspace_key_destroy_fwd2(void);                                         /* 00268708 */
void    sk_vspace_table_put(void);                                                /* 00268734 */
void    sk_vspace_table_count(long p1);                                           /* 002687a8 */
void    sk_vspace_table_put_b(void);                                              /* 002687e8 */
void    sk_vspace_table_get(void);                                                /* 00268870 */
void    sk_vspace_key_ops(void);                                                  /* 00268a78 */
void    sk_vspace_msg_send(uint64_t p1, long p2);                                 /* 00268b34 */
void    sk_vspace_ep_reply(uint64_t p1, uint64_t p2, uint64_t p3);                /* 00268b88 */
void    sk_vspace_ep_reply_b(uint64_t p1, uint64_t p2, uint64_t p3);              /* 00268bf8 */
void    sk_vspace_recv_loop(void);                                                /* 00268c58 */
void    sk_vspace_recv_loop_b(void);                                              /* 00268e7c */
void    skp10_sk_vspace_wait_sync(uint64_t p1, uint64_t p2, uint64_t p3);               /* 0026909c */
void    sk_vspace_table_op(uint64_t p1, long p2, uint64_t p3);                    /* 00269224 */
void    skp10_sk_vspace_table_dispatch(void);                                           /* 002692b8 */
void    skp10_sk_vspace_notify(uint64_t p1, uint64_t p2, uint64_t p3);                  /* 00269490 */
void    skp10_sk_vspace_signal(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4);                  /* 002698bc */
void    *sk_vspace_alloc_obj(long *slot, uint64_t p2, uint64_t p3, uint64_t p4);   /* 00269a88 */
uint64_t sk_vspace_alloc_obj_b(long *slot, uint64_t p2, long p3, uint64_t p4);     /* 00269b08 */
void    sk_vspace_obj_msg(void);                                                  /* 00269bf4 */
void    sk_vspace_scan(uint64_t p1, uint64_t p2, uint64_t p3,
                       void (*a)(void), void (*b)(void));                         /* 00269c70 */
void    sk_vspace_walk(uint64_t p1, uint64_t p2, uint64_t p3);                                                     /* 00269d30 */
void    sk_vspace_scan_b(uint64_t p1, uint64_t p2, uint64_t p3);                  /* 0026a1ac */
void    sk_vspace_noreturn_a(uint64_t p1, uint64_t p2, long p3);                  /* 0026a278 */
void    sk_vspace_noreturn_b(uint64_t p1, uint64_t p2, long p3);                  /* 0026a27c */
void    sk_vspace_noreturn_c(void);                                               /* 0026a2ac */
void    sk_vspace_noreturn_d(uint64_t p1, long p2);                               /* 0026a2bc */
void    sk_vspace_noreturn_e(uint64_t p1, uint64_t p2, long p3);                  /* 0026a2f0 */
void    sk_vspace_noreturn_f(uint64_t p1, uint64_t p2, long p3);                  /* 0026a2f4 */
bool    skp10_sk_table_lookup(long *out, long key);                                     /* 0026a328 */
void    skp10_sk_table_put_entries(uint64_t p1, uint64_t p2, uint64_t p3);              /* 0026a404 */
void    skp10_sk_table_get_entries(void);                                               /* 0026a560 */
bool    skp10_sk_table_lookup_b(uint64_t *out, uint64_t *in);                           /* 0026a744 */
bool    sk_table_lookup_c(long *out, long key);                                   /* 0026a9a8 */
void    skp10_sk_table_put_entry(uint64_t p1, uint64_t p2, long p3);                    /* 0026aa7c */
void    skp10_sk_table_remove_entry(void);                                              /* 0026acbc */
void    skp10_sk_table_get_entry(void);                                                 /* 0026adcc */
void    skp10_sk_table_lookup_d(uint64_t *out, long in);                                /* 0026af9c */
void    sk_table_remove_matching(void);                                           /* 0026b1dc */
void    sk_vspace_noreturn_g(uint64_t p1, uint64_t p2, uint64_t p3, long p4);     /* 0026b3c8 */
void    sk_vspace_noreturn_h(uint64_t p1, uint64_t p2, uint64_t p3, long p4);     /* 0026b3cc */
void    sk_vspace_noreturn_i(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4); /* 0026b3fc */
void    sk_vspace_noreturn_j(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4); /* 0026b400 */
void    sk_vspace_teardown_list(void);                                            /* 0026b434 */
void    sk_vspace_iter_entries(long list, uint64_t p2, uint64_t p3, uint64_t p4,
                               uint64_t p5, void **fn);                      /* 0026b460 */
void    sk_vspace_teardown_entries(long list, uint64_t p2, uint64_t p3,
                                   uint64_t p4, uint64_t p5, uint64_t p6);        /* 0026b5e8 */
void    sk_vspace_teardown_list_b(void);                                          /* 0026b71c */
void    sk_vspace_walk_entries(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4,
                               uint64_t p5, void (*fn)(void),
                               void (*jt)(void));                                 /* 0026b748 */
void    sk_vspace_iter_entries_b(long list, uint64_t p2, uint64_t p3,
                                 uint64_t p4, uint64_t p5, uint64_t p6);          /* 0026b9d0 */
void    skp10_sk_vspace_entry_drain(long p1, uint64_t p2, uint64_t p3, uint64_t p4,
                              uint64_t p5, uint64_t p6, uint64_t p7, uint64_t p8);/* 0026bbd4 */
uint64_t sk_vspace_load_word(void);                                               /* 0026bce8 */
void    sk_vspace_load_word_fwd(void);                                            /* 0026bd18 */
void    sk_vspace_load_word_fwd2(void);                                           /* 0026bd1c */
void    sk_vspace_bounds_check(long a, long b);                                   /* 0026bd30 */
void    skp10_sk_vspace_bounds_check_pages(uint64_t a, uint64_t b);                     /* 0026bd5c */
void    skp10_sk_vspace_invoke(void);                                                   /* 0026bdc4 */
void    sk_vspace_log(void);                                                      /* 0026c064 */
uint32_t sk_vspace_check(uint64_t p1, uint64_t p2, uint64_t p3);                  /* 0026c160 */
void    sk_vspace_callout(uint64_t p1, uint64_t p2, uint64_t p3, void (*fn)(void));/* 0026c210 */
void    sk_vspace_indirect_a(uint64_t p1, long p2);                               /* 0026c274 */
void    sk_vspace_indirect_b(uint64_t p1, long p2);                               /* 0026c2a0 */
void    sk_vspace_oob_panic(void);                                                /* 0026c6c8 */
void    skp10_sk_vspace_obj_check(uint64_t p1, uint64_t p2, uint64_t p3);               /* 0026c6d8 */
void    sk_vspace_scan_c(void);                                                   /* 0026ca24 */
void    skp10_sk_vspace_mem_validate(uint64_t p1, uint64_t p2, uint64_t p3);            /* 0026cb00 */
void    skp10_sk_vspace_mem_validate_b(uint64_t p1, uint64_t p2, uint64_t p3);          /* 0026cbd0 */
void    *sk_vspace_alloc_cap(long *slot, uint64_t p2, uint64_t p3, uint64_t p4);   /* 0026cc88 */

/* Out-of-slice forward target referenced by 0026cc88 (FUN_0026cd08). */
extern uint64_t skp10_sk_vspace_alloc_cap_b(long blk, uint64_t p2, uint64_t p3,
                                      uint64_t p4, uint64_t p5);                  /* FUN_0026cd08 */

/*--------------------------------------------------------------------*/
/* FUN_002652e4 @ 0x002652e4   (est. sk_vspace_dispatch_a)
 * Ghidra: byte skp10_sk_rt_002652e4(undefined8, undefined8, long, ulong)
 * Message dispatch that validates a capability/object pointer pair and
 * performs an access check via the object's method table. Reads the stack
 * cookie of the caller frame (param_4 & ~1 - 8), dereferences the object
 * vtable (+0x10, +0x40 offsets) and calls the object's +0x10 method with two
 * argument words. On success (FUN_000839f8 == 1 for both words) returns 1;
 * otherwise unwinds through the object teardown path.
 * Confidence: low (Swift-register-aliased indirect dispatch).
 * Notes: skp10_DAT_00658c00 = PAC'd runtime thunk; skp10_FUN_003722e4 (stack realloc),
 * FUN_000839f8 (per-word validity check), FUN_0014ae44 (indirect call).
 */
uint8_t sk_vspace_dispatch_a(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4)
{
    uint8_t b;
    int ok1, ok2;
    uint64_t cookie, vtable, meta, frame, word, obj;

    cookie = *(uint64_t *)((p4 & 0xfffffffffffffffeull) - 8);
    vtable = *(uint64_t *)(p3 + 0x10);
    meta   = *(uint64_t *)(vtable + -8);
    frame  = p3;
    skp10_sk_rt_slot_02();                    /* FUN_0034b7e4 */
    skp10_sk_rt_slot_04();                    /* FUN_0034b7b8 (skp10_DAT_00658c00 thunk) */
    obj = skp10_sk_swift_alloc_obj();         /* skp10_FUN_003722e4 */
    word = (uint64_t)(int)*(uint32_t *)(skp10_sk_rt_slot_04() + 0x30);
    {
        void (*mth)(uint64_t, uint64_t, uint64_t) =
            *(void (**)(uint64_t, uint64_t, uint64_t))(meta + 0x10);
        mth(word, p1, p3);
        mth(word + word, p2, p3);
    }
    ok1 = skp10_sk_check_one(word, 1, vtable);          /* FUN_000839f8 */
    if (ok1 == 1) {
        ok2 = skp10_sk_check_one(word + word, 1, vtable);
        b = (uint8_t)(ok2 == 1);
        if (!b) p3 = obj;
    } else {
        ((void (*)(uint64_t, uint64_t))skp10_sk_rt_slot_04())(word, p3);                /* call +0x10 mth */
        ok2 = skp10_sk_check_one(word + word, 1, vtable);
        if (ok2 == 1) {
            (*(void (**)(uint64_t, uint64_t))(meta + 8))(0, vtable);
            b = 0;
            p3 = obj;
        } else {
            (*(void (**)(void *, uint64_t, uint64_t))(meta + 0x20))(0, word + word, vtable);
            word = cookie;
            {
                uint64_t (*fp)(uint64_t, uint64_t, uint64_t, uint64_t) =
                    (uint64_t (*)(uint64_t, uint64_t, uint64_t, uint64_t))(uintptr_t)skp10_sk_rt_0014ae44(cookie);
                b = (uint8_t)fp(0, 0, vtable, word);
            }
            (*(void (**)(void *, uint64_t))(meta + 8))(0, vtable);
            (*(void (**)(uint64_t, uint64_t))(meta + 8))(0, vtable);
        }
    }
    (*(void (**)(uint64_t, uint64_t))(meta + 8))(word, p3);
    return b & 1;
}

/*--------------------------------------------------------------------*/
/* FUN_002655cc @ 0x002655cc   (est. sk_vspace_boot_enter)
 * Ghidra: void skp10_sk_rt_002655cc(undefined8, undefined8, undefined8)
 * Early boot / enter path: enables the runtime, reads the boot message block
 * (+0x10), and branches on a condition register. The ZR-true path is a
 * minimal teardown (skp10_sk_rt_00229a3c(0)); otherwise it drives a full entry
 * sequence and terminates with skp10_sk_rt_00229a3c(1).
 * Confidence: low.
 */
void sk_vspace_boot_enter(uint64_t p1, uint64_t p2, uint64_t p3)
{
    uint64_t msg;
    skp10_sk_rt_slot_05();                    /* FUN_0035a080 */
    msg = *(uint64_t *)(skp10_sk_rt_slot_00() + 0x10);
    skp10_sk_rt_slot_06();                    /* FUN_003499b4 */
    skp10_sk_rt_slot_03();                    /* FUN_0034c8e0 */
    skp10_sk_rt_slot_02();                    /* FUN_0034b7e4 */
    skp10_sk_rt_slot_07();                    /* FUN_003501b8 */
    skp10_sk_rt_slot_08();                    /* FUN_00349f3c */
    (*(void (**)(void))(0x0 + 0x10))();
    skp10_sk_rt_slot_06();
    if ((bool)0) {
        skp10_sk_rt_00229a3c(0);
    } else {
        skp10_sk_rt_slot_09();                /* FUN_00354810 */
        skp10_sk_rt_slot_0a();                /* FUN_00350470 */
        skp10_sk_rt_slot_0d();                /* FUN_00350878 */
        skp10_sk_rt_00229a3c(1);
        skp10_sk_rt_slot_0b(msg);             /* FUN_0031945c */
        skp10_sk_rt_slot_0c();                /* FUN_00351318 */
        skp10_sk_rt_slot_08();
        skp10_sk_rt_slot_0e();                /* FUN_0034da48 */
        skp10_sk_rt_slot_0d();
    }
}

/*--------------------------------------------------------------------*/
/* FUN_0026574c @ 0x0026574c   (est. sk_vspace_msg_dispatch)
 * Ghidra: undefined1 skp10_sk_rt_0026574c(undefined8, undefined8)
 * Thin wrapper over the Swift message dispatch FUN_00350884 with selector 1.
 * Confidence: medium (trivial wrapper).
 */
void sk_vspace_msg_dispatch(uint64_t p1, uint64_t p2)
{
    skp10_sk_swift_dispatch(p1, 1, p2);
}

/*--------------------------------------------------------------------*/
/* FUN_00265750 @ 0x00265750   (est. sk_vspace_msg_dispatch_b)
 * Ghidra: undefined1 skp10_sk_rt_00265750(undefined8, undefined8)
 * Duplicate wrapper of FUN_0026574c over FUN_00350884.
 * Confidence: medium.
 */
void sk_vspace_msg_dispatch_b(uint64_t p1, uint64_t p2)
{
    skp10_sk_swift_dispatch(p1, 1, p2);
}

/*--------------------------------------------------------------------*/
/* FUN_00265770 @ 0x00265770   (est. sk_vspace_msg_check)
 * Ghidra: bool skp10_sk_rt_00265770(undefined8, undefined8)
 * Wrapper over FUN_00350884 returning the negated dispatch result.
 * Confidence: medium.
 */
bool sk_vspace_msg_check(uint64_t p1, uint64_t p2)
{
    skp10_sk_swift_dispatch(p1, 1, p2);
    return true; /* ZR inverted by the dispatch's condition flag */
}

/*--------------------------------------------------------------------*/
/* FUN_00265774 @ 0x00265774   (est. sk_vspace_msg_check_b)
 * Ghidra: bool skp10_sk_rt_00265774(undefined8, undefined8)
 * Duplicate of FUN_00265770.
 * Confidence: medium.
 */
bool sk_vspace_msg_check_b(uint64_t p1, uint64_t p2)
{
    skp10_sk_swift_dispatch(p1, 1, p2);
    return true;
}

/*--------------------------------------------------------------------*/
/* FUN_00265794 @ 0x00265794   (est. sk_vspace_run_loop_a)
 * Ghidra: void skp10_sk_rt_00265794(void)
 * Run-loop iteration: builds a 16-byte key via FUN_00310d68, feeds it to
 * FUN_000a6f88, enters the runtime dispatch, and branches on ZR to either a
 * fast teardown (FUN_00353f88) or a slow path through the +0x20 method.
 * Confidence: low.
 */
void sk_vspace_run_loop_a(void)
{
    uint64_t k;
    skp10_sk_rt_slot_0f();                    /* FUN_00358fb4 */
    skp10_sk_rt_slot_10();                    /* FUN_00357748 */
    skp10_sk_rt_slot_11();                    /* FUN_003516cc */
    k = skp10_sk_rt_slot_12();                /* FUN_00310d68 */
    skp10_sk_rt_slot_13(k);                   /* FUN_000a6f88 */
    skp10_sk_rt_slot_14();                    /* FUN_0007c1a4 */
    skp10_sk_rt_slot_15();                    /* FUN_0034b05c */
    skp10_sk_rt_slot_16(*(uint64_t *)(skp10_sk_rt_slot_2f() + 0x10)); /* FUN_00350738 */
    skp10_sk_rt_slot_17();                    /* FUN_0035163c */
    skp10_sk_swift_dispatch(0, 0, 0);         /* FUN_00350884 */
    if ((bool)0) {
        skp10_sk_rt_slot_18();                /* FUN_00353f88 */
        skp10_sk_rt_slot_0d();
    } else {
        skp10_sk_rt_slot_19();                /* FUN_003511b4 */
        (*(void (**)(void))(skp10_sk_rt_slot_2f() + 0x20))();
    }
    skp10_sk_rt_slot_1a();                    /* FUN_00355f04 */
    skp10_sk_rt_slot_1b(0);                   /* FUN_00358fc8 */
}

/*--------------------------------------------------------------------*/
/* FUN_00265884 @ 0x00265884   (est. sk_vspace_run_loop_b)
 * Ghidra: void skp10_sk_rt_00265884(void)
 * Run-loop variant of FUN_00265794 with a different slow path
 * (FUN_0034b518 / FUN_0034c9e8 / FUN_000839d8).
 * Confidence: low.
 */
void sk_vspace_run_loop_b(void)
{
    uint64_t k;
    skp10_sk_rt_slot_0f();                    /* FUN_00358fb4 */
    skp10_sk_rt_slot_10();                    /* FUN_00357748 */
    skp10_sk_rt_slot_11();                    /* FUN_003516cc */
    k = skp10_sk_rt_slot_12();                /* FUN_00310d68 */
    skp10_sk_rt_slot_13(k);                   /* FUN_000a6f88 */
    skp10_sk_rt_slot_14();                    /* FUN_0007c1a4 */
    skp10_sk_rt_slot_15();                    /* FUN_0034b05c */
    skp10_sk_rt_slot_16(*(uint64_t *)(skp10_sk_rt_slot_2f() + 0x10)); /* FUN_00350738 */
    skp10_sk_rt_slot_17();                    /* FUN_0035163c */
    skp10_sk_swift_dispatch(0, 0, 0);         /* FUN_00350884 */
    if ((bool)0) {
        skp10_sk_rt_slot_18();                /* FUN_00353f88 */
        skp10_sk_rt_slot_0d();
    } else {
        skp10_sk_rt_0034b518();
        (*(void (**)(void))(skp10_sk_rt_slot_2f() + 0x20))();
        skp10_sk_rt_0034c9e8(0);
        skp10_sk_rt_000839d8();
    }
    skp10_sk_rt_slot_1a();                    /* FUN_00355f04 */
    skp10_sk_rt_slot_1b(0);                   /* FUN_00358fc8 */
}

/*--------------------------------------------------------------------*/
/* FUN_00265994 @ 0x00265994   (est. sk_vspace_release_op)
 * Ghidra: void skp10_sk_rt_00265994(undefined8, undefined8, undefined8)
 * Object release / unlock operation: acquires the object lock (FUN_00377824),
 * runs the runtime dispatch, and tears down with FUN_00359338 / FUN_0031d488 /
 * FUN_000dbdf4. Standard lock-and-release glue.
 * Confidence: low.
 */
void sk_vspace_release_op(uint64_t p1, uint64_t p2, uint64_t p3)
{
    skp10_sk_rt_00084220();
    skp10_sk_rt_00352914();
    skp10_sk_rt_00352894(p3);
    skp10_sk_rt_slot_00();                    /* FUN_0034a980 */
    skp10_sk_rt_003508d8();
    skp10_sk_object_lock(0, 0, 0, 0, 0);      /* FUN_00377824 */
    skp10_sk_rt_slot_35();                    /* FUN_00351f10 */
    skp10_sk_rt_slot_14();                    /* FUN_0007c1a4 */
    skp10_sk_rt_slot_15();                    /* FUN_0034b05c */
    skp10_sk_rt_0007b384();
    skp10_sk_rt_00350b30();
    skp10_sk_rt_0035072c();
    skp10_sk_rt_slot_39();                    /* FUN_0034c384 */
    skp10_sk_rt_slot_3a(0);                   /* FUN_0034c674 */
    skp10_sk_rt_slot_3b(p3);                  /* FUN_00359338 */
    skp10_sk_rt_slot_3c();                    /* FUN_0031d488 */
    skp10_sk_rt_slot_3d();                    /* FUN_000dbdf4 */
    skp10_sk_rt_slot_3e();                    /* FUN_00350810 */
    skp10_sk_rt_slot_0d();
    skp10_sk_rt_00084234(0);
}

/*--------------------------------------------------------------------*/
/* FUN_00265a74 @ 0x00265a74   (est. sk_vspace_release_op_b)
 * Ghidra: void skp10_sk_rt_00265a74(undefined8, undefined8, undefined8)
 * Per-CPU variant of the release op (starts with FUN_0008e518 = skp10_sk_cpu).
 * Confidence: low.
 */
void sk_vspace_release_op_b(uint64_t p1, uint64_t p2, uint64_t p3)
{
    skp10_sk_cpu();                           /* FUN_0008e518 */
    skp10_sk_rt_0035215c();
    skp10_sk_rt_slot_30();                    /* FUN_00358ef4 */
    skp10_sk_rt_slot_31();                    /* FUN_00349b3c */
    skp10_sk_rt_slot_32();                    /* FUN_00348f50 */
    skp10_sk_rt_slot_33(p3);                  /* FUN_00351ef8 */
    skp10_sk_rt_slot_00();                    /* FUN_0034a980 */
    skp10_sk_rt_slot_34();                    /* FUN_00351554 */
    skp10_sk_object_lock(0, 0, 0, 0, 0);      /* FUN_00377824 */
    skp10_sk_rt_slot_35();                    /* FUN_00351f10 */
    skp10_sk_rt_slot_14();                    /* FUN_0007c1a4 */
    skp10_sk_rt_slot_36();                    /* FUN_0034af20 */
    skp10_sk_rt_0007b384();
    skp10_sk_rt_slot_37();                    /* FUN_00351184 */
    skp10_sk_rt_slot_38();                    /* FUN_003510ac */
    skp10_sk_rt_slot_39();                    /* FUN_0034c384 */
    skp10_sk_rt_slot_3a();                    /* FUN_0034c674 */
    skp10_sk_rt_00350618(*(uint64_t *)(skp10_sk_rt_slot_2f() + 0x10));
    skp10_sk_rt_slot_3b();                    /* FUN_00359338 */
    skp10_sk_rt_003505f4();
    skp10_sk_rt_slot_3e();                    /* FUN_00350810 */
    skp10_sk_rt_slot_0d();
    skp10_sk_rt_0008e500(0);
}

/*--------------------------------------------------------------------*/
/* FUN_00265b90 @ 0x00265b90   (est. skp10_sk_vspace_dispatch_table)
 * Ghidra: void skp10_sk_rt_00265b90(undefined8, undefined8, undefined8)
 * Dispatch through an unrecovered jump table (UNRECOVERED_JUMPTABLE from
 * FUN_0014f810). The decompiler could not resolve the target; the jump is
 * treated as a call.
 * Confidence: low.
 * Notes: "Could not recover jumptable ... Too many branches" at 0x00265bd0.
 */
void skp10_sk_vspace_dispatch_table(uint64_t p1, uint64_t p2, uint64_t p3)
{
    skp10_sk_rt_0008409c();
    skp10_sk_rt_003564d0(p3);
    skp10_sk_rt_0034d190();                     /* UNRECOVERED_JUMPTABLE = skp10_sk_rt_0014f810() */
    (*(void (**)(void))skp10_sk_rt_0014f810())();
}

/*--------------------------------------------------------------------*/
/* FUN_00265e08 @ 0x00265e08   (est. skp10_sk_vspace_claim_region)
 * Ghidra: void skp10_sk_rt_00265e08(void)
 * Claim / validate a region for the current CPU. Starts with skp10_sk_cpu, reads
 * the capability (FUN_0008f6f4), and on failure (result&1==0) performs a
 * release path; on success a dispatch path. Ends with FUN_000839d8.
 * Confidence: low.
 */
void skp10_sk_vspace_claim_region(void)
{
    uint64_t cap, r, r2;
    skp10_sk_cpu();                           /* FUN_0008e518 */
    skp10_sk_rt_003531f0();
    skp10_sk_rt_slot_30();                    /* FUN_00358ef4 */
    skp10_sk_rt_slot_31();                    /* FUN_00349b3c */
    skp10_sk_rt_003489c0();
    skp10_sk_rt_0034b3d8();
    skp10_sk_rt_00351990();
    skp10_sk_rt_00350768();
    cap = skp10_sk_cap_get();                 /* FUN_0008f6f4 */
    skp10_sk_rt_0031d4e8();
    skp10_sk_rt_0034f654();
    skp10_sk_rt_00350b9c();
    skp10_sk_rt_0031d518(cap);
    r = skp10_sk_rt_0034cfe4();
    r2 = skp10_sk_rt_0034b3d8(r, cap);
    if ((r2 & 1) == 0) {
        skp10_sk_rt_0031d548(cap);
        skp10_sk_rt_0035066c();
        skp10_sk_rt_00350b9c();
        skp10_sk_rt_00350494(*(uint64_t *)(skp10_sk_rt_slot_2f() + 0x20));
    } else {
        skp10_sk_rt_0035060c(*(uint64_t *)(skp10_sk_rt_slot_2f() + 8));
    }
    skp10_sk_rt_0034dba8(r2, 1);
    skp10_sk_rt_000839d8();
    skp10_sk_rt_0008e500(0);
}

/*--------------------------------------------------------------------*/
/* FUN_00265f48 @ 0x00265f48   (est. sk_vspace_claim_region_b)
 * Ghidra: void skp10_sk_rt_00265f48(void)
 * Variant of FUN_00265e08.
 * Confidence: low.
 */
void sk_vspace_claim_region_b(void)
{
    uint64_t cap, r, r2;
    skp10_sk_cpu();                           /* FUN_0008e518 */
    skp10_sk_rt_003531f0();
    skp10_sk_rt_slot_31();                    /* FUN_00349b3c */
    skp10_sk_rt_00348a18();
    skp10_sk_rt_0034b758();
    skp10_sk_rt_00100c38();
    cap = skp10_sk_cap_get();                 /* FUN_0008f6f4 */
    skp10_sk_rt_0031d4e8();
    skp10_sk_rt_0035133c();
    skp10_sk_rt_003531cc();
    skp10_sk_rt_00350ba8();
    skp10_sk_rt_003508c0();
    skp10_sk_rt_0031d458(cap);
    skp10_sk_rt_00350648();
    skp10_sk_rt_00350ba8();
    skp10_sk_rt_0031d518(cap);
    r = skp10_sk_rt_0034bfa4();
    r2 = skp10_sk_rt_0034bfa4(r, cap);
    if ((r2 & 1) == 0) {
        skp10_sk_rt_0034f594(*(uint64_t *)(skp10_sk_rt_slot_2f() + 0x20));
    } else {
        skp10_sk_rt_0034da48();
    }
    skp10_sk_rt_00350774(0, 1);
    skp10_sk_rt_000839d8();
    skp10_sk_rt_0008e500(0);
}

/*--------------------------------------------------------------------*/
/* FUN_002660ac @ 0x002660ac   (est. sk_vspace_trap_alloc)
 * Ghidra: void skp10_sk_rt_002660ac(void)
 * Trap allocation: locks the object, allocates a capability slot
 * (FUN_00027754), and releases. Sequence of lock/dispatch/release.
 * Confidence: low.
 */
void sk_vspace_trap_alloc(void)
{
    skp10_sk_cpu();                           /* FUN_0008e518 */
    skp10_sk_rt_003531f0();
    skp10_sk_rt_00351468();
    skp10_sk_rt_00350bd8(0);
    skp10_sk_rt_slot_00();                    /* FUN_0034a980 */
    skp10_sk_object_lock(0, 0, 0, 0, 0);      /* FUN_00377824 */
    skp10_sk_rt_0034ab20();
    skp10_sk_rt_slot_14();                    /* FUN_0007c1a4 */
    skp10_sk_rt_slot_15();                    /* FUN_0034b05c */
    skp10_sk_rt_00027754();
    skp10_sk_rt_00355ab4();
    skp10_sk_rt_00349d80();
    skp10_sk_rt_00351118();
    skp10_sk_object_lock(0, 0, 0, 0, 0);      /* FUN_00377824 */
    skp10_sk_rt_00349e10();
    skp10_sk_rt_slot_14();                    /* FUN_0007c1a4 */
    skp10_sk_rt_slot_36();                    /* FUN_0034af20 */
    skp10_sk_rt_00100c38();
    skp10_sk_lock_ref(0);                     /* FUN_00377bec */
    skp10_sk_rt_00349370();
    skp10_sk_rt_0034cf44();
    skp10_sk_rt_0034d954();
    skp10_sk_rt_0035a3c4();
    skp10_sk_rt_00351dfc();
    skp10_sk_rt_0034e784();
    skp10_sk_rt_00352dd0();
    skp10_sk_rt_0035056c();
    skp10_sk_rt_0008e500(0);
}

/*--------------------------------------------------------------------*/
/* FUN_002661f4 @ 0x002661f4   (est. sk_vspace_cap_ops)
 * Ghidra: void skp10_sk_rt_002661f4(undefined8, undefined8, undefined8, undefined8)
 * Capability operation dispatch: reads the object, locks, runs two method
 * dispatches through FUN_0007b384, sends a message (FUN_00350780), then
 * dispatches the +8 method twice and rebuilds a key via FUN_0034d2f4.
 * Confidence: low.
 */
void sk_vspace_cap_ops(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4)
{
    skp10_sk_cpu();                           /* FUN_0008e518 */
    skp10_sk_rt_00351ef8(p3);
    skp10_sk_rt_slot_00();                    /* FUN_0034a980 */
    skp10_sk_rt_003514a0();
    skp10_sk_object_lock(0, 0, 0, 0, 0);      /* FUN_00377824 */
    skp10_sk_rt_00348d64();
    skp10_sk_rt_00348a80();
    skp10_sk_rt_0034a464();
    skp10_sk_rt_0034b4c0();
    skp10_sk_rt_0007b384();
    skp10_sk_rt_0035190c();
    skp10_sk_rt_0034b3c8();
    (*(void (**)(void))(skp10_sk_rt_slot_2f() + 8))();
    skp10_sk_rt_0035190c();
    skp10_sk_rt_00350780(p4);
    skp10_sk_rt_001679fc();
    skp10_sk_rt_00351184();
    skp10_sk_rt_00100c38();
    skp10_sk_rt_00351280();
    skp10_sk_rt_00350518();
    skp10_sk_rt_000e72b0();
    skp10_sk_rt_0034e784();
    skp10_sk_rt_0034d2f4();
    skp10_sk_rt_slot_2c(p3);                  /* FUN_0034e784 */
    skp10_sk_rt_0008e500(0);
}

/*--------------------------------------------------------------------*/
/* FUN_0026638c @ 0x0026638c   (est. skp10_sk_vspace_cap_ops_b)
 * Ghidra: void skp10_sk_rt_0026638c(undefined8, undefined8, undefined8, undefined8,
 *                            code *param_5)
 * Capability dispatch variant taking a callback (param_5); same structure
 * as FUN_002661f4.
 * Confidence: low.
 */
void skp10_sk_vspace_cap_ops_b(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4,
                         void (*fn)(void))
{
    skp10_sk_cpu();                           /* FUN_0008e518 */
    skp10_sk_rt_00352ee4(p3);
    skp10_sk_rt_slot_00();                    /* FUN_0034a980 */
    skp10_sk_rt_00352864();
    skp10_sk_object_lock(0, 0, 0, 0, 0);      /* FUN_00377824 */
    skp10_sk_rt_00348d4c();
    skp10_sk_rt_00348abc();
    skp10_sk_rt_0034b308();
    skp10_sk_rt_0034b758();
    skp10_sk_rt_0007b384();
    skp10_sk_rt_003514d0();
    skp10_sk_rt_0034b3c8();
    (*(void (**)(void))(skp10_sk_rt_slot_2f() + 8))();
    skp10_sk_rt_003514d0();
    skp10_sk_rt_00350780(p4);
    (*fn)();
    skp10_sk_rt_0035133c();
    skp10_sk_rt_003508f0();
    skp10_sk_rt_0034cfd4();
    skp10_sk_rt_00350618();
    skp10_sk_rt_00350a34();
    skp10_sk_rt_0034e784();
    skp10_sk_rt_00354d94();
    skp10_sk_rt_0034d334();
    skp10_sk_rt_0008e500(0);
}

/*--------------------------------------------------------------------*/
/* FUN_00266504 @ 0x00266504   (est. skp10_sk_vspace_range_load)
 * Ghidra: void skp10_sk_rt_00266504(byte *param_1, long param_2)
 * Loads a multi-word integer from a byte buffer with Swift-style bounds and
 * fatal-error checks. For n < 16 builds the low word byte-by-byte; for n >= 9
 * builds the high word from param_1+8. Range/index checks trigger
 * "Fatal error" / "Index out of range" / "Swift.Range" via FUN_001afe4c.
 * Returns a tagged {value, tag} pair. This is the cL4/Swift integer load.
 * Confidence: medium (string-verified fatal-error paths).
 * Notes: skp10_s_Range_requires_lowerBound_005cda00, skp10_s_Index_out_of_range_005cd940,
 * skp10_s_Fatal_error_005accd0, skp10_s_Swift_Range_swift_005cda30.
 */
void skp10_sk_vspace_range_load(uint8_t *bytes, long n)
{
    uint64_t lo = 0, hi = 0, tag;
    long i;

    if (n == 0) {
        lo = 0;
        tag = 0xe000000000000000ull;
        sk_vspace_object_create();      /* skp10_sk_rt_002676bc(lo, tag) */
        return;
    }
    if (n < 0x10) {
        long cnt = (n > 8) ? 8 : n;
        if (n < 0) {
            skp10_sk_rt_001afe4c(skp10_s_Fatal_error_005accd0, 0xb, 2,
                         skp10_s_Range_requires_lowerBound_005cda00, 0x27, 2,
                         skp10_s_Swift_Range_swift_005cda30, 0x11, 2, 0x2f9, 1);
        }
        lo = 0;
        for (i = 0; i < cnt; i++) {
            lo = (uint64_t)bytes[i] << ((i * 8) & 0x38) | lo;
        }
        if (n < 9) {
            hi = 0;
        } else {
            if (n - 8 <= n - 9) {
                skp10_sk_rt_001afe4c(skp10_s_Fatal_error_005accd0, 0xb, 2,
                             skp10_s_Index_out_of_range_005cd940, 0x12, 2,
                             skp10_s_Swift_Range_swift_005cda30, 0x11, 2, 0x136, 1);
            }
            hi = 0;
            for (i = 0; i < n - 8; i++) {
                hi = (uint64_t)bytes[8 + i] << ((i * 8) & 0x3f) | hi;
            }
        }
        tag = 0xe000000000000000ull;
        if (((hi | lo) & 0x8080808080808080ull) != 0) {
            tag = 0xa000000000000000ull;
        }
        hi = tag | ((uint64_t)n << 0x38) | hi;
    } else {
        uint64_t obj = skp10_sk_rt_002a4b90(bytes, n, n, 1);
        lo = *(uint64_t *)(obj + 0x18);
        hi = obj;
    }
    sk_vspace_object_create(lo, hi);    /* FUN_002676bc */
    skp10_sk_msg_dispatch(hi);
}

/*--------------------------------------------------------------------*/
/* FUN_00266688 @ 0x00266688   (est. sk_vspace_init_a)
 * Ghidra: void skp10_sk_rt_00266688(void)
 * Initialization glue: FUN_002a20cc + FUN_002b79cc then message dispatch.
 * Confidence: low.
 */
void sk_vspace_init_a(void)
{
    skp10_sk_rt_002a20cc();
    skp10_sk_rt_002b79cc();
    skp10_sk_msg_dispatch(skp10_sk_swift_msg());
}

/*--------------------------------------------------------------------*/
/* FUN_002666b8 @ 0x002666b8   (est. sk_vspace_init_b)
 * Ghidra: void skp10_sk_rt_002666b8(void)
 * Initialization glue variant ending in message dispatch.
 * Confidence: low.
 */
void sk_vspace_init_b(void)
{
    skp10_sk_rt_00350a10();
    skp10_sk_rt_002a20cc();
    skp10_sk_rt_00350f0c();
    skp10_sk_rt_0031b900();
    skp10_sk_rt_0034b6b8();
    skp10_sk_rt_slot_0d();
    skp10_sk_msg_dispatch();
}

/*--------------------------------------------------------------------*/
/* FUN_0026670c @ 0x0026670c   (est. sk_vspace_load_int)
 * Ghidra: undefined1 [16] skp10_sk_rt_0026670c(ulong *param_1, long param_2)
 * Sign/zero-extending load of a 1/2/4/8-byte integer from *param_1, selected
 * by the type tag at *(param_2-8)+0x40. Returns a 16-byte {value, tag} pair.
 * Confidence: medium (clear switch on element size).
 */
uint64_t sk_vspace_load_int(uint64_t *src, long type_info)
{
    uint64_t tag = *(uint64_t *)(*(uint64_t *)(type_info + -8) + 0x40);
    switch (tag) {
    case 1:  return (uint64_t)(int8_t)*(uint8_t *)src;
    case 2:  return (uint64_t)(uint16_t)*(uint16_t *)src;
    case 4:  return (uint64_t)(uint32_t)*(uint32_t *)src;
    case 8:  return *src;
    default: return 0; /* sizes 3,5,6,7 + out-of-range => nil tag */
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002667a8 @ 0x002667a8   (est. sk_vspace_entry_dispatch)
 * Ghidra: void skp10_sk_rt_002667a8(undefined8, undefined8, undefined8, ulong,
 *                            undefined8*, undefined8, undefined8)
 * The largest function in the slice (0x6d bytes of table + 0x63f body): a
 * Swift-style big dispatch switch on the type-tag byte (cases 1..9 plus
 * default) for vspace entry handling. Each case walks a bitmap/entry table
 * (+0x30/+0x38), builds tagged values (0xe000000000000000 nil / 0x6000...),
 * performs range checks with fatal-error traps, and calls into the
 * out-of-range runtime. Because the decompiler collapsed all branches to
 * register-aliased indirect calls, only the structural shape is faithfully
 * reconstructable.
 * Confidence: low.
 */
void sk_vspace_entry_dispatch(uint64_t p1, uint64_t p2, uint64_t p3,
                              uint64_t p4, uint64_t *p5, uint64_t p6, uint64_t p7)
{
    uint64_t cpu = skp10_sk_cpu();
    uint8_t tag = *(uint8_t *)(cpu + 0x10);
    uint64_t i6;
    (void)p5;
    if (9 < tag) {
        /* case-group 1: entry teardown / re-check */
        skp10_sk_rt_00361528(cpu, 1);
        if (0 <= 0) {
            skp10_sk_rt_00357b7c();
            if ((int64_t)skp10_sk_rt_002a218c() < 0) {
                skp10_sk_rt_00353b4c();
                skp10_sk_rt_003507bc();
                skp10_sk_rt_00352578();
                skp10_sk_rt_002a2748();
                skp10_sk_rt_003517c0();
            }
        }
        *(uint32_t *)(0 - 0x10) = 1;
        skp10_sk_rt_00348b7c(0x582);
        skp10_sk_rt_00349a04();
        skp10_sk_rt_003524c8();
        skp10_sk_swift_fatal();
    }
    switch (tag) {
    case 1: case 5: case 6: case 7:
        /* same as the >9 group */
        skp10_sk_rt_00361528(cpu, 1);
        *(uint32_t *)(0 - 0x10) = 1;
        skp10_sk_rt_00348b7c(0x582);
        skp10_sk_rt_00349a04();
        skp10_sk_rt_003524c8();
        skp10_sk_swift_fatal();
        break;
    case 2:
        /* entry-2 path: build key, dispatch, teardown */
        skp10_sk_rt_00351274();
        i6 = skp10_sk_rt_003a0b04();
        if (i6 == 0) {
            skp10_sk_rt_003573f4(cpu, 0, p4 & 1);
            skp10_sk_rt_002673dc();
            skp10_sk_rt_00351274();
            skp10_sk_rt_0026670c();
            skp10_sk_rt_00351db4();
            if (p4 & 1) {
                skp10_sk_rt_00352480(cpu, p3);
                skp10_sk_rt_002673dc();
                skp10_sk_rt_0034fb28();
                skp10_sk_rt_0031b900();
                skp10_sk_rt_00351318();
            }
        }
        break;
    case 3:
        /* entry-3 path: bitmap/entry table walk with range checks */
        skp10_sk_rt_003567f8();
        skp10_sk_rt_00350744();
        skp10_sk_rt_00354f1c();
        skp10_sk_rt_0031b900(p7);
        skp10_sk_rt_00351450();
        skp10_sk_msg_dispatch(p5);
        skp10_sk_rt_000027e8();
        skp10_sk_rt_0031b900();
        skp10_sk_swift_fatal();
        break;
    case 4:
        /* entry-4 path: key teardown */
        skp10_sk_rt_001ae82c((uint64_t*)sk_scratch, 0);
        if (0 != 0) {
            skp10_sk_rt_0034d274((uint64_t*)sk_scratch);
            skp10_sk_rt_003573f4();
            skp10_sk_rt_003526ec();
        } else {
            skp10_sk_rt_003588a0();
            skp10_sk_rt_00344e54();
            skp10_sk_rt_00353830();
            skp10_sk_rt_003540ac();
            skp10_sk_rt_003573f4(0);
        }
        break;
    case 8:
        sk_vspace_commit(cpu, p3, p4 & 1);
        skp10_sk_rt_00355fa0(&skp10_DAT_005d3bb4);
        skp10_sk_rt_0034bd90();
        skp10_sk_rt_0031b900();
        skp10_sk_rt_00351318();
        break;
    case 9:
        skp10_sk_rt_00350ad0(0);
        skp10_sk_rt_00354d80();
        skp10_sk_rt_00355bf4();
        skp10_sk_rt_003513d8();
        if (skp10_sk_rt_00365b6c() != 0) {
            skp10_sk_rt_003573f4(0, 0, p4 & 1);
            skp10_sk_rt_002673dc();
            break;
        }
        if ((skp10_sk_rt_003a0c90(cpu) != 0) && (skp10_sk_rt_001e9f14(), 0 != 0)) {
            skp10_sk_rt_003562d4();
            break;
        }
        skp10_sk_rt_00351d24();
        skp10_sk_rt_00361528();
        break;
    default:
        /* default: full entry processing loop */
        skp10_sk_rt_002673dc(cpu, p3, p4 & 1, p6, p7);
        skp10_sk_rt_003567f8();
        skp10_sk_rt_00350744();
        skp10_sk_rt_0031b900(p7);
        skp10_sk_rt_003524a4();
        skp10_sk_rt_003515fc();
        skp10_sk_msg_dispatch(0);
        skp10_sk_rt_000027e8();
        skp10_sk_rt_0007c198();
        /* walk loop over entries */
        while (true) {
            skp10_sk_rt_00310d98((uint64_t*)sk_scratch, (uint64_t*)sk_scratch);
            skp10_sk_rt_00350944();
            skp10_sk_rt_00353504(0, p3);
            skp10_sk_rt_002060d4();
        }
        break;
    }
    skp10_sk_msg_dispatch(p5);
}

/*--------------------------------------------------------------------*/
/* FUN_002673dc @ 0x002673dc   (est. sk_vspace_commit)
 * Ghidra: void skp10_sk_rt_002673dc(undefined8, undefined8, undefined8)
 * Commit / validate a vspace region: takes the IRQ state (FUN_00357ca0),
 * resolves the capability (FUN_00352700), validates via FUN_00361528
 * (fatal on failure), builds a tagged value (0xe000000000000000 nil or
 * 0xe000... | size<<0x38), and commits with FUN_00357c44.
 * Confidence: low.
 */
void sk_vspace_commit(uint64_t p1, uint64_t p2, uint64_t p3)
{
    uint64_t val, sz;
    skp10_sk_spin_irqsave(0);                 /* FUN_00357ca0 */
    val = skp10_sk_rt_00352700();
    skp10_sk_rt_00361528(val, p3);
    if ((int64_t)skp10_sk_swift_msg() < 0) {
        skp10_sk_rt_0034846c();
        skp10_sk_swift_fatal();
    }
    skp10_sk_rt_00356e28();
    if ((int64_t)skp10_sk_rt_002a218c() < 0) {
        skp10_sk_rt_00353b4c();
        skp10_sk_rt_00351384();
        skp10_sk_rt_00352578();
        skp10_sk_rt_002a2748();
        skp10_sk_rt_00351f28();
    } else {
        sz = skp10_sk_rt_00352700();
        if (sz == 0) {
            sz = 0xe000000000000000ull;
        } else if (sz < 0x10) {
            skp10_sk_rt_00355300(sz - 8);
            sz = 0xe000000000000000ull | (sz << 0x38);
        } else {
            skp10_sk_rt_00351384();
            sz = skp10_sk_rt_002a4b90();
        }
        val = sz;
    }
    skp10_sk_rt_00354da0();
    skp10_sk_rt_000aa47c();
    skp10_sk_rt_slot_0d();
    skp10_sk_rt_00357c44(val, 0);
    skp10_sk_msg_dispatch();
}

/*--------------------------------------------------------------------*/
/* FUN_00267510 @ 0x00267510   (est. sk_vspace_region_check)
 * Ghidra: void skp10_sk_rt_00267510(void)
 * Region permission / range check with Swift fatal-error traps. Reads a
 * region index (FUN_00167404), compares against the tagged bounds, walks a
 * table (FUN_0028e8c0), and validates entries (FUN_002a9ba8). On a match
 * commits via thunk_FUN_002a2698. Range mismatches hit fatal-error paths.
 * Confidence: low.
 */
void sk_vspace_region_check(void)
{
    uint64_t reg, type_bits, tag;
    skp10_sk_rt_00041138();
    skp10_sk_rt_00351708();
    reg = skp10_sk_rt_00167404();
    type_bits = reg >> 8 & 0x3f;
    tag = 0;
    while (true) {
        if (type_bits == 0) {
            if (reg >> 0xe != 0) {
                if ((reg >> 0x3c & 1) == 0) {
                    skp10_sk_rt_0006b6f4();
                    skp10_sk_rt_002a9ba8();
                    skp10_sk_rt_00351790();
                }
                skp10_sk_rt_00084174();
                skp10_sk_rt_003520dc();
                if ((int64_t)skp10_sk_rt_0028e8c0() >= 0) {
                    skp10_sk_rt_00348e48();
                    skp10_sk_rt_001e4cbc();
                    skp10_sk_rt_0034de9c();
                    skp10_sk_rt_0035847c();
                    skp10_sk_rtt_002a2698();
                    return;
                }
            }
            skp10_sk_rt_003481fc();
            skp10_sk_swift_fatal();
        }
        skp10_sk_rt_002bbcd8();
        skp10_sk_rt_0006b6f4();
        tag = skp10_sk_rt_002a9ba8();
        if (tag == 0) {
            skp10_sk_rt_00347f2c();
            skp10_sk_swift_fatal();
        }
        if ((*(uint16_t *)(tag + 0) == 0xa0d) ||
            (*(uint16_t *)(tag + 0) & 0x8080)) {
            skp10_sk_rt_0034bfb4();
            skp10_sk_rt_002c6d00();
            continue;
        }
        break;
    }
    skp10_sk_rt_00348e48();
    skp10_sk_rt_001e4cbc();
    skp10_sk_rt_0034de9c();
    skp10_sk_rt_0035847c();
    skp10_sk_rtt_002a2698();
}

/*--------------------------------------------------------------------*/
/* FUN_002676b4 @ 0x002676b4   (est. skp10_sk_vspace_lock_enter)
 * Ghidra: thunk_FUN_003d31d8 at 002676b4
 * Thunk forwarding to FUN_003d31d8 with a fixed cookie argument.
 * Confidence: high (thunk identity).
 */
void skp10_sk_vspace_lock_enter(void)
{
    skp10_sk_swift_retain(0xb4000769f84206c9ull); /* thunk_FUN_00054464 */
}

/*--------------------------------------------------------------------*/
/* FUN_002676b8 @ 0x002676b8   (est. skp10_sk_vspace_lock_leave)
 * Ghidra: thunk_FUN_003d31e8 at 002676b8
 * Thunk forwarding to FUN_003d31e8.
 * Confidence: high (thunk identity).
 */
void skp10_sk_vspace_lock_leave(void)
{
    skp10_sk_swift_release(0xb4000769f84206c9ull); /* thunk_FUN_0005453c */
}

/*--------------------------------------------------------------------*/
/* FUN_002676bc @ 0x002676bc   (est. sk_vspace_object_create)
 * Ghidra: void skp10_sk_rt_002676bc(void)
 * Vspace object creation/initialization. Allocates via thunk_FUN_0036b270,
 * handles tagged-object bits (>>0x3c&1, >>0x3d&1), resolves the capability
 * via FUN_002a9ba8 / FUN_00356364, and calls FUN_003d30b0 to install it.
 * Confidence: medium (opaque register/tag-bit forwarding; structure and
 *   arg-forwarding verified against fresh decompile — dropped args and
 *   fabricated branch removed).
 */
void sk_vspace_object_create()   /* empty parens: opaque Swift, callers forward regs */
{
    uint64_t a_lo = 0, a_hi = 0;       /* auVar2 16-byte pair */
    uint64_t st40_lo = 0, st40_hi = 0; /* auStack_40 (opaque stack buffer) */
    uint64_t s19 = 0, s20 = 0, s21 = 0;/* unaff_x19/x20/x21 (preserved regs) */
    uint64_t st;

    (void)st40_lo; (void)st40_hi; (void)s21;
    st = skp10_sk_rt_0034f064();       /* extraout_x8 status */
    if (st != 0) {
        skp10_sk_rt_003503c0();
        a_lo = (uint64_t)skp10_sk_alloc_pages(0, 0); /* thunk_FUN_0036b270 */
        if ((s19 >> 0x3c & 1) != 0) {  /* unaff_x19 tag bit */
            skp10_sk_rt_0007c1c4();
            skp10_sk_rt_0001d4a0();
            skp10_sk_rt_0034bd90();
            a_lo = skp10_sk_rt_003a25d4(); /* FUN_003a25d4 -> pair (lo) */
            s19 = s21;
        }
        if ((s19 >> 0x3d & 1) == 0) {  /* unaff_x19 tag bit */
            if ((s20 >> 0x3c & 1) == 0) {  /* unaff_x20 tag bit */
                skp10_sk_rt_0007c1c4();
                a_lo = skp10_sk_rt_002a9ba8();
                if (a_lo == 0) {
                    skp10_sk_rt_00348898(1);
                    skp10_sk_rt_0034a2f8();
                    skp10_sk_swift_fatal();  /* FUN_001afe4c, noreturn */
                }
            } else {
                a_lo = skp10_sk_rt_00356364();      /* uVar1 */
                a_hi = s20 & 0xffffffffffff;        /* auVar2._8_8_ */
            }
            skp10_sk_runtime_install(a_lo, 1, a_hi); /* FUN_003d30b0 */
            skp10_sk_msg_dispatch(s19);              /* FUN_003a25d4 */
            return;
        }
        skp10_sk_rt_003584f8(a_lo, a_hi, s19 >> 0x38 & 0xf);
        skp10_sk_runtime_install(st40_lo, 1);        /* FUN_003d30b0(auStack_40,1) */
        skp10_sk_msg_dispatch(s19);                  /* FUN_003a25d4 */
    }
}

/*--------------------------------------------------------------------*/
/* FUN_00267798 @ 0x00267798   (est. sk_vspace_lock_enter_fwd)
 * Ghidra: void skp10_sk_rt_00267798(void)
 * Forwarder to FUN_002676b4 (lock enter).
 * Confidence: medium.
 */
void sk_vspace_lock_enter_fwd(void) { skp10_sk_vspace_lock_enter(); }

/*--------------------------------------------------------------------*/
/* FUN_0026779c @ 0x0026779c   (est. sk_vspace_lock_enter_fwd2)
 * Ghidra: void skp10_sk_rt_0026779c(void)
 * Forwarder to FUN_002676b4.
 * Confidence: medium.
 */
void sk_vspace_lock_enter_fwd2(void) { skp10_sk_vspace_lock_enter(); }

/*--------------------------------------------------------------------*/
/* FUN_002677b0 @ 0x002677b0   (est. sk_vspace_lock_leave_fwd)
 * Ghidra: void skp10_sk_rt_002677b0(void)
 * Forwarder to FUN_002676b8 (lock leave).
 * Confidence: medium.
 */
void sk_vspace_lock_leave_fwd(void) { skp10_sk_vspace_lock_leave(); }

/*--------------------------------------------------------------------*/
/* FUN_002677b4 @ 0x002677b4   (est. sk_vspace_lock_leave_fwd2)
 * Ghidra: void skp10_sk_rt_002677b4(void)
 * Forwarder to FUN_002676b8.
 * Confidence: medium.
 */
void sk_vspace_lock_leave_fwd2(void) { skp10_sk_vspace_lock_leave(); }

/*--------------------------------------------------------------------*/
/* FUN_002677c8 @ 0x002677c8   (est. sk_vspace_object_create_fwd)
 * Ghidra: void skp10_sk_rt_002677c8(void)
 * Forwarder to FUN_002676bc.
 * Confidence: medium.
 */
void sk_vspace_object_create_fwd(void) { sk_vspace_object_create(); }

/*--------------------------------------------------------------------*/
/* FUN_002677cc @ 0x002677cc   (est. sk_vspace_object_create_fwd2)
 * Ghidra: void skp10_sk_rt_002677cc(void)
 * Forwarder to FUN_002676bc.
 * Confidence: medium.
 */
void sk_vspace_object_create_fwd2(void) { sk_vspace_object_create(); }

/*--------------------------------------------------------------------*/
/* FUN_002677e4 @ 0x002677e4   (est. skp10_sk_vspace_ipc_transition)
 * Ghidra: thunk_FUN_002acbb8 at 002677e4
 * IPC state transition: dereferences a 2-word stack record, validates the
 * pair via FUN_003598a0, and either fast-paths (alloc + message dispatch +
 * store) or falls to FUN_00267820.
 * Confidence: low.
 */
void skp10_sk_vspace_ipc_transition()
{
    uint64_t *rec = (uint64_t *)0;   /* unaff_x20 stack record */
    uint64_t u1 = rec[1];
    skp10_sk_rt_0008409c();
    skp10_sk_rt_003598a0(*rec);
    if ((skp10_sk_swift_msg() == 0) &&
        (((skp10_sk_swift_msg() & (u1 ^ 0xffffffffffffffffull)) >> 0x3d & 1) == 0)) {
        skp10_sk_alloc_pages(0, 0);           /* thunk_FUN_0036b270 */
        skp10_sk_msg_dispatch(u1);
        *rec = 0;
        rec[1] = 0;
        return;
    }
    skp10_sk_rt_00084180();
    skp10_sk_vspace_ipc_transition_slow();
}

/*--------------------------------------------------------------------*/
/* FUN_00267820 @ 0x00267820   (est. skp10_sk_vspace_ipc_transition_slow)
 * Ghidra: void skp10_sk_rt_00267820(void)
 * Slow IPC transition: validates the entry (>>0x3d&1 and tag comparisons),
 * and on success stores the new pair; otherwise falls to FUN_002a4c98.
 * Confidence: low.
 */
void skp10_sk_vspace_ipc_transition_slow(void)
{
    uint64_t *rec = (uint64_t *)0;
    uint64_t u1 = rec[1];
    skp10_sk_rt_0008409c();
    if ((u1 >> 0x3d & 1) == 0) {
        skp10_sk_rt_0034a798();
    } else if (((0 >> 0x3d & 1) != 0) && (skp10_sk_rt_003495a8(*rec, u1), (bool)0)) {
        skp10_sk_rt_003517c0();
        skp10_sk_msg_dispatch(u1);
        *rec = 0;
        rec[1] = 0;
        return;
    }
    skp10_sk_rt_0034c0a4();
    skp10_sk_rt_002a4c98();
}

/*--------------------------------------------------------------------*/
/* FUN_002678b4 @ 0x002678b4   (est. sk_vspace_teardown_a)
 * Ghidra: void skp10_sk_rt_002678b4(void)
 * Teardown glue: runtime dispatch sequence.
 * Confidence: low.
 */
void sk_vspace_teardown_a(void)
{
    skp10_sk_rt_0034d654();
    skp10_sk_rt_0031b900(0);
    skp10_sk_rt_000dbdf4();
    skp10_sk_rt_00356ad0();
    skp10_sk_rt_0035063c();
    skp10_sk_rt_slot_0d();
}

/*--------------------------------------------------------------------*/
/* FUN_00267914 @ 0x00267914   (est. sk_vspace_irq_sync)
 * Ghidra: void skp10_sk_rt_00267914(void)
 * IRQ save / restore wrapper: FUN_00357cb4 ... FUN_00357c74 around a
 * dispatch sequence, ending with message dispatch.
 * Confidence: low.
 */
void sk_vspace_irq_sync(void)
{
    uint64_t flags;
    skp10_sk_spin_irqsave(&flags);            /* FUN_00357cb4 */
    skp10_sk_rt_00352c34();
    skp10_sk_rt_003528cc();
    skp10_sk_rt_00255738();
    skp10_sk_rt_00354da0();
    skp10_sk_rt_0034ef78();
    skp10_sk_rt_slot_0d();
    skp10_sk_irqrestore(flags);               /* FUN_00357c74 */
    skp10_sk_msg_dispatch();
}

/*--------------------------------------------------------------------*/
/* FUN_00267994 @ 0x00267994   (est. sk_vspace_tcb_swap)
 * Ghidra: void skp10_sk_rt_00267994(undefined8, undefined8, long param_3)
 * TCB field swap: reads two slots from the current TCB (+0x20/+0x28 offsets
 * of param_3 context) and dispatches through FUN_00354da0 / FUN_00100efc.
 * Confidence: low.
 */
void sk_vspace_tcb_swap(uint64_t p1, uint64_t p2, long p3)
{
    uint64_t a, b;
    void *tcb = skp10_sk_current_tcb();       /* FUN_000867ec */
    a = skp10_sk_rt_00354da0(*(uint64_t *)(p3 + 0x20));
    skp10_sk_rt_00100efc(a, 0, *(uint64_t *)((uint64_t)tcb + 0x10));
    skp10_sk_rt_slot_0d();
    b = skp10_sk_rt_00354da0(*(uint64_t *)((uint64_t)tcb + 0x28));
    skp10_sk_rt_00100efc(b, 0, *(uint64_t *)((uint64_t)tcb + 0x18));
    skp10_sk_rt_slot_0d();
}

/*--------------------------------------------------------------------*/
/* FUN_00267a0c @ 0x00267a0c   (est. sk_vspace_tcb_swap_b)
 * Ghidra: void skp10_sk_rt_00267a0c(void)
 * TCB field swap variant using indirect dispatch (FUN_0031b8d0).
 * Confidence: low.
 */
void sk_vspace_tcb_swap_b(void)
{
    skp10_sk_rt_00358144();
    (*(void (**)(uint64_t))skp10_sk_rt_0031b8d0())(*(uint64_t *)(0 + 0x10));
    {
        uint64_t u = *(uint64_t *)(0 + 0x28);
        (*(void (**)(uint64_t, uint64_t))skp10_sk_rt_0031b8d0(u))(*(uint64_t *)(0 + 0x18), u);
    }
}

/*--------------------------------------------------------------------*/
/* FUN_00267a74 @ 0x00267a74   (est. sk_vspace_obj_dispatch)
 * Ghidra: void skp10_sk_rt_00267a74(long param_1)
 * Object dispatch on two method slots (+0x18/+0x28 and +0x10/+0x20) via
 * indirect FUN_0034310c jump table.
 * Confidence: low.
 */
void sk_vspace_obj_dispatch(long p1)
{
    uint64_t u = *(uint64_t *)(p1 + 0x28);
    (*(void (**)(uint64_t, uint64_t))skp10_sk_rt_0034310c(u))(*(uint64_t *)(p1 + 0x18), u);
    u = *(uint64_t *)(p1 + 0x20);
    /* UNRECOVERED_JUMPTABLE = skp10_sk_rt_0034310c(u) — indirect dispatch */
    (*(void (**)(uint64_t, uint64_t))skp10_sk_rt_0034310c(u))(*(uint64_t *)(p1 + 0x10), u);
}

/*--------------------------------------------------------------------*/
/* FUN_00267af8 @ 0x00267af8   (est. sk_vspace_svc_call)
 * Ghidra: void skp10_sk_rt_00267af8(undefined8, undefined8, undefined8)
 * SVC call dispatch through an unrecovered jump table (FUN_00310fc4).
 * Confidence: low.
 */
void sk_vspace_svc_call(uint64_t p1, uint64_t p2, uint64_t p3)
{
    skp10_sk_rt_00349ef4();
    skp10_sk_rt_0034b128();
    /* UNRECOVERED_JUMPTABLE = (code *)skp10_sk_rt_00310fc4(p3) — indirect dispatch */
    (*(void (**)(void))skp10_sk_rt_00310fc4(p3))();
}

/*--------------------------------------------------------------------*/
/* FUN_00267ba0 @ 0x00267ba0   (est. skp10_sk_vspace_region_compare)
 * Ghidra: bool skp10_sk_rt_00267ba0(void)
 * Compares two region values returned by FUN_00310f94; returns whether the
 * first is less than the second.
 * Confidence: low.
 */
bool skp10_sk_vspace_region_compare(void)
{
    uint64_t a, b;
    skp10_sk_rt_0034b470();
    skp10_sk_rt_00355cbc();
    skp10_sk_rt_00084180();
    a = (*(uint64_t (**)(void))skp10_sk_rt_00310f94())();
    skp10_sk_rt_0034f294();
    b = (*(uint64_t (**)(void))skp10_sk_rt_00310f94())();
    return a < b;
}

/*--------------------------------------------------------------------*/
/* FUN_00267c00 @ 0x00267c00   (est. sk_vspace_region_cursor)
 * Ghidra: void skp10_sk_rt_00267c00(void)
 * Region cursor advance: reads a cursor value (FUN_00310f94), adds the
 * element stride (+0x48) and dispatches.
 * Confidence: low.
 */
void sk_vspace_region_cursor(void)
{
    uint64_t v, stride;
    skp10_sk_rt_0034bd6c();
    skp10_sk_rt_00310f94();
    skp10_sk_rt_0034bcf0();
    v = (*(uint64_t (**)(void))skp10_sk_rt_slot_0d())();
    skp10_sk_rt_0034ce98();
    skp10_sk_object_lock(0, 0, 0, 0, 0);      /* FUN_00377824 */
    skp10_sk_rt_00351f10();
    stride = *(uint64_t *)(skp10_sk_rt_slot_2f() + 0x48);
    skp10_sk_rt_00353300();
    skp10_sk_rt_0034d334(v + stride);
    skp10_sk_rt_slot_0d();
}

/*--------------------------------------------------------------------*/
/* FUN_00267c80 @ 0x00267c80   (est. sk_vspace_region_cursor_b)
 * Ghidra: void skp10_sk_rt_00267c80(void)
 * Region cursor variant dispatching through FUN_00310fc4 on the stride.
 * Confidence: low.
 */
void sk_vspace_region_cursor_b(void)
{
    skp10_sk_rt_0034bd6c();
    skp10_sk_rt_00310f94();
    skp10_sk_rt_0034bcf0();
    skp10_sk_rt_slot_0d();
    skp10_sk_rt_0034ce98();
    skp10_sk_object_lock(0, 0, 0, 0, 0);      /* FUN_00377824 */
    skp10_sk_rt_00351f10();
    skp10_sk_rt_00310fc4(*(uint64_t *)(skp10_sk_rt_slot_2f() + 0x48));
    skp10_sk_rt_00351048();
    skp10_sk_rt_0034d334();
    skp10_sk_rt_slot_0d();
}

/*--------------------------------------------------------------------*/
/* FUN_00267cfc @ 0x00267cfc   (est. skp10_sk_vspace_region_divide)
 * Ghidra: void skp10_sk_rt_00267cfc(void)
 * Region division: computes (curA - curB) / stride with a divide-by-zero
 * and overflow guard. On stride == 0 panics via skp10_sk_rt_00348074(1); on
 * MIN/-1 overflow panics via skp10_sk_rt_0034834c(1); else stores the quotient.
 * Confidence: medium (clear arithmetic + panic structure).
 */
void skp10_sk_vspace_region_divide(void)
{
    int64_t a, b, stride, q;
    skp10_sk_spin_irqsave(0);                 /* FUN_00357ca0 */
    skp10_sk_rt_0035128c();
    skp10_sk_rt_0035248c();
    skp10_sk_rt_003504c4();
    a = (*(int64_t (**)(void))skp10_sk_rt_00310f94())();
    skp10_sk_rt_003504c4();
    b = (*(int64_t (**)(void))skp10_sk_rt_00310f94())();
    skp10_sk_rt_0034b7b8();
    skp10_sk_object_lock(0, 0, 0, 0, 0);      /* FUN_00377824 */
    skp10_sk_rt_00351f10();
    stride = *(int64_t *)(skp10_sk_rt_slot_2f() + 0x48);
    if (stride == 0) {
        skp10_sk_rt_00348074(1);
    } else if (a - b == INT64_MIN && stride == -1) {
        skp10_sk_rt_0034834c(1);
    } else {
        q = 0;
        if (stride != 0) {
            q = (a - b) / stride;
        }
        skp10_sk_rt_00357c44(q, 0);
        return;
    }
    skp10_sk_rt_00351be0();
    skp10_sk_swift_fatal();
}

/*--------------------------------------------------------------------*/
/* FUN_00267efc @ 0x00267efc   (est. sk_vspace_dispatch_ret)
 * Ghidra: void skp10_sk_rt_00267efc(void)
 * Dispatch-and-return wrapper: per-CPU entry, dispatch through runtime, and
 * returns via thunk_FUN_00229ebc.
 * Confidence: low.
 */
void sk_vspace_dispatch_ret(void)
{
    uint64_t a, b;
    skp10_sk_cpu();                           /* FUN_0008e518 */
    a = skp10_sk_rt_00350980();
    skp10_sk_rt_0034ece8();
    skp10_sk_rt_00355b28();
    skp10_sk_rt_00310d68(0);
    skp10_sk_rt_00348d4c();
    skp10_sk_rt_00348a18();
    skp10_sk_rt_0034b4c0();
    skp10_sk_rt_0034fd7c();
    skp10_sk_rt_00117cc4();
    skp10_sk_rt_0034f474();
    skp10_sk_rt_000839d8();
    skp10_sk_rt_000aa46c();
    skp10_sk_rt_003516a8();
    skp10_sk_rt_0034b2c8();
    if ((bool)0) {
        skp10_sk_rt_0034c9f8();
        skp10_sk_rt_slot_0d();
        b = 0;
    } else {
        skp10_sk_rt_003513d8(0 - 0);
        skp10_sk_rt_00117cc4();
        skp10_sk_rt_00310f94();
        skp10_sk_rt_0034c404();
        b = (*(uint64_t (**)(void))skp10_sk_rt_slot_0d())();
    }
    skp10_sk_rtt_00229ebc(a, b);
    skp10_sk_rt_0008e500(a, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_00268038 @ 0x00268038   (est. sk_vspace_state_push)
 * Ghidra: void skp10_sk_rt_00268038(void)
 * State push: allocates a block via skp10_sk_rt_003540f4(skp10_DAT_004baeb0,...), writes
 * a value at +0x30, builds a 0x29-byte record and stores it into the target
 * record (unaff_x21).
 * Confidence: low.
 */
void sk_vspace_state_push(void)
{
    uint64_t u, blk;
    uint64_t *dst = (uint64_t *)0;      /* unaff_x21 */
    skp10_sk_rt_003503d0();
    skp10_sk_rt_003519d4();
    u = skp10_sk_rt_00358fe8();
    blk = skp10_sk_rt_003540f4(skp10_DAT_004baeb0, u, u);
    *(uint64_t *)(blk + 0x30) = 0;
    skp10_sk_rt_0034d5ec((uint64_t*)sk_scratch);
    skp10_sk_rt_001e4298();
    dst[1] = 0;
    dst[0] = 0;
    dst[3] = 0;
    dst[2] = 0;
    *(uint64_t *)((uint64_t)dst + 0x21) = 0;
    *(uint64_t *)((uint64_t)dst + 0x19) = 0;
}

/*--------------------------------------------------------------------*/
/* FUN_002680a8 @ 0x002680a8   (est. sk_vspace_state_push_b)
 * Ghidra: void skp10_sk_rt_002680a8(void)
 * State push variant.
 * Confidence: low.
 */
void sk_vspace_state_push_b(void)
{
    uint64_t u, blk;
    skp10_sk_rt_0035316c();
    skp10_sk_rt_0034ab20();
    skp10_sk_rt_00355b28();
    skp10_sk_rt_00310f94(0);
    skp10_sk_rt_0034d150();
    u = (*(uint64_t (**)(void))skp10_sk_rt_slot_0d())();
    skp10_sk_rt_0034e484();
    skp10_sk_rt_00117cc4();
    skp10_sk_rt_003519d4();
    u = skp10_sk_rt_00358fe8();
    blk = skp10_sk_rt_003540f4(skp10_DAT_004baeb0, u, u);
    *(uint64_t *)(blk + 0x30) = u;
    skp10_sk_rt_0034d5ec((uint64_t*)sk_scratch, 0 - 0);
    skp10_sk_rt_001e4348();
    skp10_sk_rt_00358870();
}

/*--------------------------------------------------------------------*/
/* FUN_0026817c @ 0x0026817c   (est. sk_vspace_obj_ref)
 * Ghidra: void skp10_sk_rt_0026817c(void)
 * Object reference: dispatch and rebuild a key via FUN_0034cdd8.
 * Confidence: low.
 */
void sk_vspace_obj_ref(uint64_t p1)
{
    uint64_t u;
    skp10_sk_rt_0034c798();
    skp10_sk_rt_00354db8();
    u = skp10_sk_rt_00310ad4();
    (*(void (**)(void))0)();
    skp10_sk_rt_0034cdd8();
    skp10_sk_rt_slot_0d(u);
}

/*--------------------------------------------------------------------*/
/* FUN_002681d8 @ 0x002681d8   (est. sk_vspace_obj_unref)
 * Ghidra: void skp10_sk_rt_002681d8(void)
 * Object unreference: locks, dispatches, and cleans up via FUN_00310ca4.
 * Confidence: low.
 */
void sk_vspace_obj_unref(uint64_t p1)
{
    uint64_t u;
    skp10_sk_cpu();                           /* FUN_0008e518 */
    skp10_sk_rt_0034b430();
    u = skp10_sk_rt_00310ad4(0);
    skp10_sk_rt_0034c60c();
    skp10_sk_object_lock(0, 0, 0, 0, 0);      /* FUN_00377824 */
    skp10_sk_rt_00348d64();
    skp10_sk_rt_0007c1a4();
    skp10_sk_rt_0034b05c();
    skp10_sk_rt_0034b3e8();
    skp10_sk_rt_003508a8();
    skp10_sk_rt_00117cc4();
    skp10_sk_rt_0034c5fc();
    skp10_sk_lock_ref(0);                     /* FUN_00377bec */
    skp10_sk_rt_0031bc70();
    skp10_sk_rt_00350b30();
    skp10_sk_rt_003515e4();
    skp10_sk_rt_00310ca4(u);
    skp10_sk_rt_00351f7c();
    skp10_sk_rt_00351190();
    skp10_sk_rt_0034ded4();
    skp10_sk_rt_0008e500(0);
}

/*--------------------------------------------------------------------*/
/* FUN_0026830c @ 0x0026830c   (est. sk_vspace_alloc_block)
 * Ghidra: void skp10_sk_rt_0026830c(undefined8, undefined8, long param_3)
 * Allocates an object block: resolves the type (FUN_00352700), validates via
 * FUN_0019fd10, allocates (FUN_0036b270 / FUN_0019e578), and initializes the
 * block with the type-info-relative size.
 * Confidence: low.
 */
void sk_vspace_alloc_block(uint64_t p1, uint64_t p2, long p3)
{
    uint64_t type, obj, r;
    uint8_t tb;
    skp10_sk_rt_00354744();
    type = skp10_sk_rt_00352700();
    tb = *(uint8_t *)(*(uint64_t *)(p3 + -8) + 0x50);
    if (type == 0) {
        skp10_sk_rt_00350a64();
        obj = skp10_sk_rt_00310d34();
        type = skp10_sk_rt_00348718();
        skp10_sk_rt_00376820(type, obj);
        skp10_sk_rt_00355c28();
        r = skp10_sk_rt_0019fd10(obj);
        if ((r & 1) != 0) {
            skp10_sk_rt_00310fc4(~(uint32_t)tb);
            skp10_sk_rt_00351048();
            skp10_sk_rt_0034d334();
            skp10_sk_rt_slot_0d();
            type = 0;
            goto done;
        }
        skp10_sk_rt_00350500();
        skp10_sk_rt_00310dd8();
        skp10_sk_rt_00349f08();
        type = skp10_sk_rt_0019e578((uint64_t*)sk_scratch);
    } else {
        obj = (uint64_t)skp10_sk_alloc_pages(type, 0); /* FUN_0036b270 */
    }
    skp10_sk_rt_00353300();
    skp10_sk_rt_0034d334(type, obj + ((uint64_t)tb + 0x20 & ((uint64_t)tb ^ 0xffffffffffffffffull)));
    skp10_sk_rt_slot_0d();
done:
    skp10_sk_rt_003544c8(type, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_00268400 @ 0x00268400   (est. sk_vspace_alloc_block_b)
 * Ghidra: void skp10_sk_rt_00268400(void)
 * Block allocation variant with a retry path (two FUN_0019fd10 attempts),
 * panicking on the second failure (skp10_sk_rt_003486b8(0x1e5)).
 * Confidence: low.
 */
void sk_vspace_alloc_block_b(void)
{
    uint64_t type, obj, r;
    uint8_t tb;
    long lv;
    skp10_sk_rt_00351e20();
    skp10_sk_rt_00352700();
    skp10_sk_rt_00359ac8();
    skp10_sk_rt_00350a64();
    skp10_sk_rt_00310d34();
    skp10_sk_rt_0034f554();
    skp10_sk_rt_0019e410();
    skp10_sk_rt_00356030();
    lv = *(uint64_t*)sk_scratch;
    tb = *(uint8_t *)(skp10_sk_rt_slot_2f() + 0x50);
    if (lv == 0) {
        skp10_sk_rt_00348718();
        skp10_sk_rt_00376820();
        skp10_sk_rt_00357ab4();
        r = skp10_sk_rt_0019fd10();
        if ((r & 1) == 0) {
            skp10_sk_rt_0035047c();
            skp10_sk_rt_003486b8(0x1e5);
            skp10_sk_rt_0034975c();
            skp10_sk_swift_fatal();
        }
        lv = *(uint64_t*)sk_scratch;
        if (lv != 0) goto have;
        skp10_sk_rt_00348718();
        skp10_sk_rt_00376820();
        skp10_sk_rt_00357ab4();
        r = skp10_sk_rt_0019fd10();
        if ((r & 1) != 0) {
            skp10_sk_rt_00310fc4(~(uint32_t)tb);
            skp10_sk_rt_00351048();
            skp10_sk_rt_0034d334();
            skp10_sk_rt_slot_0d();
            lv = 0;
            goto done;
        }
        skp10_sk_rt_00350500();
        skp10_sk_rt_00310dd8();
        skp10_sk_rt_00349f08();
        lv = skp10_sk_rt_0019e578((uint64_t*)sk_scratch);
    } else {
have:
        skp10_sk_alloc_pages(lv, 0);          /* FUN_0036b270 */
    }
    skp10_sk_rt_00353300();
    skp10_sk_rt_0034d334(lv + ((uint64_t)tb + 0x20 & ((uint64_t)tb ^ 0xffffffffffffffffull)));
    skp10_sk_rt_slot_0d();
done:
    skp10_sk_rt_00351d30(lv, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_00268540 @ 0x00268540   (est. sk_vspace_string_append)
 * Ghidra: long skp10_sk_rt_00268540(ulong param_1, ulong param_2)
 * Swift String append: appends a single zero byte to a growable string
 * buffer, reallocating when full. Returns the buffer. Handles both direct
 * (untagged) and indirect (tagged) string storage. This is the cL4/Swift
 * string append primitive.
 * Confidence: medium (classic Swift string-append pattern).
 */
long sk_vspace_string_append(uint64_t value, uint64_t storage)
{
    uint64_t buf, len;
    if ((storage >> 0x3c & 1) != 0) {
        return skp10_sk_rt_002b22d4(value);
    }
    if ((storage >> 0x3d & 1) != 0) {
        uint64_t tmp[2];
        tmp[0] = value;
        tmp[1] = storage & 0xffffffffffffffull;
        buf = skp10_sk_rt_001a433c(&tmp, storage >> 0x38 & 0xf);
    } else if ((value >> 0x3c & 1) != 0) {
        uint64_t ptr = (storage & 0xfffffffffffffffull) + 0x20;
        uint64_t cnt = value & 0xffffffffffffull;
        buf = skp10_sk_rt_001a433c(ptr, cnt);
    } else {
        uint64_t p = skp10_sk_rt_002a9ba8(value);
        if (p == 0) {
            skp10_sk_rt_000a6fe0();
            buf = 0;
            goto out;
        }
        buf = skp10_sk_rt_001a433c(p, 0);
    }
out:
    len = skp10_sk_rt_003a261c(buf);
    if ((len & 1) == 0) {
        skp10_sk_rt_000824e4(0, *(long *)(buf + 0x10) + 1, 1);
    }
    len = *(uint64_t *)(buf + 0x10);
    if (*(uint64_t *)(buf + 0x18) >> 1 <= len) {
        skp10_sk_rt_0006b42c();
        skp10_sk_rt_000dbc98();
        skp10_sk_rt_000824e4();
    }
    *(uint64_t *)(buf + 0x10) = len + 1;
    *(uint8_t *)(buf + len + 0x20) = 0;
    return (long)buf;
}

/*--------------------------------------------------------------------*/
/* FUN_0026863c @ 0x0026863c   (est. sk_vspace_key_init)
 * Ghidra: void skp10_sk_rt_0026863c(void)
 * Key/string init: FUN_001a84f4 + FUN_001a8564.
 * Confidence: low.
 */
void sk_vspace_key_init(void)
{
    uint64_t stk[9];
    skp10_sk_rt_001a84f4(stk);
    skp10_sk_rt_001a8564();
}

/*--------------------------------------------------------------------*/
/* FUN_00268670 @ 0x00268670   (est. sk_vspace_key_destroy)
 * Ghidra: void skp10_sk_rt_00268670(long param_1)
 * Key destroy: reads the key (+0x20), tears down via FUN_0017e880, writes a
 * stack record ({0x674330, value, 0xd000000000000026, 0x80000000005d0240, 0,
 * ...}) and frees the object (FUN_0036986c + FUN_000026e8).
 * Confidence: low.
 */
void sk_vspace_key_destroy(long p1)
{
    uint64_t u = *(uint64_t *)(p1 + 0x20);
    uint64_t *rec = (uint64_t *)0;
    skp10_sk_rt_000dbc54();
    skp10_sk_rt_0017e880(u);
    skp10_sk_rt_0034c5cc();
    u = (*(uint64_t (**)(void))skp10_sk_rt_slot_0d())();
    skp10_sk_rt_00348730();
    rec[0] = 0x674330;
    rec[1] = u;
    rec[2] = 0xd000000000000026ull;
    rec[3] = 0x80000000005d0240ull;
    rec[4] = 0;
    *(uint8_t *)(rec + 9) = 0;
    skp10_sk_rt_0036986c();
    skp10_sk_rt_000026e8(p1);
}

/*--------------------------------------------------------------------*/
/* FUN_00268704 @ 0x00268704   (est. sk_vspace_key_destroy_fwd)
 * Ghidra: void skp10_sk_rt_00268704(void)
 * Forwarder to FUN_00268670.
 * Confidence: medium.
 */
void sk_vspace_key_destroy_fwd(void) { sk_vspace_key_destroy(0); }

/*--------------------------------------------------------------------*/
/* FUN_00268708 @ 0x00268708   (est. sk_vspace_key_destroy_fwd2)
 * Ghidra: void skp10_sk_rt_00268708(void)
 * Forwarder to FUN_00268670.
 * Confidence: medium.
 */
void sk_vspace_key_destroy_fwd2(void) { sk_vspace_key_destroy(0); }

/*--------------------------------------------------------------------*/
/* FUN_00268734 @ 0x00268734   (est. sk_vspace_table_put)
 * Ghidra: void skp10_sk_rt_00268734(void)
 * Table put: resolves the key, dispatches the +0x20 method, and stores a
 * 2-word {key,value} record at the computed offset.
 * Confidence: low.
 */
void sk_vspace_table_put(void)
{
    long r;
    uint64_t *dst;
    skp10_sk_rt_0034aa3c();
    skp10_sk_rt_00358e88();
    skp10_sk_rt_003509c8(0);
    (*(void (**)(void))(skp10_sk_rt_slot_2f() + 0x20))();
    skp10_sk_rt_00350530();
    r = (*(long (**)(void))skp10_sk_rt_slot_0d())();
    dst = (uint64_t *)(0 + *(int *)(r + 0x24));
    dst[0] = 0;
    dst[1] = 0;
}

/*--------------------------------------------------------------------*/
/* FUN_002687a8 @ 0x002687a8   (est. sk_vspace_table_count)
 * Ghidra: void skp10_sk_rt_002687a8(long param_1)
 * Table count / index: FUN_003591d0 on the int at param_1+0x28, then
 * FUN_0009461c.
 * Confidence: low.
 */
void sk_vspace_table_count(long p1)
{
    skp10_sk_rt_003591d0((long)*(int *)(p1 + 0x28));
    skp10_sk_rt_0009461c();
}

/*--------------------------------------------------------------------*/
/* FUN_002687e8 @ 0x002687e8   (est. sk_vspace_table_put_b)
 * Ghidra: void skp10_sk_rt_002687e8(void)
 * Table put variant: builds a key via FUN_003516cc, dispatches the +0x20
 * method, and stores the record.
 * Confidence: low.
 */
void sk_vspace_table_put_b(void)
{
    long r;
    int i;
    uint64_t *dst;
    skp10_sk_rt_00084220();
    skp10_sk_rt_00351da8();
    skp10_sk_rt_0034a354();
    *(uint64_t*)skp10_sk_rt_slot_0d() = 0;
    skp10_sk_rt_003516cc();
    r = (long)skp10_sk_rt_003516cc();
    i = *(int *)(r + 0x24);
    skp10_sk_rt_00349830();
    skp10_sk_rt_00350968();
    skp10_sk_object_lock(0, 0, 0, 0, 0);      /* FUN_00377824 */
    skp10_sk_rt_00349530();
    (*(void (**)(uint64_t))(skp10_sk_rt_slot_2f() + 0x20))(0 + i);
    dst = (uint64_t *)(0 + *(int *)(r + 0x28));
    dst[0] = 0;
    dst[1] = 0;
    skp10_sk_rt_00084234(0);
}

/*--------------------------------------------------------------------*/
/* FUN_00268870 @ 0x00268870   (est. sk_vspace_table_get)
 * Ghidra: void skp10_sk_rt_00268870(void)
 * Table get / lookup: locks, resolves the key via FUN_00377bec/FUN_00377dcc,
 * and dispatches through the table's +0x20 method. On a miss it sets a
 * boolean flag in the record.
 * Confidence: low.
 */
void sk_vspace_table_get(void)
{
    uint64_t u;
    uint8_t *flag = (uint8_t *)0;
    if ((*flag & 1) == 0) {
        skp10_sk_rt_00352590();
        skp10_sk_rt_00350624();
        skp10_sk_object_lock(0, 0, 0, 0, 0);  /* FUN_00377824 */
        skp10_sk_rt_0034e130();
        skp10_sk_rt_00310d68();
        skp10_sk_rt_00348d4c();
        skp10_sk_rt_0007c1a4();
        skp10_sk_rt_0034af20();
        skp10_sk_rt_00349734();
        skp10_sk_rt_0007c1a4();
        skp10_sk_rt_0034b0d4();
        skp10_sk_rt_00359530();
        skp10_sk_rt_00350624();
        skp10_sk_object_lock(0, 0, 0, 0, 0);  /* FUN_00377824 */
        skp10_sk_rt_0007c1c4();
        skp10_sk_rt_00352ea8();
        u = skp10_sk_lock_ref(0);             /* FUN_00377bec */
        skp10_sk_rt_000a68f4();
        skp10_sk_rt_003508e4();
        u = skp10_sk_lock_release(0);         /* FUN_00377dcc */
        (*(void (**)(uint64_t, uint64_t))skp10_sk_rt_000a68f4())(u, 0);
        skp10_sk_rt_0034aa54();
        if ((bool)0) {
            skp10_sk_rt_00352420();
            skp10_sk_rt_00350c38();
            skp10_sk_rt_slot_0d();
            u = 1;
        } else {
            (*(void (**)(void))(skp10_sk_rt_slot_2f() + 0x20))();
            skp10_sk_rt_00350944();
            u = (*(uint64_t (**)(void))(flag + *(int *)(skp10_sk_rt_slot_0d() + 0x28)))();
            if ((u & 1) == 0) {
                skp10_sk_rt_003508a8(*(uint64_t *)(skp10_sk_rt_slot_2f() + 8));
                skp10_sk_rt_slot_0d();
                u = 1;
                *flag = 1;
            } else {
                skp10_sk_rt_00350a04();
                (*(void (**)(void))(skp10_sk_rt_slot_2f() + 0x20))();
                u = 0;
            }
        }
    } else {
        u = 1;
    }
    skp10_sk_rt_00351548(0, u);
    skp10_sk_rt_000839d8();
    skp10_sk_rt_0008e500(0);
}

/*--------------------------------------------------------------------*/
/* FUN_00268a78 @ 0x00268a78   (est. sk_vspace_key_ops)
 * Ghidra: void skp10_sk_rt_00268a78(void)
 * Key operation: reads the key object, locks, dispatches, and stores via
 * FUN_003530a4.
 * Confidence: low.
 */
void sk_vspace_key_ops(void)
{
    long r;
    uint64_t u;
    skp10_sk_rt_00084220();
    r = skp10_sk_rt_0034c084();
    u = *(uint64_t *)(r + 0x18);
    skp10_sk_rt_00349830();
    skp10_sk_rt_003513b4();
    skp10_sk_object_lock(0, 0, 0, 0, 0);      /* FUN_00377824 */
    skp10_sk_rt_00351f10();
    skp10_sk_rt_0007c1a4();
    skp10_sk_rt_0034b05c();
    skp10_sk_rt_000a68c4(u);
    r = skp10_sk_rt_0034f654();
    u = (*(uint64_t (**)(uint64_t, uint64_t))skp10_sk_rt_slot_0d())(r, u);
    {
        uint64_t *dst = (uint64_t *)(0 + *(int *)(0 + 0x24));
        skp10_sk_rt_003530a4(u, *dst, dst[1]);
    }
    skp10_sk_rt_00354318();
    (*(void (**)(void))skp10_sk_rt_slot_0d())();
    skp10_sk_rt_00084234(0);
}

/*--------------------------------------------------------------------*/
/* FUN_00268b34 @ 0x00268b34   (est. sk_vspace_msg_send)
 * Ghidra: void skp10_sk_rt_00268b34(undefined8 param_1, long param_2)
 * Message send: FUN_0031d5a8 on the object fields (+0x10/+0x18), then
 * indirect dispatch through the +0x10 method.
 * Confidence: low.
 */
void sk_vspace_msg_send(uint64_t p1, long p2)
{
    skp10_sk_rt_0031d5a8(0, *(uint64_t *)(p2 + 0x10), *(uint64_t *)(p2 + 0x18));
    skp10_sk_rt_00350404();
    (*(void (**)(uint64_t))(skp10_sk_rt_slot_2f() + 0x10))(p1);
}

/*--------------------------------------------------------------------*/
/* FUN_00268b88 @ 0x00268b88   (est. sk_vspace_ep_reply)
 * Ghidra: void skp10_sk_rt_00268b88(undefined8, undefined8, undefined8)
 * Endpoint reply: locks, dispatches the +0x20 method, tears down.
 * Confidence: low.
 */
void sk_vspace_ep_reply(uint64_t p1, uint64_t p2, uint64_t p3)
{
    skp10_sk_rt_00352800();
    skp10_sk_rt_00349748();
    skp10_sk_object_lock(0, p3, 0);           /* FUN_00377824 */
    skp10_sk_rt_0034ab20();
    (*(void (**)(void))(skp10_sk_rt_slot_2f() + 0x20))();
    skp10_sk_rt_0034befc();
    skp10_sk_rt_000839d8();
}

/*--------------------------------------------------------------------*/
/* FUN_00268bf8 @ 0x00268bf8   (est. sk_vspace_ep_reply_b)
 * Ghidra: void skp10_sk_rt_00268bf8(undefined8, undefined8, undefined8)
 * Endpoint reply variant dispatching through the +8 method.
 * Confidence: low.
 */
void sk_vspace_ep_reply_b(uint64_t p1, uint64_t p2, uint64_t p3)
{
    uint64_t k;
    skp10_sk_rt_00350a28();
    skp10_sk_rt_0034ece8();
    (*(void (**)(void))(skp10_sk_rt_slot_2f() + 8))();
    skp10_sk_rt_00349748();
    skp10_sk_rt_00350968();
    k = skp10_sk_object_lock(0, 0, 0, 0, 0);  /* FUN_00377824 */
    skp10_sk_rt_00350744(0, k, p3, 0);
    skp10_sk_rt_000839d8();
}

/*--------------------------------------------------------------------*/
/* FUN_00268c58 @ 0x00268c58   (est. sk_vspace_recv_loop)
 * Ghidra: void skp10_sk_rt_00268c58(void)
 * Receive loop: locks, reads the capability, dispatches two validity checks
 * (FUN_000839f8), and on both-fail drives the +0x20/+8 teardown path.
 * Confidence: low.
 */
void sk_vspace_recv_loop(void)
{
    uint64_t u, v;
    int a, b;
    long off;
    skp10_sk_cpu();                           /* FUN_0008e518 */
    u = skp10_sk_rt_00349748();
    u = skp10_sk_object_lock(u, 0);           /* FUN_00377824 */
    skp10_sk_rt_000a6f88();
    skp10_sk_rt_003493c4();
    skp10_sk_rt_0034d698();
    skp10_sk_rt_0034ac3c();
    skp10_sk_rt_0034de44();
    v = skp10_sk_rt_0031d5a8();
    skp10_sk_rt_0034ce88();
    skp10_sk_rt_003515b4();
    skp10_sk_rt_003722e4();
    skp10_sk_rt_00351f10();
    skp10_sk_rt_0007c1a4();
    skp10_sk_rt_0034af20();
    off = (long)*(int *)(skp10_sk_rt_slot_0d() + 0x38);
    skp10_sk_rt_00356030();
    (*(void (**)(void))(skp10_sk_rt_slot_2f() + 0x10))();
    skp10_sk_rt_0034fd7c();
    (*(void (**)(void))(skp10_sk_rt_slot_2f() + 0x10))();
    (*(void (**)(uint64_t, uint64_t, uint64_t))(skp10_sk_rt_slot_2f() + 0x10))(0 + off, 0, v);
    skp10_sk_rt_0035163c();
    a = skp10_sk_rt_000839f8();
    skp10_sk_rt_0035163c(0 + off);
    b = skp10_sk_rt_000839f8();
    if (a == 1) {
        if (b != 1) {
            (*(void (**)(uint64_t, uint64_t))(skp10_sk_rt_slot_2f() + 8))(0 + off, v);
        }
    } else if (b == 1) {
        skp10_sk_rt_00351924();
        skp10_sk_rt_00351e90();
        skp10_sk_rt_slot_0d();
    } else {
        (*(void (**)(uint64_t, uint64_t, uint64_t))(skp10_sk_rt_slot_2f() + 0x20))(0, 0, 0);
        skp10_sk_rt_00350ea4();
        v = (*(uint64_t (**)(void))skp10_sk_rt_slot_0d())();
        skp10_sk_rt_003567b0(v, 0 + off);
        (*(void (**)(uint64_t, uint64_t, uint64_t))(skp10_sk_rt_slot_2f() + 0x20))(0, 0, 0);
        skp10_sk_rt_0034c3c4();
        skp10_sk_rt_0034b768();
        skp10_sk_lock_ref(0);                 /* FUN_00377bec */
        skp10_sk_rt_00349fe0();
        skp10_sk_rt_00100c38();
        skp10_sk_rt_0035053c();
        skp10_sk_rt_slot_0d();
        (*(void (**)(void))(skp10_sk_rt_slot_2f() + 8))();
        skp10_sk_rt_00351714();
        (*(void (**)(void))(skp10_sk_rt_slot_2f() + 8))();
        skp10_sk_rt_00351f88();
        (*(void (**)(void))(skp10_sk_rt_slot_2f() + 8))();
    }
    u = skp10_sk_rt_00353034();
    skp10_sk_rt_0008e500(u, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_00268e7c @ 0x00268e7c   (est. sk_vspace_recv_loop_b)
 * Ghidra: void skp10_sk_rt_00268e7c(void)
 * Receive loop variant with a different middle dispatch (FUN_0034ad40) and
 * result propagation via FUN_0034c464.
 * Confidence: low.
 */
void sk_vspace_recv_loop_b(void)
{
    uint64_t u, v;
    long off;
    skp10_sk_cpu();                           /* FUN_0008e518 */
    u = skp10_sk_rt_00349748();
    u = skp10_sk_object_lock(u, 0);           /* FUN_00377824 */
    skp10_sk_rt_000a6f88();
    skp10_sk_rt_003493c4();
    skp10_sk_rt_0034d698();
    skp10_sk_rt_0034ac3c();
    skp10_sk_rt_0034de44();
    v = skp10_sk_rt_0031d5a8();
    skp10_sk_rt_0034ce88();
    skp10_sk_rt_003515b4();
    skp10_sk_rt_003722e4();
    skp10_sk_rt_00351f10();
    skp10_sk_rt_0007c1a4();
    off = (long)*(int *)(skp10_sk_rt_slot_0d() + 0x38);
    skp10_sk_rt_00356030();
    (*(void (**)(void))(skp10_sk_rt_slot_2f() + 0x10))();
    skp10_sk_rt_0034fd7c();
    (*(void (**)(uint64_t, uint64_t, uint64_t))(skp10_sk_rt_slot_2f() + 0x10))(0 + off, 0, v);
    skp10_sk_rt_0034ad40();
    if ((bool)0) {
        (*(void (**)(uint64_t, uint64_t))(skp10_sk_rt_slot_2f() + 8))(0 + off, v);
    } else {
        skp10_sk_rt_0034ad40(0 + off);
        if ((bool)0) {
            skp10_sk_rt_00351924();
            skp10_sk_rt_00351e90();
            skp10_sk_rt_slot_0d();
        } else {
            (*(void (**)(uint64_t, uint64_t, uint64_t))(skp10_sk_rt_slot_2f() + 0x20))(0, 0, 0);
            skp10_sk_rt_00350ea4();
            v = (*(uint64_t (**)(void))skp10_sk_rt_slot_0d())();
            skp10_sk_rt_003567b0(v, 0 + off);
            (*(void (**)(uint64_t, uint64_t, uint64_t))(skp10_sk_rt_slot_2f() + 0x20))(0, 0, 0);
            skp10_sk_rt_0034c3c4();
            skp10_sk_rt_0034b768();
            skp10_sk_lock_ref(0);             /* FUN_00377bec */
            u = skp10_sk_rt_0034c464();
            skp10_sk_rt_0035053c(u, off);
            skp10_sk_rt_slot_0d();
            (*(void (**)(void))(skp10_sk_rt_slot_2f() + 8))();
            skp10_sk_rt_00351714();
            (*(void (**)(void))(skp10_sk_rt_slot_2f() + 8))();
            skp10_sk_rt_00351f88();
            (*(void (**)(void))(skp10_sk_rt_slot_2f() + 8))();
        }
    }
    u = skp10_sk_rt_00353034();
    skp10_sk_rt_0008e500(u, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_0026909c @ 0x0026909c   (est. skp10_sk_vspace_wait_sync)
 * Ghidra: void skp10_sk_rt_0026909c(undefined8, undefined8, undefined8)
 * Wait / sync wrapper: locks, dispatches, and on ZR-false performs a
 * wait-release sequence; ZR-true is a fast teardown (thunk_FUN_002298d4).
 * Confidence: low.
 */
void skp10_sk_vspace_wait_sync(uint64_t p1, uint64_t p2, uint64_t p3)
{
    uint64_t u;
    skp10_sk_rt_00084220();
    u = *(uint64_t *)(skp10_sk_rt_slot_0d() + 0x18);
    skp10_sk_rt_00349748();
    skp10_sk_rt_00351214();
    skp10_sk_object_lock(0, 0, 0, 0, 0);      /* FUN_00377824 */
    skp10_sk_rt_00348e00();
    skp10_sk_rt_0007c1a4();
    skp10_sk_rt_0034b2f8();
    skp10_sk_rt_003508e4();
    skp10_sk_rt_0031d5a8(0, 0, u);
    skp10_sk_rt_000a6f88();
    skp10_sk_rt_0007c1a4();
    skp10_sk_rt_0034b05c();
    skp10_sk_rt_00350618(*(uint64_t *)(skp10_sk_rt_slot_2f() + 0x10));
    skp10_sk_rt_slot_0d();
    skp10_sk_rt_0034aa54(u);
    if ((bool)0) {
        skp10_sk_rtt_002298d4(0x7fffffffffffffffll);
    } else {
        skp10_sk_rt_00354810();
        skp10_sk_rt_0034c064();
        skp10_sk_rt_slot_0d();
        skp10_sk_rt_0031945c(p3);
        skp10_sk_rt_00351318();
        skp10_sk_rt_003504a0();
        skp10_sk_rt_slot_0d();
        skp10_sk_rt_0034f2c4();
        skp10_sk_rt_slot_0d();
    }
    skp10_sk_rt_00084234(0);
}

/*--------------------------------------------------------------------*/
/* FUN_00269224 @ 0x00269224   (est. sk_vspace_table_op)
 * Ghidra: void skp10_sk_rt_00269224(undefined8 param_1, long param_2, undefined8 param_3)
 * Table operation: reads the object key (+0x10), locks, dispatches through
 * FUN_000277b8, and forwards to FUN_00268b88.
 * Confidence: low.
 */
void sk_vspace_table_op(uint64_t p1, long p2, uint64_t p3)
{
    uint64_t u = *(uint64_t *)(p2 + 0x10);
    skp10_sk_rt_00349748();
    skp10_sk_object_lock(0, 0, u);            /* FUN_00377824 */
    skp10_sk_rt_00351f10();
    skp10_sk_rt_0007c1a4();
    skp10_sk_rt_0034b2f8();
    skp10_sk_rt_000277b8(p3);
    u = skp10_sk_rt_00350390();
    skp10_sk_rt_slot_0d(u, p3);
    skp10_sk_rt_0034db38(p1);
    sk_vspace_ep_reply(0, 0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_002692b8 @ 0x002692b8   (est. skp10_sk_vspace_table_dispatch)
 * Ghidra: void skp10_sk_rt_002692b8(void)
 * Table dispatch: locks, validates via FUN_00350884, and on failure calls
 * FUN_00269224; on success dispatches the +0x24 method and forwards to
 * FUN_00268bf8.
 * Confidence: low.
 */
void skp10_sk_vspace_table_dispatch(void)
{
    uint64_t u, r;
    skp10_sk_cpu();                           /* FUN_0008e518 */
    r = skp10_sk_rt_0008409c();
    u = *(uint64_t *)(r + 0x10);
    skp10_sk_rt_003499c8();
    skp10_sk_rt_003497b4();
    skp10_sk_rt_00351c10();
    skp10_sk_rt_00348f14(0);
    u = skp10_sk_rt_00358ff4();
    skp10_sk_rt_00350920();
    skp10_sk_rt_00310d68();
    skp10_sk_rt_00348fd8();
    skp10_sk_rt_0007c1a4();
    skp10_sk_rt_0034aee4();
    skp10_sk_rt_0034a688();
    skp10_sk_rt_0007c1a4();
    skp10_sk_rt_0034b2f8();
    skp10_sk_rt_00353480();
    skp10_sk_rt_001aeab4();
    skp10_sk_rt_00351738();
    skp10_sk_swift_dispatch(0, 0, u);         /* FUN_00350884 */
    if ((bool)0) {
        skp10_sk_rt_00350ea4(*(uint64_t *)(skp10_sk_rt_slot_2f() + 8));
        skp10_sk_rt_slot_0d();
    } else {
        skp10_sk_rt_00352b50();
        skp10_sk_rt_003511a8();
        skp10_sk_rt_slot_0d(0, 0, u);
        r = (*(uint64_t (**)(void))(0 + *(int *)(0 + 0x24)))();
        skp10_sk_rt_003518b8(*(uint64_t *)(skp10_sk_rt_slot_2f() + 8));
        skp10_sk_rt_slot_0d();
        if ((r & 1) != 0) {
            skp10_sk_rt_0009461c(*(uint64_t *)(skp10_sk_rt_slot_2f() + 0x10));
            skp10_sk_rt_slot_0d(0, 0, u);
            skp10_sk_rt_0035072c(0, 0, 0, 0);
            sk_vspace_ep_reply_b(0, 0, 0);
            return;
        }
    }
    sk_vspace_table_op(0, 0, 0);
    skp10_sk_rt_0008e500(0);
}

/*--------------------------------------------------------------------*/
/* FUN_00269490 @ 0x00269490   (est. skp10_sk_vspace_notify)
 * Ghidra: void skp10_sk_rt_00269490(undefined8, undefined8, undefined8)
 * Notification dispatch: locks, runs the receive/validate helpers
 * (FUN_002692b8, FUN_00268c58), and on failure panics (FUN_00352be0); on
 * success dispatches the entry and forwards to the ep_reply helpers.
 * Confidence: low.
 */
void skp10_sk_vspace_notify(uint64_t p1, uint64_t p2, uint64_t p3)
{
    uint64_t r, u;
    skp10_sk_cpu();                           /* FUN_0008e518 */
    skp10_sk_rt_00350a28();
    u = *(uint64_t *)(skp10_sk_rt_slot_0d() + 0x10);
    skp10_sk_rt_00349734();
    skp10_sk_rt_003497b4();
    skp10_sk_rt_00348b94(p3);
    r = skp10_sk_object_lock(0, 0, u);        /* FUN_00377824 */
    skp10_sk_rt_000a6f88();
    skp10_sk_rt_0007c1a4();
    skp10_sk_rt_0034cd40();
    skp10_sk_rt_0034bec4();
    skp10_sk_rt_0031d5a8();
    u = skp10_sk_rt_000a6f88();
    skp10_sk_rt_0007c1a4();
    skp10_sk_rt_0034af20();
    skp10_sk_rt_00349748();
    skp10_sk_rt_00350878();
    skp10_sk_object_lock(0, 0, 0, 0, 0);      /* FUN_00377824 */
    skp10_sk_rt_00348d4c();
    skp10_sk_rt_003493c4();
    skp10_sk_rt_0034d294();
    skp10_sk_rt_00349fb8();
    skp10_sk_rt_0034b758();
    skp10_sk_rt_0034bec4();
    skp10_sk_rt_0031d5c0();
    skp10_sk_rt_00348cd0();
    skp10_sk_rt_0007c1a4();
    skp10_sk_rt_0034b460();
    skp10_sk_rt_0007c1c4();
    skp10_sk_rt_002692b8();
    skp10_sk_rt_0034b358(0);
    r = skp10_sk_rt_00268c58();
    skp10_sk_rt_00350c80(*(uint64_t *)(skp10_sk_rt_slot_2f() + 8));
    skp10_sk_rt_slot_0d();
    if ((r & 1) != 0) {
        skp10_sk_rt_00350410();
        skp10_sk_rt_003488bc();
        skp10_sk_rt_003526a4();
        skp10_sk_rt_00352be0();
        skp10_sk_swift_fatal();
    }
    skp10_sk_rt_00352a40();
    skp10_sk_rt_00350ab8();
    skp10_sk_rt_slot_0d(0, 0, u);
    skp10_sk_rt_0034c4bc();
    if ((bool)0) {
        skp10_sk_rt_00350b00(*(uint64_t *)(skp10_sk_rt_slot_2f() + 8));
        skp10_sk_rt_slot_0d();
        *(uint32_t *)(0 + -0x10) = 1;
        skp10_sk_rt_00348b7c(0xef);
        skp10_sk_rt_003526a4();
        skp10_sk_rt_00352be0();
        skp10_sk_swift_fatal();
    }
    skp10_sk_rt_0035478c();
    skp10_sk_rt_0035145c();
    skp10_sk_rt_slot_0d();
    skp10_sk_rt_00319658();
    skp10_sk_rt_0035036c();
    skp10_sk_rt_003504a0();
    skp10_sk_rt_slot_0d();
    (*(void (**)(void))(skp10_sk_rt_slot_2f() + 8))();
    skp10_sk_rt_00350470();
    (*(void (**)(void))(skp10_sk_rt_slot_2f() + 8))();
    skp10_sk_rt_00350704();
    skp10_sk_rt_00084180(0);
    skp10_sk_rt_slot_0d();
    skp10_sk_rt_0034c3c4();
    skp10_sk_rt_003507e0();
    skp10_sk_lock_ref(0);                     /* FUN_00377bec */
    skp10_sk_rt_0034c4fc();
    skp10_sk_rt_00350a70();
    skp10_sk_rt_0034e5fc();
    r = (*(uint64_t (**)(void))skp10_sk_rt_slot_0d())();
    skp10_sk_rt_00350470();
    (*(void (**)(void))(skp10_sk_rt_slot_2f() + 8))();
    if ((r & 1) == 0) {
        uint64_t *slot = (uint64_t *)(0 + *(int *)(0 + 0x24));
        skp10_sk_rt_00351b84();
        skp10_sk_rt_0035063c();
        (*(void (**)(void))skp10_sk_rt_slot_0d())();
        skp10_sk_rt_00352468(0);
        skp10_sk_rt_slot_0d(0, 0, r);
        skp10_sk_rt_0034cfa4();
        (*(void (**)(void))skp10_sk_rt_slot_0d())();
        (*(void (**)(void))*slot)();
        skp10_sk_rt_00357af8();
        skp10_sk_rt_00350c80();
        skp10_sk_rt_slot_0d();
        if ((0 & 1) != 0) {
            skp10_sk_rt_003504a0(0, 0);
            sk_vspace_ep_reply(0, 0, 0);
            goto done;
        }
    }
    skp10_sk_rt_00350a34();
    (*(void (**)(void))(skp10_sk_rt_slot_2f() + 8))();
    skp10_sk_rt_00352498(*(uint64_t *)(skp10_sk_rt_slot_2f() + 0x10));
    skp10_sk_rt_slot_0d(0, 0, u);
    skp10_sk_rt_0034ef68(0);
    sk_vspace_ep_reply_b(0, 0, 0);
done:
    skp10_sk_rt_0008e500(0);
}

/*--------------------------------------------------------------------*/
/* FUN_002698bc @ 0x002698bc   (est. skp10_sk_vspace_signal)
 * Ghidra: void skp10_sk_rt_002698bc(undefined8, undefined8, undefined8)
 * Signal dispatch: locks, dispatches, and on ZR-false runs a teardown path
 * that re-locks and forwards; ZR-true is a panic.
 * Confidence: low.
 */
void skp10_sk_vspace_signal(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4)
{
    uint64_t u, v;
    skp10_sk_cpu();                           /* FUN_0008e518 */
    v = p3;
    skp10_sk_rt_0035a6a8();
    u = *(uint64_t *)(skp10_sk_rt_slot_0d() + 0x10);
    skp10_sk_rt_00349748();
    skp10_sk_object_lock(0, v, u);            /* FUN_00377824 */
    skp10_sk_rt_00348e00();
    skp10_sk_rt_0007c1a4();
    skp10_sk_rt_0034b0c4();
    skp10_sk_rt_00350318();
    skp10_sk_rt_0031d5a8();
    skp10_sk_rt_000a6f88();
    skp10_sk_rt_0007c1a4();
    skp10_sk_rt_0034b0d4();
    skp10_sk_rt_00350914(*(uint64_t *)(skp10_sk_rt_slot_2f() + 0x10));
    skp10_sk_rt_slot_0d();
    skp10_sk_rt_0034aa54();
    if (!(bool)0) {
        skp10_sk_rt_00354810();
        skp10_sk_rt_00351354();
        skp10_sk_rt_slot_0d();
        skp10_sk_rt_00352ecc(p3);
        skp10_sk_rt_00350b48((uint64_t*)sk_scratch);
        skp10_sk_rt_slot_0d();
        skp10_sk_rt_0035351c();
        skp10_sk_rt_00348b94(p3);
        skp10_sk_object_lock(0, 0, u);        /* FUN_00377824 */
        skp10_sk_rt_00349530();
        (*(void (**)(void))(skp10_sk_rt_slot_2f() + 0x10))();
        skp10_sk_rt_00351d00();
        (*(void (**)(void))skp10_sk_rt_slot_0d())();
        skp10_sk_rt_003507bc(*(uint64_t *)(skp10_sk_rt_slot_2f() + 8));
        skp10_sk_rt_slot_0d();
        skp10_sk_rt_0008e500(0);
        return;
    }
    skp10_sk_rt_003489fc();
    skp10_sk_rt_00349de8();
    skp10_sk_swift_fatal();
}

/*--------------------------------------------------------------------*/
/* FUN_00269a88 @ 0x00269a88   (est. sk_vspace_alloc_obj)
 * Ghidra: undefined * skp10_sk_rt_00269a88(long *param_1, undefined8, undefined8, ulong)
 * Allocates a 0x28-byte object (tag 0x48cc), calls FUN_00269b08 to build it,
 * stores the result at +0x20, and returns a vtable pointer (skp10_DAT_003471a4).
 * Confidence: medium (clear alloc pattern).
 */
void *sk_vspace_alloc_obj(long *slot, uint64_t p2, uint64_t p3, uint64_t p4)
{
    long blk = (long)skp10_sk_alloc(0x28, 0x48cc);   /* FUN_0036a908 */
    *slot = blk;
    *(uint64_t *)(blk + 0x20) =
        skp10_sk_rt_00269b08(blk, p2, p3, *(uint64_t *)((p4 & 0xfffffffffffffffeull) - 8));
    return &skp10_DAT_003471a4;
}

/*--------------------------------------------------------------------*/
/* FUN_00269b08 @ 0x00269b08   (est. sk_vspace_alloc_obj_b)
 * Ghidra: undefined1 [16] skp10_sk_rt_00269b08(long *param_1, undefined8, long, undefined8)
 * Second-stage object build: resolves metadata (FUN_00027754), locks the
 * object, allocates the payload (tag 0xe853) and calls FUN_002698bc to
 * initialize it. Returns a {ptr, vtable} pair.
 * Confidence: low.
 */
uint64_t sk_vspace_alloc_obj_b(long *slot, uint64_t p2, long p3, uint64_t p4)
{
    uint64_t meta, blk, hdr;
    meta = skp10_sk_rt_00027754(*(uint64_t *)((p4 & 0xfffffffffffffffeull) - 8));
    blk = skp10_sk_object_lock(0, meta, *(uint64_t *)(p3 + 0x10), &skp10_DAT_00611b24, &LAB_00611b34);
    *slot = (long)blk;
    hdr = *(uint64_t *)(blk + -8);
    slot[1] = (long)hdr;
    blk = (uint64_t)skp10_sk_alloc(*(uint64_t *)(hdr + 0x40), 0xe853);
    slot[2] = (long)blk;
    skp10_sk_vspace_signal(blk, p2, p3, p4);
    return (uint64_t)&skp10_DAT_003471a8;
}

/*--------------------------------------------------------------------*/
/* FUN_00269bf4 @ 0x00269bf4   (est. sk_vspace_obj_msg)
 * Ghidra: void skp10_sk_rt_00269bf4(void)
 * Object message: dispatches with selector 0xff through a callback.
 * Confidence: low.
 */
void sk_vspace_obj_msg(void)
{
    (*(void (**)(uint64_t, uint64_t, uint64_t))0)(0xff,
        *(uint64_t *)(skp10_sk_rt_slot_0d() + 0x10),
        *(uint64_t *)(skp10_sk_rt_slot_0d() + -8));
    skp10_sk_rt_00352efc();
    skp10_sk_rt_00310d68();
    skp10_sk_rt_0034b690();
    skp10_sk_rt_000839d8();
}

/*--------------------------------------------------------------------*/
/* FUN_00269c70 @ 0x00269c70   (est. sk_vspace_scan)
 * Ghidra: void skp10_sk_rt_00269c70(undefined8, undefined8, ulong, code*, code*)
 * Scan dispatch: builds a key, dispatches through callbacks param_4/param_5.
 * Confidence: low.
 */
void sk_vspace_scan(uint64_t p1, uint64_t p2, uint64_t p3,
                    void (*a)(void), void (*b)(void))
{
    uint64_t u;
    skp10_sk_rt_00084220();
    skp10_sk_rt_003509ec();
    u = *(uint64_t *)((p3 & 0xfffffffffffffffeull) - 8);
    skp10_sk_rt_00351ecc(0, *(uint64_t *)(skp10_sk_rt_slot_0d() + 0x10));
    (*a)();
    skp10_sk_rt_00348d4c();
    skp10_sk_rt_0007c1a4();
    skp10_sk_rt_0034a2c0();
    skp10_sk_rt_00350b84();
    skp10_sk_rt_slot_0d();
    skp10_sk_rt_003507d4();
    ((void (*)(uint64_t, uint64_t, uint64_t))b)(0, 0, u);
    skp10_sk_rt_0034c9f8();
    skp10_sk_rt_slot_0d();
    skp10_sk_rt_00084234(0);
}

/*--------------------------------------------------------------------*/
/* FUN_00269d30 @ 0x00269d30   (est. sk_vspace_walk)
 * Ghidra: void skp10_sk_rt_00269d30(undefined8, undefined8, undefined8)
 * Large walk loop: locks, iterates a table via FUN_0031d5a8 /
 * FUN_00310f94 / FUN_0014ae44, and dispatches each entry through the +8
 * method, with panic on failure (FUN_00352be0). Two major branches (ZR)
 * with the same iterative walk shape.
 * Confidence: low.
 */
void sk_vspace_walk(uint64_t p1, uint64_t p2, uint64_t p3)
{
    uint64_t u, v;
    skp10_sk_cpu();                           /* FUN_0008e518 */
    skp10_sk_rt_0035316c();
    skp10_sk_rt_003514b8(p3);
    skp10_sk_rt_00350bd8();
    u = *(uint64_t *)(0 + 0x10);
    skp10_sk_rt_003497a0();
    u = skp10_sk_object_lock(0, 0, u);        /* FUN_00377824 */
    skp10_sk_rt_000a6f88();
    skp10_sk_rt_0007c1a4();
    skp10_sk_rt_0034cd54();
    skp10_sk_rt_00349748();
    skp10_sk_rt_00351df0();
    skp10_sk_object_lock(0, 0, 0, 0, 0);      /* FUN_00377824 */
    skp10_sk_rt_00348d4c();
    skp10_sk_rt_00348a18();
    skp10_sk_rt_0034aea8();
    skp10_sk_rt_0034f730();
    skp10_sk_rt_00350464();
    skp10_sk_rt_00350908();
    skp10_sk_rt_003516f0();
    skp10_sk_rt_0031d5a8();
    skp10_sk_rt_000a6f88();
    skp10_sk_rt_0007c1a4();
    skp10_sk_rt_0034ad78();
    skp10_sk_rt_slot_0d();
    skp10_sk_rt_00351bac();
    skp10_sk_rt_00350884();
    if ((bool)0) {
        /* slow walk path */
        skp10_sk_rt_0034fe64();
        skp10_sk_rt_00351ea8();
        skp10_sk_rt_00351414();
        skp10_sk_rt_slot_0d();
        skp10_sk_rt_00319658();
        skp10_sk_rt_00310924();
        skp10_sk_rt_0034c3c4();
        skp10_sk_rt_0035145c();
        skp10_sk_lock_ref(0);                 /* FUN_00377bec */
        skp10_sk_rt_00027754();
        while (true) {
            skp10_sk_rt_003531a8();
            skp10_sk_rt_003516f0();
            (*(void (**)(void))skp10_sk_rt_00319658())();
            skp10_sk_rt_0035a3ac();
            skp10_sk_rt_00351414();
            (*(void (**)(void))skp10_sk_rt_00310924())();
            skp10_sk_rt_00350a04();
            skp10_sk_rt_003512cc();
            v = (*(uint64_t (**)(void))skp10_sk_rt_0014ae44())();
            (*(void (**)(void))(skp10_sk_rt_slot_2f() + 8))();
            skp10_sk_rt_0035a76c();
            skp10_sk_rt_00350a34();
            (*(void (**)(void))(skp10_sk_rt_slot_2f() + 8))();
            if ((v & 1) != 0) break;
            skp10_sk_rt_0035a1b4();
            (*(void (**)(void))(0 + 0))();
            skp10_sk_rt_00352ecc();
            skp10_sk_rt_00355908((uint64_t*)sk_scratch, 0);
            (*(void (**)(void))skp10_sk_rt_slot_0d())();
            skp10_sk_rt_00358dac();
            (*(void (**)(uint64_t, uint64_t, uint64_t))skp10_sk_rt_slot_0d())(0, 0, u);
            skp10_sk_rt_0034c3b4();
            (*(void (**)(void))skp10_sk_rt_slot_0d())();
            v = (*(uint64_t (**)(uint64_t))0)(0);
            skp10_sk_rt_00354f80();
            (*(void (**)(uint64_t, uint64_t))skp10_sk_rt_slot_0d())(0, u);
            if ((v & 1) == 0) break;
            (*(void (**)(uint64_t, uint64_t))(skp10_sk_rt_slot_2f() + 8))(0, 0);
            skp10_sk_rt_00355224();
            skp10_sk_rt_00350738();
            skp10_sk_rt_slot_0d(0, 0, 0);
        }
        (*(void (**)(uint64_t, uint64_t))(skp10_sk_rt_slot_2f() + 8))(0, 0);
    } else {
        /* fast walk path */
        skp10_sk_rt_00356200();
        skp10_sk_rt_00350088();
        skp10_sk_rt_slot_0d();
        skp10_sk_rt_0034fe64();
        skp10_sk_rt_00351414();
        skp10_sk_rt_slot_0d();
        skp10_sk_rt_0034c3c4();
        skp10_sk_rt_0035145c();
        skp10_sk_lock_ref(0);                 /* FUN_00377bec */
        skp10_sk_rt_00351bec();
        skp10_sk_rt_0014ae44();
        u = skp10_sk_rt_00350a40();
        skp10_sk_rt_003512cc(u, 0);
        v = (*(uint64_t (**)(void))skp10_sk_rt_slot_0d())();
        (*(void (**)(void))(skp10_sk_rt_slot_2f() + 8))();
        skp10_sk_rt_00350618();
        (*(void (**)(void))(skp10_sk_rt_slot_2f() + 8))();
        if ((v & 1) != 0) {
            skp10_sk_rt_00350410();
            skp10_sk_rt_003488bc();
            skp10_sk_rt_003526a4();
            skp10_sk_rt_00352be0();
            skp10_sk_swift_fatal();
        }
        skp10_sk_rt_00354abc();
        skp10_sk_rt_0031e104();
        skp10_sk_rt_00350b30();
        skp10_sk_rt_0034e5cc();
        skp10_sk_rt_slot_0d();
        (*(void (**)(uint64_t, uint64_t))(skp10_sk_rt_slot_2f() + 8))(0, 0);
    }
    skp10_sk_rt_0034ff78(0);
    sk_vspace_ep_reply(0, 0, 0);
    skp10_sk_rt_0008e500(0);
}

/*--------------------------------------------------------------------*/
/* FUN_0026a1ac @ 0x0026a1ac   (est. sk_vspace_scan_b)
 * Ghidra: void skp10_sk_rt_0026a1ac(undefined8, undefined8, ulong)
 * Scan variant dispatching through callbacks.
 * Confidence: low.
 */
void sk_vspace_scan_b(uint64_t p1, uint64_t p2, uint64_t p3)
{
    uint64_t u;
    skp10_sk_rt_00084220();
    skp10_sk_rt_00352700();
    skp10_sk_rt_0035089c();
    u = *(uint64_t *)((p3 & 0xfffffffffffffffeull) - 8);
    skp10_sk_rt_00027754(u);
    skp10_sk_rt_0034e414();
    (*(void (**)(void))0)();
    skp10_sk_rt_00348e00();
    skp10_sk_rt_0007c1a4();
    skp10_sk_rt_0034a2c0();
    skp10_sk_rt_00350600();
    skp10_sk_rt_slot_0d();
    skp10_sk_rt_0035084c();
    (*(void (**)(uint64_t, uint64_t, uint64_t))0)(0, 0, u);
    skp10_sk_rt_003507d4(*(uint64_t *)(skp10_sk_rt_slot_2f() + 8));
    skp10_sk_rt_slot_0d();
    skp10_sk_rt_00084234(0);
}

/*--------------------------------------------------------------------*/
/* FUN_0026a278 @ 0x0026a278   (est. sk_vspace_noreturn_a)
 * Ghidra: void skp10_sk_rt_0026a278(undefined8, undefined8, long param_3)
 * Dispatch then SoftwareBreakpoint (unreachable) — a noreturn trap stub.
 * Confidence: high (explicit SoftwareBreakpoint).
 */
void sk_vspace_noreturn_a(uint64_t p1, uint64_t p2, long p3)
{
    skp10_sk_rt_0034ece8(p1, *(uint64_t *)(p3 + 0x18));
    (*(void (**)(void))(skp10_sk_rt_slot_2f() + 8))();
    SoftwareBreakpoint(1, 0x26a2ac);
}

/*--------------------------------------------------------------------*/
/* FUN_0026a27c @ 0x0026a27c   (est. sk_vspace_noreturn_b)
 * Ghidra: void skp10_sk_rt_0026a27c(undefined8, undefined8, long param_3)
 * Duplicate noreturn trap stub.
 * Confidence: high.
 */
void sk_vspace_noreturn_b(uint64_t p1, uint64_t p2, long p3)
{
    skp10_sk_rt_0034ece8(p1, *(uint64_t *)(p3 + 0x18));
    (*(void (**)(void))(skp10_sk_rt_slot_2f() + 8))();
    SoftwareBreakpoint(1, 0x26a2ac);
}

/*--------------------------------------------------------------------*/
/* FUN_0026a2ac @ 0x0026a2ac   (est. sk_vspace_noreturn_c)
 * Ghidra: void skp10_sk_rt_0026a2ac(void)
 * Noreturn trap stub dispatching through FUN_0026a2bc.
 * Confidence: high.
 */
void sk_vspace_noreturn_c(void)
{
    skp10_sk_rt_0026a2bc();
    skp10_sk_rt_0034ece8(0, *(uint64_t *)(skp10_sk_rt_slot_0d() + 0x10), (uint64_t)sk_vspace_noreturn_d);
    (*(void (**)(void))(skp10_sk_rt_slot_2f() + 8))();
    SoftwareBreakpoint(1, 0x26a2f0);
}

/*--------------------------------------------------------------------*/
/* FUN_0026a2bc @ 0x0026a2bc   (est. sk_vspace_noreturn_d)
 * Ghidra: void skp10_sk_rt_0026a2bc(undefined8 param_1, long param_2)
 * Noreturn trap stub.
 * Confidence: high.
 */
void sk_vspace_noreturn_d(uint64_t p1, long p2)
{
    skp10_sk_rt_0034ece8(p1, *(uint64_t *)(p2 + 0x10));
    (*(void (**)(void))(skp10_sk_rt_slot_2f() + 8))();
    SoftwareBreakpoint(1, 0x26a2f0);
}

/*--------------------------------------------------------------------*/
/* FUN_0026a2f0 @ 0x0026a2f0   (est. sk_vspace_noreturn_e)
 * Ghidra: void skp10_sk_rt_0026a2f0(undefined8, undefined8, long param_3)
 * Noreturn trap stub.
 * Confidence: high.
 */
void sk_vspace_noreturn_e(uint64_t p1, uint64_t p2, long p3)
{
    skp10_sk_rt_0034ece8(p2, *(uint64_t *)(p3 + 0x10));
    (*(void (**)(void))(skp10_sk_rt_slot_2f() + 8))();
    SoftwareBreakpoint(1, 0x26a328);
}

/*--------------------------------------------------------------------*/
/* FUN_0026a2f4 @ 0x0026a2f4   (est. sk_vspace_noreturn_f)
 * Ghidra: void skp10_sk_rt_0026a2f4(undefined8, undefined8, long param_3)
 * Noreturn trap stub.
 * Confidence: high.
 */
void sk_vspace_noreturn_f(uint64_t p1, uint64_t p2, long p3)
{
    skp10_sk_rt_0034ece8(p2, *(uint64_t *)(p3 + 0x10));
    (*(void (**)(void))(skp10_sk_rt_slot_2f() + 8))();
    SoftwareBreakpoint(1, 0x26a328);
}

/*--------------------------------------------------------------------*/
/* FUN_0026a328 @ 0x0026a328   (est. skp10_sk_table_lookup)
 * Ghidra: bool skp10_sk_rt_0026a328(long *param_1, long param_2)
 * Hash-table lookup keyed by a 64-bit hash. Walks the open-addressing table
 * (bitmap at +0x38, entry array at +0x30, slot width 8 bytes) starting from
 * hash index; on match stores the entry in *param_1 and returns false;
 * otherwise inserts the key (FUN_0025c33c) and returns true.
 * Confidence: medium (clear open-addressing table pattern).
 */
bool skp10_sk_table_lookup(long *out, long key)
{
    uint64_t h, bit;
    long tbl;
    h = skp10_sk_rtt_00229ebc(*(uint64_t *)(0 + 0x28));
    tbl = 0;
    while (true) {
        h &= ~(-1ull << ((uint64_t)*(uint8_t *)(tbl + 0x20) & 0x3f));
        bit = 1ull << (h & 0x3f) & *(uint64_t *)(tbl + 0x38 + (h >> 6) * 8);
        if (bit == 0) break;
        if (*(long *)(*(long *)(tbl + 0x30) + h * 8) == key) goto found;
        h = h + 1;
    }
    skp10_sk_table_insert_8((void *)key, h, skp10_sk_hash64(tbl)); /* FUN_0025c33c */
    tbl = 0;
    *(uint64_t*)sk_scratch = -0x8000000000000000ll;
    skp10_sk_rt_0025c33c(key, h, skp10_sk_hash64(0));
    *(uint64_t*)sk_scratch = tbl;
found:
    *out = key;
    return bit == 0;
}

/*--------------------------------------------------------------------*/
/* FUN_0026a404 @ 0x0026a404   (est. skp10_sk_table_put_entries)
 * Ghidra: void skp10_sk_rt_0026a404(undefined8, undefined8, ulong)
 * Table put with 2-word entries (slot width 0x10). Walks the table looking
 * for a {key,value} match; on match releases and returns; on free slot
 * inserts via FUN_0025c460. Compares tag bits (0x6000000000000000).
 * Confidence: medium.
 */
void skp10_sk_table_put_entries(uint64_t p1, uint64_t p2, uint64_t p3)
{
    uint64_t h, bit;
    long tbl = 0;
    skp10_sk_rt_00355578();
    skp10_sk_rt_00349bc4(*(uint64_t *)(tbl + 0x28));
    skp10_sk_rt_0034a5dc();
    skp10_sk_rt_0034af48();
    skp10_sk_rt_001b9084((uint64_t*)sk_scratch);
    skp10_sk_rt_001a8564();
    h = skp10_sk_hash_start(*(uint8_t *)(tbl + 0x20)); /* FUN_00354948 */
    do {
        h &= ~0;
        bit = 1ull << (h & 0x3f) & *(uint64_t *)(tbl + 0x38 + (h >> 6) * 8);
        if (bit == 0) {
            skp10_sk_rt_00352414();
            skp10_sk_alloc_pages(p3, 0);      /* thunk_FUN_0036b270 */
            skp10_sk_rt_00350560();
            skp10_sk_table_insert_16(0, 0, h, skp10_sk_hash64(*(uint64_t*)sk_scratch)); /* FUN_0025c460 */
            *(uint64_t*)sk_scratch = 0;
            *(uint64_t*)sk_scratch = 0;
            ((uint64_t*)sk_scratch)[1] = p3;
            skp10_sk_rt_00354458(bit == 0, 0);
            return;
        }
        {
            long *ent = (long *)(*(long *)(tbl + 0x30) + h * 0x10);
            uint64_t v = ent[1];
            if (*ent == 0 && v == p3) {
                skp10_sk_msg_dispatch(p3);
                ent = (long *)(*(long *)(tbl + 0x30) + h * 0x10);
                *(uint64_t*)sk_scratch = *ent;
                ((uint64_t*)sk_scratch)[1] = ent[1];
                skp10_sk_alloc_pages(0, 0);
                skp10_sk_rt_00354458(true, 0);
                return;
            }
            if (((v ^ 0xffffffffffffffffull) & 0x6000000000000000ull) != 0 ||
                (p3 & 0x6000000000000000ull) != 0x6000000000000000ull) {
                skp10_sk_rt_00351584();
                if ((skp10_sk_rt_002a0d50() & 1) != 0) {
                    skp10_sk_msg_dispatch(p3);
                    *(uint64_t*)sk_scratch = *ent;
                    ((uint64_t*)sk_scratch)[1] = ent[1];
                    skp10_sk_alloc_pages(0, 0);
                    skp10_sk_rt_00354458(true, 0);
                    return;
                }
            }
        }
        h = h + 1;
    } while (true);
}

/*--------------------------------------------------------------------*/
/* FUN_0026a560 @ 0x0026a560   (est. skp10_sk_table_get_entries)
 * Ghidra: void skp10_sk_rt_0026a560(void)
 * Table get with 0x28-byte entries: walks the table, compares the entry key,
 * and on match returns the entry; on free slot inserts via FUN_0025c570.
 * Confidence: low.
 */
void skp10_sk_table_get_entries(void)
{
    uint64_t h, bit;
    long tbl = 0;
    skp10_sk_rt_003583e8();
    skp10_sk_rt_0034bca4();
    skp10_sk_rt_000dbd0c((uint64_t*)sk_scratch);
    skp10_sk_rt_slot_0d();
    skp10_sk_rt_0034c4dc((uint64_t*)sk_scratch);
    skp10_sk_rt_0031993c();
    skp10_sk_rt_0034ce58();
    h = (*(uint64_t (**)(void))skp10_sk_rt_slot_0d())();
    skp10_sk_rt_000026e8((uint64_t*)sk_scratch);
    skp10_sk_rt_0035377c();
    h &= ~0;
    if ((*(uint64_t *)(tbl + 0x38 + (h >> 6) * 8) >> (h & 0x3f) & 1) != 0) {
        do {
            skp10_sk_rt_00358124();
            skp10_sk_rt_0031996c(0 + h * 0, (uint64_t*)sk_scratch);
            skp10_sk_rt_0034bca4((uint64_t*)sk_scratch);
            skp10_sk_rt_000dbd0c((uint64_t*)sk_scratch);
            skp10_sk_rt_slot_0d();
            skp10_sk_rt_0006a4c0((uint64_t*)sk_scratch, 0);
            skp10_sk_rt_0035190c();
            skp10_sk_rt_000dbcc8();
            skp10_sk_rt_00353b1c(0);
            skp10_sk_rt_00350944((uint64_t*)sk_scratch);
            skp10_sk_rt_slot_0d();
            skp10_sk_rt_0031997c(0);
            skp10_sk_rt_00350b18(0, (uint64_t*)sk_scratch);
            bit = (*(uint64_t (**)(void))skp10_sk_rt_slot_0d())();
            skp10_sk_rt_000026e8((uint64_t*)sk_scratch);
            skp10_sk_rt_000026e8((uint64_t*)sk_scratch);
            skp10_sk_rt_003199ac((uint64_t*)sk_scratch);
            if ((bit & 1) != 0) {
                skp10_sk_rt_003199ac(0);
                skp10_sk_rt_0031996c(*(long *)(tbl + 0x30) + h * 0x28, 0);
                skp10_sk_rt_00358454(0, 0);
                return;
            }
            h = h + 1 & ~0;
        } while ((*(uint64_t *)(tbl + 0x38 + (h >> 6) * 8) >> (h & 0x3f) & 1) != 0);
    }
    skp10_sk_rt_0031996c(0, (uint64_t*)sk_scratch);
    skp10_sk_rt_00352414();
    skp10_sk_table_insert_28(0, 0, h, skp10_sk_hash64(*(uint64_t*)sk_scratch)); /* FUN_0025c570 */
    *(uint64_t*)sk_scratch = 0;
    skp10_sk_rt_0025c570(0, h, 0);
    ((uint64_t*)sk_scratch)[1] = 0;
    *(uint64_t*)sk_scratch = 0;
    ((uint64_t*)sk_scratch)[3] = 0;
    ((uint64_t*)sk_scratch)[2] = 0;
    ((uint64_t*)sk_scratch)[4] = 0;
    skp10_sk_rt_00358454(1, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_0026a744 @ 0x0026a744   (est. skp10_sk_table_lookup_b)
 * Ghidra: bool skp10_sk_rt_0026a744(undefined8 *param_1, undefined8 *param_2)
 * Hash-table lookup with 0x28-byte keyed entries. Uses the entry's hash
 * (via FUN_0008e5d8/FUN_0031993c), walks the table, and on match copies the
 * 5-word entry into *param_1; on miss inserts via FUN_0025c754.
 * Confidence: low.
 */
bool skp10_sk_table_lookup_b(uint64_t *out, uint64_t *in)
{
    uint64_t h, bit;
    long tbl = 0;
    uint64_t k3 = in[3], k4 = in[4];
    skp10_sk_rt_0006a4c0(in, k3);
    (*(void (**)(uint64_t, uint64_t, uint64_t))skp10_sk_rt_0008e5d8(k4))(0, k3, k4);
    h = (*(uint64_t (**)(uint64_t, uint64_t, uint64_t))skp10_sk_rt_0031993c(0))(0, 0, 0);
    skp10_sk_rt_000026e8(0);
    do {
        h &= ~(-1ull << ((uint64_t)*(uint8_t *)(tbl + 0x20) & 0x3f));
        bit = 1ull << (h & 0x3f) & *(uint64_t *)(tbl + 0x38 + (h >> 6) * 8);
        if (bit == 0) {
            skp10_sk_rt_0031996c(in, 0);
            *(uint64_t*)sk_scratch = -0x8000000000000000ll;
            skp10_sk_table_insert_k(0, h, skp10_sk_hash64(*(uint64_t*)sk_scratch)); /* FUN_0025c754 */
            *(uint64_t*)sk_scratch = 0;
            out[0] = in[0]; out[1] = in[1]; out[2] = in[2];
            out[3] = in[3]; out[4] = in[4];
            return true;
        }
        skp10_sk_rt_0031996c(*(long *)(tbl + 0x30) + h * 0x28, 0);
        skp10_sk_rt_0006a4c0(0, 0);
        (*(void (**)(uint64_t, uint64_t, uint64_t))skp10_sk_rt_0008e5d8(0))(0, 0, 0);
        skp10_sk_rt_0006a4c0(0, 0);
        skp10_sk_rt_0006a4c0(in, in[3]);
        (*(void (**)(uint64_t, uint64_t, uint64_t))skp10_sk_rt_0008e5d8(in[4]))(0, in[3], in[4]);
        h = (*(uint64_t (**)(void))skp10_sk_rt_0031997c(0))();
        skp10_sk_rt_000026e8(0);
        skp10_sk_rt_000026e8(0);
        skp10_sk_rt_003199ac(0);
        if ((h & 1) != 0) {
            skp10_sk_rt_003199ac(in);
            skp10_sk_rt_0031996c(*(long *)(tbl + 0x30) + h * 0x28, out);
            return bit == 0;
        }
        h = h + 1;
    } while (true);
}

/*--------------------------------------------------------------------*/
/* FUN_0026a9a8 @ 0x0026a9a8   (est. sk_table_lookup_c)
 * Ghidra: bool skp10_sk_rt_0026a9a8(long *param_1, long param_2)
 * Table lookup with 8-byte slots (like FUN_0026a328 but insert via
 * FUN_0025c9a8). Returns false on hit, true on inserted.
 * Confidence: medium.
 */
bool sk_table_lookup_c(long *out, long key)
{
    uint64_t h, bit;
    long tbl = 0;
    h = skp10_sk_rtt_00229ebc(*(uint64_t *)(tbl + 0x28));
    while (true) {
        h &= ~(-1ull << ((uint64_t)*(uint8_t *)(tbl + 0x20) & 0x3f));
        bit = 1ull << (h & 0x3f) & *(uint64_t *)(tbl + 0x38 + (h >> 6) * 8);
        if (bit == 0) break;
        if (*(long *)(*(long *)(tbl + 0x30) + h * 8) == key) goto found;
        h = h + 1;
    }
    {
        uint64_t hv = skp10_sk_hash64(tbl);
        tbl = 0;
        *(uint64_t*)sk_scratch = -0x8000000000000000ll;
        skp10_sk_table_insert_8b((void *)key, h, hv); /* FUN_0025c9a8 */
        *(uint64_t*)sk_scratch = tbl;
    }
found:
    *out = key;
    return bit == 0;
}

/*--------------------------------------------------------------------*/
/* FUN_0026aa7c @ 0x0026aa7c   (est. skp10_sk_table_put_entry)
 * Ghidra: void skp10_sk_rt_0026aa7c(undefined8, undefined8, long param_3)
 * Table put with 0x28-byte entries: reads the key/value from param_3,
 * computes the hash, walks the table, and on free slot inserts via
 * FUN_0025cac8 (releasing the old entry with FUN_0036b118); on match
 * dispatches and returns.
 * Confidence: low.
 */
void skp10_sk_table_put_entry(uint64_t p1, uint64_t p2, long p3)
{
    uint64_t h, bit, key;
    long tbl = 0;
    skp10_sk_cpu();                           /* FUN_0008e518 */
    skp10_sk_rt_003494e8();
    key = *(uint64_t *)(p3 + 0x10);
    skp10_sk_rt_00349068();
    tbl = 0;
    skp10_sk_rt_00350678(*(uint64_t *)(p3 + 0x18));
    skp10_sk_rt_slot_0d(key, *(uint64_t *)(p3 + 0x10), *(uint64_t *)(p3 + 0x18));
    h = skp10_sk_hash_start(*(uint8_t *)(tbl + 0x20)); /* FUN_00354948 */
    do {
        h &= ~0;
        bit = 1ull << (h & 0x3f) & *(uint64_t *)(0 + (h >> 6) * 8);
        if (bit == 0) {
            skp10_sk_rt_0035056c(*(uint64_t *)(0 + 0x10));
            skp10_sk_rt_slot_0d();
            *(uint64_t*)sk_scratch = -0x8000000000000000ll;
            skp10_sk_rt_003504e8();
            skp10_sk_rt_0031d5d8(0, 0, *(uint64_t *)(p3 + 0x18));
            skp10_sk_rt_00350a04();
            skp10_sk_table_insert_28b(0, 0, skp10_sk_hash64(*(uint64_t*)sk_scratch)); /* FUN_0025cac8 */
            skp10_sk_rt_00351560(0, (uint64_t*)sk_scratch);
            skp10_sk_rt_001fb194();
            skp10_sk_free((void *)0);         /* FUN_0036b118 */
            skp10_sk_rt_0035056c(*(uint64_t *)(0 + 0x20), 0);
            skp10_sk_rt_slot_0d();
            skp10_sk_rt_0008e500(bit == 0, 0);
            return;
        }
        skp10_sk_rt_0035a28c(tbl);
        (*(void (**)(uint64_t))(0 + 0x10))(0 + 0x10);
        skp10_sk_rt_00352ee4(*(uint64_t *)(p3 + 0x18));
        skp10_sk_rt_0014ae44();
        skp10_sk_rt_00350648();
        skp10_sk_rt_00350ac4(0, 0);
        bit = (*(uint64_t (**)(void))skp10_sk_rt_slot_0d())();
        (*(void (**)(void))(0 + 8))();
        skp10_sk_rt_003505e8();
        (*(void (**)(void))(0 + 8))();
        if ((bit & 1) != 0) {
            skp10_sk_rt_0035684c();
            (*(void (**)(void))(0 + 8))();
            (*(void (**)(void))(0 + 0x10))();
            goto done;
        }
        h = h + 1;
    } while (true);
done:
    skp10_sk_rt_0008e500(0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_0026acbc @ 0x0026acbc   (est. skp10_sk_table_remove_entry)
 * Ghidra: void skp10_sk_rt_0026acbc(void)
 * Table entry removal: walks the table; on a match (tag comparison) releases
 * the entry and returns; else falls to the bitmap clear path.
 * Confidence: low.
 */
void skp10_sk_table_remove_entry(void)
{
    long tbl = 0;
    uint64_t h;
    skp10_sk_rt_000b4594();
    skp10_sk_rt_003509ec();
    tbl = 0;
    skp10_sk_rt_00349bc4(*(uint64_t *)(tbl + 0x28));
    skp10_sk_rt_0034a5dc();
    skp10_sk_rt_00351624();
    skp10_sk_rt_0034af48();
    skp10_sk_rt_00355334();
    skp10_sk_rt_00077894();
    skp10_sk_rt_001b9084();
    skp10_sk_rt_001a8564();
    h = skp10_sk_hash_start(*(uint8_t *)(tbl + 0x20)); /* FUN_00354948 */
    do {
        skp10_sk_rt_00359ec0(h);
        if ((0 & 1) == 0) {
            skp10_sk_rt_000b4390();
            skp10_sk_rt_000b45b0(0, 0, 0);
            return;
        }
        skp10_sk_rt_00359704();
        if ((bool)0 && 0 == 0) {
            skp10_sk_hash64(*(uint64_t*)sk_scratch);
            tbl = 0;
            skp10_sk_rt_00352414();
            skp10_sk_table_rm_8();            /* FUN_0025b4e8 */
            skp10_sk_table_rm_16();           /* FUN_0025db98 */
            *(uint64_t*)sk_scratch = tbl;
            skp10_sk_rt_000b4390();
            skp10_sk_rt_000b45b0(0, 0, 0);
            return;
        }
        skp10_sk_rt_00359d70();
        if (!((0 & 0x6000000000000000ull) == 0x6000000000000000ull)) {
            skp10_sk_rt_00351b78();
            skp10_sk_rt_002a0d50();
        }
        h = h + 1;
    } while (true);
}

/*--------------------------------------------------------------------*/
/* FUN_0026adcc @ 0x0026adcc   (est. skp10_sk_table_get_entry)
 * Ghidra: void skp10_sk_rt_0026adcc(void)
 * Table get with 0x28-byte entries (like FUN_0026a560): walks, on match
 * copies the entry and clears the bitmap slot via FUN_0025dee4; else zeroes
 * the output.
 * Confidence: low.
 */
void skp10_sk_table_get_entry(void)
{
    long tbl = 0;
    uint64_t h, bit;
    skp10_sk_rt_003583e8();
    tbl = 0;
    skp10_sk_rt_0034bca4();
    skp10_sk_rt_000dbd0c((uint64_t*)sk_scratch);
    skp10_sk_rt_slot_0d();
    skp10_sk_rt_0034c4dc((uint64_t*)sk_scratch);
    skp10_sk_rt_0031993c();
    skp10_sk_rt_0034ce58();
    h = (*(uint64_t (**)(void))skp10_sk_rt_slot_0d())();
    skp10_sk_rt_000026e8((uint64_t*)sk_scratch);
    skp10_sk_rt_0035377c();
    h &= ~0;
    if ((*(uint64_t *)(tbl + 0x38 + (h >> 6) * 8) >> (h & 0x3f) & 1) != 0) {
        do {
            skp10_sk_rt_00358124();
            skp10_sk_rt_0031996c(0 + h * 0, (uint64_t*)sk_scratch);
            skp10_sk_rt_0034bca4((uint64_t*)sk_scratch);
            skp10_sk_rt_000dbd0c((uint64_t*)sk_scratch);
            skp10_sk_rt_slot_0d();
            skp10_sk_rt_0006a4c0((uint64_t*)sk_scratch, 0);
            skp10_sk_rt_00350c80();
            skp10_sk_rt_000dbcc8();
            skp10_sk_rt_00353b1c(*(uint64_t *)(0 + 0x20));
            skp10_sk_rt_00350944((uint64_t*)sk_scratch);
            skp10_sk_rt_slot_0d();
            skp10_sk_rt_0031997c(0);
            skp10_sk_rt_00350b18(0, (uint64_t*)sk_scratch);
            bit = (*(uint64_t (**)(void))skp10_sk_rt_slot_0d())();
            skp10_sk_rt_000026e8((uint64_t*)sk_scratch);
            skp10_sk_rt_000026e8((uint64_t*)sk_scratch);
            skp10_sk_rt_003199ac((uint64_t*)sk_scratch);
            if ((bit & 1) != 0) {
                skp10_sk_hash64(*(uint64_t*)sk_scratch);
                *(uint64_t*)sk_scratch = -0x8000000000000000ll;
                skp10_sk_table_rm_28();       /* FUN_0025b5e0 */
                tbl = *(uint64_t*)sk_scratch;
                {
                    uint64_t *ent = (uint64_t *)(*(long *)(*(uint64_t*)sk_scratch + 0x30) + h * 0x28);
                    ((uint64_t*)sk_scratch)[0] = ent[0]; ((uint64_t*)sk_scratch)[1] = ent[1]; ((uint64_t*)sk_scratch)[2] = ent[2];
                    ((uint64_t*)sk_scratch)[3] = ent[3]; ((uint64_t*)sk_scratch)[4] = ent[4];
                }
                skp10_sk_table_rm_28b(h);     /* FUN_0025dee4 */
                *(uint64_t*)sk_scratch = tbl;
                goto out;
            }
            h = h + 1 & ~0;
        } while ((*(uint64_t *)(tbl + 0x38 + (h >> 6) * 8) >> (h & 0x3f) & 1) != 0);
    }
    ((uint64_t*)sk_scratch)[0] = 0; ((uint64_t*)sk_scratch)[1] = 0; ((uint64_t*)sk_scratch)[2] = 0; ((uint64_t*)sk_scratch)[3] = 0; ((uint64_t*)sk_scratch)[4] = 0;
out:
    skp10_sk_rt_00358454(0);
}

/*--------------------------------------------------------------------*/
/* FUN_0026af9c @ 0x0026af9c   (est. skp10_sk_table_lookup_d)
 * Ghidra: void skp10_sk_rt_0026af9c(undefined8 *param_1, long param_2)
 * Table lookup with 0x28-byte keyed entries: walks, compares keys via
 * FUN_0008e5d8/FUN_0031997c, and on match copies the entry into *param_1
 * and clears via FUN_0025dee4; on miss zeroes the output.
 * Confidence: low.
 */
void skp10_sk_table_lookup_d(uint64_t *out, long in)
{
    long tbl = 0;
    uint64_t h, bit;
    skp10_sk_rt_0006a4c0((uint64_t *)in, *(uint64_t *)(in + 0x18));
    (*(void (**)(uint64_t, uint64_t, uint64_t))skp10_sk_rt_0008e5d8(*(uint64_t *)(in + 0x20)))(0, *(uint64_t *)(in + 0x18), *(uint64_t *)(in + 0x20));
    h = (*(uint64_t (**)(void))skp10_sk_rt_0031993c(*(uint64_t *)(in + 0x20)))();
    skp10_sk_rt_000026e8(0);
    while (true) {
        h &= ~(-1ull << ((uint64_t)*(uint8_t *)(tbl + 0x20) & 0x3f));
        if ((*(uint64_t *)(tbl + 0x38 + (h >> 6) * 8) >> (h & 0x3f) & 1) == 0) {
            out[0] = 0; out[1] = 0; out[2] = 0; out[3] = 0; out[4] = 0;
            return;
        }
        skp10_sk_rt_0031996c(*(long *)(tbl + 0x30) + h * 0x28, 0);
        skp10_sk_rt_0006a4c0(0, 0);
        (*(void (**)(uint64_t, uint64_t, uint64_t))skp10_sk_rt_0008e5d8(0))(0, 0, 0);
        skp10_sk_rt_0006a4c0(0, 0);
        skp10_sk_rt_0006a4c0((uint64_t *)in, *(uint64_t *)(in + 0x18));
        (*(void (**)(uint64_t, uint64_t, uint64_t))skp10_sk_rt_0008e5d8(*(uint64_t *)(in + 0x20)))(0, *(uint64_t *)(in + 0x18), *(uint64_t *)(in + 0x20));
        bit = (*(uint64_t (**)(void))skp10_sk_rt_0031997c(0))();
        skp10_sk_rt_000026e8(0);
        skp10_sk_rt_000026e8(0);
        skp10_sk_rt_003199ac(0);
        if ((bit & 1) != 0) break;
        h = h + 1;
    }
    skp10_sk_hash64(*(uint64_t*)sk_scratch);
    *(uint64_t*)sk_scratch = -0x8000000000000000ll;
    skp10_sk_table_rm_28();                   /* FUN_0025b5e0 */
    tbl = *(uint64_t*)sk_scratch;
    {
        uint64_t *ent = (uint64_t *)(*(long *)(*(uint64_t*)sk_scratch + 0x30) + h * 0x28);
        out[0] = ent[0]; out[1] = ent[1]; out[2] = ent[2];
        out[3] = ent[3]; out[4] = ent[4];
    }
    skp10_sk_table_rm_28b(h);                 /* FUN_0025dee4 */
    *(uint64_t*)sk_scratch = tbl;
}

/*--------------------------------------------------------------------*/
/* FUN_0026b1dc @ 0x0026b1dc   (est. sk_table_remove_matching)
 * Ghidra: void skp10_sk_rt_0026b1dc(void)
 * Table entry removal matching a predicate: walks the table, and on a match
 * (bit test) clears the slot (FUN_0025b7d8 / FUN_0025e000) and releases the
 * entry.
 * Confidence: low.
 */
void sk_table_remove_matching(void)
{
    long tbl = 0;
    uint64_t h, bit, u;
    skp10_sk_cpu();                           /* FUN_0008e518 */
    skp10_sk_rt_003494e8();
    skp10_sk_rt_0034947c();
    tbl = 0;
    skp10_sk_rt_00350678(*(uint64_t *)(skp10_sk_rt_slot_0d() + 0x18));
    skp10_sk_rt_00350878();
    skp10_sk_rt_slot_0d();
    h = skp10_sk_rt_0035216c();
    do {
        h &= ~0;
        if ((*(uint64_t *)(tbl + 0x38 + (h >> 6) * 8) >> (h & 0x3f) & 1) == 0) {
            skp10_sk_rt_0034dba8(h, 1);
            skp10_sk_rt_000839d8();
            skp10_sk_rt_0008e500(0);
            return;
        }
        (*(void (**)(uint64_t))(0 + 0x10))(0 + 0x10);
        skp10_sk_rt_0034a30c(0);
        skp10_sk_rt_0034beec();
        skp10_sk_rt_slot_0d();
        skp10_sk_rt_00357b04();
        skp10_sk_rt_003509d4();
        skp10_sk_rt_slot_0d();
        if ((0 & 1) != 0) {
            u = skp10_sk_hash64(*(uint64_t*)sk_scratch);
            *(uint64_t*)sk_scratch = -0x8000000000000000ll;
            skp10_sk_rt_003504e8();
            skp10_sk_rt_0031d5d8(0, 0, 0);
            skp10_sk_table_rm_28c();          /* FUN_0025b7d8 */
            tbl = *(uint64_t*)sk_scratch;
            skp10_sk_rt_00353fa0(u, *(long *)(*(uint64_t*)sk_scratch + 0x30) + 0 * h);
            skp10_sk_rt_slot_0d();
            skp10_sk_rt_003504e8();
            skp10_sk_rt_0031d5d8(0, 0, 0);
            skp10_sk_rt_00357a9c();
            skp10_sk_table_rm_28d(h);         /* FUN_0025e000 */
            skp10_sk_rt_00350a1c(0, (uint64_t*)sk_scratch);
            skp10_sk_rt_001fb194();
            skp10_sk_free((void *)tbl);       /* FUN_0036b118 */
            skp10_sk_rt_0034dba8(h, 0);
            skp10_sk_rt_000839d8();
            skp10_sk_rt_0008e500(0);
            return;
        }
        h = h + 1;
    } while (true);
}

/*--------------------------------------------------------------------*/
/* FUN_0026b3c8 @ 0x0026b3c8   (est. sk_vspace_noreturn_g)
 * Ghidra: void skp10_sk_rt_0026b3c8(undefined8, undefined8, undefined8, long param_4)
 * Noreturn trap stub.
 * Confidence: high.
 */
void sk_vspace_noreturn_g(uint64_t p1, uint64_t p2, uint64_t p3, long p4)
{
    skp10_sk_rt_0034ece8(p1, *(uint64_t *)(p4 + 0x10));
    (*(void (**)(void))(skp10_sk_rt_slot_2f() + 8))();
    SoftwareBreakpoint(1, 0x26b3fc);
}

/*--------------------------------------------------------------------*/
/* FUN_0026b3cc @ 0x0026b3cc   (est. sk_vspace_noreturn_h)
 * Ghidra: void skp10_sk_rt_0026b3cc(undefined8, undefined8, undefined8, long param_4)
 * Noreturn trap stub.
 * Confidence: high.
 */
void sk_vspace_noreturn_h(uint64_t p1, uint64_t p2, uint64_t p3, long p4)
{
    skp10_sk_rt_0034ece8(p1, *(uint64_t *)(p4 + 0x10));
    (*(void (**)(void))(skp10_sk_rt_slot_2f() + 8))();
    SoftwareBreakpoint(1, 0x26b3fc);
}

/*--------------------------------------------------------------------*/
/* FUN_0026b3fc @ 0x0026b3fc   (est. sk_vspace_noreturn_i)
 * Ghidra: void skp10_sk_rt_0026b3fc(undefined8, undefined8, undefined8, undefined8)
 * Noreturn trap stub dispatching through FUN_003509c8.
 * Confidence: high.
 */
void sk_vspace_noreturn_i(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4)
{
    skp10_sk_rt_003509c8(p4, p1, p4);
    (*(void (**)(void))(skp10_sk_rt_slot_2f() + 8))();
    SoftwareBreakpoint(1, 0x26b434);
}

/*--------------------------------------------------------------------*/
/* FUN_0026b400 @ 0x0026b400   (est. sk_vspace_noreturn_j)
 * Ghidra: void skp10_sk_rt_0026b400(undefined8, undefined8, undefined8, undefined8)
 * Noreturn trap stub.
 * Confidence: high.
 */
void sk_vspace_noreturn_j(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4)
{
    skp10_sk_rt_003509c8(p4, p1, p4);
    (*(void (**)(void))(skp10_sk_rt_slot_2f() + 8))();
    SoftwareBreakpoint(1, 0x26b434);
}

/*--------------------------------------------------------------------*/
/* FUN_0026b434 @ 0x0026b434   (est. sk_vspace_teardown_list)
 * Ghidra: void skp10_sk_rt_0026b434(void)
 * Forwarder to FUN_0026b748.
 * Confidence: medium.
 */
void sk_vspace_teardown_list(void) { sk_vspace_walk_entries(0, 0, 0, 0, 0, 0, 0); }

/*--------------------------------------------------------------------*/
/* FUN_0026b460 @ 0x0026b460   (est. sk_vspace_iter_entries)
 * Ghidra: void skp10_sk_rt_0026b460(long param_1, ulong, ulong, undefined8,
 *                            undefined8, undefined1 (*param_6)[16])
 * Iterates the linked entry list (count at param_1+0x10, first node at
 * param_1+0x20) building a folded {value, tag} accumulator via
 * FUN_002a4c98/FUN_00291ee0, dispatching each node through FUN_00205844,
 * then tail-calls thunk_FUN_002acbb8.
 * Confidence: low.
 */
void sk_vspace_iter_entries(long list, uint64_t p2, uint64_t p3, uint64_t p4,
                            uint64_t p5, void **fn)
{
    long cnt = *(long *)(list + 0x10);
    uint64_t acc_v = 0, acc_t = 0xe000000000000000ull;
    if (cnt == 0) {
        skp10_sk_vspace_ipc_transition(p4, p5);
        return;
    }
    do {
        list += 0x20;
        cnt--;
        skp10_sk_rt_00319808((uint64_t *)list, (uint64_t *)fn);
        {
            uint64_t e0 = *(uint64_t *)*fn;
            uint64_t e1 = *(uint64_t *)(*fn + 8);
            uint64_t e6 = e0 & 0xffffffffffffull;
            if ((e1 & 0x2000000000000000ull) != 0) e6 = e1 >> 0x38 & 0xf;
            if ((e6 == 0) && (((e0 & (e1 ^ 0xffffffffffffffffull)) >> 0x3d & 1) == 0)) {
                skp10_sk_msg_dispatch(e1);
                *(uint64_t *)*fn = acc_v;
                *(uint64_t *)(*fn + 8) = acc_t;
            } else {
                uint64_t t = acc_t >> 0x38 & 0xf;
                uint64_t v;
                if ((e1 >> 0x3d & 1) == 0) {
                    v = acc_v & 0xffffffffffffull;
                    if ((acc_t & 0x2000000000000000ull) != 0) v = t;
                } else if ((acc_t >> 0x3d & 1) == 0) {
                    v = acc_v & 0xffffffffffffull;
                } else {
                    uint64_t lo = acc_v;
                    void *r = (void *)skp10_sk_rt_00291ee0(e0, e1, acc_v, acc_t);
                    if (((uint32_t)lo & 0xff) != 1) {
                        skp10_sk_msg_dispatch(e1);
                        skp10_sk_msg_dispatch(acc_t);
                        *fn = (void *)r;
                        goto next;
                    }
                    v = t;
                }
                skp10_sk_rt_002a4c98(acc_v, acc_t, 0, v);
                skp10_sk_msg_dispatch(acc_t);
            }
        }
next:
        skp10_sk_rt_00205844(fn, fn, 0x67b1e8, 0x6753a0, 0x66d1d8);
        skp10_sk_rt_000026e8(fn);
        if (cnt == 0) {
            skp10_sk_vspace_ipc_transition(p4, p5);
            return;
        }
        skp10_sk_alloc_pages(p3, 0);
        acc_t = p3;
        acc_v = p2;
    } while (true);
}

/*--------------------------------------------------------------------*/
/* FUN_0026b5e8 @ 0x0026b5e8   (est. sk_vspace_teardown_entries)
 * Ghidra: void skp10_sk_rt_0026b5e8(long param_1, undefined8, undefined8, undefined8,
 *                            undefined8, undefined8)
 * Entry-list teardown: iterates nodes dispatching each through FUN_00205844
 * and releasing via FUN_002676bc.
 * Confidence: low.
 */
void sk_vspace_teardown_entries(long list, uint64_t p2, uint64_t p3,
                                uint64_t p4, uint64_t p5, uint64_t p6)
{
    long cnt = *(long *)(list + 0x10);
    skp10_sk_vspace_lock_enter();
    if (cnt != 0) {
        skp10_sk_rt_00319808((uint64_t *)(list + 0x20), (uint64_t *)0);
        sk_vspace_object_create(0, 0xe000000000000000ull);
        skp10_sk_rt_00205844(0, (void *)p6, 0x67b1e8, 0x678490, &skp10_DAT_004f1818);
        skp10_sk_rt_000026e8(0);
        cnt--;
        if (cnt != 0) {
            list += 0x40;
            do {
                skp10_sk_rt_00319808((uint64_t *)list, (uint64_t *)0);
                sk_vspace_object_create(p2, p3);
                skp10_sk_rt_00205844(0, (void *)p6, 0x67b1e8, 0x678490, &skp10_DAT_004f1818);
                skp10_sk_rt_000026e8(0);
                list += 0x20;
                cnt--;
            } while (cnt != 0);
        }
    }
    sk_vspace_object_create(p4, p5);
    skp10_sk_vspace_lock_leave();
}

/*--------------------------------------------------------------------*/
/* FUN_0026b71c @ 0x0026b71c   (est. sk_vspace_teardown_list_b)
 * Ghidra: void skp10_sk_rt_0026b71c(void)
 * Forwarder to FUN_0026b748.
 * Confidence: medium.
 */
void sk_vspace_teardown_list_b(void) { sk_vspace_walk_entries(0, 0, 0, 0, 0, 0, 0); }

/*--------------------------------------------------------------------*/
/* FUN_0026b748 @ 0x0026b748   (est. sk_vspace_walk_entries)
 * Ghidra: void skp10_sk_rt_0026b748(undefined8, undefined8, ulong, ulong, ulong,
 *                            code*, code*)
 * Walks the vspace entry list, folding each node's {value,tag} pair through
 * the runtime (FUN_00349cbc / FUN_002a4c98), dispatching each via param_6,
 * and finally invokes the global walk callback (_DAT_006ade70) with the
 * accumulated pair. Tracks an in-flight allocator (thunk_FUN_0036b270).
 * Confidence: low.
 */
void sk_vspace_walk_entries(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4,
                            uint64_t p5, void (*fn)(void), void (*jt)(void))
{
    uint64_t acc_v = 0, acc_t = 0xe000000000000000ull;
    void (*cb)(uint64_t, uint64_t) = (void (*)(uint64_t, uint64_t))skp10_DAT_006ade70;
    skp10_sk_rt_00355578();
    skp10_sk_rt_0008409c();
    if (cb == 0) {
        skp10_sk_rt_0034ca28();
        skp10_sk_rt_00354458();
        (*jt)();
        return;
    }
    skp10_sk_alloc_pages(skp10_DAT_006ade78, 0);   /* FUN_0036b270 */
    skp10_sk_vspace_lock_enter();
    {
        long cnt = *(long *)(0 + 0x10);
        if (cnt != 0) {
            uint64_t u = 0;
            do {
                u += 0x20;
                cnt--;
                skp10_sk_rt_00319808((uint64_t *)u, (uint64_t *)0);
                {
                    uint64_t e = skp10_sk_rt_00349cbc(acc_v);
                    if ((0 == 0) && (((e & (acc_t ^ 0xffffffffffffffffull)) >> 0x3d & 1) == 0)) {
                        skp10_sk_alloc_pages(acc_t, 0);   /* thunk_FUN_0036b270 */
                        skp10_sk_msg_dispatch(acc_t);
                        acc_v = 0;
                        acc_t = 0xe000000000000000ull;
                    } else {
                        skp10_sk_rt_002a4c98();
                        acc_v = 0;
                    }
                }
                skp10_sk_rt_00100c38();
                sk_vspace_object_create();
                skp10_sk_msg_dispatch(acc_t);
                skp10_sk_rt_00002534(0x656258, &skp10_DAT_004e80b0);
                skp10_sk_rt_0034d274((uint64_t*)sk_scratch, (uint64_t*)sk_scratch);
                (*fn)();
                skp10_sk_rt_000026e8((uint64_t*)sk_scratch);
                acc_v = 0;
                acc_t = 0;
                if (cnt == 0) goto done;
                skp10_sk_alloc_pages(p3, 0);
                acc_v = p3;
                acc_t = 0;
            } while (true);
        }
        acc_v = 0;
        acc_t = 0xe000000000000000ull;
    }
done:
    skp10_sk_rt_00349cbc(acc_v);
    if ((0 == 0) && (((0 & (acc_t ^ 0xffffffffffffffffull)) >> 0x3d & 1) == 0)) {
        skp10_sk_alloc_pages(p5, 0);
        skp10_sk_msg_dispatch(acc_t);
        acc_v = p4;
        acc_t = p5;
    } else {
        skp10_sk_rt_0034dd64();
        skp10_sk_rt_002a4c98();
    }
    skp10_sk_rt_00100c38();
    sk_vspace_object_create();
    skp10_sk_vspace_lock_leave();
    (*cb)(acc_v, acc_t);
    skp10_sk_rt_0009e234();
    skp10_sk_rt_0031d5f0();
    skp10_sk_msg_dispatch(acc_t);
    skp10_sk_rt_00354458(0);
}

/*--------------------------------------------------------------------*/
/* FUN_0026b9d0 @ 0x0026b9d0   (est. sk_vspace_iter_entries_b)
 * Ghidra: void skp10_sk_rt_0026b9d0(long param_1, ulong, ulong, undefined8,
 *                            undefined8, undefined8)
 * Entry-list iteration variant: iterates nodes, folding each through
 * FUN_002a9ba8/FUN_003d30b0 with Swift nil-check fatal-error traps
 * ("Unexpectedly found nil while unwrapping"), then tail-calls
 * FUN_002676bc.
 * Confidence: low.
 */
void sk_vspace_iter_entries_b(long list, uint64_t p2, uint64_t p3,
                              uint64_t p4, uint64_t p5, uint64_t p6)
{
    long cnt = *(long *)(list + 0x10);
    skp10_sk_vspace_lock_enter();
    if (cnt != 0) {
        skp10_sk_rt_00319808((uint64_t *)(list + 0x20), (uint64_t *)0);
        sk_vspace_object_create(0, 0xe000000000000000ull);
        skp10_sk_rt_002060d4(0, (void *)p6, 0x67b1e8, 0x678490, &skp10_DAT_004f1818);
        skp10_sk_rt_000026e8(0);
        cnt--;
        if (cnt != 0) {
            uint64_t e = p2 & 0xffffffffffffull;
            if ((p3 & 0x2000000000000000ull) != 0) e = p3 >> 0x38 & 0xf;
            list += 0x40;
            do {
                skp10_sk_rt_00319808((uint64_t *)list, (uint64_t *)0);
                if (e != 0) {
                    skp10_sk_alloc_pages(p3, 0);
                    if ((p3 >> 0x3c & 1) == 0) {
                        if ((p3 >> 0x3d & 1) != 0) {
                            skp10_sk_rt_0001d4a0(p2, p3);
                            skp10_sk_msg_dispatch(p3);
                        } else {
                            skp10_sk_rt_002a9ba8(p2, p3);
                            if (0 == 0) {
                                skp10_sk_rt_001afe4c(skp10_s_Fatal_error_005accd0, 0xb, 2,
                                             skp10_s_Unexpectedly_found_nil_while_unw_005cd7d0, 0x39, 2,
                                             skp10_s_Swift_OutputStream_swift_005d3a20, 0x18, 2, 0x23f, 1);
                            }
                        }
                    } else {
                        skp10_sk_rt_0001d4a0(p2, p3);
                        skp10_sk_msg_dispatch(p3);
                    }
                    skp10_sk_runtime_install(0, 1, e);   /* FUN_003d30b0 */
                    skp10_sk_msg_dispatch(0);
                }
                skp10_sk_rt_002060d4(0, (void *)p6, 0x67b1e8, 0x678490, &skp10_DAT_004f1818);
                skp10_sk_rt_000026e8(0);
                list += 0x20;
                cnt--;
            } while (cnt != 0);
        }
    }
    sk_vspace_object_create(p4, p5);
    skp10_sk_vspace_lock_leave();
}

/*--------------------------------------------------------------------*/
/* FUN_0026bbd4 @ 0x0026bbd4   (est. skp10_sk_vspace_entry_drain)
 * Ghidra: void skp10_sk_rt_0026bbd4(undefined8, undefined8, undefined8, undefined8,
 *                            undefined8, undefined8, undefined8, undefined8)
 * Drains a list of entries: for each node dispatches through FUN_0031b900
 * and releases the accumulator; then dispatches the tail via FUN_0034310c.
 * Confidence: low.
 */
void skp10_sk_vspace_entry_drain(long p1, uint64_t p2, uint64_t p3, uint64_t p4,
                           uint64_t p5, uint64_t p6, uint64_t p7, uint64_t p8)
{
    long hdr = skp10_sk_rt_0035300c();
    skp10_sk_rt_0031b8d0(p8);
    skp10_sk_rt_0034bcf0();
    skp10_sk_rt_slot_0d();
    {
        long cnt = *(long *)(hdr + 0x10);
        if (cnt != 0) {
            void (*fn)(void) = (void (*)(void))skp10_sk_rt_0031b900(p8);
            uint64_t acc = 0xe000000000000000ull;
            while (true) {
                hdr += 0x20;
                cnt--;
                skp10_sk_rt_00319808((uint64_t *)hdr, (uint64_t *)0);
                skp10_sk_rt_003510dc();
                skp10_sk_rt_0035063c();
                (*fn)();
                skp10_sk_msg_dispatch(acc);
                acc = skp10_sk_rt_0034d274((uint64_t *)0);
                skp10_sk_rt_00352920(acc, p6);
                (*(void (**)(void))(p6))();
                skp10_sk_rt_000026e8((uint64_t *)0);
                if (cnt == 0) break;
                skp10_sk_alloc_pages(p3, 0);
                acc = p3;
            }
        }
    }
    skp10_sk_rt_00354da0(p8);
    skp10_sk_rt_0035063c(p4, p5);
    skp10_sk_rt_slot_0d();
    skp10_sk_rt_0034310c(p8);
    skp10_sk_rt_0034bcf0();
    skp10_sk_rt_slot_0d();
    skp10_sk_rt_00353238(0);
}

/*--------------------------------------------------------------------*/
/* FUN_0026bce8 @ 0x0026bce8   (est. sk_vspace_load_word)
 * Ghidra: undefined8 skp10_sk_rt_0026bce8(void)
 * Reads 8 bytes into a local via thunk_FUN_00054414 and returns the word.
 * Confidence: medium.
 */
uint64_t sk_vspace_load_word(void)
{
    uint64_t w = 0;
    skp10_sk_swift_read8(&w, 8);              /* thunk_FUN_00054414 */
    return w;
}

/*--------------------------------------------------------------------*/
/* FUN_0026bd18 @ 0x0026bd18   (est. sk_vspace_load_word_fwd)
 * Ghidra: void skp10_sk_rt_0026bd18(void)
 * Forwarder to FUN_0026bce8.
 * Confidence: medium.
 */
void sk_vspace_load_word_fwd(void) { sk_vspace_load_word(); }

/*--------------------------------------------------------------------*/
/* FUN_0026bd1c @ 0x0026bd1c   (est. sk_vspace_load_word_fwd2)
 * Ghidra: void skp10_sk_rt_0026bd1c(void)
 * Forwarder to FUN_0026bce8.
 * Confidence: medium.
 */
void sk_vspace_load_word_fwd2(void) { sk_vspace_load_word(); }

/*--------------------------------------------------------------------*/
/* FUN_0026bd30 @ 0x0026bd30   (est. sk_vspace_bounds_check)
 * Ghidra: void skp10_sk_rt_0026bd30(long param_1, long param_2)
 * Bounds check: if param_1 > param_2, panics via skp10_sk_rt_00347de8(1) +
 * FUN_001afe4c. Otherwise returns.
 * Confidence: medium (clear comparison + panic).
 */
void sk_vspace_bounds_check(long a, long b)
{
    if (a <= b) return;
    skp10_sk_rt_00347de8(1);
    skp10_sk_swift_fatal();
}

/*--------------------------------------------------------------------*/
/* FUN_0026bd5c @ 0x0026bd5c   (est. skp10_sk_vspace_bounds_check_pages)
 * Ghidra: void skp10_sk_rt_0026bd5c(ulong param_1, ulong param_2)
 * Page-granular bounds check: compares param_1>>0xe against param_2>>0xe;
 * if out of range panics with "Range requires lowerBound < upperBound"
 * (Swift.Range fatal error).
 * Confidence: medium (string-verified).
 */
void skp10_sk_vspace_bounds_check_pages(uint64_t a, uint64_t b)
{
    if (a >> 0xe <= b >> 0xe) return;
    skp10_sk_rt_001afe4c(skp10_s_Fatal_error_005accd0, 0xb, 2,
                 skp10_s_Range_requires_lowerBound_005cda00, 0x27, 2,
                 skp10_s_Swift_Range_swift_005cda30, 0x11, 2, 0xb5, 1);
}

/*--------------------------------------------------------------------*/
/* FUN_0026bdc4 @ 0x0026bdc4   (est. skp10_sk_vspace_invoke)
 * Ghidra: void skp10_sk_rt_0026bdc4(void)
 * Invocation dispatch: locks, resolves the method offset (+0x30), dispatches
 * the +0x20/+0x10/+8 methods across the vtable, and on success returns;
 * on failure panics (FUN_00350410 + FUN_00347de8 + fatal).
 * Confidence: low.
 */
void skp10_sk_vspace_invoke(void)
{
    int off;
    long hdr;
    skp10_sk_cpu();                           /* FUN_0008e518 */
    skp10_sk_rt_003531f0();
    skp10_sk_rt_0034b0b4();
    skp10_sk_rt_00359000();
    skp10_sk_rt_00348d64();
    skp10_sk_rt_00348a9c();
    skp10_sk_rt_00350434();
    skp10_sk_rt_003503f8();
    skp10_sk_rt_0034ea40();
    skp10_sk_rt_0034ac28();
    skp10_sk_rt_0034c074();
    hdr = *(long *)(0 + -8);
    (*(void (**)(void))(hdr + 0x20))();
    skp10_sk_rt_00351130();
    (*(void (**)(void))(hdr + 0x20))();
    off = *(int *)(0 + 0x30);
    skp10_sk_rt_00350968(0 + off);
    (*(void (**)(void))(hdr + 0x20))();
    skp10_sk_rt_0035166c(0);
    skp10_sk_rt_00353cd8(0, 0 + off);
    if ((0 & 1) != 0) {
        (*(void (**)(void))(0 + 0x10))();
        skp10_sk_rt_003507e0();
        skp10_sk_rt_slot_0d();
        (*(void (**)(void))(0 + 0x20))();
        skp10_sk_rt_003504f4();
        skp10_sk_rt_slot_0d();
        skp10_sk_rt_0034d180();
        (*(void (**)(void))(hdr + 0x20))();
        skp10_sk_rt_00359e14();
        (*(void (**)(void))(hdr + 0x20))();
        skp10_sk_rt_0034fd4c();
        (*(void (**)(void))(0 + 0x10))();
        off = *(int *)(0 + 0x30);
        skp10_sk_rt_00351744(0);
        (*(void (**)(void))(hdr + 0x20))();
        (*(void (**)(uint64_t))(hdr + 8))(0 + off);
        skp10_sk_rt_0034fd4c();
        (*(void (**)(void))(0 + 0x20))();
        skp10_sk_rt_00350798();
        skp10_sk_rt_00355d78(0, 0, 0);
        skp10_sk_rt_00359d9c();
        (*(void (**)(void))(hdr + 0x20))();
        skp10_sk_rt_00351714();
        (*(void (**)(void))(hdr + 8))();
        (*(void (**)(uint64_t))(hdr + 8))(0);
        skp10_sk_rt_0035a1c0();
        (*(void (**)(void))(hdr + 8))();
        skp10_sk_rt_0008e500(0);
        return;
    }
    skp10_sk_rt_00350410();
    skp10_sk_rt_00347de8();
    skp10_sk_swift_fatal();
}

/*--------------------------------------------------------------------*/
/* FUN_0026c064 @ 0x0026c064   (est. sk_vspace_log)
 * Ghidra: void skp10_sk_rt_0026c064(void)
 * Log/dispatch helper: builds a NEON-extracted key pair, dispatches via
 * FUN_000b4390 / FUN_00376820, and calls the +0x24 method.
 * Confidence: low.
 */
void sk_vspace_log(void)
{
    uint64_t k;
    skp10_sk_spin_irqsave(0);                 /* FUN_00357ca0 */
    skp10_sk_rt_00350a10();
    skp10_sk_rt_00351468();
    skp10_sk_rt_0034ada0();
    /* NEON_ext: rotate 16-byte key by 8 */
    skp10_sk_rt_000b4390(0, 0, (uint64_t*)sk_scratch);
    skp10_sk_rt_00376820();
    skp10_sk_rt_00350488(0, 0, 0);
    k = skp10_sk_rt_0031090c();
    (*(void (**)(uint64_t))skp10_sk_rt_slot_0d())(0 + *(int *)(k + 0x24));
    skp10_sk_rt_00350af4(*(uint64_t *)(0 + 8));
    skp10_sk_rt_slot_0d();
    skp10_sk_rt_00357c44(0);
}

/*--------------------------------------------------------------------*/
/* FUN_0026c160 @ 0x0026c160   (est. sk_vspace_check)
 * Ghidra: uint skp10_sk_rt_0026c160(undefined8, undefined8, undefined8)
 * Validation check: runs the runtime dispatch and returns (result & 1).
 * Confidence: low.
 */
uint32_t sk_vspace_check(uint64_t p1, uint64_t p2, uint64_t p3)
{
    uint64_t r;
    skp10_sk_rt_0035583c();
    skp10_sk_rt_0035125c(p3);
    skp10_sk_rt_0035166c();
    skp10_sk_rt_0034bf1c();
    r = (*(uint64_t (**)(void))skp10_sk_rt_slot_0d())();
    if ((r & 1) == 0) {
        return 0;
    }
    skp10_sk_rt_0035044c();
    skp10_sk_rt_00351100();
    r = (*(uint64_t (**)(void))skp10_sk_rt_slot_0d())();
    return (uint32_t)(r & 1);
}

/*--------------------------------------------------------------------*/
/* FUN_0026c210 @ 0x0026c210   (est. sk_vspace_callout)
 * Ghidra: void skp10_sk_rt_0026c210(undefined8, ulong, undefined8, code*)
 * Callout: builds a key via NEON_ext on the caller frame, dispatches
 * FUN_00376820, and calls the callback param_4.
 * Confidence: low.
 */
void sk_vspace_callout(uint64_t p1, uint64_t p2, uint64_t p3, void (*fn)(void))
{
    skp10_sk_rt_00376820(p3, p1, (uint64_t*)sk_scratch);           /* NEON_ext of the 16-byte frame value at p2-0x10 */
    skp10_sk_rt_00356b98();
    (*fn)();
}

/*--------------------------------------------------------------------*/
/* FUN_0026c274 @ 0x0026c274   (est. sk_vspace_indirect_a)
 * Ghidra: void skp10_sk_rt_0026c274(undefined8 param_1, long param_2)
 * Indirect dispatch through the object's +0x10 method (vtable at
 * *(param_2+0x10)-8).
 * Confidence: low.
 */
void sk_vspace_indirect_a(uint64_t p1, long p2)
{
    (*(void (**)(uint64_t))(*(long *)(*(long *)(p2 + 0x10) + -8) + 0x10))(p1);
}

/*--------------------------------------------------------------------*/
/* FUN_0026c2a0 @ 0x0026c2a0   (est. sk_vspace_indirect_b)
 * Ghidra: void skp10_sk_rt_0026c2a0(undefined8 param_1, long param_2)
 * Indirect dispatch through the +0x10 method with a computed offset.
 * Confidence: low.
 */
void sk_vspace_indirect_b(uint64_t p1, long p2)
{
    (*(void (**)(uint64_t, uint64_t))(*(long *)(*(long *)(p2 + 0x10) + -8) + 0x10))
        (p1, 0 + *(int *)(p2 + 0x24));
}

/*--------------------------------------------------------------------*/
/* FUN_0026c6c8 @ 0x0026c6c8   (est. sk_vspace_oob_panic)
 * Ghidra: void skp10_sk_rt_0026c6c8(void)
 * Out-of-bounds panic: FUN_00347d60 then fatal.
 * Confidence: medium.
 */
void sk_vspace_oob_panic(void)
{
    skp10_sk_rt_00347d60();
    skp10_sk_swift_fatal();
}

/*--------------------------------------------------------------------*/
/* FUN_0026c6d8 @ 0x0026c6d8   (est. skp10_sk_vspace_obj_check)
 * Ghidra: void skp10_sk_rt_0026c6d8(undefined8, undefined8, undefined8)
 * Object validation check: locks, dispatches two runtime checks; on the
 * success path re-locks and forwards (FUN_00357754, error 0x101); on
 * failure panics with error 0xf6/0xf7 (FUN_003486b8).
 * Confidence: low.
 */
void skp10_sk_vspace_obj_check(uint64_t p1, uint64_t p2, uint64_t p3)
{
    uint64_t r, u;
    skp10_sk_cpu();                           /* FUN_0008e518 */
    skp10_sk_rt_00350a64();
    skp10_sk_rt_00351b78();
    skp10_sk_object_lock(0, 0, 0, 0, 0);      /* FUN_00377824 */
    skp10_sk_rt_00348d4c();
    skp10_sk_rt_0007c1a4();
    skp10_sk_rt_0034aee4();
    skp10_sk_rt_003504ac();
    skp10_sk_rt_003528ac();
    skp10_sk_lock_ref(0);                     /* FUN_00377bec */
    skp10_sk_rt_00027754();
    skp10_sk_rt_0008f6f4();
    skp10_sk_rt_00349dfc();
    skp10_sk_rt_003516a8();
    u = skp10_sk_object_lock(0, 0, 0, 0, 0);  /* FUN_00377824 */
    skp10_sk_rt_0034ab20();
    skp10_sk_rt_0007c1a4();
    skp10_sk_rt_0034b05c();
    skp10_sk_rt_003514b8(p3);
    skp10_sk_rt_00351ee0();
    skp10_sk_rt_00351ec0();
    skp10_sk_rt_0034f2b4();
    r = (*(uint64_t (**)(void))skp10_sk_rt_slot_0d())();
    if ((r & 1) == 0) {
        skp10_sk_rt_0034b348();
        u = 0xf6;
    } else {
        skp10_sk_rt_0035166c();
        skp10_sk_rt_0034f2b4(0, 0 + *(int *)(skp10_sk_rt_slot_0d() + 0x24));
        r = (*(uint64_t (**)(void))skp10_sk_rt_slot_0d())();
        if ((r & 1) != 0) {
            skp10_sk_rt_0034ad00();
            skp10_sk_rt_00350c38();
            skp10_sk_lock_ref(0);             /* FUN_00377bec */
            skp10_sk_rt_0034d4b8();
            u = skp10_sk_rt_00357754();
            skp10_sk_rt_0035130c(u, 0x101);
            skp10_sk_rt_slot_0d();
            skp10_sk_rt_0034e74c();
            skp10_sk_rt_003531a8();
            skp10_sk_rt_00352314();
            skp10_sk_rt_slot_0d();
            skp10_sk_rt_00354f4c(p3);
            skp10_sk_rt_0035056c(0);
            skp10_sk_rt_slot_0d();
            skp10_sk_rt_00352420();
            skp10_sk_rt_00100c38();
            skp10_sk_rt_slot_0d();
            skp10_sk_rt_0008e500(0);
            return;
        }
        skp10_sk_rt_0034b348();
        u = 0xf7;
    }
    skp10_sk_rt_003486b8(u);
    skp10_sk_rt_00349410();
    skp10_sk_rt_003504b8();
    skp10_sk_swift_fatal();
}

/*--------------------------------------------------------------------*/
/* FUN_0026ca24 @ 0x0026ca24   (est. sk_vspace_scan_c)
 * Ghidra: void skp10_sk_rt_0026ca24(void)
 * Scan dispatch: locks, dispatches through runtime, builds a message.
 * Confidence: low.
 */
void sk_vspace_scan_c(void)
{
    uint64_t w;
    skp10_sk_rt_00084220();
    skp10_sk_rt_00352700();
    skp10_sk_rt_00351a80();
    skp10_sk_rt_0034d8b0();
    skp10_sk_rt_003513a8();
    skp10_sk_object_lock(0, 0, 0, 0, 0);      /* FUN_00377824 */
    skp10_sk_rt_00348d4c();
    skp10_sk_rt_0007c1a4();
    skp10_sk_rt_0034aee4();
    skp10_sk_rt_00319538();
    skp10_sk_rt_00350b24();
    skp10_sk_rt_003548c4();
    skp10_sk_rt_00350600();
    skp10_sk_rt_slot_0d();
    skp10_sk_rt_00350780();
    skp10_sk_rt_0001df60();
    skp10_sk_rt_003516fc();
    skp10_sk_rt_00100c38(&w);
    skp10_sk_rt_001e2460();
    skp10_sk_rt_0034c9f8();
    skp10_sk_rt_slot_0d();
    skp10_sk_rt_00084234(w, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_0026cb00 @ 0x0026cb00   (est. skp10_sk_vspace_mem_validate)
 * Ghidra: void skp10_sk_rt_0026cb00(undefined8, undefined8, undefined8)
 * Memory validation: runs two runtime checks; on both success dispatches the
 * +0x10 method. Returns cleanly.
 * Confidence: low.
 */
void skp10_sk_vspace_mem_validate(uint64_t p1, uint64_t p2, uint64_t p3)
{
    uint64_t r;
    skp10_sk_rt_00353b10();
    skp10_sk_rt_003514b8(p3);
    skp10_sk_rt_0035166c();
    skp10_sk_rt_0034b768();
    r = (*(uint64_t (**)(void))skp10_sk_rt_slot_0d())();
    if ((r & 1) != 0) {
        skp10_sk_rt_0035044c();
        skp10_sk_rt_00351378();
        r = (*(uint64_t (**)(void))skp10_sk_rt_slot_0d())();
        if ((r & 1) != 0) {
            skp10_sk_rt_0034b518();
            (*(void (**)(void))(0 + 0x10))();
        }
    }
    skp10_sk_rt_00351c7c();
    skp10_sk_rt_000839d8();
    skp10_sk_rt_00350798();
    skp10_sk_rt_00356e34();
    skp10_sk_rt_0034ba48();
    skp10_sk_rt_000839d8();
}

/*--------------------------------------------------------------------*/
/* FUN_0026cbd0 @ 0x0026cbd0   (est. skp10_sk_vspace_mem_validate_b)
 * Ghidra: void skp10_sk_rt_0026cbd0(undefined8, undefined8, undefined8)
 * Memory validation variant: on both checks passing dispatches the +0x10
 * method and returns; otherwise panics (FUN_00348034 + fatal).
 * Confidence: low.
 */
void skp10_sk_vspace_mem_validate_b(uint64_t p1, uint64_t p2, uint64_t p3)
{
    uint64_t r;
    skp10_sk_spin_irqsave(0);                 /* FUN_00357ca0 */
    skp10_sk_rt_00351cc4();
    skp10_sk_rt_003514b8(p3);
    skp10_sk_rt_0035166c();
    skp10_sk_rt_0034d180();
    r = (*(uint64_t (**)(void))skp10_sk_rt_slot_0d())();
    if ((r & 1) != 0) {
        skp10_sk_rt_0035044c();
        skp10_sk_rt_00351378();
        r = (*(uint64_t (**)(void))skp10_sk_rt_slot_0d())();
        if ((r & 1) != 0) {
            skp10_sk_rt_003511b4();
            (*(void (**)(void))(0 + 0x10))();
            return;
        }
    }
    skp10_sk_rt_00348034();
    skp10_sk_rt_003504b8();
    skp10_sk_swift_fatal();
}

/*--------------------------------------------------------------------*/
/* FUN_0026cc88 @ 0x0026cc88   (est. sk_vspace_alloc_cap)
 * Ghidra: undefined * skp10_sk_rt_0026cc88(long *param_1, undefined8, undefined8, ulong)
 * Allocates a 0x28-byte capability object (tag 0xccb6), builds it via
 * FUN_0026cd08, stores the result at +0x20, and returns a vtable pointer.
 * Confidence: medium (clear alloc pattern).
 */
void *sk_vspace_alloc_cap(long *slot, uint64_t p2, uint64_t p3, uint64_t p4)
{
    long blk = (long)skp10_sk_alloc(0x28, 0xccb6);   /* FUN_0036a908 */
    *slot = blk;
    *(uint64_t *)(blk + 0x20) =
        skp10_sk_vspace_alloc_cap_b(blk, p2, p3,
                              *(uint64_t *)((p4 & 0xfffffffffffffffeull) - 8),
                              *(uint64_t *)((p4 & 0xfffffffffffffffeull) - 0x10));
    return &skp10_DAT_003471a4;
}

/* (end of slice 10 — FUN_0026cd08 is out of slice and declared extern.) */
