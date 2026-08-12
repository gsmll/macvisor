/* Recreated from ringminus1/sk/cl4_kernel.raw (cL4 microkernel, arm64e, image base 0).
 * Ground truth: Ghidra FUN_ names + addresses. Names use cL4/seL4 vocabulary;
 * estimates unless matched.
 *
 * This is SLICE 2 of the vspace/MMU layer, addresses 0x0020e778..0x00214720.
 *
 * NOTES ON DECOMPILER QUALITY (arm64e PAC):
 *   The Apple arm64e binary signs return addresses, so Ghidra loses the true
 *   destination of every `bl` and models callee-saved/link registers as
 *   opaque `extraout_x16`/`extraout_x8`/`extraout_x9` values. Consequently:
 *     - Almost every shared-runtime callee in 0x0034xxxx/0x0035xxxx/0x0007xxxx
 *       decompiles to an empty `return;` (the "real" body is the signed-tail
 *       branch Ghidra cannot follow). We still keep the call: the call-sequence
 *       and its ordering ARE the observable behavior.
 *     - `(*DAT_00658c00)()` is an indirect call through the global hook slot
 *       at 0x00658c00 (a PAC-authenticated function pointer).
 *     - Object method-dispatch stubs lose their `this` (x20) register, so the
 *       vtable/self pointer appears as `extraout_x16` and the method slot as
 *       `(**(code **)(extraout_x16 + off))()`.
 *   Where the decompile was unrecoverable (jumptables, register-lost chains)
 *   we transcribe the observable call sequence faithfully and mark confidence
 *   low, documenting the artifact. Body order == decompile order.
 *
 * All shared-runtime helpers (0x0034xxxx/0x0035xxxx/0x0036xxxx/0x0037xxxx and
 * the 0x0008xxxx/0x0000xxxx/0x0002xxxx kernel boots) are OUT OF RANGE for this
 * slice; they are declared extern (generated at the top of this file) with the
 * FUN_ address in a comment. Reconstructed by sibling SK workers. */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "sk_internal.h"

/*--------------------------------------------------------------------*/
/* Named shared-runtime externs (hand-declared; rt_* are generated).   */
/*--------------------------------------------------------------------*/
extern void *sk_cpu(void);                    /* FUN_0008e518 */
extern void *sk_tcb_get(void);                /* FUN_0007c0c4 */
extern void sk_cpu_current(void);             /* FUN_0008e500 */
extern void *sk_lock_acquire(unsigned long a, unsigned long b, unsigned long c,
                             void *dbg1, void *dbg2);   /* FUN_00377824 */
extern unsigned long sk_lock_ref(unsigned long a);      /* FUN_00377bec */
extern void *sk_alloc(unsigned long size, unsigned long tag);       /* FUN_0036a908 */
extern void *sk_alloc_small(unsigned long size, unsigned long tag); /* FUN_0036a940 */
extern void *sk_alloc_pages(unsigned long size, unsigned long tag); /* FUN_0036b270 */
extern void sk_free(void *ptr);               /* FUN_0036b118 */
extern void sk_frame_enter(void);             /* FUN_00084220 */
extern void sk_frame_leave(void);             /* FUN_00084234 */
extern void sk_trap_init(void);               /* FUN_0008409c */
extern void sk_nop_01(void);                  /* FUN_0007c198 */
extern void sk_nop_02(void);                  /* FUN_0007c1a4 */
extern void sk_nop_03(void);                  /* FUN_0007c1c4 */
extern void sk_nop_04(void);                  /* FUN_0007c0b8 */
extern void sk_nop_05(void);                  /* FUN_0007c178 */
extern void sk_panic_no_return(void);         /* FUN_001afa84 (noreturn) */
extern void sk_panic_no_return2(void);        /* FUN_001afe4c (noreturn) */

/* Out-of-range in-slice dispatchers (in 0x0020xxxx but outside this slice). */
extern void sk_vspace_dispatch_e5c0(void *a);             /* FUN_0020e5c0 */
extern void sk_vspace_dispatch_c7fc(void *a);             /* FUN_0020c7fc */
extern void sk_vspace_resume(void *a);                    /* FUN_0020a084 */
extern void sk_vspace_resume2(void *a);                   /* FUN_0020a3b0 */
extern void sk_vspace_resume3(void *a);                   /* FUN_0020a918 */
extern void sk_vspace_resume4(void *a);                   /* FUN_0020c1bc */
extern void sk_vspace_resume5(void *a);                   /* FUN_002060a0 */
extern void sk_vspace_resume6(void *a);                   /* FUN_002085fc */
extern void sk_vspace_resume7(void *a, void *b);          /* FUN_002086d4 */

/* Global PAC-authenticated indirect-call hook slot (Ghia raw: DAT_00658c00). */
extern void *sk_global_hook;                /* DAT_00658c00 (fn ptr) */

/* rt_* shared-runtime externs are GENERATED below by the build script from the
 * set of rt_* identifiers actually referenced in the bodies. */


/* Generated shared-runtime externs */
/* Generated shared-runtime externs (FUN_ address per name; reconstructed
 * by the sibling SK range workers that own 0x0034xxxx/0x0035xxxx/0x0036xxxx).
 * Declared with unspecified params (historical C) so the PAC-collapsed
 * no-op helpers can be invoked with the decompiler's arbitrary args. */
extern void rt_310d68();                    /* FUN_00310d68 */
extern void rt_310da8();                    /* FUN_00310da8 */
extern void rt_310e08();                    /* FUN_00310e08 */
extern void rt_310e20();                    /* FUN_00310e20 */
extern void rt_310ea4();                    /* FUN_00310ea4 */
extern void rt_3191e8();                    /* FUN_003191e8 */
extern void rt_3193f4();                    /* FUN_003193f4 */
extern void rt_3195f8();                    /* FUN_003195f8 */
extern void rt_3196e8();                    /* FUN_003196e8 */
extern void rt_31b1c4();                    /* FUN_0031b1c4 */
extern void rt_31b28c();                    /* FUN_0031b28c */
extern void rt_31b62c();                    /* FUN_0031b62c */
extern void rt_31b978();                    /* FUN_0031b978 */
extern void rt_31b9c0();                    /* FUN_0031b9c0 */
extern void rt_31b9d8();                    /* FUN_0031b9d8 */
extern void rt_31ba3c();                    /* FUN_0031ba3c */
extern void rt_31ba70();                    /* FUN_0031ba70 */
extern void rt_31baa0();                    /* FUN_0031baa0 */
extern void rt_31bab8();                    /* FUN_0031bab8 */
extern void rt_31bb04();                    /* FUN_0031bb04 */
extern void rt_31bb1c();                    /* FUN_0031bb1c */
extern void rt_31bb80();                    /* FUN_0031bb80 */
extern void rt_31e104();                    /* FUN_0031e104 */
extern void rt_347ef4();                    /* FUN_00347ef4 */
extern void rt_34865c();                    /* FUN_0034865c */
extern void rt_348a18();                    /* FUN_00348a18 */
extern void rt_348a34();                    /* FUN_00348a34 */
extern void rt_348a80();                    /* FUN_00348a80 */
extern void rt_348b1c();                    /* FUN_00348b1c */
extern void rt_348bbc();                    /* FUN_00348bbc */
extern void rt_348cd0();                    /* FUN_00348cd0 */
extern void rt_348ce8();                    /* FUN_00348ce8 */
extern void rt_348d4c();                    /* FUN_00348d4c */
extern void rt_348d64();                    /* FUN_00348d64 */
extern void rt_348d7c();                    /* FUN_00348d7c */
extern void rt_348e00();                    /* FUN_00348e00 */
extern void rt_348e60();                    /* FUN_00348e60 */
extern void rt_3490d0();                    /* FUN_003490d0 */
extern void rt_34911c();                    /* FUN_0034911c */
extern void rt_349190();                    /* FUN_00349190 */
extern void rt_3494e8();                    /* FUN_003494e8 */
extern void rt_349518();                    /* FUN_00349518 */
extern void rt_34961c();                    /* FUN_0034961c */
extern void rt_349734();                    /* FUN_00349734 */
extern void rt_349748();                    /* FUN_00349748 */
extern void rt_349844();                    /* FUN_00349844 */
extern void rt_3498c4();                    /* FUN_003498c4 */
extern void rt_3498f4();                    /* FUN_003498f4 */
extern void rt_3499b4();                    /* FUN_003499b4 */
extern void rt_349c14();                    /* FUN_00349c14 */
extern void rt_349c58();                    /* FUN_00349c58 */
extern void rt_349c70();                    /* FUN_00349c70 */
extern void rt_349e10();                    /* FUN_00349e10 */
extern void rt_34a1e0();                    /* FUN_0034a1e0 */
extern void rt_34a210();                    /* FUN_0034a210 */
extern void rt_34a450();                    /* FUN_0034a450 */
extern void rt_34a654();                    /* FUN_0034a654 */
extern void rt_34a674();                    /* FUN_0034a674 */
extern void rt_34a868();                    /* FUN_0034a868 */
extern void rt_34aab0();                    /* FUN_0034aab0 */
extern void rt_34ab20();                    /* FUN_0034ab20 */
extern void rt_34ab9c();                    /* FUN_0034ab9c */
extern void rt_34abc4();                    /* FUN_0034abc4 */
extern void rt_34ac64();                    /* FUN_0034ac64 */
extern void rt_34ac78();                    /* FUN_0034ac78 */
extern void rt_34ad8c();                    /* FUN_0034ad8c */
extern void rt_34aee4();                    /* FUN_0034aee4 */
extern void rt_34af20();                    /* FUN_0034af20 */
extern void rt_34b014();                    /* FUN_0034b014 */
extern void rt_34b07c();                    /* FUN_0034b07c */
extern void rt_34b0c4();                    /* FUN_0034b0c4 */
extern void rt_34b0d4();                    /* FUN_0034b0d4 */
extern void rt_34b164();                    /* FUN_0034b164 */
extern void rt_34b2f8();                    /* FUN_0034b2f8 */
extern void rt_34b348();                    /* FUN_0034b348 */
extern void rt_34b3d8();                    /* FUN_0034b3d8 */
extern void rt_34b460();                    /* FUN_0034b460 */
extern void rt_34b4c0();                    /* FUN_0034b4c0 */
extern void rt_34b568();                    /* FUN_0034b568 */
extern void rt_34b758();                    /* FUN_0034b758 */
extern void rt_34b798();                    /* FUN_0034b798 */
extern void rt_34b7e4();                    /* FUN_0034b7e4 */
extern void rt_34b7f4();                    /* FUN_0034b7f4 */
extern void rt_34b8bc();                    /* FUN_0034b8bc */
extern void rt_34ba38();                    /* FUN_0034ba38 */
extern void rt_34bcf0();                    /* FUN_0034bcf0 */
extern void rt_34bddc();                    /* FUN_0034bddc */
extern void rt_34bdfc();                    /* FUN_0034bdfc */
extern void rt_34c1bc();                    /* FUN_0034c1bc */
extern void rt_34c20c();                    /* FUN_0034c20c */
extern void rt_34c2c8();                    /* FUN_0034c2c8 */
extern void rt_34c2d8();                    /* FUN_0034c2d8 */
extern void rt_34c354();                    /* FUN_0034c354 */
extern void rt_34c444();                    /* FUN_0034c444 */
extern void rt_34c454();                    /* FUN_0034c454 */
extern void rt_34c55c();                    /* FUN_0034c55c */
extern void rt_34c58c();                    /* FUN_0034c58c */
extern void rt_34c704();                    /* FUN_0034c704 */
extern void rt_34c8f8();                    /* FUN_0034c8f8 */
extern void rt_34c930();                    /* FUN_0034c930 */
extern void rt_34c998();                    /* FUN_0034c998 */
extern void rt_34cca8();                    /* FUN_0034cca8 */
extern void rt_34cd2c();                    /* FUN_0034cd2c */
extern void rt_34cd7c();                    /* FUN_0034cd7c */
extern void rt_34cff4();                    /* FUN_0034cff4 */
extern void rt_34d014();                    /* FUN_0034d014 */
extern void rt_34d070();                    /* FUN_0034d070 */
extern void rt_34d080();                    /* FUN_0034d080 */
extern void rt_34d130();                    /* FUN_0034d130 */
extern void rt_34d284();                    /* FUN_0034d284 */
extern void rt_34d3f4();                    /* FUN_0034d3f4 */
extern void rt_34d434();                    /* FUN_0034d434 */
extern void rt_34d598();                    /* FUN_0034d598 */
extern void rt_34d634();                    /* FUN_0034d634 */
extern void rt_34d758();                    /* FUN_0034d758 */
extern void rt_34d7a8();                    /* FUN_0034d7a8 */
extern void rt_34da48();                    /* FUN_0034da48 */
extern void rt_34de64();                    /* FUN_0034de64 */
extern void rt_34dee4();                    /* FUN_0034dee4 */
extern void rt_34df34();                    /* FUN_0034df34 */
extern void rt_34e3cc();                    /* FUN_0034e3cc */
extern void rt_34e3e4();                    /* FUN_0034e3e4 */
extern void rt_34e414();                    /* FUN_0034e414 */
extern void rt_34e67c();                    /* FUN_0034e67c */
extern void rt_34e69c();                    /* FUN_0034e69c */
extern void rt_34e924();                    /* FUN_0034e924 */
extern void rt_34e9b8();                    /* FUN_0034e9b8 */
extern void rt_34eb84();                    /* FUN_0034eb84 */
extern void rt_34eb94();                    /* FUN_0034eb94 */
extern void rt_34ecb8();                    /* FUN_0034ecb8 */
extern void rt_34ece8();                    /* FUN_0034ece8 */
extern void rt_34ed08();                    /* FUN_0034ed08 */
extern void rt_34ed78();                    /* FUN_0034ed78 */
extern void rt_34ee18();                    /* FUN_0034ee18 */
extern void rt_34f324();                    /* FUN_0034f324 */
extern void rt_34f344();                    /* FUN_0034f344 */
extern void rt_34f384();                    /* FUN_0034f384 */
extern void rt_34f464();                    /* FUN_0034f464 */
extern void rt_34f564();                    /* FUN_0034f564 */
extern void rt_34f584();                    /* FUN_0034f584 */
extern void rt_34f5a4();                    /* FUN_0034f5a4 */
extern void rt_34f9c8();                    /* FUN_0034f9c8 */
extern void rt_34fc34();                    /* FUN_0034fc34 */
extern void rt_3500c0();                    /* FUN_003500c0 */
extern void rt_350104();                    /* FUN_00350104 */
extern void rt_350114();                    /* FUN_00350114 */
extern void rt_350164();                    /* FUN_00350164 */
extern void rt_350210();                    /* FUN_00350210 */
extern void rt_350268();                    /* FUN_00350268 */
extern void rt_350428();                    /* FUN_00350428 */
extern void rt_350464();                    /* FUN_00350464 */
extern void rt_350470();                    /* FUN_00350470 */
extern void rt_35047c();                    /* FUN_0035047c */
extern void rt_3504c4();                    /* FUN_003504c4 */
extern void rt_3504d0();                    /* FUN_003504d0 */
extern void rt_3504e8();                    /* FUN_003504e8 */
extern void rt_3504f4();                    /* FUN_003504f4 */
extern void rt_350500();                    /* FUN_00350500 */
extern void rt_350524();                    /* FUN_00350524 */
extern void rt_3505d0();                    /* FUN_003505d0 */
extern void rt_3505e8();                    /* FUN_003505e8 */
extern void rt_35060c();                    /* FUN_0035060c */
extern void rt_350720();                    /* FUN_00350720 */
extern void rt_35072c();                    /* FUN_0035072c */
extern void rt_35075c();                    /* FUN_0035075c */
extern void rt_350768();                    /* FUN_00350768 */
extern void rt_350798();                    /* FUN_00350798 */
extern void rt_3507bc();                    /* FUN_003507bc */
extern void rt_3507d4();                    /* FUN_003507d4 */
extern void rt_3507e0();                    /* FUN_003507e0 */
extern void rt_350810();                    /* FUN_00350810 */
extern void rt_3508a8();                    /* FUN_003508a8 */
extern void rt_3508c0();                    /* FUN_003508c0 */
extern void rt_3508cc();                    /* FUN_003508cc */
extern void rt_3508d8();                    /* FUN_003508d8 */
extern void rt_350950();                    /* FUN_00350950 */
extern void rt_350974();                    /* FUN_00350974 */
extern void rt_350998();                    /* FUN_00350998 */
extern void rt_3509e0();                    /* FUN_003509e0 */
extern void rt_350a94();                    /* FUN_00350a94 */
extern void rt_350b00();                    /* FUN_00350b00 */
extern void rt_350b0c();                    /* FUN_00350b0c */
extern void rt_350b24();                    /* FUN_00350b24 */
extern void rt_350b48();                    /* FUN_00350b48 */
extern void rt_350b60();                    /* FUN_00350b60 */
extern void rt_350b90();                    /* FUN_00350b90 */
extern void rt_350b9c();                    /* FUN_00350b9c */
extern void rt_350bd8();                    /* FUN_00350bd8 */
extern void rt_350c38();                    /* FUN_00350c38 */
extern void rt_350c50();                    /* FUN_00350c50 */
extern void rt_350c5c();                    /* FUN_00350c5c */
extern void rt_350c68();                    /* FUN_00350c68 */
extern void rt_350c8c();                    /* FUN_00350c8c */
extern void rt_350ca4();                    /* FUN_00350ca4 */
extern void rt_351058();                    /* FUN_00351058 */
extern void rt_351094();                    /* FUN_00351094 */
extern void rt_351190();                    /* FUN_00351190 */
extern void rt_3511a8();                    /* FUN_003511a8 */
extern void rt_3511d8();                    /* FUN_003511d8 */
extern void rt_35125c();                    /* FUN_0035125c */
extern void rt_351274();                    /* FUN_00351274 */
extern void rt_351280();                    /* FUN_00351280 */
extern void rt_351354();                    /* FUN_00351354 */
extern void rt_351360();                    /* FUN_00351360 */
extern void rt_351384();                    /* FUN_00351384 */
extern void rt_3513c0();                    /* FUN_003513c0 */
extern void rt_351408();                    /* FUN_00351408 */
extern void rt_351444();                    /* FUN_00351444 */
extern void rt_35147c();                    /* FUN_0035147c */
extern void rt_3514ac();                    /* FUN_003514ac */
extern void rt_3514b8();                    /* FUN_003514b8 */
extern void rt_3514e8();                    /* FUN_003514e8 */
extern void rt_351560();                    /* FUN_00351560 */
extern void rt_3516b4();                    /* FUN_003516b4 */
extern void rt_3516cc();                    /* FUN_003516cc */
extern void rt_3516d8();                    /* FUN_003516d8 */
extern void rt_3516f0();                    /* FUN_003516f0 */
extern void rt_351894();                    /* FUN_00351894 */
extern void rt_3519a8();                    /* FUN_003519a8 */
extern void rt_351a68();                    /* FUN_00351a68 */
extern void rt_351a8c();                    /* FUN_00351a8c */
extern void rt_351ad4();                    /* FUN_00351ad4 */
extern void rt_351aec();                    /* FUN_00351aec */
extern void rt_351bb8();                    /* FUN_00351bb8 */
extern void rt_351bec();                    /* FUN_00351bec */
extern void rt_351c1c();                    /* FUN_00351c1c */
extern void rt_351d0c();                    /* FUN_00351d0c */
extern void rt_351d18();                    /* FUN_00351d18 */
extern void rt_351d30();                    /* FUN_00351d30 */
extern void rt_351d9c();                    /* FUN_00351d9c */
extern void rt_351de4();                    /* FUN_00351de4 */
extern void rt_351e20();                    /* FUN_00351e20 */
extern void rt_351f28();                    /* FUN_00351f28 */
extern void rt_352068();                    /* FUN_00352068 */
extern void rt_352188();                    /* FUN_00352188 */
extern void rt_3521d4();                    /* FUN_003521d4 */
extern void rt_3522b8();                    /* FUN_003522b8 */
extern void rt_35238c();                    /* FUN_0035238c */
extern void rt_35242c();                    /* FUN_0035242c */
extern void rt_3525cc();                    /* FUN_003525cc */
extern void rt_3527cc();                    /* FUN_003527cc */
extern void rt_352894();                    /* FUN_00352894 */
extern void rt_352914();                    /* FUN_00352914 */
extern void rt_352988();                    /* FUN_00352988 */
extern void rt_352b20();                    /* FUN_00352b20 */
extern void rt_352b2c();                    /* FUN_00352b2c */
extern void rt_352ba4();                    /* FUN_00352ba4 */
extern void rt_352dd0();                    /* FUN_00352dd0 */
extern void rt_352df4();                    /* FUN_00352df4 */
extern void rt_352e18();                    /* FUN_00352e18 */
extern void rt_352e84();                    /* FUN_00352e84 */
extern void rt_352ea8();                    /* FUN_00352ea8 */
extern void rt_352f54();                    /* FUN_00352f54 */
extern void rt_352ff4();                    /* FUN_00352ff4 */
extern void rt_353100();                    /* FUN_00353100 */
extern void rt_35310c();                    /* FUN_0035310c */
extern void rt_35316c();                    /* FUN_0035316c */
extern void rt_353528();                    /* FUN_00353528 */
extern void rt_3536ac();                    /* FUN_003536ac */
extern void rt_3536d0();                    /* FUN_003536d0 */
extern void rt_3537c4();                    /* FUN_003537c4 */
extern void rt_353860();                    /* FUN_00353860 */
extern void rt_353984();                    /* FUN_00353984 */
extern void rt_353a30();                    /* FUN_00353a30 */
extern void rt_353bdc();                    /* FUN_00353bdc */
extern void rt_353be8();                    /* FUN_00353be8 */
extern void rt_353c3c();                    /* FUN_00353c3c */
extern void rt_353c6c();                    /* FUN_00353c6c */
extern void rt_353cfc();                    /* FUN_00353cfc */
extern void rt_353d14();                    /* FUN_00353d14 */
extern void rt_353ea0();                    /* FUN_00353ea0 */
extern void rt_353fa0();                    /* FUN_00353fa0 */
extern void rt_35407c();                    /* FUN_0035407c */
extern void rt_354330();                    /* FUN_00354330 */
extern void rt_3543a0();                    /* FUN_003543a0 */
extern void rt_354594();                    /* FUN_00354594 */
extern void rt_354804();                    /* FUN_00354804 */
extern void rt_3548b8();                    /* FUN_003548b8 */
extern void rt_3549d8();                    /* FUN_003549d8 */
extern void rt_354b5c();                    /* FUN_00354b5c */
extern void rt_354d38();                    /* FUN_00354d38 */
extern void rt_354d74();                    /* FUN_00354d74 */
extern void rt_354dd0();                    /* FUN_00354dd0 */
extern void rt_35583c();                    /* FUN_0035583c */
extern void rt_355848();                    /* FUN_00355848 */
extern void rt_3558d8();                    /* FUN_003558d8 */
extern void rt_355b04();                    /* FUN_00355b04 */
extern void rt_355c84();                    /* FUN_00355c84 */
extern void rt_356048();                    /* FUN_00356048 */
extern void rt_356090();                    /* FUN_00356090 */
extern void rt_356140();                    /* FUN_00356140 */
extern void rt_356188();                    /* FUN_00356188 */
extern void rt_356194();                    /* FUN_00356194 */
extern void rt_356218();                    /* FUN_00356218 */
extern void rt_356310();                    /* FUN_00356310 */
extern void rt_356328();                    /* FUN_00356328 */
extern void rt_356670();                    /* FUN_00356670 */
extern void rt_35687c();                    /* FUN_0035687c */
extern void rt_356ab8();                    /* FUN_00356ab8 */
extern void rt_356b8c();                    /* FUN_00356b8c */
extern void rt_356b98();                    /* FUN_00356b98 */
extern void rt_356bc8();                    /* FUN_00356bc8 */
extern void rt_356c18();                    /* FUN_00356c18 */
extern void rt_356c24();                    /* FUN_00356c24 */
extern void rt_356c48();                    /* FUN_00356c48 */
extern void rt_356ce0();                    /* FUN_00356ce0 */
extern void rt_356f6c();                    /* FUN_00356f6c */
extern void rt_357418();                    /* FUN_00357418 */
extern void rt_357424();                    /* FUN_00357424 */
extern void rt_357508();                    /* FUN_00357508 */
extern void rt_35776c();                    /* FUN_0035776c */
extern void rt_357944();                    /* FUN_00357944 */
extern void rt_357ac0();                    /* FUN_00357ac0 */
extern void rt_357b48();                    /* FUN_00357b48 */
extern void rt_358114();                    /* FUN_00358114 */
extern void rt_3586cc();                    /* FUN_003586cc */
extern void rt_358cec();                    /* FUN_00358cec */
extern void rt_358cf8();                    /* FUN_00358cf8 */
extern void rt_358eb8();                    /* FUN_00358eb8 */
extern void rt_358fb4();                    /* FUN_00358fb4 */
extern void rt_358fc8();                    /* FUN_00358fc8 */
extern void rt_359290();                    /* FUN_00359290 */
extern void rt_359388();                    /* FUN_00359388 */
extern void rt_3593c0();                    /* FUN_003593c0 */
extern void rt_3595c0();                    /* FUN_003595c0 */
extern void rt_359f3c();                    /* FUN_00359f3c */
extern void rt_35a058();                    /* FUN_0035a058 */
extern void rt_35a128();                    /* FUN_0035a128 */
extern void rt_35a140();                    /* FUN_0035a140 */
extern void rt_35a1f4();                    /* FUN_0035a1f4 */
extern void rt_35a298();                    /* FUN_0035a298 */
extern void rt_35a328();                    /* FUN_0035a328 */
extern void rt_35a3c4();                    /* FUN_0035a3c4 */
extern void rt_35a420();                    /* FUN_0035a420 */
extern void rt_35a42c();                    /* FUN_0035a42c */
extern void rt_35a4d4();                    /* FUN_0035a4d4 */
extern void rt_35a640();                    /* FUN_0035a640 */
extern void rt_35a7c0();                    /* FUN_0035a7c0 */
extern void rt_35a7d4();                    /* FUN_0035a7d4 */
extern long rt_362acc();                    /* FUN_00362acc */
extern void rt_365b6c();                    /* FUN_00365b6c */
extern void rt_3698b0();                    /* FUN_003698b0 */
extern void rt_36993c();                    /* FUN_0036993c */
extern int  rt_3a261c();                    /* FUN_003a261c */


