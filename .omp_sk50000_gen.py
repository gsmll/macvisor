#!/usr/bin/env python3
import re, os, glob, json, sys

RAW = "/Users/gabesmall/macvisor/.omp_sk50000_raw"
LIST = "/Users/gabesmall/macvisor/.omp_local_sk_50000.txt"
OUT  = "/Users/gabesmall/macvisor/osfmk/arm64/sk/sk_region_boot_50000.c"

ADDRS = []
with open(LIST) as f:
    for line in f:
        parts = line.split()
        if parts: ADDRS.append(parts[-1])

# ---------- NAME MAPS ----------
FUN_NAMES = {
"0x5a1c4":"svc_dispatch_3arg","0x5a940":"svc_dispatch_3arg_b",
"0x5a2e8":"svc_repeat_on_suspend_1","0x5a318":"svc_repeat_on_suspend_2",
"0x5a348":"svc_repeat_on_suspend_3","0x5a378":"svc_repeat_on_suspend_4",
"0x5a3a8":"svc_repeat_on_suspend_5","0x5aa64":"svc_repeat_on_suspend_6",
"0x5aa94":"svc_repeat_on_suspend_7","0x5aac4":"svc_repeat_on_suspend_8",
"0x5aaf4":"svc_repeat_on_suspend_9","0x5ab24":"svc_repeat_on_suspend_10",
"0x5a3d8":"svc_set_arg_repeat_on_suspend","0x5ab54":"svc_set_arg_repeat_on_suspend_b",
"0x5a40c":"fill_cap_dispatch_table",
"0x5acac":"sk_global_get","0x5baac":"sk_lookup_thread_obj","0x5ba5c":"sk_register_global",
"0x5bb68":"sk_kernel_get","0x5ba14":"sk_kernel_head","0x5b860":"sk_kernel_state_get",
"0x5b89c":"sk_kernel_field_40","0x5b8c8":"sk_format_uuid","0x5bb7c":"sk_list_head",
"0x5baf0":"sk_list_push","0x5bd10":"sk_list_push_28","0x5bce0":"sk_register_cb",
"0x5bd7c":"sk_iter_list_cb","0x5be48":"sk_kernel_set_70","0x5be84":"sk_waitq_enqueue",
"0x5bf20":"sk_waitq_dequeue","0x5c0ac":"sk_waitq_dequeue_all","0x5bbd8":"sk_strtok",
"0x5bc48":"sk_range_lookup","0x5c184":"sk_log_append","0x5c278":"sk_log_consume",
"0x5c16c":"sk_register_global_2","0x5ba40":"sk_register_global_3",
"0x5b190":"sk_panic_msg","0x5b1b0":"sk_panic","0x5b824":"sk_format_vsnprintf",
"0x60524":"sk_current_thread","0x5dc4c":"sk_cpu_array","0x5dab8":"sk_ipc_call_guard",
"0x5dfa8":"sk_ipc_msg_frame","0x5d64c":"sk_msg_send","0x5db7c":"sk_msg_release",
"0x5dc8c":"sk_lock_dispatch_10","0x5dd70":"sk_lock_dispatch_18","0x5ce54":"sk_unlock",
"0x5d38c":"sk_lock_acquire","0x5cc3c":"sk_lock_acquire_recursive","0x5d394":"sk_lock_release",
"0x5cb9c":"sk_lock_prepare","0x5cdbc":"sk_lock_try","0x5cf08":"sk_lock_set_mode","0x5cf14":"sk_lock_init",
"0x5c650":"sk_error_from_code","0x5cf4c":"sk_notify_domain","0x5d03c":"sk_notify_domain_slot",
"0x5c924":"sk_error_to_word","0x5c86c":"sk_error_classify","0x5ca20":"sk_errno_name",
"0x5c5b4":"sk_cap_word_lookup","0x5c614":"sk_method_handle","0x5c710":"sk_dispatch_reset",
"0x5c764":"sk_dispatch_record","0x5c5a0":"sk_dispatch_default","0x5c588":"sk_dispatch_error_print",
"0x5cb18":"sk_set_cap_class","0x5cb24":"sk_cap_record","0x5e958":"sk_syscall_name",
"0x5ee40":"sk_shift_0","0x5ee48":"sk_shift_1","0x5ee50":"sk_shift_2",
"0x5ee58":"sk_shift_multi","0x5ee7c":"sk_shift_dispatch","0x5eec4":"sk_syscall_cap_dispatch",
"0x5e100":"sk_syscall_handler","0x5e0dc":"sk_syscall_entry","0x5e4ac":"sk_syscall_exit",
"0x5e4cc":"sk_syscall_restore","0x5e4d8":"sk_syscall_print","0x5e8a4":"sk_buf_advance",
"0x5ea94":"sk_syscall_table_lookup","0x5eb78":"sk_syscall_table_lookup2","0x5ec20":"sk_syscall_set_table",
"0x5ec98":"sk_syscall_get_table","0x5ed18":"sk_syscall_set_handlers","0x5edac":"sk_syscall_set_handlers2",
"0x5fd2c":"sk_current_cpu","0x5fdac":"sk_cpu_state_check","0x5fe48":"sk_state_enter",
"0x5fea8":"sk_state_exit","0x5ff04":"sk_alloc_stack_frame","0x5fac0":"sk_restore_ctx",
"0x5fad8":"sk_restore_ctx1","0x5fbc0":"sk_restore_ctx2","0x5fbdc":"sk_save_ctx",
"0x5fc54":"sk_save_ctx2","0x5fccc":"sk_restore_ctx3","0x5fd24":"sk_restore_ctx4",
"0x54624":"sk_setup_cpu_regs","0x52a04":"sk_init_cpu_region","0x52c54":"sk_init_cnodes",
"0x52718":"sk_boot_finish","0x52940":"sk_init_stage","0x5295c":"sk_init_stage2",
"0x52968":"sk_init_stage3","0x5296c":"sk_init_stage4","0x52994":"sk_init_check",
"0x529a0":"sk_init_result","0x529d4":"sk_init_result_word","0x528c4":"sk_domain_notify",
"0x53aa0":"sk_cpu_start","0x53aa4":"sk_cpu_startup","0x53ae0":"sk_cpu_init",
"0x53af4":"sk_cpu_ready","0x53b28":"sk_cpu_wait","0x53a14":"sk_cpu_boot",
"0x53a30":"sk_cpu_boot_get","0x53a60":"sk_cpu_cmp","0x533ec":"sk_cpu_irq",
"0x53418":"sk_cpu_irq2","0x53444":"sk_cpu_irq3","0x53470":"sk_cpu_irq4",
"0x53484":"sk_cpu_irq5","0x534c0":"sk_cpu_irq6","0x534ec":"sk_cpu_irq_slot",
"0x53568":"sk_boot_done","0x53598":"sk_boot_arg","0x53634":"sk_boot_triple",
"0x5371c":"sk_boot_state","0x537c4":"sk_boot_list","0x53858":"sk_boot_putc","0x538c8":"sk_boot_puts",
"0x539c0":"sk_obj_cmp","0x539cc":"sk_obj_get","0x539fc":"sk_obj_put",
"0x54354":"sk_tcb_abort","0x543c4":"sk_tcb_x","0x543f4":"sk_tcb_y",
"0x54414":"sk_tcb_z","0x54418":"sk_tcb_w","0x54464":"sk_tcb_v",
"0x54610":"sk_tcb_cur","0x54960":"sk_tcb_set","0x55164":"sk_tcb_clear",
"0x5526c":"sk_tcb_get","0x55288":"sk_tcb_peek","0x552a4":"sk_tcb_a",
"0x552c0":"sk_tcb_b","0x5530c":"sk_tcb_c","0x55328":"sk_tcb_d",
"0x55344":"sk_tcb_e","0x55360":"sk_tcb_f","0x5537c":"sk_tcb_g",
"0x553b0":"sk_tcb_h","0x553e4":"sk_tcb_i","0x55420":"sk_tcb_j",
"0x55454":"sk_tcb_k","0x55488":"sk_tcb_l","0x554bc":"sk_tcb_m",
"0x554f0":"sk_tcb_n","0x55524":"sk_tcb_o","0x55558":"sk_tcb_p",
"0x555ac":"sk_tcb_q","0x555f8":"sk_tcb_r","0x5562c":"sk_tcb_s",
"0x55660":"sk_tcb_t","0x55694":"sk_tcb_u","0x556c8":"sk_tcb_v2",
"0x556e4":"sk_tcb_w2","0x55718":"sk_tcb_x2","0x5574c":"sk_tcb_y2",
"0x55780":"sk_tcb_z2","0x5579c":"sk_tcb_ab","0x557e8":"sk_tcb_ac",
"0x55824":"sk_tcb_ad","0x55858":"sk_tcb_ae","0x55874":"sk_tcb_af",
"0x558c0":"sk_tcb_ag","0x5590c":"sk_tcb_ah","0x55948":"sk_tcb_ai",
"0x5597c":"sk_tcb_aj","0x559b8":"sk_tcb_ak","0x55a24":"sk_tcb_al",
"0x55a90":"sk_tcb_am","0x55afc":"sk_tcb_an","0x55b20":"sk_tcb_ao",
"0x55b44":"sk_tcb_ap","0x55b60":"sk_tcb_aq","0x55b7c":"sk_tcb_ar",
"0x55ee0":"sk_tcb_as","0x56004":"sk_tcb_at","0x56034":"sk_tcb_au",
"0x56064":"sk_tcb_av","0x56098":"sk_tcb_aw",
"0x565c4":"sk_cap_op_a","0x566e8":"sk_cap_op_b","0x56718":"sk_cap_op_c",
"0x56748":"sk_cap_op_d","0x56778":"sk_cap_op_e","0x567a8":"sk_cap_op_f",
"0x567d8":"sk_cap_op_g","0x5680c":"sk_cap_cmp","0x56d3c":"sk_cap_op_h",
"0x56e60":"sk_cap_op_i","0x56e90":"sk_cap_op_j","0x56ec0":"sk_cap_op_k",
"0x56ef0":"sk_cap_op_l","0x56f20":"sk_cap_op_m","0x56f50":"sk_cap_op_n",
"0x56f84":"sk_cap_cmp2","0x574c0":"sk_cap_op_o","0x575e4":"sk_cap_op_p",
"0x57614":"sk_cap_op_q","0x57644":"sk_cap_op_r","0x57674":"sk_cap_op_s",
"0x576a4":"sk_cap_op_t","0x576d4":"sk_cap_op_u","0x57708":"sk_cap_cmp3",
"0x57c44":"sk_cap_op_v","0x57d68":"sk_cap_op_w","0x57d98":"sk_cap_op_x",
"0x57dc8":"sk_cap_op_y","0x57df8":"sk_cap_op_z","0x57e28":"sk_cap_op_aa",
"0x57e58":"sk_cap_op_ab","0x57e8c":"sk_cap_cmp4","0x583c4":"sk_cap_op_ac",
"0x584e8":"sk_cap_op_ad","0x58518":"sk_cap_op_ae","0x58548":"sk_cap_op_af",
"0x58578":"sk_cap_op_ag","0x585a8":"sk_cap_op_ah","0x585d8":"sk_cap_op_ai",
"0x5860c":"sk_cap_cmp5","0x58b44":"sk_cap_op_aj","0x58c68":"sk_cap_op_ak",
"0x58c98":"sk_cap_op_al","0x58cc8":"sk_cap_op_am","0x58cf8":"sk_cap_op_an",
"0x58d28":"sk_cap_op_ao","0x58d58":"sk_cap_op_ap","0x58d8c":"sk_cap_cmp6",
"0x592c4":"sk_cap_op_aq","0x593e8":"sk_cap_op_ar","0x59418":"sk_cap_op_as",
"0x59448":"sk_cap_op_at","0x59478":"sk_cap_op_au","0x594a8":"sk_cap_op_av",
"0x594d8":"sk_cap_op_aw","0x5950c":"sk_cap_cmp7","0x59a44":"sk_cap_op_ax",
"0x59b68":"sk_cap_op_ay","0x59b98":"sk_cap_op_az","0x59bc8":"sk_cap_op_ba",
"0x59bf8":"sk_cap_op_bb","0x59c28":"sk_cap_op_bc","0x59c58":"sk_cap_op_bd",
"0x59c8c":"sk_cap_cmp8",
"0x5ab94":"sk_error_register","0x5ac2c":"sk_error_get","0x5ace4":"sk_error_clear",
"0x5ad24":"sk_error_status","0x5ad40":"sk_error_reset","0x5ad58":"sk_error_set",
"0x5ae4c":"sk_error_emit","0x5afe8":"sk_error_fmt","0x5b05c":"sk_error_release",
"0x5b0bc":"sk_error_broadcast","0x5b120":"sk_error_cpu","0x5b12c":"sk_error_cpu2",
"0x5b140":"sk_error_sync","0x5b160":"sk_error_flag",
"0x5417c":"sk_cnode_op","0x53db8":"sk_cnode_create","0x54034":"sk_cnode_check",
"0x54094":"sk_cnode_resolve","0x544d0":"sk_cnode_find","0x5453c":"sk_cnode_cur",
"0x545a8":"sk_cnode_notify","0x549ac":"sk_global_ensure",
"0x549c0":"sk_cnode_walk","0x54a4c":"sk_cnode_map","0x54b44":"sk_cnode_record",
"0x54ba8":"sk_cnode_get","0x54bc8":"sk_cnode_get2","0x54be8":"sk_cnode_validate",
"0x54c3c":"sk_cnode_copy","0x54c9c":"sk_cnode_revoke","0x54cfc":"sk_cnode_scan",
"0x54de4":"sk_cnode_scan2","0x54dec":"sk_cnode_scan3","0x54e54":"sk_cnode_tokenize",
"0x50654":"sk_ipc_send2","0x50838":"sk_ipc_fault","0x508e8":"sk_ipc_scan",
"0x50c88":"sk_strnlen","0x50ce8":"sk_ipc_msg_write","0x510e4":"sk_ipc_buf_write",
"0x51350":"sk_ipc_msg_read","0x51488":"sk_ipc_src_cap","0x51740":"sk_ipc_src_map",
"0x51920":"sk_ipc_cap_check","0x519c8":"sk_sec_region_find","0x51ab8":"sk_sec_regions",
"0x51d3c":"sk_macho_vmrange","0x51dc0":"sk_macho_vmrange2","0x51e0c":"sk_macho_seg",
"0x51e5c":"sk_macho_seg_by","0x51ee4":"sk_macho_seg_off","0x51fbc":"sk_macho_uuid",
"0x51ff4":"sk_macho_layout","0x520f0":"sk_macho_bind","0x52248":"sk_dump_rebasechains",
"0x5228c":"sk_rebasechain_walk","0x5236c":"sk_rebasechain_map",
"0x52c4c":"sk_exc_abort","0x539bc":"thunk_current","0x53a14":"sk_exc_entry",
"0x54350":"thunk_cpu","0x54410":"thunk_cpu2","0x5ab88":"sk_syscall_boot",
"0x5ab90":"thunk_cap_dispatch",
"0x501cc":"sk_sec_mem_scan","0x50444":"sk_sec_mem_scan2","0x5ff04":"sk_alloc_frame",
"0x5c380":"sk_dispatch_reset2","0x5c414":"sk_dispatch_reset3","0x5c440":"sk_dispatch_reset4",
"0x5c468":"sk_dispatch_reset5","0x5c490":"sk_dispatch_reset6","0x5c4a8":"sk_dispatch_reset7",
"0x5c4c0":"sk_dispatch_reset8","0x5c510":"sk_dispatch_reset9","0x5c520":"sk_dispatch_reset10",
"0x5c53c":"sk_dispatch_reset11","0x5c558":"sk_dispatch_reset12","0x5c570":"sk_dispatch_reset13",
"0x5cf18":"sk_lock_record","0x5d134":"sk_cap_lookup_slot","0x5d154":"sk_cap_resolve_name",
"0x5d470":"sk_register_cb2","0x5d5dc":"sk_msg_init","0x5d5e8":"sk_msg_send2",
"0x5d77c":"sk_ipc_retrieve","0x5d7c8":"sk_msg_push","0x5d84c":"sk_msg_pop",
"0x5d870":"sk_msg_print","0x5dc48":"thunk_cap_word","0x5dcb0":"sk_lock_release_recursive",
"0x5dd94":"sk_lock_release_recursive2","0x5deb4":"sk_ipc_begin","0x5ded8":"sk_ipc_end",
"0x5df34":"sk_ipc_set",
}

