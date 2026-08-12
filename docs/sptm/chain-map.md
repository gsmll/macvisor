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