/*--------------------------------------------------------------------*/
/* Forward declarations (functions defined in this file).             */
/*--------------------------------------------------------------------*/
void sk_vspace_trap_restore(void);          /* FUN_0020e778 */
void sk_vspace_trap_restore2(void);         /* FUN_0020e8b8 */
void sk_vspace_dispatch_tail(void);         /* FUN_0020e9e0 */
void sk_vspace_dispatch_eabc(void *a);      /* FUN_0020eabc */
void sk_vspace_dispatch_ebf0(void);         /* FUN_0020ebf0 */
void sk_vspace_dispatch_eefc(void);         /* FUN_0020eefc */
void sk_vspace_trap_f430(void *a, void *b, void *c);   /* FUN_0020f430 */
void sk_vspace_trap_f6fc(void);             /* FUN_0020f6fc */
void sk_vspace_obj_alloc_f970(void **out, void *b, void *c, void *d); /* FUN_0020f970 */
void sk_vspace_trap_fab4(void);             /* FUN_0020fab4 */
void sk_vspace_trap_ff38(void);             /* FUN_0020ff38 */
void sk_vspace_trap_10010(void);            /* FUN_00210010 */
void sk_vspace_trap_1019c(void);            /* FUN_0021019c */
void sk_vspace_trap_103ac(void);            /* FUN_002103ac */
void sk_vspace_trap_104d8(void);            /* FUN_002104d8 */
void sk_vspace_trap_105b8(void);            /* FUN_002105b8 */
void sk_vspace_trap_106f4(void);            /* FUN_002106f4 */
void sk_vspace_trap_107bc(void);            /* FUN_002107bc */
unsigned long sk_vspace_trap_108a8(void);   /* FUN_002108a8 */
void sk_vspace_trap_109a0(void);            /* FUN_002109a0 */
void sk_vspace_trap_10a68(void);            /* FUN_00210a68 */
void sk_vspace_obj_destroy_10ba0(void);     /* FUN_00210ba0 */
void sk_vspace_obj_destroy_10ba4(void);     /* FUN_00210ba4 */
void sk_vspace_obj_destroy_10bbc(void *a);  /* FUN_00210bbc */
void sk_vspace_obj_destroy_10bd4(void *a, void *handler); /* FUN_00210bd4 */
void sk_vspace_obj_destroy_10c40(void);     /* FUN_00210c40 */
void sk_vspace_obj_destroy_10c44(void);     /* FUN_00210c44 */
void sk_vspace_obj_destroy_10c5c(void *a, void *b, void *c); /* FUN_00210c5c */
void sk_vspace_trap_10dac(void);            /* FUN_00210dac */
void sk_vspace_trap_10ef0(void);            /* FUN_00210ef0 */
void sk_vspace_dispatch_tail2(void);        /* FUN_0021101c */
void sk_vspace_obj_alloc_110f8(void *a, void *b, void *c); /* FUN_002110f8 */
void sk_vspace_obj_alloc_11188(void *a, void *b, void *c, void *d); /* FUN_00211188 */
void sk_vspace_handler_11220(void *a);      /* FUN_00211220 */
void sk_vspace_dispatch_11358(void);        /* FUN_00211358 */
void sk_vspace_trap_1166c(void);            /* FUN_0021166c */
void sk_vspace_trap_11ba8(void *a, void *b, void *c); /* FUN_00211ba8 */
void sk_vspace_trap_11e7c(void);            /* FUN_00211e7c */
void sk_vspace_obj_alloc_120e4(void **out, void *b, void *c, void *d); /* FUN_002120e4 */
void sk_vspace_trap_12230(void);            /* FUN_00212230 */
void sk_vspace_trap_126c8(void);            /* FUN_002126c8 */
void sk_vspace_trap_127a4(void);            /* FUN_002127a4 */
void sk_vspace_trap_1293c(void);            /* FUN_0021293c */
void sk_vspace_obj_free_12b4c(void);        /* FUN_00212b4c */
void sk_vspace_obj_free_12b80(void);        /* FUN_00212b80 */
void sk_vspace_obj_set_12bb0(void *a, void *b, void *c, void *d, void *e); /* FUN_00212bb0 */
void sk_vspace_obj_set_12bfc(void);         /* FUN_00212bfc */
void *sk_vspace_obj_get_12c54(void);        /* FUN_00212c54 */
void sk_vspace_obj_dtor_12c80(void);        /* FUN_00212c80 (thunk to 133ac) */
void sk_vspace_obj_dtor_12c84(void);        /* FUN_00212c84 */
void sk_vspace_obj_dtor_12cc4(void);        /* FUN_00212cc4 */
void sk_vspace_obj_dtor_12d10(void);        /* FUN_00212d10 */
void sk_vspace_obj_dtor_12d50(void);        /* FUN_00212d50 */
void sk_vspace_obj_dtor_12e34(void);        /* FUN_00212e34 */
void sk_vspace_obj_dtor_12e38(void);        /* FUN_00212e38 */
void sk_vspace_obj_dtor_12e74(void);        /* FUN_00212e74 */
void sk_vspace_obj_dtor_12e8c(void);        /* FUN_00212e8c */
void sk_vspace_obj_dtor_12ea4(void);        /* FUN_00212ea4 */
void sk_vspace_obj_dtor_12ec8(void);        /* FUN_00212ec8 */
void sk_vspace_obj_dtor_12ee4(void);        /* FUN_00212ee4 */
void sk_vspace_obj_dtor_12ee8(void);        /* FUN_00212ee8 */
void sk_vspace_obj_dtor_12f24(void);        /* FUN_00212f24 */
void sk_vspace_obj_dtor_12fa4(void);        /* FUN_00212fa4 */
void sk_vspace_obj_dtor_12fe8(void);        /* FUN_00212fe8 */
void sk_vspace_obj_dtor_13028(void);        /* FUN_00213028 */
void sk_vspace_obj_dtor_13074(void);        /* FUN_00213074 */
void sk_vspace_obj_dtor_130b4(void);        /* FUN_002130b4 */
void sk_vspace_obj_dtor_130ec(void *a, void *b, void *c, void *d, void *e,
                              void *f, void *g, void *h, void *i); /* FUN_002130ec */
void sk_vspace_obj_dtor_13190(void);        /* FUN_00213190 */
void sk_vspace_obj_dtor_13194(void);        /* FUN_00213194 */
void sk_vspace_obj_dtor_131d0(void);        /* FUN_002131d0 */
void sk_vspace_obj_dtor_1321c(void);        /* FUN_0021321c */
void sk_vspace_obj_dtor_13260(void);        /* FUN_00213260 */
void sk_vspace_obj_dtor_132ac(void);        /* FUN_002132ac */
void sk_vspace_obj_dtor_132ec(void);        /* FUN_002132ec */
void sk_vspace_obj_dtor_1332c(void *a, void *b); /* FUN_0021332c */
void sk_vspace_obj_dtor_13368(void);        /* FUN_00213368 */
void sk_vspace_obj_dtor_133ac(void);        /* FUN_002133ac */
void sk_vspace_obj_dtor_13460(void *a);     /* FUN_00213460 */
void sk_vspace_obj_dtor_13464(void *a);     /* FUN_00213464 */
void sk_vspace_obj_dtor_134bc(void *a, void *b); /* FUN_002134bc */
void sk_vspace_obj_dtor_13580(void *a, void *b); /* FUN_00213580 */
void sk_vspace_obj_dtor_1360c(void);        /* FUN_0021360c */
void sk_vspace_obj_dtor_13720(void);        /* FUN_00213720 */
void sk_vspace_obj_dtor_13834(void);        /* FUN_00213834 */
void sk_vspace_obj_alloc_138b4(void);       /* FUN_002138b4 */
void sk_vspace_obj_free_138dc(void);        /* FUN_002138dc */
void sk_vspace_obj_dtor_13910(void);        /* FUN_00213910 */
void sk_vspace_obj_dtor_13940(void);        /* FUN_00213940 */
void sk_vspace_obj_dtor_1398c(void);        /* FUN_0021398c */
void sk_vspace_obj_dtor_13b28(void);        /* FUN_00213b28 */
void sk_vspace_obj_dtor_13b54(void);        /* FUN_00213b54 */
void sk_vspace_obj_dtor_13b80(void);        /* FUN_00213b80 */
void sk_vspace_obj_alloc_13bac(void *a);    /* FUN_00213bac */
void sk_vspace_obj_alloc_13c08(void);       /* FUN_00213c08 */
void sk_vspace_obj_alloc_13c30(void);       /* FUN_00213c30 */
void *sk_vspace_obj_alloc_13c58(void *a, void *b, void *c); /* FUN_00213c58 */
void sk_vspace_obj_alloc_13cd0(void *a, void *b, void *c, void *d, void *e); /* FUN_00213cd0 */
void *sk_vspace_obj_get_13e24(void);        /* FUN_00213e24 */
void sk_vspace_obj_alloc_13e58(void);       /* FUN_00213e58 */
void sk_vspace_obj_alloc_13f3c(void);       /* FUN_00213f3c */
void sk_vspace_obj_alloc_13f88(void *a, void *b, void *c, void *d, void *e); /* FUN_00213f88 */
void sk_vspace_obj_alloc_13fd8(void *a, void *b, void *c); /* FUN_00213fd8 */
void *sk_vspace_obj_alloc_1401c(void *a, void *b, void *c); /* FUN_0021401c */
void sk_vspace_obj_alloc_14094(void *a, void *b, void *c, void *d, void *e); /* FUN_00214094 */
void sk_vspace_obj_alloc_1416c(void);       /* FUN_0021416c */
long sk_vspace_obj_alloc_141d8(void *a, void *b, void *c); /* FUN_002141d8 */
void sk_vspace_obj_dtor_14218(void);        /* FUN_00214218 */
void sk_vspace_obj_dtor_14250(void);        /* FUN_00214250 */
void sk_vspace_obj_dtor_14294(void);        /* FUN_00214294 */
void sk_vspace_obj_dtor_142cc(void);        /* FUN_002142cc */
void sk_vspace_obj_dtor_14344(void);        /* FUN_00214344 */
void sk_vspace_obj_dtor_14388(void);        /* FUN_00214388 */
void sk_vspace_obj_dtor_143d4(void);        /* FUN_002143d4 */
void sk_vspace_obj_dtor_14474(void);        /* FUN_00214474 */
void sk_vspace_obj_dtor_144b8(void);        /* FUN_002144b8 */
void sk_vspace_obj_dtor_144fc(void);        /* FUN_002144fc */
void sk_vspace_obj_dtor_14540(void);        /* FUN_00214540 */
void *sk_vspace_obj_alloc_145e8(void *a, void *b, void *c); /* FUN_002145e8 */
void sk_vspace_obj_alloc_14660(void *a, void *b, void *c, void *d, void *e); /* FUN_00214660 */
void sk_vspace_obj_dtor_14720(void *a);     /* FUN_00214720 */

/*--------------------------------------------------------------------*/
/* Function bodies (address order).                                    */
/*--------------------------------------------------------------------*/

/* FUN_0020e778 @ 0x0020e778   (est. sk_vspace_trap_restore)
 * Ghidra: void FUN_0020e778(void)
 * Large trap/service handler in the vspace layer: grabs the per-CPU state,
 * runs a long sequence of shared-runtime bookkeeping calls, then tail-
 * dispatches to the restore routine (FUN_0020e5c0) and returns through
 * FUN_0008e500. The `extraout_x16` values are the PAC-clobbered register
 * carry; the exact field offsets (0x160/0x168) index the current TCB/state.
 * Confidence: low (PAC return-signing collapsed register flow).
 * Notes: Ghidra artifacts: extraout_x16/extraout_x9, (*DAT_00658c00)() hook,
 *   unaff_x19/unaff_x30. Falls into the common restore-tail pattern. */
void sk_vspace_trap_restore(void)
{
    sk_cpu();                    /* FUN_0008e518 */
    rt_352914();                 /* FUN_00352914 */
    sk_tcb_get();                /* FUN_0007c0c4 */
    rt_34b7e4();                 /* FUN_0034b7e4 */
    rt_351408();                 /* FUN_00351408 */
    (*(void (**)())sk_global_hook)();   /* (*DAT_00658c00)() */
    rt_34b014();                 /* FUN_0034b014 */
    rt_351bec((void *)0x160);    /* FUN_00351bec(*(extraout_x16 + 0x160)) */
    rt_34c20c();                 /* FUN_0034c20c */
    rt_350998();                 /* FUN_00350998 */
    sk_lock_acquire(0,0,0,0,0);  /* FUN_00377824 */
    rt_349e10();                 /* FUN_00349e10 */
    sk_nop_02();                 /* FUN_0007c1a4 */
    (*(void (**)())sk_global_hook)();   /* (*DAT_00658c00)() */
    rt_34af20();                 /* FUN_0034af20 */
    rt_35238c();                 /* FUN_0035238c */
    rt_3507d4();                 /* FUN_003507d4 */
    sk_lock_ref(0);              /* FUN_00377bec */
    rt_34c55c();                 /* FUN_0034c55c */
    rt_31ba3c();                 /* FUN_0031ba3c */
    /* FUN_000027e8 (boot helper) */
    rt_3527cc((void *)0x168);    /* FUN_003527cc(*(extraout_x16_00 + 0x168)) */
    ((void (*volatile)())0)();     /* (*extraout_x9)() */
    /* FUN_00100efc */
    rt_35a328();                 /* FUN_0035a328 */
    ((void (*volatile)())0)();     /* (*unaff_x19)() */
    sk_vspace_dispatch_e5c0(0);  /* FUN_0020e5c0 */
    sk_cpu_current();            /* FUN_0008e500 */
}

/* FUN_0020e8b8 @ 0x0020e8b8   (est. sk_vspace_trap_restore2)
 * Ghidra: void FUN_0020e8b8(void)
 * Sibling of FUN_0020e778; same restore-tail structure with a variant
 * bookkeeping sequence (0x158 field read, 0x160/0x168 offsets) before the
 * shared dispatch. Confidence: low (PAC).
 * Notes: Ghidra artifacts: extraout_x16_00/01, auVar2 from FUN_0034c20c. */
void sk_vspace_trap_restore2(void)
{
    sk_cpu();                    /* FUN_0008e518 */
    rt_352914();                 /* FUN_00352914 */
    sk_tcb_get();                /* FUN_0007c0c4 */
    /* uVar1 = *(extraout_x16 + 0x158) */
    rt_34b7e4();                 /* FUN_0034b7e4 */
    rt_351408();                 /* FUN_00351408 */
    (*(void (**)())sk_global_hook)();   /* (*DAT_00658c00)() */
    rt_34b014();                 /* FUN_0034b014 */
    rt_350bd8((void *)0x160);    /* FUN_00350bd8(*(extraout_x16_00 + 0x160)) */
    rt_34c20c();                 /* FUN_0034c20c */
    sk_lock_acquire(0,0,0,0,0);  /* FUN_00377824 */
    rt_34a450();                 /* FUN_0034a450 */
    sk_nop_02();                 /* FUN_0007c1a4 */
    (*(void (**)())sk_global_hook)();   /* (*DAT_00658c00)() */
    rt_34b0d4();                 /* FUN_0034b0d4 */
    rt_35238c();                 /* FUN_0035238c */
    rt_3504f4();                 /* FUN_003504f4 */
    sk_lock_ref(0);              /* FUN_00377bec */
    rt_34dee4();                 /* FUN_0034dee4 */
    rt_31ba3c();                 /* FUN_0031ba3c */
    /* FUN_000027e8 */
    rt_3527cc((void *)0x168);    /* FUN_003527cc(*(extraout_x16_01 + 0x168)) */
    ((void (*volatile)())0)();     /* (*extraout_x9)() */
    /* FUN_00100efc */
    rt_35a328();                 /* FUN_0035a328 */
    ((void (*volatile)())0)();     /* (*unaff_x19)() */
    sk_vspace_dispatch_e5c0(0);  /* FUN_0020e5c0 */
    sk_cpu_current();            /* FUN_0008e500 */
}

/* FUN_0020e9e0 @ 0x0020e9e0   (est. sk_vspace_dispatch_tail)
 * Ghidra: void FUN_0020e9e0(void)
 * Dispatcher that resolves a jumptable entry (unrecoverable by Ghidra) and
 * calls through it. Reads the current TCB, then jumps through an indirect
 * table slot (base+0x158, slot -8+8). Confidence: low (unrecoverable
 * jumptable; transcribed as indirect call).
 * Notes: Ghidra: "Could not recover jumptable at 0x0020ea34. Too many
 *   branches"; "Treating indirect jump as call". */
void sk_vspace_dispatch_tail(void)
{
    sk_tcb_get();                /* FUN_0007c0c4 */
    (**(void (**)())(*(void **)(*(void **)((char *)0 + 0x158) - 8) + 8))((void *)0);
}

/* FUN_0020eabc @ 0x0020eabc   (est. sk_vspace_dispatch_eabc)
 * Ghidra: void FUN_0020eabc(void)
 * Trap/service handler: per-CPU state + runtime bookkeeping, then writes a
 * 4-word result block at object+0x10..0x28 and returns through FUN_0008e500.
 * Confidence: low (PAC register flow collapsed).
 * Notes: Ghidra artifacts: extraout_x16_00/01, (*DAT_00658c00)() hook,
 *   writes *(x19+0x10/0x18/0x20/0x28). */
void sk_vspace_dispatch_eabc(void *unused)
{
    (void)unused;
    sk_cpu();                    /* FUN_0008e518 */
    rt_353860();                 /* FUN_00353860 */
    rt_3514b8((void *)0x160);    /* FUN_003514b8(*(extraout_x16 + 0x160)) */
    rt_356194();                 /* FUN_00356194 */
    rt_34de64();                 /* FUN_0034de64 */
    rt_34d3f4();                 /* FUN_0034d3f4 */
    sk_lock_acquire(0,0,0,0,0);  /* FUN_00377824 */
    rt_34a450();                 /* FUN_0034a450 */
    sk_nop_02();                 /* FUN_0007c1a4 */
    (*(void (**)())sk_global_hook)();   /* (*DAT_00658c00)() */
    rt_34b0c4();                 /* FUN_0034b0c4 */
    sk_nop_04();                 /* FUN_0007c0b8 */
    rt_3537c4((void *)0x168);    /* FUN_003537c4(*(extraout_x16_00 + 0x168)) */
    rt_3511d8(0);                /* FUN_003511d8 */
    ((void (*volatile)())0)();     /* (*extraout_x10)() */
    rt_3504c4();                 /* FUN_003504c4 */
    rt_353c3c();                 /* FUN_00353c3c */
    sk_lock_ref(0);              /* FUN_00377bec */
    rt_34dee4();                 /* FUN_0034dee4 */
    rt_31b9c0();                 /* FUN_0031b9c0 */
    rt_357b48();                 /* FUN_00357b48 */
    /* FUN_000277b8 */
    rt_34c930();                 /* FUN_0034c930 */
    ((void (*volatile)())0)();     /* (*extraout_x9)() */
    rt_356218();                 /* FUN_00356218 */
    sk_vspace_dispatch_c7fc(0);  /* FUN_0020c7fc */
    rt_35a42c();                 /* FUN_0035a42c */
    rt_351094();                 /* FUN_00310924 */
    rt_34c930();                 /* FUN_0034c930 */
    ((void (*volatile)())0)();     /* (*extraout_x9_00)() */
    rt_350b90((void *)8);        /* FUN_000b4390(*(extraout_x16_01 + 8)) */
    ((void (*volatile)())0)();     /* (*extraout_x8_00)() */
    rt_356218();                 /* FUN_00356218 */
    /* write result block at x19+0x10..0x28 from FUN_00348b1c etc. */
    rt_348b1c();                 /* FUN_00348b1c */
    rt_353100();                 /* FUN_00353100 */
    sk_cpu_current();            /* FUN_0008e500 */
}

/* FUN_0020ebf0 @ 0x0020ebf0   (est. sk_vspace_dispatch_ebf0)
 * Ghidra: void FUN_0020ebf0(void)
 * Trap handler: runtime bookkeeping then a branch — if the predicate
 * (FUN_0034f044, tested via flags) is false it returns through the vtable
 * slot at +0x20; otherwise it continues a second bookkeeping chain and falls
 * into the noreturn panic FUN_001afa84. Confidence: low.
 * Notes: Ghidra artifacts: in_ZR flag test, (*DAT_00658c00)() hook,
 *   (**(code **)(extraout_x16_00 + 0x20)) indirect, noreturn FUN_001afa84. */
void sk_vspace_dispatch_ebf0(void)
{
    sk_cpu();                    /* FUN_0008e518 */
    rt_358114();                 /* FUN_00358114 */
    rt_34c998();                 /* FUN_0034c998 */
    rt_350950((void *)0x160);    /* FUN_00350950(*(extraout_x16 + 0x160)) */
    rt_35147c();                 /* FUN_0035147c */
    rt_34d598();                 /* FUN_0034d598 */
    rt_34c444(0xff);             /* FUN_0034c444(0xff) */
    sk_lock_acquire(0,0,0,0,0);  /* FUN_00377824 */
    rt_34e67c();                 /* FUN_0034e67c */
    rt_310d68();                 /* FUN_00310d68 */
    /* FUN_000a6f88 */
    sk_nop_02();                 /* FUN_0007c1a4 */
    (*(void (**)())sk_global_hook)();   /* (*DAT_00658c00)() */
    rt_34bdfc();                 /* FUN_0034bdfc */
    rt_31b9d8(0);                /* FUN_0031b9d8 */
    rt_350210();                 /* FUN_00350210 */
    sk_lock_ref(0);              /* FUN_00377bec */
    rt_354d74(0,0);              /* FUN_00354d74 */
    rt_351aec();                 /* FUN_00351aec */
    ((void (*volatile)())0)();     /* (*pcVar2)() */
    if (0) {  /* !(bool)in_ZR from FUN_0034f044 result */
        rt_34f384();             /* FUN_0034f384 */
        (**(void (**)())(0 + 0x20))((void *)0);   /* (**(code**)(extraout_x16_00+0x20))() */
        sk_cpu_current();        /* FUN_0008e500 */
        return;
    }
    rt_352e18(0, 0);             /* FUN_00352e18 */
    ((void (*volatile)())0)();     /* (*extraout_x8_00)() */
    rt_34abc4();                 /* FUN_0034abc4 */
    rt_3593c0();                 /* FUN_003593c0 */
    rt_349c58();                 /* FUN_00349c58 */
    sk_panic_no_return();        /* FUN_001afa84 (noreturn) */
}

/* FUN_0020eefc @ 0x0020eefc   (est. sk_vspace_dispatch_eefc)
 * Ghidra: void FUN_0020eefc(void)
 * Largest handler in the opening block: two lock-guarded bookkeeping
 * sequences, a Swift-existential metadata call, recursive dispatch to
 * FUN_0020ebf0 twice, then either a long teardown chain ending in the
 * restore-tail, or the noreturn panic FUN_001afe4c. Confidence: low.
 * Notes: Ghidra artifacts: s_Swift_ExistentialCollection_swif_005cf680,
 *   (*DAT_00658c00)() hooks, FUN_0020ebf0 recursion, (*unaff_x28)() indirect,
 *   noreturn FUN_001afe4c. */
