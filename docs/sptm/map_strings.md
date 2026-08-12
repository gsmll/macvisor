# SPTM function-name string map

SPTM trace/panic macros embed the enclosing function's name as a `sptm_*`
string in `__cstring`. For each string we locate its address, then
`get_xrefs_to` that address; every `[DATA]`/`[PARAM]` xref from code lands
inside the function whose name the string is. The enclosing function
(`FUN_xxxxxxxx` in Ghidra, image base 0) is therefore the named function.

- **confidence = high**: the string is referenced from exactly one function and
  is that function's natural trace tag.
- **confidence = medium**: the string is referenced from multiple functions, or
  is co-located with several sibling name-tags inside one large function
  (sub-operation / inlined-helper tags), or is a data-global name.

Method: `switch_program sptm.raw` → `search_strings "sptm_"` (+ `txm_`/misc) →
`get_xrefs_to <string_addr>` for each. `[DATA]` = code ref, `[PARAM]` = string
passed as a panic/logging format arg.

## Resolved function-name strings

| name | string_addr | function_addr | confidence |
|---|---|---|---|
| sptm_uat_init_state | 000011f7 | FUN_000b5fd0 | high |
| sptm_uat_destroy_state | 00001280 | FUN_000b5be0 | high |
| sptm_uat_map_table | 00001305 | FUN_000b5904 | high |
| sptm_uat_unmap_table | 0000132f | FUN_000b5608 | high |
| sptm_uat_map_continue | 000013bf | FUN_000b486c | high |
| sptm_uat_prepare_fw_unmap_begin | 000013f8 | FUN_000b46bc | high |
| sptm_uat_prepare_fw_unmap_continue | 00001463 | FUN_000b4374 | high |
| sptm_uat_unmap_begin | 0000152a | FUN_000b4068 | high |
| sptm_uat_unmap_continue | 0000157d | FUN_000b32d0 | high |
| sptm_uat_set_ctx_id | 000015bf | FUN_000b2f54 | high |
| sptm_uat_remove_ctx_id | 00001607 | FUN_000b2928 | high |
| sptm_uat_get_info | 00001674 | FUN_000b26b0 | high |
| sptm_fixup | 000021e4 | FUN_000b7eec | high |
| sptm_register_cpu | 000022f5 | FUN_000b86bc | high |
| sptm_slide_region | 00002378 | FUN_000b8a3c | high |
| sptm_cpu_id | 000023d3 | FUN_000b8e68 | high |
| sptm_init | 00002411 | FUN_000b8f84 | high |
| sptm_init_txm_bootstrap_complete | 000025c0 | FUN_000bb804 | high |
| sptm_resume_cpu | 0000262c | FUN_000bc4c0 | high |
| sptm_cputrace_set_base | 00002ba4 | FUN_000bdb04 | high |
| sptm_cputrace_start | 00002bdb | FUN_000bdab4 | high |
| sptm_cputrace_stop | 00002bef | FUN_000bda44 | high |
| sptm_cputrace_va_frame_lock | 00002c02 | FUN_000bd57c | high |
| sptm_cputrace_va_frame_unlock | 00002c58 | FUN_000bd120 | high |
| sptm_cputrace_va_init | 00002c76 | FUN_000bcea0 | high |
| sptm_cputrace_va_deinit | 00002ca2 | FUN_000bcbb0 | high |
| sptm_cputrace_va_set_base | 00002cba | FUN_000bc7fc | high |
| sptm_cputrace_va_start | 00002cd4 | FUN_000bc78c | high |
| sptm_cputrace_va_stop | 00002ceb | FUN_000bc6f0 | high |
| hib_sptm_panic_func | 00003431 | FUN_000f84b4 | high |
| sptm_hib_begin | 00003647 | FUN_000bf9dc | high |
| sptm_hib_hash_hibseg_page | 00003752 | FUN_000bffc8 | high |
| sptm_hib_hash_page | 00003821 | FUN_000c06ec | high |
| sptm_hib_finalize_sk | 0000385e | FUN_000c0cec | high |
| sptm_hib_finalize_image | 000038b9 | FUN_000c0e64 | high |
| sptm_hib_verify_hash_non_wired_page | 000038d1 | FUN_000c1128 | high |
| sptm_hib_verify_finalize_non_wired_hash | 0000394f | FUN_000c12a4 | high |
| sptm_nvme_map_pages | 0000439f | FUN_000c3434 | high |
| sptm_nvme_unmap_pages | 0000447d | FUN_000c2dec | high |
| sptm_nvme_bar_admin_queue_regs | 0000450b | FUN_000c2908 | high |
| sptm_nvme_bar_ioqa_reg | 00004593 | FUN_000c2734 | high |
| sptm_nvme_bar_iosq_reg | 000045fc | FUN_000c24c8 | high |
| sptm_nvme_bar_iocq_reg | 00004631 | FUN_000c2248 | high |
| sptm_nvme_ans_sha_reg | 00004683 | FUN_000c1e94 | high |
| sptm_sart_unmap_region | 000056cc | FUN_000c5a28 | high |
| sptm_t8110dart_map_table | 000071ae | FUN_000cfaec | high |
| sptm_t8110dart_unmap_table | 00007232 | FUN_000cef24 | high |
| sptm_t8110dart_map | 00007272 | FUN_000ce144 | high |
| sptm_t8110dart_unmap | 00007320 | FUN_000cd0bc | high |
| sptm_t8110dart_init | 00007346 | FUN_000c9728 | high |
| sptm_t8110dart_powerup | 00007369 | FUN_000cacd0 | high |
| sptm_t8110dart_powerdown | 00007380 | FUN_000cc5e8 | high |
| sptm_t8110dart_query_tlb | 000073e2 | FUN_000c8554 | high |
| sptm_t8110dart_set_smmu_window | 000073fb | FUN_000c8384 | high |
| sptm_t8110dart_read_smmu_stt_index | 0000741a | FUN_000c8174 | high |
| sptm_t8110dart_clamp_tlimits | 0000743d | FUN_000c7efc | high |
| sptm_t8110dart_clear_err | 0000745a | FUN_000c8d04 | high |
| sptm_t8110dart_clear_exception | 000074c8 | FUN_000c7424 | high |
| sptm_t8110dart_disable_translation | 000074e7 | FUN_000c93d8 | high |
| sptm_t8110dart_enable_translation | 0000750a | FUN_000c8fb8 | high |
| sptm_t8110dart_enable_clock_protection | 00009dee | FUN_000cacd0 | high |
| sptm_t8110dart_skip_enable_clock_protection_write | 00009fbf | FUN_000cacd0 | high |
| sptm_t8110dart_disable_clock_protection | 0000a2af | FUN_000cc5e8 | high |
| sptm_iofilter_protected_write | 0000b979 | FUN_000d6524 | high |
| sptm_init_parse_io_space | 0000b9df | FUN_000d6860 | high |
| sptm_broadcast_tlbi | 0000c302 | FUN_000d76fc | high |
| sptm_bootstrap_tlbi | 0000c3b1 | FUN_000d7dc0 | high |
| sptm_bootstrap_finalize | 0000ceea | FUN_000dfe80 | high |
| sptm_cpu_init | 0000cfd4 | FUN_000dce04 | high |
| sptm_drop_table_refcnts | 0000d5de | FUN_000e3394 | high |
| sptm_register_dispatch_table | 0000ee7f | FUN_000e6768 | high |
| sptm_register_xnu_exc_return | 0000ef02 | FUN_000e6a50 | high |
| register_sptm_iommu_dispatch_table | 0000ef42 | FUN_000e71ec | high |
| sptm_dispatch | 0000efe5 | FUN_000e72f4 | high |
| sptm_early_platform_error | 0000f46c | FUN_000f89f8 | high |
| sptm_retype | 00011214 | FUN_000ed6b4 | high |
| sptm_map_page | 0001137d | FUN_000ee278 | high |
| sptm_map_table | 000114e0 | FUN_000efa78 | high |
| sptm_unmap_table | 00011613 | FUN_000f05e4 | high |
| sptm_surt_alloc | 000116b2 | FUN_000f1290 | high |
| sptm_surt_free | 00011726 | FUN_000f1910 | high |
| sptm_region_op | 0001177c | FUN_000f1b78 | high |
| sptm_update_region | 0001196c | FUN_000f3034 | high |
| sptm_disjoint_op | 000119d5 | FUN_000f3144 | high |
| sptm_update_disjoint_multipage | 00011a96 | FUN_000f3998 | high |
| sptm_configure_shared_region | 00011af7 | FUN_000f3f60 | high |
| sptm_set_shared_region | 00011b47 | FUN_000f4188 | high |
| sptm_nest_region | 00011be6 | FUN_000f458c | high |
| sptm_unnest_region | 00011cef | FUN_000f4eec | high |
| sptm_switch_root | 00011d40 | FUN_000f57c8 | high |
| sptm_guest_stage1_tlb_op | 00011d6e | FUN_000f5f2c | high |
| sptm_guest_exit | 00011d8a | FUN_000f6634 | high |
| sptm_batch_sign_user_pointer | 00011e2a | FUN_000f6e30 | high |
| sptm_tag_op | 00011e6d | FUN_000f719c | high |
| sptm_tag_papt_multipage | 00011ef4 | FUN_000f7880 | high |
| sptm_untag_papt_multipage | 00011f2b | FUN_000f78e0 | high |
| sptm_guest_dispatch | 00011f45 | FUN_000f7924 | high |
| sptm_guest_va_to_ipa | 00012047 | FUN_000f7cc0 | high |
| sptm_leaf_table_condemn_op | 0001233a | FUN_000f0d50 | high |
| sptm_guest_enter | 000127fd | FUN_000f6368 | high |
| validate_sptm_cputrace_mode | 000128ee | FUN_000bdd48 | high |
| sptm_determine_kernel_ctrr | 000027b9 | FUN_000b8f84 | medium (co-located in sptm_init FUN_000b8f84) |
| sptm_init_mte_boundaries | 00002a08 | FUN_000b8f84 | medium (co-located in sptm_init FUN_000b8f84) |
| sptm_parse_io_ranges | 0000b94e | FUN_000dcf80 | medium (co-located w/ many io tags) |
| sptm_parse_io_filters | 0000b963 | FUN_000dcf80 | medium (co-located w/ many io tags) |
| sptm_compute_io_ranges | 0000ba9f | FUN_000dcf80 | medium (co-located w/ many io tags) |
| sptm_load_io_ranges | 0000bcd9 | FUN_000dcf80 | medium (co-located w/ many io tags) |
| sptm_register_io_frame | 0000bd5c | FUN_000dcf80 | medium (co-located w/ many io tags) |
| sptm_validate_io_ranges | 0000bed3 | FUN_000dcf80 | medium (co-located w/ many io tags) |
| sptm_compute_io_filters | 0000beeb | FUN_000dcf80 | medium (co-located w/ many io tags) |
| sptm_load_io_filters | 0000bf88 | FUN_000dcf80 | medium (co-located w/ many io tags) |
| sptm_validate_io_filters | 0000bff3 | FUN_000dcf80 | medium (co-located w/ many io tags) |
| validate_sptm_io_filter_protected_write_size | 0000c00c | FUN_000d6524 | medium (co-located in sptm_iofilter_protected_write) |
| sptm_io_filter_protected_write_size | 0000c039 | FUN_000d6524 | medium (co-located in sptm_iofilter_protected_write) |
| validate_sptm_io_filter_protected_paddr | 0000c05d | FUN_000d6524 | medium (co-located in sptm_iofilter_protected_write) |
| sptm_io_filter_protected_paddr | 0000c085 | FUN_000d6524 | medium (co-located in sptm_iofilter_protected_write) |
| sptm_find_io_filter_entry | 0000c0a4 | FUN_000d6524 | medium (co-located in sptm_iofilter_protected_write) |
| sptm_init_register_allow_io_range | 0000c0ed | FUN_000d6860 | medium (co-located in sptm_init_parse_io_space) |
| sptm_bootstrap_early | 0000cacf | FUN_000d9ec8 | medium (co-located w/ parse_cpu_ranges) |
| sptm_bootstrap_late | 0000cda0 | FUN_000dcf80 | medium (co-located w/ many io tags) |
| sptm_parse_cpu_ranges | 0000d065 | FUN_000d9ec8 | medium (co-located in sptm_bootstrap_early) |
| sptm_update_disjoint | 00011a2c | FUN_000f38c8 | medium (also referenced from FUN_000f3998) |
| sptm_update_papt | 00012599 | FUN_000f3998 | medium (co-located in sptm_update_disjoint_multipage) |
| validate_sptm_dispatch_table_id | 0000f88d | FUN_000e71ec | medium (also referenced from FUN_000e6768) |
| validate_sptm_ptrauth_user_key | 0001283e | FUN_000f6d54 | medium (also referenced from FUN_000f6e30/000f7108) |