EXT_NAMES = {
"FUN_004b5e60":"sk_syscall_get_state","FUN_0005c650":"sk_error_from_code",
"FUN_0005c924":"sk_error_to_word","FUN_0005cf4c":"sk_notify_domain",
"FUN_00060524":"sk_current_thread","FUN_00060570":"sk_disable_preempt",
"FUN_000605f8":"sk_enable_preempt","FUN_0005acac":"sk_global_get",
"FUN_0005baac":"sk_lookup_thread_obj","FUN_0005ba5c":"sk_register_global",
"FUN_0005bb68":"sk_kernel_get","FUN_0005bb7c":"sk_list_head",
"FUN_0005bc48":"sk_range_lookup","FUN_0005b860":"sk_kernel_state_get",
"FUN_0005d154":"sk_cap_resolve_name","FUN_0005b8c8":"sk_format_uuid",
"FUN_0005b824":"sk_format_vsnprintf","FUN_0005b190":"sk_panic_msg",
"FUN_0005b1b0":"sk_panic","FUN_0005dab8":"sk_ipc_call_guard",
"FUN_0005dfa8":"sk_ipc_msg_frame","FUN_0005d64c":"sk_msg_send",
"FUN_0005dc4c":"sk_cpu_array","FUN_0005d38c":"sk_lock_acquire",
"FUN_0005cc3c":"sk_lock_acquire_recursive","FUN_0005ce54":"sk_unlock",
"FUN_0005dc8c":"sk_lock_dispatch_10","FUN_0005dd70":"sk_lock_dispatch_18",
"FUN_0005cb9c":"sk_lock_prepare","FUN_0005d03c":"sk_notify_domain_slot",
"FUN_0005e8a4":"sk_buf_advance","FUN_0005e958":"sk_syscall_name",
"FUN_0005fbc0":"sk_restore_ctx2","FUN_0005fccc":"sk_restore_ctx3",
"FUN_0005fe48":"sk_state_enter","FUN_0005fea8":"sk_state_exit",
"FUN_0005ff04":"sk_alloc_frame","FUN_00034a2c":"sk_vspace_get_ops",
"FUN_00034f70":"sk_vspace_op2","FUN_00035a78":"sk_pmap_op",
"FUN_0004ed48":"sk_msg_capacity","FUN_0004ed84":"sk_msg_zero",
"FUN_0004eb4c":"sk_msg_iter","FUN_0004e7b8":"sk_msg_get","FUN_0004e8b0":"sk_msg_count",
"FUN_0004eb44":"sk_msg_push_cap","FUN_0004fed0":"sk_msg_record","FUN_0004fe80":"sk_domain_state",
"FUN_0004ffd0":"sk_syscall_exc","FUN_0004e88c":"sk_msg_next","FUN_0004d8ec":"sk_cap_store",
"FUN_0004dfd0":"sk_cap_load","FUN_0004d150":"sk_obj_alloc","FUN_0004d39c":"sk_obj_ref",
"FUN_0004cdc0":"sk_cnode_alloc","FUN_0004ba18":"sk_boot_heap",
"FUN_00114330":"sk_memset","FUN_001143a0":"sk_memcpy","FUN_001144a0":"sk_strchr",
"FUN_00114e50":"sk_strcmp","FUN_00114fe0":"sk_strlen","FUN_00115080":"sk_memcmp",
"FUN_001150e0":"sk_abort_msg","FUN_00116bb4":"sk_snprintf","FUN_00116bcc":"sk_vsnprintf",
"FUN_00116c20":"sk_printf","FUN_00117cc4":"sk_memcpy2","FUN_00117cc8":"sk_memmove",
"FUN_00118148":"sk_klog","FUN_00118164":"sk_klog2","FUN_0011817c":"sk_klog3",
"FUN_00118194":"sk_klog4","FUN_001185ec":"sk_panic_log","FUN_001187f4":"sk_hexdump",
"FUN_0011883c":"sk_trace","FUN_00118abc":"sk_log_fmt","FUN_00118b28":"sk_log_str",
"FUN_00118b94":"sk_log_char","FUN_00118c38":"sk_log_v","FUN_001190fc":"sk_console",
"FUN_0011d7e8":"sk_noreturn_error",
"FUN_000600f0":"sk_thread_create","FUN_0006037c":"sk_thread_state",
"FUN_000603ac":"sk_thread_switch","FUN_000603c4":"sk_thread_yield",
"FUN_000604fc":"sk_thread_resume","FUN_00060540":"sk_thread_lock",
"FUN_0006054c":"sk_thread_unlock","FUN_00060564":"sk_preempt_check",
"FUN_00060650":"sk_tlb_flush","FUN_000606b0":"sk_phys_to_obj",
"FUN_00061044":"sk_msg_cap_read","FUN_000612d8":"sk_ctx_push","FUN_000612e0":"sk_ctx_pop",
"FUN_0006132c":"sk_ctx_regs","FUN_000613ec":"sk_ctx_state","FUN_00061488":"sk_ctx_ip",
"FUN_000614f8":"sk_ctx_sp","FUN_0006156c":"sk_ctx_fp","FUN_000615fc":"sk_ctx_save",
"FUN_00061630":"sk_ctx_flag","FUN_00061638":"sk_ctx_id","FUN_0006166c":"sk_ctx_type",
"FUN_000618cc":"sk_ctx_alloc","FUN_0006198c":"sk_ctx_owner","FUN_000619c8":"sk_ctx_meta",
"FUN_00062474":"sk_ctx_panic","FUN_00062848":"sk_trap","FUN_0006285c":"sk_trap2",
"FUN_000628d8":"sk_trap3","FUN_000628e0":"sk_trap4","FUN_00063910":"sk_ctx_vm",
"FUN_00063970":"sk_ctx_vm2","FUN_00063a50":"sk_ctx_el","FUN_00063aa8":"sk_ctx_cpsr",
"FUN_00063cfc":"sk_ctx_exc","FUN_00063dd4":"sk_ctx_fault","FUN_00063ffc":"sk_ctx_abort",
"FUN_0006402c":"sk_ctx_abort2","FUN_000640e4":"sk_ctx_dbg","FUN_00064108":"sk_ctx_trace",
"FUN_00064c24":"sk_ctx_stack","FUN_00065020":"sk_ctx_finish","FUN_0006562c":"sk_ctx_irq",
"FUN_000656e4":"sk_ctx_printf","FUN_00001378":"sk_boot_next","FUN_0000178c":"sk_timer",
"FUN_00011d7c":"sk_debug",
"FUN_004afae4":"sk_xrt_abort","FUN_004b23d8":"sk_xrt_init",
"FUN_004b5e20":"sk_rt_flags","FUN_004b5e30":"sk_rt_phase","FUN_004b5e48":"sk_rt_state",
"FUN_004b5e60":"sk_syscall_get_state","FUN_004b5e78":"sk_rt_done","FUN_004b5e9c":"sk_rt_wait",
"FUN_004b5ee0":"sk_rt_barrier","FUN_004b5ef8":"sk_rt_sync","FUN_004b5f30":"sk_rt_sync2",
"FUN_004b5fa8":"sk_rt_park","FUN_004b5fb8":"sk_rt_unpark","FUN_004b6194":"sk_rt_log",
"FUN_004b63cc":"sk_rt_run","FUN_004b6430":"sk_rt_runflags","FUN_004b6864":"sk_rt_lock",
"FUN_004b68a4":"sk_rt_unlock","FUN_004b6938":"sk_rt_error","FUN_004b6984":"sk_rt_assert",
"FUN_004b69d0":"sk_rt_check","FUN_004b6c04":"sk_rt_list","FUN_004b6c50":"sk_rt_list2",
"FUN_004b6c9c":"sk_rt_dbg","FUN_004b6d60":"sk_rt_meta","FUN_004b6e24":"sk_rt_proc",
"FUN_004b6e74":"sk_rt_proc2","FUN_004b6e88":"sk_rt_proc3","FUN_004b6e9c":"sk_rt_proc4",
"FUN_004b6ed0":"sk_rt_proc5","FUN_004b6f20":"sk_rt_proc6","FUN_004b6f48":"sk_rt_proc7",
"FUN_004b6f70":"sk_rt_proc8","FUN_004b6fc0":"sk_rt_proc9","FUN_004b6fd8":"sk_rt_proc10",
"FUN_004b6ff0":"sk_rt_proc11","FUN_004b7008":"sk_rt_proc12",
"FUN_0019ae2c":"sk_macho_hdr","FUN_0019ae60":"sk_macho_loadcmds",
"FUN_0019ae9c":"sk_macho_segcmd","FUN_0019af14":"sk_macho_symtab",
"FUN_0019af88":"sk_macho_dysymtab","FUN_0019afb0":"sk_macho_uuid","FUN_0019afbc":"sk_macho_uuid2",
"FUN_0005fdac":"sk_cpu_state_check","FUN_0005fd2c":"sk_current_cpu",
}