void sk_vspace_dispatch_eefc(void)
{
    sk_cpu();                    /* FUN_0008e518 */
    rt_3586cc();                 /* FUN_003586cc */
    rt_34c998();                 /* FUN_0034c998 */
    rt_35125c();                 /* FUN_0035125c */
    rt_35147c();                 /* FUN_0035147c */
    rt_3525cc();                 /* FUN_003525cc */
    rt_34ba38();                 /* FUN_0034ba38 */
    sk_lock_acquire(0,0,0,0,0);  /* FUN_00377824 */
    rt_34ab20();                 /* FUN_0034ab20 */
    sk_nop_02();                 /* FUN_0007c1a4 */
    (*(void (**)())sk_global_hook)();   /* (*DAT_00658c00)() */
    rt_34aab0();                 /* FUN_0034aab0 */
    rt_352f54();                 /* FUN_00352f54 */
    rt_34ba38();                 /* FUN_0034ba38 */
    sk_lock_acquire(0,0,0,0,0);  /* FUN_00377824 */
    rt_34a654();                 /* FUN_0034a654 */
    rt_348d7c();                 /* FUN_00348d7c */
    (*(void (**)())sk_global_hook)((void *)0x40);   /* (*DAT_00658c00)(*(x8+0x40)) */
    rt_348a18();                 /* FUN_00348a18 */
    (*(void (**)())sk_global_hook)();   /* (*DAT_00658c00)() */
    rt_350464();                 /* FUN_00350464 */
    rt_34961c();                 /* FUN_00349618 */
    (*(void (**)())sk_global_hook)((void *)0x40);   /* (*DAT_00658c00)(*(x8_00+0x40)) */
    rt_348a34();                 /* FUN_00348a34 */
    (*(void (**)())sk_global_hook)();   /* (*DAT_00658c00)() */
    rt_34b8bc();                 /* FUN_0034b8bc */
    rt_34ac78();                 /* FUN_0034ac78 */
    sk_lock_ref(0);              /* FUN_00377bec */
    rt_350500();                 /* FUN_00350500 */
    rt_310e08(0,0,0);            /* FUN_00310e08 */
    rt_348e00();                 /* FUN_00348e00 */
    sk_nop_02();                 /* FUN_0007c1a4 */
    (*(void (**)())sk_global_hook)();   /* (*DAT_00658c00)() */
    rt_350428();                 /* FUN_00350428 */
    rt_34911c();                 /* FUN_0034911c */
    sk_nop_02();                 /* FUN_0007c1a4 */
    (*(void (**)())sk_global_hook)();   /* (*DAT_00658c00)() */
    rt_355c84();                 /* FUN_00355c84 */
    /* FUN_000027e8 */
    rt_3558d8((void *)0x168);    /* FUN_003558d8(*(extraout_x16_01 + 0x168)) */
    ((void (*volatile)())0)();     /* (*extraout_x10)() */
    rt_351c1c(0,0,0);            /* FUN_00351c1c(Swift existential) */
    sk_vspace_dispatch_ebf0();   /* FUN_0020ebf0 */
    rt_35a420();                 /* FUN_0035a420 */
    rt_351c1c(0,0,0);            /* FUN_00351c1c */
    sk_vspace_dispatch_ebf0();   /* FUN_0020ebf0 */
    rt_310e20(0);                /* FUN_00310e20 */
    rt_350104();                 /* FUN_00350104 */
    rt_3516b4();                 /* FUN_003516b4 */
    if (((unsigned long (*volatile)())0)() & 1) {   /* (*extraout_x8_01)() */
        rt_35238c();             /* FUN_0035238c */
        rt_354594();             /* FUN_00354594 */
        rt_350798(0,0,0);        /* FUN_00350798 */
        rt_31ba3c();             /* FUN_0031ba3c */
        rt_356670();             /* FUN_00356670 */
        rt_350b48();             /* FUN_00350b48 */
        ((void (*volatile)())0)(); /* (*pcVar4)() */
        rt_3516f0(0);            /* FUN_003516f0 */
        ((void (*volatile)())0)(); /* (*pcVar4)() */
        rt_351d0c();             /* FUN_00351d0c */
        rt_3507d4();             /* FUN_003507d4 */
        ((void (*volatile)())0)(); /* (*extraout_x9)() */
        rt_351360();             /* FUN_00351360 */
        ((void (*volatile)())0)(); /* (*pcVar4)() */
        rt_35a058();             /* FUN_0035a058 */
        ((void (*volatile)())0)(); /* (*unaff_x28)() */
        rt_3507d4((void *)0x20); /* FUN_003507d4(*(extraout_x16+0x20)) */
        ((void (*volatile)())0)(); /* (*extraout_x8_02)() */
        rt_357424();             /* FUN_00357424 */
        ((void (*volatile)())0)(); /* (*pcVar4)() */
        /* FUN_000e72b0 */
        ((void (*volatile)())0)(); /* (*unaff_x28)() */
        rt_351bb8();             /* FUN_00351bb8 */
        rt_35242c();             /* FUN_0035242c */
        rt_351190();             /* FUN_00351190 */
        ((void (*volatile)())0)(); /* (*extraout_x9_00)() */
        rt_353be8();             /* FUN_00353be8 */
        rt_3507bc();             /* FUN_003507bc */
        ((void (*volatile)())0)(); /* (*extraout_x8_03)() */
        rt_354d38();             /* FUN_00354d38 */
        sk_nop_03();             /* FUN_0007c1c4 */
        ((void (*volatile)())0)(); /* (*extraout_x8_04)() */
        sk_vspace_dispatch_e5c0(0);  /* FUN_0020e5c0 */
        sk_cpu_current();        /* FUN_0008e500 */
        return;
    }
    rt_34b348();                 /* FUN_0034b348 */
    rt_35a4d4();                 /* FUN_0035a4d4 */
    rt_347ef4();                 /* FUN_00347ef4 */
    sk_panic_no_return2();       /* FUN_001afe4c (noreturn) */
}

/* FUN_0020f430 @ 0x0020f430   (est. sk_vspace_trap_f430)
 * Ghidra: void FUN_0020f430(undefined8 param_1,undefined8 param_2,undefined8 param_3)
 * Two-phase handler. Phase 1 does bookkeeping; if FUN_00362acc finds the
 * object it unwinds and returns through FUN_00084234. Otherwise phase 2 runs
 * a longer sequence ending in the restore-tail (FUN_0020ebf0 recursion + tail).
 * Confidence: low (PAC).
 * Notes: Ghidra artifacts: auVar3/auVar4 [16], extraout_x16_02, (*DAT_00658c00)(). */
void sk_vspace_trap_f430(void *a, void *b, void *c)
{
    (void)a; (void)b; (void)c;
    rt_34c20c();                 /* FUN_00084220 -> FUN_0034c20c (auVar3) */
    sk_tcb_get();                /* FUN_0007c0c4 */
    rt_3499b4();                 /* FUN_003499b4 */
    rt_351408();                 /* FUN_00351408 */
    (*(void (**)())sk_global_hook)();   /* (*DAT_00658c00)() */
    rt_349c14();                 /* FUN_00349c14 */
    rt_3514b8((void *)0x160);    /* FUN_003514b8(*(extraout_x16 + 0x160)) */
    rt_3521d4();                 /* FUN_003521d4 */
    rt_350768(0xff);             /* FUN_00350768(0xff) */
    sk_lock_acquire(0,0,0,0,0);  /* FUN_00377824 */
    rt_350524();                 /* FUN_00350524 */
    rt_352ea8();                 /* FUN_00352ea8 */
    sk_lock_ref(0);              /* FUN_00377bec */
    rt_34dee4();                 /* FUN_0034dee4 */
    rt_31b9c0();                 /* FUN_0031b9c0 */
    rt_356b8c();                 /* FUN_00356b8c */
    if (rt_362acc() != 0) {      /* FUN_00362acc */
        sk_nop_05();             /* FUN_0007c178 */
        rt_34a868((void *)0x168);/* FUN_0034a868(*(extraout_x16_00 + 0x168)) */
        ((void (*volatile)())0)(); /* (*extraout_x10)() */
        rt_3595c0();             /* FUN_003595c0 */
        /* FUN_00027818 */
        rt_350114();             /* FUN_00350114 */
        ((void (*volatile)())0)(); /* (*extraout_x8)() */
        rt_34eb84();             /* FUN_0034eb84 */
        ((void (*volatile)())0)(); /* (*extraout_x8_00)() */
        sk_frame_leave();        /* FUN_00084234 */
        return;
    }
    rt_3498f4();                 /* FUN_003498f4 */
    rt_349190();                 /* FUN_00349190 */
    sk_cpu();                    /* FUN_0008e518 */
    rt_34a674();                 /* FUN_0034a674 */
    rt_3499b4();                 /* FUN_003499b4 */
    rt_351408();                 /* FUN_00351408 */
    (*(void (**)())sk_global_hook)();   /* (*DAT_00658c00)() */
    rt_34c8f8();                 /* FUN_0034c8f8 */
    rt_3549d8();                 /* FUN_003549d8 */
    rt_351bec(0);                /* FUN_00351bec */
    rt_34c354();                 /* FUN_0034c354 */
    rt_3508c0();                 /* FUN_003508c0 */
    sk_lock_acquire(0,0,0,0,0);  /* FUN_00377824 */
    rt_348cd0();                 /* FUN_00348cd0 */
    (*(void (**)())sk_global_hook)((void *)0x40);   /* (*DAT_00658c00)(*(x8_01+0x40)) */
    rt_348a80();                 /* FUN_00348a80 */
    (*(void (**)())sk_global_hook)();   /* (*DAT_00658c00)() */
    rt_34c2d8();                 /* FUN_0034c2d8 */
    rt_356bc8();                 /* FUN_00356bc8 */
    rt_34f5a4();                 /* FUN_0034f5a4 */
    sk_lock_ref(0);              /* FUN_00377bec */
    rt_34c55c();                 /* FUN_0034c55c */
    rt_31b9c0();                 /* FUN_0031b9c0 */
    /* FUN_000027e8 */
    rt_34ad8c((void *)0x168);    /* FUN_0034ad8c(*(extraout_x16_02 + 0x168)) */
    ((void (*volatile)())0)();     /* (*extraout_x10_00)() */
    rt_353bdc();                 /* FUN_00353bdc */
    rt_351c1c(0,0,0);            /* FUN_00351c1c */
    sk_vspace_dispatch_ebf0();   /* FUN_0020ebf0 */
    rt_356c24();                 /* FUN_00356c24 */
    rt_310ea4();                 /* FUN_00310ea4 */
    rt_351058();                 /* FUN_00351058 */
    rt_351444(0, c);             /* FUN_00351444 */
    ((void (*volatile)())0)();     /* (*extraout_x9)() */
    rt_351354((void *)8);        /* FUN_00351354(*(extraout_x16_01 + 8)) */
    ((void (*volatile)())0)();     /* (*extraout_x8_02)() */
    rt_34eb94();                 /* FUN_0034eb94 */
    ((void (*volatile)())0)();     /* (*extraout_x8_03)() */
    rt_348b1c();                 /* FUN_00348b1c */
    rt_356090();                 /* FUN_00356090 */
    sk_cpu_current();            /* FUN_0008e500 */
}

/* FUN_0020f6fc @ 0x0020f6fc   (est. sk_vspace_trap_f6fc)
 * Ghidra: void FUN_0020f6fc(void)
 * Handler with two recursive dispatches to FUN_0020ebf0, an indirect fn-ptr
 * pair (FUN_000e15d8 + pcVar3), and a final restore-tail. Confidence: low.
 * Notes: Ghidra artifacts: auVar5/auVar6, extraout_x16_03, (*DAT_00658c00)(). */
void sk_vspace_trap_f6fc(void)
{
    rt_34c20c();                 /* FUN_0008e518 -> FUN_0034c20c */
    rt_34c998();                 /* FUN_0034c998 */
    rt_350bd8((void *)0x160);    /* FUN_00350bd8(*(extraout_x16 + 0x160)) */
    rt_35147c();                 /* FUN_0035147c */
    rt_349748();                 /* FUN_00349748 (auVar6) */
    sk_lock_acquire(0,0,0,0,0);  /* FUN_00377824 */
    rt_348d64();                 /* FUN_00348d64 */
    (*(void (**)())sk_global_hook)((void *)0x40);   /* (*DAT_00658c00)(*(x8+0x40)) */
    rt_3490d0();                 /* FUN_003490d0 */
    (*(void (**)())sk_global_hook)();   /* (*DAT_00658c00)() */
    rt_34b3d8();                 /* FUN_0034b3d8 */
    rt_349734();                 /* FUN_00349734 */
    sk_nop_02();                 /* FUN_0007c1a4 */
    (*(void (**)())sk_global_hook)();   /* (*DAT_00658c00)() */
    rt_34bdfc();                 /* FUN_0034bdfc */
    rt_350500();                 /* FUN_00350500 */
    rt_310d68();                 /* FUN_00310d68 */
    /* FUN_000a6f88 */
    sk_nop_02();                 /* FUN_0007c1a4 */
    (*(void (**)())sk_global_hook)();   /* (*DAT_00658c00)() */
    rt_34aee4();                 /* FUN_0034aee4 */
    /* FUN_000027e8 */
    rt_350b60((void *)0x168);    /* FUN_00350b60(*(extraout_x16_03 + 0x168)) */
    ((void (*volatile)())0)();     /* (*extraout_x10)() */
    rt_35a128();                 /* FUN_0035a128 */
    rt_34fc34(0,0);              /* FUN_0034fc34 */
    sk_vspace_dispatch_ebf0();   /* FUN_0020ebf0 */
    rt_34fc34(0,0);              /* FUN_0034fc34 */
    sk_vspace_dispatch_ebf0();   /* FUN_0020ebf0 */
    rt_3195f8(0);                /* FUN_003195f8 */
    rt_350b24();                 /* FUN_00350b24 */
    ((void (*volatile)())0)();     /* (*extraout_x9)() */
    /* FUN_000e15d8 */
    ((void (*volatile)())0)();     /* (*pcVar3)() */
    rt_351274();                 /* FUN_00351274 */
    ((void (*volatile)())0)();     /* (*pcVar3)() */
    rt_3507e0((void *)8);        /* FUN_003507e0(*(extraout_x16_02 + 8)) */
    ((void (*volatile)())0)();     /* (*extraout_x8_00)() */
    rt_356f6c();                 /* FUN_00356f6c */
    rt_3536ac();                 /* FUN_003536ac */
    rt_358cf8(0, 0, 0, 0);       /* FUN_00358cf8(FUN_0031ba54,...) */
    /* FUN_001d88fc */
    rt_354d38();                 /* FUN_00354d38 */
    rt_3505e8();                 /* FUN_003505e8 */
    ((void (*volatile)())0)();     /* (*extraout_x8_01)() */
    sk_cpu_current();            /* FUN_0008e500 */
}

/* FUN_0020f970 @ 0x0020f970   (est. sk_vspace_obj_alloc_f970)
 * Ghidra: void FUN_0020f970(undefined8 *param_1, undefined8 param_2, undefined8 param_3, undefined8 param_4)
 * Small object allocator: resolves the object vtable, locks, allocates the
 * object, invokes its constructor at vtable+0x10, and stores the result + a
 * 0x66c280 tag into the out-slot. Confidence: medium (small, locally coherent).
 * Notes: Ghidra artifacts: &DAT_0060e208/&DAT_0060e230/&LAB_0060e218 debug
 *   strings, 0x66c280 method tag, (**(code **)(lVar3 + 0x10)) constructor. */
void sk_vspace_obj_alloc_f970(void **out, void *b, void *c, void *d)
{
    (void)b; (void)c; (void)d;
    rt_34c8f8();                 /* FUN_00027754 (param_4) */
    sk_lock_acquire(0,0,0,0,0);  /* FUN_00377824 */
    rt_350500();                 /* FUN_00350500 */
    sk_lock_ref(0);              /* FUN_00377bec */
    rt_31b9c0(0,0,0);            /* FUN_0031b9c0 */
    (*(void (**)())sk_global_hook)((void *)0x40);   /* (*DAT_00658c00)(vtable+0x40 & ~0xf) */
    rt_350c8c(0);                /* FUN_00350c8c */
    sk_vspace_dispatch_c7fc(0);             /* FUN_0020c7fc */
    out[0] = 0;
    out[1] = (void *)0x66c280;
}

/* FUN_0020fab4 @ 0x0020fab4   (est. sk_vspace_trap_fab4)
 * Ghidra: void FUN_0020fab4(void)
 * Three-phase handler: two independent bookkeeping paths gated by
 * FUN_00362acc, each ending in an unwind or a long teardown sequence; the
 * third path is a near-copy of FUN_0020eefc with recursive dispatch.
 * Confidence: low (PAC).
 * Notes: Ghidra artifacts: auVar8, in_stack_*, (*DAT_00658c00)() hooks,
 *   FUN_0020ebf0 recursion, Swift existentials, noreturn paths. */
void sk_vspace_trap_fab4(void)
{
    sk_cpu();                    /* FUN_0008e518 */
    sk_tcb_get();                /* FUN_0007c0c4 */
    rt_3499b4();                 /* FUN_003499b4 */
    rt_351408();                 /* FUN_00351408 */
    (*(void (**)())sk_global_hook)();   /* (*DAT_00658c00)() */
    rt_34c8f8();                 /* FUN_0034c8f8 */
    rt_3549d8();                 /* FUN_003549d8 */
    rt_352894((void *)0x160);    /* FUN_00352894(*(extraout_x16 + 0x160)) */
    rt_34cd7c();                 /* FUN_0034cd7c */
    rt_3508d8();                 /* FUN_003508d8 */
    sk_lock_acquire(0,0,0,0,0);  /* FUN_00377824 */
    rt_357944();                 /* FUN_00357944 */
    rt_34f344();                 /* FUN_0034f344 */
    sk_lock_ref(0);              /* FUN_00377bec */
    rt_34c55c();                 /* FUN_0034c55c */
    rt_31b9c0();                 /* FUN_0031b9c0 */
    if (rt_362acc() != 0) {      /* FUN_00362acc */
        sk_nop_05();             /* FUN_0007c178 */
        rt_34ad8c((void *)0x168);/* FUN_0034ad8c(*(extraout_x16_00 + 0x168)) */
        ((void (*volatile)())0)(); /* (*extraout_x10)() */
        rt_35a140();             /* FUN_0035a140 */
        rt_34f564(0);            /* FUN_0034f564 */
        /* FUN_001d30f8 */
        rt_34eb94();             /* FUN_0034eb94 */
        ((void (*volatile)())0)(); /* (*extraout_x8)() */
        sk_cpu_current();        /* FUN_0008e500 */
        return;
    }
    rt_3498f4();                 /* FUN_003498f4 */
    rt_349190();                 /* FUN_00349190 */
    sk_cpu();                    /* FUN_0008e518 */
    rt_34c998();                 /* FUN_0034c998 */
    rt_35125c((void *)0x160);    /* FUN_0035125c(*(extraout_x16_02 + 0x160)) */
    rt_35147c();                 /* FUN_0035147c */
    rt_34b164();                 /* FUN_0034b164 */
    rt_34f564();                 /* FUN_0034f564 */
    sk_lock_acquire(0,0,0,0,0);  /* FUN_00377824 */
    rt_348d7c();                 /* FUN_00348d7c */
    sk_nop_02();                 /* FUN_0007c1a4 */
    (*(void (**)())sk_global_hook)();   /* (*DAT_00658c00)() */
    rt_34af20();                 /* FUN_0034af20 */
    rt_3494e8();                 /* FUN_003494e8 */
    sk_nop_02();                 /* FUN_0007c1a4 */
    (*(void (**)())sk_global_hook)();   /* (*DAT_00658c00)() */
    rt_34cff4();                 /* FUN_0034cff4 */
    rt_350c8c(0);                /* FUN_00350c8c */
    sk_lock_ref(0);              /* FUN_00377bec */
    rt_34e414();                 /* FUN_0034e414 */
    rt_31b9c0();                 /* FUN_0031b9c0 */
    rt_357ac0();                 /* FUN_00357ac0 */
    if (rt_362acc() != 0) {      /* FUN_00362acc */
        sk_nop_05();             /* FUN_0007c178 */
        rt_350b60((void *)0x168);/* FUN_00350b60(*(extraout_x16_04 + 0x168)) */
        rt_353fa0();             /* FUN_00353fa0 */
        ((void (*volatile)())0)(); /* (*extraout_x10_00)() */
        rt_353bdc();             /* FUN_00353bdc */
        rt_351c1c(0,0);          /* FUN_00351c1c */
        sk_vspace_dispatch_ebf0();   /* FUN_0020ebf0 */
        rt_3513c0(0,0);          /* FUN_003513c0 */
        /* FUN_001d31b0 */
        rt_3500c0();             /* FUN_003500c0 */
        ((void (*volatile)())0)(); /* (*extraout_x8_00)() */
        /* FUN_00084180 */
        ((void (*volatile)())0)(); /* (*extraout_x8_01)() */
        rt_352988();             /* FUN_00352980 */
        sk_cpu_current();        /* FUN_0008e500 */
        return;
    }
    rt_3498f4();                 /* FUN_003498f4 */
    rt_349190();                 /* FUN_00349190 */
    sk_cpu();                    /* FUN_0008e518 */
    rt_3586cc();                 /* FUN_003586cc */
    rt_34c998();                 /* FUN_0034c998 */
    rt_350bd8((void *)0x160);    /* FUN_00350bd8(*(extraout_x16_05 + 0x160)) */
    rt_35147c();                 /* FUN_0035147c */
    rt_349748();                 /* FUN_00349748 (auVar8) */
    sk_lock_acquire(0,0,0,0,0);  /* FUN_00377824 */
    rt_348ce8();                 /* FUN_00348ce8 */
    (*(void (**)())sk_global_hook)((void *)0x40);   /* (*DAT_00658c00)(*(x8_02+0x40)) */
    rt_348a34();                 /* FUN_00348a34 */
    (*(void (**)())sk_global_hook)();   /* (*DAT_00658c00)() */
    rt_34b8bc();                 /* FUN_0034b8bc */
    rt_3494e8();                 /* FUN_003494e8 */
    sk_nop_02();                 /* FUN_0007c1a4 */
    (*(void (**)())sk_global_hook)();   /* (*DAT_00658c00)() */
    rt_34aee4();                 /* FUN_0034aee4 */
    /* FUN_000027e8 */
    rt_34a1e0((void *)0x168);    /* FUN_0034a1e0(*(extraout_x16_09 + 0x168)) */
    ((void (*volatile)())0)();     /* (*extraout_x10_01)() */
    rt_351c1c(0,0,0);            /* FUN_00351c1c(Swift existential) */
    sk_vspace_dispatch_ebf0();   /* FUN_0020ebf0 */
    rt_35a420();                 /* FUN_0035a420 */
    rt_351c1c(0,0,0);            /* FUN_00351c1c */
    sk_vspace_dispatch_ebf0();   /* FUN_0020ebf0 */
    rt_31ba70(0);                /* FUN_0031ba70 */
    rt_350104();                 /* FUN_00350104 */
    rt_350974();                 /* FUN_00350974 */
    ((void (*volatile)())0)();     /* (*extraout_x8_03)() */
    rt_350b00();                 /* FUN_00350b00 */
    ((void (*volatile)())0)();     /* (*pcVar6)() */
    rt_351384();                 /* FUN_00351384 */
    ((void (*volatile)())0)();     /* (*pcVar6)() */
    rt_3505e8((void *)8);        /* FUN_003505e8(*(extraout_x16_08 + 8)) */
    ((void (*volatile)())0)();     /* (*extraout_x8_04)() */
    rt_3548b8();                 /* FUN_003548b8 */
    sk_cpu_current();            /* FUN_0008e500 */
}

/* FUN_0020ff38 @ 0x0020ff38   (est. sk_vspace_trap_ff38)
 * Ghidra: void FUN_0020ff38(void)
 * Short teardown handler: two bookkeeping sequences (each starting with
 * FUN_0034ecb8 + FUN_003494e8), then an indirect call, and FUN_00356310.
 * Confidence: low (PAC).
 * Notes: Ghidra artifacts: extraout_x8_00, (*DAT_00658c00)() hook. */
void sk_vspace_trap_ff38(void)
{
    rt_34ecb8();                 /* FUN_0034ecb8 */
    rt_3494e8();                 /* FUN_003494e8 */
    sk_nop_02();                 /* FUN_0007c1a4 */
    (*(void (**)())sk_global_hook)();   /* (*DAT_00658c00)() */
    rt_34b2f8();                 /* FUN_0034b2f8 */
    rt_351d9c();                 /* FUN_00351d9c */
    rt_34ad8c((void *)0x168);    /* FUN_0034ad8c(*(extraout_x16 + 0x168)) */
    ((void (*volatile)())0)();     /* (*extraout_x10)() */
    rt_351d9c();                 /* FUN_00351d9c */
    rt_350950((void *)0x160);    /* FUN_00350950(*(extraout_x16_00 + 0x160)) */
    /* FUN_00027788 */
    rt_34ac64();                 /* FUN_0034ac64 */
    ((void (*volatile)())0)();     /* (*extraout_x8)() */
    rt_34da48();                 /* FUN_0034da48 */
    ((void (*volatile)())0)();     /* (*extraout_x8_00)() */
    rt_356310();                 /* FUN_00356310 */
}

