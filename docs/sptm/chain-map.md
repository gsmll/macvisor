# ring −1 call-graph map (SPTM / TXM / Secure Kernel)

Call-graph edges discovered while decompiling. Append with both addresses:
`FUN_0009c2c8 (sptm_map_page) → FUN_0009d000 (sptm_retype)`.

## Entry surfaces (to map)

- GENTER entry stub + guarded-level dispatch (x16 selector decode)
- SPTM exception vectors (SPTM_VECTOR_IRQ/FIQ/SERROR/SYNC)
- SPTMArgs bootstrap (SPTM runs before XNU)
- Dispatch tables: XNU_BOOTSTRAP, TXM_BOOTSTRAP, SK_BOOTSTRAP, DART/SART/NVME/UAT/SHART/HIB

## Boot / entry / dispatch edges (boot/entry/dispatch batch)

- FUN_ab000 (sptm_main) → FUN_ab7bc (sptm_el2_setup)  [0xab698 `bl 0xab7bc`]
- FUN_ab000 (sptm_main) → FUN_ab8ac (sptm_genter_receive)  [0xab6a8 `bl 0xab8ac`]
- FUN_ab000 (sptm_main) installs VBAR_EL1 = 0xa9000 (sptm_vectors_boot)
- FUN_9c000 (sptm_per_cpu_bootstrap) → FUN_e7d78 (el1 boot finish)  [0x9c198 `bl 0xe7d78`]
- FUN_9c000 (sptm_per_cpu_bootstrap) → FUN_aba70 (per-cpu finish tail)  [0x9c2bc `bl 0xaba70`]
- FUN_9c000 (sptm_per_cpu_bootstrap) installs VBAR_EL1 = 0x9d000 (sptm_vectors_percpu)
- sptm_vectors_percpu (slot) → FUN_9c2dc (sptm_vector_context_save)  [each slot `bl 0x9c2dc`]
- FUN_9c2dc (sptm_vector_context_save) → FUN_ed340 (sptm_exception_dispatch)  [0x9c3c0 `b 0xed340`]
- FUN_a0f7c (sptm_txm_sk_entry) → FUN_e6bc0 (sptm_dispatch_engine)  [event 3]
- FUN_a111c (sptm_sk_entry) → FUN_e6bc0 (sptm_dispatch_engine)  [event 4]
- FUN_b8f84 (sptm_init) → FUN_ab8ac (sptm_genter_receive)  [`FUN_ab8ac(&DAT_00106180)`]
- FUN_b8f84 (sptm_init) → FUN_ab7bc (sptm_el2_setup)  [`FUN_ab7bc()`]
- FUN_e6bc0 (sptm_dispatch_transition) — central state-transition dispatcher; reads table @0x16770 = state*0x1e0 + event*0x20; validates via FUN_e7068 (sptm_dispatch_validate_state) + FUN_e70b4 (sptm_dispatch_validate_event); jumps to target handler (indirect). This is the guarded GENTER/GEXIT boundary (selector in x16).
- FUN_e74e0 (sptm_dispatch_route) → FUN_e6bc0  [derives event 0x2/0x3/0x4/0xc/0xd/0xe from selector]
- dispatch handlers (batch 0xa0000..0xa2b50) → FUN_e6bc0, e.g.:
  - FUN_a0298 / FUN_a0360 → FUN_e6bc0 [event 5]
  - FUN_a0594 → FUN_e6bc0 [event 0xb]
  - FUN_a05dc → FUN_f89b4 (sptm_invalid_genter_panic)  [noreturn]
  - FUN_a0abc → FUN_e74e0 (sptm_dispatch_route)
  - FUN_a2318 / FUN_a2458 → FUN_e6bc0 [event 2]
  - FUN_a235c → FUN_e6bc0 [event 7, flag (p3&1)<<2|2]
  - FUN_a2530 → FUN_e6bc0 [event 7, arg 1]
  - FUN_a259c → FUN_e6bc0 [event 5]
  - FUN_a249c → FUN_e6bc0 [event 5] (also writes EL1 dbg regs)
- FUN_e7100 (sptm_exception_vector_dispatch) → FUN_a0adc (sptm_exception_return)  [validates vector_type<=3, xnu_el2_exception_vector, xnu_exc_return_handler first]
- FUN_a0adc (sptm_exception_return) → FUN_e7c30 (sptm_stage2_state_save)  [mode==2 path]
- FUN_a1318 (sptm_exception_return_el0) → FUN_e78dc (sptm_debug_state_restore)
- FUN_a21b4 / FUN_a2718 / FUN_a28d4 → FUN_e7678 (sptm_dispatch_name) → FUN_f8804 (sptm_panic_str)  [noreturn panic]
- FUN_a1374 (sptm_guest_exit_handoff) → FUN_d8a58 (sptm_papt_to_phys)  [resolve exit PC]
- FUN_b2620..b2698 (SPTM->TXM stubs) → FUN_a0f7c (sptm_txm_sk_entry)  [6 call sites]

## trace-hib (SPTM CPU-trace + hibernation) — TraceHib

- FUN_000bc6f0 (sptm_cputrace_va_stop) → FUN_000bc75c (sptm_cputrace_state_code), FUN_000f8844 (sptm_panic)
- FUN_000bc78c (sptm_cputrace_va_start) → FUN_000bc75c, FUN_000f8844
- FUN_000bc7fc (sptm_cputrace_va_set_base) → FUN_000bc75c, FUN_000f8844, FUN_000f8804 (sptm_panic_assert)
- FUN_000bcbb0 (sptm_cputrace_va_deinit) → FUN_000bc75c, FUN_000f8844, FUN_000f8804
- FUN_000bcea0 (sptm_cputrace_va_init) → FUN_000bc75c, FUN_000f8844, FUN_000f8804
- FUN_000bd57c (sptm_cputrace_va_frame_lock) → FUN_000f7d60 (validate_trace_request), FUN_000d8a58 (sptm_region_handle), FUN_000e2480 (sptm_guard_get), FUN_000e5f8c (sptm_guard_op), FUN_000f8844, FUN_000f8804
- FUN_000bd120 (sptm_cputrace_va_frame_unlock) → FUN_000f7d60, FUN_000d8a58, FUN_000e2480, FUN_000e5f8c, FUN_000f8844, FUN_000f8804
- FUN_000bda44 (sptm_cputrace_stop) → FUN_000bc75c, FUN_000f8844   [unconditional panic]
- FUN_000bdab4 (sptm_cputrace_start) → FUN_000bc75c, FUN_000f8844   [unconditional panic]
- FUN_000bdb04 (sptm_cputrace_set_base) → FUN_000bc75c, FUN_000f8844, FUN_000f8804
- FUN_000bdd48 (validate_sptm_cputrace_mode) → FUN_000f8844

- FUN_000bf9dc (sptm_hib_begin) → FUN_000d617c (sptm_hib_setup), FUN_000ad3b0 (sptm_hib_register_callback), FUN_000ae158 (begin_callback_tail), FUN_000e2480, FUN_000ae8b4 (sptm_sha_reset), FUN_000aeaa4 (sptm_sha_update), FUN_000b25c0 (sptm_sk_hib_start), FUN_000f8844, FUN_000f8804
- FUN_000bffc8 (sptm_hib_hash_hibseg_page) → FUN_000c02bc (sptm_hib_hash_page_internal), FUN_000bf874 (sptm_ace_finalize), FUN_000ae8b4, FUN_000aeaa4, FUN_000f8804
- FUN_000c06ec (sptm_hib_hash_page) → FUN_000c02bc, FUN_000f8844, FUN_000f8804
- FUN_000c0cec (sptm_hib_finalize_sk) → FUN_000b25f0 (sptm_sk_hib_finish), FUN_000abeb0 (sptm_copy_mem), FUN_000ae8b4, FUN_000aeaa4, FUN_000f8804
- FUN_000c0e64 (sptm_hib_finalize_image) → FUN_000aeaa4, FUN_000e40ec (sptm_large_mem_translate), FUN_000bf874, FUN_000f8844, FUN_000f8804
- FUN_000c1128 (sptm_hib_verify_hash_non_wired_page) → FUN_000c02bc, FUN_000f8844, FUN_000f8804
- FUN_000c12a4 (sptm_hib_verify_finalize_non_wired_hash) → FUN_000bf874, FUN_000f8844, FUN_000f8804
- FUN_000f84b4 (hib_sptm_panic_func) → FUN_000f8804

- FUN_000c02bc (sptm_hib_hash_page_internal) → FUN_000e3d7c (sptm_external_desc_lookup), FUN_000e40ec, FUN_000b25d8 (sptm_sk_hib_encrypt), FUN_000abb60 (sptm_scratch_zero), FUN_000abeb0 (sptm_copy_mem), FUN_000aeaa4 (sptm_sha_update), FUN_000e03f4 (zero page), FUN_000e0770 (zero-page alloc), FUN_000e05bc (zero-page release), FUN_000f8804, FUN_000f8844

## Entry-stub / libc helper batch (entry-stubs tree, Wave3b)

- FUN_000b8f84 (sptm_init) → FUN_000ab7bc (sptm_cpu_el2_bringup)  [per-CPU EL2 bring-up]
- FUN_000baa60 → FUN_000ab8dc (sptm_el2_enable)  [vector + SCTLR install]
- FUN_000ab994 (sptm_dcache_flush) → FUN_000ab964 (sptm_dcache_clean_invalidate_range)
- FUN_000aba24 (sptm_icache_invalidate_range) → FUN_000ab958 (sptm_dsb_sy)  [range via x0/x1 passthrough]
- printf family:
  - FUN_000ad278 (sptm_snprintf) → FUN_000ad25c (sptm_vsnprintf) → FUN_000ac524 (sptm_vsnprintf_core)
  - FUN_000ac524 → FUN_000acbac (sptm_buf_putc), FUN_000acc60 (sptm_format_number), FUN_000acf28 (sptm_out_emit), FUN_000ad218 (sptm_va_arg), FUN_000ad1f0/000ad238 (sptm_va_arg_ptr*)
  - FUN_000acc60 → FUN_000acf28, FUN_000ac500 (sptm_panic_fmtstate), FUN_000ad248 (sptm_stack_chk_guard)
  - FUN_000acf28 → FUN_000ad020 (sptm_out_fill), FUN_000ad0e0 (sptm_out_write)
  - FUN_000ad020 → FUN_000abbd0 (sptm_memset_bytes); FUN_000ad0e0 → FUN_000abeb0 (sptm_memcpy_guestio)
  - FUN_000ad218 → FUN_000ace64 (sptm_va_arg_get)
- qsort family:
  - FUN_000ad3b0 (sptm_qsort) → FUN_000ad40c (sptm_qsort_core)
  - FUN_000ad40c → FUN_000addb8 (sptm_qsort_median3), FUN_000adbf0 (sptm_qsort_insertion), FUN_000adf80 (sptm_qsort_swap)
- panic stubs: FUN_000ad278 (sptm_snprintf) → FUN_000ac4e0 (sptm_panic_msg); FUN_000ac4e0 → FUN_000f8824; FUN_000ac500 → FUN_000f8804