SLICE_BY_FUN = {}
for a in ADDRS:
    h = a[2:].rjust(8,'0')
    SLICE_BY_FUN["FUN_"+h] = FUN_NAMES[a]

FUN_FULL = {**EXT_NAMES, **SLICE_BY_FUN}
THUNK_FULL = {("thunk_"+k): v for k,v in FUN_FULL.items()}

# ---- collect DAT_, s_ refs from raw files ----
dat_refs, s_refs = set(), set()
for f in glob.glob(RAW+"/d_*.c"):
    t = open(f).read()
    for m in re.findall(r'\b_DAT_([0-9a-f]{6,8})\b', t): dat_refs.add("_DAT_"+m)
    for m in re.findall(r'\bDAT_([0-9a-f]{6,8})\b', t): dat_refs.add("DAT_"+m)
    for m in re.findall(r'\buRam([0-9a-f]{8})\b', t): dat_refs.add("uRam"+m)
    for m in re.findall(r'\bs_([A-Za-z0-9_]+)\b', t): s_refs.add("s_"+m)

DAT_MAP = {d: f"sk_global_{i:03d}" for i,d in enumerate(sorted(dat_refs))}
STR_EXT = {s: f"sk_str_{i:02d}" for i,s in enumerate(sorted(s_refs))}