/* FUN_00210010 @ 0x00210010   (est. sk_vspace_trap_10010)
 * Ghidra: void FUN_00210010(void)
 * Two-phase handler like FUN_0020f430 (object-lookup branch then longer
 * sequence ending in the restore-tail). Confidence: low (PAC).
 * Notes: Ghidra artifacts: auVar1, in_stack_00000038, (*DAT_00658c00)(). */
void sk_vspace_trap_10010(void)
{
    sk_cpu();                    /* FUN_0008e518 */
    sk_tcb_get();                /* FUN_0007c0c4 */
    rt_3499b4();                 /* FUN_003499b4 */
    rt_351408();                 /* FUN_00351408 */
    (*(void (**)())sk_global_hook)();   /* (*DAT_00658c00)() */
    rt_349c14();                 /* FUN_00349c14 */
    rt_352894(0);                /* FUN_00352894 */
    rt_3521d4();                 /* FUN_003521d4 */
    rt_34c454();                 /* FUN_0034c454 */
    sk_lock_acquire(0,0,0,0,0);  /* FUN_00377824 */
    rt_348e60();                 /* FUN_00348e60 */
    (*(void (**)())sk_global_hook)((void *)0x40);   /* (*DAT_00658c00)(*(x8+0x40)) */
    rt_348bbc();                 /* FUN_00348bbc */
    (*(void (**)())sk_global_hook)();   /* (*DAT_00658c00)() */
    rt_34b4c0();                 /* FUN_0034b4c0 */
    rt_350b9c();                 /* FUN_00350b9c */
    sk_lock_ref(0);              /* FUN_00377bec */
    rt_34dee4();                 /* FUN_0034dee4 */
    rt_31b9c0();                 /* FUN_0031b9c0 */
    /* FUN_000027e8 */
    rt_34a868((void *)0x168);    /* FUN_0034a868(*(extraout_x16_00 + 0x168)) */
    ((void (*volatile)())0)();     /* (*extraout_x10)() */
    rt_34e9b8();                 /* FUN_0034e9b8 */
    sk_vspace_dispatch_ebf0();   /* FUN_0020ebf0 */
    rt_357508();                 /* FUN_00357508 */
    rt_31e104();                 /* FUN_0031e104 */
    rt_34d434();                 /* FUN_0034d434 */
    rt_350c8c();                 /* FUN_00350c8c */
    ((void (*volatile)())0)();     /* (*extraout_x9)() */
    rt_3511a8((void *)8);        /* FUN_003511a8(*(extraout_x16 + 8)) */
    ((void (*volatile)())0)();     /* (*extraout_x8_00)() */
    rt_34eb84();                 /* FUN_0034eb84 */
    ((void (*volatile)())0)();     /* (*extraout_x8_01)() */
    rt_35a3c4();                 /* FUN_0035a3c4 */
    rt_348b1c();                 /* FUN_00348b1c */
    rt_356090();                 /* FUN_00356090 */
    sk_cpu_current();            /* FUN_0008e500 */
}

/* FUN_0021019c @ 0x0021019c   (est. sk_vspace_trap_1019c)
 * Ghidra: void FUN_0021019c(void)
 * Two-phase handler (FUN_00362acc gate); second phase dispatches through an
 * unrecoverable jumptable at 0x0021031c. Confidence: low.
 * Notes: Ghidra: "Could not recover jumptable at 0x0021031c"; extraout_x8_02
 *   chain; 0x2102c0 table address. */
void sk_vspace_trap_1019c(void)
{
    sk_cpu();                    /* FUN_0008e518 */
    sk_tcb_get();                /* FUN_0007c0c4 */
    rt_3499b4();                 /* FUN_003499b4 */
    rt_351408();                 /* FUN_00351408 */
    (*(void (**)())sk_global_hook)();   /* (*DAT_00658c00)() */
    rt_349c14();                 /* FUN_00349c14 */
    rt_351bec((void *)0x160);    /* FUN_00351bec(*(extraout_x16 + 0x160)) */
    rt_34cd7c();                 /* FUN_0034cd7c */
    rt_3508c0();                 /* FUN_003508c0 */
    sk_lock_acquire(0,0,0,0,0);  /* FUN_00377824 */
    rt_356bc8();                 /* FUN_00356bc8 */
    rt_34f5a4();                 /* FUN_0034f5a4 */
    sk_lock_ref(0);              /* FUN_00377bec */
    rt_34c55c();                 /* FUN_0034c55c */
    rt_31b9c0();                 /* FUN_0031b9c0 */
    rt_356b8c();                 /* FUN_00356b8c */
    if (rt_362acc() != 0) {      /* FUN_00362acc */
        sk_nop_05();             /* FUN_0007c178 */
        rt_34a868((void *)0x168);/* FUN_0034a868(*(extraout_x16_00 + 0x168)) */
        ((void (*volatile)())0)(); /* (*extraout_x10)() */
        rt_3595c0();             /* FUN_003595c0 */
        rt_3196e8(0);            /* FUN_003196e8 */
        rt_350114();             /* FUN_00350114 */
        ((void (*volatile)())0)(); /* (*extraout_x8)() */
        rt_34eb84();             /* FUN_0034eb84 */
        ((void (*volatile)())0)(); /* (*extraout_x8_00)() */
        sk_cpu_current();        /* FUN_0008e500 */
        return;
    }
    rt_3498f4();                 /* FUN_003498f4 */
    rt_349190();                 /* FUN_00349190 */
    rt_34c20c();                 /* FUN_0007c0c4(...,0x2102c0) */
    (**(void (**)())(*(void **)(*(void **)((char *)0 + 0x158) - 8) + 0x10))((void *)0);
}

/* FUN_002103ac @ 0x002103ac   (est. sk_vspace_trap_103ac)
 * Ghidra: void FUN_002103ac(void)
 * Handler: frame enter, bookkeeping, then returns through FUN_002085fc and
 * FUN_00084234. Confidence: low (PAC).
 * Notes: Ghidra artifacts: auVar1, extraout_x16_00/01, (*DAT_00658c00)(). */
void sk_vspace_trap_103ac(void)
{
    sk_frame_enter();            /* FUN_00084220 */
    sk_tcb_get();                /* FUN_0007c0c4 */
    rt_3499b4();                 /* FUN_003499b4 */
    rt_351408();                 /* FUN_00351408 */
    (*(void (**)())sk_global_hook)();   /* (*DAT_00658c00)() */
    rt_349c14();                 /* FUN_00349c14 */
    rt_350b60((void *)0x168);    /* FUN_00027754(*(extraout_x16 + 0x168)) */
    /* FUN_00027754() */
    rt_352894(0);                /* FUN_00352894 */
    rt_350ca4();                 /* FUN_00350ca4 */
    rt_34c454();                 /* FUN_0034c454 */
    sk_lock_acquire(0,0,0,0,0);  /* FUN_00377824 */
    rt_34ab20();                 /* FUN_0034ab20 */
    sk_nop_02();                 /* FUN_0007c1a4 */
    (*(void (**)())sk_global_hook)();   /* (*DAT_00658c00)() */
    rt_34aee4();                 /* FUN_0034aee4 */
    /* FUN_000027e8 */
    rt_34d284((void *)0x170);    /* FUN_0034d284(*(extraout_x16_00 + 0x170)) */
    ((void (*volatile)())0)();     /* (*extraout_x9)() */
    /* FUN_000a68c4 */
    rt_350b24();                 /* FUN_00350b24 */
    rt_35072c();                 /* FUN_0035072c */
    ((void (*volatile)())0)();     /* (*extraout_x9_00)() */
    rt_34ed78();                 /* FUN_0034ed78 */
    sk_lock_ref(0);              /* FUN_00377bec */
    rt_355b04();                 /* FUN_00355b04 */
    sk_vspace_resume6(0);        /* FUN_002085fc */
    sk_frame_leave();            /* FUN_00084234 */
}

/* FUN_002104d8 @ 0x002104d8   (est. sk_vspace_trap_104d8)
 * Ghidra: void FUN_002104d8(void)
 * Short teardown handler (mirror of FUN_0020ff38 with 0x170/0x168 fields).
 * Confidence: low (PAC).
 * Notes: Ghidra artifacts: extraout_x8_00, (*DAT_00658c00)() hook. */
void sk_vspace_trap_104d8(void)
{
    rt_34ecb8();                 /* FUN_0034ecb8 */
    rt_3494e8();                 /* FUN_003494e8 */
    sk_nop_02();                 /* FUN_0007c1a4 */
    (*(void (**)())sk_global_hook)();   /* (*DAT_00658c00)() */
    rt_34b2f8();                 /* FUN_0034b2f8 */
    rt_351d9c();                 /* FUN_00351d9c */
    rt_34ad8c((void *)0x170);    /* FUN_0034ad8c(*(extraout_x16 + 0x170)) */
    ((void (*volatile)())0)();     /* (*extraout_x10)() */
    rt_351d9c();                 /* FUN_00351d9c */
    rt_350b60((void *)0x168);    /* FUN_00027754(*(extraout_x16_00 + 0x168)) */
    /* FUN_00027754() */
    rt_350950(0);                /* FUN_00350950 */
    /* FUN_000a6894 */
    rt_34ac64();                 /* FUN_0034ac64 */
    ((void (*volatile)())0)();     /* (*extraout_x8)() */
    rt_34da48();                 /* FUN_0034da48 */
    ((void (*volatile)())0)();     /* (*extraout_x8_00)() */
    rt_356310();                 /* FUN_00356310 */
}

/* FUN_002105b8 @ 0x002105b8   (est. sk_vspace_trap_105b8)
 * Ghidra: void FUN_002105b8(void)
 * Handler with a local state block (auStack_40), runtime bookkeeping, and a
 * final result through FUN_00353d14. Confidence: low (PAC).
 * Notes: Ghidra artifacts: auStack_40[32], FUN_00351560(FUN_00346ff4,...). */
void sk_vspace_trap_105b8(void)
{
    rt_353cfc();                 /* FUN_00353cfc */
    rt_34d634();                 /* FUN_0034d634 */
    rt_3494e8();                 /* FUN_003494e8 */
    sk_nop_02();                 /* FUN_0007c1a4 */
    (*(void (**)())sk_global_hook)();   /* (*DAT_00658c00)() */
    rt_34b0c4();                 /* FUN_0034b0c4 */
    rt_352ff4();                 /* FUN_00352ff4 */
    rt_34c1bc((void *)0x170);    /* FUN_0034c1bc(*(extraout_x16 + 0x170)) */
    ((void (*volatile)())0)();     /* (*extraout_x10)() */
    rt_35a1f4();                 /* FUN_0035a1f4 */
    rt_34a210();                 /* FUN_0034a210 */
    /* FUN_00002534 */
    rt_350b60(0);                /* FUN_00027754(uVar1) */
    /* FUN_00027754() */
    rt_351560(0, 0);             /* FUN_00351560(FUN_00346ff4, auStack_40) */
    rt_358eb8();                 /* FUN_00358eb8 */
    /* FUN_000262fc */
    rt_354dd0();                 /* FUN_00354dd0 */
    rt_34f9c8();                 /* FUN_0034f9c8 */
    ((void (*volatile)())0)();     /* (*extraout_x8)() */
    rt_352df4();                 /* FUN_00352df4 */
    rt_353d14(0,0);              /* FUN_00353d14 */
}

/* FUN_002106f4 @ 0x002106f4   (est. sk_vspace_trap_106f4)
 * Ghidra: void FUN_002106f4(void)
 * Handler: bookkeeping + an indirect call (extraout_x9) then returns through
 * FUN_0020a084 / FUN_00358fc8. Confidence: low (PAC).
 * Notes: Ghidra artifacts: auVar2 from FUN_00352ba4, (*DAT_00658c00)(). */
void sk_vspace_trap_106f4(void)
{
    rt_358fb4();                 /* FUN_00358fb4 */
    rt_34c704();                 /* FUN_0034c704 */
    rt_349c70((void *)0x160);    /* FUN_00349c70(*(extraout_x16 + 0x160)) */
    sk_nop_02();                 /* FUN_0007c1a4 */
    (*(void (**)())sk_global_hook)();   /* (*DAT_00658c00)() */
    rt_34aee4();                 /* FUN_0034aee4 */
    rt_352188();                 /* FUN_00352188 */
    rt_352ba4((void *)0x170);    /* FUN_00352ba4(*(extraout_x16_00 + 0x170)) */
    ((void (*volatile)())0)(0,0,0);/* (*extraout_x9)() */
    rt_352188();                 /* FUN_00352188 */
    rt_350b60((void *)0x168);    /* FUN_00027754(*(extraout_x16_01 + 0x168)) */
    rt_356ce0();                 /* FUN_00356ce0 */
    rt_34d130();                 /* FUN_0034d130 */
    rt_358cec();                 /* FUN_00358cec */
    sk_vspace_resume(0);         /* FUN_0020a084 */
    rt_358fc8(0,0);              /* FUN_00358fc8 */
}

/* FUN_002107bc @ 0x002107bc   (est. sk_vspace_trap_107bc)
 * Ghidra: void FUN_002107bc(void)
 * Handler (triple FUN_00354330 bookkeeping) then FUN_0020a3b0 / FUN_0035a7d4.
 * Confidence: low (PAC).
 * Notes: Ghidra artifacts: extraout_x8, (*DAT_00658c00)() hook. */
void sk_vspace_trap_107bc(void)
{
    rt_35a7c0();                 /* FUN_0035a7c0 */
    rt_351a68();                 /* FUN_00351a68 */
    rt_354330();                 /* FUN_00354330 */
    rt_3494e8();                 /* FUN_003494e8 */
    sk_nop_02();                 /* FUN_0007c1a4 */
    (*(void (**)())sk_global_hook)();   /* (*DAT_00658c00)() */
    rt_34b0d4();                 /* FUN_0034b0d4 */
    rt_354330();                 /* FUN_00354330 */
    rt_34e924((void *)0x170);    /* FUN_0034e924(*(extraout_x16_00 + 0x170)) */
    ((void (*volatile)())0)();     /* (*extraout_x10)() */
    rt_354330();                 /* FUN_00354330 */
    rt_350b60((void *)0x168);    /* FUN_00027754(*(extraout_x16_01 + 0x168)) */
    rt_356ce0();                 /* FUN_00356ce0 */
    rt_34d758();                 /* FUN_0034d758 */
    sk_vspace_resume2(0);        /* FUN_0020a3b0 */
    rt_3508cc((void *)8);        /* FUN_003508cc(*(extraout_x16 + 8)) */
    ((void (*volatile)())0)();     /* (*extraout_x8)() */
    rt_359f3c();                 /* FUN_00359f3c */
    rt_35a7d4(0);                /* FUN_0035a7d4 */
}

/* FUN_002108a8 @ 0x002108a8   (est. sk_vspace_trap_108a8)
 * Ghidra: undefined8 FUN_002108a8(void)
 * Handler returning a value: bookkeeping (triple FUN_003536d0), an indirect
 * call, then returns through rt_3514e8 with the value. Confidence: low.
 * Notes: Ghidra artifacts: extraout_x8_00, (*DAT_00658c00)() hook. */
unsigned long sk_vspace_trap_108a8(void)
{
    rt_3536d0();                 /* FUN_003536d0 */
    rt_3494e8();                 /* FUN_003494e8 */
    sk_nop_02();                 /* FUN_0007c1a4 */
    (*(void (**)())sk_global_hook)();   /* (*DAT_00658c00)() */
    rt_34b0c4();                 /* FUN_0034b0c4 */
    rt_3536d0();                 /* FUN_003536d0 */
    rt_34c1bc((void *)0x170);    /* FUN_0034c1bc(*(extraout_x16_00 + 0x170)) */
    ((void (*volatile)())0)();     /* (*extraout_x10)() */
    rt_3536d0();                 /* FUN_003536d0 */
    rt_350b60((void *)0x168);    /* FUN_00027754(*(extraout_x16_01 + 0x168)) */
    /* FUN_00027754() */
    rt_3514b8(0);                /* FUN_003514b8 */
    rt_31b62c();                 /* FUN_0031b62c */
    /* FUN_000dbdf4 */
    rt_350810();                 /* FUN_00350810 */
    unsigned long v = ((unsigned long (*volatile)())0)();
    rt_3514e8((void *)8);        /* FUN_003514e8(*(extraout_x16 + 8)) */
    ((void (*volatile)())0)();     /* (*extraout_x8_00)() */
    return v;
}

/* FUN_002109a0 @ 0x002109a0   (est. sk_vspace_trap_109a0)
 * Ghidra: void FUN_002109a0(void)
 * Short teardown handler (FUN_0034ecb8/FUN_003494e8 prelude). Confidence: low.
 * Notes: Ghidra artifacts: extraout_x8, (*DAT_00658c00)() hook. */
void sk_vspace_trap_109a0(void)
{
    rt_34ecb8();                 /* FUN_0034ecb8 */
    rt_3494e8();                 /* FUN_003494e8 */
    sk_nop_02();                 /* FUN_0007c1a4 */
    (*(void (**)())sk_global_hook)();   /* (*DAT_00658c00)() */
    rt_34b460();                 /* FUN_0034b460 */
    rt_351d9c();                 /* FUN_00351d9c */
    rt_34d284((void *)0x170);    /* FUN_0034d284(*(extraout_x16 + 0x170)) */
    ((void (*volatile)())0)();     /* (*extraout_x9)() */
    rt_351d9c();                 /* FUN_00351d9c */
    rt_350b60((void *)0x168);    /* FUN_00027754(*(extraout_x16_00 + 0x168)) */
    /* FUN_00027754() */
    rt_350950(0);                /* FUN_00350950 */
    rt_310da8();                 /* FUN_00310da8 */
    rt_3514ac();                 /* FUN_003514ac */
    rt_3507e0(0);                /* FUN_003507e0 */
    ((void (*volatile)())0)();     /* (*extraout_x8)() */
}

/* FUN_00210a68 @ 0x00210a68   (est. sk_vspace_trap_10a68)
 * Ghidra: void FUN_00210a68(void)
 * Handler: per-CPU + bookkeeping, then returns through FUN_00354804 /
 * FUN_0008e500. Confidence: low (PAC).
 * Notes: Ghidra artifacts: auVar1 [16], (*DAT_00658c00)() hook. */
void sk_vspace_trap_10a68(void)
{
    sk_cpu();                    /* FUN_0008e518 */
    rt_35316c();                 /* FUN_0035316c */
    sk_tcb_get();                /* FUN_0007c0c4 */
    rt_3499b4();                 /* FUN_003499b4 */
    rt_351408();                 /* FUN_00351408 */
    (*(void (**)())sk_global_hook)();   /* (*DAT_00658c00)() */
    rt_34c8f8();                 /* FUN_0034c8f8 */
    rt_3549d8();                 /* FUN_003549d8 */
    rt_350b60((void *)0x168);    /* FUN_00027754(*(extraout_x16 + 0x168)) */
    /* FUN_00027754() */
    rt_351ad4();                 /* FUN_00351ad4 */
    rt_34d014();                 /* FUN_0034d014 */
    sk_lock_acquire(0,0,0,0,0);  /* FUN_00377824 */
    rt_349e10();                 /* FUN_00349e10 */
    sk_nop_02();                 /* FUN_0007c1a4 */
    (*(void (**)())sk_global_hook)();   /* (*DAT_00658c00)() */
    rt_34af20();                 /* FUN_0034af20 */
    /* FUN_000027e8 */
    rt_34d080((void *)0x170);    /* FUN_0034d080(*(extraout_x16_00 + 0x170)) */
    ((void (*volatile)())0)();     /* (*extraout_x9)() */
    rt_3191e8();                 /* FUN_003191e8 */
    rt_34cd2c();                 /* FUN_0034cd2c */
    ((void (*volatile)())0)();     /* (*extraout_x8)() */
    rt_34ee18();                 /* FUN_0034ee18 */
    sk_lock_ref(0);              /* FUN_00377bec */
    rt_359388();                 /* FUN_00359388 */
    rt_354804();                 /* FUN_00354804 */
    sk_cpu_current();            /* FUN_0008e500 */
}

/* FUN_00210ba0 @ 0x00210ba0   (est. sk_vspace_obj_destroy_10ba0)
 * Ghidra: void FUN_00210ba0(void)
 * Wrapper: runs FUN_0034e3e4 then FUN_00210c5c (destroy). Confidence: medium
 * (small forwarder).
 */
void sk_vspace_obj_destroy_10ba0(void)
{
    rt_34e3e4();                 /* FUN_0034e3e4 */
    sk_vspace_obj_destroy_10c5c(0,0,0);  /* FUN_00210c5c */
}

/* FUN_00210ba4 @ 0x00210ba4   (est. sk_vspace_obj_destroy_10ba4)
 * Ghidra: void FUN_00210ba4(void)
 * Mirror of FUN_00210ba0. Confidence: medium.
 */
void sk_vspace_obj_destroy_10ba4(void)
{
    rt_34e3e4();                 /* FUN_0034e3e4 */
    sk_vspace_obj_destroy_10c5c(0,0,0);  /* FUN_00210c5c */
}

/* FUN_00210bbc @ 0x00210bbc   (est. sk_vspace_obj_destroy_10bbc)
 * Ghidra: void FUN_00210bbc(undefined8 param_1)
 * Dispatcher wrapper: forwards param_1 + the FUN_00211220 handler into
 * FUN_00210bd4 (the generic dispatch setup). Confidence: medium.
 */
void sk_vspace_obj_destroy_10bbc(void *a)
{
    sk_vspace_obj_destroy_10bd4(a, (void *)sk_vspace_handler_11220); /* FUN_00210bd4 */
}

/* FUN_00210bd4 @ 0x00210bd4   (est. sk_vspace_obj_destroy_10bd4)
 * Ghidra: void FUN_00210bd4(void)
 * Generic dispatch setup: trap-init, two runtime helpers, then calls the
 * handler pointer (unaff_x19). Confidence: medium.
 * Notes: Ghidra artifacts: (*unaff_x19)() indirect handler call.
 */
void sk_vspace_obj_destroy_10bd4(void *a, void *handler)
{
    (void)a; (void)handler;
    sk_trap_init();              /* FUN_0008409c */
    rt_359290();                 /* FUN_00359290 */
    rt_353528();                 /* FUN_00353528 */
    ((void (*volatile)())0)();     /* (*unaff_x19)() handler */
}

/* FUN_00210c40 @ 0x00210c40   (est. sk_vspace_obj_destroy_10c40)
 * Ghidra: void FUN_00210c40(void)
 * Wrapper: FUN_0034e3cc + FUN_00210c5c. Confidence: medium.
 */
void sk_vspace_obj_destroy_10c40(void)
{
    rt_34e3cc();                 /* FUN_0034e3cc */
    sk_vspace_obj_destroy_10c5c(0,0,0);  /* FUN_00210c5c */
}

/* FUN_00210c44 @ 0x00210c44   (est. sk_vspace_obj_destroy_10c44)
 * Ghidra: void FUN_00210c44(void)
 * Mirror of FUN_00210c40. Confidence: medium.
 */
void sk_vspace_obj_destroy_10c44(void)
{
    rt_34e3cc();                 /* FUN_0034e3cc */
    sk_vspace_obj_destroy_10c5c(0,0,0);  /* FUN_00210c5c */
}

/* FUN_00210c5c @ 0x00210c5c   (est. sk_vspace_obj_destroy_10c5c)
 * Ghidra: void FUN_00210c5c(undefined8 param_1,undefined8 param_2,code *param_3)
 * Core destroy routine: bookkeeping, invokes the destructor callback
 * (param_3), and if the object refcount (unaff_x21) is zero runs the teardown
 * tail and dispatches FUN_00210bbc. Confidence: low (PAC).
 * Notes: Ghidra artifacts: (*param_3)() destructor, extraout_x16_00. */