## Crypto + fortified-libc helper batch (ringminus1 sptm_helpers tree, Wave3c)
- fortified libc (panic on overflow → FUN_000ac4e0 sptm_panic_msg, string "Security assertion" 0xacd):
  - FUN_000ae158 (sptm_memcpy_chk) → FUN_000abeb0 (sptm_memcpy)  [b 0xabeb0 after cap check]
  - FUN_000ae214 (sptm_memset_s_chk) → FUN_000abbd0 (sptm_memset)  [b 0xae1bc → abbd0]
  - FUN_000ae278 (sptm_strlcpy_chk) → FUN_000ac480 (sptm_strlen) + FUN_000abeb0 (memcpy)
  - FUN_000ae3e0 (sptm_bzero_chk) → FUN_000abb60 (sptm_memset)  [b 0xabb60]
  - FUN_000ae44c (sptm_stack_chk_fail) → FUN_000f8804 (sptm_panic_str)  [noreturn]
  - FUN_000ae3a0 / FUN_000ae424 (panic-arg pushers) → FUN_000ac4e0  [noreturn]
- AES key schedule:
  - FUN_000ae498 (sptm_aes_gcm_keysize) → FUN_000b0a00 (sptm_aes_key_expand)  [dispatch]
  - FUN_000b0a00 → FUN_000b0850 (aes128) / FUN_000b08c0 (aes192) / FUN_000b0950 (aes256)
  - FUN_000b0a70 (sptm_aes_decrypt_keysched) → FUN_000b0a00
- SHA:
  - FUN_000b0d14 (thunk) → FUN_000b17a0 (sptm_sha512_compress)
  - FUN_000b0e30 (sptm_sha256_compress) — K table 0xb0d30
- GHASH / AES-GCM:
  - FUN_000b0cb4 (sptm_ghash_step) → FUN_000b1440 (sptm_ghash_mul)
  - FUN_000b14c0 (sptm_ghash_update) / FUN_000b1140 (sptm_ghash_table_build) → gf(2^128) mul
  - FUN_000afad0 (sptm_aes_gcm_encrypt) — 0x80-byte NEON loop, tag at ctx+0x10/+0x20
  - FUN_000b03b8 (sptm_ct_memcmp) → FUN_000ae5e8 (sptm_barrier_dsb_isb) + FUN_000b0d1c
  - FUN_000b0ad4 (sptm_gcm_finalize_tag) → FUN_000b2204 (gcm_state_advance), FUN_000b0cb4 (ghash_step), FUN_000b03b8 (ct compare), FUN_000abeb0 (memcpy)
  - FUN_000b055c (sptm_gcm_update_encrypt) → FUN_000ae858 (gcm_flush), FUN_000ae928 (chunk_loop), FUN_000abeb0/000abbd0
  - FUN_000b0434 (sptm_gcm_finalize) → indirect block callback [ctx+7]; memcpy 0xabeb0
  - FUN_000ae604 (sptm_gcm_tag_fold) → FUN_000ae3d8 (memset), FUN_000ae150 (memcpy), FUN_000b2584 (block fill)
- barrier wrappers: FUN_000ae5e8 (sptm_barrier_dsb_isb) called by ae8b4/aeaa4/b0504/b07bc/b0d1c

## sptm_pmap core (ringminus1 sptm_pmap tree)

- FUN_000ed6b4 (sptm_retype) → FUN_000f8844 (sptm_violation), FUN_000f8804 (sptm_assert_fail), FUN_000d7348 (sptm_set_pte_attr), FUN_000aba24 (sptm_tlb_flush1), FUN_000e3d7c (sptm_ft_dynamic), FUN_000e40ec (sptm_phys_to_virt)  [per-type ft_pre/ft_retype/ft_update callbacks via DAT_00095dc0/db8/d88]
- FUN_000ee278 (sptm_map_page) → FUN_000eefd4 (sptm_get_current_root), FUN_000ef1f8 (sptm_validate_va), FUN_000e276c (sptm_walk), FUN_000e2480 (sptm_ft_for_paddr), FUN_000e0a10 (sptm_cacheattr), FUN_000b2638 (sptm_user_map), FUN_000e2150 (sptm_tlb_root), FUN_000d76fc (sptm_tlb_op), FUN_000e2e2c (sptm_write_pte), FUN_000d8a58 (sptm_get_parent_paddr)
- FUN_000efa78 (sptm_map_table) → FUN_000eefd4, FUN_000ef1f8, FUN_000e276c, FUN_000e2480/000e3d7c, FUN_000e2c18 (sptm_clear_pte), FUN_000e3394 (sptm_release_table_pair)
- FUN_000f05e4 (sptm_unmap_table) → FUN_000eefd4, FUN_000ef1f8, FUN_000e2150, FUN_000e276c, FUN_000e2480, FUN_000d76fc, FUN_000e3394
- FUN_000f1290 (sptm_surt_alloc) → FUN_000f175c (sptm_surt_ft), FUN_000ae3e0 (sptm_ref_release), FUN_000b2650 (sptm_asid_bind)
- FUN_000f1910 (sptm_surt_free) → FUN_000f175c, FUN_000e1acc (sptm_ref_release2)
- FUN_000f0d50 (sptm_leaf_table_condemn_op) → FUN_000eefd4, FUN_000ef1f8, FUN_000e276c, FUN_000e2480
- FUN_000f1b78 (sptm_region_op) → FUN_000eefd4, FUN_000f2304 (sptm_parse_region), FUN_000e276c, FUN_000e2480, FUN_000d617c (sptm_copyin_handoff), FUN_000e2150, FUN_000d76fc, FUN_000d8a58, FUN_000ae3e0; calls caller preflight/finalize callbacks
- FUN_000f3034 (sptm_update_region) → FUN_000f1b78 (sptm_region_op)
- FUN_000f3144 (sptm_disjoint_op) → FUN_000eefd4, FUN_000ef1f8, FUN_000e2480, FUN_000d617c, FUN_000e276c, FUN_000e233c (sptm_ft_for_pte), FUN_000e2150, FUN_000d76fc, FUN_000d8a58; calls preflight/finalize callbacks
- FUN_000f38c8 (sptm_update_disjoint) → FUN_000f3144 (sptm_disjoint_op)
- FUN_000f3998 (sptm_update_disjoint_multipage) → FUN_000e2480, FUN_000d7348 (sptm_set_pte_attr), FUN_000f3144 (sptm_disjoint_op)
- FUN_000f3f60 (sptm_configure_shared_region) → FUN_000ef8c8 (sptm_shared_ft), FUN_000f2304 (sptm_parse_region)
- FUN_000f4188 (sptm_set_shared_region) → FUN_000ef4e0 (sptm_root_ft), FUN_000ef8c8, FUN_000b2698 (sptm_shared_bind)
- FUN_000f458c (sptm_nest_region) → FUN_000ef4e0, FUN_000ef8c8, FUN_000f4d60 (sptm_parse_region2), FUN_000e276c, FUN_000e2480, FUN_000e2c18
- FUN_000f4eec (sptm_unnest_region) → FUN_000ef4e0, FUN_000ef8c8, FUN_000f4d60, FUN_000e276c, FUN_000e2480, FUN_000e2150, FUN_000d76fc, FUN_000e2c18

## UAT stub region edges (sptm_stubs_uat.c batch)

- 0x000b2014 sptm_uat_get_u64 -> 0x000eb004 (UAT object dispatch entry)
- 0x000b2020 sptm_uat_obj_set_flag -> 0x000eb004
- 0x000b211c sptm_uat_obj_op_30 -> 0x000eb004
- 0x000b2198 sptm_uat_obj_op_38 -> 0x000eb004
- 0x000b20d0 sptm_uat_counter_bump -> 0x000f8084, 0x000f8214
- 0x000b2584 sptm_uat_copy_chk -> 0x000ae214 (checked block copy)
- 0x000b2260 sptm_uat_table_commit_bswap -> 0x000b2584 (copy_chk)
- 0x000b24c0 sptm_aes_block <- thunk 0x000ae4ec
- 0x000b2258 sptm_thunk_sha256_compress -> 0x000b0e30 (sha256_compress)
- 0x000b2d40 sptm_uat_tlb_invalidate -> TLBI op table 0x00014408 (0xb2f00..b2f48)
- 0x000b3600 sptm_uat_unmap_walk -> 0x000c5784 (uat_va_walk); callback -> 0x000b37fc / 0x000b3d90
- 0x000b37fc sptm_uat_unmap_cb_table -> 0x000b3adc (uat_cleanup), 0x000b3b34 (uat_walk_entry), 0x000e2480 (fte_acquire)
- 0x000b3d90 sptm_uat_unmap_cb_leaf -> 0x000b3adc, 0x000b3b34
- 0x000b52fc sptm_uat_copy_segments -> 0x000c5248 (uat_state_get), 0x000b486c (uat_map_continue)
- 0x000b6524 sptm_uat_init -> 0x000b79e8 (dt_node), 0x000b7c04 (dt_prop), 0x000e45a8 (iommu_region_ref), 0x000e41bc (alloc), 0x000e4d78 (dart_state_get)
- SK/TXM entry stubs: 0x000b25c0..0x000b2608 -> 0x000a111c (sptm_sk_entry); 0x000b2620..0x000b2698 -> 0x000a0f7c (sptm_txm_sk_entry)


## IOMMU batch edges (sptm_iommu.c) — UAT / NVMe / T8110 DART