# ---- transform helpers ----
def fix_types(s):
    s = s.replace('undefined8','uint64_t').replace('undefined4','uint32_t')
    s = s.replace('undefined2','uint16_t').replace('undefined1','uint8_t')
    s = re.sub(r'\bundefined\b','uint8_t',s)
    s = re.sub(r'\buint3\b','uint64_t',s).replace('uint5','uint64_t')
    s = s.replace('ulong','unsigned long').replace('ushort','unsigned short')
    s = re.sub(r'\bbyte\b','uint8_t',s)
    s = re.sub(r'\buint\b','unsigned int',s)
    s = re.sub(r'\bcode\s*\*','sk_code_t ',s)
    return s

def strip_warnings(text):
    text = re.sub(r'/\* WARNING[^*]*\*/', '', text)
    return text

def split_func(text):
    idx = text.find('{')
    if idx < 0: return text.strip(), ''
    return text[:idx], text[idx:]

def collect_tokens(body):
    return sorted(set(re.findall(r'\b(?:uVar|iVar|lVar|plVar|puVar|pbVar|pcVar|piVar|bVar|cVar|sVar|extraout_|local_|uStack_|auStack_|abStack_|auVar)[0-9a-zA-Z_]*\b', body)))

def build_map(tokens):
    mp={}; stack_i=0; tmp_i=0
    pre={'uVar':'t','iVar':'t','lVar':'v','plVar':'p','puVar':'p','pbVar':'bp',
         'pcVar':'cp','piVar':'ip','bVar':'f','cVar':'c','sVar':'s','extraout_':'xo'}
    for tok in tokens:
        if re.match(r'^(local_|uStack_|auStack_|abStack_|auVar)', tok):
            mp[tok]=f"stk{stack_i}"; stack_i+=1
        else:
            m=re.match(r'^([a-z]+_?)(\d+)?$', tok)
            if m:
                p=pre.get(m.group(1),'t'); num=m.group(2) or ''
                mp[tok]=f"{p}{num or tmp_i}"; tmp_i+=1
            else:
                mp[tok]=f"t{tmp_i}"; tmp_i+=1
    used={}
    for k in list(mp):
        n=mp[k]
        if n in used: used[n]+=1; mp[k]=f"{n}_{used[n]}"
        else: used[n]=0
    return mp

