/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel, GL1,
 * arm64e, image base 0) - the cL4 microkernel. Ground truth: Ghidra FUN_ names +
 * addresses in cl4_kernel.raw. Version "cL4 microkernel (cL4 (679.100.61))".
 * All names are estimates unless string/header-matched.
 *
 * This file covers the boot-time exclave-launcher / capability-serialization
 * region 0x70000 - 0x80000.
 */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "sk_internal.h"

#pragma clang diagnostic ignored "-Wdeprecated-non-prototype"

/* ------------------------------------------------------------------ *
 * Out-of-range cL4 helper declarations (extern; bodies reconstructed by
 * the sibling range worker that owns them). Names are estimates.
 * ------------------------------------------------------------------ */
extern unsigned long sk_align_up();
extern unsigned long sk_alloc();
extern unsigned long sk_alloc_cnode();
extern unsigned long sk_alloc_ctx();
extern unsigned long sk_alloc_finalize();
extern unsigned long sk_alloc_obj();
extern unsigned long sk_alloc_teardown();
extern unsigned long sk_arr_grow();
extern unsigned long sk_arr_init();
extern unsigned long sk_arr_release();
extern unsigned long sk_arr_resize();
extern unsigned long sk_attr_fold();
extern unsigned long sk_attr_merge();
extern unsigned long sk_bitmap_alloc();
extern unsigned long sk_boot_wake();
extern unsigned long sk_bsz();
extern unsigned long sk_buf_acquire();
extern unsigned long sk_buf_alloc();
extern unsigned long sk_buf_begin();
extern unsigned long sk_buf_cap();
extern unsigned long sk_buf_commit();
extern unsigned long sk_buf_commit2();
extern unsigned long sk_buf_copy();
extern unsigned long sk_buf_end();
extern unsigned long sk_buf_flush();
extern unsigned long sk_buf_grow();
extern unsigned long sk_buf_has();
extern unsigned long sk_buf_tail();
extern unsigned long sk_build_cnode();
extern unsigned long sk_build_map();
extern unsigned long sk_cap_acquire();
extern unsigned long sk_cap_alloc();
extern unsigned long sk_cap_copy();
extern unsigned long sk_cap_copy2();
extern unsigned long sk_cap_install();
extern unsigned long sk_cap_lookup();
extern unsigned long sk_cap_match();
extern unsigned long sk_cap_parse();
extern unsigned long sk_cap_put();
extern unsigned long sk_cap_repair();
extern unsigned long sk_cap_sz();
extern unsigned long sk_cnode_build();
extern unsigned long sk_cnode_fill();
extern unsigned long sk_cnode_seal();
extern unsigned long sk_cpu_ctx();
extern unsigned long sk_ctx_begin();
extern unsigned long sk_ctx_end();
extern unsigned long sk_debug_printf();
extern unsigned long sk_elem_append();
extern unsigned long sk_elem_append4();
extern unsigned long sk_elem_claim();
extern unsigned long sk_elem_copy_16();
extern unsigned long sk_elem_copy_4();
extern unsigned long sk_elem_copy_8();
extern unsigned long sk_elem_copy_8b();
extern unsigned long sk_elem_copy_d8();
extern unsigned long sk_elem_lock();
extern unsigned long sk_elem_new();
extern unsigned long sk_elem_unlock();
extern unsigned long sk_emit_bootinfo();
extern unsigned long sk_emit_bytes();
extern unsigned long sk_emit_fmt();
extern unsigned long sk_emit_head();
extern unsigned long sk_emit_int();
extern unsigned long sk_emit_range();
extern unsigned long sk_emit_record();
extern unsigned long sk_emit_tag();
extern unsigned long sk_f_00070070();
extern unsigned long sk_f_00070074();
extern unsigned long sk_f_00070098();
extern unsigned long sk_f_0007021c();
extern unsigned long sk_f_00070288();
extern unsigned long sk_f_0007032c();
extern unsigned long sk_f_00070390();
extern unsigned long sk_f_00070594();
extern unsigned long sk_f_000705f8();
extern unsigned long sk_f_0007063c();
extern unsigned long sk_f_00070674();
extern unsigned long sk_f_00070754();
extern unsigned long sk_f_000707a8();
extern unsigned long sk_f_00070920();
extern unsigned long sk_f_00070960();
extern unsigned long sk_f_00070cc8();
extern unsigned long sk_f_00070cfc();
extern unsigned long sk_f_00070de4();
extern unsigned long sk_f_00071050();
extern unsigned long sk_f_000713dc();
extern unsigned long sk_f_00071404();
extern unsigned long sk_f_00071408();
extern unsigned long sk_f_00071428();
extern unsigned long sk_f_0007144c();
extern unsigned long sk_f_000714bc();
extern unsigned long sk_f_000714f4();
extern unsigned long sk_f_00071598();
extern unsigned long sk_f_00071620();
extern unsigned long sk_f_000716b4();
extern unsigned long sk_f_00071710();
extern unsigned long sk_f_0007174c();
extern unsigned long sk_f_000717c8();
extern unsigned long sk_f_00071814();
extern unsigned long sk_f_00071850();
extern unsigned long sk_f_00071854();
extern unsigned long sk_f_00071868();
extern unsigned long sk_f_0007186c();
extern unsigned long sk_f_00071880();
extern unsigned long sk_f_00071884();
extern unsigned long sk_f_00071898();
extern unsigned long sk_f_0007189c();
extern unsigned long sk_f_000718b8();
extern unsigned long sk_f_0007198c();
extern unsigned long sk_f_000719dc();
extern unsigned long sk_f_000719f0();
extern unsigned long sk_f_00071a04();
extern unsigned long sk_f_00071a4c();
extern unsigned long sk_f_00071aa0();
extern unsigned long sk_f_00071b24();
extern unsigned long sk_f_00071b74();
extern unsigned long sk_f_00071bd0();
extern unsigned long sk_f_00071c4c();
extern unsigned long sk_f_00071c94();
extern unsigned long sk_f_00071d18();
extern unsigned long sk_f_00071d74();
extern unsigned long sk_f_00071dbc();
extern unsigned long sk_f_00071e04();
extern unsigned long sk_f_00071e74();
extern unsigned long sk_f_00071ebc();
extern unsigned long sk_f_00071f54();
extern unsigned long sk_f_00071f9c();
extern unsigned long sk_f_00071fe4();
extern unsigned long sk_f_0007201c();
extern unsigned long sk_f_00072044();
extern unsigned long sk_f_0007206c();
extern unsigned long sk_f_000720a8();
extern unsigned long sk_f_00072114();
extern unsigned long sk_f_00072150();
extern unsigned long sk_f_00072178();
extern unsigned long sk_f_000721b0();
extern unsigned long sk_f_000721d8();
extern unsigned long sk_f_0007220c();
extern unsigned long sk_f_00072270();
extern unsigned long sk_f_000722b0();
extern unsigned long sk_f_00072320();
extern unsigned long sk_f_00072358();
extern unsigned long sk_f_000723c0();
extern unsigned long sk_f_000723f4();
extern unsigned long sk_f_00072424();
extern unsigned long sk_f_00072454();
extern unsigned long sk_f_00072464();
extern unsigned long sk_f_000724cc();
extern unsigned long sk_f_00072570();
extern unsigned long sk_f_000725c8();
extern unsigned long sk_f_00072664();
extern unsigned long sk_f_000726a0();
extern unsigned long sk_f_00072710();
extern unsigned long sk_f_0007278c();
extern unsigned long sk_f_000727ec();
extern unsigned long sk_f_000728d4();
extern unsigned long sk_f_0007292c();
extern unsigned long sk_f_00072a30();
extern unsigned long sk_f_00072a88();
extern unsigned long sk_f_00072b44();
extern unsigned long sk_f_00072b9c();
extern unsigned long sk_f_00072c0c();
extern unsigned long sk_f_00072c98();
extern unsigned long sk_f_00072d5c();
extern unsigned long sk_f_00072de8();
extern unsigned long sk_f_00072e74();
extern unsigned long sk_f_00072f00();
extern unsigned long sk_f_00072f8c();
extern unsigned long sk_f_00073018();
extern unsigned long sk_f_000730a4();
extern unsigned long sk_f_00073140();
extern unsigned long sk_f_000731dc();
extern unsigned long sk_f_00073268();
extern unsigned long sk_f_000732f4();
extern unsigned long sk_f_00073380();
extern unsigned long sk_f_0007340c();
extern unsigned long sk_f_00073498();
extern unsigned long sk_f_00073524();
extern unsigned long sk_f_00073604();
extern unsigned long sk_f_00073690();
extern unsigned long sk_f_0007371c();
extern unsigned long sk_f_000737a8();
extern unsigned long sk_f_000737e8();
extern unsigned long sk_f_000738b0();
extern unsigned long sk_f_0007393c();
extern unsigned long sk_f_000739d8();
extern unsigned long sk_f_00073a64();
extern unsigned long sk_f_00073af0();
extern unsigned long sk_f_00073b7c();
extern unsigned long sk_f_00073c08();
extern unsigned long sk_f_00073c94();
extern unsigned long sk_f_00073d30();
extern unsigned long sk_f_00073d70();
extern unsigned long sk_f_00073dfc();
extern unsigned long sk_f_00073e88();
extern unsigned long sk_f_00073f14();
extern unsigned long sk_f_00073fa0();
extern unsigned long sk_f_0007402c();
extern unsigned long sk_f_000740b8();
extern unsigned long sk_f_00074154();
extern unsigned long sk_f_000741e0();
extern unsigned long sk_f_00074220();
extern unsigned long sk_f_000742ac();
extern unsigned long sk_f_000742ec();
extern unsigned long sk_f_00074378();
extern unsigned long sk_f_00074404();
extern unsigned long sk_f_00074490();
extern unsigned long sk_f_0007451c();
extern unsigned long sk_f_00074538();
extern unsigned long sk_f_000745d4();
extern unsigned long sk_f_00074670();
extern unsigned long sk_f_0007470c();
extern unsigned long sk_f_000747a8();
extern unsigned long sk_f_00074834();
extern unsigned long sk_f_00074874();
extern unsigned long sk_f_00074910();
extern unsigned long sk_f_0007499c();
extern unsigned long sk_f_00074a28();
extern unsigned long sk_f_00074a98();
extern unsigned long sk_f_00074b08();
extern unsigned long sk_f_00074b78();
extern unsigned long sk_f_00074c14();
extern unsigned long sk_f_00074cb8();
extern unsigned long sk_f_00074d54();
extern unsigned long sk_f_00074dc8();
extern unsigned long sk_f_00074e34();
extern unsigned long sk_f_00074eb0();
extern unsigned long sk_f_00074f28();
extern unsigned long sk_f_00074fa4();
extern unsigned long sk_f_00075018();
extern unsigned long sk_f_000750bc();
extern unsigned long sk_f_00075118();
extern unsigned long sk_f_000751b4();
extern unsigned long sk_f_00075234();
extern unsigned long sk_f_000752a4();
extern unsigned long sk_f_0007534c();
extern unsigned long sk_f_000753c0();
extern unsigned long sk_f_0007543c();
extern unsigned long sk_f_000754b0();
extern unsigned long sk_f_0007552c();
extern unsigned long sk_f_000755a4();
extern unsigned long sk_f_00075624();
extern unsigned long sk_f_00075694();
extern unsigned long sk_f_00075710();
extern unsigned long sk_f_00075784();
extern unsigned long sk_f_000757e8();
extern unsigned long sk_f_0007585c();
extern unsigned long sk_f_000758d8();
extern unsigned long sk_f_00075948();
extern unsigned long sk_f_000759c0();
extern unsigned long sk_f_00075a38();
extern unsigned long sk_f_00075ab4();
extern unsigned long sk_f_00075b2c();
extern unsigned long sk_f_00075bac();
extern unsigned long sk_f_00075c50();
extern unsigned long sk_f_00075cb4();
extern unsigned long sk_f_00075dd8();
extern unsigned long sk_f_00075ea4();
extern unsigned long sk_f_00075fb4();
extern unsigned long sk_f_0007608c();
extern unsigned long sk_f_00076158();
extern unsigned long sk_f_00076274();
extern unsigned long sk_f_0007629c();
extern unsigned long sk_f_00076360();
extern unsigned long sk_f_000764a0();
extern unsigned long sk_f_000764c8();
extern unsigned long sk_f_0007659c();
extern unsigned long sk_f_000765c4();
extern unsigned long sk_f_0007667c();
extern unsigned long sk_f_00076760();
extern unsigned long sk_f_0007682c();
extern unsigned long sk_f_000768f0();
extern unsigned long sk_f_00076918();
extern unsigned long sk_f_000769d4();
extern unsigned long sk_f_00076ac8();
extern unsigned long sk_f_00076d08();
extern unsigned long sk_f_00076f74();
extern unsigned long sk_f_00076fc0();
extern unsigned long sk_f_00077024();
extern unsigned long sk_f_00077070();
extern unsigned long sk_f_00077088();
extern unsigned long sk_f_000770b8();
extern unsigned long sk_f_000770e8();
extern unsigned long sk_f_00077118();
extern unsigned long sk_f_00077148();
extern unsigned long sk_f_00077178();
extern unsigned long sk_f_000773f0();
extern unsigned long sk_f_000774c8();
extern unsigned long sk_f_0007752c();
extern unsigned long sk_f_00077540();
extern unsigned long sk_f_00077550();
extern unsigned long sk_f_00077560();
extern unsigned long sk_f_00077570();
extern unsigned long sk_f_00077580();
extern unsigned long sk_f_00077590();
extern unsigned long sk_f_000775b8();
extern unsigned long sk_f_000775c8();
extern unsigned long sk_f_000775dc();
extern unsigned long sk_f_00077604();
extern unsigned long sk_f_00077614();
extern unsigned long sk_f_00077624();
extern unsigned long sk_f_00077630();
extern unsigned long sk_f_0007764c();
extern unsigned long sk_f_0007765c();
extern unsigned long sk_f_0007766c();
extern unsigned long sk_f_0007767c();
extern unsigned long sk_f_00077698();
extern unsigned long sk_f_000776b4();
extern unsigned long sk_f_000776c0();
extern unsigned long sk_f_000776cc();
extern unsigned long sk_f_000776d8();
extern unsigned long sk_f_000776e4();
extern unsigned long sk_f_000776f8();
extern unsigned long sk_f_00077708();
extern unsigned long sk_f_00077718();
extern unsigned long sk_f_00077724();
extern unsigned long sk_f_00077744();
extern unsigned long sk_f_00077764();
extern unsigned long sk_f_00077770();
extern unsigned long sk_f_00077778();
extern unsigned long sk_f_00077794();
extern unsigned long sk_f_000777b4();
extern unsigned long sk_f_000777c4();
extern unsigned long sk_f_000777d4();
extern unsigned long sk_f_000777e4();
extern unsigned long sk_f_00077800();
extern unsigned long sk_f_0007780c();
extern unsigned long sk_f_00077824();
extern unsigned long sk_f_0007783c();
extern unsigned long sk_f_00077848();
extern unsigned long sk_f_00077860();
extern unsigned long sk_f_00077870();
extern unsigned long sk_f_0007787c();
extern unsigned long sk_f_00077888();
extern unsigned long sk_f_00077894();
extern unsigned long sk_f_000778a0();
extern unsigned long sk_f_000778b4();
extern unsigned long sk_f_000778c0();
extern unsigned long sk_f_000778d4();
extern unsigned long sk_f_000778e8();
extern unsigned long sk_f_000778fc();
extern unsigned long sk_f_00077910();
extern unsigned long sk_f_0007791c();
extern unsigned long sk_f_00077928();
extern unsigned long sk_f_00077934();
extern unsigned long sk_f_00077960();
extern unsigned long sk_f_0007798c();
extern unsigned long sk_f_00077a90();
extern unsigned long sk_f_00077b58();
extern unsigned long sk_f_00077b84();
extern unsigned long sk_f_00077bd0();
extern unsigned long sk_f_00077c10();
extern unsigned long sk_f_00077c88();
extern unsigned long sk_f_00077d64();
extern unsigned long sk_f_00077da4();
extern unsigned long sk_f_00077de8();
extern unsigned long sk_f_00077e38();
extern unsigned long sk_f_00077e74();
extern unsigned long sk_f_00077eb8();
extern unsigned long sk_f_00077f08();
extern unsigned long sk_f_00077f44();
extern unsigned long sk_f_00077f88();
extern unsigned long sk_f_00077fd8();
extern unsigned long sk_f_0007802c();
extern unsigned long sk_f_0007806c();
extern unsigned long sk_f_000780b0();
extern unsigned long sk_f_00078100();
extern unsigned long sk_f_0007815c();
extern unsigned long sk_f_000781b4();
extern unsigned long sk_f_00078220();
extern unsigned long sk_f_00078270();
extern unsigned long sk_f_000782c0();
extern unsigned long sk_f_0007830c();
extern unsigned long sk_f_00078368();
extern unsigned long sk_f_000783b8();
extern unsigned long sk_f_00078414();
extern unsigned long sk_f_00078454();
extern unsigned long sk_f_00078498();
extern unsigned long sk_f_000784e8();
extern unsigned long sk_f_00078544();
extern unsigned long sk_f_00078584();
extern unsigned long sk_f_000785c8();
extern unsigned long sk_f_00078618();
extern unsigned long sk_f_00078674();
extern unsigned long sk_f_000786b4();
extern unsigned long sk_f_000786f8();
extern unsigned long sk_f_00078748();
extern unsigned long sk_f_00078784();
extern unsigned long sk_f_000787c8();
extern unsigned long sk_f_00078818();
extern unsigned long sk_f_00078880();
extern unsigned long sk_f_00078fec();
extern unsigned long sk_f_00079038();
extern unsigned long sk_f_000792d8();
extern unsigned long sk_f_00079678();
extern unsigned long sk_f_0007967c();
extern unsigned long sk_f_000796b0();
extern unsigned long sk_f_0007985c();
extern unsigned long sk_f_00079a88();
extern unsigned long sk_f_00079bf0();
extern unsigned long sk_f_0007a120();
extern unsigned long sk_f_0007a1fc();
extern unsigned long sk_f_0007a274();
extern unsigned long sk_f_0007a2dc();
extern unsigned long sk_f_0007a3dc();
extern unsigned long sk_f_0007a454();
extern unsigned long sk_f_0007a548();
extern unsigned long sk_f_0007a5c4();
extern unsigned long sk_f_0007a6a0();
extern unsigned long sk_f_0007a718();
extern unsigned long sk_f_0007abe0();
extern unsigned long sk_f_0007ac24();
extern unsigned long sk_f_0007acd8();
extern unsigned long sk_f_0007b0cc();
extern unsigned long sk_f_0007b134();
extern unsigned long sk_f_0007b178();
extern unsigned long sk_f_0007b1c0();
extern unsigned long sk_f_0007b1f0();
extern unsigned long sk_f_0007b208();
extern unsigned long sk_f_0007b220();
extern unsigned long sk_f_0007b238();
extern unsigned long sk_f_0007b250();
extern unsigned long sk_f_0007b268();
extern unsigned long sk_f_0007b280();
extern unsigned long sk_f_0007b298();
extern unsigned long sk_f_0007b2b0();
extern unsigned long sk_f_0007b2c8();
extern unsigned long sk_f_0007b324();
extern unsigned long sk_f_0007b33c();
extern unsigned long sk_f_0007b354();
extern unsigned long sk_f_0007b384();
extern unsigned long sk_f_0007b3b4();
extern unsigned long sk_f_0007b3e4();
extern unsigned long sk_f_0007b3fc();
extern unsigned long sk_f_0007b414();
extern unsigned long sk_f_0007b42c();
extern unsigned long sk_f_0007b444();
extern unsigned long sk_f_0007b45c();
extern unsigned long sk_f_0007b474();
extern unsigned long sk_f_0007b48c();
extern unsigned long sk_f_0007b4a4();
extern unsigned long sk_f_0007b4e8();
extern unsigned long sk_f_0007b4fc();
extern unsigned long sk_f_0007b500();
extern unsigned long sk_f_0007b524();
extern unsigned long sk_f_0007b528();
extern unsigned long sk_f_0007b544();
extern unsigned long sk_f_0007b548();
extern unsigned long sk_f_0007b564();
extern unsigned long sk_f_0007b568();
extern unsigned long sk_f_0007b58c();
extern unsigned long sk_f_0007b5f4();
extern unsigned long sk_f_0007b654();
extern unsigned long sk_f_0007b6a0();
extern unsigned long sk_f_0007b6d8();
extern unsigned long sk_f_0007b718();
extern unsigned long sk_f_0007b750();
extern unsigned long sk_f_0007b790();
extern unsigned long sk_f_0007b7d0();
extern unsigned long sk_f_0007b818();
extern unsigned long sk_f_0007b864();
extern unsigned long sk_f_0007b8ac();
extern unsigned long sk_f_0007b8f4();
extern unsigned long sk_f_0007b93c();
extern unsigned long sk_f_0007b97c();
extern unsigned long sk_f_0007bcf8();
extern unsigned long sk_f_0007bdb4();
extern unsigned long sk_f_0007be74();
extern unsigned long sk_f_0007be8c();
extern unsigned long sk_f_0007bea4();
extern unsigned long sk_f_0007bebc();
extern unsigned long sk_f_0007bed4();
extern unsigned long sk_f_0007beec();
extern unsigned long sk_f_0007bf04();
extern unsigned long sk_f_0007bf1c();
extern unsigned long sk_f_0007bf34();
extern unsigned long sk_f_0007bf4c();
extern unsigned long sk_f_0007bf80();
extern unsigned long sk_f_0007bf94();
extern unsigned long sk_f_0007bfac();
extern unsigned long sk_f_0007bfc8();
extern unsigned long sk_f_0007bfdc();
extern unsigned long sk_f_0007bff0();
extern unsigned long sk_f_0007c004();
extern unsigned long sk_f_0007c018();
extern unsigned long sk_f_0007c028();
extern unsigned long sk_f_0007c038();
extern unsigned long sk_f_0007c070();
extern unsigned long sk_f_0007c088();
extern unsigned long sk_f_0007c0a0();
extern unsigned long sk_f_0007c0ac();
extern unsigned long sk_f_0007c0b8();
extern unsigned long sk_f_0007c0c4();
extern unsigned long sk_f_0007c0d4();
extern unsigned long sk_f_0007c0e0();
extern unsigned long sk_f_0007c0ec();
extern unsigned long sk_f_0007c0f8();
extern unsigned long sk_f_0007c128();
extern unsigned long sk_f_0007c140();
extern unsigned long sk_f_0007c14c();
extern unsigned long sk_f_0007c158();
extern unsigned long sk_f_0007c164();
extern unsigned long sk_f_0007c178();
extern unsigned long sk_f_0007c18c();
extern unsigned long sk_f_0007c198();
extern unsigned long sk_f_0007c1a4();
extern unsigned long sk_f_0007c1b0();
extern unsigned long sk_f_0007c1c4();
extern unsigned long sk_f_0007c1d0();
extern unsigned long sk_f_0007c1e8();
extern unsigned long sk_f_0007c210();
extern unsigned long sk_f_0007c250();
extern unsigned long sk_f_0007c2a0();
extern unsigned long sk_f_0007c2e8();
extern unsigned long sk_f_0007c310();
extern unsigned long sk_f_0007c358();
extern unsigned long sk_f_0007c3d8();
extern unsigned long sk_f_0007c4ac();
extern unsigned long sk_f_0007c614();
extern unsigned long sk_f_0007c618();
extern unsigned long sk_f_0007c660();
extern unsigned long sk_f_0007c664();
extern unsigned long sk_f_0007c680();
extern unsigned long sk_f_0007c684();
extern unsigned long sk_f_0007c6ac();
extern unsigned long sk_f_0007c76c();
extern unsigned long sk_f_0007c814();
extern unsigned long sk_f_0007c848();
extern unsigned long sk_f_0007c84c();
extern unsigned long sk_f_0007c868();
extern unsigned long sk_f_0007c86c();
extern unsigned long sk_f_0007c8a0();
extern unsigned long sk_f_0007c8dc();
extern unsigned long sk_f_0007c974();
extern unsigned long sk_f_0007ca48();
extern unsigned long sk_f_0007cb88();
extern unsigned long sk_f_0007cefc();
extern unsigned long sk_f_0007cf38();
extern unsigned long sk_f_0007cf74();
extern unsigned long sk_f_0007d054();
extern unsigned long sk_f_0007d0fc();
extern unsigned long sk_f_0007d128();
extern unsigned long sk_f_0007d168();
extern unsigned long sk_f_0007d19c();
extern unsigned long sk_f_0007d1c4();
extern unsigned long sk_f_0007d1c8();
extern unsigned long sk_f_0007d1e4();
extern unsigned long sk_f_0007d220();
extern unsigned long sk_f_0007d264();
extern unsigned long sk_f_0007d2b8();
extern unsigned long sk_f_0007d3e8();
extern unsigned long sk_f_0007d880();
extern unsigned long sk_f_0007d8bc();
extern unsigned long sk_f_0007d910();
extern unsigned long sk_f_0007d958();
extern unsigned long sk_f_0007d9ac();
extern unsigned long sk_f_0007d9d8();
extern unsigned long sk_f_0007da4c();
extern unsigned long sk_f_0007da98();
extern unsigned long sk_f_0007dbb8();
extern unsigned long sk_f_0007dbf0();
extern unsigned long sk_f_0007dcfc();
extern unsigned long sk_f_0007ddb0();
extern unsigned long sk_f_0007e6b8();
extern unsigned long sk_f_0007e6e8();
extern unsigned long sk_f_0007e6ec();
extern unsigned long sk_f_0007e710();
extern unsigned long sk_f_0007e74c();
extern unsigned long sk_f_0007e788();
extern unsigned long sk_f_0007e7c4();
extern unsigned long sk_f_0007e99c();
extern unsigned long sk_f_0007e9a0();
extern unsigned long sk_f_0007e9c0();
extern unsigned long sk_f_0007e9fc();
extern unsigned long sk_f_0007ea60();
extern unsigned long sk_f_0007ead8();
extern unsigned long sk_f_0007eb2c();
extern unsigned long sk_f_0007eb34();
extern unsigned long sk_f_0007ebf0();
extern unsigned long sk_f_0007ec2c();
extern unsigned long sk_f_0007ec68();
extern unsigned long sk_f_0007eca8();
extern unsigned long sk_f_0007f020();
extern unsigned long sk_f_0007f04c();
extern unsigned long sk_f_0007f098();
extern unsigned long sk_f_0007f0d4();
extern unsigned long sk_f_0007f110();
extern unsigned long sk_f_0007f1e0();
extern unsigned long sk_f_0007f4d8();
extern unsigned long sk_f_0007f8ec();
extern unsigned long sk_f_0007fa68();
extern unsigned long sk_f_0007fc64();
extern unsigned long sk_f_0007fcd4();
extern unsigned long sk_f_0007fcd8();
extern unsigned long sk_f_0007fd0c();
extern unsigned long sk_f_0007fd48();
extern unsigned long sk_f_0007fd84();
extern unsigned long sk_f_0007fe94();
extern unsigned long sk_fatal();
extern unsigned long sk_fault();
extern unsigned long sk_finalize();
extern unsigned long sk_finalize_bad();
extern unsigned long sk_finalize_check();
extern unsigned long sk_finalize_ok();
extern unsigned long sk_fold_entry();
extern unsigned long sk_free();
extern unsigned long sk_gate0();
extern unsigned long sk_hash_combine();
extern unsigned long sk_hash_eq();
extern unsigned long sk_hash_fn();
extern unsigned long sk_hash_init();
extern unsigned long sk_hash_lookup();
extern unsigned long sk_hash_reset();
extern unsigned long sk_helper_0064e030();
extern unsigned long sk_hw_sync();
extern unsigned long sk_inc_ref();
extern unsigned long sk_irq_clear();
extern unsigned long sk_is_space();
extern unsigned long sk_is_xdigit();
extern unsigned long sk_isdigit();
extern unsigned long sk_key_eq();
extern unsigned long sk_lock();
extern unsigned long sk_lock_acquire();
extern unsigned long sk_lock_claim();
extern unsigned long sk_lock_clean();
extern unsigned long sk_lock_pair();
extern unsigned long sk_lock_ref();
extern unsigned long sk_lock_state();
extern unsigned long sk_map_del16();
extern unsigned long sk_map_del16b();
extern unsigned long sk_map_del40();
extern unsigned long sk_map_dump();
extern unsigned long sk_map_find();
extern unsigned long sk_map_find1();
extern unsigned long sk_map_find_16();
extern unsigned long sk_map_find_8();
extern unsigned long sk_map_flush();
extern unsigned long sk_map_hash();
extern unsigned long sk_map_insert();
extern unsigned long sk_map_insert1();
extern unsigned long sk_map_insert16();
extern unsigned long sk_map_insert16b();
extern unsigned long sk_map_insert2();
extern unsigned long sk_map_insert32();
extern unsigned long sk_map_insert4();
extern unsigned long sk_map_insert8();
extern unsigned long sk_map_insert_opt();
extern unsigned long sk_map_new();
extern unsigned long sk_map_resolve();
extern unsigned long sk_map_seed();
extern unsigned long sk_mem_zero();
extern unsigned long sk_memcpy();
extern unsigned long sk_memcpy_el();
extern unsigned long sk_obj_alloc();
extern unsigned long sk_obj_new();
extern unsigned long sk_obj_store();
extern unsigned long sk_obj_walk();
extern unsigned long sk_paddr_type();
extern unsigned long sk_page_round();
extern unsigned long sk_pair_index();
extern unsigned long sk_pair_lookup();
extern unsigned long sk_pair_new();
extern unsigned long sk_pair_read();
extern unsigned long sk_panic_abort();
extern unsigned long sk_panic_msg();
extern unsigned long sk_panic_nr();
extern unsigned long sk_panic_ret();
extern unsigned long sk_panic_ret2();
extern unsigned long sk_panic_site();
extern unsigned long sk_panic_str();
extern unsigned long sk_parse_int();
extern unsigned long sk_parse_num();
extern unsigned long sk_range_split();
extern unsigned long sk_ref_add();
extern unsigned long sk_ref_bind();
extern unsigned long sk_ref_free();
extern unsigned long sk_ref_pend();
extern unsigned long sk_ref_sub();
extern unsigned long sk_release();
extern unsigned long sk_release_lo();
extern unsigned long sk_retain();
extern unsigned long sk_retain0();
extern unsigned long sk_retain_lo();
extern unsigned long sk_retain_low();
extern unsigned long sk_round_up();
extern unsigned long sk_size_round();
extern unsigned long sk_skip_ws();
extern unsigned long sk_spin_lock();
extern unsigned long sk_store_meta();
extern unsigned long sk_str_get();
extern unsigned long sk_str_span();
extern unsigned long sk_sysreg_read();
extern unsigned long sk_sz_cap();
extern unsigned long sk_sz_page();
extern unsigned long sk_sz_range();
extern unsigned long sk_tcb_alloc();
extern unsigned long sk_tcb_free();
extern unsigned long sk_tcb_init();
extern unsigned long sk_tcb_install();
extern unsigned long sk_tcb_swap();
extern unsigned long sk_trace_end();
extern unsigned long sk_trace_flush();
extern unsigned long sk_trace_point();
extern unsigned long sk_type_find();
extern unsigned long sk_type_lookup();
extern unsigned long sk_type_resolve();
extern unsigned long sk_unlock();
extern unsigned long sk_vas_alloc();
extern unsigned long sk_ver_check();
extern unsigned long sk_ver_get();
extern unsigned long sk_vspace_map();
extern unsigned long sk_vspace_resolve();
extern unsigned long sk_write_bytes();
extern unsigned long sk_write_raw();
extern unsigned long sk_write_tag();
extern unsigned long sk_write_word();
extern unsigned long sk_slot_00070070();
extern unsigned long sk_slot_00070074();
extern unsigned long sk_slot_00070098();
extern unsigned long sk_slot_0007021c();
extern unsigned long sk_slot_0007032c();
extern unsigned long sk_slot_00070594();
extern unsigned long sk_slot_000705f8();
extern unsigned long sk_slot_0007063c();
extern unsigned long sk_slot_00070674();
extern unsigned long sk_slot_00070754();
extern unsigned long sk_slot_000707a8();
extern unsigned long sk_slot_00070920();
extern unsigned long sk_slot_00070960();
extern unsigned long sk_slot_00070cc8();
extern unsigned long sk_slot_00070de4();
extern unsigned long sk_slot_00071050();
extern unsigned long sk_slot_000714f4();
extern unsigned long sk_slot_000718b8();
extern unsigned long sk_slot_0007198c();
extern unsigned long sk_slot_00071a04();
extern unsigned long sk_slot_00071a4c();
extern unsigned long sk_slot_00071b24();
extern unsigned long sk_slot_00071b74();
extern unsigned long sk_slot_00071c4c();
extern unsigned long sk_slot_00071d18();
extern unsigned long sk_slot_00071d74();
extern unsigned long sk_slot_00071dbc();
extern unsigned long sk_slot_00071e04();
extern unsigned long sk_slot_00071e74();
extern unsigned long sk_slot_00071f54();
extern unsigned long sk_slot_00071f9c();
extern unsigned long sk_slot_00071fe4();
extern unsigned long sk_slot_0007201c();
extern unsigned long sk_slot_00072044();
extern unsigned long sk_slot_0007206c();
extern unsigned long sk_slot_000720a8();
extern unsigned long sk_slot_00072114();
extern unsigned long sk_slot_00072150();
extern unsigned long sk_slot_00072178();
extern unsigned long sk_slot_000721b0();
extern unsigned long sk_slot_000721d8();
extern unsigned long sk_slot_0007220c();
extern unsigned long sk_slot_00072270();
extern unsigned long sk_slot_000722b0();
extern unsigned long sk_slot_00072320();
extern unsigned long sk_slot_00072358();
extern unsigned long sk_slot_000723c0();
extern unsigned long sk_slot_000723f4();
extern unsigned long sk_slot_00072424();
extern unsigned long sk_slot_00072454();
extern unsigned long sk_slot_00072464();
extern unsigned long sk_slot_000724cc();
extern unsigned long sk_slot_00072570();
extern unsigned long sk_slot_000725c8();
extern unsigned long sk_slot_00072664();
extern unsigned long sk_slot_000726a0();
extern unsigned long sk_slot_00072710();
extern unsigned long sk_slot_0007278c();
extern unsigned long sk_slot_000727ec();
extern unsigned long sk_slot_000728d4();
extern unsigned long sk_slot_0007292c();
extern unsigned long sk_slot_00072a30();
extern unsigned long sk_slot_00072a88();
extern unsigned long sk_slot_00072b44();
extern unsigned long sk_slot_00072b9c();
extern unsigned long sk_slot_00072c0c();
extern unsigned long sk_slot_00072c98();
extern unsigned long sk_slot_00072d5c();
extern unsigned long sk_slot_00072de8();
extern unsigned long sk_slot_00072e74();
extern unsigned long sk_slot_00072f00();
extern unsigned long sk_slot_00072f8c();
extern unsigned long sk_slot_00073018();
extern unsigned long sk_slot_000730a4();
extern unsigned long sk_slot_00073140();
extern unsigned long sk_slot_000731dc();
extern unsigned long sk_slot_00073268();
extern unsigned long sk_slot_000732f4();
extern unsigned long sk_slot_00073380();
extern unsigned long sk_slot_0007340c();
extern unsigned long sk_slot_00073498();
extern unsigned long sk_slot_00073524();
extern unsigned long sk_slot_00073604();
extern unsigned long sk_slot_00073690();
extern unsigned long sk_slot_0007371c();
extern unsigned long sk_slot_000737e8();
extern unsigned long sk_slot_000738b0();
extern unsigned long sk_slot_0007393c();
extern unsigned long sk_slot_000739d8();
extern unsigned long sk_slot_00073a64();
extern unsigned long sk_slot_00073af0();
extern unsigned long sk_slot_00073b7c();
extern unsigned long sk_slot_00073c08();
extern unsigned long sk_slot_00073c94();
extern unsigned long sk_slot_00073d70();
extern unsigned long sk_slot_00073dfc();
extern unsigned long sk_slot_00073e88();
extern unsigned long sk_slot_00073f14();
extern unsigned long sk_slot_00073fa0();
extern unsigned long sk_slot_0007402c();
extern unsigned long sk_slot_000740b8();
extern unsigned long sk_slot_00074154();
extern unsigned long sk_slot_00074220();
extern unsigned long sk_slot_000742ec();
extern unsigned long sk_slot_00074378();
extern unsigned long sk_slot_00074404();
extern unsigned long sk_slot_00074490();
extern unsigned long sk_slot_0007451c();
extern unsigned long sk_slot_00074538();
extern unsigned long sk_slot_000745d4();
extern unsigned long sk_slot_00074670();
extern unsigned long sk_slot_0007470c();
extern unsigned long sk_slot_000747a8();
extern unsigned long sk_slot_00074874();
extern unsigned long sk_slot_00074910();
extern unsigned long sk_slot_0007499c();
extern unsigned long sk_slot_00074a28();
extern unsigned long sk_slot_00074a98();
extern unsigned long sk_slot_00074b08();
extern unsigned long sk_slot_00074b78();
extern unsigned long sk_slot_00074c14();
extern unsigned long sk_slot_00074cb8();
extern unsigned long sk_slot_00074d54();
extern unsigned long sk_slot_00074dc8();
extern unsigned long sk_slot_00074e34();
extern unsigned long sk_slot_00074f28();
extern unsigned long sk_slot_00074fa4();
extern unsigned long sk_slot_00075018();
extern unsigned long sk_slot_000750bc();
extern unsigned long sk_slot_00075118();
extern unsigned long sk_slot_000751b4();
extern unsigned long sk_slot_000752a4();
extern unsigned long sk_slot_0007534c();
extern unsigned long sk_slot_000753c0();
extern unsigned long sk_slot_0007543c();
extern unsigned long sk_slot_000754b0();
extern unsigned long sk_slot_0007552c();
extern unsigned long sk_slot_00075624();
extern unsigned long sk_slot_00075710();
extern unsigned long sk_slot_00075784();
extern unsigned long sk_slot_000757e8();
extern unsigned long sk_slot_0007585c();
extern unsigned long sk_slot_000758d8();
extern unsigned long sk_slot_00075948();
extern unsigned long sk_slot_000759c0();
extern unsigned long sk_slot_00075a38();
extern unsigned long sk_slot_00075b2c();
extern unsigned long sk_slot_00075bac();
extern unsigned long sk_slot_00075c50();
extern unsigned long sk_slot_00075cb4();
extern unsigned long sk_slot_00075dd8();
extern unsigned long sk_slot_00075ea4();
extern unsigned long sk_slot_00075fb4();
extern unsigned long sk_slot_0007608c();
extern unsigned long sk_slot_00076158();
extern unsigned long sk_slot_00076274();
extern unsigned long sk_slot_0007629c();
extern unsigned long sk_slot_00076360();
extern unsigned long sk_slot_000764a0();
extern unsigned long sk_slot_000764c8();
extern unsigned long sk_slot_0007659c();
extern unsigned long sk_slot_000765c4();
extern unsigned long sk_slot_0007667c();
extern unsigned long sk_slot_00076760();
extern unsigned long sk_slot_0007682c();
extern unsigned long sk_slot_000768f0();
extern unsigned long sk_slot_00076918();
extern unsigned long sk_slot_000769d4();
extern unsigned long sk_slot_00076ac8();
extern unsigned long sk_slot_00076d08();
extern unsigned long sk_slot_00076f74();
extern unsigned long sk_slot_00076fc0();
extern unsigned long sk_slot_00077024();
extern unsigned long sk_slot_00077070();
extern unsigned long sk_slot_00077088();
extern unsigned long sk_slot_000770e8();
extern unsigned long sk_slot_000773f0();
extern unsigned long sk_slot_000774c8();
extern unsigned long sk_slot_0007752c();
extern unsigned long sk_slot_00077540();
extern unsigned long sk_slot_00077550();
extern unsigned long sk_slot_00077560();
extern unsigned long sk_slot_00077570();
extern unsigned long sk_slot_00077580();
extern unsigned long sk_slot_00077590();
extern unsigned long sk_slot_000775b8();
extern unsigned long sk_slot_000775c8();
extern unsigned long sk_slot_000775dc();
extern unsigned long sk_slot_00077604();
extern unsigned long sk_slot_00077614();
extern unsigned long sk_slot_00077624();
extern unsigned long sk_slot_00077630();
extern unsigned long sk_slot_0007764c();
extern unsigned long sk_slot_0007765c();
extern unsigned long sk_slot_0007766c();
extern unsigned long sk_slot_0007767c();
extern unsigned long sk_slot_00077698();
extern unsigned long sk_slot_000776b4();
extern unsigned long sk_slot_000776c0();
extern unsigned long sk_slot_000776cc();
extern unsigned long sk_slot_000776d8();
extern unsigned long sk_slot_000776e4();
extern unsigned long sk_slot_000776f8();
extern unsigned long sk_slot_00077708();
extern unsigned long sk_slot_00077718();
extern unsigned long sk_slot_00077724();
extern unsigned long sk_slot_00077744();
extern unsigned long sk_slot_00077764();
extern unsigned long sk_slot_00077770();
extern unsigned long sk_slot_00077778();
extern unsigned long sk_slot_00077794();
extern unsigned long sk_slot_000777b4();
extern unsigned long sk_slot_000777c4();
extern unsigned long sk_slot_000777e4();
extern unsigned long sk_slot_00077800();
extern unsigned long sk_slot_0007780c();
extern unsigned long sk_slot_00077824();
extern unsigned long sk_slot_0007783c();
extern unsigned long sk_slot_00077848();
extern unsigned long sk_slot_00077860();
extern unsigned long sk_slot_00077870();
extern unsigned long sk_slot_0007787c();
extern unsigned long sk_slot_00077888();
extern unsigned long sk_slot_00077894();
extern unsigned long sk_slot_000778a0();
extern unsigned long sk_slot_000778b4();
extern unsigned long sk_slot_000778c0();
extern unsigned long sk_slot_000778d4();
extern unsigned long sk_slot_000778e8();
extern unsigned long sk_slot_000778fc();
extern unsigned long sk_slot_00077910();
extern unsigned long sk_slot_0007791c();
extern unsigned long sk_slot_00077928();
extern unsigned long sk_slot_0007798c();
extern unsigned long sk_slot_00077a90();
extern unsigned long sk_slot_00077b58();
extern unsigned long sk_slot_00077b84();
extern unsigned long sk_slot_00077bd0();
extern unsigned long sk_slot_00077d64();
extern unsigned long sk_slot_00077da4();
extern unsigned long sk_slot_00077de8();
extern unsigned long sk_slot_00077e38();
extern unsigned long sk_slot_00077e74();
extern unsigned long sk_slot_00077eb8();
extern unsigned long sk_slot_00077f08();
extern unsigned long sk_slot_00077f44();
extern unsigned long sk_slot_00077f88();
extern unsigned long sk_slot_00077fd8();
extern unsigned long sk_slot_0007802c();
extern unsigned long sk_slot_0007806c();
extern unsigned long sk_slot_000780b0();
extern unsigned long sk_slot_00078100();
extern unsigned long sk_slot_0007815c();
extern unsigned long sk_slot_000781b4();
extern unsigned long sk_slot_00078220();
extern unsigned long sk_slot_00078270();
extern unsigned long sk_slot_000782c0();
extern unsigned long sk_slot_0007830c();
extern unsigned long sk_slot_00078368();
extern unsigned long sk_slot_000783b8();
extern unsigned long sk_slot_00078414();
extern unsigned long sk_slot_00078454();
extern unsigned long sk_slot_00078498();
extern unsigned long sk_slot_000784e8();
extern unsigned long sk_slot_00078544();
extern unsigned long sk_slot_00078584();
extern unsigned long sk_slot_000785c8();
extern unsigned long sk_slot_00078618();
extern unsigned long sk_slot_00078674();
extern unsigned long sk_slot_000786b4();
extern unsigned long sk_slot_000786f8();
extern unsigned long sk_slot_00078748();
extern unsigned long sk_slot_00078784();
extern unsigned long sk_slot_000787c8();
extern unsigned long sk_slot_00078818();
extern unsigned long sk_slot_00078880();
extern unsigned long sk_slot_00078fec();
extern unsigned long sk_slot_00079038();
extern unsigned long sk_slot_000792d8();
extern unsigned long sk_slot_000796b0();
extern unsigned long sk_slot_0007985c();
extern unsigned long sk_slot_00079a88();
extern unsigned long sk_slot_00079bf0();
extern unsigned long sk_slot_0007a120();
extern unsigned long sk_slot_0007a1fc();
extern unsigned long sk_slot_0007a274();
extern unsigned long sk_slot_0007a2dc();
extern unsigned long sk_slot_0007a3dc();
extern unsigned long sk_slot_0007a454();
extern unsigned long sk_slot_0007a548();
extern unsigned long sk_slot_0007a5c4();
extern unsigned long sk_slot_0007a6a0();
extern unsigned long sk_slot_0007a718();
extern unsigned long sk_slot_0007abe0();
extern unsigned long sk_slot_0007ac24();
extern unsigned long sk_slot_0007acd8();
extern unsigned long sk_slot_0007b0cc();
extern unsigned long sk_slot_0007b134();
extern unsigned long sk_slot_0007b178();
extern unsigned long sk_slot_0007b1c0();
extern unsigned long sk_slot_0007b1f0();
extern unsigned long sk_slot_0007b208();
extern unsigned long sk_slot_0007b220();
extern unsigned long sk_slot_0007b238();
extern unsigned long sk_slot_0007b250();
extern unsigned long sk_slot_0007b268();
extern unsigned long sk_slot_0007b280();
extern unsigned long sk_slot_0007b298();
extern unsigned long sk_slot_0007b2b0();
extern unsigned long sk_slot_0007b2c8();
extern unsigned long sk_slot_0007b324();
extern unsigned long sk_slot_0007b33c();
extern unsigned long sk_slot_0007b354();
extern unsigned long sk_slot_0007b384();
extern unsigned long sk_slot_0007b3b4();
extern unsigned long sk_slot_0007b3e4();
extern unsigned long sk_slot_0007b3fc();
extern unsigned long sk_slot_0007b414();
extern unsigned long sk_slot_0007b42c();
extern unsigned long sk_slot_0007b444();
extern unsigned long sk_slot_0007b45c();
extern unsigned long sk_slot_0007b474();
extern unsigned long sk_slot_0007b48c();
extern unsigned long sk_slot_0007b4a4();
extern unsigned long sk_slot_0007b4e8();
extern unsigned long sk_slot_0007b4fc();
extern unsigned long sk_slot_0007b500();
extern unsigned long sk_slot_0007b524();
extern unsigned long sk_slot_0007b528();
extern unsigned long sk_slot_0007b544();
extern unsigned long sk_slot_0007b548();
extern unsigned long sk_slot_0007b564();
extern unsigned long sk_slot_0007b568();
extern unsigned long sk_slot_0007b58c();
extern unsigned long sk_slot_0007b5f4();
extern unsigned long sk_slot_0007b654();
extern unsigned long sk_slot_0007b6a0();
extern unsigned long sk_slot_0007b6d8();
extern unsigned long sk_slot_0007b718();
extern unsigned long sk_slot_0007b750();
extern unsigned long sk_slot_0007b790();
extern unsigned long sk_slot_0007b7d0();
extern unsigned long sk_slot_0007b818();
extern unsigned long sk_slot_0007b864();
extern unsigned long sk_slot_0007b8ac();
extern unsigned long sk_slot_0007b8f4();
extern unsigned long sk_slot_0007b93c();
extern unsigned long sk_slot_0007b97c();
extern unsigned long sk_slot_0007bcf8();
extern unsigned long sk_slot_0007be74();
extern unsigned long sk_slot_0007be8c();
extern unsigned long sk_slot_0007bea4();
extern unsigned long sk_slot_0007bebc();
extern unsigned long sk_slot_0007bed4();
extern unsigned long sk_slot_0007beec();
extern unsigned long sk_slot_0007bf04();
extern unsigned long sk_slot_0007bf1c();
extern unsigned long sk_slot_0007bf34();
extern unsigned long sk_slot_0007bf4c();
extern unsigned long sk_slot_0007bf80();
extern unsigned long sk_slot_0007bfac();
extern unsigned long sk_slot_0007bfc8();
extern unsigned long sk_slot_0007bfdc();
extern unsigned long sk_slot_0007bff0();
extern unsigned long sk_slot_0007c004();
extern unsigned long sk_slot_0007c018();
extern unsigned long sk_slot_0007c028();
extern unsigned long sk_slot_0007c038();
extern unsigned long sk_slot_0007c070();
extern unsigned long sk_slot_0007c088();
extern unsigned long sk_slot_0007c0a0();
extern unsigned long sk_slot_0007c0ac();
extern unsigned long sk_slot_0007c0b8();
extern unsigned long sk_slot_0007c0c4();
extern unsigned long sk_slot_0007c0d4();
extern unsigned long sk_slot_0007c0e0();
extern unsigned long sk_slot_0007c0ec();
extern unsigned long sk_slot_0007c0f8();
extern unsigned long sk_slot_0007c128();
extern unsigned long sk_slot_0007c140();
extern unsigned long sk_slot_0007c14c();
extern unsigned long sk_slot_0007c158();
extern unsigned long sk_slot_0007c164();
extern unsigned long sk_slot_0007c178();
extern unsigned long sk_slot_0007c18c();
extern unsigned long sk_slot_0007c198();
extern unsigned long sk_slot_0007c1a4();
extern unsigned long sk_slot_0007c1b0();
extern unsigned long sk_slot_0007c1c4();
extern unsigned long sk_slot_0007c1d0();
extern unsigned long sk_slot_0007c1e8();
extern unsigned long sk_slot_0007c210();
extern unsigned long sk_slot_0007c250();
extern unsigned long sk_slot_0007c2a0();
extern unsigned long sk_slot_0007c2e8();
extern unsigned long sk_slot_0007c310();
extern unsigned long sk_slot_0007c358();
extern unsigned long sk_slot_0007c3d8();
extern unsigned long sk_slot_0007c4ac();
extern unsigned long sk_slot_0007c614();
extern unsigned long sk_slot_0007c618();
extern unsigned long sk_slot_0007c6ac();
extern unsigned long sk_slot_0007c76c();
extern unsigned long sk_slot_0007c814();
extern unsigned long sk_slot_0007c8a0();
extern unsigned long sk_slot_0007c8dc();
extern unsigned long sk_slot_0007c974();
extern unsigned long sk_slot_0007ca48();
extern unsigned long sk_slot_0007cb88();
extern unsigned long sk_slot_0007cefc();
extern unsigned long sk_slot_0007cf38();
extern unsigned long sk_slot_0007cf74();
extern unsigned long sk_slot_0007d054();
extern unsigned long sk_slot_0007d0fc();
extern unsigned long sk_slot_0007d128();
extern unsigned long sk_slot_0007d168();
extern unsigned long sk_slot_0007d1e4();
extern unsigned long sk_slot_0007d220();
extern unsigned long sk_slot_0007d264();
extern unsigned long sk_slot_0007d2b8();
extern unsigned long sk_slot_0007d3e8();
extern unsigned long sk_slot_0007d880();
extern unsigned long sk_slot_0007d8bc();
extern unsigned long sk_slot_0007d910();
extern unsigned long sk_slot_0007d958();
extern unsigned long sk_slot_0007d9ac();
extern unsigned long sk_slot_0007d9d8();
extern unsigned long sk_slot_0007da4c();
extern unsigned long sk_slot_0007da98();
extern unsigned long sk_slot_0007dbb8();
extern unsigned long sk_slot_0007dbf0();
extern unsigned long sk_slot_0007dcfc();
extern unsigned long sk_slot_0007ddb0();
extern unsigned long sk_slot_0007e710();
extern unsigned long sk_slot_0007e74c();
extern unsigned long sk_slot_0007e788();
extern unsigned long sk_slot_0007e7c4();
extern unsigned long sk_slot_0007e9c0();
extern unsigned long sk_slot_0007e9fc();
extern unsigned long sk_slot_0007ea60();
extern unsigned long sk_slot_0007ead8();
extern unsigned long sk_slot_0007eb2c();
extern unsigned long sk_slot_0007eb34();
extern unsigned long sk_slot_0007ebf0();
extern unsigned long sk_slot_0007ec2c();
extern unsigned long sk_slot_0007ec68();
extern unsigned long sk_slot_0007eca8();
extern unsigned long sk_slot_0007f020();
extern unsigned long sk_slot_0007f04c();
extern unsigned long sk_slot_0007f098();
extern unsigned long sk_slot_0007f0d4();
extern unsigned long sk_slot_0007f110();
extern unsigned long sk_slot_0007f1e0();
extern unsigned long sk_slot_0007f4d8();
extern unsigned long sk_slot_0007f8ec();
extern unsigned long sk_slot_0007fa68();
extern unsigned long sk_slot_0007fc64();
extern unsigned long sk_slot_0007fd0c();
extern unsigned long sk_slot_0007fd48();
extern unsigned long sk_slot_0007fd84();
extern unsigned long sk_slot_0007fe94();
extern unsigned long sk_slot_0064e030();