- 0x000b4068 sptm_uat_unmap_begin -> 0x000c5248 (uat_state_begin), 0x000f8844 (panic), 0x000f8804 (assert), 0x000e4e74 (kernel_ref), 0x000e5090 (kernel_unref), 0x000e40ec (guest_to_phys), 0x000abeb0 (memcpy), 0x000d8a58, 0x000b32d0 (uat_end)
- 0x000b4374 sptm_uat_prepare_fw_unmap_continue -> 0x000c5248, 0x000f8804, 0x000b3adc+0x000b3b34 (pte lookup), 0x000b2d40 (tlb_invalidate), 0x000d8a58, 0x000e5090
- 0x000b46bc sptm_uat_prepare_fw_unmap_begin -> 0x000c5248, 0x000f8844, 0x000c5784 (guest_range_validate), 0x000b4374 (continue), 0x000d8a58, 0x000e5090
- 0x000b486c sptm_uat_map_continue -> 0x000c5248, 0x000f8844/8804, 0x000c5784, 0x000e2480 (fte_acquire), 0x000e56ac (phys_lock), 0x000e4e74/0x000e53d8/0x000e5090 (kernel_ref family), 0x000d8a58; consults boot_dispatch + iommu_dart_info tables
- 0x000c1e94 sptm_nvme_ans_sha_reg -> 0x000f8844/8804, 0x000e56ac (phys_lock)
- 0x000c2248 sptm_nvme_bar_iocq_reg -> 0x000f8844/8804, 0x000e56ac
- 0x000c24c8 sptm_nvme_bar_iosq_reg -> 0x000f8844/8804, 0x000e56ac
- 0x000c2734 sptm_nvme_bar_ioqa_reg -> 0x000f8844/8804
- 0x000c2908 sptm_nvme_bar_admin_queue_regs -> 0x000f8844/8804, 0x000e56ac
- 0x000c7424 sptm_t8110dart_clear_exception -> 0x000e4d78 (dart_state_get), 0x000d617c (dart_pte_lookup), 0x000c76ac (dart_clear_error), 0x000f8844/8804
- 0x000c7efc sptm_t8110dart_clamp_tlimits -> 0x000e4d78, 0x000f8844/8804
- 0x000c8174 sptm_t8110dart_read_smmu_stt_index -> 0x000e4d78, 0x000c7bac (dart_flush), 0x000f8844/8804
- 0x000c8384 sptm_t8110dart_set_smmu_window -> 0x000e4d78, 0x000f8844/8804
- 0x000c8554 sptm_t8110dart_query_tlb -> 0x000e4d78, 0x000c786c (dart_poll), 0x000abeb0 (memcpy), LOAcquire/Release, 0x000f8844/8804
- 0x000c8d04 sptm_t8110dart_clear_err -> 0x000e4d78, 0x000c76ac (dart_clear_error), 0x000f8844/8804
- 0x000c8fb8 sptm_t8110dart_enable_translation -> 0x000e4d78, 0x000c9364/0x000c92e8 (dart_acquire v2/v1), 0x000f8844/8804
- 0x000c93d8 sptm_t8110dart_disable_translation -> 0x000e4d78, 0x000c9364/0x000c92e8, 0x000f8844/8804
- 0x000c9728 sptm_t8110dart_init -> 0x000e4d78, 0x000caa9c (dart_lock), 0x000cabb4 (dart_lock_set), 0x000f8844/8804
- 0x000cacd0 sptm_t8110dart_skip_enable_clock_protection_write (alias enable_clock_protection/powerup) -> 0x000e4d78, 0x000caa9c, 0x000cc2bc (ps_refcount inc), 0x000c9364/0x000c92e8, 0x000cc540/0x000c7e5c (dart_write_reg v2/v1), 0x000cc490/0x000cc3f8 (dart_write_field v2/v1), 0x000c786c (dart_poll), 0x000abeb0 (memcpy), 0x000cabb4 (dart_lock_set), 0x000f8844/8804
- 0x000cc5e8 sptm_t8110dart_disable_clock_protection (alias powerdown) -> 0x000e4d78, 0x000c8a14 (dart_save), 0x000cc2bc (ps_refcount dec), 0x000c786c, 0x000abeb0, 0x000f8844/8804
- 0x000ce144 sptm_t8110dart_map -> 0x000e4d78, 0x000c9364/0x000c92e8, 0x000d617c (dart_pte_lookup), 0x000cd970 (dart_tt_lookup), 0x000cdd0c (dart_tlb_flush), 0x000e3d7c (phys_lookup), 0x000e56ac/0x000e5c80 (phys_lock/unlock), 0x000e4e74/0x000e53d8/0x000e5090 (kernel_ref family), 0x000f8844/8804
- Shared helpers called by the above: 0x000c5248 uat_state_begin; 0x000b32d0 uat_end; 0x000e4d78 dart_state_get; 0x000d617c dart_pte_lookup; 0x000e40ec guest_to_phys; 0x000e3d7c phys_lookup; 0x000e2480 fte_acquire; 0x000e4e74/0x000e5090/0x000e53d8 kernel_ref/unref/add; 0x000e56ac/0x000e5c80 phys_lock/unlock; 0x000f8844 panic; 0x000f8804 assert; 0x000abeb0 memcpy; 0x000abb60 memset; 0x000d8a58; 0x000c5784 guest_range_validate

## SART + T8110 DART driver region (osfmk/arm64/sptm/sptm_region_dart.c)
- 0x000c60e4 sptm_sart_validate_region -> 0x000f8844 (panic), DAT_00094cc8/95d18/95d20
- 0x000c6364 sptm_sart_region_lookup -> 0x000f8804 (assert), DAT_00094cc8, 00094cc0
- 0x000c64b4 sptm_sart_region_add -> 0x000c60e4, 0x000c68e4, 0x000e56ac (iommu_page_ref), 0x000f8844/8804, sysreg guard (state+0x24a)
- 0x000c68e4 sptm_sart_region_program -> 0x000f8804
- 0x000c6a54 sptm_sart_program_regions -> 0x000c6364, 0x000c68e4, 0x000f8844/8804
- 0x000c6e30 sptm_sart_state_init -> 0x000e4424, 0x000e4d78, 0x000b7898 (dt_next_node), 0x000b79e8 (dt_find_node), 0x000b7c04 (dt_get_prop), 0x000e63c8 (phys_map_va), 0x000e45a8 (va_to_phys), 0x000f8804
- 0x000c72f0 sptm_dart_disable -> 0x000e4d78, 0x000f8844/8804
- 0x000c76ac sptm_dart_clear_error -> 0x000c786c (dart_poll), 0x000abeb0 (memcpy), 0x000f8804/8844
- 0x000c786c sptm_dart_poll -> 0x000c7bac (dart_flush), LOAcquire/Release, 0x000f8804
- 0x000c7bac sptm_dart_flush -> 0x000c7df8 (dart_read_reg), 0x000c7e5c (dart_write_reg_v1), 0x000f8804, DSB+WFE+CNTPCT wait
- 0x000c8960 sptm_dart_save_all -> 0x000e4d78, 0x000c8a14 (dart_save), 0x000f8844
- 0x000c8a14 sptm_dart_save -> 0x000f8804
- 0x000c8ba0 sptm_dart_ctrl_write -> 0x000e4d78, 0x000f8844/8804
- 0x000c92e8 sptm_dart_acquire_v1 -> 0x000f8804
- 0x000c9364 sptm_dart_acquire_v2 (alias sptm_dart_instance_lookup) -> 0x000f8804
- 0x000caa9c sptm_dart_lock -> 0x000f8804
- 0x000cabb4 sptm_dart_lock_set -> 0x000f8804
- 0x000cc2bc sptm_dart_ps_refcount -> 0x000f8804, DAT_001012b4/001012b8
- 0x000cc3f8 sptm_dart_write_field_v1 -> 0x000f8804
- 0x000cc490 sptm_dart_write_field_v2 -> 0x000f8804
- 0x000cc540 sptm_dart_write_reg_v2 -> 0x000f8804
- 0x000cd970 sptm_dart_tt_lookup (alias sptm_dart_va_to_pte) -> 0x000e40ec (va_lookup), 0x000f8804/8844, DAT_000130d8/130f8, 001012d8/00101ac8/00101ad0
- 0x000cdd0c sptm_dart_tlb_flush (alias sptm_dart_tlb_invalidate) -> 0x000c786c, 0x000ce0b4 (dart_flush_cmd), 0x000abeb0, 0x000f8804/8844, DAT_00012f40/12f48
- 0x000ce0b4 sptm_dart_flush_cmd -> 0x000c786c, 0x000abeb0, 0x000f8804

## DT / region-init helper edges (region-init batch)

- FUN_000b79e8 (sptm_dt_find_node) → FUN_000b7c04 (sptm_dt_get_prop), FUN_000b7cfc (sptm_dt_next_sibling)
- FUN_000b7dc8 (sptm_dt_iterate) → FUN_000b7cfc (sptm_dt_next_sibling)
- FUN_000b7cfc (sptm_dt_next_sibling) → FUN_000b7cfc (recursive over children)
- FUN_000b7898 (sptm_dt_find_by_name_recursive) → FUN_000b7898 (recursive DFS)
- FUN_000b7784 (sptm_dt_gpu_iouat_present) → FUN_000b79e8, FUN_000b7c04
- FUN_000b8154 (sptm_boot_fixups) → FUN_000b79e8 (find /chosen/memory-map)
- FUN_000b807c (sptm_boot_region) → FUN_000b7c04
- FUN_000b8230 (sptm_dispatch_engine_init) → FUN_000d9be8, FUN_000c1b70, FUN_000bf298, FUN_000bf4bc, FUN_000ae8b4, FUN_000aeaa4
- FUN_000b8470 (sptm_init_kc_regions) → FUN_000b2620 (TXM enter), FUN_000d9be8, FUN_000c1cc4, FUN_000bf298
- FUN_000ba950 (sptm_get_random) → FUN_000b79e8, FUN_000b7c04, thunk_FUN_000abeb0, thunk_FUN_000abb60
- FUN_000baa60 (sptm_init_sched) → FUN_000b79e8, FUN_000b7dc8, FUN_000b7c04, FUN_000ab8dc (sptm_el2_enable)
- FUN_000bb51c (sptm_start_sk) → FUN_000b807c, FUN_000d8a58 (sptm_txm_handoff)
- FUN_000bb9f0 (sptm_start_sk_ctx) → FUN_000b807c, FUN_000b7c04, FUN_000e40ec (sptm_va_lookup)

## hib/nvme/amcc/uat region (osfmk/arm64/sptm/sptm_region_nvme.c)
- FUN_000c0874 (sptm_hib_hash_nonwired) → FUN_000ae8b4 (sptm_sha_reset), FUN_000aeaa4 (sptm_sha_update), FUN_000bf874 (sptm_ace_finalize), FUN_000ad2dc (sptm_bsearch over DAT_000950d0, cmp 0xd649c), FUN_000f8844/8804 (panic), FUN_000ae44c (stack_chk_fail)
- FUN_000c1430 (sptm_hib_nonwired_hash_guard) → FUN_000d6524 (sptm_dram_write dispatch)
- FUN_000c1688 (sptm_announce_bootstrap) → sptm_panic_str; sets stage bit 0x800000 + LORelease
- FUN_000c172c (sptm_amcc_ctrr_program) → 12x sysreg (3,0,0xb,*) + TLBI alle1 + DSB + ISB
- FUN_000c1ab0 (sptm_amcc_ctrr_program_protected) → 12x sysreg (3,0,0xb,5,2..5) + TLBI
- FUN_000c1b70 (sptm_amcc_cache_enable) → FUN_000c4c68 (sptm_amcc_lock_check 2/3), FUN_000c44ac (sptm_amcc_lock_regs_parse), FUN_000c4d8c (sptm_amcc_memcache_enable 2), sptm_reg_read/write CTRR C/D, TLBI
- FUN_000c1cc4 (sptm_amcc_cache_disable) → FUN_000c4c68 (3), FUN_000c44ac, FUN_000c4d8c (3), FUN_000d977c (sptm_papt_op_b unmap)
- FUN_000c2ccc (sptm_nvme_validate_queue_entries) → FUN_000f8844 (panic 0x3000005/a/b)
- FUN_000c3b94 (sptm_nvme_bar_setup) → FUN_000d8a58 (sptm_kvtophys), FUN_000f8844
- FUN_000c3c78 (sptm_nvme_init) → FUN_000e63c8 (sptm_dt_io_translate), FUN_000e45a8 (sptm_frame_alloc), FUN_000e41bc (sptm_boot_alloc_frames), FUN_000d8a58 (sptm_kvtophys), FUN_000b79e8/000b7c04 (DT), FUN_000c446c (sptm_format_region_id), FUN_000f8844/8804
- FUN_000c446c (sptm_format_region_id) → FUN_000ad278 (sptm_snprintf)
- FUN_000c44ac (sptm_amcc_lock_regs_parse) → FUN_000b79e8/000b7c04 (DT), FUN_000ae158 (sptm_memcpy), FUN_000c48e0 (sptm_dt_get_reg_pair), FUN_000c4adc (sptm_amcc_ctrr_parse x4)
- FUN_000c48e0 (sptm_dt_get_reg_pair) → FUN_000b7748 (sptm_dt_prop_name), FUN_000b7c04 (DT)
- FUN_000c4adc (sptm_amcc_ctrr_parse) → FUN_000b79e8 (DT), FUN_000c48e0 (x5)
- FUN_000c4c68 (sptm_amcc_lock_check) → FUN_000c44ac
- FUN_000c4d8c (sptm_amcc_memcache_enable) → FUN_000b79e8/000b7c04 (DT), FUN_000c44ac, FUN_000ab994 (sptm_dcache_flush), per-CPU CPM via sptm_percpu_state
- FUN_000c5248 (sptm_uat_state_get) → FUN_000e4e74 (sptm_paddr_validate), FUN_000e3d7c (sptm_phystokv), FUN_000c5550 (sptm_uat_fte_get), FUN_000e40ec (sptm_phystokv_outside_window), FUN_000d8a58 (sptm_kvtophys), FUN_000f8844
- FUN_000c5550 (sptm_uat_fte_get) → FUN_000e3d7c
- FUN_000c55cc (sptm_uat_table_translate) → FUN_000e4e74, FUN_000e3d7c, FUN_000c5550, FUN_000f8844
- FUN_000c5784 (sptm_uat_va_walk) → FUN_000f8844
- FUN_000c59b8 (sptm_snprintf_wrap) → FUN_000ad278
- FUN_000c59f4 (sptm_uat_handoff_magic) → reads handoff magic at sptm_uat_driver_state+cpu+10 (FUN_000f89b4 callee)
- FUN_000c5a18 (sptm_hang_spin) → infinite `mov x0,#0x9898; b .` fail-stop