void sk_vspace_obj_destroy_10c5c(void *a, void *b, void *c)
{
    (void)a; (void)b;
    rt_353cfc();                 /* FUN_00353cfc */
    rt_34cca8();                 /* FUN_0034cca8 */
    rt_3499b4();                 /* FUN_003499b4 */
    rt_351408();                 /* FUN_00351408 */
    (*(void (**)())sk_global_hook)();   /* (*DAT_00658c00)() */
    rt_349c14();                 /* FUN_00349c14 */
    rt_350b60((void *)0x168);    /* FUN_00027754(*(extraout_x16 + 0x168)) */
    rt_351ad4();                 /* FUN_00351ad4 */
    rt_34c20c();                 /* FUN_0034c20c */
    rt_350c68();                 /* FUN_00350c68 */
    sk_lock_acquire(0,0,0,0,0);  /* FUN_00377824 */
    rt_349e10();                 /* FUN_00349e10 */
    sk_nop_02();                 /* FUN_0007c1a4 */
    (*(void (**)())sk_global_hook)();   /* (*DAT_00658c00)() */
    rt_34b2f8();                 /* FUN_0034b2f8 */
    /* FUN_000027e8 */
    rt_34d284((void *)0x170);    /* FUN_0034d284(*(extraout_x16_00 + 0x170)) */
    ((void (*volatile)())0)();     /* (*extraout_x9)() */
    rt_352dd0();                 /* FUN_00352dd0 */
    rt_351444(0,0);              /* FUN_00351444 */
    (*(void (**)())c)();     /* (*param_3)() destructor */
    if (0 == 0) {                /* unaff_x21 == 0 */
        rt_355848();             /* FUN_00355848 */
        rt_34f344();             /* FUN_0034f344 */
        sk_lock_ref(0);          /* FUN_00377bec */
        rt_34c55c();             /* FUN_0034c55c */
        rt_31baa0();             /* FUN_0031baa0 */
        rt_3519a8();             /* FUN_003519a8 */
        sk_vspace_obj_destroy_10bbc(0);  /* FUN_00210bbc */
    }
    rt_354b5c();                 /* FUN_00354b5c */
    rt_353d14(0,0);              /* FUN_00353d14 */
}

/* FUN_00210dac @ 0x00210dac   (est. sk_vspace_trap_10dac)
 * Ghidra: void FUN_00210dac(void)
 * Restore-tail handler: same skeleton as FUN_0020e778/10ef0 but dispatches
 * FUN_00210bbc instead of FUN_0020e5c0. Confidence: low (PAC).
 * Notes: Ghidra artifacts: extraout_x16_00, (*DAT_00658c00)() hook. */
void sk_vspace_trap_10dac(void)
{
    sk_cpu();                    /* FUN_0008e518 */
    rt_352914();                 /* FUN_00352914 */
    sk_tcb_get();                /* FUN_0007c0c4 */
    rt_34b7e4();                 /* FUN_0034b7e4 */
    rt_351408();                 /* FUN_00351408 */
    (*(void (**)())sk_global_hook)();   /* (*DAT_00658c00)() */
    rt_34b014();                 /* FUN_0034b014 */
    rt_350b60((void *)0x168);    /* FUN_00027754(*(extraout_x16 + 0x168)) */
    rt_351bec(0);                /* FUN_00351bec */
    rt_34c20c();                 /* FUN_0034c20c */
    rt_350998();                 /* FUN_00350998 */
    sk_lock_acquire(0,0,0,0,0);  /* FUN_00377824 */
    rt_349e10();                 /* FUN_00349e10 */
    sk_nop_02();                 /* FUN_0007c1a4 */
    (*(void (**)())sk_global_hook)();   /* (*DAT_00658c00)() */
    rt_34af20();                 /* FUN_0034af20 */
    rt_355848();                 /* FUN_00355848 */
    rt_3507d4();                 /* FUN_003507d4 */
    sk_lock_ref(0);              /* FUN_00377bec */
    rt_34c55c();                 /* FUN_0034c55c */
    rt_31baa0();                 /* FUN_0031baa0 */
    /* FUN_000027e8 */
    rt_3527cc((void *)0x170);    /* FUN_003527cc(*(extraout_x16_00 + 0x170)) */
    ((void (*volatile)())0)();     /* (*extraout_x9)() */
    /* FUN_00100efc */
    rt_35a328();                 /* FUN_0035a328 */
    ((void (*volatile)())0)();     /* (*unaff_x19)() */
    sk_vspace_obj_destroy_10bbc(0);  /* FUN_00210bbc */
    sk_cpu_current();            /* FUN_0008e500 */
}

/* FUN_00210ef0 @ 0x00210ef0   (est. sk_vspace_trap_10ef0)
 * Ghidra: void FUN_00210ef0(void)
 * Restore-tail handler (variant of FUN_0020e778). Confidence: low (PAC).
 * Notes: Ghidra artifacts: auVar2, extraout_x16_01, (*DAT_00658c00)() hook. */
void sk_vspace_trap_10ef0(void)
{
    sk_cpu();                    /* FUN_0008e518 */
    rt_352914();                 /* FUN_00352914 */
    sk_tcb_get();                /* FUN_0007c0c4 */
    rt_34b7e4();                 /* FUN_0034b7e4 */
    rt_351408();                 /* FUN_00351408 */
    (*(void (**)())sk_global_hook)();   /* (*DAT_00658c00)() */
    rt_34b014();                 /* FUN_0034b014 */
    rt_351bec((void *)0x168);    /* FUN_00351bec(*(extraout_x16_00 + 0x168)) */
    rt_350bd8(0);                /* FUN_00350bd8 */
    rt_34c20c();                 /* FUN_0034c20c */
    sk_lock_acquire(0,0,0,0,0);  /* FUN_00377824 */
    rt_349e10();                 /* FUN_00349e10 */
    sk_nop_02();                 /* FUN_0007c1a4 */
    (*(void (**)())sk_global_hook)();   /* (*DAT_00658c00)() */
    rt_34af20();                 /* FUN_0034af20 */
    rt_355848();                 /* FUN_00355848 */
    rt_3507d4();                 /* FUN_003507d4 */
    sk_lock_ref(0);              /* FUN_00377bec */
    rt_34c55c();                 /* FUN_0034c55c */
    rt_31baa0();                 /* FUN_0031baa0 */
    /* FUN_000027e8 */
    rt_3527cc((void *)0x170);    /* FUN_003527cc(*(extraout_x16_01 + 0x170)) */
    ((void (*volatile)())0)();     /* (*extraout_x9)() */
    /* FUN_00100efc */
    rt_35a328();                 /* FUN_0035a328 */
    ((void (*volatile)())0)();     /* (*unaff_x19)() */
    sk_vspace_obj_destroy_10bbc(0);  /* FUN_00210bbc */
    sk_cpu_current();            /* FUN_0008e500 */
}

/* FUN_0021101c @ 0x0021101c   (est. sk_vspace_dispatch_tail2)
 * Ghidra: void FUN_0021101c(void)
 * Jumptable dispatcher (unrecoverable at 0x00211070). Confidence: low.
 * Notes: Ghidra: "Could not recover jumptable"; indirect through +0x160/-8+8.
 */
void sk_vspace_dispatch_tail2(void)
{
    sk_tcb_get();                /* FUN_0007c0c4 */
    (**(void (**)())(*(void **)(*(void **)((char *)0 + 0x160) - 8) + 8))((void *)0);
}

/* FUN_002110f8 @ 0x002110f8   (est. sk_vspace_obj_alloc_110f8)
 * Ghidra: void FUN_002110f8(long param_1,undefined8 param_2,undefined8 param_3)
 * Object allocator: stores args into the object header (x20+0x30/0x38/0x40),
 * allocates two 0x18-byte nodes (tag 7), copies a field, and links them into
 * the object (x20+0x10/0x20) with 0x66c280 tags. Confidence: medium.
 * Notes: Ghidra artifacts: FUN_0036a940(uVar1,0x18,7) alloc, &DAT_00657630,
 *   &DAT_004f2110, 0x66c280 tags. */
void sk_vspace_obj_alloc_110f8(void *a, void *b, void *c)
{
    (void)b; (void)c;
    void *n1 = sk_alloc_small(0x18, 7);   /* FUN_0036a940 */
    *(void **)((char *)n1 + 0x10) = 0;
    void *n2 = sk_alloc_small(0x18, 7);   /* FUN_0036a940 */
    *(void **)((char *)n2 + 0x10) = *(void **)((char *)a + 0x10);
    /* writes to object header (unaff_x20 + 0x10..0x28): */
    ((void (*volatile)())0)();     /* object header writes */
    (void)n1; (void)n2;
}

/* FUN_00211188 @ 0x00211188   (est. sk_vspace_obj_alloc_11188)
 * Ghidra: void FUN_00211188(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)
 * Object allocator (4-arg variant of FUN_002110f8): stores args, allocates
 * two nodes, links them. Confidence: medium.
 * Notes: Ghidra artifacts: FUN_0036a940, 0x66c280 tags. */
void sk_vspace_obj_alloc_11188(void *a, void *b, void *c, void *d)
{
    (void)a; (void)b; (void)c; (void)d;
    void *n1 = sk_alloc_small(0x18, 7);   /* FUN_0036a940 */
    *(void **)((char *)n1 + 0x10) = a;
    void *n2 = sk_alloc_small(0x18, 7);   /* FUN_0036a940 */
    *(void **)((char *)n2 + 0x10) = b;
    ((void (*volatile)())0)();     /* object header writes (x20+0x10..0x28) */
    (void)n1; (void)n2;
}

/* FUN_00211220 @ 0x00211220   (est. sk_vspace_handler_11220)
 * Ghidra: void FUN_00211220(void)
 * Handler for the FUN_00210bbc dispatch target; near-copy of FUN_0020eabc
 * (per-CPU + bookkeeping + result-block write). Confidence: low (PAC).
 * Notes: Ghidra artifacts: extraout_x16_01, (*DAT_00658c00)() hook,
 *   writes x19+0x10..0x28. */
void sk_vspace_handler_11220(void *unused)
{
    (void)unused;
    sk_cpu();                    /* FUN_0008e518 */
    rt_353860();                 /* FUN_00353860 */
    rt_350b60((void *)0x168);    /* FUN_00027754(*(extraout_x16 + 0x168)) */
    rt_3514b8(0);                /* FUN_003514b8 */
    rt_356194();                 /* FUN_00356194 */
    rt_34de64();                 /* FUN_0034de64 */
    rt_34d3f4();                 /* FUN_0034d3f4 */
    sk_lock_acquire(0,0,0,0,0);  /* FUN_00377824 */
    rt_34a450();                 /* FUN_0034a450 */
    sk_nop_02();                 /* FUN_0007c1a4 */
    (*(void (**)())sk_global_hook)();   /* (*DAT_00658c00)() */
    rt_34b0c4();                 /* FUN_0034b0c4 */
    sk_nop_04();                 /* FUN_0007c0b8 */
    rt_3537c4((void *)0x170);    /* FUN_003537c4(*(extraout_x16_00 + 0x170)) */
    rt_3511d8(0);                /* FUN_003511d8 */
    ((void (*volatile)())0)();     /* (*extraout_x10)() */
    rt_3504c4();                 /* FUN_003504c4 */
    rt_353c3c();                 /* FUN_00353c3c */
    sk_lock_ref(0);              /* FUN_00377bec */
    rt_34dee4();                 /* FUN_0034dee4 */
    rt_31b9c0();                 /* FUN_0031b9c0 */
    rt_357b48();                 /* FUN_00357b48 */
    /* FUN_000277b8 */
    rt_34c930();                 /* FUN_0034c930 */
    ((void (*volatile)())0)();     /* (*extraout_x9)() */
    rt_356218();                 /* FUN_00356218 */
    sk_vspace_dispatch_c7fc(0);  /* FUN_0020c7fc */
    rt_35a42c();                 /* FUN_0035a42c */
    rt_351094();                 /* FUN_00310924 */
    rt_34c930();                 /* FUN_0034c930 */
    ((void (*volatile)())0)();     /* (*extraout_x9_00)() */
    rt_350b90((void *)8);        /* FUN_000b4390(*(extraout_x16_01 + 8)) */
    ((void (*volatile)())0)();     /* (*extraout_x8_00)() */
    rt_356218();                 /* FUN_00356218 */
    rt_348b1c();                 /* FUN_00348b1c */
    rt_353100();                 /* FUN_00353100 */
    sk_cpu_current();            /* FUN_0008e500 */
}

/* FUN_00211358 @ 0x00211358   (est. sk_vspace_dispatch_11358)
 * Ghidra: void FUN_00211358(void)
 * Dispatch handler (mirror of FUN_0020ebf0 with 0x168/0x170 fields).
 * Confidence: low (PAC).
 * Notes: Ghidra artifacts: in_ZR, (*DAT_00658c00)() hook, noreturn
 *   FUN_001afa84. */
void sk_vspace_dispatch_11358(void)
{
    sk_cpu();                    /* FUN_0008e518 */
    rt_358114();                 /* FUN_00358114 */
    rt_34c998();                 /* FUN_0034c998 */
    rt_350b60((void *)0x168);    /* FUN_00027754(*(extraout_x16 + 0x168)) */
    rt_350950(0);                /* FUN_00350950 */
    rt_35147c();                 /* FUN_0035147c */
    rt_34d598();                 /* FUN_0034d598 */
    rt_34c444(0xff);             /* FUN_0034c444(0xff) */
    sk_lock_acquire(0,0,0,0,0);  /* FUN_00377824 */
    rt_34e67c();                 /* FUN_0034e67c */
    rt_310d68();                 /* FUN_00310d68 */
    /* FUN_000a6f88 */
    sk_nop_02();                 /* FUN_0007c1a4 */
    (*(void (**)())sk_global_hook)();   /* (*DAT_00658c00)() */
    rt_34bdfc();                 /* FUN_0034bdfc */
    rt_31b9d8(0);                /* FUN_0031b9d8 */
    rt_350210();                 /* FUN_00350210 */
    sk_lock_ref(0);              /* FUN_00377bec */
    rt_354d74(0,0);              /* FUN_00354d74 */
    rt_351aec();                 /* FUN_00351aec */
    ((void (*volatile)())0)();     /* (*pcVar2)() */
    if (0) {                     /* !(bool)in_ZR */
        rt_34f384();             /* FUN_0034f384 */
        (**(void (**)())(0 + 0x20))((void *)0);   /* vtable +0x20 */
        sk_cpu_current();        /* FUN_0008e500 */
        return;
    }
    rt_352e18(0,0);              /* FUN_00352e18 */
    ((void (*volatile)())0)();     /* (*extraout_x8_00)() */
    rt_34abc4();                 /* FUN_0034abc4 */
    rt_3593c0();                 /* FUN_003593c0 */
    rt_349c58();                 /* FUN_00349c58 */
    sk_panic_no_return();        /* FUN_001afa84 (noreturn) */
}

/* FUN_0021166c @ 0x0021166c   (est. sk_vspace_trap_1166c)
 * Ghidra: void FUN_0021166c(void)
 * Large handler (mirror of FUN_0020eefc) with recursive dispatch to
 * FUN_00211358. Confidence: low (PAC).
 * Notes: Ghidra artifacts: Swift existentials, FUN_00211358 recursion,
 *   noreturn FUN_001afe4c. */
void sk_vspace_trap_1166c(void)
{
    sk_cpu();                    /* FUN_0008e518 */
    rt_3586cc();                 /* FUN_003586cc */
    rt_34c998();                 /* FUN_0034c998 */
    /* FUN_00027754() */
    rt_35125c();                 /* FUN_0035125c */
    rt_35147c();                 /* FUN_0035147c */
    rt_3525cc();                 /* FUN_003525cc */
    rt_34ba38();                 /* FUN_0034ba38 */
    sk_lock_acquire(0,0,0,0,0);  /* FUN_00377824 */
    rt_34ab20();                 /* FUN_0034ab20 */
    sk_nop_02();                 /* FUN_0007c1a4 */
    (*(void (**)())sk_global_hook)();   /* (*DAT_00658c00)() */
    rt_34aab0();                 /* FUN_0034aab0 */
    rt_352f54();                 /* FUN_00352f54 */
    rt_34ba38();                 /* FUN_0034ba38 */
    sk_lock_acquire(0,0,0,0,0);  /* FUN_00377824 */
    rt_34a654();                 /* FUN_0034a654 */
    rt_348d7c();                 /* FUN_00348d7c */
    (*(void (**)())sk_global_hook)((void *)0x40);   /* (*DAT_00658c00)(*(x8+0x40)) */
    rt_348a18();                 /* FUN_00348a18 */
    (*(void (**)())sk_global_hook)();   /* (*DAT_00658c00)() */
    rt_350464();                 /* FUN_00350464 */
    rt_34961c();                 /* FUN_00349618 */
    (*(void (**)())sk_global_hook)((void *)0x40);   /* (*DAT_00658c00)(*(x8_00+0x40)) */
    rt_348a34();                 /* FUN_00348a34 */
    (*(void (**)())sk_global_hook)();   /* (*DAT_00658c00)() */
    rt_34b8bc();                 /* FUN_0034b8bc */
    rt_34ac78();                 /* FUN_0034ac78 */
    sk_lock_ref(0);              /* FUN_00377bec */
    rt_350500();                 /* FUN_00350500 */
    rt_310e08(0,0,0);            /* FUN_00310e08 */
    rt_348e00();                 /* FUN_00348e00 */
    sk_nop_02();                 /* FUN_0007c1a4 */
    (*(void (**)())sk_global_hook)();   /* (*DAT_00658c00)() */
    rt_350428();                 /* FUN_00350428 */
    rt_34911c();                 /* FUN_0034911c */
    sk_nop_02();                 /* FUN_0007c1a4 */
    (*(void (**)())sk_global_hook)();   /* (*DAT_00658c00)() */
    rt_355c84();                 /* FUN_00355c84 */
    /* FUN_000027e8 */
    rt_3558d8((void *)0x170);    /* FUN_003558d8(*(extraout_x16_01 + 0x170)) */
    ((void (*volatile)())0)();     /* (*extraout_x10)() */
    rt_351c1c(0,0,0);            /* FUN_00351c1c */
    sk_vspace_dispatch_11358();  /* FUN_00211358 */
    rt_35a420();                 /* FUN_0035a420 */
    rt_351c1c(0,0,0);            /* FUN_00351c1c */
    sk_vspace_dispatch_11358();  /* FUN_00211358 */
    rt_310e20(0);                /* FUN_00310e20 */
    rt_350104();                 /* FUN_00350104 */
    rt_3516b4();                 /* FUN_003516b4 */
    if (((unsigned long (*volatile)())0)() & 1) {
        rt_35238c();             /* FUN_0035238c */
        rt_354594();             /* FUN_00354594 */
        rt_350798(0,0,0);        /* FUN_00350798 */
        rt_31baa0();             /* FUN_0031baa0 */
        rt_356670();             /* FUN_00356670 */
        rt_350b48();             /* FUN_00350b48 */
        ((void (*volatile)())0)(); /* (*pcVar4)() */
        rt_3516f0(0);            /* FUN_003516f0 */
        ((void (*volatile)())0)(); /* (*pcVar4)() */
        rt_351d0c();             /* FUN_00351d0c */
        rt_3507d4();             /* FUN_003507d4 */
        ((void (*volatile)())0)(); /* (*extraout_x9)() */
        rt_351360();             /* FUN_00351360 */
        ((void (*volatile)())0)(); /* (*pcVar4)() */
        rt_35a058();             /* FUN_0035a058 */
        ((void (*volatile)())0)(); /* (*unaff_x28)() */
        rt_3507d4((void *)0x20); /* FUN_003507d4(*(extraout_x16+0x20)) */
        ((void (*volatile)())0)(); /* (*extraout_x8_02)() */
        rt_357424();             /* FUN_00357424 */
        ((void (*volatile)())0)(); /* (*pcVar4)() */
        /* FUN_000e72b0 */
        ((void (*volatile)())0)(); /* (*unaff_x28)() */
        rt_351bb8();             /* FUN_00351bb8 */
        rt_35242c();             /* FUN_0035242c */
        rt_351190();             /* FUN_00351190 */
        ((void (*volatile)())0)(); /* (*extraout_x9_00)() */
        rt_353be8();             /* FUN_00353be8 */
        rt_3507bc();             /* FUN_003507bc */
        ((void (*volatile)())0)(); /* (*extraout_x8_03)() */
        rt_354d38();             /* FUN_00354d38 */
        sk_nop_03();             /* FUN_0007c1c4 */
        ((void (*volatile)())0)(); /* (*extraout_x8_04)() */
        sk_vspace_obj_destroy_10bbc(0);  /* FUN_00210bbc */
        sk_cpu_current();        /* FUN_0008e500 */
        return;
    }
    rt_34b348();                 /* FUN_0034b348 */
    rt_35a4d4();                 /* FUN_0035a4d4 */
    rt_347ef4();                 /* FUN_00347ef4 */
    sk_panic_no_return2();       /* FUN_001afe4c (noreturn) */
}

/* FUN_00211ba8 @ 0x00211ba8   (est. sk_vspace_trap_11ba8)
 * Ghidra: void FUN_00211ba8(undefined8 param_1,undefined8 param_2,undefined8 param_3)
 * Two-phase handler (mirror of FUN_0020f430 with 0x170/0x168 fields, recusing
 * into FUN_00211358). Confidence: low (PAC).
 * Notes: Ghidra artifacts: auVar3/auVar4, extraout_x16_02, (*DAT_00658c00)(). */
void sk_vspace_trap_11ba8(void *a, void *b, void *c)
{
    (void)a; (void)b; (void)c;
    rt_34c20c();                 /* FUN_00084220 -> FUN_0034c20c */
    sk_tcb_get();                /* FUN_0007c0c4 */
    rt_3499b4();                 /* FUN_003499b4 */
    rt_351408();                 /* FUN_00351408 */
    (*(void (**)())sk_global_hook)();   /* (*DAT_00658c00)() */
    rt_349c14();                 /* FUN_00349c14 */
    rt_350b60((void *)0x168);    /* FUN_00027754(*(extraout_x16 + 0x168)) */
    rt_3514b8(0);                /* FUN_003514b8 */
    rt_3521d4();                 /* FUN_003521d4 */
    rt_350768(0xff);             /* FUN_00350768(0xff) */
    sk_lock_acquire(0,0,0,0,0);  /* FUN_00377824 */
    rt_350524();                 /* FUN_00350524 */
    rt_352ea8();                 /* FUN_00352ea8 */
    sk_lock_ref(0);              /* FUN_00377bec */
    rt_34dee4();                 /* FUN_0034dee4 */
    rt_31b9c0();                 /* FUN_0031b9c0 */
    rt_356b8c();                 /* FUN_00356b8c */
    if (rt_362acc() != 0) {      /* FUN_00362acc */
        sk_nop_05();             /* FUN_0007c178 */
        rt_34a868((void *)0x170);/* FUN_0034a868(*(extraout_x16_00 + 0x170)) */
        ((void (*volatile)())0)(); /* (*extraout_x10)() */
        rt_3595c0();             /* FUN_003595c0 */
        /* FUN_00027818 */
        rt_350114();             /* FUN_00350114 */
        ((void (*volatile)())0)(); /* (*extraout_x8)() */
        rt_34eb84();             /* FUN_0034eb84 */
        ((void (*volatile)())0)(); /* (*extraout_x8_00)() */
        sk_frame_leave();        /* FUN_00084234 */
        return;
    }
    rt_3498f4();                 /* FUN_003498f4 */
    rt_349190();                 /* FUN_00349190 */
    sk_cpu();                    /* FUN_0008e518 */
    rt_34a674();                 /* FUN_0034a674 */
    rt_3499b4();                 /* FUN_003499b4 */
    rt_351408();                 /* FUN_00351408 */
    (*(void (**)())sk_global_hook)();   /* (*DAT_00658c00)() */
    rt_34c8f8();                 /* FUN_0034c8f8 */
    rt_3549d8();                 /* FUN_003549d8 */
    /* FUN_00027754() */
    rt_351bec(0);                /* FUN_00351bec */
    rt_34c354();                 /* FUN_0034c354 */
    rt_3508c0();                 /* FUN_003508c0 */
    sk_lock_acquire(0,0,0,0,0);  /* FUN_00377824 */
    rt_348cd0();                 /* FUN_00348cd0 */
    (*(void (**)())sk_global_hook)((void *)0x40);   /* (*DAT_00658c00)(*(x8_01+0x40)) */
    rt_348a80();                 /* FUN_00348a80 */
    (*(void (**)())sk_global_hook)();   /* (*DAT_00658c00)() */
    rt_34c2d8();                 /* FUN_0034c2d8 */
    rt_356bc8();                 /* FUN_00356bc8 */
    rt_34f5a4();                 /* FUN_0034f5a4 */
    sk_lock_ref(0);              /* FUN_00377bec */
    rt_34c55c();                 /* FUN_0034c55c */
    rt_31b9c0();                 /* FUN_0031b9c0 */
    /* FUN_000027e8 */
    rt_34ad8c((void *)0x170);    /* FUN_0034ad8c(*(extraout_x16_02 + 0x170)) */
    ((void (*volatile)())0)();     /* (*extraout_x10_00)() */
    rt_353bdc();                 /* FUN_00353bdc */
    rt_351c1c(0,0,0);            /* FUN_00351c1c */
    sk_vspace_dispatch_11358();  /* FUN_00211358 */
    rt_356c24();                 /* FUN_00356c24 */
    rt_31b1c4();                 /* FUN_0031b1c4 */
    rt_351058();                 /* FUN_00351058 */
    rt_351444(0, c);             /* FUN_00351444 */
    ((void (*volatile)())0)();     /* (*extraout_x9)() */
    rt_351354((void *)8);        /* FUN_00351354(*(extraout_x16_01 + 8)) */
    ((void (*volatile)())0)();     /* (*extraout_x8_02)() */
    rt_34eb94();                 /* FUN_0034eb94 */
    ((void (*volatile)())0)();     /* (*extraout_x8_03)() */
    rt_348b1c();                 /* FUN_00348b1c */
    rt_356090();                 /* FUN_00356090 */
    sk_cpu_current();            /* FUN_0008e500 */
}