**Resolved count: 125** (101 high + 24 medium).

## Format / panic strings → panicking function (skipped as name tags)

These contain `%`/spaces; they are panic/trace format strings. The function that
passes the string is the panicking function (evidence `[PARAM]`).

| format string | string_addr | panicking function | evidence |
|---|---|---|---|
| %s: FTE %p should be held exclusive by sptm_retype() | 00001127 | FUN_000ed6b4 (sptm_retype) | xref 000ee0d8 [PARAM] |
| %s: The ASC carveout region is smaller than a page ... | 00001891 | FUN_000b6524 | xref 000b74f8 [PARAM] |
| %s: The TTBR1 shared L2 region size (0x%llx) ... | 0000192d | FUN_000b6524 | xref 000b7510 [PARAM] |
| %s: The TTBAT is smaller than a page ... | 0000199d | FUN_000b6524 | xref 000b7528 [PARAM] |
| %s: The Handoff region is smaller than a page ... | 00001a19 | FUN_000b6524 | xref 000b755c [PARAM] |
| %s: assert '!(region_start & SPTM_PAGE_MASK)' failed. | 00002e27 | FUN_000bd120 / FUN_000bd57c | xrefs 000bd3c0, 000bd74c |
| %s: assert 'region_size >= SPTM_PAGE_SIZE' failed. | 00002f79 | FUN_000bd120 | xref 000bd470 [PARAM] |
| %s: sptm_pmap_io_ranges ... overlap. | 0000be76 | FUN_000dcf80 | xref 000dd558 [PARAM] |
| %s: sptm_first_dram is not page-aligned | 0000cc4a | FUN_000d9ec8 (sptm_bootstrap_early) | xref 000dca00 [PARAM] |
| %s: sptm_last_dram is not page-aligned | 0000cc72 | FUN_000d9ec8 (sptm_bootstrap_early) | xref 000dca18 [PARAM] |
| %s: ASID 0x%hx was already clear in sptm_asid_bitmap | 0000d7d7 | FUN_000e1acc | xref 000e1cb8 [PARAM] |
| %s: VMID 0x%hx was already clear in sptm_vmid_bitmap | 0000d8b7 | FUN_000e1810 | xref 000e1a48 [PARAM] |
| %s: invalid bootstrap frames type %d ... | 0000e052 | FUN_000e41bc | xref 000e43c8 [PARAM] |
| %s: SPTM_UPDATE_DEFER_TLBI passed for untag operation?! | 00011ebc | FUN_000f719c (sptm_tag_op) | xref 000f7470 [PARAM] |