<!-- trace region (sptm_region_trace.c) -->
- FUN_000bc084 (sptm_sk_bootstrap_complete) → FUN_000c15b4 (sptm_dbg_print), FUN_000d7f80 (sptm_teardown_el2_alloc), FUN_000d8bf8 (sptm_map_handoff), FUN_000b8230 (sptm_dispatch_engine_init), FUN_000bb61c/FUN_000a10e0 (sptm_start_txm/sptm_txm_entry), FUN_000a121c (sptm_enter_domain), sptm_per_cpu_state
- FUN_000bc19c (sptm_boot_stage_bootkc) → FUN_000d9be8 (sptm_memmap_available), thunk_FUN_000ac190 (sptm_strcmp), PAPT table DAT_001012f8, FUN_000f8844/8804, SCTLR_EL1
- FUN_000bc338 (sptm_boot_stage_txm) → FUN_000d9be8 (sptm_memmap_available), FUN_000f8804
- FUN_000bc3d0 (sptm_boot_stage_sk_handoff) → FUN_000dce04 (sptm_cpu_init), FUN_000baa60 (sptm_init_sched), FUN_000d8a58 (sptm_txm_handoff), FUN_000a11e0 (sptm_sk_entry_early), FUN_000a121c (sptm_enter_domain)
- FUN_000bdd34 (sptm_cputrace_carveout_start) → reads *(DAT_00095d40+0x18)
- FUN_000bddd0 (sptm_cputrace_carveout_init) → FUN_000e4424 (sptm_subsys_register), FUN_000e4d78 (sptm_percpu_base), FUN_000b79e8/000b7c04 (DT), FUN_000e41bc (sptm_alloc_elements), FUN_000d8a58 (sptm_txm_handoff)
- FUN_000bdf54 (sptm_trace_region_add) → FUN_000f8804; region table 0x949b0/count 0x94978
- FUN_000be044 (sptm_dt_key_read) → FUN_000b79e8/000b7c04 (DT), FUN_000e9f28 (sptm_panic_hib)
- FUN_000be150 (sptm_memmove) → self-contained
- FUN_000becd0 (sptm_dt_key_copy) → FUN_000be044 (sptm_dt_key_read), FUN_000b2584 (sptm_bzero_block), FUN_000e9f28 (sptm_panic_hib)
- FUN_000bf298 (sptm_sha_hash_range) → FUN_000ae8b4 (sptm_sha_reset), FUN_000aeaa4 (sptm_sha_update), FUN_000e3d7c (sptm_frame_lookup), FUN_000e03f4/000e0770/000e05bc (zero page), FUN_000e40ec (sptm_va_lookup), g_sha_obj->finalize, FUN_000bf4bc (sptm_crypto_finalize)
- FUN_000bf4bc (sptm_crypto_finalize) → FUN_000b25b0 (sptm_crypto_ctx), FUN_000b07bc (sptm_gcm_update_barr), FUN_000aeaa4 (sptm_sha_update), FUN_000b0504 (sptm_gcm_finalize_barr), FUN_000b2584 (sptm_bzero_block)
- FUN_000bf5d0 (sptm_nvram / SK-HIB begin) → FUN_000ae8b4/000aeaa4 (SHA), FUN_000e3d7c (sptm_frame_lookup), FUN_000f8804, FUN_000b2608 (sptm_sk_hib_patchup); FTE class2 table DAT_00095d51, refcnt desc+6
- FUN_000bf874 (sptm_ace_finalize) → FUN_000f8804; ACE ctx input +0x200 / result +0x100

## bootstrap/io region (0xd0000-0xe0000) — sptm_region_io.c
- 000d0c98 (sptm_dart_t8110_init) -> 000d1b2c (sptm_dart_register)  [per dart-t8110 node]
- 000d1b2c (sptm_dart_register) -> 000d4d30, 000d4dd4, 000d4efc, 000d5a40, 000d5bd8
- 000d4efc (sptm_dart_sid_setup) -> 000d5a40 (sptm_dart_sid_alloc), 000d5bd8
- 000d056c/000d0610/000d06c0/000d074c (dart lookup/clock-protection helpers) -> FUN_000e4d78 (per-CPU dart state), FUN_000c786c (clock-protection op), FUN_000c9364/FUN_000c92e8 (dart write gates)
- 000d9aa8 (sptm_map_boot_region) <- called by 000b8f84 (sptm_init) for each boot region
- 000d9be8 (sptm_retype_boot_range) -> 000d8bf8 (sptm_retype_frames)
- 000d9d44 (sptm_papt_commit) -> sptm_qsort; produces g_committed_range_{base,va,pages}
- 000d9940 (sptm_phystokv) -> 000d8f94 (sptm_papt_walk_alloc), 000d941c (sptm_papt_install_leaf)
- 000d8f94 -> 000d823c (sptm_alloc_frames), 000d8bf8, 000d8a58 (sptm_va_to_pa)
- 000d823c -> 000d8914 (sptm_papt_unmap_leaf), 000d8784 (sptm_papt_update_root_pte)
- 000d8914 -> 000d8a58; 000d8bf8 -> 000d8914/000d8784; 000d7348 -> 000d6f00 (sptm_papt_walk) -> 000d76fc (slice update)
- 000d6124/000d617c (copy-to-scratch) -> FUN_000f8714, FUN_000e3d7c, FUN_000e40ec
- 000dcf80 (sptm_io_bootstrap) -> 000d6860 (sptm_dt_parse_io_space), 000d9940, 000d823c, sptm_enable_iommu (FUN_000e61f0), 000d64d0/000d6e64 (comparators)

## dispatch/register region (0xe0000-0xeb000) — Wave3j

- FUN_000e6bc0 (sptm_dispatch_transition) — central gate; validates via FUN_000e7068 (sptm_dispatch_state_name, table @0x16640) + FUN_000e70b4 (sptm_dispatch_event_name, table @0x166f8)
- FUN_000e74e0 (sptm_dispatch_route) → FUN_000e6bc0  [selector→event 0x2/0x3/0x4/0xc/0xd/0xe; domain field 48-55]
- FUN_000e7644 (sptm_dispatch_vector_type) → FUN_000e6bc0 [event 6]
- FUN_000e7100 (sptm_vector_type_dispatch) → FUN_000a0adc (sptm_exception_return) [3 guard panics]
- FUN_000e71c4 / 0xe71c8 → FUN_000a1318 + branch 0xe71d8
- FUN_000e71d8 / 0xe71dc → FUN_000a0d80 + branch 0xe71ec
- FUN_000e61f0 (sptm_iommu_bootstrap) → FUN_000e71ec (sptm_register_dispatch) [register IOMMU endpoints]
- FUN_000e71ec (sptm_register_dispatch) → FUN_000e6768 (register endpoint under caller domain) [single-write slot]
- FUN_000e3d7c (sptm_phystokv) → FUN_000e4030 (sptm_ftes_overlap), FUN_000ad2dc (sptm_bsearch_range)
- FUN_000e7d78 (sptm_hib_setup) → FUN_000ea744 (sptm_dt_pmap_io_ranges), FUN_000eaa44 (sptm_hib_alloc_page), FUN_000eabb4 (sptm_hib_map_region), FUN_000ea40c (sptm_page_list_next_free), FUN_000e9ecc (sptm_assert_fail), FUN_000e9f28 (sptm_panic_hib)
- FUN_000eaa44 (sptm_hib_alloc_page) → FUN_000ea40c, FUN_000ea5f8 (sptm_hib_is_managed_page)
- FUN_000ea744 (sptm_dt_pmap_io_ranges) → FUN_000eaf10 (sptm_hib_io_range_add) [callback]
- FUN_000e78dc (sptm_guest_state_restore) — full EL2/EL1 guest context restore (no callees)
- FUN_000e7c30 (sptm_stage2_state_restore) — restore stage-2 EL2 MMU/exception context
- IO-frame paths: FUN_000e56ac/0xe5c80 (map/unmap) → FUN_000e4e74 (check_owner), FUN_000e5958 (refcount_ex), FUN_000e5090 (release); FUN_000e45a8 (io_frame_add) → FUN_000e3d7c, FUN_000d9940 (commit)
- IOMMU state: FUN_000e4424 (state_alloc) / FUN_000e4d78 (state_get) — per-dispatch state arrays (DAT_00095320/0x95328/0x95330)
- DRAM/paddr: FUN_000e35b4 (dram_update_type), FUN_000e3a14 (sptm_paddr_in_dram), FUN_000e384c (sptm_paddr_type) — DRAM byte table DAT_000952e8
- SPTM pmap/guest-adjacent region (000eb004-000f89b4, sptm_region_pmap.c):
  - 000eb004 (sptm_hib_restore) → 000ecd20 (sptm_hib_disjoint_region), 000ed0f0 (sptm_hib_disjoint_update), 000ed244 (sptm_hib_ctrr_region), 000b25a0/000ae8b4/000aeaa4/000bf874 (SHA), 000becd0 (ctrr key), 000b211c (gcm decrypt), 000b2584 (key zeroize), 000e9ecc/000e9f28 (panic)
  - 000ecd20 → 000ed464 (sptm_ctrr_print_hex) [debug output], 000eaa44 (sptm_alloc)
  - 000ed244 → 000ae8b4/000aeaa4 (SHA), 000bf4bc (crypto finalize), 000e9ecc (panic)
  - 000ed340 (sptm_exception_dispatch) → 000ed464 (sptm_ctrr_print_hex), 0009c2c8 (sptm_fatal); caller 0009c2dc (sptm_vector_context_save)
  - 000eefd4 (sptm_fte_acquire) → 000ef4e0 (sptm_root_ft), 000ef8c8 (sptm_shared_ft)
  - 000ef1f8 (sptm_fte_validate) → 000ef468 (sptm_fte_next_paddr); called by 000ee278 (sptm_map_page)
  - PTE layer: 000f25fc (sptm_pte_enter), 000f2878 (sptm_pte_remove), 000f29f0 (sptm_pte_update) → 000f2eec (sptm_pte_perm_check), 000f2f54 (sptm_fte_ptep), 000e2e2c (sptm_write_pte), 000e0a10 (sptm_cacheattr); 000f2fb4 (sptm_pte_remove_final)
  - Region/TLB: 000f4d60 (sptm_parse_region2) → 000f2304 (sptm_parse_region); 000f61c0 (sptm_root_acquire_shared) called by 000f5f2c/000f6368/000f6634/000f6aec; 000f6aec (sptm_region_tlb_flush) → 000f61c0, 000d76fc (sptm_tlb_op); 000f6d54 (sptm_tlb_maintenance) / 000f7108 (sptm_invalid_op) pair
  - GCM (exclave protected-metadata): 000f7ff4 (sptm_gcm_ctx_setup) → 000b0cc8 (gcm_ctx_init), 000b1140 (ghash table), ops->keysched; 000f8084 (sptm_gcm_key_iv_setup); 000f8214 (sptm_gcm_update) → 000b2204 (state adv), 000b0cb4 (ghash_step), 000b20d0 (counter bump), 000afad0 (aes_gcm_core)
  - Panic printers: 000f84e4 (sptm_panic_format) → 000ad278 (snprintf), 000c15b4 (serial), 000ae278 (strlcpy_chk), 000a1374 (sptm_guest_exit_handoff); 000f8804 (sptm_panic) → 000f84e4, 000c5a18 (panicking cpu), 000f8714 (sptm_panic_record), 000e7678 (dispatch name); 000f8844 (sptm_panic_code) / 000f8824 (sptm_panic_fmt) / 000f8834 (sptm_panic_bad_dt); 000f89b4 (sptm_invalid_genter) → 000c59f4, 000f8804