def apply_local_map(body, mp):
    for t, n in sorted(mp.items(), key=lambda kv: -len(kv[0])):
        body = re.sub(r'\b'+re.escape(t)+r'\b', n, body)
    return body

def rename_identifiers2(text):
    for k in sorted(THUNK_FULL, key=len, reverse=True):
        text = text.replace(k, THUNK_FULL[k])
    for k in sorted(FUN_FULL, key=len, reverse=True):
        text = text.replace(k, FUN_FULL[k])
    for k in sorted(dat_refs, key=len, reverse=True):
        if k in DAT_MAP: text = text.replace(k, DAT_MAP[k])
    for k in sorted(s_refs, key=len, reverse=True):
        text = re.sub(r'\b'+re.escape(k)+r'\b', STR_EXT[k], text)
    text = text.replace("SoftwareBreakpoint(", "sk_break(")
    text = text.replace("CallSupervisor(", "sk_svc(")
    text = text.replace("LORelease()", "sk_lo_release()")
    text = text.replace("DataMemoryBarrier(", "sk_dmb(")
    text = text.replace("NEON_ext(", "sk_neon_ext(")
    text = text.replace("tpidrro_el0", "sk_tpidrro")
    text = text.replace("tpidr_el0", "sk_tpidr")
    return text

def normalize_sig(sig, addr):
    fn = "FUN_"+addr[2:].rjust(8,'0')
    en = FUN_NAMES.get(addr, f"sk_fn_{addr[2:]}")
    sig = re.sub(r'\b'+re.escape(fn)+r'\b', en, sig)
    return sig