Additional assert-expression strings (`0000fea8` … `0001112c`, the
`!sptm_add_overflow(...)` / `!((uint64_t)...)` / `(… & SPTM_PAGE_MASK)==0`
family) are panic assertions inside the SPTM HIB / page-table code; they embed
sub-expressions (not function names) and are omitted from the name map.

## Data-global names (excluded from function map)

These strings name global data/variables referenced from many functions, not
functions:

| name | string_addr | referenced from |
|---|---|---|
| sptm_n_cpus | 0000231f | FUN_000b86bc (sptm_register_cpu) |
| sptm_root_table_paddr | 00011624 | FUN_000f05e4 (sptm_unmap_table) |
| sptm_first_tag_storage_paddr / sptm_last_tag_storage_paddr | 0000d9c0 / 0000d9dd | FUN_000e0f00 |
| sptm_first_phys / sptm_last_phys | 00012084 / 00012094 | many (data) |
| sptm_num_asids | 0001245b | FUN_000e1d28, FUN_000f1290 |
| sptm_iommu_reg_base | 0000e718 | FUN_000e63c8 |
| sptm_cpu_data_ptr_fast (in `calling_domain(sptm_cpu_data_ptr_fast())`) | 000112a4 | — |
| txm_stack | 0000ee5d | — |