### Reconcile wave (sptm_reconcile.c) — batch-fallthrough functions
- 000ab9e0 (sptm_dcache_flush, body in sptm_entry_stubs.c) → 000ab964 (sptm_dcache_clean_invalidate_range); called by 000c2dec, 000c3434 (sptm_nvme_map_pages)
- 000abeb0 (sptm_memcpy) — tree-wide memcpy/memmove thunk (body in sptm_reconcile.c)
- 000bc75c (sptm_cputrace_state_code, body in sptm_trace_hib.c) — caller set at top of this section
- 000c15b4 (sptm_dbg_print / sptm_serial_str) → 000ad278 (snprintf), 000abb60 (bzero), 000ae44c (stack_chk); called by 000b8f84, 000bb804, 000bc084, 000f84e4
- 000cf7a8 (sptm_dart_pte_ref_update) → 000caa9c, 000c7df8; called by 000cef24, 000cfaec (sptm_t8110dart_map_table)
- 000f57c8 (sptm_switch_root) → 000ef4e0 (sptm_root_ft), 000d7cf8 (sptm_tlbi_va), 000e2150 (sptm_fte_info), 000d8a58 (sptm_get_parent_paddr), 000e233c (sptm_ft_for_pte)
- 000f6e30 (sptm_batch_sign_user_pointer) → 000d617c (sptm_copy_to_scratch)
- 000f719c (sptm_tag_op) → 000d617c, 000e0a10 (sptm_cacheattr), 000d7348 (sptm_set_pte_attr), 000d76fc (sptm_tlb_op), 000e40ec (VA translation)
- 000f7880 (sptm_tag_papt_multipage) → 000f719c; 000f78e0 (sptm_untag_papt_multipage) → 000f719c

### TXM region tail (osfmk/arm64/txm/txm_region_tail.c) — CoreEntitlements/IMG4 validator (00060000-0006228c)
- 00060088 (txm_ce_object_lookup) → 0005e960 (hash-subrange), 0005f5a4 (linear fallback), 0005ef74/0005ed6c/0005efe0 (name-lookup helpers); called by 00031388/00031424/000314b0/00032104/000321dc/00034420/00034cf4/00034d68/00034e90/00034f24/00034ff8 + __text 00020000
- 0006037c (txm_ce_validate_dictionary) → 00060608 (txm_ce_validate_string_type), 0006066c (txm_ce_validate_value), 00025c6c (log); string 0x6b80 "CoreEntitlements validation"
- 0006066c (txm_ce_validate_value) → 00060230 (txm_ce_parse_dict_or_array), 0006037c (dict recurse), 0004443c/0004447c/000444fc/00044580 (int getters)
- 00060230 (txm_ce_parse_dict_or_array) → 000448ac (ce_parse), 00044580, 00044178; template DAT_0000dc40
- 000612e0 (txm_ce_parse_im4p, magic IM4P) → 00061268 (txm_ce_validate_small_dict), 00061394 (txm_ce_parse_payp); template DAT_00007990
- 00061418 (txm_ce_parse_cryptex) → 000612e0, 000447e4 (ce_parse_magic), 00061268; template DAT_00007900
- 00061cbc (txm_ce_verify_cryptex) → 000455b8 (ce_parse_im4c, magic IM4C), 00061570 (txm_ce_parse_cryptex_dict); ops callbacks at *param_9
- 00061570 (txm_ce_parse_cryptex_dict) → 000448ac; templates DAT_00007b10 "CTRP", 00007b40
- 0006151c/00061538/00061554 (cryptex wrappers) → 00044e28/00044e54 (ce_manifest_parse); string 0x3429 "Cryptex1 boot verification VMA2"
- 00061ea4 (txm_phys_to_virt) → 0004ed7c (pa_is_mapped), 0004f2b4 (pa_walk); globals DAT_000153a8/b0/b8/c0/c8/d0/d8/e0/e8, 00015400/408/410
- 00062260/00062264 → 00050750 (txm_antireplay_write) then 00050d70 (txm_panic "panic: writing anti replay state" @0x37f4); 00062274/00062288/0006228c → 00050d70 directly
- 00061b9c (txm_ce_foreach_entry) → 00044c6c (ce_entry), 000446f4/00044724 (iter), 00045708 (ctx)
- 00061880/00061960 (ctx copy) → 00045760/00045750/00045708/000457b8 (ctx accessors)
- 00061a80/00061ae4/00061b48 (ce getters) → 00045718 (ctx_state), 0004577c (ctx_set), 0004447c/000444fc/0004443c

### TXM region core (osfmk/arm64/txm/txm_region_core.c) — bignum/ECDSA/DER/IMG4 verify layer (00040000-0004b000)
- 00040fb4 (txm_sha256_compress) / 00041a9c (txm_sha512_compress) → SHA-2 block transforms; K tables DAT_00007210 / 00006f20
- 00043670 (txm_bn_mulmod_p256) → P-256 field multiply (schoolbook + Mersenne-fold); 000415a0 (txm_bn_mul6) → 384-bit mul; 00043d38 (txm_ecdsa_scalar_mul_p384) → P-384 ladder
- 00040c54 (txm_ecdsa_scalar_mul_p256) → 00043670 (squarings), fixed-window ladder
- 00042e34 (txm_bn_modinv) → Newton inverse; 00042fd0 (txm_bn_modpow) → 00041488 (txm_bn_mont_mul) square-and-multiply
- 00042418 (txm_ecdsa_verify) → 00042b84/00042b78 (bn getters), 00043cc4 (txm_bn_cmp), 0003c9bc/0003b770/0003d10c/0003b0c0/00039d4c (engine verify)
- 00044184 (txm_der_read_tlv) → 0004a2d0 (txm_der_read_len); DER TLV decode (traps 0x5513/0x5515/0x5519 on malformed)
- 00044c6c (txm_img4_elem) → 00044c4c/00044e54 (IM4M verify, tag 0x494d344d), 00044efc (txm_im4m_key, MANP)
- 000455b8 (txm_im4m_decode) → 00044c4c/0006151c (IM4M/IM4C dispatch by magic 0x494d3443/4d)
- 000457d0 (txm_cert_verify_chain) → 00044c6c, 000446f4, 000610a8; cert store DAT_000127a0/000481cc
- 00045a38 (txm_verify_developer) → 00044e18; callback table param_4[0..3] drives EC/RSA digest verify
- 00049ae4 (txm_manifest_handler_2) → tag OIDs DAT_0000a0d9/a0e2/a0eb/a106/a10f/a0f4/a0fd, 0004ab28/0004ad00/0004af1c/0004aff8/0004b0ac (element checks)
- 000483a8 / 00048700 (txm_sig_verify_p256 / p384) → 00043c50 (txm_bn_from_bytes_checked), 0003833c/0003be50 (EC verify)
- 000481cc (txm_cert_lookup) → DAT_000127a0 (8x0x20 cert-name table); 0004824c (txm_oid_alg) → OID→{name,len} map
- 0004a498 (txm_img4_parse_elems) → 0004b80c, tailq ops; 0004a7b8 (txm_im4p_probe) → 00048c2c/000490b8/0003767c

### TXM image4/boot-manifest region (batch T6, txm_region_b.c) — 0x56000-0x60000
- 0005602c (txm_manifest_exec_policy_check) → 0005652c/0005077c (per-cpu ctx), 000564b8 (panic), 0005979c (constraint ctx), 000598b0/000598bc/00059a54 (manifest decode + trust eval), 000585b8 (log), 00050d70 (panic)
- 00056584 (txm_cdhash_lookup_dispatch) → 00051bd0/00051b3c/00051ce0/00051ccc (CDhash lookup)
- 00056834 (odometer entangle) → 0005c0cc (nonce query), 00058fa0 (mix-match), 0005bd78 (entangle), 0005b7f0 (digest constraint)
- 00056a1c/0x56aa4 (image4 cert root parse) → 00058e9c (cert type), 00056e70 (unsupported cert panic), 00058fc0 (query anchor), 00044178 (DERDecodeItem), 00057a30 (digest OID type), 00047ba0 (parse root)
- 000566b8 (iterator next) → 00056628 (null iter), DAT_0001cf30 table
- 00057f7c (manifest dump) → 000566b8, 0005861c/0x587f0/0x589bc/0x58b88/0x58d18 (property queries), 000585b8
- 000592b4 (manifest trust eval) → 00057ed0 (impl dispatch), 00056e00 (boot impl), 0005c61c/0x5c6d4 (anti-replay prep), 00059628/0x596b8 (trust eval), 0005c944 (replay check)
- 0005a0ac (policy impose) → 00056d6c/0x56d88 (property resolve), 0005b180 (available), 0005b224/0x5b430/0x5b610/0x5b7f0/0x5bb1c (constraint enforcers)
- 0005c230 (restore constraint) → 0005861c/0x587f0/0x589bc/0x58b88/0x58d18, 0005c5bc/0x5c5d0
- 0005c944 (policy replay check) → 0005c00c (chip query), 0005cab8 (policy table find), 00052a88/0x52a78 (policy validate/present)
- 0005d258 (digest64/odometer import) → 0005789c (ident from cstr), 00053070 (digest oid), 0005d3b8 (minmax), 0002d990 (strtoul)
- 0005db20 (dict parse) → 00037304/0x37570/0x37584/0x374a0 (dict helpers), 0005d80c/0x5d8a4/0x5d93c/0x5d9d4/0x5da6c (key-length parsers), 0005e080 (collection)
- 0005e374 family (CoreEntitlements subset) → 0005f1d0 (count), 0005ed6c/0x5ef74 (dict apply), 0005f5a4 (key lookup), 0005f690 (data cmp)
- 0005fb88 (entitlements blob parse) → 00044178 (DER), 00060230 (decode object), 0006037c (parse ident), 0005db20 (dict parse), 0005e168 (dict init)
- 000576f0-00057850 (runtime callback table) → 00057870 (chain builder), 00029784 (panic "function should never be called")

## TXM trust-cache / txm_enter dispatch region (TxmT2, osfmk/arm64/txm/txm_region_trustcache.c, 0x2a000-0x35000)