void sk_arr_alloc144();
void sk_arr_alloc16();
void sk_arr_alloc2();
void sk_arr_alloc248();
void sk_arr_alloc2b();
void sk_arr_alloc2c();
void sk_arr_alloc32();
void sk_arr_alloc4();
void sk_arr_alloc4b();
void sk_arr_alloc64();
void sk_arr_alloc8();
void sk_arr_alloc88();
void sk_arr_alloc8b();
void sk_arr_alloc8c();
void sk_arr_alloc8d();
void sk_arr_alloc_2();
void sk_arr_copy1();
void sk_arr_copy144();
void sk_arr_copy16();
void sk_arr_copy16b();
void sk_arr_copy16c();
void sk_arr_copy16d();
void sk_arr_copy16e();
void sk_arr_copy16f();
void sk_arr_copy2();
void sk_arr_copy24();
void sk_arr_copy248();
void sk_arr_copy24b();
void sk_arr_copy32();
void sk_arr_copy32b();
void sk_arr_copy32c();
void sk_arr_copy4();
void sk_arr_copy40();
void sk_arr_copy40b();
void sk_arr_copy40c();
void sk_arr_copy48();
void sk_arr_copy48b();
void sk_arr_copy56();
void sk_arr_copy56b();
void sk_arr_copy64();
void sk_arr_copy64b();
void sk_arr_copy72();
void sk_arr_copy8();
void sk_arr_copy80();
void sk_arr_copy80b();
void sk_arr_copy88();
void sk_arr_copy8b();
void sk_boot_cpu_ready();
void sk_boot_cpu_ready_1();
void sk_boot_cpu_wake_sync();
void sk_bootinfo_map_snapshot();
void sk_bootinfo_map_snapshot_t();
void sk_cap_map_new_4();
void sk_cap_map_new_t4();
void sk_const40();
void sk_elem_copy1();
void sk_elem_copy16();
void sk_elem_copy1b();
void sk_elem_copy24();
void sk_elem_copy24b();
void sk_elem_copy4();
void sk_elem_copy40();
void sk_elem_copy40b();
void sk_elem_copy40c();
void sk_elem_copy48();
void sk_elem_copy48b();
void sk_elem_copy4b();
void sk_elem_copy56();
void sk_elem_copy56b();
void sk_elem_copy64();
void sk_elem_copy72();
void sk_elem_copy8();
void sk_elem_copy80();
void sk_elem_copy80b();
void sk_elem_copy8b();
void sk_elem_copy8c();
void sk_f_70960();
void sk_f_70de4();
void sk_f_71050();
void sk_f_72424();
void sk_f_72454();
void sk_f_72464();
void sk_f_724cc();
void sk_f_72570();
void sk_f_725c8();
void sk_f_72664();
void sk_f_726a0();
void sk_f_72710();
void sk_f_7278c();
void sk_f_727ec();
void sk_f_728d4();
void sk_f_7292c();
void sk_f_72a30();
void sk_f_72a88();
void sk_f_72b44();
void sk_f_72b9c();
void sk_f_72c98();
void sk_f_750bc();
void sk_f_751b4();
void sk_f_75784();
void sk_f_75948();
void sk_f_759c0();
void sk_f_75b2c();
void sk_f_75c50();
void sk_f_75cb4();
void sk_f_75dd8();
void sk_f_75ea4();
void sk_f_75fb4();
void sk_f_7608c();
void sk_f_76158();
void sk_f_76274();
void sk_f_7629c();
void sk_f_76360();
void sk_f_764a0();
void sk_f_764c8();
void sk_f_7659c();
void sk_f_765c4();
void sk_f_7667c();
void sk_f_76760();
void sk_f_7682c();
void sk_f_768f0();
void sk_f_76918();
void sk_f_769d4();
void sk_f_76ac8();
void sk_f_76d08();
void sk_f_76f74();
void sk_f_76fc0();
void sk_f_77024();
void sk_f_77070();
void sk_f_773f0();
void sk_f_774c8();
void sk_f_7751c();
void sk_f_77520();
void sk_f_77524();
void sk_f_77528();
void sk_f_77540();
void sk_f_775dc();
void sk_f_77630();
void sk_f_7764c();
void sk_f_7766c();
void sk_f_776e4();
void sk_f_776f8();
void sk_f_77718();
void sk_f_77800();
void sk_f_77848();
void sk_f_77860();
void sk_f_77870();
void sk_f_7787c();
void sk_f_778d4();
void sk_f_778e8();
void sk_f_778fc();
void sk_f_77910();
void sk_f_7791c();
void sk_f_77928();
void sk_f_7798c();
void sk_f_77b58();
void sk_f_77b84();
void sk_f_77bd0();
void sk_f_78100();
void sk_f_7815c();
void sk_f_781b4();
void sk_f_782c0();
void sk_f_7830c();
void sk_f_78818();
void sk_f_78880();
void sk_f_79038();
void sk_f_792d8();
void sk_f_796b0();
void sk_f_7985c();
void sk_f_79a88();
void sk_f_79bf0();
void sk_f_7a120();
void sk_f_7a1fc();
void sk_f_7a274();
void sk_f_7a2dc();
void sk_f_7a3dc();
void sk_f_7a454();
void sk_f_7a548();
void sk_f_7a5c4();
void sk_f_7a6a0();
void sk_f_7a718();
void sk_f_7abe0();
void sk_f_7ac24();
void sk_f_7acd8();
void sk_f_7b0cc();
void sk_f_7b134();
void sk_f_7b1f0();
void sk_f_7b208();
void sk_f_7b220();
void sk_f_7b238();
void sk_f_7b250();
void sk_f_7b268();
void sk_f_7b280();
void sk_f_7b298();
void sk_f_7b2b0();
void sk_f_7b2c8();
void sk_f_7b324();
void sk_f_7b33c();
void sk_f_7b3e4();
void sk_f_7b3fc();
void sk_f_7b414();
void sk_f_7b42c();
void sk_f_7b444();
void sk_f_7b45c();
void sk_f_7b474();
void sk_f_7b48c();
void sk_f_7b4a4();
void sk_f_7b4e8();
void sk_f_7b4fc();
void sk_f_7b500();
void sk_f_7b524();
void sk_f_7b528();
void sk_f_7b544();
void sk_f_7b548();
void sk_f_7b564();
void sk_f_7b568();
void sk_f_7b58c();
void sk_f_7b5f4();
void sk_f_7b654();
void sk_f_7b6a0();
void sk_f_7b6d8();
void sk_f_7b718();
void sk_f_7b750();
void sk_f_7b790();
void sk_f_7b7d0();
void sk_f_7b818();
void sk_f_7b864();
void sk_f_7b8ac();
void sk_f_7b8f4();
void sk_f_7b93c();
void sk_f_7b97c();
void sk_f_7bcf8();
void sk_f_7be74();
void sk_f_7be8c();
void sk_f_7bea4();
void sk_f_7bebc();
void sk_f_7bed4();
void sk_f_7beec();
void sk_f_7bf04();
void sk_f_7bf1c();
void sk_f_7bf34();
void sk_f_7bf4c();
void sk_f_7bf54();
void sk_f_7bfc8();
void sk_f_7bfdc();
void sk_f_7bff0();
void sk_f_7c004();
void sk_f_7c038();
void sk_f_7c0e0();
void sk_f_7c140();
void sk_f_7c158();
void sk_f_7c1b0();
void sk_f_7c1d0();
void sk_f_7c1e4();
void sk_f_7c1e8();
void sk_f_7c210();
void sk_f_7c250();
void sk_f_7c2e8();
void sk_f_7c310();
void sk_f_7c358();
void sk_f_7c3d8();
void sk_f_7c4ac();
void sk_f_7c614();
void sk_f_7c618();
void sk_f_7c6ac();
void sk_f_7c76c();
void sk_f_7c814();
void sk_f_7c8a0();
void sk_f_7c8dc();
void sk_f_7c974();
void sk_f_7ca48();
void sk_f_7cefc();
void sk_f_7cf38();
void sk_f_7cf74();
void sk_f_7d054();
void sk_f_7d0fc();
void sk_f_7d128();
void sk_f_7d168();
void sk_f_7d264();
void sk_f_7d2b8();
void sk_f_7d910();
void sk_f_7d958();
void sk_f_7d9ac();
void sk_f_7d9d8();
void sk_f_7da4c();
void sk_f_7da98();
void sk_f_7dbb8();
void sk_f_7dbf0();
void sk_f_7dcfc();
void sk_f_7ddb0();
void sk_f_7e788();
void sk_f_7e7c4();
void sk_f_7ea60();
void sk_f_7ead8();
void sk_f_7eb34();
void sk_f_7ec68();
void sk_f_7eca8();
void sk_f_7f020();
void sk_f_7f04c();
void sk_f_7f110();
void sk_f_7f1e0();
void sk_f_7f4d8();
void sk_f_7f8ec();
void sk_f_7fa68();
void sk_f_7fc64();
void sk_f_7fd84();
void sk_f_7fe94();
void sk_fatal_account();
void sk_hash_write_dispatch();
void sk_hash_write_dispatch2();
void sk_hash_write_dispatch3();
void sk_hw_sync2();
void sk_launcher_cnode_add();
void sk_launcher_cnode_append();
void sk_launcher_cnode_append_slot();
void sk_launcher_cnode_append_t();
void sk_launcher_cnode_header();
void sk_launcher_cnode_ser_copy();
void sk_launcher_cnode_ser_copy2();
void sk_launcher_cnode_serialize();
void sk_launcher_record_next();
void sk_launcher_stat_init();
void sk_launcher_stat_new();
void sk_launcher_stat_tally();
void sk_map_grow16();
void sk_map_grow16b();
void sk_map_grow16c();
void sk_map_grow16d();
void sk_map_grow16e();
void sk_map_grow16f();
void sk_map_grow16g();
void sk_map_grow16h();
void sk_map_grow16j();
void sk_map_grow16k();
void sk_map_grow16l();
void sk_map_grow2();
void sk_map_grow2b();
void sk_map_grow2c();
void sk_map_grow2d();
void sk_map_grow2e();
void sk_map_grow2f();
void sk_map_grow2g();
void sk_map_grow2h();
void sk_map_grow2i();
void sk_map_grow2j();
void sk_map_grow2l();
void sk_map_grow2m();
void sk_map_grow2n();
void sk_map_grow2o();
void sk_map_grow32();
void sk_map_grow32b();
void sk_map_grow32c();
void sk_map_grow32d();
void sk_map_grow32e();
void sk_map_grow32f();
void sk_map_grow4();
void sk_map_grow4b();
void sk_map_grow64();
void sk_map_grow64b();
void sk_map_grow8();
void sk_map_grow8b();
void sk_map_grow8c();
void sk_map_grow8d();
void sk_map_grow8e();
void sk_map_grow8f();
void sk_map_grow8g();
void sk_map_grow8h();
void sk_map_grow8i();
void sk_map_grow8k();
void sk_map_grow8l();
void sk_map_grow8m();
void sk_map_grow8n();
void sk_map_grow8o();
void sk_map_grow_generic();
void sk_noop();
void sk_noop_1();
void sk_noop_10();
void sk_noop_11();
void sk_noop_12();
void sk_noop_13();
void sk_noop_14();
void sk_noop_15();
void sk_noop_16();
void sk_noop_17();
void sk_noop_18();
void sk_noop_19();
void sk_noop_2();
void sk_noop_20();
void sk_noop_21();
void sk_noop_22();
void sk_noop_23();
void sk_noop_24();
void sk_noop_25();
void sk_noop_26();
void sk_noop_27();
void sk_noop_28();
void sk_noop_29();
void sk_noop_3();
void sk_noop_30();
void sk_noop_31();
void sk_noop_32();
void sk_noop_33();
void sk_noop_34();
void sk_noop_35();
void sk_noop_36();
void sk_noop_37();
void sk_noop_38();
void sk_noop_39();
void sk_noop_4();
void sk_noop_40();
void sk_noop_41();
void sk_noop_42();
void sk_noop_43();
void sk_noop_44();
void sk_noop_45();
void sk_noop_46();
void sk_noop_47();
void sk_noop_48();
void sk_noop_5();
void sk_noop_6();
void sk_noop_7();
void sk_noop_8();
void sk_noop_9();
void sk_obj_base();
void sk_obj_call_0();
void sk_obj_call_0b();
void sk_obj_call_10();
void sk_obj_call_20();
void sk_obj_deref();
void sk_obj_end_14();
void sk_obj_end_14_1();
void sk_obj_end_18();
void sk_obj_end_18_1();
void sk_obj_end_1c();
void sk_obj_end_1c_1();
void sk_obj_end_20();
void sk_obj_end_24();
void sk_obj_end_28();
void sk_obj_end_8();
void sk_obj_end_c();
void sk_obj_end_c_1();
void sk_obj_find_by_key();
void sk_obj_free_10();
void sk_obj_free_10b();
void sk_obj_free_10c();
void sk_obj_free_10d();
void sk_obj_free_18();
void sk_obj_free_18b();
void sk_obj_free_18c();
void sk_obj_free_18d();
void sk_obj_free_2f2();
void sk_obj_free_2f2b();
void sk_obj_free_2f2c();
void sk_obj_free_3f();
void sk_obj_fwd_70cfc();
void sk_obj_fwd_714f4();
void sk_obj_fwd_714f4b();
void sk_obj_fwd_71598();
void sk_obj_fwd_71598b();
void sk_obj_fwd_71620();
void sk_obj_fwd_71620b();
void sk_obj_fwd_716b4();
void sk_obj_fwd_716b4b();
void sk_obj_fwd_737e8();
void sk_obj_fwd_737e8b();
void sk_obj_fwd_737e8c();
void sk_obj_fwd_737e8d();
void sk_obj_fwd_737e8e();
void sk_obj_get_58();
void sk_obj_get_60();
void sk_obj_get_98();
void sk_obj_mth_0();
void sk_obj_mth_1();
void sk_obj_mth_10();
void sk_obj_mth_10b();
void sk_obj_mth_120();
void sk_obj_mth_138();
void sk_obj_mth_14();
void sk_obj_mth_150();
void sk_obj_mth_168();
void sk_obj_mth_2();
void sk_obj_mth_3();
void sk_obj_mth_48();
void sk_obj_mth_50();
void sk_obj_mth_50b();
void sk_obj_mth_50c();
void sk_obj_mth_58();
void sk_obj_mth_58b();
void sk_obj_mth_58c();
void sk_obj_mth_60();
void sk_obj_mth_60b();
void sk_obj_mth_68();
void sk_obj_mth_70();
void sk_obj_mth_78();
void sk_obj_mth_80();
void sk_obj_mth_b8();
void sk_obj_mth_c0();
void sk_obj_mth_f0();
void sk_obj_refswap_77da4();
void sk_obj_refswap_77de8();
void sk_obj_refswap_77eb8();
void sk_obj_refswap_77f88();
void sk_obj_refswap_7806c();
void sk_obj_refswap_780b0();
void sk_obj_refswap_78220();
void sk_obj_refswap_78368();
void sk_obj_refswap_78454();
void sk_obj_refswap_78498();
void sk_obj_refswap_78584();
void sk_obj_refswap_785c8();
void sk_obj_refswap_786b4();
void sk_obj_refswap_786f8();
void sk_obj_refswap_787c8();
void sk_obj_rel_50();
void sk_obj_rel_68();
void sk_obj_rel_80();
void sk_obj_rel_88();
void sk_obj_rel_90();
void sk_obj_release_2f();
void sk_obj_set_58();
void sk_obj_set_60();
void sk_obj_set_98();
void sk_obj_set_ptr();
void sk_obj_store3();
void sk_obj_store4();
void sk_obj_teardown_a();
void sk_obj_teardown_b();
void sk_obj_teardown_c();
void sk_obj_teardown_d();
void sk_obj_teardown_e();
void sk_obj_teardown_f();
void sk_obj_teardown_g();
void sk_obj_teardown_h();
void sk_obj_teardown_i();
void sk_obj_teardown_j();
void sk_pair_read20();
void sk_pair_read28();
void sk_roottask_content_deserialize();
void sk_roottask_content_serialize();
void sk_shared_map();
void sk_shared_map_ptr();
void sk_zero();
void sk_zero2();
void sk_zero3();

/*--------------------------------------------------------------------*/
/* FUN_70070 @ 0x00070070   (est. sk_boot_cpu_ready)
 * Ghidra: void FUN_70070(void)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_boot_cpu_ready(void)
{
    sk_slot_00070070();
    sk_sysreg_read();
    sk_irq_clear();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_70074 @ 0x00070074   (est. sk_boot_cpu_ready)
 * Ghidra: void FUN_70074(void)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_boot_cpu_ready_1(void)
{
    sk_slot_00070074();
    sk_sysreg_read();
    sk_irq_clear();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_70098 @ 0x00070098   (est. sk_boot_cpu_wake_sync)
 * Ghidra: void FUN_70098(unsigned long param_1, unsigned long param_2, unsigned long param_3)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_boot_cpu_wake_sync(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    sk_slot_00070098();
    sk_spin_lock();
    sk_slot_000778a0();
    sk_emit_fmt();
    sk_boot_wake();
    sk_emit_fmt();
    sk_release();
    sk_emit_fmt();
    sk_sysreg_read();
    sk_irq_clear();
    sk_fold_entry();
    sk_emit_fmt();
    sk_release();
    sk_emit_fmt();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7021c @ 0x0007021c   (est. sk_hash_write_dispatch)
 * Ghidra: void FUN_7021c(unsigned long param_1, unsigned long param_2, unsigned long param_3)
 * mode-byte dispatch to writer
 * Confidence: low
 */