## Unresolved / notes

- Source/header path strings (`sptm_init.c`, `sptm_hibentry.c`, `sptm_io.c`,
  `sptm_page_tables.c`, `sptm_types.c`, `sptm_misc.c`, `sptm_internal.h`,
  `sptm_validation.h`, `sptm_types.h`, `sptm_concurrency.h`, and the
  `/AppleInternal/.../SPTM/sptm/core/sptm_hibentry.c` build path) are debug
  filename tags, not function names — excluded.
- Enum/constant name strings (`EXEC_MODE_SPTM_DEFAULT`, `SPTM_UNTYPED`,
  `SPTM_PAGE_TABLE`, `VIOLATION_*`, `STATE_*`, `EVENT_*`, `DISPATCH_ID_SPTM_CORE`,
  `TXM_*` frame types) are symbol-table / state names, not function tags —
  excluded.
- No `sptm_` function-name string had xrefs landing outside a function body;
  every candidate string's xrefs resolved to a known `FUN_*`. The only
  ambiguity is the co-located multi-tag functions noted above (FUN_000dcf80,
  FUN_000d9ec8, FUN_000b8f84, FUN_000d6524, FUN_000f3998), where several
  sub-operation name-tags share one enclosing function — these are most likely
  inlined helpers whose trace tags were folded into the parent body.
