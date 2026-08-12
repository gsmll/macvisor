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