- 0002adec (txm_enter) → 0002b380/0002b3e8/0002b470/0002b4f8/0002b58c/0002b5e8/0002b644/0002b760/0002b870/0002b974/0002ba18/0002bad8/0002bbac/0002bc08/0002bc50/0002bc84/0002bd5c/0002bdb8/0002be18/0002be60/0002bf3c/0002c018/0002c134/0002c18c/0002c1f4/0002c258/0002c2c8/0002c314/0002c3a0/0002c3f8  [per-op handlers]
- 0002adec (txm_enter) → 0002ab70 (finalize_state_string)  [state block commit]
- 0002abec (txm_enter_platform_ops) → 0002ab70, 0002ab30, 0002aba4, 0002abb0  [secondary platform dispatch]
- 0002b644 (load_trust_cache) → 00026350 (txm_trust_cache_load) → 00028594/000285d0/0002c5a4/0002c76c/00027284/00031060
- 00026350 (txm_trust_cache_load) → 00031060 (txm_cert_register_full) → 0002fa00 (txm_image4_eval)
- 0002c3f8 (txm_op_image4_dispatch) → 0002cbd0 (txm_image4_dispatch) → 000535e0 (img4 handler) + 00053cb0 (input size)
- 0002a674 (txm_trust_cache_range) → 0004e8b4/0004eb24 (DT node/prop)
- 0002a004..0002a434 (DT getters) → 0004e8b4/0004eb24 (DT)
- 0002c5a4/0002c76c (range_translate/flush) → 0002c6a8 (range_page_translate) → 0002c84c (range_resolve) → 00061ea4 (translate)
- 0002cbd0 (image4_dispatch kind 5) → 0002c5a4/0002c76c (code+data range translate)
- 00032630 (txm_codedir_parse) → 00033150/000331b8/00033254/00033334/00033414/000334cc (per-version parsers) + 00032910 (mark)
- 00032b38 (superblob_find_command) → 0002d4d0 (memcmp)
- 00032c70 (superblob_parse) → 00032c30 (get_cmd), 00033150/000331b8/00033254/00033334/00033414/000334cc
- 00031714 (txm_amfi_cms_verify) → 0003154c (hash_amfi) + 000476a0 + 00047754 + 000318c8 (chain verify)
- 000345f4 (txm_trust_eval) → 00031714 + 000319a8 + 00031b44 + 000318c8
- 00031b70 (txm_cectx_create) → 0003161c (amfi_cms_parse) → 00047588
- 00031cb0 (txm_cectx_init_with_type) → 00031714 + 0005fb88 + 00034e90 + 00034dc4 + 00034420
- 0002fa00 (txm_image4_eval) → 0002fc9c (status callback), 00052e90 (prepare), 00055ecc/00055dec/00055f00/00055f88/0005642c (img4 core)
- fortified libc: 0002d240 (bzero), 0002d2b0 (memset), 0002d4d0 (memcmp), 0002d5f0 (ct_memcmp), 0002d6b0 (memmove), 0002d990 (strcmp), 0002da90 (strncmp), 0002dbe0/2dc80 (strlen), 0002efc4 (strlcpy), 0002ddf0 (vsnprintf core), 0002eba8/2ebb8 (strtol/strtoul)

## Batch T3 (0x35000-0x40000) — code-signing policy engine + crypto toolkit
- 00035f08 (txm_policy_check_dispatch) → 00035aa0/35a38/3596c/358a4/35800/35760/356e4/35650 (shared selectors) + 000351c8/35264/35364/354c8/35550 (per-rule)
- 000350c0/350e8/35178 (restricted-execution enable/disable state machine) ← 0002b4f8 (caller, "system_does_not_support_restricted") / 00022348
- 00035f08 → 00034b18 (trust context), 00031388/31424/314b0 (entitlement checks), 00033c9c/33bf4/33ad4 (range checks)
- 00035acc (policy prepare) → 00032630/33d40 (region resolve), 00034b30/34b50 (trust probes)
- 00035d24 (policy commit) → 00034028/325b0 (digest) — digest stored at ctx+0x40
- 0003a604 (txm_ecdsa_verify) → 0003a33c (core) → 0003f574 (modpow-mul), 0003d568 (exp window), 0003ecf0 (finalize), 0003f0e4 (GF combine), 0003bf90 (ct_memcmp)
- 0003b784 (scalarmul window) → 00037110/371a0 (window build/next), 00038cb4 (pt double), 000393bc/39d60 (pt add/sub wrap)
- 0003a6f4 (scalarmul ladder) → 0003b0d4/3b354/38cb4 (point ops), 00036fc4/37d84/3d430/3f070/3e984 (PRNG conditional ops), 0003d498 (PRNG)
- 0003c3d8 (modinv) → 0003d81c/3d8e4 (divstep), 0003c7e4 (inv step), 0003c2f0/3e8a0 (muladd)
- 0003eec4/0003ff50 (SHA-512 core) ← 00036f54/3ece8 (thunks)
- 0003f270 (SHA-256 core), 0003f9fc (SHA-1 core)
- 00039f60 (digest alg dispatch) → 000388b0/3e258/40c1c/43d00/38b9c (alg name tables)

## TXM core runtime primitives (osfmk/arm64/txm/txm_region_runtime.c) — 0x24f14-0x29f28
- Lock/refcount: 0x27128 txm_lock_acquire, 0x27218 txm_lock_release (per-object +0x10 counter, +0x11 active bit). Called by every region file's object lifecycle.
- Object pools (alloc/free/handle-validate): small 0x40 (0x26e80/0x27284/0x26de0), obj 0x1a0 (0x27448/0x27614/0x27378), medium 0x148 (0x278e4/0x27ab0/0x27814), node 0x50 (0x27d78/0x27f44/0x27ca8), slot 0x70 (0x281ec/0x283b8/0x2811c). Release wrappers 0x27720/0x27bb4/0x28028/0x284a0.
- Large slabs: 0x286d8/0x288a8/0x28a78/0x28c48 alloc, 0x28e20 free, 0x285d0 size-class select, 0x28594 span check. Back 0x24fc8 txm_boot_obj_release.
- Page alloc/release: 0x26ba4/0x26a74 (boot free-list DAT_000706b0/b8).
- Panic family: 0x298ec txm_panic -> 0x29730 txm_panic_msg -> 0x29784 txm_panic_call; 0x29a3c txm_fault; 0x2976c txm_panic_abort; 0x29a98 header write. Terminal secure-channel trap thunk_FUN_0002d230 (code 0xa0 only).
- Platform init: 0x2940c txm_platform_init (DT setup 0x29ad8, security/version probes 0x29bc8/0x29c9c/0x29d84/0x29e48/0x29f28, version 0x29714).

## Kernel-side SPTM/TXM client interface (kernelcache.arm64.kc, osfmk/arm64/sptm/kernel_client.c) — GENTER stub batch
- txm_enter (0xfffffe000bdbba20) → txm_enter_genter_core (0xfffffe000c0d7970) [TXM_DOMAIN=2 << 48 | selector] → GENTER
- txm_enter_genter_core (0xfffffe000c0d7970) ← txm_enter (single caller, verified get_function_callers)
- sk_enter_genter_core (0xfffffe000c0d7948) → GENTER [SK_DOMAIN=3 << 48 | selector]
- sptm_guest_va_to_ipa (0xfffffe000c0d993c) ← hv_el2_guest_fault (0xfffffe000b967768) [endpoint 24]
- sptm_guest_dispatch (0xfffffe000c0d997c) ← FUN_fffffe000b953e14 (guest-entry hub) [endpoint 27]
- sptm_retype (0xfffffe000c0d83e8) ← FUN_fffffe000b9552c4 (txm_alloc_free_page OOM path: retypes a VM page for TXM) [endpoint 1]
- Every sptm_* wrapper (0xfffffe000c0d83c0..0xfffffe000c0d8a78) → _sptm_pre_entry_hook (0xfffffe000b75e8e8) → GENTER → _sptm_post_exit_hook (0xfffffe000b75e954)

## cL4 Secure Kernel Tightbeam subsystem (osfmk/arm64/sk/sk_slice_03.c) — 0x1a2f4-0x20c88
Serialization/validation core for the Tightbeam inter-component data layer.
- Record writers: 0x1a4f0 cL4_typedata_write, 0x1a838 cL4_clntdata_write, 0x1b02c cL4_component_write, 0x1b620 cL4_initdata_write.
- Size computation: 0x1a760 cL4_clntdata_size, 0x1afb4 cL4_component_size, 0x1b370 cL4_component_metadata_size, 0x1dfb4 cL4_comp_fields_size.
- Record validators (consume loops): 0x1ba18/0x1c038, 0x1c81c cL4_comp_array_consume, 0x1cf2c/0x1d05c size-summers.
- Range/pair helpers: 0x1ab00 cL4_range_validate, 0x1db00 cL4_range_pair, 0x1a2f4 cL4_tagdata_validate_copy, 0x1a1dc (tagdata copy, out-of-slice).
- Growable buffers: 0x1db94/0x1dc08/0x1dc8c alloc, 0x1dd14/0x1dde4 grow, 0x1dd00 wrapper.
- Task/async engine glue: 0x1f1d0/0x1f670/0x1fa18 init, 0x1f38c cb, 0x1f834/0x1fc10 ForwardingConnection send, 0x1fde8 cL4_entry_resolve.
- TransportBuffer: 0x20448 write, 0x20560 seek, 0x20628/0x208a8 forward/dispatch, 0x209f8/0x20ac8/0x20bb8 pointer getters, 0x20c88 forget.
- Module singletons: 0x1df60 (ComponentInitData, id 0x677880), 0x1e790 (TransportBuffer, id 0x677790).
- Fatal-error family (module Tightbeam_ComponentInitData @ 0x5ac9c0 / TransportBuffer @ 0x5accb0): 0x1b998, 0x1bcac, 0x1ced0, 0x1afa84 (shared reporter).

## cL4 Secure Kernel transport-buffer message layer (osfmk/arm64/sk/sk_slice_02.c) — 0x157dc-0x1a1dc
Transport-buffer (tb_transport) + tb_message serialization layer.
- Message state machine: 0x15834 reset, 0x1585c set_state, 0x1586c init (encode, kind), 0x1590c state_transition (1/4→2), 0x15964 release, 0x15984 for_type, 0x159c0/0x159c8 state/kind getters.
- Transport accessors: 0x159b8 get_transport, 0x159d0 end, 0x15cd0 set_pos, 0x15cbc flags_test, 0x15bb4/0x15bbc/0x15be8/0x15c30 slot get/push/pop, 0x15b84/0x15b8c/0x15b94/0x15ba4/0x15bac field accessors.
- Buffer alloc/resize/map: 0x16134/0x16154 get_or_alloc, 0x16174 alloc, 0x16208 create_virt, 0x16318 create_phys, 0x16af0 alloc_buffer, 0x16ba4 resize_buffer, 0x16458 channel_create, 0x16a5c channel_flush.
- Copy core: 0x159dc/0x15a44/0x15ce4 transport copy (fail-closed TB_ASSERT), 0x16c24 copy_obj, 0x16d78 message_receive, 0x16e1c message_decode, 0x176a4 message_commit.
- Write/read: 0x17e94/0x17edc transport_write pair, 0x181f4 append_cap, 0x183f0 transport_read.
- put/get primitives: u8 0x187a4/0x1882c/0x188fc/0x18984/0x19000, u16 0x18b0c/0x18b98/0x18be8/0x1910c, u32 0x18c70/0x18cfc/0x18d4c/0x19220/0x19224/0x192b0, u64 0x18dd4/0x18e60/0x18f38/0x18fb8/0x19334/0x19338/0x193c4, words 0x18eb0, bytes 0x189d0.
- f32/f64: 0x19490/0x19588 encode/decode f32 (NaN-reject 6/7), 0x19670/0x19768 encode/decode f64.
- Capref transport records: 0x17a08/0x17a88 create, 0x17b7c/0x17b88 bind, 0x17b94/0x17bd4 release/destroy, 0x17c14 handler.
- Utility: 0x18560 flags_check_all, 0x185b8/0x18600/0x18650 region get/put, 0x19aac register, 0x19d40 emit_tag, 0x1a138 sorted_lookup, 0x1a1dc va_cap_resolve.