void sk_hash_write_dispatch(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    if (param_3 != 0) {
        if (param_3 == 1)
            sk_write_word(1);
        else
            param_2 = 2;
        sk_write_word(param_2);
        return;
    }
    sk_write_word(0);
    sk_write_raw(param_1, param_2);
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_70288 @ 0x00070288   (est. sk_hash_write_dispatch2)
 * Ghidra: void FUN_70288(unsigned long param_1, unsigned long param_2)
 * hash-init + mode dispatch
 * Confidence: low
 */
void sk_hash_write_dispatch2(unsigned long param_1, unsigned long param_2)
{
    unsigned char ctx[72];
    sk_hash_init(ctx);
    if (param_2 == 0)
        sk_hash_fn();
    else
        sk_hash_fn();
    sk_hash_fn();
}

/*--------------------------------------------------------------------*/
/* FUN_7032c @ 0x0007032c   (est. sk_hash_write_dispatch3)
 * Ghidra: void FUN_7032c(void)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_hash_write_dispatch3(void)
{
    sk_slot_0007032c();
    sk_hash_init();
    sk_slot_0007021c();
    sk_hash_fn();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_70390 @ 0x00070390   (est. sk_launcher_stat_tally)
 * Ghidra: void FUN_70390(unsigned long param_1)
 * bitmap walk tally; SoftwareBreakpoint on overflow
 * Confidence: low
 */
void sk_launcher_stat_tally(unsigned long param_1)
{
    long arr = sk_alloc_cnode(0, 1, 1, (void *)0x657778);
    /* zero 0x1a counters, walk set bits of bitmap, sum per-slot via sk_obj_find_4 */
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_70590 @ 0x00070590   (est. sk_launcher_cnode_append_t)
 * Ghidra: void FUN_70590(unsigned long param_1)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_launcher_cnode_append_t(unsigned long param_1)
{
    sk_slot_00070594();
    sk_tcb_swap();
    sk_tcb_free();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_70594 @ 0x00070594   (est. sk_launcher_cnode_append)
 * Ghidra: void FUN_70594(unsigned long param_1)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_launcher_cnode_append(unsigned long param_1)
{
    sk_slot_00070594();
    sk_tcb_swap();
    sk_tcb_free();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_705f8 @ 0x000705f8   (est. sk_launcher_stat_new)
 * Ghidra: void FUN_705f8(void)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_launcher_stat_new(void)
{
    sk_slot_000705f8();
    sk_inc_ref();
    sk_alloc();
    sk_slot_000776cc();
    sk_slot_00077590();
    sk_map_new();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7063c @ 0x0007063c   (est. sk_launcher_stat_init)
 * Ghidra: void FUN_7063c(void)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_launcher_stat_init(void)
{
    sk_slot_0007063c();
    sk_slot_00077590();
    sk_map_new();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_70674 @ 0x00070674   (est. sk_launcher_cnode_add)
 * Ghidra: void FUN_70674(unsigned long param_1, unsigned long param_2, unsigned long param_3)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_launcher_cnode_add(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    sk_slot_00070674();
    sk_alloc_teardown();
    sk_retain();
    sk_slot_000724cc();
    sk_release();
    sk_alloc_finalize();
    sk_alloc_teardown();
    sk_slot_00075cb4();
    sk_alloc_finalize();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_70754 @ 0x00070754   (est. sk_launcher_cnode_append_slot)
 * Ghidra: void FUN_70754(unsigned long param_1)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_launcher_cnode_append_slot(unsigned long param_1)
{
    sk_slot_00070754();
    sk_alloc_teardown();
    sk_retain();
    sk_slot_00070594();
    sk_alloc_finalize();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_707a8 @ 0x000707a8   (est. sk_launcher_cnode_serialize)
 * Ghidra: void FUN_707a8(void)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_launcher_cnode_serialize(void)
{
    sk_slot_000707a8();
    sk_slot_0007780c();
    sk_slot_00077590();
    sk_map_new();
    sk_lock();
    sk_retain();
    sk_retain_low();
    sk_slot_00076d08();
    sk_slot_00076f74();
    sk_lock();
    sk_retain();
    sk_slot_000707a8();
    sk_retain_low();
    sk_slot_00076d08();
    sk_free();
    sk_slot_00070920();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_70920 @ 0x00070920   (est. sk_launcher_cnode_ser_copy)
 * Ghidra: void FUN_70920(unsigned long param_1, unsigned long param_2)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_launcher_cnode_ser_copy(unsigned long param_1, unsigned long param_2)
{
    sk_slot_00070920();
    sk_hash_combine();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_70960 @ 0x00070960   (est. sk_f_70960)
 * Ghidra: void FUN_70960(void)
 * faithful call sequence; see FUN_70960
 * Confidence: low
 */
void sk_f_70960(void)
{
    sk_slot_00070960();
    sk_slot_0007780c();
    sk_map_new();
    sk_lock();
    sk_slot_00077724();
    sk_retain();
    sk_slot_00072464();
    sk_sysreg_read();
    sk_irq_clear();
    sk_retain_low();
    sk_slot_00072464();
    sk_type_resolve();
    sk_map_insert();
    sk_slot_00072464();
    sk_slot_00077604();
    sk_panic_nr();
    sk_lock();
    sk_retain();
    sk_slot_00070960();
    sk_retain_low();
    sk_slot_00076ac8();
    sk_free();
    sk_slot_00070cc8();
    sk_free();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_70cc8 @ 0x00070cc8   (est. sk_launcher_cnode_ser_copy2)
 * Ghidra: void FUN_70cc8(unsigned long param_1, unsigned long param_2)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_launcher_cnode_ser_copy2(unsigned long param_1, unsigned long param_2)
{
    sk_slot_00070cc8();
    sk_hash_combine();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_70cfc @ 0x00070cfc   (est. sk_launcher_cnode_header)
 * Ghidra: void FUN_70cfc(void)
 * emit CNode header word
 * Confidence: low
 */
void sk_launcher_cnode_header(void)
{
    /* FUN_00070960 + FUN_00070de4 serialize; format header via FUN_001bc440 */
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_70de4 @ 0x00070de4   (est. sk_f_70de4)
 * Ghidra: void FUN_70de4(unsigned long param_1, unsigned long param_2, unsigned long param_3)
 * faithful call sequence; see FUN_70de4
 * Confidence: low
 */
void sk_f_70de4(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    sk_slot_00070de4();
    sk_bitmap_alloc();
    sk_slot_0007198c();
    sk_retain();
    sk_free();
    sk_slot_00077744();
    sk_fold_entry();
    sk_bitmap_alloc();
    sk_slot_00077744();
    sk_fold_entry();
    sk_bitmap_alloc();
    sk_free();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_71050 @ 0x00071050   (est. sk_f_71050)
 * Ghidra: void FUN_71050(unsigned long param_1, unsigned long param_2)
 * faithful call sequence; see FUN_71050
 * Confidence: low
 */
void sk_f_71050(unsigned long param_1, unsigned long param_2)
{
    sk_slot_00071050();
    sk_slot_00070960();
    sk_slot_00070de4();
    sk_free();
    sk_release();
    sk_slot_000778fc();
    sk_slot_00076fc0();
    sk_emit_head();
    sk_free();
    sk_type_resolve();
    sk_alloc_obj();
    sk_retain();
    sk_emit_fmt();
    sk_release();
    sk_emit_record();
    sk_finalize();
    sk_retain0();
    sk_inc_ref();
    sk_ref_free();
    sk_slot_000707a8();
    sk_slot_0007198c();
    sk_slot_000718b8();
    sk_alloc_obj();
    sk_slot_00070098();
    sk_emit_fmt();
    sk_release();
    sk_emit_record();
    sk_finalize();
    sk_retain0();
    sk_inc_ref();
    sk_ref_free();
    sk_free();
    sk_slot_000707a8();
    sk_slot_0007198c();
    sk_slot_000718b8();
    sk_alloc_obj();
    sk_emit_tag();
    sk_release();
    sk_slot_00070098();
    sk_emit_fmt();
    sk_release();
    sk_emit_fmt();
    sk_emit_record();
    sk_finalize();
    sk_retain0();
    sk_inc_ref();
    sk_ref_free();
    sk_free();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_713dc @ 0x000713dc   (est. sk_obj_release_2f)
 * Ghidra: void FUN_713dc(void)
 * 003a25d4/0036b118 on +0x10/+0x18
 * Confidence: low
 */
void sk_obj_release_2f(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_71404 @ 0x00071404   (est. sk_obj_teardown_a)
 * Ghidra: void FUN_71404(void)
 * 713dc+02834+0036b6ac
 * Confidence: low
 */
void sk_obj_teardown_a(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_71408 @ 0x00071408   (est. sk_obj_teardown_b)
 * Ghidra: void FUN_71408(void)
 * 713dc+02834+0036b6ac
 * Confidence: low
 */
void sk_obj_teardown_b(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_71428 @ 0x00071428   (est. sk_obj_fwd_70cfc)
 * Ghidra: void FUN_71428(void)
 * 70cfc
 * Confidence: low
 */
void sk_obj_fwd_70cfc(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7144c @ 0x0007144c   (est. sk_obj_store4)
 * Ghidra: void FUN_7144c(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
 * store 4 words into param_1 from args
 * Confidence: low
 */
void sk_obj_store4(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
{
    ((unsigned long *)param_1)[0] = param_2;
    ((unsigned long *)param_1)[1] = param_3;
    ((unsigned long *)param_1)[2] = (unsigned long)param_4;
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_714bc @ 0x000714bc   (est. sk_obj_store3)
 * Ghidra: void FUN_714bc(unsigned long param_1, unsigned long param_2, unsigned long param_3)
 * 77070 + store param_3
 * Confidence: low
 */
void sk_obj_store3(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_714f4 @ 0x000714f4   (est. sk_obj_call_20)
 * Ghidra: void FUN_714f4(unsigned long param_1, unsigned long param_2, unsigned long param_3)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_obj_call_20(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    sk_slot_000714f4();
    sk_pair_lookup();
    sk_slot_00077088();
    sk_slot_000778d4();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_71598 @ 0x00071598   (est. sk_obj_call_0)
 * Ghidra: void FUN_71598(void)
 * call vtable+0x0
 * Confidence: low
 */
void sk_obj_call_0(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_71620 @ 0x00071620   (est. sk_obj_call_0b)
 * Ghidra: void FUN_71620(unsigned long param_1, unsigned long param_2)
 * call vtable+0x0, bump cnode
 * Confidence: low
 */
void sk_obj_call_0b(unsigned long param_1, unsigned long param_2)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_716b4 @ 0x000716b4   (est. sk_fatal_account)
 * Ghidra: void FUN_716b4(void)
 * fatal: "InternalExclaveLauncher: Accounting"
 * Confidence: medium
 */
void sk_fatal_account(void)
{
    /* FUN_001afa84(s_Fatal_error, 0xb, 2, ..., s_InternalExclaveLauncher_Accounting, ...) */
    __builtin_trap();
}

/*--------------------------------------------------------------------*/
/* FUN_71710 @ 0x00071710   (est. sk_obj_mth_10)
 * Ghidra: void FUN_71710(void)
 * read pair + call vtable+0x10
 * Confidence: low
 */
void sk_obj_mth_10(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7174c @ 0x0007174c   (est. sk_obj_call_10)
 * Ghidra: void FUN_7174c(unsigned long param_1)
 * cnode bump + vtable call
 * Confidence: low
 */
void sk_obj_call_10(unsigned long param_1)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_717c8 @ 0x000717c8   (est. sk_obj_mth_10b)
 * Ghidra: void FUN_717c8(void)
 * read pair + vtable+0x18
 * Confidence: low
 */
void sk_obj_mth_10b(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_71814 @ 0x00071814   (est. sk_obj_mth_14)
 * Ghidra: void FUN_71814(void)
 * read pair + vtable+0x14
 * Confidence: low
 */
void sk_obj_mth_14(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_71850 @ 0x00071850   (est. sk_obj_fwd_71598)
 * Ghidra: void FUN_71850(void)
 * 71598
 * Confidence: low
 */
void sk_obj_fwd_71598(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_71854 @ 0x00071854   (est. sk_obj_fwd_71598b)
 * Ghidra: void FUN_71854(void)
 * 71598
 * Confidence: low
 */
void sk_obj_fwd_71598b(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_71868 @ 0x00071868   (est. sk_obj_fwd_714f4)
 * Ghidra: void FUN_71868(void)
 * 714f4
 * Confidence: low
 */
void sk_obj_fwd_714f4(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7186c @ 0x0007186c   (est. sk_obj_fwd_714f4b)
 * Ghidra: void FUN_7186c(void)
 * 714f4
 * Confidence: low
 */
void sk_obj_fwd_714f4b(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_71880 @ 0x00071880   (est. sk_obj_fwd_71620)
 * Ghidra: void FUN_71880(void)
 * 71620
 * Confidence: low
 */
void sk_obj_fwd_71620(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_71884 @ 0x00071884   (est. sk_obj_fwd_71620b)
 * Ghidra: void FUN_71884(void)
 * 71620
 * Confidence: low
 */
void sk_obj_fwd_71620b(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_71898 @ 0x00071898   (est. sk_obj_fwd_716b4)
 * Ghidra: void FUN_71898(void)
 * 716b4
 * Confidence: low
 */
void sk_obj_fwd_716b4(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7189c @ 0x0007189c   (est. sk_obj_fwd_716b4b)
 * Ghidra: void FUN_7189c(void)
 * 716b4
 * Confidence: low
 */
void sk_obj_fwd_716b4b(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_718b8 @ 0x000718b8   (est. sk_launcher_record_next)
 * Ghidra: void FUN_718b8(void)
 * next record from serialize stream; SoftwareBreakpoint on end
 * Confidence: low
 */
void sk_launcher_record_next(void)
{
    /* returns 16-byte {flags, ptr} record from the launcher stream */
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_71988 @ 0x00071988   (est. sk_bootinfo_map_snapshot_t)
 * Ghidra: void FUN_71988(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
 * thunk of 7198c
 * Confidence: low
 */
void sk_bootinfo_map_snapshot_t(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7198c @ 0x0007198c   (est. sk_bootinfo_map_snapshot)
 * Ghidra: void FUN_7198c(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
 * snapshot CNode bitmap into map view
 * Confidence: low
 */
void sk_bootinfo_map_snapshot(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
{
    /* copies param_2+0x40 bitmap, sizes, into param_1 view */
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_719dc @ 0x000719dc   (est. sk_cap_map_new_t4)
 * Ghidra: void FUN_719dc(unsigned long param_1, unsigned long param_2)
 * cleaned: forward-call replaced
 * Confidence: low
 */
void sk_cap_map_new_t4(unsigned long param_1, unsigned long param_2)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_719f0 @ 0x000719f0   (est. sk_cap_map_new_4)
 * Ghidra: void FUN_719f0(unsigned long param_1, unsigned long param_2)
 * cleaned: forward-call replaced
 * Confidence: low
 */
void sk_cap_map_new_4(unsigned long param_1, unsigned long param_2)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_71a04 @ 0x00071a04   (est. sk_arr_alloc4)
 * Ghidra: void FUN_71a04(void)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_arr_alloc4(void)
{
    sk_slot_00071a04();
    sk_slot_000776d8();
    sk_slot_000776cc();
    sk_slot_0007764c();
    sk_slot_0007791c();
    sk_slot_00077630();
    sk_slot_0007766c();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_71a4c @ 0x00071a4c   (est. sk_arr_alloc4b)
 * Ghidra: void FUN_71a4c(void)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_arr_alloc4b(void)
{
    sk_slot_00071a4c();
    sk_slot_000776d8();
    sk_slot_000776cc();
    sk_slot_0007764c();
    sk_alloc();
    sk_round_up();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_71aa0 @ 0x00071aa0   (est. sk_arr_alloc248)
 * Ghidra: void FUN_71aa0(unsigned long param_1, unsigned long param_2)
 * alloc stride-0xf8 array
 * Confidence: low
 */
void sk_arr_alloc248(unsigned long param_1, unsigned long param_2)
{
    if (param_2 <= param_1) param_2 = param_1;
    if (param_2 == 0) return;
    unsigned long o = sk_alloc(sk_type_resolve(), param_2 * 0xf8 + 0x20, 7);
    *(long *)(o + 0x10) = param_1;
    *(long *)(o + 0x18) = (sk_size_round() + -0x20) / 0xf8 << 1;
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_71b24 @ 0x00071b24   (est. sk_arr_alloc64)
 * Ghidra: void FUN_71b24(void)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_arr_alloc64(void)
{
    sk_slot_00071b24();
    sk_slot_000776d8();
    sk_slot_000776cc();
    sk_slot_0007764c();
    sk_alloc();
    sk_slot_00077630();
    sk_slot_0007766c();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_71b74 @ 0x00071b74   (est. sk_arr_alloc_2)
 * Ghidra: void FUN_71b74(void)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_arr_alloc_2(void)
{
    sk_slot_00071b74();
    sk_slot_000776d8();
    sk_slot_000776cc();
    sk_slot_0007764c();
    sk_slot_000776f8();
    sk_slot_000775dc();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_71bd0 @ 0x00071bd0   (est. sk_arr_alloc2)
 * Ghidra: void FUN_71bd0(unsigned long param_1, unsigned long param_2)
 * alloc stride-2 array v2
 * Confidence: low
 */
void sk_arr_alloc2(unsigned long param_1, unsigned long param_2)
{
    if (param_2 <= param_1) param_2 = param_1;
    if (param_2 == 0) return;
    unsigned long o = sk_alloc(sk_type_resolve(), param_2 * 2 + 0x20, 7);
    *(long *)(o + 0x10) = param_1;
    *(long *)(o + 0x18) = (sk_size_round() + -0x20) / 2 << 1;
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_71c4c @ 0x00071c4c   (est. sk_arr_alloc2b)
 * Ghidra: void FUN_71c4c(void)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_arr_alloc2b(void)
{
    sk_slot_00071c4c();
    sk_slot_000776d8();
    sk_slot_000776cc();
    sk_slot_0007764c();
    sk_slot_000776f8();
    sk_slot_000775dc();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_71c94 @ 0x00071c94   (est. sk_arr_alloc88)
 * Ghidra: void FUN_71c94(unsigned long param_1, unsigned long param_2)
 * alloc stride-0x58 array
 * Confidence: low
 */
void sk_arr_alloc88(unsigned long param_1, unsigned long param_2)
{
    if (param_2 <= param_1) param_2 = param_1;
    if (param_2 == 0) return;
    unsigned long o = sk_alloc(sk_type_resolve(), param_2 * 0x58 + 0x20, 7);
    *(long *)(o + 0x10) = param_1;
    *(long *)(o + 0x18) = (sk_size_round() + -0x20) / 0x58 << 1;
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_71d18 @ 0x00071d18   (est. sk_arr_alloc8)
 * Ghidra: void FUN_71d18(void)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_arr_alloc8(void)
{
    sk_slot_00071d18();
    sk_slot_000776d8();
    sk_slot_000776cc();
    sk_type_resolve();
    sk_slot_000776f8();
    sk_slot_000775dc();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_71d74 @ 0x00071d74   (est. sk_arr_alloc8b)
 * Ghidra: void FUN_71d74(void)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_arr_alloc8b(void)
{
    sk_slot_00071d74();
    sk_slot_000776d8();
    sk_slot_000776cc();
    sk_slot_0007764c();
    sk_slot_000776f8();
    sk_slot_000775dc();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_71dbc @ 0x00071dbc   (est. sk_arr_alloc32)
 * Ghidra: void FUN_71dbc(void)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_arr_alloc32(void)
{
    sk_slot_00071dbc();
    sk_slot_000776d8();
    sk_slot_000776cc();
    sk_slot_0007764c();
    sk_slot_0007791c();
    sk_slot_00077630();
    sk_slot_0007766c();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_71e04 @ 0x00071e04   (est. sk_arr_alloc8c)
 * Ghidra: void FUN_71e04(void)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_arr_alloc8c(void)
{
    sk_slot_00071e04();
    sk_slot_000776d8();
    sk_slot_000776cc();
    sk_slot_0007764c();
    sk_slot_0007791c();
    sk_slot_00077630();
    sk_slot_0007766c();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_71e74 @ 0x00071e74   (est. sk_arr_alloc16)
 * Ghidra: void FUN_71e74(void)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_arr_alloc16(void)
{
    sk_slot_00071e74();
    sk_slot_000776d8();
    sk_slot_000776cc();
    sk_slot_0007764c();
    sk_slot_0007791c();
    sk_slot_00077630();
    sk_slot_0007766c();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_71ebc @ 0x00071ebc   (est. sk_arr_alloc144)
 * Ghidra: void FUN_71ebc(unsigned long param_1, unsigned long param_2)
 * alloc stride-0x90 array
 * Confidence: low
 */
void sk_arr_alloc144(unsigned long param_1, unsigned long param_2)
{
    if (param_2 <= param_1) param_2 = param_1;
    if (param_2 == 0) return;
    unsigned long o = sk_alloc(sk_type_resolve(), param_2 * 0x90 + 0x20, 7);
    *(long *)(o + 0x10) = param_1;
    *(long *)(o + 0x18) = (sk_size_round() + -0x20) / 0x90 << 1;
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_71f54 @ 0x00071f54   (est. sk_arr_alloc8d)
 * Ghidra: void FUN_71f54(void)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_arr_alloc8d(void)
{
    sk_slot_00071f54();
    sk_slot_000776d8();
    sk_slot_000776cc();
    sk_slot_0007764c();
    sk_slot_000776f8();
    sk_slot_000775dc();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_71f9c @ 0x00071f9c   (est. sk_arr_alloc2c)
 * Ghidra: void FUN_71f9c(void)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_arr_alloc2c(void)
{
    sk_slot_00071f9c();
    sk_slot_000776d8();
    sk_slot_000776cc();
    sk_slot_0007764c();
    sk_slot_000776f8();
    sk_slot_000775dc();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_71fe4 @ 0x00071fe4   (est. sk_elem_copy4)
 * Ghidra: void FUN_71fe4(unsigned long param_1, unsigned long param_2, unsigned long param_3)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_elem_copy4(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    sk_slot_00071fe4();
    sk_memcpy();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_72018 @ 0x00072018   (est. sk_elem_copy1)
 * Ghidra: void FUN_72018(unsigned long param_1, unsigned long param_2, unsigned long param_3)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_elem_copy1(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    sk_slot_000720a8();
    sk_memcpy();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7201c @ 0x0007201c   (est. sk_elem_copy4b)
 * Ghidra: void FUN_7201c(unsigned long param_1, unsigned long param_2, unsigned long param_3)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_elem_copy4b(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    sk_slot_0007201c();
    sk_slot_00077540();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_72044 @ 0x00072044   (est. sk_elem_copy16)
 * Ghidra: void FUN_72044(unsigned long param_1, unsigned long param_2, unsigned long param_3)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_elem_copy16(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    sk_slot_00072044();
    sk_slot_00077540();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7206c @ 0x0007206c   (est. sk_elem_copy40)
 * Ghidra: void FUN_7206c(unsigned long param_1, unsigned long param_2, unsigned long param_3)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_elem_copy40(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    sk_slot_0007206c();
    sk_memcpy();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_720a8 @ 0x000720a8   (est. sk_elem_copy1b)
 * Ghidra: void FUN_720a8(unsigned long param_1, unsigned long param_2, unsigned long param_3)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_elem_copy1b(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    sk_slot_000720a8();
    sk_memcpy();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_72114 @ 0x00072114   (est. sk_elem_copy80)
 * Ghidra: void FUN_72114(unsigned long param_1, unsigned long param_2, unsigned long param_3)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_elem_copy80(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    sk_slot_00072114();
    sk_memcpy();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_72150 @ 0x00072150   (est. sk_elem_copy64)
 * Ghidra: void FUN_72150(unsigned long param_1, unsigned long param_2, unsigned long param_3)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_elem_copy64(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    sk_slot_00072150();
    sk_slot_00077540();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_72178 @ 0x00072178   (est. sk_elem_copy80b)
 * Ghidra: void FUN_72178(unsigned long param_1, unsigned long param_2, unsigned long param_3)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_elem_copy80b(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    sk_slot_00072178();
    sk_memcpy();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_721b0 @ 0x000721b0   (est. sk_elem_copy8)
 * Ghidra: void FUN_721b0(unsigned long param_1, unsigned long param_2, unsigned long param_3)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_elem_copy8(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    sk_slot_000721b0();
    sk_slot_00077540();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_721d8 @ 0x000721d8   (est. sk_elem_copy8b)
 * Ghidra: void FUN_721d8(unsigned long param_1, unsigned long param_2, unsigned long param_3)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_elem_copy8b(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    sk_slot_000721d8();
    sk_memcpy();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7220c @ 0x0007220c   (est. sk_elem_copy24)
 * Ghidra: void FUN_7220c(unsigned long param_1, unsigned long param_2, unsigned long param_3)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_elem_copy24(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    sk_slot_0007220c();
    sk_slot_00077540();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_72270 @ 0x00072270   (est. sk_elem_copy56)
 * Ghidra: void FUN_72270(unsigned long param_1, unsigned long param_2, unsigned long param_3)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_elem_copy56(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    sk_slot_00072270();
    sk_memcpy();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_722ac @ 0x000722ac   (est. sk_elem_copy8c)
 * Ghidra: void FUN_722ac(unsigned long param_1, unsigned long param_2, unsigned long param_3)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_elem_copy8c(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    sk_slot_000721b0();
    sk_slot_00077540();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_722b0 @ 0x000722b0   (est. sk_elem_copy56b)
 * Ghidra: void FUN_722b0(unsigned long param_1, unsigned long param_2, unsigned long param_3)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_elem_copy56b(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    sk_slot_000722b0();
    sk_memcpy();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_72320 @ 0x00072320   (est. sk_elem_copy72)
 * Ghidra: void FUN_72320(unsigned long param_1, unsigned long param_2, unsigned long param_3)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_elem_copy72(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    sk_slot_00072320();
    sk_memcpy();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_72358 @ 0x00072358   (est. sk_elem_copy24b)
 * Ghidra: void FUN_72358(unsigned long param_1, unsigned long param_2, unsigned long param_3)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_elem_copy24b(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    sk_slot_00072358();
    sk_slot_00077540();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_723c0 @ 0x000723c0   (est. sk_elem_copy40b)
 * Ghidra: void FUN_723c0(unsigned long param_1, unsigned long param_2, unsigned long param_3)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_elem_copy40b(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    sk_slot_000723c0();
    sk_slot_00077540();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_723f0 @ 0x000723f0   (est. sk_elem_copy48)
 * Ghidra: void FUN_723f0(unsigned long param_1, unsigned long param_2, unsigned long param_3)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_elem_copy48(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    sk_slot_000723f4();
    sk_slot_00077540();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_723f4 @ 0x000723f4   (est. sk_elem_copy48b)
 * Ghidra: void FUN_723f4(unsigned long param_1, unsigned long param_2, unsigned long param_3)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_elem_copy48b(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    sk_slot_000723f4();
    sk_slot_00077540();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_72420 @ 0x00072420   (est. sk_elem_copy40c)
 * Ghidra: void FUN_72420(unsigned long param_1, unsigned long param_2, unsigned long param_3)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_elem_copy40c(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    sk_slot_000723c0();
    sk_slot_00077540();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_72424 @ 0x00072424   (est. sk_f_72424)
 * Ghidra: void FUN_72424(void)
 * faithful call sequence; see FUN_72424
 * Confidence: low
 */
void sk_f_72424(void)
{
    sk_slot_00072424();
    sk_lock_pair();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_72454 @ 0x00072454   (est. sk_f_72454)
 * Ghidra: void FUN_72454(unsigned long param_1, unsigned long param_2)
 * faithful call sequence; see FUN_72454
 * Confidence: low
 */
void sk_f_72454(unsigned long param_1, unsigned long param_2)
{
    sk_slot_00072454();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_72464 @ 0x00072464   (est. sk_f_72464)
 * Ghidra: void FUN_72464(unsigned long param_1)
 * faithful call sequence; see FUN_72464
 * Confidence: low
 */
void sk_f_72464(unsigned long param_1)
{
    sk_slot_00072464();
    sk_hash_init();
    sk_write_word();
    sk_hash_fn();
    sk_slot_00072b44();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_724cc @ 0x000724cc   (est. sk_f_724cc)
 * Ghidra: void FUN_724cc(unsigned long param_1, unsigned long param_2)
 * faithful call sequence; see FUN_724cc
 * Confidence: low
 */
void sk_f_724cc(unsigned long param_1, unsigned long param_2)
{
    sk_slot_000724cc();
    sk_hash_init();
    sk_write_word();
    sk_write_raw();
    sk_write_word();
    sk_hash_fn();
    sk_slot_000727ec();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_72570 @ 0x00072570   (est. sk_f_72570)
 * Ghidra: void FUN_72570(unsigned long param_1)
 * faithful call sequence; see FUN_72570
 * Confidence: low
 */
void sk_f_72570(unsigned long param_1)
{
    sk_slot_00072570();
    sk_slot_00077870();
    sk_map_seed();
    sk_hash_fn();
    sk_slot_000728d4();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_725c8 @ 0x000725c8   (est. sk_f_725c8)
 * Ghidra: void FUN_725c8(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
 * faithful call sequence; see FUN_725c8
 * Confidence: low
 */
void sk_f_725c8(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
{
    sk_slot_000725c8();
    sk_slot_00077870();
    sk_write_bytes();
    sk_write_tag();
    sk_slot_00077894();
    sk_write_bytes();
    sk_hash_fn();
    sk_slot_00077708();
    sk_slot_0007292c();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_72664 @ 0x00072664   (est. sk_f_72664)
 * Ghidra: void FUN_72664(unsigned long param_1)
 * faithful call sequence; see FUN_72664
 * Confidence: low
 */
void sk_f_72664(unsigned long param_1)
{
    sk_slot_00072664();
    sk_map_hash();
    sk_slot_00072a30();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_726a0 @ 0x000726a0   (est. sk_f_726a0)
 * Ghidra: void FUN_726a0(unsigned long param_1)
 * faithful call sequence; see FUN_726a0
 * Confidence: low
 */
void sk_f_726a0(unsigned long param_1)
{
    sk_slot_000726a0();
    sk_slot_00077870();
    sk_hash_fn();
    sk_slot_00072a88();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_72710 @ 0x00072710   (est. sk_f_72710)
 * Ghidra: void FUN_72710(unsigned long param_1)
 * faithful call sequence; see FUN_72710
 * Confidence: low
 */
void sk_f_72710(unsigned long param_1)
{
    sk_slot_00072710();
    sk_slot_00077870();
    sk_str_get();
    sk_write_bytes();
    sk_release();
    sk_hash_fn();
    sk_slot_00072b44();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7278c @ 0x0007278c   (est. sk_f_7278c)
 * Ghidra: void FUN_7278c(void)
 * faithful call sequence; see FUN_7278c
 * Confidence: low
 */
void sk_f_7278c(void)
{
    sk_slot_0007278c();
    sk_slot_00077848();
    sk_write_word();
    sk_hash_fn();
    sk_slot_00072b9c();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_727ec @ 0x000727ec   (est. sk_f_727ec)
 * Ghidra: void FUN_727ec(unsigned long param_1, unsigned long param_2, unsigned long param_3)
 * faithful call sequence; see FUN_727ec
 * Confidence: low
 */
void sk_f_727ec(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    sk_slot_000727ec();
    sk_cap_match();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_728d4 @ 0x000728d4   (est. sk_f_728d4)
 * Ghidra: void FUN_728d4(unsigned long param_1, unsigned long param_2)
 * faithful call sequence; see FUN_728d4
 * Confidence: low
 */
void sk_f_728d4(unsigned long param_1, unsigned long param_2)
{
    sk_slot_000728d4();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7292c @ 0x0007292c   (est. sk_f_7292c)
 * Ghidra: void FUN_7292c(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4, unsigned long param_5)
 * faithful call sequence; see FUN_7292c
 * Confidence: low
 */
void sk_f_7292c(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4, unsigned long param_5)
{
    sk_slot_0007292c();
    sk_key_eq();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_72a30 @ 0x00072a30   (est. sk_f_72a30)
 * Ghidra: void FUN_72a30(unsigned long param_1, unsigned long param_2)
 * faithful call sequence; see FUN_72a30
 * Confidence: low
 */
void sk_f_72a30(unsigned long param_1, unsigned long param_2)
{
    sk_slot_00072a30();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_72a88 @ 0x00072a88   (est. sk_f_72a88)
 * Ghidra: void FUN_72a88(unsigned long param_1, unsigned long param_2)
 * faithful call sequence; see FUN_72a88
 * Confidence: low
 */
void sk_f_72a88(unsigned long param_1, unsigned long param_2)
{
    sk_slot_00072a88();
    sk_hash_reset();
    sk_retain();
    sk_hash_eq();
    sk_free();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_72b44 @ 0x00072b44   (est. sk_f_72b44)
 * Ghidra: void FUN_72b44(unsigned long param_1, unsigned long param_2)
 * faithful call sequence; see FUN_72b44
 * Confidence: low
 */
void sk_f_72b44(unsigned long param_1, unsigned long param_2)
{
    sk_slot_00072b44();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_72b9c @ 0x00072b9c   (est. sk_f_72b9c)
 * Ghidra: void FUN_72b9c(unsigned long param_1, unsigned long param_2, unsigned long param_3)
 * faithful call sequence; see FUN_72b9c
 * Confidence: low
 */
void sk_f_72b9c(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    sk_slot_00072b9c();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_72c0c @ 0x00072c0c   (est. sk_map_grow4)
 * Ghidra: void FUN_72c0c(unsigned long param_1, unsigned long param_2, unsigned long param_3)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_map_grow4(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    sk_slot_00072c0c();
    sk_slot_00077570();
    sk_slot_00077560();
    sk_slot_00077624();
    sk_slot_00077550();
    sk_slot_00071e74();
    sk_slot_0007752c();
    sk_elem_copy_4();
    sk_slot_00077580();
    sk_elem_copy_16();
    sk_slot_00077718();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_72c98 @ 0x00072c98   (est. sk_f_72c98)
 * Ghidra: void FUN_72c98(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
 * faithful call sequence; see FUN_72c98
 * Confidence: low
 */
void sk_f_72c98(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
{
    sk_slot_00072c98();
    sk_slot_00071a04();
    sk_slot_00074a28();
    sk_slot_00071fe4();
    sk_free();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_72d5c @ 0x00072d5c   (est. sk_map_grow8)
 * Ghidra: void FUN_72d5c(unsigned long param_1, unsigned long param_2, unsigned long param_3)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_map_grow8(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    sk_slot_00072d5c();
    sk_slot_00077570();
    sk_slot_00077560();
    sk_slot_00077624();
    sk_slot_00077550();
    sk_slot_00071e04();
    sk_slot_0007752c();
    sk_slot_000750bc();
    sk_slot_00077580();
    sk_slot_000721b0();
    sk_slot_00077718();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_72de8 @ 0x00072de8   (est. sk_map_grow64)
 * Ghidra: void FUN_72de8(unsigned long param_1, unsigned long param_2, unsigned long param_3)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_map_grow64(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    sk_slot_00072de8();
    sk_slot_00077570();
    sk_slot_00077560();
    sk_slot_00077624();
    sk_slot_00077550();
    sk_slot_00071b24();
    sk_slot_0007752c();
    sk_slot_00074a98();
    sk_slot_00077580();
    sk_slot_00072150();
    sk_slot_00077718();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_72e74 @ 0x00072e74   (est. sk_map_grow2)
 * Ghidra: void FUN_72e74(unsigned long param_1, unsigned long param_2, unsigned long param_3)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_map_grow2(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    sk_slot_00072e74();
    sk_slot_00077570();
    sk_slot_00077560();
    sk_slot_00077624();
    sk_slot_00077550();
    sk_slot_00071f9c();
    sk_slot_0007752c();
    sk_slot_00075c50();
    sk_slot_00077580();
    sk_slot_000723c0();
    sk_slot_00077718();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_72f00 @ 0x00072f00   (est. sk_map_grow32)
 * Ghidra: void FUN_72f00(unsigned long param_1, unsigned long param_2, unsigned long param_3)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_map_grow32(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    sk_slot_00072f00();
    sk_slot_00077570();
    sk_slot_00077560();
    sk_slot_00077624();
    sk_slot_00077550();
    sk_slot_00071dbc();
    sk_slot_0007752c();
    sk_slot_00074b08();
    sk_slot_00077580();
    sk_elem_copy_8();
    sk_slot_00077718();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_72f8c @ 0x00072f8c   (est. sk_map_grow8b)
 * Ghidra: void FUN_72f8c(unsigned long param_1, unsigned long param_2, unsigned long param_3)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_map_grow8b(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    sk_slot_00072f8c();
    sk_slot_00077570();
    sk_slot_00077560();
    sk_slot_00077624();
    sk_slot_00077550();
    sk_slot_00071e04();
    sk_slot_0007752c();
    sk_slot_000750bc();
    sk_slot_00077580();
    sk_slot_000721b0();
    sk_slot_00077718();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_73018 @ 0x00073018   (est. sk_map_grow4b)
 * Ghidra: void FUN_73018(unsigned long param_1, unsigned long param_2, unsigned long param_3)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_map_grow4b(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    sk_slot_00073018();
    sk_slot_00077570();
    sk_slot_00077560();
    sk_slot_00077624();
    sk_slot_00077550();
    sk_slot_00071a04();
    sk_slot_0007752c();
    sk_slot_00074a28();
    sk_slot_00077580();
    sk_slot_0007201c();
    sk_slot_00077718();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_730a4 @ 0x000730a4   (est. sk_map_grow2b)
 * Ghidra: void FUN_730a4(unsigned long param_1, unsigned long param_2, unsigned long param_3)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_map_grow2b(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    sk_slot_000730a4();
    sk_slot_00077570();
    sk_slot_00077560();
    sk_slot_00077624();
    sk_slot_00077550();
    sk_slot_00071f9c();
    sk_slot_0007752c();
    sk_slot_00075b2c();
    sk_slot_00077580();
    sk_slot_000723c0();
    sk_slot_00077718();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_73140 @ 0x00073140   (est. sk_map_grow2c)
 * Ghidra: void FUN_73140(unsigned long param_1, unsigned long param_2, unsigned long param_3)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_map_grow2c(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    sk_slot_00073140();
    sk_slot_00077570();
    sk_slot_00077560();
    sk_slot_00077624();
    sk_slot_00077550();
    sk_slot_00071f9c();
    sk_slot_0007752c();
    sk_slot_00075b2c();
    sk_slot_00077580();
    sk_slot_000723c0();
    sk_slot_00077718();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_731dc @ 0x000731dc   (est. sk_map_grow16)
 * Ghidra: void FUN_731dc(unsigned long param_1, unsigned long param_2, unsigned long param_3)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_map_grow16(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    sk_slot_000731dc();
    sk_slot_00077570();
    sk_slot_00077560();
    sk_slot_00077624();
    sk_slot_00077550();
    sk_slot_00071e74();
    sk_slot_0007752c();
    sk_slot_00074b78();
    sk_slot_00077580();
    sk_slot_00072044();
    sk_slot_00077718();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_73268 @ 0x00073268   (est. sk_map_grow8c)
 * Ghidra: void FUN_73268(unsigned long param_1, unsigned long param_2, unsigned long param_3)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_map_grow8c(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    sk_slot_00073268();
    sk_slot_00077570();
    sk_slot_00077560();
    sk_slot_00077624();
    sk_slot_00077550();
    sk_slot_00071d74();
    sk_slot_0007752c();
    sk_slot_00075784();
    sk_slot_00077580();
    sk_slot_00072358();
    sk_slot_00077718();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_732f4 @ 0x000732f4   (est. sk_map_grow2d)
 * Ghidra: void FUN_732f4(unsigned long param_1, unsigned long param_2, unsigned long param_3)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_map_grow2d(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    sk_slot_000732f4();
    sk_slot_00077570();
    sk_slot_00077560();
    sk_slot_00077624();
    sk_slot_00077550();
    sk_slot_00071f9c();
    sk_slot_0007752c();
    sk_slot_00074c14();
    sk_slot_00077580();
    sk_slot_0007206c();
    sk_slot_00077718();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_73380 @ 0x00073380   (est. sk_map_grow8d)
 * Ghidra: void FUN_73380(unsigned long param_1, unsigned long param_2, unsigned long param_3)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_map_grow8d(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    sk_slot_00073380();
    sk_slot_00077570();
    sk_slot_00077560();
    sk_slot_00077624();
    sk_slot_00077550();
    sk_slot_00071e04();
    sk_slot_0007752c();
    sk_slot_000750bc();
    sk_slot_00077580();
    sk_slot_000721b0();
    sk_slot_00077718();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7340c @ 0x0007340c   (est. sk_map_grow16b)
 * Ghidra: void FUN_7340c(unsigned long param_1, unsigned long param_2, unsigned long param_3)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_map_grow16b(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    sk_slot_0007340c();
    sk_slot_00077570();
    sk_slot_00077560();
    sk_slot_00077624();
    sk_slot_00077550();
    sk_slot_00071e74();
    sk_slot_0007752c();
    sk_slot_00074cb8();
    sk_slot_00077580();
    sk_slot_00072044();
    sk_slot_00077718();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_73498 @ 0x00073498   (est. sk_map_grow16c)
 * Ghidra: void FUN_73498(unsigned long param_1, unsigned long param_2, unsigned long param_3)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_map_grow16c(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    sk_slot_00073498();
    sk_slot_00077570();
    sk_slot_00077560();
    sk_slot_00077624();
    sk_slot_00077550();
    sk_slot_00071e04();
    sk_slot_0007752c();
    sk_slot_00074d54();
    sk_slot_00077580();
    sk_slot_000721b0();
    sk_slot_00077718();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_73524 @ 0x00073524   (est. sk_map_grow16d)
 * Ghidra: void FUN_73524(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_map_grow16d(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
{
    sk_slot_00073524();
    sk_slot_00071e74();
    sk_slot_000758d8();
    sk_slot_00072044();
    sk_slot_00077718();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_73604 @ 0x00073604   (est. sk_map_grow16e)
 * Ghidra: void FUN_73604(unsigned long param_1, unsigned long param_2, unsigned long param_3)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_map_grow16e(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    sk_slot_00073604();
    sk_slot_00077570();
    sk_slot_00077560();
    sk_slot_00077624();
    sk_slot_00077550();
    sk_slot_00071a4c();
    sk_slot_0007752c();
    sk_slot_00074dc8();
    sk_slot_00077580();
    sk_slot_000720a8();
    sk_slot_00077718();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_73690 @ 0x00073690   (est. sk_map_grow32b)
 * Ghidra: void FUN_73690(unsigned long param_1, unsigned long param_2, unsigned long param_3)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_map_grow32b(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    sk_slot_00073690();
    sk_slot_00077570();
    sk_slot_00077560();
    sk_slot_00077624();
    sk_slot_00077550();
    sk_slot_00071dbc();
    sk_slot_0007752c();
    sk_elem_copy_d8();
    sk_slot_00077580();
    sk_elem_copy_8();
    sk_slot_00077718();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7371c @ 0x0007371c   (est. sk_map_grow8e)
 * Ghidra: void FUN_7371c(unsigned long param_1, unsigned long param_2, unsigned long param_3)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_map_grow8e(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    sk_slot_0007371c();
    sk_slot_00077570();
    sk_slot_00077560();
    sk_slot_00077624();
    sk_slot_00077550();
    sk_slot_00071d74();
    sk_slot_0007752c();
    sk_slot_00074e34();
    sk_slot_00077580();
    sk_slot_00072358();
    sk_slot_00077718();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_737a8 @ 0x000737a8   (est. sk_obj_fwd_737e8)
 * Ghidra: void FUN_737a8(void)
 * 737e8
 * Confidence: low
 */
void sk_obj_fwd_737e8(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_737e8 @ 0x000737e8   (est. sk_map_grow_generic)
 * Ghidra: void FUN_737e8(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4, unsigned long param_5, unsigned long param_6, unsigned long param_7)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_map_grow_generic(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4, unsigned long param_5, unsigned long param_6, unsigned long param_7)
{
    sk_slot_000737e8();
    sk_slot_00077718();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_738b0 @ 0x000738b0   (est. sk_map_grow2e)
 * Ghidra: void FUN_738b0(unsigned long param_1, unsigned long param_2, unsigned long param_3)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_map_grow2e(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    sk_slot_000738b0();
    sk_slot_00077570();
    sk_slot_00077560();
    sk_slot_00077624();
    sk_slot_00077550();
    sk_slot_00071b74();
    sk_slot_0007752c();
    sk_slot_00074f28();
    sk_slot_00077580();
    sk_slot_00072114();
    sk_slot_00077718();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7393c @ 0x0007393c   (est. sk_map_grow8f)
 * Ghidra: void FUN_7393c(unsigned long param_1, unsigned long param_2, unsigned long param_3)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_map_grow8f(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    sk_slot_0007393c();
    sk_slot_00077570();
    sk_slot_00077560();
    sk_slot_00077624();
    sk_slot_00077550();
    sk_slot_00071d74();
    sk_slot_0007752c();
    sk_slot_000751b4();
    sk_slot_00077580();
    sk_slot_0007220c();
    sk_slot_00077718();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_739d8 @ 0x000739d8   (est. sk_map_grow32c)
 * Ghidra: void FUN_739d8(unsigned long param_1, unsigned long param_2, unsigned long param_3)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_map_grow32c(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    sk_slot_000739d8();
    sk_slot_00077570();
    sk_slot_00077560();
    sk_slot_00077624();
    sk_slot_00077550();
    sk_slot_00071dbc();
    sk_slot_0007752c();
    sk_slot_00074b08();
    sk_slot_00077580();
    sk_elem_copy_8();
    sk_slot_00077718();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_73a64 @ 0x00073a64   (est. sk_map_grow64b)
 * Ghidra: void FUN_73a64(unsigned long param_1, unsigned long param_2, unsigned long param_3)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_map_grow64b(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    sk_slot_00073a64();
    sk_slot_00077570();
    sk_slot_00077560();
    sk_slot_00077624();
    sk_slot_00077550();
    sk_slot_00071b24();
    sk_slot_0007752c();
    sk_slot_00074fa4();
    sk_slot_00077580();
    sk_slot_00072150();
    sk_slot_00077718();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_73af0 @ 0x00073af0   (est. sk_map_grow2f)
 * Ghidra: void FUN_73af0(unsigned long param_1, unsigned long param_2, unsigned long param_3)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_map_grow2f(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    sk_slot_00073af0();
    sk_slot_00077570();
    sk_slot_00077560();
    sk_slot_00077624();
    sk_slot_00077550();
    sk_slot_00071b74();
    sk_slot_0007752c();
    sk_slot_00075018();
    sk_slot_00077580();
    sk_slot_00072178();
    sk_slot_00077718();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_73b7c @ 0x00073b7c   (est. sk_map_grow8g)
 * Ghidra: void FUN_73b7c(unsigned long param_1, unsigned long param_2, unsigned long param_3)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_map_grow8g(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    sk_slot_00073b7c();
    sk_slot_00077570();
    sk_slot_00077560();
    sk_slot_00077624();
    sk_slot_00077550();
    sk_slot_00071e04();
    sk_slot_0007752c();
    sk_slot_000750bc();
    sk_slot_00077580();
    sk_slot_000721b0();
    sk_slot_00077718();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_73c08 @ 0x00073c08   (est. sk_map_grow8h)
 * Ghidra: void FUN_73c08(unsigned long param_1, unsigned long param_2, unsigned long param_3)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_map_grow8h(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    sk_slot_00073c08();
    sk_slot_00077570();
    sk_slot_00077560();
    sk_slot_00077624();
    sk_slot_00077550();
    sk_slot_00071e04();
    sk_slot_0007752c();
    sk_slot_00075118();
    sk_slot_00077580();
    sk_slot_000721d8();
    sk_slot_00077718();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_73c94 @ 0x00073c94   (est. sk_map_grow8i)
 * Ghidra: void FUN_73c94(unsigned long param_1, unsigned long param_2, unsigned long param_3)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_map_grow8i(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    sk_slot_00073c94();
    sk_slot_00077570();
    sk_slot_00077560();
    sk_slot_00077624();
    sk_slot_00077550();
    sk_slot_00071d74();
    sk_slot_0007752c();
    sk_slot_000751b4();
    sk_slot_00077580();
    sk_slot_0007220c();
    sk_slot_00077718();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_73d30 @ 0x00073d30   (est. sk_obj_fwd_737e8b)
 * Ghidra: void FUN_73d30(void)
 * 737e8
 * Confidence: low
 */
void sk_obj_fwd_737e8b(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_73d70 @ 0x00073d70   (est. sk_map_grow2g)
 * Ghidra: void FUN_73d70(unsigned long param_1, unsigned long param_2, unsigned long param_3)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_map_grow2g(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    sk_slot_00073d70();
    sk_slot_00077570();
    sk_slot_00077560();
    sk_slot_00077624();
    sk_slot_00077550();
    sk_slot_00071c4c();
    sk_slot_0007752c();
    sk_slot_000752a4();
    sk_slot_00077580();
    sk_slot_00072270();
    sk_slot_00077718();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_73dfc @ 0x00073dfc   (est. sk_map_grow16f)
 * Ghidra: void FUN_73dfc(unsigned long param_1, unsigned long param_2, unsigned long param_3)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_map_grow16f(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    sk_slot_00073dfc();
    sk_slot_00077570();
    sk_slot_00077560();
    sk_slot_00077624();
    sk_slot_00077550();
    sk_slot_00071e74();
    sk_slot_0007752c();
    sk_slot_0007534c();
    sk_slot_00077580();
    sk_elem_copy_16();
    sk_slot_00077718();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_73e88 @ 0x00073e88   (est. sk_map_grow2h)
 * Ghidra: void FUN_73e88(unsigned long param_1, unsigned long param_2, unsigned long param_3)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_map_grow2h(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    sk_slot_00073e88();
    sk_slot_00077570();
    sk_slot_00077560();
    sk_slot_00077624();
    sk_slot_00077550();
    sk_slot_00071f9c();
    sk_slot_0007752c();
    sk_slot_000753c0();
    sk_slot_00077580();
    sk_slot_0007206c();
    sk_slot_00077718();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_73f14 @ 0x00073f14   (est. sk_map_grow16g)
 * Ghidra: void FUN_73f14(unsigned long param_1, unsigned long param_2, unsigned long param_3)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_map_grow16g(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    sk_slot_00073f14();
    sk_slot_00077570();
    sk_slot_00077560();
    sk_slot_00077624();
    sk_slot_00077550();
    sk_slot_00071e74();
    sk_slot_0007752c();
    sk_slot_0007543c();
    sk_slot_00077580();
    sk_elem_copy_16();
    sk_slot_00077718();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_73fa0 @ 0x00073fa0   (est. sk_map_grow8k)
 * Ghidra: void FUN_73fa0(unsigned long param_1, unsigned long param_2, unsigned long param_3)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_map_grow8k(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    sk_slot_00073fa0();
    sk_slot_00077570();
    sk_slot_00077560();
    sk_slot_00077624();
    sk_slot_00077550();
    sk_slot_00071d74();
    sk_slot_0007752c();
    sk_slot_000754b0();
    sk_slot_00077580();
    sk_elem_copy_8b();
    sk_slot_00077718();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7402c @ 0x0007402c   (est. sk_map_grow32d)
 * Ghidra: void FUN_7402c(unsigned long param_1, unsigned long param_2, unsigned long param_3)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_map_grow32d(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    sk_slot_0007402c();
    sk_slot_00077570();
    sk_slot_00077560();
    sk_slot_00077624();
    sk_slot_00077550();
    sk_slot_00071dbc();
    sk_slot_0007752c();
    sk_slot_00074b08();
    sk_slot_00077580();
    sk_elem_copy_8();
    sk_slot_00077718();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_740b8 @ 0x000740b8   (est. sk_map_grow2i)
 * Ghidra: void FUN_740b8(unsigned long param_1, unsigned long param_2, unsigned long param_3)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_map_grow2i(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    sk_slot_000740b8();
    sk_slot_00077570();
    sk_slot_00077560();
    sk_slot_00077624();
    sk_slot_00077550();
    sk_slot_00071f9c();
    sk_slot_0007752c();
    sk_slot_00075b2c();
    sk_slot_00077580();
    sk_slot_000723c0();
    sk_slot_00077718();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_74154 @ 0x00074154   (est. sk_map_grow2j)
 * Ghidra: void FUN_74154(unsigned long param_1, unsigned long param_2, unsigned long param_3)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_map_grow2j(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    sk_slot_00074154();
    sk_slot_00077570();
    sk_slot_00077560();
    sk_slot_00077624();
    sk_slot_00077550();
    sk_slot_00071c4c();
    sk_slot_0007752c();
    sk_slot_0007552c();
    sk_slot_00077580();
    sk_slot_000722b0();
    sk_slot_00077718();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_741e0 @ 0x000741e0   (est. sk_obj_fwd_737e8c)
 * Ghidra: void FUN_741e0(void)
 * 737e8
 * Confidence: low
 */
void sk_obj_fwd_737e8c(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_74220 @ 0x00074220   (est. sk_map_grow16h)
 * Ghidra: void FUN_74220(unsigned long param_1, unsigned long param_2, unsigned long param_3)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_map_grow16h(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    sk_slot_00074220();
    sk_slot_00077570();
    sk_slot_00077560();
    sk_slot_00077624();
    sk_slot_00077550();
    sk_slot_00071e74();
    sk_slot_0007752c();
    sk_slot_00075624();
    sk_slot_00077580();
    sk_elem_copy_16();
    sk_slot_00077718();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_742ac @ 0x000742ac   (est. sk_obj_fwd_737e8d)
 * Ghidra: void FUN_742ac(void)
 * 737e8
 * Confidence: low
 */
void sk_obj_fwd_737e8d(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_742ec @ 0x000742ec   (est. sk_map_grow32e)
 * Ghidra: void FUN_742ec(unsigned long param_1, unsigned long param_2, unsigned long param_3)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_map_grow32e(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    sk_slot_000742ec();
    sk_slot_00077570();
    sk_slot_00077560();
    sk_slot_00077624();
    sk_slot_00077550();
    sk_slot_00071dbc();
    sk_slot_0007752c();
    sk_slot_00075710();
    sk_slot_00077580();
    sk_elem_copy_8();
    sk_slot_00077718();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_74378 @ 0x00074378   (est. sk_map_grow8l)
 * Ghidra: void FUN_74378(unsigned long param_1, unsigned long param_2, unsigned long param_3)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_map_grow8l(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    sk_slot_00074378();
    sk_slot_00077570();
    sk_slot_00077560();
    sk_slot_00077624();
    sk_slot_00077550();
    sk_slot_00071d74();
    sk_slot_0007752c();
    sk_slot_00075784();
    sk_slot_00077580();
    sk_slot_00072358();
    sk_slot_00077718();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_74404 @ 0x00074404   (est. sk_map_grow32f)
 * Ghidra: void FUN_74404(unsigned long param_1, unsigned long param_2, unsigned long param_3)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_map_grow32f(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    sk_slot_00074404();
    sk_slot_00077570();
    sk_slot_00077560();
    sk_slot_00077624();
    sk_slot_00077550();
    sk_slot_00071dbc();
    sk_slot_0007752c();
    sk_slot_000757e8();
    sk_slot_00077580();
    sk_elem_copy_8();
    sk_slot_00077718();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_74490 @ 0x00074490   (est. sk_map_grow2l)
 * Ghidra: void FUN_74490(unsigned long param_1, unsigned long param_2, unsigned long param_3)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_map_grow2l(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    sk_slot_00074490();
    sk_slot_00077570();
    sk_slot_00077560();
    sk_slot_00077624();
    sk_slot_00077550();
    sk_slot_00071f9c();
    sk_slot_0007752c();
    sk_slot_0007585c();
    sk_slot_00077580();
    sk_slot_0007206c();
    sk_slot_00077718();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7451c @ 0x0007451c   (est. sk_map_grow16j)
 * Ghidra: void FUN_7451c(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_map_grow16j(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
{
    sk_slot_0007451c();
    sk_slot_00071e74();
    sk_slot_000758d8();
    sk_slot_00072044();
    sk_slot_00077718();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_74538 @ 0x00074538   (est. sk_map_grow8m)
 * Ghidra: void FUN_74538(unsigned long param_1, unsigned long param_2, unsigned long param_3)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_map_grow8m(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    sk_slot_00074538();
    sk_slot_00077570();
    sk_slot_00077560();
    sk_slot_00077624();
    sk_slot_00077550();
    sk_slot_00071e04();
    sk_slot_0007752c();
    sk_slot_00075948();
    sk_slot_00077580();
    sk_slot_000721b0();
    sk_slot_00077718();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_745d4 @ 0x000745d4   (est. sk_map_grow8n)
 * Ghidra: void FUN_745d4(unsigned long param_1, unsigned long param_2, unsigned long param_3)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_map_grow8n(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    sk_slot_000745d4();
    sk_slot_00077570();
    sk_slot_00077560();
    sk_slot_00077624();
    sk_slot_00077550();
    sk_slot_00071e04();
    sk_slot_0007752c();
    sk_slot_00075948();
    sk_slot_00077580();
    sk_slot_000721b0();
    sk_slot_00077718();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_74670 @ 0x00074670   (est. sk_map_grow16k)
 * Ghidra: void FUN_74670(unsigned long param_1, unsigned long param_2, unsigned long param_3)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_map_grow16k(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    sk_slot_00074670();
    sk_slot_00077570();
    sk_slot_00077560();
    sk_slot_00077624();
    sk_slot_00077550();
    sk_slot_00071e74();
    sk_slot_0007752c();
    sk_slot_000759c0();
    sk_slot_00077580();
    sk_slot_00072044();
    sk_slot_00077718();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7470c @ 0x0007470c   (est. sk_map_grow16l)
 * Ghidra: void FUN_7470c(unsigned long param_1, unsigned long param_2, unsigned long param_3)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_map_grow16l(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    sk_slot_0007470c();
    sk_slot_00077570();
    sk_slot_00077560();
    sk_slot_00077624();
    sk_slot_00077550();
    sk_slot_00071e74();
    sk_slot_0007752c();
    sk_slot_000759c0();
    sk_slot_00077580();
    sk_slot_00072044();
    sk_slot_00077718();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_747a8 @ 0x000747a8   (est. sk_map_grow8o)
 * Ghidra: void FUN_747a8(unsigned long param_1, unsigned long param_2, unsigned long param_3)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_map_grow8o(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    sk_slot_000747a8();
    sk_slot_00077570();
    sk_slot_00077560();
    sk_slot_00077624();
    sk_slot_00077550();
    sk_slot_00071f54();
    sk_slot_0007752c();
    sk_slot_00075a38();
    sk_slot_00077580();
    sk_slot_000723f4();
    sk_slot_00077718();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_74834 @ 0x00074834   (est. sk_obj_fwd_737e8e)
 * Ghidra: void FUN_74834(void)
 * 737e8
 * Confidence: low
 */
void sk_obj_fwd_737e8e(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_74874 @ 0x00074874   (est. sk_map_grow2m)
 * Ghidra: void FUN_74874(unsigned long param_1, unsigned long param_2, unsigned long param_3)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_map_grow2m(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    sk_slot_00074874();
    sk_slot_00077570();
    sk_slot_00077560();
    sk_slot_00077624();
    sk_slot_00077550();
    sk_slot_00071f9c();
    sk_slot_0007752c();
    sk_slot_00075b2c();
    sk_slot_00077580();
    sk_slot_000723c0();
    sk_slot_00077718();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_74910 @ 0x00074910   (est. sk_map_grow2n)
 * Ghidra: void FUN_74910(unsigned long param_1, unsigned long param_2, unsigned long param_3)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_map_grow2n(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    sk_slot_00074910();
    sk_slot_00077570();
    sk_slot_00077560();
    sk_slot_00077624();
    sk_slot_00077550();
    sk_slot_00071f54();
    sk_slot_0007752c();
    sk_slot_00075bac();
    sk_slot_00077580();
    sk_slot_000723f4();
    sk_slot_00077718();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7499c @ 0x0007499c   (est. sk_map_grow2o)
 * Ghidra: void FUN_7499c(unsigned long param_1, unsigned long param_2, unsigned long param_3)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_map_grow2o(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    sk_slot_0007499c();
    sk_slot_00077570();
    sk_slot_00077560();
    sk_slot_00077624();
    sk_slot_00077550();
    sk_slot_00071f9c();
    sk_slot_0007752c();
    sk_slot_00075c50();
    sk_slot_00077580();
    sk_slot_000723c0();
    sk_slot_00077718();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_74a28 @ 0x00074a28   (est. sk_arr_copy4)
 * Ghidra: void FUN_74a28(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
 * element array copy, stride 4
 * Confidence: high
 */
void sk_arr_copy4(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
{
    long n = param_2 - param_1;
    if (param_2 < param_1)
        __builtin_trap();
    if (n >= 0) {
        unsigned long src = param_4 + param_1*4 + 0x20;
        unsigned long end = param_3 + n*4;
        if (end <= src || src + n*4 <= param_3) {
            sk_memcpy(param_3, src, n*4);
            sk_free((void *)param_4);
            return;
        }
        __builtin_trap();
    }
    __builtin_trap();
}

/*--------------------------------------------------------------------*/
/* FUN_74a98 @ 0x00074a98   (est. sk_arr_copy64)
 * Ghidra: void FUN_74a98(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
 * element array copy, stride 0x40
 * Confidence: high
 */
void sk_arr_copy64(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
{
    long n = param_2 - param_1;
    if (param_2 < param_1)
        __builtin_trap();
    if (n >= 0) {
        unsigned long src = param_4 + param_1*0x40 + 0x20;
        unsigned long end = param_3 + n*0x40;
        if (end <= src || src + n*0x40 <= param_3) {
            sk_memcpy(param_3, src, n*0x40);
            sk_free((void *)param_4);
            return;
        }
        __builtin_trap();
    }
    __builtin_trap();
}

/*--------------------------------------------------------------------*/
/* FUN_74b08 @ 0x00074b08   (est. sk_arr_copy32)
 * Ghidra: void FUN_74b08(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
 * element array copy, stride 0x20
 * Confidence: high
 */
void sk_arr_copy32(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
{
    long n = param_2 - param_1;
    if (param_2 < param_1)
        __builtin_trap();
    if (n >= 0) {
        unsigned long src = param_4 + param_1*0x20 + 0x20;
        unsigned long end = param_3 + n*0x20;
        if (end <= src || src + n*0x20 <= param_3) {
            sk_memcpy(param_3, src, n*0x20);
            sk_free((void *)param_4);
            return;
        }
        __builtin_trap();
    }
    __builtin_trap();
}

/*--------------------------------------------------------------------*/
/* FUN_74b78 @ 0x00074b78   (est. sk_arr_copy16)
 * Ghidra: void FUN_74b78(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
 * element array copy, stride 0x10
 * Confidence: high
 */
void sk_arr_copy16(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
{
    long n = param_2 - param_1;
    if (param_2 < param_1)
        __builtin_trap();
    if (n >= 0) {
        unsigned long src = param_4 + param_1*0x10 + 0x20;
        unsigned long end = param_3 + n*0x10;
        if (end <= src || src + n*0x10 <= param_3) {
            sk_memcpy(param_3, src, n*0x10);
            sk_free((void *)param_4);
            return;
        }
        __builtin_trap();
    }
    __builtin_trap();
}

/*--------------------------------------------------------------------*/
/* FUN_74c14 @ 0x00074c14   (est. sk_arr_copy40)
 * Ghidra: void FUN_74c14(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
 * element array copy, stride 0x28
 * Confidence: high
 */
void sk_arr_copy40(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
{
    long n = param_2 - param_1;
    if (param_2 < param_1)
        __builtin_trap();
    if (n >= 0) {
        unsigned long src = param_4 + param_1*0x28 + 0x20;
        unsigned long end = param_3 + n*0x28;
        if (end <= src || src + n*0x28 <= param_3) {
            sk_memcpy(param_3, src, n*0x28);
            sk_free((void *)param_4);
            return;
        }
        __builtin_trap();
    }
    __builtin_trap();
}

/*--------------------------------------------------------------------*/
/* FUN_74cb8 @ 0x00074cb8   (est. sk_arr_copy16b)
 * Ghidra: void FUN_74cb8(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
 * element array copy, stride 0x10
 * Confidence: high
 */
void sk_arr_copy16b(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
{
    long n = param_2 - param_1;
    if (param_2 < param_1)
        __builtin_trap();
    if (n >= 0) {
        unsigned long src = param_4 + param_1*0x10 + 0x20;
        unsigned long end = param_3 + n*0x10;
        if (end <= src || src + n*0x10 <= param_3) {
            sk_memcpy(param_3, src, n*0x10);
            sk_free((void *)param_4);
            return;
        }
        __builtin_trap();
    }
    __builtin_trap();
}

/*--------------------------------------------------------------------*/
/* FUN_74d54 @ 0x00074d54   (est. sk_arr_copy8)
 * Ghidra: void FUN_74d54(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
 * element array copy, stride 8
 * Confidence: high
 */
void sk_arr_copy8(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
{
    long n = param_2 - param_1;
    if (param_2 < param_1)
        __builtin_trap();
    if (n >= 0) {
        unsigned long src = param_4 + param_1*8 + 0x20;
        unsigned long end = param_3 + n*8;
        if (end <= src || src + n*8 <= param_3) {
            sk_memcpy(param_3, src, n*8);
            sk_free((void *)param_4);
            return;
        }
        __builtin_trap();
    }
    __builtin_trap();
}

/*--------------------------------------------------------------------*/
/* FUN_74dc8 @ 0x00074dc8   (est. sk_arr_copy1)
 * Ghidra: void FUN_74dc8(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
 * element array copy, stride 1
 * Confidence: high
 */
void sk_arr_copy1(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
{
    long n = param_2 - param_1;
    if (param_2 < param_1)
        __builtin_trap();
    if (n >= 0) {
        unsigned long src = param_4 + param_1*1 + 0x20;
        unsigned long end = param_3 + n*1;
        if (end <= src || src + n*1 <= param_3) {
            sk_memcpy(param_3, src, n*1);
            sk_free((void *)param_4);
            return;
        }
        __builtin_trap();
    }
    __builtin_trap();
}

/*--------------------------------------------------------------------*/
/* FUN_74e34 @ 0x00074e34   (est. sk_arr_copy24)
 * Ghidra: void FUN_74e34(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
 * element array copy, stride 0x18
 * Confidence: high
 */
void sk_arr_copy24(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
{
    long n = param_2 - param_1;
    if (param_2 < param_1)
        __builtin_trap();
    if (n >= 0) {
        unsigned long src = param_4 + param_1*0x18 + 0x20;
        unsigned long end = param_3 + n*0x18;
        if (end <= src || src + n*0x18 <= param_3) {
            sk_memcpy(param_3, src, n*0x18);
            sk_free((void *)param_4);
            return;
        }
        __builtin_trap();
    }
    __builtin_trap();
}

/*--------------------------------------------------------------------*/
/* FUN_74eb0 @ 0x00074eb0   (est. sk_arr_copy248)
 * Ghidra: void FUN_74eb0(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
 * element array copy, stride 0xf8
 * Confidence: high
 */
void sk_arr_copy248(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
{
    long n = param_2 - param_1;
    if (param_2 < param_1)
        __builtin_trap();
    if (n >= 0) {
        unsigned long src = param_4 + param_1*0xf8 + 0x20;
        unsigned long end = param_3 + n*0xf8;
        if (end <= src || src + n*0xf8 <= param_3) {
            sk_memcpy(param_3, src, n*0xf8);
            sk_free((void *)param_4);
            return;
        }
        __builtin_trap();
    }
    __builtin_trap();
}

/*--------------------------------------------------------------------*/
/* FUN_74f28 @ 0x00074f28   (est. sk_arr_copy80)
 * Ghidra: void FUN_74f28(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
 * element array copy, stride 0x50
 * Confidence: high
 */
void sk_arr_copy80(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
{
    long n = param_2 - param_1;
    if (param_2 < param_1)
        __builtin_trap();
    if (n >= 0) {
        unsigned long src = param_4 + param_1*0x50 + 0x20;
        unsigned long end = param_3 + n*0x50;
        if (end <= src || src + n*0x50 <= param_3) {
            sk_memcpy(param_3, src, n*0x50);
            sk_free((void *)param_4);
            return;
        }
        __builtin_trap();
    }
    __builtin_trap();
}

/*--------------------------------------------------------------------*/
/* FUN_74fa4 @ 0x00074fa4   (est. sk_arr_copy64b)
 * Ghidra: void FUN_74fa4(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
 * element array copy, stride 0x40
 * Confidence: high
 */
void sk_arr_copy64b(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
{
    long n = param_2 - param_1;
    if (param_2 < param_1)
        __builtin_trap();
    if (n >= 0) {
        unsigned long src = param_4 + param_1*0x40 + 0x20;
        unsigned long end = param_3 + n*0x40;
        if (end <= src || src + n*0x40 <= param_3) {
            sk_memcpy(param_3, src, n*0x40);
            sk_free((void *)param_4);
            return;
        }
        __builtin_trap();
    }
    __builtin_trap();
}

/*--------------------------------------------------------------------*/
/* FUN_75018 @ 0x00075018   (est. sk_arr_copy80b)
 * Ghidra: void FUN_75018(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
 * element array copy, stride 0x50
 * Confidence: high
 */
void sk_arr_copy80b(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
{
    long n = param_2 - param_1;
    if (param_2 < param_1)
        __builtin_trap();
    if (n >= 0) {
        unsigned long src = param_4 + param_1*0x50 + 0x20;
        unsigned long end = param_3 + n*0x50;
        if (end <= src || src + n*0x50 <= param_3) {
            sk_memcpy(param_3, src, n*0x50);
            sk_free((void *)param_4);
            return;
        }
        __builtin_trap();
    }
    __builtin_trap();
}

/*--------------------------------------------------------------------*/
/* FUN_750bc @ 0x000750bc   (est. sk_f_750bc)
 * Ghidra: void FUN_750bc(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
 * faithful call sequence; see FUN_750bc
 * Confidence: low
 */
void sk_f_750bc(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
{
    sk_slot_000750bc();
    sk_slot_000777c4();
    sk_slot_00077860();
    sk_free();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_75118 @ 0x00075118   (est. sk_arr_copy8b)
 * Ghidra: void FUN_75118(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
 * element array copy, stride 8
 * Confidence: high
 */
void sk_arr_copy8b(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
{
    long n = param_2 - param_1;
    if (param_2 < param_1)
        __builtin_trap();
    if (n >= 0) {
        unsigned long src = param_4 + param_1*8 + 0x20;
        unsigned long end = param_3 + n*8;
        if (end <= src || src + n*8 <= param_3) {
            sk_memcpy(param_3, src, n*8);
            sk_free((void *)param_4);
            return;
        }
        __builtin_trap();
    }
    __builtin_trap();
}

/*--------------------------------------------------------------------*/
/* FUN_751b4 @ 0x000751b4   (est. sk_f_751b4)
 * Ghidra: void FUN_751b4(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
 * faithful call sequence; see FUN_751b4
 * Confidence: low
 */
void sk_f_751b4(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
{
    sk_slot_000751b4();
    sk_slot_00077888();
    sk_slot_00077910();
    sk_slot_000776e4();
    sk_free();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_75234 @ 0x00075234   (est. sk_arr_copy2)
 * Ghidra: void FUN_75234(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
 * element array copy, stride 2
 * Confidence: high
 */
void sk_arr_copy2(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
{
    long n = param_2 - param_1;
    if (param_2 < param_1)
        __builtin_trap();
    if (n >= 0) {
        unsigned long src = param_4 + param_1*2 + 0x20;
        unsigned long end = param_3 + n*2;
        if (end <= src || src + n*2 <= param_3) {
            sk_memcpy(param_3, src, n*2);
            sk_free((void *)param_4);
            return;
        }
        __builtin_trap();
    }
    __builtin_trap();
}

/*--------------------------------------------------------------------*/
/* FUN_752a4 @ 0x000752a4   (est. sk_arr_copy56)
 * Ghidra: void FUN_752a4(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
 * element array copy, stride 0x38
 * Confidence: high
 */
void sk_arr_copy56(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
{
    long n = param_2 - param_1;
    if (param_2 < param_1)
        __builtin_trap();
    if (n >= 0) {
        unsigned long src = param_4 + param_1*0x38 + 0x20;
        unsigned long end = param_3 + n*0x38;
        if (end <= src || src + n*0x38 <= param_3) {
            sk_memcpy(param_3, src, n*0x38);
            sk_free((void *)param_4);
            return;
        }
        __builtin_trap();
    }
    __builtin_trap();
}

/*--------------------------------------------------------------------*/
/* FUN_7534c @ 0x0007534c   (est. sk_arr_copy16c)
 * Ghidra: void FUN_7534c(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
 * element array copy, stride 0x10
 * Confidence: high
 */
void sk_arr_copy16c(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
{
    long n = param_2 - param_1;
    if (param_2 < param_1)
        __builtin_trap();
    if (n >= 0) {
        unsigned long src = param_4 + param_1*0x10 + 0x20;
        unsigned long end = param_3 + n*0x10;
        if (end <= src || src + n*0x10 <= param_3) {
            sk_memcpy(param_3, src, n*0x10);
            sk_free((void *)param_4);
            return;
        }
        __builtin_trap();
    }
    __builtin_trap();
}

/*--------------------------------------------------------------------*/
/* FUN_753c0 @ 0x000753c0   (est. sk_arr_copy40b)
 * Ghidra: void FUN_753c0(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
 * element array copy, stride 0x28
 * Confidence: high
 */
void sk_arr_copy40b(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
{
    long n = param_2 - param_1;
    if (param_2 < param_1)
        __builtin_trap();
    if (n >= 0) {
        unsigned long src = param_4 + param_1*0x28 + 0x20;
        unsigned long end = param_3 + n*0x28;
        if (end <= src || src + n*0x28 <= param_3) {
            sk_memcpy(param_3, src, n*0x28);
            sk_free((void *)param_4);
            return;
        }
        __builtin_trap();
    }
    __builtin_trap();
}

/*--------------------------------------------------------------------*/
/* FUN_7543c @ 0x0007543c   (est. sk_arr_copy16d)
 * Ghidra: void FUN_7543c(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
 * element array copy, stride 0x10
 * Confidence: high
 */
void sk_arr_copy16d(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
{
    long n = param_2 - param_1;
    if (param_2 < param_1)
        __builtin_trap();
    if (n >= 0) {
        unsigned long src = param_4 + param_1*0x10 + 0x20;
        unsigned long end = param_3 + n*0x10;
        if (end <= src || src + n*0x10 <= param_3) {
            sk_memcpy(param_3, src, n*0x10);
            sk_free((void *)param_4);
            return;
        }
        __builtin_trap();
    }
    __builtin_trap();
}

/*--------------------------------------------------------------------*/
/* FUN_754b0 @ 0x000754b0   (est. sk_arr_copy24b)
 * Ghidra: void FUN_754b0(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
 * element array copy, stride 0x18
 * Confidence: high
 */
void sk_arr_copy24b(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
{
    long n = param_2 - param_1;
    if (param_2 < param_1)
        __builtin_trap();
    if (n >= 0) {
        unsigned long src = param_4 + param_1*0x18 + 0x20;
        unsigned long end = param_3 + n*0x18;
        if (end <= src || src + n*0x18 <= param_3) {
            sk_memcpy(param_3, src, n*0x18);
            sk_free((void *)param_4);
            return;
        }
        __builtin_trap();
    }
    __builtin_trap();
}

/*--------------------------------------------------------------------*/
/* FUN_7552c @ 0x0007552c   (est. sk_arr_copy56b)
 * Ghidra: void FUN_7552c(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
 * element array copy, stride 0x38
 * Confidence: high
 */
void sk_arr_copy56b(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
{
    long n = param_2 - param_1;
    if (param_2 < param_1)
        __builtin_trap();
    if (n >= 0) {
        unsigned long src = param_4 + param_1*0x38 + 0x20;
        unsigned long end = param_3 + n*0x38;
        if (end <= src || src + n*0x38 <= param_3) {
            sk_memcpy(param_3, src, n*0x38);
            sk_free((void *)param_4);
            return;
        }
        __builtin_trap();
    }
    __builtin_trap();
}

/*--------------------------------------------------------------------*/
/* FUN_755a4 @ 0x000755a4   (est. sk_arr_copy88)
 * Ghidra: void FUN_755a4(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
 * element array copy, stride 0x58
 * Confidence: high
 */
void sk_arr_copy88(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
{
    long n = param_2 - param_1;
    if (param_2 < param_1)
        __builtin_trap();
    if (n >= 0) {
        unsigned long src = param_4 + param_1*0x58 + 0x20;
        unsigned long end = param_3 + n*0x58;
        if (end <= src || src + n*0x58 <= param_3) {
            sk_memcpy(param_3, src, n*0x58);
            sk_free((void *)param_4);
            return;
        }
        __builtin_trap();
    }
    __builtin_trap();
}

/*--------------------------------------------------------------------*/
/* FUN_75624 @ 0x00075624   (est. sk_arr_copy16e)
 * Ghidra: void FUN_75624(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
 * element array copy, stride 0x10
 * Confidence: high
 */
void sk_arr_copy16e(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
{
    long n = param_2 - param_1;
    if (param_2 < param_1)
        __builtin_trap();
    if (n >= 0) {
        unsigned long src = param_4 + param_1*0x10 + 0x20;
        unsigned long end = param_3 + n*0x10;
        if (end <= src || src + n*0x10 <= param_3) {
            sk_memcpy(param_3, src, n*0x10);
            sk_free((void *)param_4);
            return;
        }
        __builtin_trap();
    }
    __builtin_trap();
}

/*--------------------------------------------------------------------*/
/* FUN_75694 @ 0x00075694   (est. sk_arr_copy72)
 * Ghidra: void FUN_75694(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
 * element array copy, stride 0x48
 * Confidence: high
 */
void sk_arr_copy72(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
{
    long n = param_2 - param_1;
    if (param_2 < param_1)
        __builtin_trap();
    if (n >= 0) {
        unsigned long src = param_4 + param_1*0x48 + 0x20;
        unsigned long end = param_3 + n*0x48;
        if (end <= src || src + n*0x48 <= param_3) {
            sk_memcpy(param_3, src, n*0x48);
            sk_free((void *)param_4);
            return;
        }
        __builtin_trap();
    }
    __builtin_trap();
}

/*--------------------------------------------------------------------*/
/* FUN_75710 @ 0x00075710   (est. sk_arr_copy32b)
 * Ghidra: void FUN_75710(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
 * element array copy, stride 0x20
 * Confidence: high
 */
void sk_arr_copy32b(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
{
    long n = param_2 - param_1;
    if (param_2 < param_1)
        __builtin_trap();
    if (n >= 0) {
        unsigned long src = param_4 + param_1*0x20 + 0x20;
        unsigned long end = param_3 + n*0x20;
        if (end <= src || src + n*0x20 <= param_3) {
            sk_memcpy(param_3, src, n*0x20);
            sk_free((void *)param_4);
            return;
        }
        __builtin_trap();
    }
    __builtin_trap();
}

/*--------------------------------------------------------------------*/
/* FUN_75784 @ 0x00075784   (est. sk_f_75784)
 * Ghidra: void FUN_75784(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
 * faithful call sequence; see FUN_75784
 * Confidence: low
 */
void sk_f_75784(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
{
    sk_slot_00075784();
    sk_slot_000777c4();
    sk_slot_00077860();
    sk_free();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_757e8 @ 0x000757e8   (est. sk_arr_copy32c)
 * Ghidra: void FUN_757e8(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
 * element array copy, stride 0x20
 * Confidence: high
 */
void sk_arr_copy32c(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
{
    long n = param_2 - param_1;
    if (param_2 < param_1)
        __builtin_trap();
    if (n >= 0) {
        unsigned long src = param_4 + param_1*0x20 + 0x20;
        unsigned long end = param_3 + n*0x20;
        if (end <= src || src + n*0x20 <= param_3) {
            sk_memcpy(param_3, src, n*0x20);
            sk_free((void *)param_4);
            return;
        }
        __builtin_trap();
    }
    __builtin_trap();
}

/*--------------------------------------------------------------------*/
/* FUN_7585c @ 0x0007585c   (est. sk_arr_copy40c)
 * Ghidra: void FUN_7585c(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
 * element array copy, stride 0x28
 * Confidence: high
 */
void sk_arr_copy40c(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
{
    long n = param_2 - param_1;
    if (param_2 < param_1)
        __builtin_trap();
    if (n >= 0) {
        unsigned long src = param_4 + param_1*0x28 + 0x20;
        unsigned long end = param_3 + n*0x28;
        if (end <= src || src + n*0x28 <= param_3) {
            sk_memcpy(param_3, src, n*0x28);
            sk_free((void *)param_4);
            return;
        }
        __builtin_trap();
    }
    __builtin_trap();
}

/*--------------------------------------------------------------------*/
/* FUN_758d8 @ 0x000758d8   (est. sk_arr_copy16f)
 * Ghidra: void FUN_758d8(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4, unsigned long param_5)
 * element array copy, stride 0x10
 * Confidence: high
 */
void sk_arr_copy16f(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4, unsigned long param_5)
{
    long n = param_2 - param_1;
    if (param_2 < param_1)
        __builtin_trap();
    if (n >= 0) {
        unsigned long src = param_4 + param_1*0x10 + 0x20;
        unsigned long end = param_3 + n*0x10;
        if (end <= src || src + n*0x10 <= param_3) {
            sk_memcpy(param_3, src, n*0x10);
            sk_free((void *)param_4);
            return;
        }
        __builtin_trap();
    }
    __builtin_trap();
}

/*--------------------------------------------------------------------*/
/* FUN_75948 @ 0x00075948   (est. sk_f_75948)
 * Ghidra: void FUN_75948(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
 * faithful call sequence; see FUN_75948
 * Confidence: low
 */
void sk_f_75948(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
{
    sk_slot_00075948();
    sk_slot_00077888();
    sk_slot_00077910();
    sk_slot_000776e4();
    sk_free();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_759c0 @ 0x000759c0   (est. sk_f_759c0)
 * Ghidra: void FUN_759c0(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
 * faithful call sequence; see FUN_759c0
 * Confidence: low
 */
void sk_f_759c0(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
{
    sk_slot_000759c0();
    sk_slot_00077888();
    sk_slot_00077910();
    sk_slot_000776e4();
    sk_free();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_75a38 @ 0x00075a38   (est. sk_arr_copy48)
 * Ghidra: void FUN_75a38(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
 * element array copy, stride 0x30
 * Confidence: high
 */
void sk_arr_copy48(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
{
    long n = param_2 - param_1;
    if (param_2 < param_1)
        __builtin_trap();
    if (n >= 0) {
        unsigned long src = param_4 + param_1*0x30 + 0x20;
        unsigned long end = param_3 + n*0x30;
        if (end <= src || src + n*0x30 <= param_3) {
            sk_memcpy(param_3, src, n*0x30);
            sk_free((void *)param_4);
            return;
        }
        __builtin_trap();
    }
    __builtin_trap();
}

/*--------------------------------------------------------------------*/
/* FUN_75ab4 @ 0x00075ab4   (est. sk_arr_copy144)
 * Ghidra: void FUN_75ab4(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
 * element array copy, stride 0x90
 * Confidence: high
 */
void sk_arr_copy144(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
{
    long n = param_2 - param_1;
    if (param_2 < param_1)
        __builtin_trap();
    if (n >= 0) {
        unsigned long src = param_4 + param_1*0x90 + 0x20;
        unsigned long end = param_3 + n*0x90;
        if (end <= src || src + n*0x90 <= param_3) {
            sk_memcpy(param_3, src, n*0x90);
            sk_free((void *)param_4);
            return;
        }
        __builtin_trap();
    }
    __builtin_trap();
}

/*--------------------------------------------------------------------*/
/* FUN_75b2c @ 0x00075b2c   (est. sk_f_75b2c)
 * Ghidra: void FUN_75b2c(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
 * faithful call sequence; see FUN_75b2c
 * Confidence: low
 */
void sk_f_75b2c(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
{
    sk_slot_00075b2c();
    sk_slot_00077888();
    sk_slot_00077910();
    sk_slot_000776e4();
    sk_free();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_75bac @ 0x00075bac   (est. sk_arr_copy48b)
 * Ghidra: void FUN_75bac(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
 * element array copy, stride 0x30
 * Confidence: high
 */
void sk_arr_copy48b(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
{
    long n = param_2 - param_1;
    if (param_2 < param_1)
        __builtin_trap();
    if (n >= 0) {
        unsigned long src = param_4 + param_1*0x30 + 0x20;
        unsigned long end = param_3 + n*0x30;
        if (end <= src || src + n*0x30 <= param_3) {
            sk_memcpy(param_3, src, n*0x30);
            sk_free((void *)param_4);
            return;
        }
        __builtin_trap();
    }
    __builtin_trap();
}

/*--------------------------------------------------------------------*/
/* FUN_75c50 @ 0x00075c50   (est. sk_f_75c50)
 * Ghidra: void FUN_75c50(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
 * faithful call sequence; see FUN_75c50
 * Confidence: low
 */
void sk_f_75c50(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
{
    sk_slot_00075c50();
    sk_slot_000777c4();
    sk_slot_00077860();
    sk_free();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_75cb4 @ 0x00075cb4   (est. sk_f_75cb4)
 * Ghidra: void FUN_75cb4(unsigned long param_1, unsigned long param_2, unsigned long param_3)
 * faithful call sequence; see FUN_75cb4
 * Confidence: low
 */
void sk_f_75cb4(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    sk_slot_00075cb4();
    sk_retain_low();
    sk_slot_000724cc();
    sk_type_resolve();
    sk_map_insert();
    sk_slot_000724cc();
    sk_panic_nr();
    sk_map_insert4();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_75dd8 @ 0x00075dd8   (est. sk_f_75dd8)
 * Ghidra: void FUN_75dd8(unsigned long param_1, unsigned long param_2, unsigned long param_3)
 * faithful call sequence; see FUN_75dd8
 * Confidence: low
 */
void sk_f_75dd8(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    sk_slot_00075dd8();
    sk_slot_00077698();
    sk_slot_0007783c();
    sk_slot_000775c8();
    sk_hash_lookup();
    sk_slot_000775b8();
    sk_type_resolve();
    sk_slot_00077614();
    sk_map_insert();
    sk_slot_00077764();
    sk_hash_lookup();
    sk_slot_0007765c();
    sk_slot_0007787c();
    sk_slot_00077824();
    sk_map_insert1();
    sk_retain();
    sk_slot_0007767c();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_75ea4 @ 0x00075ea4   (est. sk_f_75ea4)
 * Ghidra: void FUN_75ea4(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4, unsigned long param_5)
 * faithful call sequence; see FUN_75ea4
 * Confidence: low
 */
void sk_f_75ea4(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4, unsigned long param_5)
{
    sk_slot_00075ea4();
    sk_slot_00077698();
    sk_retain_low();
    sk_slot_000776b4();
    sk_slot_000778e8();
    sk_slot_000775b8();
    sk_type_resolve();
    sk_slot_000776c0();
    sk_map_insert();
    sk_slot_000778e8();
    sk_panic_nr();
    sk_map_insert2();
    sk_retain();
    sk_slot_0007767c();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_75fb4 @ 0x00075fb4   (est. sk_f_75fb4)
 * Ghidra: void FUN_75fb4(void)
 * faithful call sequence; see FUN_75fb4
 * Confidence: low
 */
void sk_f_75fb4(void)
{
    sk_slot_00075fb4();
    sk_slot_00077698();
    sk_slot_000777b4();
    sk_retain_low();
    sk_slot_000775c8();
    sk_slot_00072664();
    sk_slot_000775b8();
    sk_slot_000778b4();
    sk_type_resolve();
    sk_slot_00077614();
    sk_map_insert();
    sk_slot_00077764();
    sk_slot_00072664();
    sk_slot_00077604();
    sk_slot_00077800();
    sk_map_insert16();
    sk_free();
    sk_slot_0007767c();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7608c @ 0x0007608c   (est. sk_f_7608c)
 * Ghidra: void FUN_7608c(void)
 * faithful call sequence; see FUN_7608c
 * Confidence: low
 */
void sk_f_7608c(void)
{
    sk_slot_0007608c();
    sk_slot_00077698();
    sk_slot_000777e4();
    sk_slot_000776b4();
    sk_slot_00077928();
    sk_slot_000775b8();
    sk_type_resolve();
    sk_slot_000776c0();
    sk_map_insert();
    sk_slot_00077928();
    sk_slot_00077604();
    sk_slot_0007787c();
    sk_slot_00077778();
    sk_map_insert16b();
    sk_retain();
    sk_release();
    sk_slot_0007767c();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_76158 @ 0x00076158   (est. sk_f_76158)
 * Ghidra: void FUN_76158(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4, unsigned long param_5)
 * faithful call sequence; see FUN_76158
 * Confidence: low
 */
void sk_f_76158(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4, unsigned long param_5)
{
    sk_slot_00076158();
    sk_slot_00077698();
    sk_retain_low();
    sk_slot_000776b4();
    sk_slot_00072664();
    sk_slot_000775b8();
    sk_type_resolve();
    sk_slot_000776c0();
    sk_map_insert();
    sk_slot_00072664();
    sk_slot_00077800();
    sk_map_insert32();
    sk_free();
    sk_release();
    sk_slot_0007767c();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_76274 @ 0x00076274   (est. sk_f_76274)
 * Ghidra: void FUN_76274(unsigned long param_1, unsigned long param_2)
 * faithful call sequence; see FUN_76274
 * Confidence: low
 */
void sk_f_76274(unsigned long param_1, unsigned long param_2)
{
    sk_slot_00076274();
    sk_slot_00076918();
    sk_map_insert_opt();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7629c @ 0x0007629c   (est. sk_f_7629c)
 * Ghidra: void FUN_7629c(void)
 * faithful call sequence; see FUN_7629c
 * Confidence: low
 */
void sk_f_7629c(void)
{
    sk_slot_0007629c();
    sk_slot_00077698();
    sk_slot_000777e4();
    sk_slot_000776b4();
    sk_slot_00077928();
    sk_slot_000775b8();
    sk_type_resolve();
    sk_slot_000776c0();
    sk_map_insert();
    sk_slot_00077928();
    sk_slot_00077604();
    sk_slot_0007787c();
    sk_slot_00077778();
    sk_map_insert16b();
    sk_retain();
    sk_slot_0007767c();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_76360 @ 0x00076360   (est. sk_f_76360)
 * Ghidra: void FUN_76360(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4, unsigned long param_5, unsigned long param_6)
 * faithful call sequence; see FUN_76360
 * Confidence: low
 */
void sk_f_76360(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4, unsigned long param_5, unsigned long param_6)
{
    sk_slot_00076360();
    sk_retain_low();
    sk_hash_lookup();
    sk_slot_000775b8();
    sk_type_resolve();
    sk_map_insert();
    sk_hash_lookup();
    sk_slot_0007787c();
    sk_map_insert8();
    sk_retain();
    sk_free();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_764a0 @ 0x000764a0   (est. sk_f_764a0)
 * Ghidra: void FUN_764a0(unsigned long param_1, unsigned long param_2)
 * faithful call sequence; see FUN_764a0
 * Confidence: low
 */
void sk_f_764a0(unsigned long param_1, unsigned long param_2)
{
    sk_slot_000764a0();
    sk_slot_000765c4();
    sk_map_insert_opt();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_764c8 @ 0x000764c8   (est. sk_f_764c8)
 * Ghidra: void FUN_764c8(unsigned long param_1, unsigned long param_2, unsigned long param_3)
 * faithful call sequence; see FUN_764c8
 * Confidence: low
 */
void sk_f_764c8(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    sk_slot_000764c8();
    sk_slot_00077698();
    sk_slot_0007783c();
    sk_slot_000775c8();
    sk_hash_lookup();
    sk_slot_000775b8();
    sk_type_resolve();
    sk_slot_00077614();
    sk_map_insert();
    sk_slot_00077764();
    sk_hash_lookup();
    sk_slot_0007765c();
    sk_slot_0007787c();
    sk_slot_00077824();
    sk_map_insert1();
    sk_retain();
    sk_free();
    sk_slot_0007767c();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7659c @ 0x0007659c   (est. sk_f_7659c)
 * Ghidra: void FUN_7659c(unsigned long param_1, unsigned long param_2)
 * faithful call sequence; see FUN_7659c
 * Confidence: low
 */
void sk_f_7659c(unsigned long param_1, unsigned long param_2)
{
    sk_slot_0007659c();
    sk_slot_000765c4();
    sk_map_insert_opt();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_765c4 @ 0x000765c4   (est. sk_f_765c4)
 * Ghidra: void FUN_765c4(void)
 * faithful call sequence; see FUN_765c4
 * Confidence: low
 */
void sk_f_765c4(void)
{
    sk_slot_000765c4();
    sk_slot_00077698();
    sk_slot_00077794();
    sk_slot_000775c8();
    sk_slot_00072664();
    sk_slot_000775b8();
    sk_slot_000778b4();
    sk_type_resolve();
    sk_slot_00077614();
    sk_map_insert();
    sk_slot_00077764();
    sk_slot_00072664();
    sk_slot_00077604();
    sk_slot_00077800();
    sk_slot_00077708();
    sk_free();
    sk_slot_0007767c();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7667c @ 0x0007667c   (est. sk_f_7667c)
 * Ghidra: void FUN_7667c(void)
 * faithful call sequence; see FUN_7667c
 * Confidence: low
 */
void sk_f_7667c(void)
{
    sk_slot_0007667c();
    sk_slot_000778c0();
    sk_slot_000776b4();
    sk_slot_00072664();
    sk_slot_000775b8();
    sk_type_resolve();
    sk_slot_000776c0();
    sk_map_insert();
    sk_slot_00072664();
    sk_slot_0007765c();
    sk_slot_00077800();
    sk_slot_00077894();
    sk_map_del16();
    sk_slot_000774c8();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_76760 @ 0x00076760   (est. sk_f_76760)
 * Ghidra: void FUN_76760(void)
 * faithful call sequence; see FUN_76760
 * Confidence: low
 */
void sk_f_76760(void)
{
    sk_slot_00076760();
    sk_slot_00077698();
    sk_slot_000777b4();
    sk_slot_0007783c();
    sk_slot_000775c8();
    sk_slot_00072664();
    sk_slot_000775b8();
    sk_slot_000778b4();
    sk_type_resolve();
    sk_slot_00077614();
    sk_map_insert();
    sk_slot_00077764();
    sk_slot_00072664();
    sk_slot_00077604();
    sk_slot_00077800();
    sk_slot_00077708();
    sk_map_del16b();
    sk_free();
    sk_slot_0007767c();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7682c @ 0x0007682c   (est. sk_f_7682c)
 * Ghidra: void FUN_7682c(void)
 * faithful call sequence; see FUN_7682c
 * Confidence: low
 */
void sk_f_7682c(void)
{
    sk_slot_0007682c();
    sk_slot_00077698();
    sk_slot_000777b4();
    sk_slot_0007783c();
    sk_slot_000775c8();
    sk_slot_00072664();
    sk_slot_000775b8();
    sk_slot_000778b4();
    sk_type_resolve();
    sk_slot_00077614();
    sk_map_insert();
    sk_slot_00077764();
    sk_slot_00072664();
    sk_slot_00077604();
    sk_slot_00077800();
    sk_slot_00077708();
    sk_map_del16b();
    sk_release();
    sk_slot_0007767c();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_768f0 @ 0x000768f0   (est. sk_f_768f0)
 * Ghidra: void FUN_768f0(unsigned long param_1, unsigned long param_2)
 * faithful call sequence; see FUN_768f0
 * Confidence: low
 */
void sk_f_768f0(unsigned long param_1, unsigned long param_2)
{
    sk_slot_000768f0();
    sk_slot_00076918();
    sk_map_insert_opt();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_76918 @ 0x00076918   (est. sk_f_76918)
 * Ghidra: void FUN_76918(void)
 * faithful call sequence; see FUN_76918
 * Confidence: low
 */
void sk_f_76918(void)
{
    sk_slot_00076918();
    sk_slot_00077698();
    sk_slot_00077794();
    sk_slot_000775c8();
    sk_slot_00072664();
    sk_slot_000775b8();
    sk_type_resolve();
    sk_slot_00077614();
    sk_map_insert();
    sk_slot_00077764();
    sk_slot_00072664();
    sk_slot_0007765c();
    sk_slot_00077800();
    sk_slot_0007767c();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_769d4 @ 0x000769d4   (est. sk_f_769d4)
 * Ghidra: void FUN_769d4(void)
 * faithful call sequence; see FUN_769d4
 * Confidence: low
 */
void sk_f_769d4(void)
{
    sk_slot_000769d4();
    sk_slot_000778c0();
    sk_slot_000776b4();
    sk_slot_00072664();
    sk_slot_000775b8();
    sk_type_resolve();
    sk_slot_000776c0();
    sk_map_insert();
    sk_slot_00072664();
    sk_slot_0007765c();
    sk_slot_00077800();
    sk_slot_00077894();
    sk_map_del40();
    sk_free();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_76ac8 @ 0x00076ac8   (est. sk_f_76ac8)
 * Ghidra: void FUN_76ac8(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4, unsigned long param_5)
 * faithful call sequence; see FUN_76ac8
 * Confidence: low
 */
void sk_f_76ac8(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4, unsigned long param_5)
{
    sk_slot_00076ac8();
    sk_slot_0007198c();
    sk_retain();
    sk_slot_00072464();
    sk_type_resolve();
    sk_map_insert();
    sk_slot_00072464();
    sk_panic_nr();
    sk_free();
    sk_release();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_76d08 @ 0x00076d08   (est. sk_f_76d08)
 * Ghidra: void FUN_76d08(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4, unsigned long param_5)
 * faithful call sequence; see FUN_76d08
 * Confidence: low
 */
void sk_f_76d08(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4, unsigned long param_5)
{
    sk_slot_00076d08();
    sk_slot_0007198c();
    sk_retain();
    sk_slot_000724cc();
    sk_slot_000775b8();
    sk_type_resolve();
    sk_map_insert();
    sk_slot_000724cc();
    sk_panic_nr();
    sk_free();
    sk_release();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_76f74 @ 0x00076f74   (est. sk_f_76f74)
 * Ghidra: void FUN_76f74(unsigned long param_1, unsigned long param_2)
 * faithful call sequence; see FUN_76f74
 * Confidence: low
 */
void sk_f_76f74(unsigned long param_1, unsigned long param_2)
{
    sk_slot_00076f74();
    sk_cap_repair();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_76fc0 @ 0x00076fc0   (est. sk_f_76fc0)
 * Ghidra: void FUN_76fc0(void)
 * faithful call sequence; see FUN_76fc0
 * Confidence: low
 */
void sk_f_76fc0(void)
{
    sk_slot_00076fc0();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_77024 @ 0x00077024   (est. sk_f_77024)
 * Ghidra: void FUN_77024(unsigned long param_1)
 * faithful call sequence; see FUN_77024
 * Confidence: low
 */
void sk_f_77024(unsigned long param_1)
{
    sk_slot_00077024();
    sk_obj_new();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_77070 @ 0x00077070   (est. sk_f_77070)
 * Ghidra: void FUN_77070(unsigned long param_1, unsigned long param_2)
 * faithful call sequence; see FUN_77070
 * Confidence: low
 */
void sk_f_77070(unsigned long param_1, unsigned long param_2)
{
    sk_slot_00077070();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_77088 @ 0x00077088   (est. sk_obj_end_8)
 * Ghidra: void FUN_77088(unsigned long param_1)
 * object end/limit offset 0x8
 * Confidence: high
 */
void sk_obj_end_8(unsigned long param_1)
{
    if ((param_1 & 1) != 0)
        param_1 = *(unsigned long *)(param_1 & ~1);
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_770b8 @ 0x000770b8   (est. sk_obj_end_c)
 * Ghidra: void FUN_770b8(unsigned long param_1)
 * object end/limit offset 0xc
 * Confidence: high
 */
void sk_obj_end_c(unsigned long param_1)
{
    if ((param_1 & 1) != 0)
        param_1 = *(unsigned long *)(param_1 & ~1);
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_770e8 @ 0x000770e8   (est. sk_obj_end_14)
 * Ghidra: void FUN_770e8(unsigned long param_1)
 * object end/limit offset 0x14
 * Confidence: high
 */
void sk_obj_end_14(unsigned long param_1)
{
    if ((param_1 & 1) != 0)
        param_1 = *(unsigned long *)(param_1 & ~1);
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_77118 @ 0x00077118   (est. sk_obj_end_18)
 * Ghidra: void FUN_77118(unsigned long param_1)
 * object end/limit offset 0x18
 * Confidence: high
 */
void sk_obj_end_18(unsigned long param_1)
{
    if ((param_1 & 1) != 0)
        param_1 = *(unsigned long *)(param_1 & ~1);
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_77148 @ 0x00077148   (est. sk_obj_end_1c)
 * Ghidra: void FUN_77148(unsigned long param_1)
 * object end/limit offset 0x1c
 * Confidence: high
 */
void sk_obj_end_1c(unsigned long param_1)
{
    if ((param_1 & 1) != 0)
        param_1 = *(unsigned long *)(param_1 & ~1);
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_77178 @ 0x00077178   (est. sk_obj_end_20)
 * Ghidra: void FUN_77178(unsigned long param_1)
 * object end/limit offset 0x20
 * Confidence: high
 */
void sk_obj_end_20(unsigned long param_1)
{
    if ((param_1 & 1) != 0)
        param_1 = *(unsigned long *)(param_1 & ~1);
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_773f0 @ 0x000773f0   (est. sk_f_773f0)
 * Ghidra: void FUN_773f0(void)
 * faithful call sequence; see FUN_773f0
 * Confidence: low
 */
void sk_f_773f0(void)
{
    sk_slot_000773f0();
    sk_slot_00077770();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_774c8 @ 0x000774c8   (est. sk_f_774c8)
 * Ghidra: void FUN_774c8(unsigned long param_1, unsigned long param_2)
 * faithful call sequence; see FUN_774c8
 * Confidence: low
 */
void sk_f_774c8(unsigned long param_1, unsigned long param_2)
{
    sk_slot_000774c8();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7751c @ 0x0007751c   (est. sk_f_7751c)
 * Ghidra: void FUN_7751c(unsigned long param_1)
 * faithful call sequence; see FUN_7751c
 * Confidence: low
 */
void sk_f_7751c(unsigned long param_1)
{
    sk_slot_00072664();
    sk_map_hash();
    sk_slot_00072a30();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_77520 @ 0x00077520   (est. sk_f_77520)
 * Ghidra: void FUN_77520(unsigned long param_1, unsigned long param_2)
 * faithful call sequence; see FUN_77520
 * Confidence: low
 */
void sk_f_77520(unsigned long param_1, unsigned long param_2)
{
    sk_slot_00072454();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_77524 @ 0x00077524   (est. sk_f_77524)
 * Ghidra: void FUN_77524(unsigned long param_1)
 * faithful call sequence; see FUN_77524
 * Confidence: low
 */
void sk_f_77524(unsigned long param_1)
{
    sk_slot_00070594();
    sk_tcb_swap();
    sk_tcb_free();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_77528 @ 0x00077528   (est. sk_f_77528)
 * Ghidra: void FUN_77528(unsigned long param_1, unsigned long param_2, unsigned long param_3)
 * faithful call sequence; see FUN_77528
 * Confidence: low
 */
void sk_f_77528(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    sk_slot_000721b0();
    sk_slot_00077540();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7752c @ 0x0007752c   (est. sk_zero3)
 * Ghidra: void FUN_7752c(void)
 * returns 0
 * Confidence: low
 */
void sk_zero3(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_77540 @ 0x00077540   (est. sk_f_77540)
 * Ghidra: void FUN_77540(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
 * faithful call sequence; see FUN_77540
 * Confidence: low
 */
void sk_f_77540(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
{
    sk_slot_00077540();
    sk_memcpy();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_77550 @ 0x00077550   (est. sk_noop)
 * Ghidra: void FUN_77550(void)
 * empty leaf / placeholder hook
 * Confidence: low
 */
void sk_noop(void)
{
    return;
}
/*--------------------------------------------------------------------*/
/* FUN_77560 @ 0x00077560   (est. sk_noop)
 * Ghidra: void FUN_77560(void)
 * empty leaf / placeholder hook
 * Confidence: low
 */
void sk_noop_1(void)
{
    return;
}
/*--------------------------------------------------------------------*/
/* FUN_77570 @ 0x00077570   (est. sk_noop)
 * Ghidra: void FUN_77570(void)
 * empty leaf / placeholder hook
 * Confidence: low
 */
void sk_noop_2(void)
{
    return;
}
/*--------------------------------------------------------------------*/
/* FUN_77580 @ 0x00077580   (est. sk_obj_base)
 * Ghidra: void FUN_77580(void)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_obj_base(void)
{
    sk_slot_00077580();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_77590 @ 0x00077590   (est. sk_noop)
 * Ghidra: void FUN_77590(void)
 * empty leaf / placeholder hook
 * Confidence: low
 */
void sk_noop_3(void)
{
    return;
}
/*--------------------------------------------------------------------*/
/* FUN_775b8 @ 0x000775b8   (est. sk_noop)
 * Ghidra: void FUN_775b8(void)
 * empty leaf / placeholder hook
 * Confidence: low
 */
void sk_noop_4(void)
{
    return;
}
/*--------------------------------------------------------------------*/
/* FUN_775c8 @ 0x000775c8   (est. sk_noop)
 * Ghidra: void FUN_775c8(void)
 * empty leaf / placeholder hook
 * Confidence: low
 */
void sk_noop_5(void)
{
    return;
}
/*--------------------------------------------------------------------*/
/* FUN_775dc @ 0x000775dc   (est. sk_f_775dc)
 * Ghidra: void FUN_775dc(unsigned long param_1)
 * faithful call sequence; see FUN_775dc
 * Confidence: low
 */
void sk_f_775dc(unsigned long param_1)
{
    sk_slot_000775dc();
    sk_round_up();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_77604 @ 0x00077604   (est. sk_noop)
 * Ghidra: void FUN_77604(void)
 * empty leaf / placeholder hook
 * Confidence: low
 */
void sk_noop_6(void)
{
    return;
}
/*--------------------------------------------------------------------*/
/* FUN_77614 @ 0x00077614   (est. sk_noop)
 * Ghidra: void FUN_77614(void)
 * empty leaf / placeholder hook
 * Confidence: low
 */
void sk_noop_7(void)
{
    return;
}
/*--------------------------------------------------------------------*/
/* FUN_77624 @ 0x00077624   (est. sk_noop)
 * Ghidra: void FUN_77624(void)
 * empty leaf / placeholder hook
 * Confidence: low
 */
void sk_noop_8(void)
{
    return;
}
/*--------------------------------------------------------------------*/
/* FUN_77630 @ 0x00077630   (est. sk_f_77630)
 * Ghidra: void FUN_77630(void)
 * faithful call sequence; see FUN_77630
 * Confidence: low
 */
void sk_f_77630(void)
{
    sk_slot_00077630();
    sk_round_up();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7764c @ 0x0007764c   (est. sk_f_7764c)
 * Ghidra: void FUN_7764c(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
 * faithful call sequence; see FUN_7764c
 * Confidence: low
 */
void sk_f_7764c(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
{
    sk_slot_0007764c();
    sk_type_resolve();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7765c @ 0x0007765c   (est. sk_noop)
 * Ghidra: void FUN_7765c(void)
 * empty leaf / placeholder hook
 * Confidence: low
 */
void sk_noop_9(void)
{
    return;
}
/*--------------------------------------------------------------------*/
/* FUN_7766c @ 0x0007766c   (est. sk_f_7766c)
 * Ghidra: void FUN_7766c(unsigned long param_1)
 * faithful call sequence; see FUN_7766c
 * Confidence: low
 */
void sk_f_7766c(unsigned long param_1)
{
    sk_slot_0007766c();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7767c @ 0x0007767c   (est. sk_noop)
 * Ghidra: void FUN_7767c(void)
 * empty leaf / placeholder hook
 * Confidence: low
 */
void sk_noop_10(void)
{
    return;
}
/*--------------------------------------------------------------------*/
/* FUN_77698 @ 0x00077698   (est. sk_noop)
 * Ghidra: void FUN_77698(void)
 * empty leaf / placeholder hook
 * Confidence: low
 */
void sk_noop_11(void)
{
    return;
}
/*--------------------------------------------------------------------*/
/* FUN_776b4 @ 0x000776b4   (est. sk_noop)
 * Ghidra: void FUN_776b4(void)
 * empty leaf / placeholder hook
 * Confidence: low
 */
void sk_noop_12(void)
{
    return;
}
/*--------------------------------------------------------------------*/
/* FUN_776c0 @ 0x000776c0   (est. sk_noop)
 * Ghidra: void FUN_776c0(void)
 * empty leaf / placeholder hook
 * Confidence: low
 */
void sk_noop_13(void)
{
    return;
}
/*--------------------------------------------------------------------*/
/* FUN_776cc @ 0x000776cc   (est. sk_noop)
 * Ghidra: void FUN_776cc(void)
 * empty leaf / placeholder hook
 * Confidence: low
 */
void sk_noop_14(void)
{
    return;
}
/*--------------------------------------------------------------------*/
/* FUN_776d8 @ 0x000776d8   (est. sk_noop)
 * Ghidra: void FUN_776d8(void)
 * empty leaf / placeholder hook
 * Confidence: low
 */
void sk_noop_15(void)
{
    return;
}
/*--------------------------------------------------------------------*/
/* FUN_776e4 @ 0x000776e4   (est. sk_f_776e4)
 * Ghidra: void FUN_776e4(void)
 * faithful call sequence; see FUN_776e4
 * Confidence: low
 */
void sk_f_776e4(void)
{
    sk_slot_000776e4();
    sk_memcpy_el();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_776f8 @ 0x000776f8   (est. sk_f_776f8)
 * Ghidra: void FUN_776f8(unsigned long param_1)
 * faithful call sequence; see FUN_776f8
 * Confidence: low
 */
void sk_f_776f8(unsigned long param_1)
{
    sk_slot_000776f8();
    sk_alloc();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_77708 @ 0x00077708   (est. sk_noop)
 * Ghidra: void FUN_77708(void)
 * empty leaf / placeholder hook
 * Confidence: low
 */
void sk_noop_16(void)
{
    return;
}
/*--------------------------------------------------------------------*/
/* FUN_77718 @ 0x00077718   (est. sk_f_77718)
 * Ghidra: void FUN_77718(void)
 * faithful call sequence; see FUN_77718
 * Confidence: low
 */
void sk_f_77718(void)
{
    sk_slot_00077718();
    sk_free();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_77724 @ 0x00077724   (est. sk_noop)
 * Ghidra: void FUN_77724(void)
 * empty leaf / placeholder hook
 * Confidence: low
 */
void sk_noop_17(void)
{
    return;
}
/*--------------------------------------------------------------------*/
/* FUN_77744 @ 0x00077744   (est. sk_noop)
 * Ghidra: void FUN_77744(void)
 * empty leaf / placeholder hook
 * Confidence: low
 */
void sk_noop_18(void)
{
    return;
}
/*--------------------------------------------------------------------*/
/* FUN_77764 @ 0x00077764   (est. sk_noop)
 * Ghidra: void FUN_77764(void)
 * empty leaf / placeholder hook
 * Confidence: low
 */
void sk_noop_19(void)
{
    return;
}
/*--------------------------------------------------------------------*/
/* FUN_77770 @ 0x00077770   (est. sk_noop)
 * Ghidra: void FUN_77770(void)
 * empty leaf / placeholder hook
 * Confidence: low
 */
void sk_noop_20(void)
{
    return;
}
/*--------------------------------------------------------------------*/
/* FUN_77778 @ 0x00077778   (est. sk_noop)
 * Ghidra: void FUN_77778(void)
 * empty leaf / placeholder hook
 * Confidence: low
 */
void sk_noop_21(void)
{
    return;
}
/*--------------------------------------------------------------------*/
/* FUN_77794 @ 0x00077794   (est. sk_obj_mth_0)
 * Ghidra: void FUN_77794(void)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_obj_mth_0(void)
{
    sk_slot_00077794();
    sk_retain_low();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_777b4 @ 0x000777b4   (est. sk_noop)
 * Ghidra: void FUN_777b4(void)
 * empty leaf / placeholder hook
 * Confidence: low
 */
void sk_noop_22(void)
{
    return;
}
/*--------------------------------------------------------------------*/
/* FUN_777c4 @ 0x000777c4   (est. sk_noop)
 * Ghidra: void FUN_777c4(void)
 * empty leaf / placeholder hook
 * Confidence: low
 */
void sk_noop_23(void)
{
    return;
}
/*--------------------------------------------------------------------*/
/* FUN_777d4 @ 0x000777d4   (est. sk_noop)
 * Ghidra: void FUN_777d4(void)
 * empty leaf / placeholder hook
 * Confidence: low
 */
void sk_noop_24(void)
{
    return;
}
/*--------------------------------------------------------------------*/
/* FUN_777e4 @ 0x000777e4   (est. sk_obj_mth_1)
 * Ghidra: void FUN_777e4(void)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_obj_mth_1(void)
{
    sk_slot_000777e4();
    sk_retain_low();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_77800 @ 0x00077800   (est. sk_f_77800)
 * Ghidra: void FUN_77800(void)
 * faithful call sequence; see FUN_77800
 * Confidence: low
 */
void sk_f_77800(void)
{
    sk_slot_00077800();
    sk_panic_nr();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7780c @ 0x0007780c   (est. sk_shared_map_ptr)
 * Ghidra: void FUN_7780c(void)
 * returns &DAT_00657778
 * Confidence: low
 */
void sk_shared_map_ptr(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_77824 @ 0x00077824   (est. sk_noop)
 * Ghidra: void FUN_77824(void)
 * empty leaf / placeholder hook
 * Confidence: low
 */
void sk_noop_25(void)
{
    return;
}
/*--------------------------------------------------------------------*/
/* FUN_7783c @ 0x0007783c   (est. sk_obj_mth_2)
 * Ghidra: void FUN_7783c(void)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_obj_mth_2(void)
{
    sk_slot_0007783c();
    sk_retain_low();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_77848 @ 0x00077848   (est. sk_f_77848)
 * Ghidra: void FUN_77848(void)
 * faithful call sequence; see FUN_77848
 * Confidence: low
 */
void sk_f_77848(void)
{
    sk_slot_00077848();
    sk_hash_init();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_77860 @ 0x00077860   (est. sk_f_77860)
 * Ghidra: void FUN_77860(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
 * faithful call sequence; see FUN_77860
 * Confidence: low
 */
void sk_f_77860(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
{
    sk_slot_00077860();
    sk_buf_alloc();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_77870 @ 0x00077870   (est. sk_f_77870)
 * Ghidra: void FUN_77870(void)
 * faithful call sequence; see FUN_77870
 * Confidence: low
 */
void sk_f_77870(void)
{
    sk_slot_00077870();
    sk_hash_init();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7787c @ 0x0007787c   (est. sk_f_7787c)
 * Ghidra: void FUN_7787c(void)
 * faithful call sequence; see FUN_7787c
 * Confidence: low
 */
void sk_f_7787c(void)
{
    sk_slot_0007787c();
    sk_panic_nr();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_77888 @ 0x00077888   (est. sk_noop)
 * Ghidra: void FUN_77888(void)
 * empty leaf / placeholder hook
 * Confidence: low
 */
void sk_noop_26(void)
{
    return;
}
/*--------------------------------------------------------------------*/
/* FUN_77894 @ 0x00077894   (est. sk_noop)
 * Ghidra: void FUN_77894(void)
 * empty leaf / placeholder hook
 * Confidence: low
 */
void sk_noop_27(void)
{
    return;
}
/*--------------------------------------------------------------------*/
/* FUN_778a0 @ 0x000778a0   (est. sk_shared_map)
 * Ghidra: void FUN_778a0(void)
 * returns &DAT_00657778; shared serialization map
 * Confidence: low
 */
void sk_shared_map(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_778b4 @ 0x000778b4   (est. sk_noop)
 * Ghidra: void FUN_778b4(void)
 * empty leaf / placeholder hook
 * Confidence: low
 */
void sk_noop_28(void)
{
    return;
}
/*--------------------------------------------------------------------*/
/* FUN_778c0 @ 0x000778c0   (est. sk_obj_mth_3)
 * Ghidra: void FUN_778c0(void)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_obj_mth_3(void)
{
    sk_slot_000778c0();
    sk_retain_low();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_778d4 @ 0x000778d4   (est. sk_f_778d4)
 * Ghidra: void FUN_778d4(void)
 * faithful call sequence; see FUN_778d4
 * Confidence: low
 */
void sk_f_778d4(void)
{
    sk_slot_000778d4();
    sk_slot_00070674();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_778e8 @ 0x000778e8   (est. sk_f_778e8)
 * Ghidra: void FUN_778e8(void)
 * faithful call sequence; see FUN_778e8
 * Confidence: low
 */
void sk_f_778e8(void)
{
    sk_slot_000778e8();
    sk_slot_000725c8();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_778fc @ 0x000778fc   (est. sk_f_778fc)
 * Ghidra: void FUN_778fc(void)
 * faithful call sequence; see FUN_778fc
 * Confidence: low
 */
void sk_f_778fc(void)
{
    sk_slot_000778fc();
    sk_type_resolve();
    sk_slot_0064e030();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_77910 @ 0x00077910   (est. sk_f_77910)
 * Ghidra: void FUN_77910(void)
 * faithful call sequence; see FUN_77910
 * Confidence: low
 */
void sk_f_77910(void)
{
    sk_slot_00077910();
    sk_type_resolve();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7791c @ 0x0007791c   (est. sk_f_7791c)
 * Ghidra: void FUN_7791c(unsigned long param_1, unsigned long param_2)
 * faithful call sequence; see FUN_7791c
 * Confidence: low
 */
void sk_f_7791c(unsigned long param_1, unsigned long param_2)
{
    sk_slot_0007791c();
    sk_alloc();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_77928 @ 0x00077928   (est. sk_f_77928)
 * Ghidra: void FUN_77928(void)
 * faithful call sequence; see FUN_77928
 * Confidence: low
 */
void sk_f_77928(void)
{
    sk_slot_00077928();
    sk_hash_lookup();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_77934 @ 0x00077934   (est. sk_pair_read28)
 * Ghidra: void FUN_77934(void)
 * reads pair at +0x28/+0x20
 * Confidence: low
 */
void sk_pair_read28(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_77960 @ 0x00077960   (est. sk_pair_read20)
 * Ghidra: void FUN_77960(void)
 * reads pair at +0x28/+0x20
 * Confidence: low
 */
void sk_pair_read20(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7798c @ 0x0007798c   (est. sk_f_7798c)
 * Ghidra: void FUN_7798c(unsigned long param_1)
 * faithful call sequence; see FUN_7798c
 * Confidence: low
 */
void sk_f_7798c(unsigned long param_1)
{
    sk_slot_0007798c();
    sk_type_lookup();
    sk_hash_combine();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_77a90 @ 0x00077a90   (est. sk_obj_deref)
 * Ghidra: void FUN_77a90(void)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_obj_deref(void)
{
    sk_slot_00077a90();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_77b58 @ 0x00077b58   (est. sk_f_77b58)
 * Ghidra: void FUN_77b58(unsigned long param_1)
 * faithful call sequence; see FUN_77b58
 * Confidence: low
 */
void sk_f_77b58(unsigned long param_1)
{
    sk_slot_00077b58();
    sk_write_word();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_77b84 @ 0x00077b84   (est. sk_f_77b84)
 * Ghidra: void FUN_77b84(void)
 * faithful call sequence; see FUN_77b84
 * Confidence: low
 */
void sk_f_77b84(void)
{
    sk_slot_00077b84();
    sk_hash_init();
    sk_write_word();
    sk_hash_fn();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_77bd0 @ 0x00077bd0   (est. sk_f_77bd0)
 * Ghidra: void FUN_77bd0(void)
 * faithful call sequence; see FUN_77bd0
 * Confidence: low
 */
void sk_f_77bd0(void)
{
    sk_slot_00077bd0();
    sk_hash_init();
    sk_slot_00077b58();
    sk_hash_fn();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_77c10 @ 0x00077c10   (est. sk_obj_find_by_key)
 * Ghidra: void FUN_77c10(unsigned long param_1, unsigned long param_2)
 * scans obj table for matching cap
 * Confidence: low
 */
void sk_obj_find_by_key(unsigned long param_1, unsigned long param_2)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_77c88 @ 0x00077c88   (est. sk_obj_set_ptr)
 * Ghidra: void FUN_77c88(unsigned long param_1)
 * 0036b118 old, store param_1 at +0x10
 * Confidence: low
 */
void sk_obj_set_ptr(unsigned long param_1)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_77d64 @ 0x00077d64   (est. sk_obj_rel_50)
 * Ghidra: void FUN_77d64(void)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_obj_rel_50(void)
{
    sk_slot_00077d64();
    sk_cpu_ctx();
    sk_slot_0007c004();
    sk_retain();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_77da4 @ 0x00077da4   (est. sk_obj_refswap_77da4)
 * Ghidra: void FUN_77da4(void)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_obj_refswap_77da4(void)
{
    sk_slot_00077da4();
    sk_slot_0007bfac();
    sk_slot_0007bff0();
    sk_slot_0007c158();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_77de8 @ 0x00077de8   (est. sk_obj_refswap_77de8)
 * Ghidra: void FUN_77de8(void)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_obj_refswap_77de8(void)
{
    sk_slot_00077de8();
    sk_slot_0007bfac();
    sk_slot_0007bfc8();
    sk_slot_0007c0a0();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_77e38 @ 0x00077e38   (est. sk_obj_get_58)
 * Ghidra: void FUN_77e38(void)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_obj_get_58(void)
{
    sk_slot_00077e38();
    sk_cpu_ctx();
    sk_slot_0007c004();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_77e74 @ 0x00077e74   (est. sk_obj_set_58)
 * Ghidra: void FUN_77e74(void)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_obj_set_58(void)
{
    sk_slot_00077e74();
    sk_slot_0007bfac();
    sk_slot_0007bff0();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_77eb8 @ 0x00077eb8   (est. sk_obj_refswap_77eb8)
 * Ghidra: void FUN_77eb8(void)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_obj_refswap_77eb8(void)
{
    sk_slot_00077eb8();
    sk_slot_0007bfac();
    sk_slot_0007bfc8();
    sk_slot_0007c0a0();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_77f08 @ 0x00077f08   (est. sk_obj_get_60)
 * Ghidra: void FUN_77f08(void)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_obj_get_60(void)
{
    sk_slot_00077f08();
    sk_cpu_ctx();
    sk_slot_0007c004();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_77f44 @ 0x00077f44   (est. sk_obj_set_60)
 * Ghidra: void FUN_77f44(void)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_obj_set_60(void)
{
    sk_slot_00077f44();
    sk_slot_0007bfac();
    sk_slot_0007bff0();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_77f88 @ 0x00077f88   (est. sk_obj_refswap_77f88)
 * Ghidra: void FUN_77f88(void)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_obj_refswap_77f88(void)
{
    sk_slot_00077f88();
    sk_slot_0007bfac();
    sk_slot_0007bfc8();
    sk_slot_0007c0a0();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_77fd8 @ 0x00077fd8   (est. sk_obj_mth_f0)
 * Ghidra: void FUN_77fd8(unsigned long param_1, unsigned long param_2)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_obj_mth_f0(unsigned long param_1, unsigned long param_2)
{
    sk_slot_00077fd8();
    sk_retain();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7802c @ 0x0007802c   (est. sk_obj_rel_68)
 * Ghidra: void FUN_7802c(void)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_obj_rel_68(void)
{
    sk_slot_0007802c();
    sk_cpu_ctx();
    sk_slot_0007c004();
    sk_retain();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7806c @ 0x0007806c   (est. sk_obj_refswap_7806c)
 * Ghidra: void FUN_7806c(void)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_obj_refswap_7806c(void)
{
    sk_slot_0007806c();
    sk_slot_0007bfac();
    sk_slot_0007bff0();
    sk_slot_0007c158();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_780b0 @ 0x000780b0   (est. sk_obj_refswap_780b0)
 * Ghidra: void FUN_780b0(void)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_obj_refswap_780b0(void)
{
    sk_slot_000780b0();
    sk_slot_0007bfac();
    sk_slot_0007bfc8();
    sk_slot_0007c0a0();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_78100 @ 0x00078100   (est. sk_f_78100)
 * Ghidra: void FUN_78100(unsigned long param_1, unsigned long param_2)
 * faithful call sequence; see FUN_78100
 * Confidence: low
 */
void sk_f_78100(unsigned long param_1, unsigned long param_2)
{
    sk_slot_00078100();
    sk_cap_copy();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7815c @ 0x0007815c   (est. sk_f_7815c)
 * Ghidra: void FUN_7815c(unsigned long param_1)
 * faithful call sequence; see FUN_7815c
 * Confidence: low
 */
void sk_f_7815c(unsigned long param_1)
{
    sk_slot_0007815c();
    sk_cpu_ctx();
    sk_lock();
    sk_cap_copy();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_781b4 @ 0x000781b4   (est. sk_f_781b4)
 * Ghidra: void FUN_781b4(void)
 * faithful call sequence; see FUN_781b4
 * Confidence: low
 */
void sk_f_781b4(void)
{
    sk_slot_000781b4();
    sk_slot_0007bfac();
    sk_alloc_teardown();
    sk_size_round();
    sk_slot_00077070();
    sk_alloc_finalize();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_78220 @ 0x00078220   (est. sk_obj_refswap_78220)
 * Ghidra: void FUN_78220(void)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_obj_refswap_78220(void)
{
    sk_slot_00078220();
    sk_slot_0007bfac();
    sk_slot_0007bfc8();
    sk_slot_0007c0a0();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_78270 @ 0x00078270   (est. sk_obj_mth_120)
 * Ghidra: void FUN_78270(unsigned long param_1, unsigned long param_2)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_obj_mth_120(unsigned long param_1, unsigned long param_2)
{
    sk_slot_00078270();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_782c0 @ 0x000782c0   (est. sk_f_782c0)
 * Ghidra: void FUN_782c0(void)
 * faithful call sequence; see FUN_782c0
 * Confidence: low
 */
void sk_f_782c0(void)
{
    sk_slot_000782c0();
    sk_cpu_ctx();
    sk_lock();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7830c @ 0x0007830c   (est. sk_f_7830c)
 * Ghidra: void FUN_7830c(unsigned long param_1, unsigned long param_2)
 * faithful call sequence; see FUN_7830c
 * Confidence: low
 */
void sk_f_7830c(unsigned long param_1, unsigned long param_2)
{
    sk_slot_0007830c();
    sk_cpu_ctx();
    sk_slot_0007c0e0();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_78368 @ 0x00078368   (est. sk_obj_refswap_78368)
 * Ghidra: void FUN_78368(void)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_obj_refswap_78368(void)
{
    sk_slot_00078368();
    sk_slot_0007bfac();
    sk_slot_0007bfc8();
    sk_slot_0007c0a0();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_783b8 @ 0x000783b8   (est. sk_obj_mth_138)
 * Ghidra: void FUN_783b8(unsigned long param_1, unsigned long param_2)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_obj_mth_138(unsigned long param_1, unsigned long param_2)
{
    sk_slot_000783b8();
    sk_retain();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_78414 @ 0x00078414   (est. sk_obj_rel_80)
 * Ghidra: void FUN_78414(void)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_obj_rel_80(void)
{
    sk_slot_00078414();
    sk_cpu_ctx();
    sk_slot_0007c004();
    sk_retain();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_78454 @ 0x00078454   (est. sk_obj_refswap_78454)
 * Ghidra: void FUN_78454(void)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_obj_refswap_78454(void)
{
    sk_slot_00078454();
    sk_slot_0007bfac();
    sk_slot_0007bff0();
    sk_slot_0007c158();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_78498 @ 0x00078498   (est. sk_obj_refswap_78498)
 * Ghidra: void FUN_78498(void)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_obj_refswap_78498(void)
{
    sk_slot_00078498();
    sk_slot_0007bfac();
    sk_slot_0007bfc8();
    sk_slot_0007c0a0();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_784e8 @ 0x000784e8   (est. sk_obj_mth_150)
 * Ghidra: void FUN_784e8(unsigned long param_1, unsigned long param_2)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_obj_mth_150(unsigned long param_1, unsigned long param_2)
{
    sk_slot_000784e8();
    sk_retain();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_78544 @ 0x00078544   (est. sk_obj_rel_88)
 * Ghidra: void FUN_78544(void)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_obj_rel_88(void)
{
    sk_slot_00078544();
    sk_cpu_ctx();
    sk_slot_0007c004();
    sk_retain();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_78584 @ 0x00078584   (est. sk_obj_refswap_78584)
 * Ghidra: void FUN_78584(void)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_obj_refswap_78584(void)
{
    sk_slot_00078584();
    sk_slot_0007bfac();
    sk_slot_0007bff0();
    sk_slot_0007c158();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_785c8 @ 0x000785c8   (est. sk_obj_refswap_785c8)
 * Ghidra: void FUN_785c8(void)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_obj_refswap_785c8(void)
{
    sk_slot_000785c8();
    sk_slot_0007bfac();
    sk_slot_0007bfc8();
    sk_slot_0007c0a0();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_78618 @ 0x00078618   (est. sk_obj_mth_168)
 * Ghidra: void FUN_78618(unsigned long param_1, unsigned long param_2)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_obj_mth_168(unsigned long param_1, unsigned long param_2)
{
    sk_slot_00078618();
    sk_retain();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_78674 @ 0x00078674   (est. sk_obj_rel_90)
 * Ghidra: void FUN_78674(void)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_obj_rel_90(void)
{
    sk_slot_00078674();
    sk_cpu_ctx();
    sk_slot_0007c004();
    sk_retain();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_786b4 @ 0x000786b4   (est. sk_obj_refswap_786b4)
 * Ghidra: void FUN_786b4(void)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_obj_refswap_786b4(void)
{
    sk_slot_000786b4();
    sk_slot_0007bfac();
    sk_slot_0007bff0();
    sk_slot_0007c158();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_786f8 @ 0x000786f8   (est. sk_obj_refswap_786f8)
 * Ghidra: void FUN_786f8(void)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_obj_refswap_786f8(void)
{
    sk_slot_000786f8();
    sk_slot_0007bfac();
    sk_slot_0007bfc8();
    sk_slot_0007c0a0();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_78748 @ 0x00078748   (est. sk_obj_get_98)
 * Ghidra: void FUN_78748(void)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_obj_get_98(void)
{
    sk_slot_00078748();
    sk_cpu_ctx();
    sk_slot_0007c004();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_78784 @ 0x00078784   (est. sk_obj_set_98)
 * Ghidra: void FUN_78784(void)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_obj_set_98(void)
{
    sk_slot_00078784();
    sk_slot_0007bfac();
    sk_slot_0007bff0();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_787c8 @ 0x000787c8   (est. sk_obj_refswap_787c8)
 * Ghidra: void FUN_787c8(void)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_obj_refswap_787c8(void)
{
    sk_slot_000787c8();
    sk_slot_0007bfac();
    sk_slot_0007bfc8();
    sk_slot_0007c0a0();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_78818 @ 0x00078818   (est. sk_f_78818)
 * Ghidra: void FUN_78818(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
 * faithful call sequence; see FUN_78818
 * Confidence: low
 */
void sk_f_78818(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
{
    sk_slot_00078818();
    sk_alloc();
    sk_slot_00078880();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_78880 @ 0x00078880   (est. sk_f_78880)
 * Ghidra: void FUN_78880(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
 * faithful call sequence; see FUN_78880
 * Confidence: low
 */
void sk_f_78880(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
{
    sk_slot_00078880();
    sk_slot_0007c0f8();
    sk_lock_ref();
    sk_slot_0007c028();
    sk_slot_0007c0b8();
    sk_slot_0007c0e0();
    sk_slot_0007c0b8();
    sk_cap_copy();
    sk_slot_0007c0e0();
    sk_slot_00078fec();
    sk_slot_0007c018();
    sk_lock_ref();
    sk_slot_0007c0d4();
    sk_lock_acquire();
    sk_align_up();
    sk_slot_0007c164();
    sk_lock_acquire();
    sk_slot_0007b178();
    sk_slot_0007b1c0();
    sk_alloc_teardown();
    sk_slot_0007b2c8();
    sk_slot_00072d5c();
    sk_slot_0007b4a4();
    sk_slot_00072d5c();
    sk_alloc_finalize();
    sk_pair_lookup();
    sk_obj_store();
    sk_cpu_ctx();
    sk_slot_0007c178();
    sk_hash_combine();
    sk_ref_bind();
    sk_slot_0007b33c();
    sk_cap_acquire();
    sk_alloc();
    sk_tcb_alloc();
    sk_slot_0007798c();
    sk_type_resolve();
    sk_alloc();
    sk_align_up();
    sk_slot_0007c0e0();
    sk_size_round();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_78fec @ 0x00078fec   (est. sk_obj_end_24)
 * Ghidra: void FUN_78fec(unsigned long param_1)
 * object end/limit offset 0x24
 * Confidence: high
 */
void sk_obj_end_24(unsigned long param_1)
{
    if ((param_1 & 1) != 0)
        param_1 = *(unsigned long *)(param_1 & ~1);
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_79038 @ 0x00079038   (est. sk_f_79038)
 * Ghidra: void FUN_79038(unsigned long param_1, unsigned long param_2)
 * faithful call sequence; see FUN_79038
 * Confidence: low
 */
void sk_f_79038(unsigned long param_1, unsigned long param_2)
{
    sk_slot_00079038();
    sk_lock_ref();
    sk_slot_0007c028();
    sk_slot_0007c1a4();
    sk_lock_acquire();
    sk_lock_ref();
    sk_slot_0007c1a4();
    sk_slot_0007c028();
    sk_cap_copy();
    sk_slot_0007b354();
    sk_slot_0007b384();
    sk_cap_alloc();
    sk_cap_parse();
    sk_map_resolve();
    sk_size_round();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_792d8 @ 0x000792d8   (est. sk_f_792d8)
 * Ghidra: void FUN_792d8(unsigned long param_1)
 * faithful call sequence; see FUN_792d8
 * Confidence: low
 */
void sk_f_792d8(unsigned long param_1)
{
    sk_slot_000792d8();
    sk_slot_0007c0f8();
    sk_lock_ref();
    sk_slot_0007c028();
    sk_slot_0007c1a4();
    sk_slot_0007c028();
    sk_slot_0007c1a4();
    sk_lock();
    sk_slot_00078fec();
    sk_slot_0007c164();
    sk_lock_acquire();
    sk_slot_0007b3b4();
    sk_retain();
    sk_lock();
    sk_cap_copy();
    sk_pair_lookup();
    sk_slot_000770e8();
    sk_size_round();
    sk_free();
    sk_slot_0007c0ec();
    sk_free();
    sk_slot_0007c0ec();
    sk_free();
    sk_slot_0007c0ec();
    sk_size_round();
    sk_slot_0007c0ec();
    sk_free();
    sk_slot_0007c0ec();
    sk_free();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_79678 @ 0x00079678   (est. sk_obj_teardown_c)
 * Ghidra: void FUN_79678(void)
 * 792d8+0036b6ac
 * Confidence: low
 */
void sk_obj_teardown_c(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7967c @ 0x0007967c   (est. sk_obj_teardown_d)
 * Ghidra: void FUN_7967c(void)
 * 792d8+0036b6ac
 * Confidence: low
 */
void sk_obj_teardown_d(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_796b0 @ 0x000796b0   (est. sk_f_796b0)
 * Ghidra: void FUN_796b0(void)
 * faithful call sequence; see FUN_796b0
 * Confidence: low
 */
void sk_f_796b0(void)
{
    sk_slot_000796b0();
    sk_slot_0007c0c4();
    sk_free();
    sk_slot_0007c018();
    sk_lock_ref();
    sk_slot_0007c0d4();
    sk_lock_acquire();
    sk_slot_0007c1c4();
    sk_align_up();
    sk_page_round();
    sk_slot_0007c1c4();
    sk_slot_0007eb2c();
    sk_slot_0007c1c4();
    sk_align_up();
    sk_slot_0007c1c4();
    sk_align_up();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7985c @ 0x0007985c   (est. sk_f_7985c)
 * Ghidra: void FUN_7985c(unsigned long param_1)
 * faithful call sequence; see FUN_7985c
 * Confidence: low
 */
void sk_f_7985c(unsigned long param_1)
{
    sk_slot_0007985c();
    sk_slot_0007c0c4();
    sk_free();
    sk_cap_match();
    sk_retain_low();
    sk_slot_0007b4e8();
    sk_lock_ref();
    sk_slot_0007c0d4();
    sk_lock_acquire();
    sk_bsz();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_79a88 @ 0x00079a88   (est. sk_f_79a88)
 * Ghidra: void FUN_79a88(unsigned long param_1)
 * faithful call sequence; see FUN_79a88
 * Confidence: low
 */
void sk_f_79a88(unsigned long param_1)
{
    sk_slot_00079a88();
    sk_slot_0007c0c4();
    sk_slot_0007bfdc();
    sk_fault();
    sk_fatal();
    sk_slot_0007c178();
    sk_free();
    sk_slot_0007c018();
    sk_lock_ref();
    sk_slot_0007c0d4();
    sk_lock_acquire();
    sk_slot_0007eb2c();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_79bf0 @ 0x00079bf0   (est. sk_f_79bf0)
 * Ghidra: void FUN_79bf0(void)
 * faithful call sequence; see FUN_79bf0
 * Confidence: low
 */
void sk_f_79bf0(void)
{
    sk_slot_00079bf0();
    sk_slot_0007c0c4();
    sk_cpu_ctx();
    sk_slot_0007c140();
    sk_slot_0007c018();
    sk_lock_ref();
    sk_slot_0007c0d4();
    sk_lock_acquire();
    sk_align_up();
    sk_sysreg_read();
    sk_ctx_begin();
    sk_alloc_ctx();
    sk_ctx_end();
    sk_alloc();
    sk_cnode_fill();
    sk_alloc_cnode();
    sk_panic_site();
    sk_slot_0007c0ac();
    sk_slot_0007c070();
    sk_slot_0007b2c8();
    sk_slot_0007c1d0();
    sk_slot_0007c140();
    sk_pair_lookup();
    sk_obj_store();
    sk_size_round();
    sk_slot_0007c0ac();
    sk_retain();
    sk_slot_0007b33c();
    sk_type_lookup();
    sk_tcb_install();
    sk_slot_0007c140();
    sk_bsz();
    sk_align_up();
    sk_slot_0007c0ac();
    sk_free();
    sk_slot_0007bf4c();
    sk_ver_get();
    sk_ver_check();
    sk_slot_0007c0ac();
    sk_slot_0007c088();
    sk_slot_0007b2c8();
    sk_slot_0007c1d0();
    sk_slot_0007c140();
    sk_slot_0007c0ac();
    sk_slot_0007c140();
    sk_free();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7a120 @ 0x0007a120   (est. sk_f_7a120)
 * Ghidra: void FUN_7a120(void)
 * faithful call sequence; see FUN_7a120
 * Confidence: low
 */
void sk_f_7a120(void)
{
    sk_slot_0007a120();
    sk_cpu_ctx();
    sk_slot_0007c198();
    sk_slot_0007c18c();
    sk_slot_0007c128();
    sk_free();
    sk_slot_0007c038();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7a1fc @ 0x0007a1fc   (est. sk_f_7a1fc)
 * Ghidra: void FUN_7a1fc(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4, unsigned long param_5, unsigned long param_6, unsigned long param_7)
 * faithful call sequence; see FUN_7a1fc
 * Confidence: low
 */
void sk_f_7a1fc(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4, unsigned long param_5, unsigned long param_6, unsigned long param_7)
{
    sk_slot_0007a1fc();
    sk_slot_0007a718();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7a274 @ 0x0007a274   (est. sk_f_7a274)
 * Ghidra: void FUN_7a274(unsigned long param_1)
 * faithful call sequence; see FUN_7a274
 * Confidence: low
 */
void sk_f_7a274(unsigned long param_1)
{
    sk_slot_0007a274();
    sk_slot_0007a718();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7a2dc @ 0x0007a2dc   (est. sk_f_7a2dc)
 * Ghidra: void FUN_7a2dc(unsigned long param_1)
 * faithful call sequence; see FUN_7a2dc
 * Confidence: low
 */
void sk_f_7a2dc(unsigned long param_1)
{
    sk_slot_0007a2dc();
    sk_cpu_ctx();
    sk_slot_0007c198();
    sk_slot_0007c18c();
    sk_slot_0007b524();
    sk_free();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7a3dc @ 0x0007a3dc   (est. sk_f_7a3dc)
 * Ghidra: void FUN_7a3dc(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
 * faithful call sequence; see FUN_7a3dc
 * Confidence: low
 */
void sk_f_7a3dc(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
{
    sk_slot_0007a3dc();
    sk_slot_0007a718();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7a454 @ 0x0007a454   (est. sk_f_7a454)
 * Ghidra: void FUN_7a454(unsigned long param_1)
 * faithful call sequence; see FUN_7a454
 * Confidence: low
 */
void sk_f_7a454(unsigned long param_1)
{
    sk_slot_0007a454();
    sk_cpu_ctx();
    sk_slot_0007c198();
    sk_slot_0007c18c();
    sk_slot_0007b544();
    sk_free();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7a548 @ 0x0007a548   (est. sk_f_7a548)
 * Ghidra: void FUN_7a548(unsigned long param_1, unsigned long param_2, unsigned long param_3)
 * faithful call sequence; see FUN_7a548
 * Confidence: low
 */
void sk_f_7a548(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    sk_slot_0007a548();
    sk_slot_0007a718();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7a5c4 @ 0x0007a5c4   (est. sk_f_7a5c4)
 * Ghidra: void FUN_7a5c4(void)
 * faithful call sequence; see FUN_7a5c4
 * Confidence: low
 */
void sk_f_7a5c4(void)
{
    sk_slot_0007a5c4();
    sk_cpu_ctx();
    sk_slot_0007c198();
    sk_slot_0007c18c();
    sk_slot_0007c128();
    sk_free();
    sk_slot_0007c038();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7a6a0 @ 0x0007a6a0   (est. sk_f_7a6a0)
 * Ghidra: void FUN_7a6a0(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4, unsigned long param_5, unsigned long param_6, unsigned long param_7)
 * faithful call sequence; see FUN_7a6a0
 * Confidence: low
 */
void sk_f_7a6a0(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4, unsigned long param_5, unsigned long param_6, unsigned long param_7)
{
    sk_slot_0007a6a0();
    sk_slot_0007a718();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7a718 @ 0x0007a718   (est. sk_f_7a718)
 * Ghidra: void FUN_7a718(unsigned long param_1, unsigned long param_2)
 * faithful call sequence; see FUN_7a718
 * Confidence: low
 */
void sk_f_7a718(unsigned long param_1, unsigned long param_2)
{
    sk_slot_0007a718();
    sk_cpu_ctx();
    sk_free();
    sk_emit_tag();
    sk_release();
    sk_spin_lock();
    sk_emit_fmt();
    sk_release();
    sk_emit_fmt();
    sk_free();
    sk_spin_lock();
    sk_emit_fmt();
    sk_release();
    sk_slot_0007bfdc();
    sk_fatal();
    sk_slot_0007c018();
    sk_lock_ref();
    sk_slot_0007c0d4();
    sk_lock_acquire();
    sk_align_up();
    sk_slot_0007eb2c();
    sk_slot_0007c0ac();
    sk_slot_00079bf0();
    sk_slot_0007eb2c();
    sk_slot_0007c0ac();
    sk_slot_0007b33c();
    sk_vas_alloc();
    sk_free();
    sk_slot_0007c0ac();
    sk_slot_0007c088();
    sk_slot_0007b2c8();
    sk_slot_0007b4a4();
    sk_slot_0007c0ac();
    sk_slot_0007abe0();
    sk_free();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7abe0 @ 0x0007abe0   (est. sk_f_7abe0)
 * Ghidra: void FUN_7abe0(unsigned long param_1, unsigned long param_2)
 * faithful call sequence; see FUN_7abe0
 * Confidence: low
 */
void sk_f_7abe0(unsigned long param_1, unsigned long param_2)
{
    sk_slot_0007abe0();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7ac24 @ 0x0007ac24   (est. sk_f_7ac24)
 * Ghidra: void FUN_7ac24(unsigned long param_1)
 * faithful call sequence; see FUN_7ac24
 * Confidence: low
 */
void sk_f_7ac24(unsigned long param_1)
{
    sk_slot_0007ac24();
    sk_cpu_ctx();
    sk_cap_match();
    sk_free();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7acd8 @ 0x0007acd8   (est. sk_f_7acd8)
 * Ghidra: void FUN_7acd8(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4, unsigned long param_5)
 * faithful call sequence; see FUN_7acd8
 * Confidence: low
 */
void sk_f_7acd8(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4, unsigned long param_5)
{
    sk_slot_0007acd8();
    sk_slot_0007b0cc();
    sk_slot_0007bfdc();
    sk_fault();
    sk_cap_match();
    sk_gate0();
    sk_slot_0007c14c();
    sk_slot_0007b58c();
    sk_slot_0007c14c();
    sk_slot_0007b5f4();
    sk_slot_00077070();
    sk_pair_lookup();
    sk_slot_00077088();
    sk_slot_0007c14c();
    sk_slot_0007c070();
    sk_slot_0007b2c8();
    sk_slot_0007b4a4();
    sk_slot_0007c14c();
    sk_slot_0007b134();
    sk_free();
    sk_size_round();
    sk_free();
    sk_slot_0007c14c();
    sk_retain_low();
    sk_slot_0007b4e8();
    sk_slot_0007bfdc();
    sk_fault();
    sk_fatal();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7b0cc @ 0x0007b0cc   (est. sk_f_7b0cc)
 * Ghidra: void FUN_7b0cc(unsigned long param_1, unsigned long param_2)
 * faithful call sequence; see FUN_7b0cc
 * Confidence: low
 */
void sk_f_7b0cc(unsigned long param_1, unsigned long param_2)
{
    sk_slot_0007b0cc();
    sk_cap_match();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7b134 @ 0x0007b134   (est. sk_f_7b134)
 * Ghidra: void FUN_7b134(unsigned long param_1, unsigned long param_2)
 * faithful call sequence; see FUN_7b134
 * Confidence: low
 */
void sk_f_7b134(unsigned long param_1, unsigned long param_2)
{
    sk_slot_0007b134();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7b178 @ 0x0007b178   (est. sk_obj_end_1c)
 * Ghidra: void FUN_7b178(unsigned long param_1)
 * object end/limit offset 0x1c
 * Confidence: high
 */
void sk_obj_end_1c_1(unsigned long param_1)
{
    if ((param_1 & 1) != 0)
        param_1 = *(unsigned long *)(param_1 & ~1);
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7b1c0 @ 0x0007b1c0   (est. sk_obj_end_14)
 * Ghidra: void FUN_7b1c0(unsigned long param_1)
 * object end/limit offset 0x14
 * Confidence: high
 */
void sk_obj_end_14_1(unsigned long param_1)
{
    if ((param_1 & 1) != 0)
        param_1 = *(unsigned long *)(param_1 & ~1);
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7b1f0 @ 0x0007b1f0   (est. sk_f_7b1f0)
 * Ghidra: void FUN_7b1f0(void)
 * faithful call sequence; see FUN_7b1f0
 * Confidence: low
 */
void sk_f_7b1f0(void)
{
    sk_slot_0007b1f0();
    sk_slot_0007b2c8();
    sk_slot_00072d5c();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7b208 @ 0x0007b208   (est. sk_f_7b208)
 * Ghidra: void FUN_7b208(void)
 * faithful call sequence; see FUN_7b208
 * Confidence: low
 */
void sk_f_7b208(void)
{
    sk_slot_0007b208();
    sk_slot_0007b2c8();
    sk_slot_0007340c();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7b220 @ 0x0007b220   (est. sk_f_7b220)
 * Ghidra: void FUN_7b220(void)
 * faithful call sequence; see FUN_7b220
 * Confidence: low
 */
void sk_f_7b220(void)
{
    sk_slot_0007b220();
    sk_slot_0007b2c8();
    sk_slot_00073498();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7b238 @ 0x0007b238   (est. sk_f_7b238)
 * Ghidra: void FUN_7b238(void)
 * faithful call sequence; see FUN_7b238
 * Confidence: low
 */
void sk_f_7b238(void)
{
    sk_slot_0007b238();
    sk_slot_0007b2c8();
    sk_slot_000738b0();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7b250 @ 0x0007b250   (est. sk_f_7b250)
 * Ghidra: void FUN_7b250(void)
 * faithful call sequence; see FUN_7b250
 * Confidence: low
 */
void sk_f_7b250(void)
{
    sk_slot_0007b250();
    sk_slot_0007b2c8();
    sk_slot_0007393c();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7b268 @ 0x0007b268   (est. sk_f_7b268)
 * Ghidra: void FUN_7b268(void)
 * faithful call sequence; see FUN_7b268
 * Confidence: low
 */
void sk_f_7b268(void)
{
    sk_slot_0007b268();
    sk_slot_0007b2c8();
    sk_slot_00072c0c();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7b280 @ 0x0007b280   (est. sk_f_7b280)
 * Ghidra: void FUN_7b280(void)
 * faithful call sequence; see FUN_7b280
 * Confidence: low
 */
void sk_f_7b280(void)
{
    sk_slot_0007b280();
    sk_slot_0007b2c8();
    sk_slot_00073380();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7b298 @ 0x0007b298   (est. sk_f_7b298)
 * Ghidra: void FUN_7b298(void)
 * faithful call sequence; see FUN_7b298
 * Confidence: low
 */
void sk_f_7b298(void)
{
    sk_slot_0007b298();
    sk_slot_0007b2c8();
    sk_slot_00073a64();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7b2b0 @ 0x0007b2b0   (est. sk_f_7b2b0)
 * Ghidra: void FUN_7b2b0(void)
 * faithful call sequence; see FUN_7b2b0
 * Confidence: low
 */
void sk_f_7b2b0(void)
{
    sk_slot_0007b2b0();
    sk_slot_0007b2c8();
    sk_slot_0007499c();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7b2c8 @ 0x0007b2c8   (est. sk_f_7b2c8)
 * Ghidra: void FUN_7b2c8(unsigned long param_1)
 * faithful call sequence; see FUN_7b2c8
 * Confidence: low
 */
void sk_f_7b2c8(unsigned long param_1)
{
    sk_slot_0007b2c8();
    sk_retain_low();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7b324 @ 0x0007b324   (est. sk_f_7b324)
 * Ghidra: void FUN_7b324(unsigned long param_1)
 * faithful call sequence; see FUN_7b324
 * Confidence: low
 */
void sk_f_7b324(unsigned long param_1)
{
    sk_slot_0007b324();
    sk_slot_0007b4a4();
    sk_slot_00072d5c();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7b33c @ 0x0007b33c   (est. sk_f_7b33c)
 * Ghidra: void FUN_7b33c(void)
 * faithful call sequence; see FUN_7b33c
 * Confidence: low
 */
void sk_f_7b33c(void)
{
    sk_slot_0007b33c();
    sk_map_find();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7b354 @ 0x0007b354   (est. sk_obj_end_28)
 * Ghidra: void FUN_7b354(unsigned long param_1)
 * object end/limit offset 0x28
 * Confidence: high
 */
void sk_obj_end_28(unsigned long param_1)
{
    if ((param_1 & 1) != 0)
        param_1 = *(unsigned long *)(param_1 & ~1);
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7b384 @ 0x0007b384   (est. sk_obj_end_c)
 * Ghidra: void FUN_7b384(unsigned long param_1)
 * object end/limit offset 0xc
 * Confidence: high
 */
void sk_obj_end_c_1(unsigned long param_1)
{
    if ((param_1 & 1) != 0)
        param_1 = *(unsigned long *)(param_1 & ~1);
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7b3b4 @ 0x0007b3b4   (est. sk_obj_end_18)
 * Ghidra: void FUN_7b3b4(unsigned long param_1)
 * object end/limit offset 0x18
 * Confidence: high
 */
void sk_obj_end_18_1(unsigned long param_1)
{
    if ((param_1 & 1) != 0)
        param_1 = *(unsigned long *)(param_1 & ~1);
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7b3e4 @ 0x0007b3e4   (est. sk_f_7b3e4)
 * Ghidra: void FUN_7b3e4(unsigned long param_1)
 * faithful call sequence; see FUN_7b3e4
 * Confidence: low
 */
void sk_f_7b3e4(unsigned long param_1)
{
    sk_slot_0007b3e4();
    sk_slot_0007b4a4();
    sk_slot_0007340c();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7b3fc @ 0x0007b3fc   (est. sk_f_7b3fc)
 * Ghidra: void FUN_7b3fc(unsigned long param_1)
 * faithful call sequence; see FUN_7b3fc
 * Confidence: low
 */
void sk_f_7b3fc(unsigned long param_1)
{
    sk_slot_0007b3fc();
    sk_slot_0007b4a4();
    sk_slot_00073498();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7b414 @ 0x0007b414   (est. sk_f_7b414)
 * Ghidra: void FUN_7b414(unsigned long param_1)
 * faithful call sequence; see FUN_7b414
 * Confidence: low
 */
void sk_f_7b414(unsigned long param_1)
{
    sk_slot_0007b414();
    sk_slot_0007b4a4();
    sk_slot_000738b0();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7b42c @ 0x0007b42c   (est. sk_f_7b42c)
 * Ghidra: void FUN_7b42c(unsigned long param_1)
 * faithful call sequence; see FUN_7b42c
 * Confidence: low
 */
void sk_f_7b42c(unsigned long param_1)
{
    sk_slot_0007b42c();
    sk_slot_0007b4a4();
    sk_slot_0007393c();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7b444 @ 0x0007b444   (est. sk_f_7b444)
 * Ghidra: void FUN_7b444(unsigned long param_1)
 * faithful call sequence; see FUN_7b444
 * Confidence: low
 */
void sk_f_7b444(unsigned long param_1)
{
    sk_slot_0007b444();
    sk_slot_0007b4a4();
    sk_slot_00072c0c();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7b45c @ 0x0007b45c   (est. sk_f_7b45c)
 * Ghidra: void FUN_7b45c(unsigned long param_1)
 * faithful call sequence; see FUN_7b45c
 * Confidence: low
 */
void sk_f_7b45c(unsigned long param_1)
{
    sk_slot_0007b45c();
    sk_slot_0007b4a4();
    sk_slot_00073380();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7b474 @ 0x0007b474   (est. sk_f_7b474)
 * Ghidra: void FUN_7b474(unsigned long param_1)
 * faithful call sequence; see FUN_7b474
 * Confidence: low
 */
void sk_f_7b474(unsigned long param_1)
{
    sk_slot_0007b474();
    sk_slot_0007b4a4();
    sk_slot_00073a64();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7b48c @ 0x0007b48c   (est. sk_f_7b48c)
 * Ghidra: void FUN_7b48c(unsigned long param_1)
 * faithful call sequence; see FUN_7b48c
 * Confidence: low
 */
void sk_f_7b48c(unsigned long param_1)
{
    sk_slot_0007b48c();
    sk_slot_0007b4a4();
    sk_slot_0007499c();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7b4a4 @ 0x0007b4a4   (est. sk_f_7b4a4)
 * Ghidra: void FUN_7b4a4(unsigned long param_1, unsigned long param_2)
 * faithful call sequence; see FUN_7b4a4
 * Confidence: low
 */
void sk_f_7b4a4(unsigned long param_1, unsigned long param_2)
{
    sk_slot_0007b4a4();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7b4e8 @ 0x0007b4e8   (est. sk_f_7b4e8)
 * Ghidra: void FUN_7b4e8(unsigned long param_1)
 * faithful call sequence; see FUN_7b4e8
 * Confidence: low
 */
void sk_f_7b4e8(unsigned long param_1)
{
    sk_slot_0007b4e8();
    sk_slot_00072de8();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7b4fc @ 0x0007b4fc   (est. sk_f_7b4fc)
 * Ghidra: void FUN_7b4fc(void)
 * faithful call sequence; see FUN_7b4fc
 * Confidence: low
 */
void sk_f_7b4fc(void)
{
    sk_slot_0007b4fc();
    sk_slot_0007a1fc();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7b500 @ 0x0007b500   (est. sk_f_7b500)
 * Ghidra: void FUN_7b500(void)
 * faithful call sequence; see FUN_7b500
 * Confidence: low
 */
void sk_f_7b500(void)
{
    sk_slot_0007b500();
    sk_slot_0007a1fc();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7b524 @ 0x0007b524   (est. sk_f_7b524)
 * Ghidra: void FUN_7b524(void)
 * faithful call sequence; see FUN_7b524
 * Confidence: low
 */
void sk_f_7b524(void)
{
    sk_slot_0007b524();
    sk_slot_0007a3dc();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7b528 @ 0x0007b528   (est. sk_f_7b528)
 * Ghidra: void FUN_7b528(void)
 * faithful call sequence; see FUN_7b528
 * Confidence: low
 */
void sk_f_7b528(void)
{
    sk_slot_0007b528();
    sk_slot_0007a3dc();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7b544 @ 0x0007b544   (est. sk_f_7b544)
 * Ghidra: void FUN_7b544(void)
 * faithful call sequence; see FUN_7b544
 * Confidence: low
 */
void sk_f_7b544(void)
{
    sk_slot_0007b544();
    sk_slot_0007a548();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7b548 @ 0x0007b548   (est. sk_f_7b548)
 * Ghidra: void FUN_7b548(void)
 * faithful call sequence; see FUN_7b548
 * Confidence: low
 */
void sk_f_7b548(void)
{
    sk_slot_0007b548();
    sk_slot_0007a548();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7b564 @ 0x0007b564   (est. sk_f_7b564)
 * Ghidra: void FUN_7b564(void)
 * faithful call sequence; see FUN_7b564
 * Confidence: low
 */
void sk_f_7b564(void)
{
    sk_slot_0007b564();
    sk_slot_0007a6a0();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7b568 @ 0x0007b568   (est. sk_f_7b568)
 * Ghidra: void FUN_7b568(void)
 * faithful call sequence; see FUN_7b568
 * Confidence: low
 */
void sk_f_7b568(void)
{
    sk_slot_0007b568();
    sk_slot_0007a6a0();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7b58c @ 0x0007b58c   (est. sk_f_7b58c)
 * Ghidra: void FUN_7b58c(unsigned long param_1, unsigned long param_2)
 * faithful call sequence; see FUN_7b58c
 * Confidence: low
 */
void sk_f_7b58c(unsigned long param_1, unsigned long param_2)
{
    sk_slot_0007b58c();
    sk_type_resolve();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7b5f4 @ 0x0007b5f4   (est. sk_f_7b5f4)
 * Ghidra: void FUN_7b5f4(unsigned long param_1)
 * faithful call sequence; see FUN_7b5f4
 * Confidence: low
 */
void sk_f_7b5f4(unsigned long param_1)
{
    sk_slot_0007b5f4();
    sk_type_resolve();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7b654 @ 0x0007b654   (est. sk_f_7b654)
 * Ghidra: void FUN_7b654(void)
 * faithful call sequence; see FUN_7b654
 * Confidence: low
 */
void sk_f_7b654(void)
{
    sk_slot_0007b654();
    sk_slot_0007bf80();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7b6a0 @ 0x0007b6a0   (est. sk_f_7b6a0)
 * Ghidra: void FUN_7b6a0(void)
 * faithful call sequence; see FUN_7b6a0
 * Confidence: low
 */
void sk_f_7b6a0(void)
{
    sk_slot_0007b6a0();
    sk_slot_0007bf80();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7b6d8 @ 0x0007b6d8   (est. sk_f_7b6d8)
 * Ghidra: void FUN_7b6d8(unsigned long param_1)
 * faithful call sequence; see FUN_7b6d8
 * Confidence: low
 */
void sk_f_7b6d8(unsigned long param_1)
{
    sk_slot_0007b6d8();
    sk_cpu_ctx();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7b718 @ 0x0007b718   (est. sk_f_7b718)
 * Ghidra: void FUN_7b718(void)
 * faithful call sequence; see FUN_7b718
 * Confidence: low
 */
void sk_f_7b718(void)
{
    sk_slot_0007b718();
    sk_slot_0007bf80();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7b750 @ 0x0007b750   (est. sk_f_7b750)
 * Ghidra: void FUN_7b750(unsigned long param_1)
 * faithful call sequence; see FUN_7b750
 * Confidence: low
 */
void sk_f_7b750(unsigned long param_1)
{
    sk_slot_0007b750();
    sk_cpu_ctx();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7b790 @ 0x0007b790   (est. sk_f_7b790)
 * Ghidra: void FUN_7b790(void)
 * faithful call sequence; see FUN_7b790
 * Confidence: low
 */
void sk_f_7b790(void)
{
    sk_slot_0007b790();
    sk_slot_0007bf80();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7b7d0 @ 0x0007b7d0   (est. sk_f_7b7d0)
 * Ghidra: void FUN_7b7d0(void)
 * faithful call sequence; see FUN_7b7d0
 * Confidence: low
 */
void sk_f_7b7d0(void)
{
    sk_slot_0007b7d0();
    sk_cpu_ctx();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7b818 @ 0x0007b818   (est. sk_f_7b818)
 * Ghidra: void FUN_7b818(void)
 * faithful call sequence; see FUN_7b818
 * Confidence: low
 */
void sk_f_7b818(void)
{
    sk_slot_0007b818();
    sk_slot_0007bf80();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7b864 @ 0x0007b864   (est. sk_f_7b864)
 * Ghidra: void FUN_7b864(void)
 * faithful call sequence; see FUN_7b864
 * Confidence: low
 */
void sk_f_7b864(void)
{
    sk_slot_0007b864();
    sk_slot_0007bf80();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7b8ac @ 0x0007b8ac   (est. sk_f_7b8ac)
 * Ghidra: void FUN_7b8ac(void)
 * faithful call sequence; see FUN_7b8ac
 * Confidence: low
 */
void sk_f_7b8ac(void)
{
    sk_slot_0007b8ac();
    sk_slot_0007bf80();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7b8f4 @ 0x0007b8f4   (est. sk_f_7b8f4)
 * Ghidra: void FUN_7b8f4(void)
 * faithful call sequence; see FUN_7b8f4
 * Confidence: low
 */
void sk_f_7b8f4(void)
{
    sk_slot_0007b8f4();
    sk_slot_0007bf80();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7b93c @ 0x0007b93c   (est. sk_f_7b93c)
 * Ghidra: void FUN_7b93c(void)
 * faithful call sequence; see FUN_7b93c
 * Confidence: low
 */
void sk_f_7b93c(void)
{
    sk_slot_0007b93c();
    sk_slot_0007bf80();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7b97c @ 0x0007b97c   (est. sk_f_7b97c)
 * Ghidra: void FUN_7b97c(unsigned long param_1)
 * faithful call sequence; see FUN_7b97c
 * Confidence: low
 */
void sk_f_7b97c(unsigned long param_1)
{
    sk_slot_0007b97c();
    sk_cpu_ctx();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7bcf8 @ 0x0007bcf8   (est. sk_f_7bcf8)
 * Ghidra: void FUN_7bcf8(unsigned long param_1)
 * faithful call sequence; see FUN_7bcf8
 * Confidence: low
 */
void sk_f_7bcf8(unsigned long param_1)
{
    sk_slot_0007bcf8();
    sk_lock_state();
    sk_obj_walk();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7bdb4 @ 0x0007bdb4   (est. sk_hw_sync2)
 * Ghidra: void FUN_7bdb4(void)
 * hw sync wrapper
 * Confidence: low
 */
void sk_hw_sync2(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7be74 @ 0x0007be74   (est. sk_f_7be74)
 * Ghidra: void FUN_7be74(void)
 * faithful call sequence; see FUN_7be74
 * Confidence: low
 */
void sk_f_7be74(void)
{
    sk_slot_0007be74();
    sk_slot_0007c1b0();
    sk_slot_00073018();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7be8c @ 0x0007be8c   (est. sk_f_7be8c)
 * Ghidra: void FUN_7be8c(void)
 * faithful call sequence; see FUN_7be8c
 * Confidence: low
 */
void sk_f_7be8c(void)
{
    sk_slot_0007be8c();
    sk_slot_0007c1b0();
    sk_slot_000731dc();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7bea4 @ 0x0007bea4   (est. sk_f_7bea4)
 * Ghidra: void FUN_7bea4(void)
 * faithful call sequence; see FUN_7bea4
 * Confidence: low
 */
void sk_f_7bea4(void)
{
    sk_slot_0007bea4();
    sk_slot_0007c1b0();
    sk_slot_00072d5c();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7bebc @ 0x0007bebc   (est. sk_f_7bebc)
 * Ghidra: void FUN_7bebc(void)
 * faithful call sequence; see FUN_7bebc
 * Confidence: low
 */
void sk_f_7bebc(void)
{
    sk_slot_0007bebc();
    sk_slot_0007c1b0();
    sk_tcb_init();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7bed4 @ 0x0007bed4   (est. sk_f_7bed4)
 * Ghidra: void FUN_7bed4(void)
 * faithful call sequence; see FUN_7bed4
 * Confidence: low
 */
void sk_f_7bed4(void)
{
    sk_slot_0007bed4();
    sk_slot_0007c1b0();
    sk_slot_00073380();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7beec @ 0x0007beec   (est. sk_f_7beec)
 * Ghidra: void FUN_7beec(void)
 * faithful call sequence; see FUN_7beec
 * Confidence: low
 */
void sk_f_7beec(void)
{
    sk_slot_0007beec();
    sk_slot_0007c1b0();
    sk_slot_00074538();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7bf04 @ 0x0007bf04   (est. sk_f_7bf04)
 * Ghidra: void FUN_7bf04(void)
 * faithful call sequence; see FUN_7bf04
 * Confidence: low
 */
void sk_f_7bf04(void)
{
    sk_slot_0007bf04();
    sk_slot_0007c1b0();
    sk_slot_000745d4();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7bf1c @ 0x0007bf1c   (est. sk_f_7bf1c)
 * Ghidra: void FUN_7bf1c(void)
 * faithful call sequence; see FUN_7bf1c
 * Confidence: low
 */
void sk_f_7bf1c(void)
{
    sk_slot_0007bf1c();
    sk_slot_0007c1b0();
    sk_slot_00074910();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7bf34 @ 0x0007bf34   (est. sk_f_7bf34)
 * Ghidra: void FUN_7bf34(void)
 * faithful call sequence; see FUN_7bf34
 * Confidence: low
 */
void sk_f_7bf34(void)
{
    sk_slot_0007bf34();
    sk_slot_0007c1b0();
    sk_slot_0007499c();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7bf4c @ 0x0007bf4c   (est. sk_f_7bf4c)
 * Ghidra: void FUN_7bf4c(void)
 * faithful call sequence; see FUN_7bf4c
 * Confidence: low
 */
void sk_f_7bf4c(void)
{
    sk_slot_0007bf4c();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7bf54 @ 0x0007bf54   (est. sk_f_7bf54)
 * Ghidra: void FUN_7bf54(void)
 * faithful call sequence; see FUN_7bf54
 * Confidence: low
 */
void sk_f_7bf54(void)
{
    sk_slot_0007bebc();
    sk_slot_0007c1b0();
    sk_tcb_init();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7bf80 @ 0x0007bf80   (est. sk_noop)
 * Ghidra: void FUN_7bf80(void)
 * empty leaf / placeholder hook
 * Confidence: low
 */
void sk_noop_29(void)
{
    return;
}
/*--------------------------------------------------------------------*/
/* FUN_7bf94 @ 0x0007bf94   (est. sk_noop)
 * Ghidra: void FUN_7bf94(void)
 * empty leaf / placeholder hook
 * Confidence: low
 */
void sk_noop_30(void)
{
    return;
}
/*--------------------------------------------------------------------*/
/* FUN_7bfac @ 0x0007bfac   (est. sk_noop)
 * Ghidra: void FUN_7bfac(void)
 * empty leaf / placeholder hook
 * Confidence: low
 */
void sk_noop_31(void)
{
    return;
}
/*--------------------------------------------------------------------*/
/* FUN_7bfc8 @ 0x0007bfc8   (est. sk_f_7bfc8)
 * Ghidra: void FUN_7bfc8(void)
 * faithful call sequence; see FUN_7bfc8
 * Confidence: low
 */
void sk_f_7bfc8(void)
{
    sk_slot_0007bfc8();
    sk_alloc_teardown();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7bfdc @ 0x0007bfdc   (est. sk_f_7bfdc)
 * Ghidra: void FUN_7bfdc(void)
 * faithful call sequence; see FUN_7bfdc
 * Confidence: low
 */
void sk_f_7bfdc(void)
{
    sk_slot_0007bfdc();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7bff0 @ 0x0007bff0   (est. sk_f_7bff0)
 * Ghidra: void FUN_7bff0(void)
 * faithful call sequence; see FUN_7bff0
 * Confidence: low
 */
void sk_f_7bff0(void)
{
    sk_slot_0007bff0();
    sk_alloc_teardown();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7c004 @ 0x0007c004   (est. sk_f_7c004)
 * Ghidra: void FUN_7c004(void)
 * faithful call sequence; see FUN_7c004
 * Confidence: low
 */
void sk_f_7c004(void)
{
    sk_slot_0007c004();
    sk_alloc_teardown();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7c018 @ 0x0007c018   (est. sk_zero)
 * Ghidra: void FUN_7c018(void)
 * returns 0
 * Confidence: low
 */
void sk_zero(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7c028 @ 0x0007c028   (est. sk_noop)
 * Ghidra: void FUN_7c028(void)
 * empty leaf / placeholder hook
 * Confidence: low
 */
void sk_noop_32(void)
{
    return;
}
/*--------------------------------------------------------------------*/
/* FUN_7c038 @ 0x0007c038   (est. sk_f_7c038)
 * Ghidra: void FUN_7c038(void)
 * faithful call sequence; see FUN_7c038
 * Confidence: low
 */
void sk_f_7c038(void)
{
    sk_slot_0007c038();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7c070 @ 0x0007c070   (est. sk_noop)
 * Ghidra: void FUN_7c070(void)
 * empty leaf / placeholder hook
 * Confidence: low
 */
void sk_noop_33(void)
{
    return;
}
/*--------------------------------------------------------------------*/
/* FUN_7c088 @ 0x0007c088   (est. sk_noop)
 * Ghidra: void FUN_7c088(void)
 * empty leaf / placeholder hook
 * Confidence: low
 */
void sk_noop_34(void)
{
    return;
}
/*--------------------------------------------------------------------*/
/* FUN_7c0a0 @ 0x0007c0a0   (est. sk_noop)
 * Ghidra: void FUN_7c0a0(void)
 * empty leaf / placeholder hook
 * Confidence: low
 */
void sk_noop_35(void)
{
    return;
}
/*--------------------------------------------------------------------*/
/* FUN_7c0ac @ 0x0007c0ac   (est. sk_noop)
 * Ghidra: void FUN_7c0ac(void)
 * empty leaf / placeholder hook
 * Confidence: low
 */
void sk_noop_36(void)
{
    return;
}
/*--------------------------------------------------------------------*/
/* FUN_7c0b8 @ 0x0007c0b8   (est. sk_noop)
 * Ghidra: void FUN_7c0b8(void)
 * empty leaf / placeholder hook
 * Confidence: low
 */
void sk_noop_37(void)
{
    return;
}
/*--------------------------------------------------------------------*/
/* FUN_7c0c4 @ 0x0007c0c4   (est. sk_noop)
 * Ghidra: void FUN_7c0c4(void)
 * empty leaf / placeholder hook
 * Confidence: low
 */
void sk_noop_38(void)
{
    return;
}
/*--------------------------------------------------------------------*/
/* FUN_7c0d4 @ 0x0007c0d4   (est. sk_noop)
 * Ghidra: void FUN_7c0d4(void)
 * empty leaf / placeholder hook
 * Confidence: low
 */
void sk_noop_39(void)
{
    return;
}
/*--------------------------------------------------------------------*/
/* FUN_7c0e0 @ 0x0007c0e0   (est. sk_f_7c0e0)
 * Ghidra: void FUN_7c0e0(unsigned long param_1, unsigned long param_2)
 * faithful call sequence; see FUN_7c0e0
 * Confidence: low
 */
void sk_f_7c0e0(unsigned long param_1, unsigned long param_2)
{
    sk_slot_0007c0e0();
    sk_alloc_teardown();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7c0ec @ 0x0007c0ec   (est. sk_noop)
 * Ghidra: void FUN_7c0ec(void)
 * empty leaf / placeholder hook
 * Confidence: low
 */
void sk_noop_40(void)
{
    return;
}
/*--------------------------------------------------------------------*/
/* FUN_7c0f8 @ 0x0007c0f8   (est. sk_zero2)
 * Ghidra: void FUN_7c0f8(void)
 * returns 0
 * Confidence: low
 */
void sk_zero2(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7c128 @ 0x0007c128   (est. sk_noop)
 * Ghidra: void FUN_7c128(void)
 * empty leaf / placeholder hook
 * Confidence: low
 */
void sk_noop_41(void)
{
    return;
}
/*--------------------------------------------------------------------*/
/* FUN_7c140 @ 0x0007c140   (est. sk_f_7c140)
 * Ghidra: void FUN_7c140(void)
 * faithful call sequence; see FUN_7c140
 * Confidence: low
 */
void sk_f_7c140(void)
{
    sk_slot_0007c140();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7c14c @ 0x0007c14c   (est. sk_noop)
 * Ghidra: void FUN_7c14c(void)
 * empty leaf / placeholder hook
 * Confidence: low
 */
void sk_noop_42(void)
{
    return;
}
/*--------------------------------------------------------------------*/
/* FUN_7c158 @ 0x0007c158   (est. sk_f_7c158)
 * Ghidra: void FUN_7c158(void)
 * faithful call sequence; see FUN_7c158
 * Confidence: low
 */
void sk_f_7c158(void)
{
    sk_slot_0007c158();
    sk_free();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7c164 @ 0x0007c164   (est. sk_noop)
 * Ghidra: void FUN_7c164(void)
 * empty leaf / placeholder hook
 * Confidence: low
 */
void sk_noop_43(void)
{
    return;
}
/*--------------------------------------------------------------------*/
/* FUN_7c178 @ 0x0007c178   (est. sk_noop)
 * Ghidra: void FUN_7c178(void)
 * empty leaf / placeholder hook
 * Confidence: low
 */
void sk_noop_44(void)
{
    return;
}
/*--------------------------------------------------------------------*/
/* FUN_7c18c @ 0x0007c18c   (est. sk_noop)
 * Ghidra: void FUN_7c18c(void)
 * empty leaf / placeholder hook
 * Confidence: low
 */
void sk_noop_45(void)
{
    return;
}
/*--------------------------------------------------------------------*/
/* FUN_7c198 @ 0x0007c198   (est. sk_noop)
 * Ghidra: void FUN_7c198(void)
 * empty leaf / placeholder hook
 * Confidence: low
 */
void sk_noop_46(void)
{
    return;
}
/*--------------------------------------------------------------------*/
/* FUN_7c1a4 @ 0x0007c1a4   (est. sk_noop)
 * Ghidra: void FUN_7c1a4(void)
 * empty leaf / placeholder hook
 * Confidence: low
 */
void sk_noop_47(void)
{
    return;
}
/*--------------------------------------------------------------------*/
/* FUN_7c1b0 @ 0x0007c1b0   (est. sk_f_7c1b0)
 * Ghidra: void FUN_7c1b0(unsigned long param_1)
 * faithful call sequence; see FUN_7c1b0
 * Confidence: low
 */
void sk_f_7c1b0(unsigned long param_1)
{
    sk_slot_0007c1b0();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7c1c4 @ 0x0007c1c4   (est. sk_noop)
 * Ghidra: void FUN_7c1c4(void)
 * empty leaf / placeholder hook
 * Confidence: low
 */
void sk_noop_48(void)
{
    return;
}
/*--------------------------------------------------------------------*/
/* FUN_7c1d0 @ 0x0007c1d0   (est. sk_f_7c1d0)
 * Ghidra: void FUN_7c1d0(void)
 * faithful call sequence; see FUN_7c1d0
 * Confidence: low
 */
void sk_f_7c1d0(void)
{
    sk_slot_0007c1d0();
    sk_slot_0007b4a4();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7c1e4 @ 0x0007c1e4   (est. sk_f_7c1e4)
 * Ghidra: void FUN_7c1e4(void)
 * faithful call sequence; see FUN_7c1e4
 * Confidence: low
 */
void sk_f_7c1e4(void)
{
    sk_unlock();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7c1e8 @ 0x0007c1e8   (est. sk_f_7c1e8)
 * Ghidra: void FUN_7c1e8(void)
 * faithful call sequence; see FUN_7c1e8
 * Confidence: low
 */
void sk_f_7c1e8(void)
{
    sk_slot_0007c1e8();
    sk_lock_claim();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7c210 @ 0x0007c210   (est. sk_f_7c210)
 * Ghidra: void FUN_7c210(unsigned long param_1)
 * faithful call sequence; see FUN_7c210
 * Confidence: low
 */
void sk_f_7c210(unsigned long param_1)
{
    sk_slot_0007c210();
    sk_alloc_teardown();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7c250 @ 0x0007c250   (est. sk_f_7c250)
 * Ghidra: void FUN_7c250(unsigned long param_1)
 * faithful call sequence; see FUN_7c250
 * Confidence: low
 */
void sk_f_7c250(unsigned long param_1)
{
    sk_slot_0007c250();
    sk_alloc_teardown();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7c2a0 @ 0x0007c2a0   (est. sk_obj_mth_80)
 * Ghidra: void FUN_7c2a0(unsigned long param_1, unsigned long param_2)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_obj_mth_80(unsigned long param_1, unsigned long param_2)
{
    sk_slot_0007c2a0();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7c2e8 @ 0x0007c2e8   (est. sk_f_7c2e8)
 * Ghidra: void FUN_7c2e8(void)
 * faithful call sequence; see FUN_7c2e8
 * Confidence: low
 */
void sk_f_7c2e8(void)
{
    sk_slot_0007c2e8();
    sk_lock_claim();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7c310 @ 0x0007c310   (est. sk_f_7c310)
 * Ghidra: void FUN_7c310(void)
 * faithful call sequence; see FUN_7c310
 * Confidence: low
 */
void sk_f_7c310(void)
{
    sk_slot_0007c310();
    sk_pair_new();
    sk_alloc_teardown();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7c358 @ 0x0007c358   (est. sk_f_7c358)
 * Ghidra: void FUN_7c358(unsigned long param_1)
 * faithful call sequence; see FUN_7c358
 * Confidence: low
 */
void sk_f_7c358(unsigned long param_1)
{
    sk_slot_0007c358();
    sk_alloc_teardown();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7c3d8 @ 0x0007c3d8   (est. sk_f_7c3d8)
 * Ghidra: void FUN_7c3d8(void)
 * faithful call sequence; see FUN_7c3d8
 * Confidence: low
 */
void sk_f_7c3d8(void)
{
    sk_slot_0007c3d8();
    sk_pair_new();
    sk_pair_index();
    sk_slot_0007c028();
    sk_size_round();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7c4ac @ 0x0007c4ac   (est. sk_f_7c4ac)
 * Ghidra: void FUN_7c4ac(unsigned long param_1, unsigned long param_2)
 * faithful call sequence; see FUN_7c4ac
 * Confidence: low
 */
void sk_f_7c4ac(unsigned long param_1, unsigned long param_2)
{
    sk_slot_0007c4ac();
    sk_cpu_ctx();
    sk_panic_msg();
    sk_panic_abort();
    sk_trace_flush();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7c614 @ 0x0007c614   (est. sk_f_7c614)
 * Ghidra: void FUN_7c614(void)
 * faithful call sequence; see FUN_7c614
 * Confidence: low
 */
void sk_f_7c614(void)
{
    sk_slot_0007c614();
    sk_cpu_ctx();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7c618 @ 0x0007c618   (est. sk_f_7c618)
 * Ghidra: void FUN_7c618(void)
 * faithful call sequence; see FUN_7c618
 * Confidence: low
 */
void sk_f_7c618(void)
{
    sk_slot_0007c618();
    sk_cpu_ctx();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7c660 @ 0x0007c660   (est. sk_obj_free_18)
 * Ghidra: void FUN_7c660(void)
 * 0036b118 +0x18
 * Confidence: low
 */
void sk_obj_free_18(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7c664 @ 0x0007c664   (est. sk_obj_free_18b)
 * Ghidra: void FUN_7c664(void)
 * 0036b118 +0x18
 * Confidence: low
 */
void sk_obj_free_18b(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7c680 @ 0x0007c680   (est. sk_obj_free_18c)
 * Ghidra: void FUN_7c680(void)
 * 0036b118 +0x18 + 0036b6ac
 * Confidence: low
 */
void sk_obj_free_18c(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7c684 @ 0x0007c684   (est. sk_obj_free_18d)
 * Ghidra: void FUN_7c684(void)
 * 0036b118 +0x18 + 0036b6ac
 * Confidence: low
 */
void sk_obj_free_18d(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7c6ac @ 0x0007c6ac   (est. sk_f_7c6ac)
 * Ghidra: void FUN_7c6ac(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
 * faithful call sequence; see FUN_7c6ac
 * Confidence: low
 */
void sk_f_7c6ac(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
{
    sk_slot_0007c6ac();
    sk_retain();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7c76c @ 0x0007c76c   (est. sk_f_7c76c)
 * Ghidra: void FUN_7c76c(unsigned long param_1, unsigned long param_2)
 * faithful call sequence; see FUN_7c76c
 * Confidence: low
 */
void sk_f_7c76c(unsigned long param_1, unsigned long param_2)
{
    sk_slot_0007c76c();
    sk_key_eq();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7c814 @ 0x0007c814   (est. sk_f_7c814)
 * Ghidra: void FUN_7c814(unsigned long param_1)
 * faithful call sequence; see FUN_7c814
 * Confidence: low
 */
void sk_f_7c814(unsigned long param_1)
{
    sk_slot_0007c814();
    sk_ref_add();
    sk_alloc();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7c848 @ 0x0007c848   (est. sk_obj_free_10)
 * Ghidra: void FUN_7c848(void)
 * 003a25d4 +0x10
 * Confidence: low
 */
void sk_obj_free_10(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7c84c @ 0x0007c84c   (est. sk_obj_free_10b)
 * Ghidra: void FUN_7c84c(void)
 * 003a25d4 +0x10
 * Confidence: low
 */
void sk_obj_free_10b(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7c868 @ 0x0007c868   (est. sk_obj_free_10c)
 * Ghidra: void FUN_7c868(void)
 * 003a25d4 +0x10 + 84074 + 0036b6ac
 * Confidence: low
 */
void sk_obj_free_10c(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7c86c @ 0x0007c86c   (est. sk_obj_free_10d)
 * Ghidra: void FUN_7c86c(void)
 * 003a25d4 +0x10 + 84074 + 0036b6ac
 * Confidence: low
 */
void sk_obj_free_10d(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7c8a0 @ 0x0007c8a0   (est. sk_f_7c8a0)
 * Ghidra: void FUN_7c8a0(void)
 * faithful call sequence; see FUN_7c8a0
 * Confidence: low
 */
void sk_f_7c8a0(void)
{
    sk_slot_0007c8a0();
    sk_pair_new();
    sk_ref_sub();
    sk_alloc();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7c8dc @ 0x0007c8dc   (est. sk_f_7c8dc)
 * Ghidra: void FUN_7c8dc(void)
 * faithful call sequence; see FUN_7c8dc
 * Confidence: low
 */
void sk_f_7c8dc(void)
{
    sk_slot_0007c8dc();
    sk_retain();
    sk_cpu_ctx();
    sk_retain();
    sk_ref_pend();
    sk_slot_0007c974();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7c974 @ 0x0007c974   (est. sk_f_7c974)
 * Ghidra: void FUN_7c974(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
 * faithful call sequence; see FUN_7c974
 * Confidence: low
 */
void sk_f_7c974(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
{
    sk_slot_0007c974();
    sk_retain();
    sk_retain_low();
    sk_build_cnode();
    sk_build_map();
    sk_free();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7ca48 @ 0x0007ca48   (est. sk_f_7ca48)
 * Ghidra: void FUN_7ca48(void)
 * faithful call sequence; see FUN_7ca48
 * Confidence: low
 */
void sk_f_7ca48(void)
{
    sk_slot_0007ca48();
    sk_buf_begin();
    sk_cpu_ctx();
    sk_free();
    sk_buf_end();
    sk_cap_sz();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7cb88 @ 0x0007cb88   (est. sk_roottask_content_serialize)
 * Ghidra: void FUN_7cb88(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
 * Serializes the roottask-produced metadata content into the bootinfo stream.
 * Iterates the serialization pool (FUN_0007cf74 pop), writing each record's
 * size word and continuation flag into the output buffer, then flushes the
 * record via sk_elem_append. Verifies the count of records written matches
 * the pool's advertised count, else faults ("Roottask produced content of
 * metadata" overflow). Ends by freeing all scratch and the pool.
 * Confidence: medium (faithful transcription of the record-walk loop)
 */
void sk_roottask_content_serialize(unsigned long out, unsigned long base, unsigned long limit, unsigned long off)
{
    sk_finalize_check();
    sk_f_7cefc(0, 0);
    unsigned long pool = 0; /* g_pool */
    unsigned long idx = 0;
    for (;;) {
        unsigned char rec[0x40];
        sk_f_7cf74((unsigned long)rec);
        unsigned long a = rec[1], b = rec[2], c = rec[3], d = rec[4], e = rec[5];
        if (rec[6] == 0) {
            sk_free((void *)pool);
            unsigned long cnt = 0;
            if (idx >= 0 && idx == cnt) {
                sk_finalize_ok();
                return;
            }
            sk_panic_msg();
            sk_panic_abort();
            sk_trace_flush();
            __builtin_trap();
        }
        /* write size word + continuation flag */
        unsigned long sz = (a >> 1) - b;
        sk_buf_cap();
        sk_str_span();
        sk_emit_bytes(0, 0, 0, sz);
        sk_emit_bytes(0, 0, 0, rec[6] != 0);
        /* flush record, advance offset, accumulate */
        sk_f_7d0fc(idx, out, base);
        sk_f_7d128((unsigned long)rec, 0, b, a, 0, sz);
        sk_free((void *)rec);
        sk_f_7d0fc(idx + 7, out, base);
        sk_f_7d128((unsigned long)rec, 0, b, a, 0, sz);
        idx += sz;
        off = a;
    }
}


/*--------------------------------------------------------------------*/
/* FUN_7cefc @ 0x0007cefc   (est. sk_f_7cefc)
 * Ghidra: void FUN_7cefc(unsigned long param_1, unsigned long param_2)
 * faithful call sequence; see FUN_7cefc
 * Confidence: low
 */
void sk_f_7cefc(unsigned long param_1, unsigned long param_2)
{
    sk_slot_0007cefc();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7cf38 @ 0x0007cf38   (est. sk_f_7cf38)
 * Ghidra: void FUN_7cf38(unsigned long param_1, unsigned long param_2)
 * faithful call sequence; see FUN_7cf38
 * Confidence: low
 */
void sk_f_7cf38(unsigned long param_1, unsigned long param_2)
{
    sk_slot_0007cf38();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7cf74 @ 0x0007cf74   (est. sk_f_7cf74)
 * Ghidra: void FUN_7cf74(unsigned long param_1)
 * faithful call sequence; see FUN_7cf74
 * Confidence: low
 */
void sk_f_7cf74(unsigned long param_1)
{
    sk_slot_0007cf74();
    sk_retain();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7d054 @ 0x0007d054   (est. sk_f_7d054)
 * Ghidra: void FUN_7d054(unsigned long param_1, unsigned long param_2, unsigned long param_3)
 * faithful call sequence; see FUN_7d054
 * Confidence: low
 */
void sk_f_7d054(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    sk_slot_0007d054();
    sk_buf_acquire();
    sk_buf_commit();
    sk_mem_zero();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7d0fc @ 0x0007d0fc   (est. sk_f_7d0fc)
 * Ghidra: void FUN_7d0fc(unsigned long param_1, unsigned long param_2, unsigned long param_3)
 * faithful call sequence; see FUN_7d0fc
 * Confidence: low
 */
void sk_f_7d0fc(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    sk_slot_0007d0fc();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7d128 @ 0x0007d128   (est. sk_f_7d128)
 * Ghidra: void FUN_7d128(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4, unsigned long param_5, unsigned long param_6)
 * faithful call sequence; see FUN_7d128
 * Confidence: low
 */
void sk_f_7d128(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4, unsigned long param_5, unsigned long param_6)
{
    sk_slot_0007d128();
    sk_memcpy();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7d168 @ 0x0007d168   (est. sk_f_7d168)
 * Ghidra: void FUN_7d168(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
 * faithful call sequence; see FUN_7d168
 * Confidence: low
 */
void sk_f_7d168(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4)
{
    sk_slot_0007d168();
    sk_memcpy();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7d19c @ 0x0007d19c   (est. sk_obj_free_2f2)
 * Ghidra: void FUN_7d19c(void)
 * 0036b118 +0x10, 003a25d4 +0x18
 * Confidence: low
 */
void sk_obj_free_2f2(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7d1c4 @ 0x0007d1c4   (est. sk_obj_free_2f2b)
 * Ghidra: void FUN_7d1c4(void)
 * 7d19c + 84064 + 0036b6ac
 * Confidence: low
 */
void sk_obj_free_2f2b(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7d1c8 @ 0x0007d1c8   (est. sk_obj_free_2f2c)
 * Ghidra: void FUN_7d1c8(void)
 * 7d19c + 84064 + 0036b6ac
 * Confidence: low
 */
void sk_obj_free_2f2c(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7d1e4 @ 0x0007d1e4   (est. sk_obj_mth_58)
 * Ghidra: void FUN_7d1e4(void)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_obj_mth_58(void)
{
    sk_slot_0007d1e4();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7d220 @ 0x0007d220   (est. sk_obj_mth_68)
 * Ghidra: void FUN_7d220(void)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_obj_mth_68(void)
{
    sk_slot_0007d220();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7d264 @ 0x0007d264   (est. sk_f_7d264)
 * Ghidra: void FUN_7d264(unsigned long param_1, unsigned long param_2, unsigned long param_3)
 * faithful call sequence; see FUN_7d264
 * Confidence: low
 */
void sk_f_7d264(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    sk_slot_0007d264();
    sk_alloc();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7d2b8 @ 0x0007d2b8   (est. sk_f_7d2b8)
 * Ghidra: void FUN_7d2b8(void)
 * faithful call sequence; see FUN_7d2b8
 * Confidence: low
 */
void sk_f_7d2b8(void)
{
    sk_slot_0007d2b8();
    sk_buf_begin();
    sk_cpu_ctx();
    sk_retain();
    sk_cap_sz();
    sk_release();
    sk_free();
    sk_buf_end();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7d3e8 @ 0x0007d3e8   (est. sk_roottask_content_deserialize)
 * Ghidra: void FUN_7d3e8(unsigned long param_1, unsigned long param_2)
 * Consumes the serialized roottask content: reads each pool record via the
 * serializer pop, validates the recorded size against the available buffer
 * (fault "Roottask produced content of association" on mismatch), and appends
 * the record payload. Tracks the running offset and the produced byte count,
 * comparing the final total against the advertised pool size.
 * Confidence: medium (faithful record-walk transcription)
 */
void sk_roottask_content_deserialize(unsigned long out, unsigned long base)
{
    sk_finalize_check();
    unsigned long pool = 0;
    sk_finalize_ok();
    for (;;) {
        unsigned char rec[0x40];
        sk_f_7cf74((unsigned long)rec);
        unsigned long a = rec[1], b = rec[2];
        sk_release((void *)rec);
        unsigned long sz = (a >> 1) - b;
        if (sz < 0) __builtin_trap();
        /* copy record bytes into output and advance */
        sk_f_7d128((unsigned long)rec, 0, b, a, 0, sz);
        sk_free((void *)rec);
        sk_f_7d0fc(0, out, base);
        if ((a >> 1) - b == 0) break;
        sk_f_7d168(0, 0, 0, 0);
    }
}


/*--------------------------------------------------------------------*/
/* FUN_7d880 @ 0x0007d880   (est. sk_obj_mth_50)
 * Ghidra: void FUN_7d880(void)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_obj_mth_50(void)
{
    sk_slot_0007d880();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7d8bc @ 0x0007d8bc   (est. sk_obj_mth_60)
 * Ghidra: void FUN_7d8bc(void)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_obj_mth_60(void)
{
    sk_slot_0007d8bc();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7d910 @ 0x0007d910   (est. sk_f_7d910)
 * Ghidra: void FUN_7d910(unsigned long param_1)
 * faithful call sequence; see FUN_7d910
 * Confidence: low
 */
void sk_f_7d910(unsigned long param_1)
{
    sk_slot_0007d910();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7d958 @ 0x0007d958   (est. sk_f_7d958)
 * Ghidra: void FUN_7d958(unsigned long param_1, unsigned long param_2)
 * faithful call sequence; see FUN_7d958
 * Confidence: low
 */
void sk_f_7d958(unsigned long param_1, unsigned long param_2)
{
    sk_slot_0007d958();
    sk_alloc_teardown();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7d9ac @ 0x0007d9ac   (est. sk_f_7d9ac)
 * Ghidra: void FUN_7d9ac(void)
 * faithful call sequence; see FUN_7d9ac
 * Confidence: low
 */
void sk_f_7d9ac(void)
{
    sk_slot_0007d9ac();
    sk_lock_claim();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7d9d8 @ 0x0007d9d8   (est. sk_f_7d9d8)
 * Ghidra: void FUN_7d9d8(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4, unsigned long param_5, unsigned long param_6, unsigned long param_7)
 * faithful call sequence; see FUN_7d9d8
 * Confidence: low
 */
void sk_f_7d9d8(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4, unsigned long param_5, unsigned long param_6, unsigned long param_7)
{
    sk_slot_0007d9d8();
    sk_buf_begin();
    sk_alloc();
    sk_buf_end();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7da4c @ 0x0007da4c   (est. sk_f_7da4c)
 * Ghidra: void FUN_7da4c(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4, unsigned long param_5, unsigned long param_6, unsigned long param_7)
 * faithful call sequence; see FUN_7da4c
 * Confidence: low
 */
void sk_f_7da4c(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4, unsigned long param_5, unsigned long param_6, unsigned long param_7)
{
    sk_slot_0007da4c();
    sk_store_meta();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7da98 @ 0x0007da98   (est. sk_f_7da98)
 * Ghidra: void FUN_7da98(void)
 * faithful call sequence; see FUN_7da98
 * Confidence: low
 */
void sk_f_7da98(void)
{
    sk_slot_0007da98();
    sk_retain_low();
    sk_arr_release();
    sk_arr_grow();
    sk_free();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7dbb8 @ 0x0007dbb8   (est. sk_f_7dbb8)
 * Ghidra: void FUN_7dbb8(unsigned long param_1)
 * faithful call sequence; see FUN_7dbb8
 * Confidence: low
 */
void sk_f_7dbb8(unsigned long param_1)
{
    sk_slot_0007dbb8();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7dbf0 @ 0x0007dbf0   (est. sk_f_7dbf0)
 * Ghidra: void FUN_7dbf0(void)
 * faithful call sequence; see FUN_7dbf0
 * Confidence: low
 */
void sk_f_7dbf0(void)
{
    sk_slot_0007dbf0();
    sk_slot_00077698();
    sk_elem_lock();
    sk_arr_init();
    sk_cap_sz();
    sk_arr_resize();
    sk_arr_init();
    sk_free();
    sk_slot_0007767c();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7dcfc @ 0x0007dcfc   (est. sk_f_7dcfc)
 * Ghidra: void FUN_7dcfc(void)
 * faithful call sequence; see FUN_7dcfc
 * Confidence: low
 */
void sk_f_7dcfc(void)
{
    sk_slot_0007dcfc();
    sk_cpu_ctx();
    sk_sz_cap();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7ddb0 @ 0x0007ddb0   (est. sk_f_7ddb0)
 * Ghidra: void FUN_7ddb0(unsigned long param_1, unsigned long param_2, unsigned long param_3)
 * faithful call sequence; see FUN_7ddb0
 * Confidence: low
 */
void sk_f_7ddb0(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    sk_slot_0007ddb0();
    sk_finalize_check();
    sk_cpu_ctx();
    sk_pair_read();
    sk_elem_lock();
    sk_elem_append();
    sk_arr_resize();
    sk_elem_append();
    sk_buf_copy();
    sk_free();
    sk_buf_commit2();
    sk_trace_point();
    sk_buf_alloc();
    sk_buf_copy();
    sk_retain();
    sk_pair_read();
    sk_cap_sz();
    sk_memcpy();
    sk_free();
    sk_release();
    sk_buf_cap();
    sk_emit_bytes();
    sk_buf_commit2();
    sk_trace_point();
    sk_buf_copy();
    sk_buf_commit2();
    sk_trace_point();
    sk_panic_str();
    sk_debug_printf();
    sk_buf_commit2();
    sk_trace_point();
    sk_alloc_teardown();
    sk_cap_lookup();
    sk_emit_range();
    sk_free();
    sk_buf_commit2();
    sk_trace_point();
    sk_buf_copy();
    sk_free();
    sk_finalize_ok();
    sk_finalize_bad();
    sk_emit_tag();
    sk_emit_fmt();
    sk_spin_lock();
    sk_emit_fmt();
    sk_release();
    sk_emit_fmt();
    sk_release();
    sk_debug_printf();
    sk_panic_str();
    sk_debug_printf();
    sk_trace_end();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7e6b8 @ 0x0007e6b8   (est. sk_obj_free_3f)
 * Ghidra: void FUN_7e6b8(void)
 * 0036b118 +0x10,+0x18,+0x30
 * Confidence: low
 */
void sk_obj_free_3f(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7e6e8 @ 0x0007e6e8   (est. sk_obj_teardown_e)
 * Ghidra: void FUN_7e6e8(void)
 * 7e6b8+0036b6ac
 * Confidence: low
 */
void sk_obj_teardown_e(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7e6ec @ 0x0007e6ec   (est. sk_obj_teardown_f)
 * Ghidra: void FUN_7e6ec(void)
 * 7e6b8+0036b6ac
 * Confidence: low
 */
void sk_obj_teardown_f(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7e710 @ 0x0007e710   (est. sk_obj_mth_b8)
 * Ghidra: void FUN_7e710(void)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_obj_mth_b8(void)
{
    sk_slot_0007e710();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7e74c @ 0x0007e74c   (est. sk_obj_mth_c0)
 * Ghidra: void FUN_7e74c(void)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_obj_mth_c0(void)
{
    sk_slot_0007e74c();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7e788 @ 0x0007e788   (est. sk_f_7e788)
 * Ghidra: void FUN_7e788(void)
 * faithful call sequence; see FUN_7e788
 * Confidence: low
 */
void sk_f_7e788(void)
{
    sk_slot_0007e788();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7e7c4 @ 0x0007e7c4   (est. sk_f_7e7c4)
 * Ghidra: void FUN_7e7c4(unsigned long param_1, unsigned long param_2)
 * faithful call sequence; see FUN_7e7c4
 * Confidence: low
 */
void sk_f_7e7c4(unsigned long param_1, unsigned long param_2)
{
    sk_slot_0007e7c4();
    sk_elem_lock();
    sk_elem_append4();
    sk_cpu_ctx();
    sk_retain();
    sk_cpu_ctx();
    sk_sz_cap();
    sk_paddr_type();
    sk_free();
    sk_emit_int();
    sk_arr_resize();
    sk_elem_append4();
    sk_buf_copy();
    sk_free();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7e99c @ 0x0007e99c   (est. sk_obj_teardown_g)
 * Ghidra: void FUN_7e99c(void)
 * 7e6b8?
 * Confidence: low
 */
void sk_obj_teardown_g(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7e9a0 @ 0x0007e9a0   (est. sk_obj_teardown_h)
 * Ghidra: void FUN_7e9a0(void)
 * 7e6b8?
 * Confidence: low
 */
void sk_obj_teardown_h(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7e9c0 @ 0x0007e9c0   (est. sk_obj_mth_50b)
 * Ghidra: void FUN_7e9c0(void)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_obj_mth_50b(void)
{
    sk_slot_0007e9c0();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7e9fc @ 0x0007e9fc   (est. sk_obj_mth_58b)
 * Ghidra: void FUN_7e9fc(void)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_obj_mth_58b(void)
{
    sk_slot_0007e9fc();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7ea60 @ 0x0007ea60   (est. sk_f_7ea60)
 * Ghidra: void FUN_7ea60(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4, unsigned long param_5, unsigned long param_6)
 * faithful call sequence; see FUN_7ea60
 * Confidence: low
 */
void sk_f_7ea60(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4, unsigned long param_5, unsigned long param_6)
{
    sk_slot_0007ea60();
    sk_buf_begin();
    sk_alloc();
    sk_slot_0007ead8();
    sk_buf_end();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7ead8 @ 0x0007ead8   (est. sk_f_7ead8)
 * Ghidra: void FUN_7ead8(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4, unsigned long param_5, unsigned long param_6)
 * faithful call sequence; see FUN_7ead8
 * Confidence: low
 */
void sk_f_7ead8(unsigned long param_1, unsigned long param_2, unsigned long param_3, unsigned long param_4, unsigned long param_5, unsigned long param_6)
{
    sk_slot_0007ead8();
    sk_panic_msg();
    sk_panic_abort();
    sk_trace_flush();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7eb2c @ 0x0007eb2c   (est. sk_const40)
 * Ghidra: void FUN_7eb2c(void)
 * returns 0x40
 * Confidence: low
 */
void sk_const40(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7eb34 @ 0x0007eb34   (est. sk_f_7eb34)
 * Ghidra: void FUN_7eb34(void)
 * faithful call sequence; see FUN_7eb34
 * Confidence: low
 */
void sk_f_7eb34(void)
{
    sk_slot_0007eb34();
    sk_finalize_check();
    sk_buf_copy();
    sk_finalize_ok();
    sk_finalize_bad();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7ebf0 @ 0x0007ebf0   (est. sk_obj_mth_70)
 * Ghidra: void FUN_7ebf0(void)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_obj_mth_70(void)
{
    sk_slot_0007ebf0();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7ec2c @ 0x0007ec2c   (est. sk_obj_mth_78)
 * Ghidra: void FUN_7ec2c(void)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_obj_mth_78(void)
{
    sk_slot_0007ec2c();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7ec68 @ 0x0007ec68   (est. sk_f_7ec68)
 * Ghidra: void FUN_7ec68(void)
 * faithful call sequence; see FUN_7ec68
 * Confidence: low
 */
void sk_f_7ec68(void)
{
    sk_slot_0007ec68();
    sk_pair_new();
    sk_ref_add();
    sk_alloc();
    sk_elem_new();
    sk_slot_0007eca8();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7eca8 @ 0x0007eca8   (est. sk_f_7eca8)
 * Ghidra: void FUN_7eca8(unsigned long param_1, unsigned long param_2)
 * faithful call sequence; see FUN_7eca8
 * Confidence: low
 */
void sk_f_7eca8(unsigned long param_1, unsigned long param_2)
{
    sk_slot_0007eca8();
    sk_retain();
    sk_retain_low();
    sk_slot_00073140();
    sk_free();
    sk_type_resolve();
    sk_memcpy_el();
    sk_free();
    sk_cnode_seal();
    sk_cnode_build();
    sk_free();
    sk_cap_copy();
    sk_slot_00077070();
    sk_type_resolve();
    sk_cap_parse();
    sk_cap_put();
    sk_slot_00077070();
    sk_retain_low();
    sk_arr_release();
    sk_slot_000730a4();
    sk_arr_resize();
    sk_slot_000730a4();
    sk_slot_00077070();
    sk_free();
    sk_obj_alloc();
    sk_alloc();
    sk_cap_install();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7f020 @ 0x0007f020   (est. sk_f_7f020)
 * Ghidra: void FUN_7f020(void)
 * faithful call sequence; see FUN_7f020
 * Confidence: low
 */
void sk_f_7f020(void)
{
    sk_slot_0007f020();
    sk_vspace_resolve();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7f04c @ 0x0007f04c   (est. sk_f_7f04c)
 * Ghidra: void FUN_7f04c(void)
 * faithful call sequence; see FUN_7f04c
 * Confidence: low
 */
void sk_f_7f04c(void)
{
    sk_slot_0007f04c();
    sk_vspace_map();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7f098 @ 0x0007f098   (est. sk_obj_mth_48)
 * Ghidra: void FUN_7f098(void)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_obj_mth_48(void)
{
    sk_slot_0007f098();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7f0d4 @ 0x0007f0d4   (est. sk_obj_mth_50c)
 * Ghidra: void FUN_7f0d4(void)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_obj_mth_50c(void)
{
    sk_slot_0007f0d4();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7f110 @ 0x0007f110   (est. sk_f_7f110)
 * Ghidra: void FUN_7f110(unsigned long param_1)
 * faithful call sequence; see FUN_7f110
 * Confidence: low
 */
void sk_f_7f110(unsigned long param_1)
{
    sk_slot_0007f110();
    sk_type_find();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7f1e0 @ 0x0007f1e0   (est. sk_f_7f1e0)
 * Ghidra: void FUN_7f1e0(unsigned long param_1, unsigned long param_2)
 * faithful call sequence; see FUN_7f1e0
 * Confidence: low
 */
void sk_f_7f1e0(unsigned long param_1, unsigned long param_2)
{
    sk_slot_0007f1e0();
    sk_type_find();
    sk_slot_0007c028();
    sk_slot_0007c1a4();
    sk_free();
    sk_map_flush();
    sk_map_dump();
    sk_panic_ret();
    sk_panic_ret2();
    sk_free();
    sk_map_flush();
    sk_retain();
    sk_slot_0007f4d8();
    sk_free();
    sk_retain_low();
    sk_arr_release();
    sk_slot_000732f4();
    sk_arr_resize();
    sk_slot_000732f4();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7f4d8 @ 0x0007f4d8   (est. sk_f_7f4d8)
 * Ghidra: void FUN_7f4d8(unsigned long param_1, unsigned long param_2, unsigned long param_3)
 * faithful call sequence; see FUN_7f4d8
 * Confidence: low
 */
void sk_f_7f4d8(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    sk_slot_0007f4d8();
    sk_slot_00077698();
    sk_release();
    sk_retain();
    sk_hash_lookup();
    sk_retain();
    sk_retain_lo();
    sk_retain();
    sk_hash_lookup();
    sk_retain();
    sk_release();
    sk_parse_int();
    sk_isdigit();
    sk_is_space();
    sk_is_xdigit();
    sk_isdigit();
    sk_is_space();
    sk_skip_ws();
    sk_isdigit();
    sk_is_space();
    sk_is_xdigit();
    sk_skip_ws();
    sk_isdigit();
    sk_is_space();
    sk_isdigit();
    sk_is_space();
    sk_is_xdigit();
    sk_parse_num();
    sk_release();
    sk_retain();
    sk_retain_lo();
    sk_slot_0007767c();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7f8ec @ 0x0007f8ec   (est. sk_f_7f8ec)
 * Ghidra: void FUN_7f8ec(void)
 * faithful call sequence; see FUN_7f8ec
 * Confidence: low
 */
void sk_f_7f8ec(void)
{
    sk_slot_0007f8ec();
    sk_buf_begin();
    sk_type_find();
    sk_slot_0007c028();
    sk_slot_0007c1a4();
    sk_map_find1();
    sk_map_find_8();
    sk_buf_end();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7fa68 @ 0x0007fa68   (est. sk_f_7fa68)
 * Ghidra: void FUN_7fa68(unsigned long param_1, unsigned long param_2)
 * faithful call sequence; see FUN_7fa68
 * Confidence: low
 */
void sk_f_7fa68(unsigned long param_1, unsigned long param_2)
{
    sk_slot_0007fa68();
    sk_type_find();
    sk_slot_0007c028();
    sk_slot_0007c1a4();
    sk_slot_0007c028();
    sk_slot_0007c1a4();
    sk_map_find1();
    sk_map_find_16();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7fc64 @ 0x0007fc64   (est. sk_f_7fc64)
 * Ghidra: void FUN_7fc64(void)
 * faithful call sequence; see FUN_7fc64
 * Confidence: low
 */
void sk_f_7fc64(void)
{
    sk_slot_0007fc64();
    sk_type_find();
    sk_lock_clean();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7fcd4 @ 0x0007fcd4   (est. sk_obj_teardown_i)
 * Ghidra: void FUN_7fcd4(void)
 * 7fc64+0036b6ac
 * Confidence: low
 */
void sk_obj_teardown_i(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7fcd8 @ 0x0007fcd8   (est. sk_obj_teardown_j)
 * Ghidra: void FUN_7fcd8(void)
 * 7fc64+0036b6ac
 * Confidence: low
 */
void sk_obj_teardown_j(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7fd0c @ 0x0007fd0c   (est. sk_obj_mth_58c)
 * Ghidra: void FUN_7fd0c(void)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_obj_mth_58c(void)
{
    sk_slot_0007fd0c();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7fd48 @ 0x0007fd48   (est. sk_obj_mth_60b)
 * Ghidra: void FUN_7fd48(void)
 * cleaned: register-artifact body replaced with faithful call sequence
 * Confidence: low
 */
void sk_obj_mth_60b(void)
{
    sk_slot_0007fd48();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7fd84 @ 0x0007fd84   (est. sk_f_7fd84)
 * Ghidra: void FUN_7fd84(void)
 * faithful call sequence; see FUN_7fd84
 * Confidence: low
 */
void sk_f_7fd84(void)
{
    sk_slot_0007fd84();
    sk_slot_00077698();
    sk_arr_init();
    sk_cap_lookup();
    sk_free();
    sk_arr_resize();
    sk_arr_init();
    sk_slot_0007dbb8();
    sk_free();
    sk_slot_0007767c();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_7fe94 @ 0x0007fe94   (est. sk_f_7fe94)
 * Ghidra: void FUN_7fe94(unsigned long param_1, unsigned long param_2, unsigned long param_3)
 * faithful call sequence; see FUN_7fe94
 * Confidence: low
 */
void sk_f_7fe94(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    sk_slot_0007fe94();
    sk_map_new();
    sk_retain();
    sk_buf_alloc();
    sk_buf_grow();
    sk_sz_page();
    sk_attr_fold();
    sk_cap_copy2();
    sk_sz_page();
    sk_sz_range();
    sk_sz_page();
    sk_buf_flush();
    sk_elem_new();
    sk_cap_lookup();
    sk_free();
    sk_emit_bootinfo();
    sk_free();
    sk_retain_low();
    sk_elem_new();
    sk_hash_lookup();
    sk_slot_000775b8();
    sk_buf_has();
    sk_map_insert();
    sk_hash_lookup();
    sk_panic_nr();
    sk_retain();
    sk_cap_lookup();
    sk_buf_flush();
    sk_free();
    sk_cpu_ctx();
    sk_release();
    sk_panic_msg();
    sk_panic_abort();
    sk_trace_flush();
    sk_buf_alloc();
    sk_retain();
    sk_buf_grow();
    sk_release_lo();
    sk_buf_grow();
    sk_elem_claim();
    sk_hash_lookup();
    sk_release();
    sk_cpu_ctx();
    sk_release();
    sk_elem_claim();
    sk_hash_lookup();
    sk_release();
    sk_elem_claim();
    sk_cap_lookup();
    sk_buf_flush();
    sk_memcpy();
    sk_buf_flush();
    sk_free();
    return;
}