/* FUN_00211e7c @ 0x00211e7c   (est. sk_vspace_trap_11e7c)
 * Ghidra: void FUN_00211e7c(void)
 * Handler (mirror of FUN_0020f6fc) with recursive dispatch to FUN_00211358.
 * Confidence: low (PAC).
 * Notes: Ghidra artifacts: auVar4/auVar5, extraout_x16_03, (*DAT_00658c00)(). */
void sk_vspace_trap_11e7c(void)
{
    rt_34c20c();                 /* FUN_0008e518 -> FUN_0034c20c */
    rt_34c998();                 /* FUN_0034c998 */
    rt_350b60((void *)0x168);    /* FUN_00027754(*(extraout_x16 + 0x168)) */
    rt_350bd8(0);                /* FUN_00350bd8 */
    rt_35147c();                 /* FUN_0035147c */
    rt_349748();                 /* FUN_00349748 */
    sk_lock_acquire(0,0,0,0,0);  /* FUN_00377824 */
    rt_348d7c();                 /* FUN_00348d7c */
    (*(void (**)())sk_global_hook)((void *)0x40);   /* (*DAT_00658c00)(*(x8+0x40)) */
    rt_3490d0();                 /* FUN_003490d0 */
    (*(void (**)())sk_global_hook)();   /* (*DAT_00658c00)() */
    rt_34c2c8();                 /* FUN_0034c2c8 */
    rt_349734();                 /* FUN_00349734 */
    sk_nop_02();                 /* FUN_0007c1a4 */
    (*(void (**)())sk_global_hook)();   /* (*DAT_00658c00)() */
    rt_34aee4();                 /* FUN_0034aee4 */
    rt_350720();                 /* FUN_00350720 */
    rt_310d68();                 /* FUN_00310d68 */
    /* FUN_000a6f88 */
    sk_nop_02();                 /* FUN_0007c1a4 */
    (*(void (**)())sk_global_hook)();   /* (*DAT_00658c00)() */
    rt_34b0c4();                 /* FUN_0034b0c4 */
    /* FUN_000027e8 */
    rt_34c58c((void *)0x170);    /* FUN_0034c58c(*(extraout_x16_03 + 0x170)) */
    rt_356ab8();                 /* FUN_00356ab8 */
    ((void (*volatile)())0)();     /* (*extraout_x10)() */
    rt_35a128();                 /* FUN_0035a128 */
    rt_34fc34(0,0);              /* FUN_0034fc34 */
    sk_vspace_dispatch_11358();  /* FUN_00211358 */
    rt_34fc34(0,0);              /* FUN_0034fc34 */
    sk_vspace_dispatch_11358();  /* FUN_00211358 */
    rt_31bab8(0);                /* FUN_0031bab8 */
    rt_350c50();                 /* FUN_00350c50 */
    ((void (*volatile)())0)();     /* (*extraout_x9)() */
    /* FUN_0009e234 */
    ((void (*volatile)())0)();     /* (*pcVar2)() */
    rt_3509e0();                 /* FUN_003509e0 */
    ((void (*volatile)())0)();     /* (*pcVar2)() */
    rt_3507d4((void *)8);        /* FUN_003507d4(*(extraout_x16_02 + 8)) */
    ((void (*volatile)())0)();     /* (*extraout_x8_00)() */
    rt_356f6c();                 /* FUN_00356f6c */
    rt_3536ac();                 /* FUN_003536ac */
    rt_35a298(0);                /* FUN_0035a298(FUN_0031bae8) */
    /* FUN_001d88fc */
    rt_35407c();                 /* FUN_0035407c */
    rt_3514e8(0);                /* FUN_003514e8 */
    ((void (*volatile)())0)();     /* (*extraout_x8_01)() */
    sk_cpu_current();            /* FUN_0008e500 */
}

/* FUN_002120e4 @ 0x002120e4   (est. sk_vspace_obj_alloc_120e4)
 * Ghidra: void FUN_002120e4(undefined8 *param_1, undefined8 param_2, undefined8 param_3, undefined8 param_4)
 * Small object allocator (mirror of FUN_0020f970). Confidence: medium.
 * Notes: Ghidra artifacts: &DAT_0060e208/&DAT_0060e230/&LAB_0060e218, 0x66c280. */
void sk_vspace_obj_alloc_120e4(void **out, void *b, void *c, void *d)
{
    (void)b; (void)c; (void)d;
    rt_34c8f8();                 /* FUN_00027754 (param_4) */
    sk_lock_acquire(0,0,0,0,0);  /* FUN_00377824 */
    rt_350500();                 /* FUN_00350500 */
    sk_lock_ref(0);              /* FUN_00377bec */
    rt_31b9c0(0,0,0);            /* FUN_0031b9c0 */
    (*(void (**)())sk_global_hook)((void *)0x40);   /* (*DAT_00658c00)(vtable+0x40 & ~0xf) */
    rt_350c8c(0);                /* FUN_00350c8c */
    sk_vspace_dispatch_c7fc(0);             /* FUN_0020c7fc */
    out[0] = 0;
    out[1] = (void *)0x66c280;
}

/* FUN_00212230 @ 0x00212230   (est. sk_vspace_trap_12230)
 * Ghidra: void FUN_00212230(void)
 * Three-phase handler (mirror of FUN_0020fab4 with recursive dispatch to
 * FUN_00211358). Confidence: low (PAC).
 * Notes: Ghidra artifacts: auVar8, in_stack_*, Swift existentials, noreturn. */
void sk_vspace_trap_12230(void)
{
    sk_cpu();                    /* FUN_0008e518 */
    sk_tcb_get();                /* FUN_0007c0c4 */
    rt_3499b4();                 /* FUN_003499b4 */
    rt_351408();                 /* FUN_00351408 */
    (*(void (**)())sk_global_hook)();   /* (*DAT_00658c00)() */
    rt_34c8f8();                 /* FUN_0034c8f8 */
    rt_3549d8();                 /* FUN_003549d8 */
    rt_350b60((void *)0x168);    /* FUN_00027754(*(extraout_x16 + 0x168)) */
    rt_352894(0);                /* FUN_00352894 */
    rt_34cd7c();                 /* FUN_0034cd7c */
    rt_3508d8();                 /* FUN_003508d8 */
    sk_lock_acquire(0,0,0,0,0);  /* FUN_00377824 */
    rt_357944();                 /* FUN_00357944 */
    rt_34f344();                 /* FUN_0034f344 */
    sk_lock_ref(0);              /* FUN_00377bec */
    rt_34c55c();                 /* FUN_0034c55c */
    rt_31b9c0();                 /* FUN_0031b9c0 */
    if (rt_362acc() != 0) {      /* FUN_00362acc */
        sk_nop_05();             /* FUN_0007c178 */
        rt_34ad8c((void *)0x170);/* FUN_0034ad8c(*(extraout_x16_00 + 0x170)) */
        ((void (*volatile)())0)(); /* (*extraout_x10)() */
        rt_35a140();             /* FUN_0035a140 */
        rt_34f564(0);            /* FUN_0034f564 */
        /* FUN_001d30f8 */
        rt_34eb94();             /* FUN_0034eb94 */
        ((void (*volatile)())0)(); /* (*extraout_x8)() */
        sk_cpu_current();        /* FUN_0008e500 */
        return;
    }
    rt_3498f4();                 /* FUN_003498f4 */
    rt_349190();                 /* FUN_00349190 */
    sk_cpu();                    /* FUN_0008e518 */
    rt_34c998();                 /* FUN_0034c998 */
    rt_350b60((void *)0x168);    /* FUN_00027754(*(extraout_x16_02 + 0x168)) */
    rt_35125c(0);                /* FUN_0035125c */
    rt_35147c();                 /* FUN_0035147c */
    rt_34b164();                 /* FUN_0034b164 */
    rt_34f564();                 /* FUN_0034f564 */
    sk_lock_acquire(0,0,0,0,0);  /* FUN_00377824 */
    rt_348d7c();                 /* FUN_00348d7c */
    sk_nop_02();                 /* FUN_0007c1a4 */
    (*(void (**)())sk_global_hook)();   /* (*DAT_00658c00)() */
    rt_34af20();                 /* FUN_0034af20 */
    rt_3494e8();                 /* FUN_003494e8 */
    sk_nop_02();                 /* FUN_0007c1a4 */
    (*(void (**)())sk_global_hook)();   /* (*DAT_00658c00)() */
    rt_34cff4();                 /* FUN_0034cff4 */
    rt_350c8c(0);                /* FUN_00350c8c */
    sk_lock_ref(0);              /* FUN_00377bec */
    rt_34e414();                 /* FUN_0034e414 */
    rt_31b9c0();                 /* FUN_0031b9c0 */
    rt_357ac0();                 /* FUN_00357ac0 */
    if (rt_362acc() != 0) {      /* FUN_00362acc */
        sk_nop_05();             /* FUN_0007c178 */
        rt_350b60((void *)0x170);/* FUN_00350b60(*(extraout_x16_04 + 0x170)) */
        rt_353fa0();             /* FUN_00353fa0 */
        ((void (*volatile)())0)(); /* (*extraout_x10_00)() */
        rt_353bdc();             /* FUN_00353bdc */
        rt_351c1c(0,0);          /* FUN_00351c1c */
        sk_vspace_dispatch_11358();  /* FUN_00211358 */
        rt_3513c0(0,0);          /* FUN_003513c0 */
        /* FUN_001d31b0 */
        rt_3500c0();             /* FUN_003500c0 */
        ((void (*volatile)())0)(); /* (*extraout_x8_00)() */
        /* FUN_00084180 */
        ((void (*volatile)())0)(); /* (*extraout_x8_01)() */
        rt_352988();             /* FUN_00352980 */
        sk_cpu_current();        /* FUN_0008e500 */
        return;
    }
    rt_3498f4();                 /* FUN_003498f4 */
    rt_349190();                 /* FUN_00349190 */
    sk_cpu();                    /* FUN_0008e518 */
    rt_3586cc();                 /* FUN_003586cc */
    rt_34c998();                 /* FUN_0034c998 */
    rt_350bd8((void *)0x160);    /* FUN_00350bd8(*(extraout_x16_05 + 0x160)) */
    rt_35147c();                 /* FUN_0035147c */
    rt_349748();                 /* FUN_00349748 */
    sk_lock_acquire(0,0,0,0,0);  /* FUN_00377824 */
    rt_348d4c();                 /* FUN_00348d4c */
    (*(void (**)())sk_global_hook)((void *)0x40);   /* (*DAT_00658c00)(*(x8_02+0x40)) */
    rt_348a34();                 /* FUN_00348a34 */
    (*(void (**)())sk_global_hook)();   /* (*DAT_00658c00)() */
    rt_34b758();                 /* FUN_0034b758 */
    rt_3494e8();                 /* FUN_003494e8 */
    sk_nop_02();                 /* FUN_0007c1a4 */
    (*(void (**)())sk_global_hook)();   /* (*DAT_00658c00)() */
    rt_34aee4();                 /* FUN_0034aee4 */
    /* FUN_000027e8 */
    rt_34ab9c((void *)0x170);    /* FUN_0034ab9c(*(extraout_x16_09 + 0x170)) */
    ((void (*volatile)())0)();     /* (*extraout_x10_01)() */
    rt_351c1c(0,0,0);            /* FUN_00351c1c(Swift existential) */
    sk_vspace_dispatch_11358();  /* FUN_00211358 */
    rt_35a420();                 /* FUN_0035a420 */
    rt_351c1c(0,0,0);            /* FUN_00351c1c */
    sk_vspace_dispatch_11358();  /* FUN_00211358 */
    rt_31b28c(0);                /* FUN_0031b28c */
    rt_3505d0();                 /* FUN_003505d0 */
    rt_350974();                 /* FUN_00350974 */
    ((void (*volatile)())0)();     /* (*extraout_x8_03)() */
    rt_350c38();                 /* FUN_00350c38 */
    ((void (*volatile)())0)();     /* (*pcVar6)() */
    rt_350470();                 /* FUN_00350470 */
    ((void (*volatile)())0)();     /* (*pcVar6)() */
    rt_3505e8((void *)8);        /* FUN_003505e8(*(extraout_x16_08 + 8)) */
    ((void (*volatile)())0)();     /* (*extraout_x8_04)() */
    rt_3548b8();                 /* FUN_003548b8 */
    sk_cpu_current();            /* FUN_0008e500 */
}

/* FUN_002126c8 @ 0x002126c8   (est. sk_vspace_trap_126c8)
 * Ghidra: void FUN_002126c8(void)
 * Short teardown handler (0x170/0x168 variant). Confidence: low (PAC).
 * Notes: Ghidra artifacts: extraout_x8_00, (*DAT_00658c00)() hook. */
void sk_vspace_trap_126c8(void)
{
    rt_34ecb8();                 /* FUN_0034ecb8 */
    rt_3494e8();                 /* FUN_003494e8 */
    sk_nop_02();                 /* FUN_0007c1a4 */
    (*(void (**)())sk_global_hook)();   /* (*DAT_00658c00)() */
    rt_34b2f8();                 /* FUN_0034b2f8 */
    rt_351d9c();                 /* FUN_00351d9c */
    rt_34ad8c((void *)0x170);    /* FUN_0034ad8c(*(extraout_x16 + 0x170)) */
    ((void (*volatile)())0)();     /* (*extraout_x10)() */
    rt_351d9c();                 /* FUN_00351d9c */
    rt_350b60((void *)0x168);    /* FUN_00027754(*(extraout_x16_00 + 0x168)) */
    rt_350950(0);                /* FUN_00350950 */
    /* FUN_00027788 */
    rt_34ac64();                 /* FUN_0034ac64 */
    ((void (*volatile)())0)();     /* (*extraout_x8)() */
    rt_34da48();                 /* FUN_0034da48 */
    ((void (*volatile)())0)();     /* (*extraout_x8_00)() */
    rt_356310();                 /* FUN_00356310 */
}

/* FUN_002127a4 @ 0x002127a4   (est. sk_vspace_trap_127a4)
 * Ghidra: void FUN_002127a4(void)
 * Two-phase handler (mirror of FUN_00210010 recusing into FUN_00211358).
 * Confidence: low (PAC).
 * Notes: Ghidra artifacts: auVar1, in_stack_00000038, (*DAT_00658c00)(). */
void sk_vspace_trap_127a4(void)
{
    sk_cpu();                    /* FUN_0008e518 */
    sk_tcb_get();                /* FUN_0007c0c4 */
    rt_3499b4();                 /* FUN_003499b4 */
    rt_351408();                 /* FUN_00351408 */
    (*(void (**)())sk_global_hook)();   /* (*DAT_00658c00)() */
    rt_349c14();                 /* FUN_00349c14 */
    rt_351bec((void *)0x168);    /* FUN_00351bec(*(extraout_x16 + 0x168)) */
    rt_352894(0);                /* FUN_00352894 */
    rt_34d070();                 /* FUN_0034d070 */
    rt_34c454();                 /* FUN_0034c454 */
    sk_lock_acquire(0,0,0,0,0);  /* FUN_00377824 */
    rt_348e60();                 /* FUN_00348e60 */
    (*(void (**)())sk_global_hook)((void *)0x40);   /* (*DAT_00658c00)(*(x8+0x40)) */
    rt_348bbc();                 /* FUN_00348bbc */
    (*(void (**)())sk_global_hook)();   /* (*DAT_00658c00)() */
    rt_34b4c0();                 /* FUN_0034b4c0 */
    rt_350b9c();                 /* FUN_00350b9c */
    sk_lock_ref(0);              /* FUN_00377bec */
    rt_34dee4();                 /* FUN_0034dee4 */
    rt_31b9c0();                 /* FUN_0031b9c0 */
    /* FUN_000027e8 */
    rt_34b568((void *)0x170);    /* FUN_0034b568(*(extraout_x16_01 + 0x170)) */
    ((void (*volatile)())0)();     /* (*extraout_x10)() */
    rt_34e9b8();                 /* FUN_0034e9b8 */
    sk_vspace_dispatch_11358();  /* FUN_00211358 */
    rt_31e104();                 /* FUN_0031e104 */
    rt_34d434();                 /* FUN_0034d434 */
    rt_350c8c();                 /* FUN_00350c8c */
    ((void (*volatile)())0)();     /* (*extraout_x9)() */
    rt_3511a8((void *)8);        /* FUN_003511a8(*(extraout_x16_00 + 8)) */
    ((void (*volatile)())0)();     /* (*extraout_x8_00)() */
    rt_34f324();                 /* FUN_0034f324 */
    ((void (*volatile)())0)();     /* (*extraout_x8_01)() */
    rt_352b2c();                 /* FUN_00352b2c */
    rt_348b1c();                 /* FUN_00348b1c */
    rt_356090();                 /* FUN_00356090 */
    sk_cpu_current();            /* FUN_0008e500 */
}

/* FUN_0021293c @ 0x0021293c   (est. sk_vspace_trap_1293c)
 * Ghidra: void FUN_0021293c(void)
 * Two-phase handler (mirror of FUN_0021019c; jumptable at 0x00212abc).
 * Confidence: low.
 * Notes: Ghidra: "Could not recover jumptable at 0x00212abc"; 0x212a60 table. */
void sk_vspace_trap_1293c(void)
{
    sk_cpu();                    /* FUN_0008e518 */
    sk_tcb_get();                /* FUN_0007c0c4 */
    rt_3499b4();                 /* FUN_003499b4 */
    rt_351408();                 /* FUN_00351408 */
    (*(void (**)())sk_global_hook)();   /* (*DAT_00658c00)() */
    rt_349c14();                 /* FUN_00349c14 */
    rt_3514b8((void *)0x168);    /* FUN_003514b8(*(extraout_x16 + 0x168)) */
    rt_351bec(0);                /* FUN_00351bec */
    rt_34cd7c();                 /* FUN_0034cd7c */
    rt_3508c0();                 /* FUN_003508c0 */
    sk_lock_acquire(0,0,0,0,0);  /* FUN_00377824 */
    rt_356bc8();                 /* FUN_00356bc8 */
    rt_34f5a4();                 /* FUN_0034f5a4 */
    sk_lock_ref(0);              /* FUN_00377bec */
    rt_34c55c();                 /* FUN_0034c55c */
    rt_31b9c0();                 /* FUN_0031b9c0 */
    rt_356b8c();                 /* FUN_00356b8c */
    if (rt_362acc() != 0) {      /* FUN_00362acc */
        sk_nop_05();             /* FUN_0007c178 */
        rt_34a868((void *)0x170);/* FUN_0034a868(*(extraout_x16_00 + 0x170)) */
        ((void (*volatile)())0)(); /* (*extraout_x10)() */
        rt_3595c0();             /* FUN_003595c0 */
        rt_3196e8(0);            /* FUN_003196e8 */
        rt_350114();             /* FUN_00350114 */
        ((void (*volatile)())0)(); /* (*extraout_x8)() */
        rt_34eb84();             /* FUN_0034eb84 */
        ((void (*volatile)())0)(); /* (*extraout_x8_00)() */
        sk_cpu_current();        /* FUN_0008e500 */
        return;
    }
    rt_3498f4();                 /* FUN_003498f4 */
    rt_349190();                 /* FUN_00349190 */
    rt_34c20c();                 /* FUN_0007c0c4(...,0x212a60) */
    (**(void (**)())(*(void **)(*(void **)((char *)0 + 0x160) - 8) + 0x10))((void *)0);
}

/* FUN_00212b4c @ 0x00212b4c   (est. sk_vspace_obj_free_12b4c)
 * Ghidra: void FUN_00212b4c(void)
 * Small object free: trap-init, frees slot[1], then relinks the list head
 * (x20) to point at unaff_x21/x19. Confidence: medium.
 * Notes: Ghidra artifacts: FUN_0036b118 (sk_free), unaff_x19/x20/x21. */
void sk_vspace_obj_free_12b4c(void)
{
    sk_trap_init();              /* FUN_0008409c */
    sk_free((void *)0);
    ((void (*volatile)())0)();     /* relink list head (x20) */
}

/* FUN_00212b80 @ 0x00212b80   (est. sk_vspace_obj_free_12b80)
 * Ghidra: void FUN_00212b80(void)
 * Free variant: FUN_002086d4(slot[0], slot[1]) then frees slot[1].
 * Confidence: medium.
 * Notes: Ghidra artifacts: FUN_0036b118, FUN_002086d4. */
void sk_vspace_obj_free_12b80(void)
{
    sk_vspace_resume7(0, 0);     /* FUN_002086d4 */
    sk_free((void *)0);
}

/* FUN_00212bb0 @ 0x00212bb0   (est. sk_vspace_obj_set_12bb0)
 * Ghidra: void FUN_00212bb0(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,undefined8 param_5)
 * Object setter: stores (param_1,param_2) locally, calls FUN_003516cc with
 * param_5, then dispatches into FUN_00212bfc with a tag 0x66c230.
 * Confidence: medium.
 * Notes: Ghidra artifacts: auVar1 [16], 0x66c230 tag. */
void sk_vspace_obj_set_12bb0(void *a, void *b, void *c, void *d, void *e)
{
    (void)c; (void)d;
    rt_3516cc(a, b, e);          /* FUN_003516cc */
    rt_31bb04();                 /* FUN_0031bb04 */
    sk_vspace_obj_set_12bfc();   /* FUN_00212bfc */
}

/* FUN_00212bfc @ 0x00212bfc   (est. sk_vspace_obj_set_12bfc)
 * Ghidra: void FUN_00212bfc(void)
 * Object teardown: bookkeeping then FUN_0020a918. Confidence: medium.
 * Notes: Ghidra artifacts: rt_34d7a8, rt_31b978, rt_351d18, FUN_0020a918. */
void sk_vspace_obj_set_12bfc(void)
{
    rt_34d7a8();                 /* FUN_0034d7a8 */
    rt_31b978();                 /* FUN_0031b978 */
    rt_351d18();                 /* FUN_00351d18 */
    sk_vspace_resume3(0);        /* FUN_0020a918 */
}

/* FUN_00212c54 @ 0x00212c54   (est. sk_vspace_obj_get_12c54)
 * Ghidra: undefined8 FUN_00212c54(void)
 * Object getter: runs FUN_0035776c, then returns the 16-byte value from
 * thunk_FUN_002133ac (FUN_002133ac), storing its low half at x19.
 * Confidence: medium.
 * Notes: Ghidra artifacts: auVar1 [16], thunk_FUN_002133ac. */
void *sk_vspace_obj_get_12c54(void)
{
    rt_35776c();                 /* FUN_0035776c */
    /* thunk_FUN_002133ac -> auVar1 */
    sk_vspace_obj_dtor_133ac();                    /* FUN_002133ac (via thunk) */
    return 0;
}

/* FUN_00212c80 @ 0x00212c80   (est. sk_vspace_obj_dtor_12c80)
 * Ghidra: void thunk_FUN_002133ac(void)
 * Thunk to FUN_002133ac (vtable method @+0x80 teardown). Confidence: medium.
 * Notes: Ghidra: thunk_FUN_002133ac; see FUN_002133ac for the body. */
void sk_vspace_obj_dtor_12c80(void)
{
    sk_vspace_obj_dtor_133ac();
}

/* FUN_00212c84 @ 0x00212c84   (est. sk_vspace_obj_dtor_12c84)
 * Ghidra: void FUN_00212c84(void)
 * Object method-dispatch teardown: run vtable method at +0x98 then free.
 * Confidence: low (this register lost to PAC; transcribed as indirect).
 * Notes: Ghidra: (**(code **)(extraout_x16 + 0x98))(), sk_free. */
void sk_vspace_obj_dtor_12c84(void)
{
    rt_34b798();                 /* FUN_0034b798 */
    (**(void (**)())(0 + 0x98))();   /* vtable +0x98 */
    rt_35310c();                 /* FUN_0035310c */
    sk_free(0);
}

/* FUN_00212cc4 @ 0x00212cc4   (est. sk_vspace_obj_dtor_12cc4)
 * Ghidra: void FUN_00212cc4(void)
 * Object method-dispatch teardown: vtable method @+0xa8 then free.
 * Confidence: low (PAC).
 * Notes: Ghidra: (**(code **)(extraout_x16 + 0xa8))(). */
void sk_vspace_obj_dtor_12cc4(void)
{
    rt_34f464();                 /* FUN_0034f464 */
    (**(void (**)())(0 + 0xa8))();   /* vtable +0xa8 */
    rt_357418();                 /* FUN_00357418 */
    sk_free(0);
    rt_356c48();                 /* FUN_00356c48 */
}