## Batch SkWave5 (0x200000-0x280000) — cL4 Secure Kernel vspace/MMU layer (osfmk/arm64/sk/sk_region_vspace.c)
- 1563 functions decompiled (range fully covered), assembled from 13 namespaced slice parts.
- Region is the cL4 kernel's vspace/page-table/MMU boundary + embedded Swift stdlib runtime (String/Range/Collection/UTF-8, integer formatting, SipHash, KeyPath) that the vspace layer calls.
- Key security-relevant cores (see docs/sptm/findings.md [sk-vspace]): slot-set bitmap walk 0x2587e0 (bitmap = sole mapping-permission authority, medium), open-addressing slot-key insert 0x25a864/0x25acb8 (no owner check, panic-on-dup), slot-path subscript 0x2557b8 (bounds-checked fail-closed), vspace entry table lookup-insert 0x26a328/0x26a9a8, owner-mask isolation gate 0x249a64/0x24a648, size-divisibility permission gate 0x24c2ec, region-equality gate 0x24ad48.
- Runtime prologue/epilogue thunks: 0x200150 object-describe root, 0x2023c4 sk_map_region_core, 0x277d80 guarded TLB/ASID flush entry (per-cpu ready gate 0x1e3048).
- Shared seL4/Swift runtime callees are extern (FUN_ addresses in comments); bodies owned by other waves (0x3xxxxx runtime library, out of this range).

## Batch SK14 (0x6a468-0x6d52c) — cL4 Secure Kernel cbootinfo/IPMM bootstrap (osfmk/arm64/sk/sk_slice_14.c)
- 120 functions decompiled (range fully covered) — launcher IPMM physical-memory manager + cbootinfo bootstrap parser + vspace-table client registry + embedded Swift-runtime thunks (DeviceTreeKit, Swift.NativeDictionary).
- Internal edges: sk_ipmm_freelist_init 0x6b7e0 → cboot alloc 0x6d240, launcher cap-table 0x6cea4; sk_ipmm_frame_alloc 0x6bcf8 → 0x6b7e0 (arena extend) + 0x6cea4 (freelist-table); sk_cbootinfo_parse 0x6c5cc → untyped-region finders 0x6cf50/0x6cfe4/0x6d024/0x6d0b8/0x6d150/0x6d1e4; dict layer 0x6abac → pair build 0x6ae9c → probe 0x6af08.
- Key security cores (see findings [Sk14]): frame alloc 0x6bcf8 (type-gated, arena-exhaustion fail-closed), boot-info parse 0x6c5cc (bounds-gated untyped/DART tables), freelist/zero-frame cap create 0x6b7e0, vspace list unlink 0x6c454 (fail-closed).
- Shared cL4/Swift runtime callees (FUN_004b7xxx/004b8xxx error funnels, 0x34a2c/0x36b118/0x36b270 etc) are extern (FUN_ addresses in comments); bodies owned by sibling SK wave workers.

## Batch SK18 (0x000776c0-0x0007b324) — cL4 Secure Kernel InternalExclaveLauncher CNodeAllocator (osfmk/arm64/sk/sk_slice_18.c)
- 120 functions decompiled (range fully covered) — pure-Swift CNode (capability-node) allocator for the internal exclave launcher (CNode.swift + CNodeAllocator.swift).
- Core edges: sk_cnode_allocator_init 0x78880 → sk_cnode_entry_build 0x7a718 (per-object CNodeEntry build) → sk_cnode_buf_append 0x7b2c8 (COW growable append) → sk_cnode_resize_cb 0x72d5c; sk_cnode_alloc_object_and_cap 0x7acd8 → sk_cnode_table_contains_id 0x7b0cc + sk_cnode_table_index_of 0x7b134; sk_cnode_buffer_append_all 0x7985c → sk_cnode_buf_reserve2 0x7b4e8; entry offset lookup 0x79a88; entry teardown 0x792d8 (releases all retained fields).
- Security cores (see findings [SK18-ringminus1]): allocObjectAndCap 0x7acd8 (fail-closed relocated-cap / object-type / generic-entry allocation gates), entry_build 0x7a718 (overflow-checked index/stride math), init 0x78880 (single-time root space-cap + fault-data setup).
- Swift-runtime callees (0x36b118 release, 0x36b270 retain, 0x3a261c COW unique, 0x377824/0x377bec string convert, accessor-state helpers 0x7c0xx) are extern (FUN_ addresses in comments); bodies owned by sibling SK wave workers.

## Batch SK13 (0x65640-0x6a414) — cL4 Secure Kernel device-tree parser + DeviceTreeKit helpers (osfmk/arm64/sk/sk_slice_13.c)
- 120 functions decompiled (range fully covered) — cL4's device-tree integrity parser (Apple device_tree.c) plus the DeviceTreeKit node-name/property/children iterators and the Swift-runtime growable-buffer (16/24/32-byte element) and hex/string-render helpers built on them.
- Core edges: dt_find_entry 0x65640 (keyed list lookup) → FUN_00115080(size)/FUN_00114d10(compare); dt_build_root_iter 0x656f8 → dt_validate_root 0x657ac → dt_validate_range 0x65838 → dt_range_make 0x65a3c; dt_integrity_parse 0x658f0 → dt_list_at 0x66178 / dt_node_get 0x65bc4 / dt_node_name_propcount 0x65d98 / dt_iter_advance 0x65ec0; dt_walk 0x660bc (recursive subtree walk) → dt_children 0x65f48; dt_find_child 0x65dec → dt_name_compare 0x65d18.
- DeviceTreeKit layer: dtk_collect_props 0x69bdc / dtk_collect_names 0x69a14 / dtk_collect_from_list 0x69e10 / dtk_collect_children 0x688cc → growable vectors dtk_vec_alloc16/24/32 (0x694ec/0x69560/0x69470) → reserve/copy/memmove (0x695e4, 0x696a8, 0x69770/0x697e4/0x69858/0x698cc, 0x69970/0x699a4/0x699d8); tree dump 0x66be4 + hex render 0x67edc; report/child classify 0x68cd0; key/value deep compare 0x68ef8/0x690f0.
- Security cores (see findings [ringminus1/SK13]): DT integrity parse 0x658f0 and node iterator 0x65c30 (fail-closed bounds/overflow checks on DT-derived descriptors), prop collector 0x69bdc (per-node property-count/negative-length rejection).
- Swift-runtime callees (0x36b270 retain, 0x36b118 release, 0x3a25d4 masked release, 0x3a261c COW-unique, 0x36a940 buffer alloc, 0x3xxxxx string/vector primitives) are extern (FUN_ addresses in comments); bodies owned by sibling SK wave workers.

## Batch SK188 (0x004081cc-0x0040a9f4) — cL4 Secure Kernel Swift L4 async-runtime / job machinery (osfmk/arm64/sk/sk_slice_188.c)
- 120 functions decompiled (range fully covered) — Swift L4 async runtime: error-code slot machinery, job/future builder, enqueue/destroy, and a block of stored-property accessor witnesses for the async job object.
- Core edges: sk_err_reply_build 0x4085c0 (double-word CAS finalise bit 0x800 on job status 0x60/0x68; slow path 0x40c0f8/0x40bda0) → error slot globals s_L4_ErrorCodePermissionInvalid 0x0068a6b8 / OperationInvalid 0x0068a698; sk_run_job 0x4095a0 → sk_build_front 0x40bdd0/sk_build_cb 0x40af00 + error slot pump (0x408834/0x408ae4/0x408864); sk_job_build 0x409e90 → sk_future_get 0x4097cc + timer/async finalisers (0x40c970/0x40c3a4/0x40c4b0/0x40c748/0x40eef8/0x40f5c0); sk_job_enqueue 0x4098c8 → async-arg forward 0x40cfd0; sk_run_inline 0x409c24 → sk_job_build + sk_job_destroy 0x4099d4; sk_job_alloc 0x40a8d8 / sk_job_alloc2 0x40a9f4 → CAS callback 0x40c09c; refcount release sk_ref_dec 0x4090f0 → 0x53aa0 + swift obj free 0x36b6ac.
- Security cores (see findings [sk]): data-race detector 0x4088d8 (installs raw-instruction trampoline via 0x369b04; fatal 0x116d60), error-reply indirect callback obj+0x38 (0x4085c0), job_alloc arbitrary fn-ptr invoke (0x40a8d8).
- Swift-runtime/error callees (0x40bb18 alloc, 0x40bd24 free, 0x40bcf8/0x101a0 alloc, 0x36b270 retain, 0x36b118 release, 0x377824/0x377dcc string convert, 0x4ba640 fatal, error-code slot allocators at 0x0068a6b8/0x0068a698) are extern (FUN_ addresses in comments); bodies owned by sibling SK wave workers.

## Batch SK189 (0x0040aa98-0x0040fcb4) — cL4 _Concurrency runtime (osfmk/arm64/sk/sk_slice_189.c)
- 120 functions decompiled (range fully covered) — the embedded Swift `_Concurrency` runtime: continuation registry, TaskGroup result store, task-local storage, and actor executors.
- Core edges: sk_task_continuation_init 0x40ab60 → sk_registry_add 0x40b724 (hash-set insert) → sk_hashtable_resize 0x37d700; resume/suspend CAS core sk_cont_suspend 0x40bed0 ↔ sk_cont_wake_loop 0x40bdd0 (task +0x60/+0x68 state record); TaskGroup child-add 0x40d098 / wait 0x40d99c / child-end 0x40de9c → result ring sk_task_group_store 0x40e2f0 / sk_cont_record_pop 0x40e258 → sk_cont_result_dispatch 0x40eac8; task-local store init 0x40cfec / collect 0x40eef8 / value alloc 0x40f0cc / RB-tree sk_tl_buf_insert 0x40f718 + rebalance 0x40f82c; actor executor enqueue 0x40f9f4 / dequeue 0x40faac.
- Security cores (see findings [SK189-ringminus1]): TaskGroup child delivery 0x40de9c (kind-gated result, NULL-waiter fatal), actor executor enqueue 0x40f9f4 (null-job/executor fatal), continuation registry 0x40b724 (bounds-trapped insert).
- Swift-runtime callees (0x36a804 alloc, 0x36b118 release, 0x36b270 retain, 0x37a48c/0x37a978 atomic enter/exit, 0x3a2578 fatal, 0x3d5338 executor enq, C11 mtx/cnd 0x118148/0x118164/0x118194/0x1180fc/0x11812c, error-string 0x116bb4/0x1131f4/0x112db4/0x112e8c) are extern (FUN_ addresses in comments); bodies owned by sibling SK wave workers.