def transform_full(text, addr):
    text = strip_warnings(text)
    sig, body = split_func(text)
    tokens = collect_tokens(body)
    params = sorted(set(re.findall(r'\bparam_([0-9]+)\b', sig + '\n' + body)), key=int)
    pmap = {f'param_{p}': f'arg{i}' for i,p in enumerate(params, start=1)}
    tokens = [t for t in tokens if not re.match(r'^param_\d+$', t)]
    mp = build_map(tokens)
    body = apply_local_map(body, mp)
    body = fix_types(body)
    body = rename_identifiers2(body)
    for k,v in sorted(pmap.items(), key=lambda kv:-len(kv[0])):
        body = re.sub(r'\b'+re.escape(k)+r'\b', v, body)
    body = re.sub(r'&stack0x[0-9a-fA-F]+', 'NULL', body)
    body = re.sub(r'\bstack0x[0-9a-fA-F]+\b', 'NULL', body)
    sig = fix_types(sig)
    for k,v in sorted(pmap.items(), key=lambda kv:-len(kv[0])):
        sig = re.sub(r'\b'+re.escape(k)+r'\b', v, sig)
    sig = normalize_sig(sig, addr)
    sig = re.sub(r'\s+', ' ', sig).strip()
    return sig, body

# ---- build extern declarations ----
# Hand-written bodies for special cases (128-bit struct returns / NEON).
HAND_WRITTEN = {
"0x5c650": (
"""void sk_error_from_code(uint64_t *out, unsigned long code)
{
    long t0;
    unsigned long t1;
    uint64_t hi, lo;

    /* Build the per-error-code dispatch records (4 fixed records at 0x64db60). */
    t1 = 0;
    t0 = 0x64db60;
    do {
        if ((((unsigned int)t1 - 1) & 0xff) < 3) {
            sk_dispatch_record((unsigned int)t1 & 0xff, t0);
        }
        t1 = t1 + 1;
        t0 = t0 + 0x50;
    } while (t1 != 4);

    lo = 0;
    hi = 0;
    sk_dispatch_record(code, &lo);
    sk_error_classify(code, &lo, 0, 1);

    /* 128-bit payload: the record's two 64-bit words are swapped so that the
     * classified error code lands in the message's result word. */
    out[0] = hi;
    out[1] = lo;
    out[2] = code & 0xffffffff;
    return;
}"""),
"0x5dfa8": (
"""sk_u128_t sk_ipc_msg_frame(unsigned long arg1, unsigned short *msg)
{
    unsigned short tag;
    uint64_t word2, word3;
    uint8_t *frame;

    tag = *msg;
    word2 = *(uint64_t *)(msg + 4);
    word3 = *(uint64_t *)(msg + 8);

    /* The SVC message frame (tpidrro) is the ABI for issuing a supervisor call:
     * write tag + two message words into the frame, then trap. */
    frame = (uint8_t *)sk_tpidrro;
    frame[4] = 0; frame[2] = 0; frame[5] = 0; frame[3] = 0;
    frame[6] = 0; frame[7] = 0;
    *frame = (char)tag;
    frame[1] = (uint8_t)(tag >> 8);
    frame[0xd] = (char)(word2 >> 0x28);
    frame[8]  = (char)word2;
    frame[0xb] = (char)(word2 >> 0x18);
    frame[10] = (char)(word2 >> 0x10);
    frame[9]  = (char)(word2 >> 8);
    frame[0xc] = (char)(word2 >> 0x20);
    frame[0xf] = (char)(word2 >> 0x38);
    frame[0xe] = (char)(word2 >> 0x30);
    frame[0x15] = (char)(word3 >> 0x28);
    frame[0x10] = (char)word3;
    frame[0x13] = (char)(word3 >> 0x18);
    frame[0x12] = (char)(word3 >> 0x10);
    frame[0x11] = (char)(word3 >> 8);
    frame[0x14] = (char)(word3 >> 0x20);
    frame[0x17] = (char)(word3 >> 0x38);
    frame[0x16] = (char)(word3 >> 0x30);

    sk_svc(0);

    /* Restore the caller's frame contents. */
    *frame = (char)tag;
    frame[7] = 0; frame[6] = 0; frame[5] = 0; frame[4] = 0;
    frame[3] = 0; frame[2] = 0; frame[1] = (uint8_t)(tag >> 8);

    /* Result: if the request tag matched a 8-byte message slot, return the
     * message payload word and the capability selector; else zero. */
    bool ok = ((msg[0x10] & arg1) == 8);
    unsigned long lo = ok ? (unsigned long)tag : 0;
    unsigned long hi = ok ? arg1 : 0;
    *(unsigned long *)(msg + 0xc) = lo;
    sk_u128_t r;
    r.lo = hi;
    r.hi = 0;
    return r;
}"""),
}