/* FUN_00212d10 @ 0x00212d10   (est. sk_vspace_obj_dtor_12d10)
 * Ghidra: void FUN_00212d10(void)
 * Object method-dispatch teardown: vtable method @+0xb0 then free.
 * Confidence: low (PAC).
 * Notes: Ghidra: (**(code **)(extraout_x16 + 0xb0))(). */
void sk_vspace_obj_dtor_12d10(void)
{
    rt_34b798();                 /* FUN_0034b798 */
    (**(void (**)())(0 + 0xb0))();   /* vtable +0xb0 */
    rt_35310c();                 /* FUN_0035310c */
    sk_free(0);
}

/* FUN_00212d50 @ 0x00212d50   (est. sk_vspace_obj_dtor_12d50)
 * Ghidra: void FUN_00212d50(void)
 * Object teardown: resolve vtable (in_x5), hook call, and if the object
 * (unaff_x21) is non-null invoke vtable method @+0x20. Confidence: low.
 * Notes: Ghidra artifacts: (*DAT_00658c00)(), (**(code **)(lVar2 + 0x20))(). */
void sk_vspace_obj_dtor_12d50(void)
{
    (*(void (**)())sk_global_hook)();
    ((void (*volatile)())0)(0, 0); /* (*extraout_x12)(...) */
    if (1) {                     /* unaff_x21 != 0 */
        rt_36993c(0,0,0,0);      /* FUN_0036993c */
        (**(void (**)())(0 + 0x20))(0, 0, 0);   /* vtable +0x20 */
    }
}

/* FUN_00212e34 @ 0x00212e34   (est. sk_vspace_obj_dtor_12e34)
 * Ghidra: void FUN_00212e34(void)
 * Forwarder to FUN_00212f24. Confidence: high (trivial).
 */
void sk_vspace_obj_dtor_12e34(void)
{
    sk_vspace_obj_dtor_12f24();
}

/* FUN_00212e38 @ 0x00212e38   (est. sk_vspace_obj_dtor_12e38)
 * Ghidra: void FUN_00212e38(void)
 * Forwarder to FUN_00212f24. Confidence: high.
 */
void sk_vspace_obj_dtor_12e38(void)
{
    sk_vspace_obj_dtor_12f24();
}

/* FUN_00212e74 @ 0x00212e74   (est. sk_vspace_obj_dtor_12e74)
 * Ghidra: void FUN_00212e74(void)
 * Forwarder to FUN_002131d0. Confidence: high.
 */
void sk_vspace_obj_dtor_12e74(void)
{
    sk_vspace_obj_dtor_131d0();
}

/* FUN_00212e8c @ 0x00212e8c   (est. sk_vspace_obj_dtor_12e8c)
 * Ghidra: void FUN_00212e8c(void)
 * Forwarder to FUN_0021321c. Confidence: high.
 */
void sk_vspace_obj_dtor_12e8c(void)
{
    sk_vspace_obj_dtor_1321c();
}

/* FUN_00212ea4 @ 0x00212ea4   (est. sk_vspace_obj_dtor_12ea4)
 * Ghidra: void FUN_00212ea4(void)
 * Forwarder to FUN_00213260. Confidence: high.
 */
void sk_vspace_obj_dtor_12ea4(void)
{
    sk_vspace_obj_dtor_13260();
}

/* FUN_00212ec8 @ 0x00212ec8   (est. sk_vspace_obj_dtor_12ec8)
 * Ghidra: void FUN_00212ec8(void)
 * Forwarder to FUN_00213028. Confidence: high.
 */
void sk_vspace_obj_dtor_12ec8(void)
{
    sk_vspace_obj_dtor_13028();
}

/* FUN_00212ee4 @ 0x00212ee4   (est. sk_vspace_obj_dtor_12ee4)
 * Ghidra: void FUN_00212ee4(void)
 * Forwarder to FUN_00212f24. Confidence: high.
 */
void sk_vspace_obj_dtor_12ee4(void)
{
    sk_vspace_obj_dtor_12f24();
}

/* FUN_00212ee8 @ 0x00212ee8   (est. sk_vspace_obj_dtor_12ee8)
 * Ghidra: void FUN_00212ee8(void)
 * Forwarder to FUN_00212f24. Confidence: high.
 */
void sk_vspace_obj_dtor_12ee8(void)
{
    sk_vspace_obj_dtor_12f24();
}

/* FUN_00212f24 @ 0x00212f24   (est. sk_vspace_obj_dtor_12f24)
 * Ghidra: void FUN_00212f24(void)
 * Object teardown core: runs a bookkeeping sequence then FUN_002130ec.
 * Confidence: medium.
 * Notes: Ghidra artifacts: FUN_00356188/FUN_00352068/FUN_0034a210,
 *   FUN_00002534, FUN_003498c4, FUN_003516d8, FUN_002130ec. */
void sk_vspace_obj_dtor_12f24(void)
{
    rt_356188();                 /* FUN_00356188 */
    rt_352068();                 /* FUN_00352068 */
    rt_34a210();                 /* FUN_0034a210 */
    /* FUN_00002534 */
    rt_3498c4();                 /* FUN_003498c4 */
    rt_3516d8();                 /* FUN_003516d8 */
    sk_vspace_obj_dtor_130ec(0,0,0,0,0,0,0,0,0);  /* FUN_002130ec */
}

/* FUN_00212fa4 @ 0x00212fa4   (est. sk_vspace_obj_dtor_12fa4)
 * Ghidra: void FUN_00212fa4(void)
 * Object method-dispatch teardown: vtable method @+0x48 then free.
 * Confidence: low (PAC).
 * Notes: Ghidra: (**(code **)(extraout_x16 + 0x48))(). */
void sk_vspace_obj_dtor_12fa4(void)
{
    sk_nop_01();                 /* FUN_0007c198 */
    (**(void (**)())(0 + 0x48))();   /* vtable +0x48 */
    rt_35310c();                 /* FUN_0035310c */
    sk_free(0);
}

/* FUN_00212fe8 @ 0x00212fe8   (est. sk_vspace_obj_dtor_12fe8)
 * Ghidra: void FUN_00212fe8(void)
 * Object method-dispatch teardown: vtable method @+0xd0 then free.
 * Confidence: low (PAC). */
void sk_vspace_obj_dtor_12fe8(void)
{
    rt_34b798();                 /* FUN_0034b798 */
    (**(void (**)())(0 + 0xd0))();   /* vtable +0xd0 */
    rt_35310c();                 /* FUN_0035310c */
    sk_free(0);
}

/* FUN_00213028 @ 0x00213028   (est. sk_vspace_obj_dtor_13028)
 * Ghidra: void FUN_00213028(void)
 * Object method-dispatch teardown: vtable method @+0xd8 then free.
 * Confidence: low (PAC). */
void sk_vspace_obj_dtor_13028(void)
{
    rt_34f464();                 /* FUN_0034f464 */
    (**(void (**)())(0 + 0xd8))();   /* vtable +0xd8 */
    rt_357418();                 /* FUN_00357418 */
    sk_free(0);
    rt_356c48();                 /* FUN_00356c48 */
}

/* FUN_00213074 @ 0x00213074   (est. sk_vspace_obj_dtor_13074)
 * Ghidra: void FUN_00213074(void)
 * Object method-dispatch teardown: vtable method @+0xe0 then free.
 * Confidence: low (PAC). */
void sk_vspace_obj_dtor_13074(void)
{
    rt_34b798();                 /* FUN_0034b798 */
    (**(void (**)())(0 + 0xe0))();   /* vtable +0xe0 */
    rt_35310c();                 /* FUN_0035310c */
    sk_free(0);
}

/* FUN_002130b4 @ 0x002130b4   (est. sk_vspace_obj_dtor_130b4)
 * Ghidra: void FUN_002130b4(void)
 * Object method-dispatch teardown: vtable method @+0x50 (no free).
 * Confidence: low (PAC). */
void sk_vspace_obj_dtor_130b4(void)
{
    sk_nop_01();                 /* FUN_0007c198 */
    (**(void (**)())(0 + 0x50))();   /* vtable +0x50 */
}

/* FUN_002130ec @ 0x002130ec   (est. sk_vspace_obj_dtor_130ec)
 * Ghidra: void FUN_002130ec(undefined8 param_1..param_9)
 * Multi-arg object teardown: stores 6 args into a stack block, calls vtable
 * method @+0x58, and if unaff_x21 nonzero runs an unwind sequence with
 * FUN_00365b6c/FUN_003698b0. Confidence: low (PAC).
 * Notes: Ghidra artifacts: auStack_80[16], (**(code **)(extraout_x16+0x58))(). */
void sk_vspace_obj_dtor_130ec(void *a, void *b, void *c, void *d, void *e,
                              void *f, void *g, void *h, void *i)
{
    (void)a; (void)b; (void)c; (void)d; (void)e; (void)f; (void)g; (void)h; (void)i;
    rt_353ea0(i);                /* FUN_00353ea0 */
    (**(void (**)())(0 + 0x58))(0, 0, e);   /* vtable +0x58 */
    if (1) {                     /* unaff_x21 != 0 */
        rt_34a210();             /* FUN_0034a210 */
        /* FUN_00002534 -> uVar1 */
        rt_365b6c(h, 0, 0, f, 7);/* FUN_00365b6c */
        rt_34e69c();             /* FUN_0034e69c */
        rt_3698b0();             /* FUN_003698b0 */
    }
}

/* FUN_00213190 @ 0x00213190   (est. sk_vspace_obj_dtor_13190)
 * Ghidra: void FUN_00213190(void)
 * Forwarder to FUN_00212f24. Confidence: high.
 */
void sk_vspace_obj_dtor_13190(void)
{
    sk_vspace_obj_dtor_12f24();
}

/* FUN_00213194 @ 0x00213194   (est. sk_vspace_obj_dtor_13194)
 * Ghidra: void FUN_00213194(void)
 * Forwarder to FUN_00212f24. Confidence: high.
 */
void sk_vspace_obj_dtor_13194(void)
{
    sk_vspace_obj_dtor_12f24();
}

/* FUN_002131d0 @ 0x002131d0   (est. sk_vspace_obj_dtor_131d0)
 * Ghidra: void FUN_002131d0(void)
 * Object method-dispatch teardown: vtable method @+0x60 then free.
 * Confidence: low (PAC). */
void sk_vspace_obj_dtor_131d0(void)
{
    rt_34f464();                 /* FUN_0034f464 */
    (**(void (**)())(0 + 0x60))();   /* vtable +0x60 */
    rt_357418();                 /* FUN_00357418 */
    sk_free(0);
    rt_356c48();                 /* FUN_00356c48 */
}

/* FUN_0021321c @ 0x0021321c   (est. sk_vspace_obj_dtor_1321c)
 * Ghidra: void FUN_0021321c(void)
 * Object method-dispatch teardown: vtable method @+0x68 then free.
 * Confidence: low (PAC). */
void sk_vspace_obj_dtor_1321c(void)
{
    rt_34f464();                 /* FUN_0034f464 */
    (**(void (**)())(0 + 0x68))();   /* vtable +0x68 */
    sk_free(0);
}

/* FUN_00213260 @ 0x00213260   (est. sk_vspace_obj_dtor_13260)
 * Ghidra: void FUN_00213260(void)
 * Object method-dispatch teardown: vtable method @+0x88 then free.
 * Confidence: low (PAC). */
void sk_vspace_obj_dtor_13260(void)
{
    rt_34f464();                 /* FUN_0034f464 */
    (**(void (**)())(0 + 0x88))();   /* vtable +0x88 */
    rt_357418();                 /* FUN_00357418 */
    sk_free(0);
    rt_356c48();                 /* FUN_00356c48 */
}

/* FUN_002132ac @ 0x002132ac   (est. sk_vspace_obj_dtor_132ac)
 * Ghidra: void FUN_002132ac(void)
 * Object method-dispatch teardown: vtable method @+0x90 then free.
 * Confidence: low (PAC). */
void sk_vspace_obj_dtor_132ac(void)
{
    rt_34b798();                 /* FUN_0034b798 */
    (**(void (**)())(0 + 0x90))();   /* vtable +0x90 */
    rt_35310c();                 /* FUN_0035310c */
    sk_free(0);
}

/* FUN_002132ec @ 0x002132ec   (est. sk_vspace_obj_dtor_132ec)
 * Ghidra: void FUN_002132ec(void)
 * Object method-dispatch teardown: vtable method @+0xa0 then free.
 * Confidence: low (PAC). */
void sk_vspace_obj_dtor_132ec(void)
{
    rt_34b798();                 /* FUN_0034b798 */
    (**(void (**)())(0 + 0xa0))();   /* vtable +0xa0 */
    rt_35310c();                 /* FUN_0035310c */
    sk_free(0);
}

/* FUN_0021332c @ 0x0021332c   (est. sk_vspace_obj_dtor_1332c)
 * Ghidra: void FUN_0021332c(undefined8 param_1,long *param_2)
 * Object method-dispatch: vtable method @+0x70 (from param_2's vtable).
 * Confidence: medium.
 * Notes: Ghidra: (**(code **)(*param_2 + 0x70))(). */
void sk_vspace_obj_dtor_1332c(void *a, void *b)
{
    (void)a;
    (**(void (**)())(*(void **)b + 0x70))();
}

/* FUN_00213368 @ 0x00213368   (est. sk_vspace_obj_dtor_13368)
 * Ghidra: void FUN_00213368(void)
 * Object method-dispatch teardown: vtable method @+0x78 then free.
 * Confidence: low (PAC). */
void sk_vspace_obj_dtor_13368(void)
{
    sk_nop_01();                 /* FUN_0007c198 */
    (**(void (**)())(0 + 0x78))();   /* vtable +0x78 */
    rt_35310c();                 /* FUN_0035310c */
    sk_free(0);
}

/* FUN_002133ac @ 0x002133ac   (est. sk_vspace_obj_dtor_133ac)
 * Ghidra: void FUN_002133ac(void)
 * Object method-dispatch teardown: vtable method @+0x80, then a pair of
 * helpers and FUN_002085fc dispatch. Confidence: low (PAC).
 * Notes: Ghidra: (**(code **)(extraout_x16 + 0x80))(), 0x66c1d8 tag. */
void sk_vspace_obj_dtor_133ac(void)
{
    rt_34f464();                 /* FUN_0034f464 */
    (**(void (**)())(0 + 0x80))();   /* vtable +0x80 */
    /* FUN_000b43e8 */
    sk_free(0);
    rt_3504e8();                 /* FUN_003504e8 */
    rt_31bb1c();                 /* FUN_0031bb1c */
    sk_vspace_resume6(0);        /* FUN_002085fc (tag 0x66c1d8) */
}

/* FUN_00213460 @ 0x00213460   (est. sk_vspace_obj_dtor_13460)
 * Ghidra: void FUN_00213460(undefined8 param_1)
 * Object method-dispatch: vtable method @+0x20 after FUN_0034b07c.
 * Confidence: medium.
 * Notes: Ghidra: (**(code **)(extraout_x16 + 0x20))(). */
void sk_vspace_obj_dtor_13460(void *a)
{
    (void)a;
    rt_34c20c();                 /* FUN_0007c0c4(a,a) -> FUN_0034c20c */
    rt_34b07c(0,0,0);            /* FUN_0034b07c */
    (**(void (**)())(0 + 0x20))((void *)0);   /* vtable +0x20 */
}

/* FUN_00213464 @ 0x00213464   (est. sk_vspace_obj_dtor_13464)
 * Ghidra: void FUN_00213464(undefined8 param_1)
 * Mirror of FUN_00213460. Confidence: medium. */
void sk_vspace_obj_dtor_13464(void *a)
{
    (void)a;
    rt_34c20c();                 /* FUN_0007c0c4(a,a) -> FUN_0034c20c */
    rt_34b07c(0,0,0);            /* FUN_0034b07c */
    (**(void (**)())(0 + 0x20))((void *)0);   /* vtable +0x20 */
}

/* FUN_002134bc @ 0x002134bc   (est. sk_vspace_obj_dtor_134bc)
 * Ghidra: void FUN_002134bc(undefined8 param_1,long param_2)
 * Object lookup/teardown: FUN_00362acc gate; on hit dispatch through the
 * object vtable at +0x38/-8+0x10 with param_2; else a noreturn panic.
 * Confidence: low (PAC, unrecoverable jumptable at 0x00213548).
 * Notes: Ghidra: "Could not recover jumptable"; noreturn FUN_001afe4c. */
void sk_vspace_obj_dtor_134bc(void *a, void *b)
{
    (void)a;
    if (rt_362acc() != 0) {      /* FUN_00362acc */
        /* FUN_000027e8 */
        (**(void (**)())(*(void **)(*(void **)((char *)0 + 0x38) - 8) + 0x10))
            (a, (char *)b + 0x48);
        return;
    }
    rt_34865c();                 /* FUN_0034865c */
    rt_349844();                 /* FUN_00349844 */
    rt_350a94();                 /* FUN_00350a94 */
    sk_panic_no_return2();       /* FUN_001afe4c (noreturn) */
}

/* FUN_00213580 @ 0x00213580   (est. sk_vspace_obj_dtor_13580)
 * Ghidra: void FUN_00213580(undefined8 param_1,undefined8 param_2)
 * Object teardown: FUN_00362acc gate; on hit invoke vtable method @+0x10,
 * then FUN_00350268(...,hit) and FUN_000839d8. Confidence: low (PAC).
 * Notes: Ghidra artifacts: (**(code **)(extraout_x16_00 + 0x10))(). */
void sk_vspace_obj_dtor_13580(void *a, void *b)
{
    (void)b;
    rt_34ed08(a, b, b);          /* FUN_0034ed08 */
    rt_31b9c0();                 /* FUN_0031b9c0 */
    rt_356b98();                 /* FUN_00356b98 */
    int hit = (rt_362acc() != 0);/* FUN_00362acc */
    unsigned long v;
    if (!hit) {
        v = 0;
    } else {
        sk_nop_01();             /* FUN_0007c198 */
        rt_3522b8((void *)0x48); /* FUN_003522b8(*(extraout_x16 + 0x48)) */
        v = (**(unsigned long (**)(void))(0 + 0x10))();   /* vtable +0x10 */
    }
    rt_350268(v, hit);           /* FUN_00350268 */
    /* FUN_000839d8 */
}

/* FUN_0021360c @ 0x0021360c   (est. sk_vspace_obj_dtor_1360c)
 * Ghidra: void FUN_0021360c(void)
 * Object teardown: two-phase (mirror pattern) ending in FUN_002134bc and a
 * pair of indirect calls through auVar2. Confidence: low (PAC).
 * Notes: Ghidra artifacts: auVar2 [16], (*auVar2._0_8_)() indirect, FUN_002134bc. */
void sk_vspace_obj_dtor_1360c(void)
{
    sk_frame_enter();            /* FUN_00084220 */
    rt_3536d0();                 /* FUN_003536d0 */
    rt_3494e8();                 /* FUN_003494e8 */
    (*(void (**)())sk_global_hook)((void *)0x40);   /* (*DAT_00658c00)(*(x8+0x40)) */
    rt_348a80();                 /* FUN_00348a80 */
    (*(void (**)())sk_global_hook)();   /* (*DAT_00658c00)() */
    rt_34b3d8();                 /* FUN_0034b3d8 */
    rt_3536d0();                 /* FUN_003536d0 */
    rt_350b60((void *)0x48);     /* FUN_00350b60(*(extraout_x16 + 0x48)) */
    rt_353c6c();                 /* FUN_00353c6c */
    ((void (*volatile)())0)();     /* (*extraout_x10)() */
    rt_353984();                 /* FUN_00353984 */
    sk_vspace_obj_dtor_134bc(0,0);  /* FUN_002134bc */
    rt_3536d0();                 /* FUN_003536d0 */
    rt_35125c((void *)0x40);     /* FUN_0035125c(*(extraout_x16_00 + 0x40)) */
    /* FUN_0014ae44 */
    rt_34bddc();                 /* FUN_0034bddc */
    rt_34df34();                 /* FUN_0034df34 */
    ((void (*volatile)())0)();     /* (*extraout_x8_00)() */
    rt_35a640();                 /* FUN_0035a640 */
    rt_3514e8(0);                /* FUN_003514e8 */
    ((void (*volatile)())0)();     /* (*auVar2._0_8_)() */
    rt_35060c();                 /* FUN_0035060c */
    ((void (*volatile)())0)();     /* (*auVar2._0_8_)() */
    rt_35687c();                 /* FUN_0035687c */
    sk_frame_leave();            /* FUN_00084234 */
}

/* FUN_00213720 @ 0x00213720   (est. sk_vspace_obj_dtor_13720)
 * Ghidra: void FUN_00213720(void)
 * Object teardown (mirror of FUN_0021360c with pcVar2 indirection).
 * Confidence: low (PAC).
 * Notes: Ghidra artifacts: (*pcVar2)() indirect, FUN_002134bc. */
void sk_vspace_obj_dtor_13720(void)
{
    sk_frame_enter();            /* FUN_00084220 */
    rt_3536d0();                 /* FUN_003536d0 */
    rt_3494e8();                 /* FUN_003494e8 */
    (*(void (**)())sk_global_hook)((void *)0x40);   /* (*DAT_00658c00)(*(x8+0x40)) */
    rt_348a80();                 /* FUN_00348a80 */
    (*(void (**)())sk_global_hook)();   /* (*DAT_00658c00)() */
    rt_34b3d8();                 /* FUN_0034b3d8 */
    rt_3536d0();                 /* FUN_003536d0 */
    rt_350b60((void *)0x48);     /* FUN_00350b60(*(extraout_x16 + 0x48)) */
    rt_353c6c();                 /* FUN_00353c6c */
    ((void (*volatile)())0)();     /* (*extraout_x10)() */
    rt_353984();                 /* FUN_00353984 */
    sk_vspace_obj_dtor_134bc(0,0);  /* FUN_002134bc */
    rt_3536d0();                 /* FUN_003536d0 */
    void *pc = (void *)0;        /* *(extraout_x16_00 + 0x40) */
    /* FUN_0016186c(pc) */
    rt_34bddc();                 /* FUN_0034bddc */
    rt_34df34();                 /* FUN_0034df34 */
    ((void (*volatile)())0)();     /* (*extraout_x8_00)() */
    rt_35a640();                 /* FUN_0035a640 */
    rt_3514e8(0);                /* FUN_003514e8 */
    (*(void (**)())pc)();    /* (*pcVar2)() */
    rt_35060c();                 /* FUN_0035060c */
    (*(void (**)())pc)();    /* (*pcVar2)() */
    rt_35687c();                 /* FUN_0035687c */
    sk_frame_leave();            /* FUN_00084234 */
}

/* FUN_00213834 @ 0x00213834   (est. sk_vspace_obj_dtor_13834)
 * Ghidra: void FUN_00213834(void)
 * Object method-dispatch: vtable method @+8 after FUN_0034ece8.
 * Confidence: medium.
 * Notes: Ghidra: (**(code **)(extraout_x16 + 8))(). */
void sk_vspace_obj_dtor_13834(void)
{
    rt_34c20c();                 /* FUN_0007c0c4() -> FUN_0034c20c */
    rt_34ece8(0, 0);             /* FUN_0034ece8 */
    (**(void (**)())(0 + 8))((void *)0);   /* vtable +8 */
}

/* FUN_002138b4 @ 0x002138b4   (est. sk_vspace_obj_alloc_138b4)
 * Ghidra: void FUN_002138b4(void)
 * Page allocator wrapper (FUN_0036b270). Confidence: medium (trivial).
 */
void sk_vspace_obj_alloc_138b4(void)
{
    sk_alloc_pages(0, 0);        /* FUN_0036b270 */
}

/* FUN_002138dc @ 0x002138dc   (est. sk_vspace_obj_free_138dc)
 * Ghidra: void FUN_002138dc(void)
 * Small object free (mirror of FUN_00212b4c). Confidence: medium.
 * Notes: Ghidra artifacts: FUN_0036b118, unaff_x19/x20/x21. */
void sk_vspace_obj_free_138dc(void)
{
    sk_trap_init();              /* FUN_0008409c */
    sk_free((void *)0);
    ((void (*volatile)())0)();     /* relink list head (x20) */
}

/* FUN_00213910 @ 0x00213910   (est. sk_vspace_obj_dtor_13910)
 * Ghidra: void FUN_00213910(void)
 * Object teardown: bookkeeping then FUN_00348b1c. Confidence: medium.
 * Notes: Ghidra artifacts: FUN_00351894/FUN_0031b9c0/FUN_00351d18/FUN_00348b1c. */
void sk_vspace_obj_dtor_13910(void)
{
    rt_351894();                 /* FUN_00351894 */
    rt_31b9c0();                 /* FUN_0031b9c0 */
    rt_351d18();                 /* FUN_00351d18 */
    rt_348b1c();                 /* FUN_00348b1c */
}

/* FUN_00213940 @ 0x00213940   (est. sk_vspace_obj_dtor_13940)
 * Ghidra: void FUN_00213940(void)
 * Object teardown: bookkeeping + indirect call. Confidence: low (PAC).
 * Notes: Ghidra artifacts: (*extraout_x8)() indirect. */