## Batch SK-BOOT (0x0-0x80000) — cL4 Secure Kernel boot/early-init region (osfmk/arm64/sk/sk_region_boot.c + slice files)
- 2487 functions decompiled (range fully covered) — kernel entry/reset, boot launcher, libmalloc zone/buddy page allocator bootstrap, TCB/capability-buffer/transport bootstrap, tightbeam message layer, vspace/span-map/region layer, syscall/exception/IPC/CNode dispatch, altstack/boot-phase machinery.
- Core boot edges: sk_boot_launcher_entry 0x12d4 (diag marker, tick init, platform setup) → sk_launcher_root 0x1378 (UUID/slide print, page-map via CallSupervisor svc 0x0, symbol-table commit) → sk_boot_run 0x17f4 (method tables, CNode/caps, device tree, SAS/SAAS wiring) → sk_boot_finish 0x25ac (boot-done flag DAT_006adfd0); sk_boot_ec_switch_impl 0x16b4 (boot EC switch, breakpoint 0x5519).
- Allocator: sk_slab_alloc 0x2e50 → sk_slab_alloc_core 0x3280 (freelist + bitmap carving) ↔ sk_slab_free 0x38ac; sk_zone_ctor 0x6630 → sk_zone_boot_layout 0x2a10 (arena/node layout); sk_zone_slab_alloc 0x5324 dispatch by size; sk_zone_free 0x5a94.
- Vspace/span: sk_vspace_root 0x32514 (&DAT_0064c3f0) → sk_vspace_create_object 0x32520 → sk_vspace_alloc_and_link 0x30fb0; sk_span_lookup_build 0x35ba0/0x36008; span merge 0x367a8, split 0x3abf4, attach 0x3afe4; region create 0x3c56c / map 0x3d438 / unmap 0x3da18.
- IPC/transport: sk_ipc_msg_dispatch 0x60f60 → sk_ipc_transfer 0x610b8; tightbeam transport init 0x20134 → append 0x20448 → decoder 0x259c0 / encoder 0x22d60.
- Capability: sk_cap_validate 0x3e440 / release 0x3e4c0 / revoke 0x3e5f0; sk_cnode_alloc_cap 0x7acd8 (strings CNodeAllocator); roottask metadata serialize/deserialize 0x7cb88/0x7d3e8.
- Boot-phase barrier: sk_boot_phase_enter 0x60570 / notify 0x605f8 / drain 0x60650 (DAT_006ad900); sk_boot_main 0x60728 (handler table DAT_006b26d8).

## Sk190 (0x40fd2c-0x4158ac, Swift object-service region)
- 0041001c -> 0041144c, 00411930, 00411d40, 00412248 (object compare dispatch)
- 00410414 -> 0041360c, 0041235c, 00413b68 (per-type dispatch)
- 004108a0 -> 00413b68 family (service descriptor build)
- 00411cc4 -> 00413b68 (root dispatcher -> typed handler)
- 0041465c -> 00462b80, 002a0cf8 (syscall-number decode)
- 00413b68 -> 00414dec, 00414bf4, 004150e8 (typed Swift value encoding)
- cross-region helpers: 0036b270/0036b118 (alloc/free), 002a0cf8 (flag check), 002298d4 (logger)

## SkGap07 (0x0034f22c-0x0034fb14, Swift-runtime stub region)
- 0034f6a8 -> 001afa84 (swift_string_fatal_precondition; GraphemeBreaking fatal)
- 0034fa9c -> 001afa84 (swift_string_fatal_precondition; FloatingPointToString fatal)
- 0034f958 -> 001a89a8 (swift_small_string_encode; "Cannot initialize")
- 0034f6dc -> 00376820 (sk_obj_resolve_forward; &DAT_004eb948)
- 0034f6f8 -> 00376820 (sk_obj_resolve_forward; &DAT_004ead58)
- 0034f714 -> 0006a4c0 (shared helper)
- 0034f7ec -> 0036a940 (0x66aa10,0x20,0xf)
- 0034f9b4 -> 00002534 (0x6560e8,&DAT_004e7ed0)
- 0034fadc -> 003246ec, 003722e4
- 0034fb14 -> 001fab14 (cl4_sched_grow_capacity)

## SkGap18 (0x00357bf8-0x0035841c, frame-fragment / forwarding-stub region)
- 00357bf8 -> 00365b6c (tail-call forwarding stub)
- 00357c04 -> 00027754 (x3 triple init/teardown sequence)
- 00357c2c -> 000026e8 ([stack+8] slot init)
- 00357c58 -> 00310a74, 0001df60 (two-phase state transition)
- 00357c88 -> 000a6b64 (tail-call forwarding stub)
- 003581d4 -> 002298d4 (thunk, x3)
- 003581fc -> 00376820 (tail-call forwarding stub)
- 00358318 -> 001a0354 (0,1)
- 00358358 -> 001b7524 (param, x29-0x80)
- 00358388 -> 00377bec (three caller-frame words)
- 003583a4 -> 00312d08 (reordered 7-arg dispatch)
- 003583c0 -> 001da714 (x29-0xd0)
- 00358404 -> 00117d14 (tail-call forwarding stub)
- 00358410 -> 00377824 (0xff)
- 00357cc8 -> data s_Swift_ExistentialCollection_swif_005cf680 (Swift existential pair ctor)
- 00357f34 / 003580a4: pte->canonical fixup + capability-word masking leaves

## SkGap11 (0x00351d24-0x00353118, leaf/thunk/helper run)
- 00351d4c -> FUN_001a842c, FUN_00229ebc (hash/PRF round callers)
- 00351ee0 -> 00310b08 (swift_type_metadata_field_14 forwarding thunk)
- 00351ef8 -> 00027754 (boot-region helper forwarding thunk)
- 00351fe0 -> 00310a74 (swift_type_metadata_field_30) then 0001df60
- 003522e4 -> 00310a74 then 0001df60
- 003523bc -> 00310a74 then 0001df60 (after frame store)
- 00351fd0 <- 0022ceac, 0022cf60, 0022cff0, 0022d080, 0022d118, 002a4ab4 (tagged-ptr build)
- 0035239c <- 002b45a8, 002b7808, 002b7830 (pair builder)
- 003521a4 -> &DAT_00657778 (global address init)

## SkR07 (0x3d2f10-0x3d952c, Swift stdlib + _Concurrency async/executor runtime)
- 003d2f10 -> 0038df24 (str_format) + 004b9d68 (ref_take) + 00012568 (print thunk) + 003d2e80 (print dispatch)
- 003d2ffc / 003d3dd8 (once token) -> 003d3e94 (mtx_lock) + 003d3ed0 (mtx_unlock) + 001180e0/0011812c (cnd_broadcast/wait on 0x6c0b40)
- 003d3f0c (once init) -> 00118148 (mtx_init) + 001180fc (cnd_init) on globals 0x6c0b30/0x6c0b40
- 003d3200 (nan/snan token detect) <- 003d3130/003d30c4 (float/double parser) <- 003d319c (float parse)
- Unicode property index: 003d326c/003d3398 (bitmap/popcount) <- 003d3470/351c/3550/35b0/35f0/37a4/37f0/3838/38c4/3c1c/3c88
- 003d3964 (lowercase mapping) uses DAT_0050a214/DAT_00532a14/DAT_0056adec/DAT_005781a0
- async task setup: 003d62dc/003d71b8/003d85b8/003d93f8 -> 00377824 (job build, metadata 00614a5c) -> 003d5a4c/003d69f8/003d7c18/003d8cc0 (suite enter/run)
- async completion/fatal: 003d4d0c/003d4dbc/003d4f18/003d4f78 -> 001afa84 (cL4_runtime_fatal, noreturn)
- executor permits: 003d6418/003d72f0 -> 003d6470 (post-release) -> 003dd540; negative count traps
- SKR22 fragment helpers: 0x464090/0x464918 -> FUN_0029fa0c / FUN_00461894 (vspace/page-walk); 0x4645a4/0x464630/0x464890/0x4647f4 -> FUN_00117cc4 (memcpy); 0x464354/0x464550 -> thunk_FUN_0036b270 (retain); 0x464224/0x4645f8 -> thunk_FUN_002acbb8 (report emit); 0x464268/0x4642a8 -> FUN_0042ec68; 0x464520/0x464538 -> FUN_002a4ab4; 0x4644e8/0x4648fc -> FUN_001a84f4

## SKR32 (0x0049a51c-0x0049ee70) — object-table / hash-set layer
- 0x0049a91c set-lookup-word → 0x0049ac48 commit-word → 0x000b3910 set-mark
- 0x0049aa14 set-lookup-int → 0x0049ad48 commit-int → 0x0049c0a8 set-mark-int
- 0x0049ab00 map-lookup-pair → 0x0049ae44 commit-pair → 0x000b394c set-mark-pair
- grow/rehash: 0x0049af70 (word) / 0x0049b180 (int) / 0x0049b390 (pair); compact: 0x0049b5b8/0x0049b6fc/0x0049b840; in-place: 0x0049b99c/0x0049bbf0/0x0049be44
- grow allocators: 0x0025a840 (array grow), 0x0025b994 (bucket realloc), 0x00258c60 (grow)
- 0x0049c0e4 dict insert → 0x00499f0c (key pair) / 0x00499fcc (release) / 0x00258c60
- 0x0049c200 vec remove → 0x0049a348 / 0x00498500 (memmove) / 0x0035bc70 (memset)
- teardown dispatchers: 0x0049c904 / 0x0049d538 / 0x0049d320 / 0x0049d690 → 0x004592dc/0x00459138/0x0045a1f8/0x0045a4b4
- big dispatch: 0x004aac88 (12-16 w) / 0x004ab67c (6-8 w) / 0x004abb1c (4 w)
- launch-image pipeline: 0x0049d8a8/0x0049dac8 → 0x0008e518 (launch pair) → 0x0008e500 (report)

## SKR33 (0x0049eee8-0x004a36fc) — frame/context bookkeeping + message-send dispatch (120 fns)
- context-open/migrate: 0x0049eee8/0x0049f318/0x0049f2ac/0x004a18e8/0x004a1624/0x004a16bc/0x004a17d0 → 0x004ab150 (pair), 0x0036b118 (release), 0x003a25d4
- message-send/refill trampolines: 0x0049ef90/0x0049f05c/0x0049f144/0x0049fd8c/0x0049ff7c/0x004a0058/0x004a00f4/0x004a0d6c/0x004a0eb8/0x004a0f64/0x004a1010/0x004a10bc → 0x00350c5c (pair), 0x00377824, 0x004aa47c, 0x004aa914, 0x0009461c (pair), 0x00117cc4
- dispatch helpers: 0x004a1d6c/0x004a1e84/0x004a1fb4/0x004a204c/0x004a20e4 → indirect through *(base+0x18/0x20/0x28) (unrecovered jumptable 0x4a1f18)
- variable-width packed-index decode: 0x004a217c → 0x004ac168, 0x000839f8 (uint3 3-byte reads)
- tag-lookup: 0x004a0a94 → 0x0006b438, 0x000839f8 (width from scratch reg)
- lazy init guard: 0x004a35b8 → 0x00027614, 0x00376820, global DAT_00657d98
- object-registration/check: 0x004a1cc0/0x004a07e4 → 0x00377824, 0x00377dcc, 0x004ab710 (pair), 0x003728b8
- shared callees (pair): 0x00350c5c/0x00377824/0x004aa914/0x004aa4fc/0x004ab710/0x004abf7c/0x004ac784/0x004ac7c8

## cL4 SKR30 slice (0x00490174-0x004961a0) — Swift runtime / _StringProcessing matcher
- 120 functions in `osfmk/arm64/sk/sk_slice_r30.c` (manifest: 120/120 decompiled, status file `osfmk/arm64/sk/sk_slice_r30.c`).
- Dense in-slice call cluster: sk_r30_00490268 ↔ 00490174/0049341c/0049153c/00491644/00494b44/00494810/0049490c/004934a8 (collection copy + recursive type-value walker).
- Shared Swift-runtime callees across the slice: FUN_0036b118 (release), FUN_0036b270 (retain), FUN_0036a940 (alloc/emplace), FUN_00117cc4 (memcpy), FUN_003a25d4/FUN_0049153c (dispatch).
- Guarded-entry supervisor calls rendered as `((code)0x54ffff60f100041f)(...)` (GENTER-style opaque SUB_54ffff60f100041f).