defined = set(FUN_NAMES[a] for a in ADDRS)
ALL_FUN_CALLS=set(); ALL_GLOBALS=set(); ALL_STRS=set(); ALL_HW=set()
func_sigs = {}
for a in ADDRS:
    fn = f"{RAW}/d_{a[2:]}.c"
    if not os.path.exists(fn):
        print("MISSING", a); continue
    if a in HAND_WRITTEN:
        body = HAND_WRITTEN[a]
        func_sigs[a] = (body[:body.find('{')].strip(), body)
    else:
        sig, body = transform_full(open(fn).read(), a)
        func_sigs[a] = (sig, sig + "\n" + body)
    for m in re.findall(r'\b(sk_[a-z0-9_]+)\s*\(', body): ALL_FUN_CALLS.add(m)
    for m in re.findall(r'\b(sk_global_\d+)\b', body): ALL_GLOBALS.add(m)
    for m in re.findall(r'\b(sk_str_\d+)\b', body): ALL_STRS.add(m)
    for m in re.findall(r'\b(sk_break|sk_svc|sk_lo_release|sk_dmb|sk_neon_ext|sk_tpidrro|sk_tpidr)\b', body): ALL_HW.add(m)

need_extern = ALL_FUN_CALLS - defined - set(["sk_break","sk_svc","sk_lo_release","sk_dmb","sk_neon_ext"])
print("extern funcs:", len(need_extern))
print("globals:", len(ALL_GLOBALS), "strs:", len(ALL_STRS), "hw:", len(ALL_HW))
with open("/tmp/need_extern.txt","w") as f: f.write("\n".join(sorted(need_extern)))
with open("/tmp/func_sigs.json","w") as f: json.dump({a:func_sigs[a][0] for a in func_sigs}, f)
print("sigs:", len(func_sigs))