void sk_vspace_obj_dtor_13940(void)
{
    rt_3504d0();                 /* FUN_003504d0 */
    sk_nop_01();                 /* FUN_0007c198 */
    rt_31bb80(0);                /* FUN_0031bb80 */
    rt_34bcf0();                 /* FUN_0034bcf0 */
    ((void (*volatile)())0)();     /* (*extraout_x8)() */
}

/* FUN_0021398c @ 0x0021398c   (est. sk_vspace_obj_dtor_1398c)
 * Ghidra: void FUN_0021398c(void)
 * Object teardown with a consistency check: two runtime reads (lVar2/lVar3);
 * if equal the teardown tail runs and returns; else a noreturn panic.
 * Confidence: low (PAC).
 * Notes: Ghidra artifacts: pcVar4=FUN_0031bbb0, noreturn FUN_001afe4c. */
void sk_vspace_obj_dtor_1398c(void)
{
    rt_351e20();                 /* FUN_00351e20 */
    rt_3543a0();                 /* FUN_003543a0 */
    rt_352914();                 /* FUN_00352914 */
    sk_nop_01();                 /* FUN_0007c198 */
    rt_31bb80(0);                /* FUN_0031bb80 */
    rt_3514ac();                 /* FUN_003514ac */
    rt_3505e8();                 /* FUN_003505e8 */
    long l2 = ((long (*volatile)())0)();
    rt_31bb80();                 /* FUN_0031bb80 */
    rt_35075c();                 /* FUN_0035075c */
    rt_3508a8();                 /* FUN_003508a8 */
    long l3 = ((long (*volatile)())0)();
    if (l2 == l3) {
        ((void (*volatile)())0)(); /* (*pcVar4)() = FUN_0031bbb0 */
        rt_350164();             /* FUN_00350164 */
        rt_351de4();             /* FUN_00351de4 */
        rt_351d30(((unsigned int (*volatile)())0)() & 1, 0); /* FUN_00351d30 */
        return;
    }
    rt_35047c();                 /* FUN_0035047c */
    rt_349518();                 /* FUN_0034951c */
    /* FUN_0006f768 */
    rt_351a8c();                 /* FUN_00351a8c */
    sk_panic_no_return2();       /* FUN_001afe4c (noreturn) */
}

/* FUN_00213b28 @ 0x00213b28   (est. sk_vspace_obj_dtor_13b28)
 * Ghidra: void FUN_00213b28(void)
 * Object teardown: bookkeeping then FUN_0020c1bc. Confidence: medium.
 * Notes: Ghidra artifacts: FUN_0034d7a8/FUN_003193f4/FUN_00351d18/FUN_0020c1bc. */
void sk_vspace_obj_dtor_13b28(void)
{
    rt_34d7a8();                 /* FUN_0034d7a8 */
    rt_3193f4();                 /* FUN_003193f4 */
    rt_351d18();                 /* FUN_00351d18 */
    sk_vspace_resume4(0);        /* FUN_0020c1bc */
}

/* FUN_00213b54 @ 0x00213b54   (est. sk_vspace_obj_dtor_13b54)
 * Ghidra: void FUN_00213b54(void)
 * Object teardown: bookkeeping then FUN_0020e5c0. Confidence: medium.
 * Notes: Ghidra artifacts: FUN_0034d7a8/FUN_0031ba3c/FUN_00351d18/FUN_0020e5c0. */
void sk_vspace_obj_dtor_13b54(void)
{
    rt_34d7a8();                 /* FUN_0034d7a8 */
    rt_31ba3c();                 /* FUN_0031ba3c */
    rt_351d18();                 /* FUN_00351d18 */
    sk_vspace_dispatch_e5c0(0);  /* FUN_0020e5c0 */
}

/* FUN_00213b80 @ 0x00213b80   (est. sk_vspace_obj_dtor_13b80)
 * Ghidra: void FUN_00213b80(void)
 * Object teardown: bookkeeping then FUN_00210bbc. Confidence: medium.
 * Notes: Ghidra artifacts: FUN_0034d7a8/FUN_0031baa0/FUN_00351d18/FUN_00210bbc. */
void sk_vspace_obj_dtor_13b80(void)
{
    rt_34d7a8();                 /* FUN_0034d7a8 */
    rt_31baa0();                 /* FUN_0031baa0 */
    rt_351d18();                 /* FUN_00351d18 */
    sk_vspace_obj_destroy_10bbc(0);  /* FUN_00210bbc */
}

/* FUN_00213bac @ 0x00213bac   (est. sk_vspace_obj_alloc_13bac)
 * Ghidra: void FUN_00213bac(long param_1)
 * Page allocator for param_1+0x20. Confidence: medium.
 * Notes: Ghidra artifacts: FUN_0036b270(*(param_1+0x20)). */
void sk_vspace_obj_alloc_13bac(void *a)
{
    sk_alloc_pages((unsigned long)*(void **)((char *)a + 0x20), 0);  /* FUN_0036b270 */
}

/* FUN_00213c08 @ 0x00213c08   (est. sk_vspace_obj_alloc_13c08)
 * Ghidra: void FUN_00213c08(void)
 * Object allocator: FUN_00356c18 then stores 16-byte value from FUN_002060a0.
 * Confidence: medium.
 * Notes: Ghidra artifacts: auVar1 [16], FUN_002060a0. */
void sk_vspace_obj_alloc_13c08(void)
{
    rt_356c18();                 /* FUN_00356c18 */
    sk_vspace_resume5(0);        /* FUN_002060a0 */
}

/* FUN_00213c30 @ 0x00213c30   (est. sk_vspace_obj_alloc_13c30)
 * Ghidra: void FUN_00213c30(void)
 * Object allocator: FUN_00356c18 then FUN_00213bac. Confidence: medium.
 * Notes: Ghidra artifacts: auVar1 [16], FUN_00213bac. */
void sk_vspace_obj_alloc_13c30(void)
{
    rt_356c18();                 /* FUN_00356c18 */
    sk_vspace_obj_alloc_13bac(0);/* FUN_00213bac */
}

/* FUN_00213c58 @ 0x00213c58   (est. sk_vspace_obj_alloc_13c58)
 * Ghidra: undefined * FUN_00213c58(long *param_1, undefined8 *param_2, long param_3)
 * Object allocator: allocates 0x28 bytes (tag 0x1d1c), stores it, calls
 * FUN_00213cd0 to initialize, stores the returned 16-byte value at obj+0x20,
 * returns a static type descriptor (&DAT_003471a4). Confidence: high (small,
 * locally coherent).
 * Notes: Ghidra artifacts: FUN_0036a908(0x28,0x1d1c), &DAT_003471a4. */
void *sk_vspace_obj_alloc_13c58(void *a, void *b, void *c)
{
    (void)b; (void)c;
    void *obj = sk_alloc(0x28, 0x1d1c);   /* FUN_0036a908 */
    *(void **)a = obj;
    /* FUN_00213cd0(lVar1, *param_2, param_2[1], *unaff_x20, *(param_3+0x10)) */
    sk_vspace_obj_alloc_13cd0(obj, 0, 0, 0, *(void **)((char *)c + 0x10));
    *(void **)((char *)obj + 0x20) = (void *)0;    /* uVar2 from FUN_00213cd0 */
    return (void *)0;            /* &DAT_003471a4 */
}

/* FUN_00213cd0 @ 0x00213cd0   (est. sk_vspace_obj_alloc_13cd0)
 * Ghidra: undefined1 [16] FUN_00213cd0(long *param_1,undefined8 param_2,undefined8 param_3,long *param_4,long param_5)
 * Object initializer: sets obj[0]=param_5, obj[1]=vtable(param_5-8), allocates
 * a sub-node sized from vtable+0x40 (tag 0xe087), and calls vtable method
 * @+0xe8 to fill it; returns a 16-byte descriptor (&DAT_003471a8, node).
 * Confidence: high (small, locally coherent).
 * Notes: Ghidra artifacts: (**(code **)(*param_4 + 0xe8))(..), &DAT_003471a8. */
void sk_vspace_obj_alloc_13cd0(void *a, void *b, void *c, void *d, void *e)
{
    (void)b; (void)c; (void)d;
    void **obj = a;
    obj[0] = e;
    void *vt = *(void **)((char *)e - 8);
    obj[1] = vt;
    void *node = sk_alloc((unsigned long)*(void **)((char *)vt + 0x40), 0xe087);  /* FUN_0036a908 */
    obj[2] = node;
    (**(void (**)())(*(void **)d + 0xe8))(node, b, c);
}

/* FUN_00213e24 @ 0x00213e24   (est. sk_vspace_obj_get_13e24)
 * Ghidra: undefined8 thunk_FUN_00077a90(void)
 * Getter: returns *x20. Confidence: high (trivial).
 * Notes: Ghidra: thunk_FUN_00077a90.
 */
void *sk_vspace_obj_get_13e24(void)
{
    return (void *)0;            /* *unaff_x20 */
}

/* FUN_00213e58 @ 0x00213e58   (est. sk_vspace_obj_alloc_13e58)
 * Ghidra: void FUN_00213e58(void)
 * Object alloc/free dispatcher: checks a runtime predicate (FUN_003a261c);
 * on false frees an object and relinks the free list, else invokes a vtable
 * method @+0x118. Confidence: low (PAC).
 * Notes: Ghidra artifacts: FUN_003a261c, (*in_x4 + 0x118) indirect, sk_free. */
void sk_vspace_obj_alloc_13e58(void)
{
    sk_frame_enter();            /* FUN_00084220 */
    rt_356048();                 /* FUN_00356048 */
    rt_35583c();                 /* FUN_0035583c */
    if (rt_3a261c() == 0) {      /* FUN_003a261c */
        rt_351280(0,0);          /* FUN_00351280 */
        rt_356140();             /* FUN_00356140 */
        ((void (*volatile)())0)(); /* (*in_x6)() */
        rt_351f28();             /* FUN_00351f28 */
        sk_free(0);
        sk_alloc_pages(0,0);     /* FUN_0036b270 (relink) */
    } else {
        (*(void (**volatile)())(*(void **volatile)0 + 0x118))();   /* vtable +0x118 */
    }
    sk_frame_leave();            /* FUN_00084234 */
}

/* FUN_00213f3c @ 0x00213f3c   (est. sk_vspace_obj_alloc_13f3c)
 * Ghidra: void FUN_00213f3c(void)
 * Object allocator: FUN_00352e84 then indirect call storing 16-byte value.
 * Confidence: low (PAC).
 * Notes: Ghidra artifacts: (*in_x3)(..) indirect. */
void sk_vspace_obj_alloc_13f3c(void)
{
    rt_352e84();                 /* FUN_00352e84 */
    ((void (*volatile)())0)(0,0,0);/* (*in_x3)() */
}

/* FUN_00213f88 @ 0x00213f88   (est. sk_vspace_obj_alloc_13f88)
 * Ghidra: void FUN_00213f88(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,code *param_5)
 * Object allocator: FUN_00352e84 then indirect call (param_5). Confidence: low.
 * Notes: Ghidra artifacts: (*param_5)(extraout_x8) indirect. */
void sk_vspace_obj_alloc_13f88(void *a, void *b, void *c, void *d, void *e)
{
    (void)d;
    rt_352e84(a, b, b);          /* FUN_00352e84 */
    (*(void (**)())e)(0);    /* (*param_5)() */
    (void)c;
}

/* FUN_00213fd8 @ 0x00213fd8   (est. sk_vspace_obj_alloc_13fd8)
 * Ghidra: void FUN_00213fd8(undefined8 param_1,undefined8 param_2,undefined8 *param_3)
 * Object allocator: FUN_00352e84 then indirect call through 6 args.
 * Confidence: low (PAC).
 * Notes: Ghidra artifacts: (*extraout_x9)(..) indirect. */
void sk_vspace_obj_alloc_13fd8(void *a, void *b, void *c)
{
    (void)a; (void)b; (void)c;
    rt_352e84();                 /* FUN_00352e84 */
    ((void (*volatile)())0)(0,0,0,0,0,0);
}

/* FUN_0021401c @ 0x0021401c   (est. sk_vspace_obj_alloc_1401c)
 * Ghidra: undefined * FUN_0021401c(long *param_1, undefined8 *param_2, long param_3)
 * Object allocator (mirror of FUN_00213c58, tag 0xf7b7, init FUN_00214094).
 * Confidence: high (small, locally coherent).
 * Notes: Ghidra artifacts: FUN_0036a908(0x28,0xf7b7), &DAT_003471a4. */
void *sk_vspace_obj_alloc_1401c(void *a, void *b, void *c)
{
    (void)b;
    void *obj = sk_alloc(0x28, 0xf7b7);   /* FUN_0036a908 */
    *(void **)a = obj;
    sk_vspace_obj_alloc_14094(obj, 0, 0, 0, *(void **)((char *)c + 0x10));
    *(void **)((char *)obj + 0x20) = (void *)0;
    return (void *)0;            /* &DAT_003471a4 */
}

/* FUN_00214094 @ 0x00214094   (est. sk_vspace_obj_alloc_14094)
 * Ghidra: undefined1 [16] FUN_00214094(long *param_1,undefined8 param_2,undefined8 param_3,long *param_4,long param_5)
 * Object initializer (mirror of FUN_00213cd0, tag 0x894b). Confidence: high.
 * Notes: Ghidra artifacts: FUN_0036a908(..,0x894b), &DAT_003471a8. */
void sk_vspace_obj_alloc_14094(void *a, void *b, void *c, void *d, void *e)
{
    (void)b; (void)c; (void)d;
    void **obj = a;
    obj[0] = e;
    void *vt = *(void **)((char *)e - 8);
    obj[1] = vt;
    void *node = sk_alloc((unsigned long)*(void **)((char *)vt + 0x40), 0x894b);  /* FUN_0036a908 */
    obj[2] = node;
    (**(void (**)())(*(void **)d + 0xe8))(node, b, c);
}

/* FUN_0021416c @ 0x0021416c   (est. sk_vspace_obj_alloc_1416c)
 * Ghidra: void FUN_0021416c(void)
 * Object allocator: FUN_00352e84 then indirect call through the 16-byte
 * value returned. Confidence: low (PAC).
 * Notes: Ghidra artifacts: (*extraout_x9)(..) indirect. */
void sk_vspace_obj_alloc_1416c(void)
{
    rt_352e84();                 /* FUN_00352e84 */
    ((void (*volatile)())0)(0,0,0,0,0);
}

/* FUN_002141d8 @ 0x002141d8   (est. sk_vspace_obj_alloc_141d8)
 * Ghidra: long FUN_002141d8(undefined8 param_1,undefined8 param_2,code *param_3)
 * Object allocator returning success: FUN_00351894, invoke callback, then
 * FUN_00362acc gate; frees on miss and returns 0. Confidence: medium.
 * Notes: Ghidra artifacts: (*param_3)() callback, sk_free, FUN_00362acc. */
long sk_vspace_obj_alloc_141d8(void *a, void *b, void *c)
{
    (void)a; (void)b;
    rt_351894();                 /* FUN_00351894 */
    (*(void (**)())c)();     /* (*param_3)() */
    rt_353a30();                 /* FUN_00353a30 */
    if (rt_362acc() == 0) {      /* FUN_00362acc */
        sk_free(0);
        return 0;
    }
    return (long)rt_362acc();    /* lVar1 */
}

/* FUN_00214218 @ 0x00214218   (est. sk_vspace_obj_dtor_14218)
 * Ghidra: void FUN_00214218(void)
 * Object method-dispatch teardown: vtable method @+0xe8. Confidence: low.
 * Notes: Ghidra: (**(code **)(extraout_x16 + 0xe8))(). */
void sk_vspace_obj_dtor_14218(void)
{
    rt_353ea0();                 /* FUN_00353ea0 */
    (**(void (**)())(0 + 0xe8))();   /* vtable +0xe8 */
}

/* FUN_00214250 @ 0x00214250   (est. sk_vspace_obj_dtor_14250)
 * Ghidra: void FUN_00214250(void)
 * Object method-dispatch teardown: vtable method @+0x138. Confidence: low.
 * Notes: Ghidra: (**(code **)(*in_x4 + 0x138))(). */
void sk_vspace_obj_dtor_14250(void)
{
    (*(void (**volatile)())(*(void **volatile)0 + 0x138))();   /* vtable +0x138 */
}

/* FUN_00214294 @ 0x00214294   (est. sk_vspace_obj_dtor_14294)
 * Ghidra: void FUN_00214294(void)
 * Object method-dispatch teardown: vtable method @+0xf0. Confidence: low.
 * Notes: Ghidra: (**(code **)(extraout_x16 + 0xf0))(). */
void sk_vspace_obj_dtor_14294(void)
{
    rt_353ea0();                 /* FUN_00353ea0 */
    (**(void (**)())(0 + 0xf0))();   /* vtable +0xf0 */
}

/* FUN_002142cc @ 0x002142cc   (est. sk_vspace_obj_dtor_142cc)
 * Ghidra: void FUN_002142cc(void)
 * Object teardown with runtime predicate (FUN_003a261c); on false invokes
 * vtable @+0xf0 + free + relink; else vtable @+0xf8. Confidence: low (PAC).
 * Notes: Ghidra artifacts: FUN_003a261c, (**(code **)(*x20+0xf0/0xf8))(). */
void sk_vspace_obj_dtor_142cc(void)
{
    rt_350c5c();                 /* FUN_00350c5c */
    if (rt_3a261c() == 0) {      /* FUN_003a261c */
        (*(void (**volatile)())(*(void **volatile)0 + 0xf0))(0,0);   /* vtable +0xf0 */
        rt_34f584();             /* FUN_0034f584 */
        sk_free(0);
    } else {
        (*(void (**volatile)())(*(void **volatile)0 + 0xf8))(0);   /* vtable +0xf8 */
    }
}

/* FUN_00214344 @ 0x00214344   (est. sk_vspace_obj_dtor_14344)
 * Ghidra: void FUN_00214344(void)
 * Object method-dispatch teardown: vtable method @+0x100. Confidence: low.
 * Notes: Ghidra: (**(code **)(*in_x3 + 0x100))(). */
void sk_vspace_obj_dtor_14344(void)
{
    (*(void (**volatile)())(*(void **volatile)0 + 0x100))();   /* vtable +0x100 */
}

/* FUN_00214388 @ 0x00214388   (est. sk_vspace_obj_dtor_14388)
 * Ghidra: void FUN_00214388(void)
 * Object method-dispatch teardown: vtable method @+0x108. Confidence: low.
 * Notes: Ghidra: (**(code **)(*in_x5 + 0x108))(). */
void sk_vspace_obj_dtor_14388(void)
{
    (*(void (**volatile)())(*(void **volatile)0 + 0x108))();   /* vtable +0x108 */
}

/* FUN_002143d4 @ 0x002143d4   (est. sk_vspace_obj_dtor_143d4)
 * Ghidra: void FUN_002143d4(void)
 * Object teardown with runtime predicate (FUN_003a261c); on false invokes
 * vtable @+0x100 + free + relink; else vtable @+0x110. Confidence: low (PAC).
 * Notes: Ghidra artifacts: FUN_003a261c, (**(code **)(x16+0x100/0x110))(). */
void sk_vspace_obj_dtor_143d4(void)
{
    rt_350b0c();                 /* FUN_00350b0c */
    rt_352b20();                 /* FUN_00352b20 */
    if ((int)rt_3a261c() == 0) { /* FUN_003a261c */
        void *v = (void *)0;
        /* FUN_000027e8 */
        (**(void (**)())(0 + 0x100))(v);   /* vtable +0x100 */
        rt_350b90();             /* FUN_00350b90 */
        sk_free(v);
    } else {
        (*(void (**volatile)())(*(void **volatile)0 + 0x110))();   /* vtable +0x110 */
    }
}

/* FUN_00214474 @ 0x00214474   (est. sk_vspace_obj_dtor_14474)
 * Ghidra: void FUN_00214474(void)
 * Object method-dispatch teardown: vtable method @+0x120. Confidence: low.
 * Notes: Ghidra: (**(code **)(*in_x4 + 0x120))(). */
void sk_vspace_obj_dtor_14474(void)
{
    (*(void (**volatile)())(*(void **volatile)0 + 0x120))();   /* vtable +0x120 */
}

/* FUN_002144b8 @ 0x002144b8   (est. sk_vspace_obj_dtor_144b8)
 * Ghidra: void FUN_002144b8(void)
 * Object method-dispatch teardown: vtable method @+0x128. Confidence: low.
 * Notes: Ghidra: (**(code **)(extraout_x16 + 0x128))(). */
void sk_vspace_obj_dtor_144b8(void)
{
    sk_nop_01();                 /* FUN_0007c198 */
    (**(void (**)())(0 + 0x128))();   /* vtable +0x128 */
}

/* FUN_002144fc @ 0x002144fc   (est. sk_vspace_obj_dtor_144fc)
 * Ghidra: void FUN_002144fc(void)
 * Object method-dispatch teardown: vtable method @+0x148. Confidence: low.
 * Notes: Ghidra: (**(void (**)())(extraout_x16 + 0x148))(). */
void sk_vspace_obj_dtor_144fc(void)
{
    rt_353ea0();                 /* FUN_00353ea0 */
    (**(void (**)())(0 + 0x148))();   /* vtable +0x148 */
}

/* FUN_00214540 @ 0x00214540   (est. sk_vspace_obj_dtor_14540)
 * Ghidra: void FUN_00214540(void)
 * Object teardown with runtime predicate (FUN_003a261c); on false invokes
 * vtable @+0x148 + free + relink; else vtable @+0x150. Confidence: low (PAC).
 * Notes: Ghidra artifacts: FUN_003a261c, (**(code **)(lVar3+0x148/0x150))(). */
void sk_vspace_obj_dtor_14540(void)
{
    rt_350c5c();                 /* FUN_00350c5c */
    int rc = rt_3a261c();        /* FUN_003a261c */
    void *vt = (void *)0;        /* *unaff_x20 */
    if (rc == 0) {
        (**(void (**)())(vt + 0x148))(vt + 0x148, 0, 0);
        rt_34f584();             /* FUN_0034f584 */
        sk_free(0);
    } else {
        (**(void (**)())(vt + 0x150))(vt + 0x150, 0);
    }
}

/* FUN_002145e8 @ 0x002145e8   (est. sk_vspace_obj_alloc_145e8)
 * Ghidra: undefined * FUN_002145e8(long *param_1, undefined8 *param_2, long param_3)
 * Object allocator (mirror of FUN_00213c58, tag 0x843d, init FUN_00214660).
 * Confidence: high (small, locally coherent).
 * Notes: Ghidra artifacts: FUN_0036a908(0x28,0x843d), &DAT_003471a4. */
void *sk_vspace_obj_alloc_145e8(void *a, void *b, void *c)
{
    (void)b;
    void *obj = sk_alloc(0x28, 0x843d);   /* FUN_0036a908 */
    *(void **)a = obj;
    sk_vspace_obj_alloc_14660(obj, 0, 0, 0, *(void **)((char *)c + 0x10));
    *(void **)((char *)obj + 0x20) = (void *)0;
    return (void *)0;            /* &DAT_003471a4 */
}

/* FUN_00214660 @ 0x00214660   (est. sk_vspace_obj_alloc_14660)
 * Ghidra: undefined1 [16] FUN_00214660(long *param_1,undefined8 param_2,undefined8 param_3,long *param_4,long param_5)
 * Object initializer (mirror of FUN_00213cd0, tag 0x7ec4). Confidence: high.
 * Notes: Ghidra artifacts: FUN_0036a908(..,0x7ec4), &DAT_003471a8. */
void sk_vspace_obj_alloc_14660(void *a, void *b, void *c, void *d, void *e)
{
    (void)b; (void)c; (void)d;
    void **obj = a;
    obj[0] = e;
    void *vt = *(void **)((char *)e - 8);
    obj[1] = vt;
    void *node = sk_alloc((unsigned long)*(void **)((char *)vt + 0x40), 0x7ec4);  /* FUN_0036a908 */
    obj[2] = node;
    (**(void (**)())(*(void **)d + 0xe8))(node, b, c);
}

/* FUN_00214720 @ 0x00214720   (est. sk_vspace_obj_dtor_14720)
 * Ghidra: void FUN_00214720(undefined8 *param_1)
 * Object teardown: vtable method @+0x48, runtime helpers, free, and stores
 * unaff_x21 into param_1. Confidence: low (PAC).
 * Notes: Ghidra artifacts: (**(code **)(extraout_x16 + 0x48))(), sk_free. */
void sk_vspace_obj_dtor_14720(void *a)
{
    rt_34b7f4();                 /* FUN_0034b7f4 */
    (**(void (**)())(0 + 0x48))();   /* vtable +0x48 */
    rt_356328();                 /* FUN_00356328 */
    sk_free(0);
    *(void **)a = 0;             /* *param_1 = unaff_x21 */
}