# ---------- ASSEMBLE OUTPUT ----------
# Load real extern prototypes (converted from Ghidra signatures).
import json as _json
if os.path.exists("/tmp/ext_protos.json"):
    protos = _json.load(open("/tmp/ext_protos.json"))
else:
    protos = {}
HDR = """/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel,
 * arm64e, image base 0) — the cL4 microkernel (GL1). Ground truth: Ghidra FUN_
 * names + addresses in program cl4_kernel.raw. Version "cL4 microkernel
 * (cL4 (679.100.61))". All names are estimates unless string/header-matched.
 *
 * This file covers the syscall/exception/IPC/CNode dispatch + error-code and
 * boot-region machinery at 0x50000 - 0x60000.
 *
 * SeL4/cL4 vocabulary is used for naming: TCB, cap, CNode, IPC, notification,
 * vspace, sched, etc. Confidence is medium unless a string matches.
 */

#ifndef _SK_REGION_BOOT_50000_H_
#define _SK_REGION_BOOT_50000_H_

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

/* 128-bit message/result word used by the SVC frame ABI. */
typedef struct { uint64_t lo; uint64_t hi; } sk_u128_t;
/* Function pointer rendered from Ghidra's "code *" type. */
typedef void (*sk_code_t)(void);
"""

def proto_for(name):
    return f"extern uint64_t {name}(uintptr_t a, ...);"

# Hardware intrinsics
HW_DECL = """/* Supervisor-call + debug intrinsics (render of CallSupervisor /
 * SoftwareBreakpoint / LORelease / DataMemoryBarrier / NEON_ext and the
 * tpidr/tpidrro register reads). */
extern uint64_t sk_break(uintptr_t a, ...);
extern uint64_t sk_svc(uintptr_t n, ...);
extern void sk_lo_release(void);
extern void sk_dmb(unsigned long a, unsigned long b);
extern unsigned long sk_tpidrro;
extern unsigned long sk_tpidr;
"""

# Global data externs
glob_lines = "\n".join(f"extern uint64_t {g};  /* Ghidra DAT_/global */" for g in sorted(ALL_GLOBALS))
str_lines = "\n".join(f"extern const char {s}[];  /* Ghidra string label */" for s in sorted(ALL_STRS))
struct_ret = set(["sk_boot_heap","sk_ctx_finish","sk_macho_segcmd","sk_macho_symtab",
                  "sk_noreturn_error","sk_vspace_get_ops","sk_msg_zero","sk_msg_capacity"])
def ext_proto(n):
    if n in struct_ret:
        return f"extern sk_u128_t {n}();"   # old-style struct return
    return f"extern uint64_t {n}();"
ext_fn_lines = "\n".join(f"/* Ghidra {EXT_NAMES.get(n, '')} */ {ext_proto(n)}" for n in sorted(need_extern))

# Header comment per function
def func_comment(addr, sig):
    fn = "FUN_"+addr[2:].rjust(8,'0')
    en = FUN_NAMES.get(addr, f"sk_fn_{addr[2:]}")
    # strip return type from sig for the Ghidra line (approx)
    gsig = sig.replace(en, fn).replace("uint64_t","undefined8").replace("unsigned long","ulong").replace("unsigned short","ushort")
    return (f"/* {fn} @ {addr}   (est. {en})\n"
            f" * Ghidra: {gsig}\n"
            f" * {en}: cL4 {en.replace('_',' ')} operation.\n"
            f" * Confidence: medium\n"
            f" * Notes: name estimated from call-graph role and string usage;\n"
            f" *   Ghidra identifiers renamed to English in body.\n"
            f" */\n")

# Order functions by address
def keyaddr(a): return int(a, 16)
out = [HDR, HW_DECL, "/* Out-of-region kernel helpers (FUN_ addr in the declaration notes). */\n", ext_fn_lines, "", "/* Out-of-region globals (DAT_ refs). */\n", glob_lines, "", "/* String literals referenced by this region (s_ labels). */\n", str_lines, ""]

# Forward declarations for functions defined in this file, so cross-references
# and thunk/tail calls resolve regardless of definition order.
fwds = []
for a in sorted(ADDRS, key=keyaddr):
    if a not in func_sigs:
        continue
    sig, body = func_sigs[a]
    fwds.append(sig.rstrip(';') + ";")
out.append("/* Forward declarations of functions defined in this region. */\n")
out.append("\n".join(fwds))
out.append("\n")

for a in sorted(ADDRS, key=keyaddr):
    if a not in func_sigs:
        continue
    sig, body = func_sigs[a]
    out.append(func_comment(a, sig))
    out.append(body)
    out.append("\n")

open(OUT, "w").write("\n".join(out))
print("WROTE", OUT, "bytes:", os.path.getsize(OUT))
