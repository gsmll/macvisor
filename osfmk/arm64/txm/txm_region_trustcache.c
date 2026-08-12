/* Recreated from txm.macosx.release.im4p (TXM, arm64e, image base 0) — the
 * Trusted Execution Monitor (GL0). Ground truth: Ghidra FUN_ names + addresses.
 * This file covers the trust-cache + txm_enter-dispatch region 0x2a000-0x35000
 * (txm_waves/T2.txt, 268 functions). All names are estimates unless
 * string/header-matched; see docs/sptm/manifest.json.
 *
 * The region comprises: (a) DT /chosen + /defaults boot-config getters
 * (0x2a000-0x2ab00), (b) the txm_enter selector dispatch hub (0x2adec) and its
 * per-op handlers (0x2b380-0x2c3f8), (c) address-range translate/copy helpers
 * and image4 dispatch (0x2c464-0x2d200), (d) a fortified libc (memset/memcmp/
 * strcmp/strlen/strlcpy/printf family + bounded copies) (0x2d214-0x2f0ec),
 * (e) boot-arg / trust-cache state accessors (0x2f190-0x2f960), and
 * (f) the AppleImage4 trust-evaluation / code-signing verification stack
 * (0x2fa00-0x34ff8): CodeDirectory/superblob parsing, CEContext, AMFI CMS
 * verify, entitlements.
 *
 * Security-relevant observations are logged to docs/sptm/findings.md. */

typedef unsigned long ulong;
typedef unsigned int  uint;
typedef unsigned char uchar;
typedef unsigned short ushort;
typedef int bool;
#define true 1
#define false 0

#define CallSupervisor(n)   /* svc #n */
#define DC_ZVA(p)           /* dc zva */
#define DataSynchronizationBarrier(a,b,c)  __asm__ volatile("dsb sy")
#define InstructionSynchronizationBarrier() __asm__ volatile("isb")

/* device-tree + TXM primitives (externs into other TXM regions) */
extern int dt_find_node(unsigned long *tree, int parent, const char *name, unsigned long *out);
extern int dt_get_property(unsigned long *tree, unsigned long node, const char *name, unsigned long *out, int *len);
extern void txm_log(const char *fmt, ...);
extern void txm_log_state(unsigned long v);
extern void txm_panic(unsigned long code, unsigned long arg);
extern void txm_assert(unsigned long code);
extern void txm_panic_str(const char *msg);
extern void txm_stack_check_fail(void);
extern unsigned long txm_syscall_26(void);
extern int txm_strcmp(const char *a, const char *b);
extern int txm_strncmp(const char *a, const char *b, unsigned long n);
extern unsigned long txm_strlen(const char *s);
extern unsigned long txm_strlen_v(const char *s);
extern unsigned long txm_strlcpy_chk(char *dst, const char *src, unsigned long cap, unsigned long max);
extern int txm_snprintf_chk(char *out, unsigned long cap, unsigned long off, unsigned long max, const char *fmt, ...);
extern void txm_memcpy_chk(void *dst, const void *src, unsigned long n, unsigned long cap);
extern void txm_memset(void *p, int byte, unsigned long n);
extern void txm_bzero(void *p, unsigned long n);
extern int txm_memcmp(const void *a, const void *b, unsigned long n);
extern void *txm_memmove(void *dst, const void *src, unsigned long n);
extern void txm_panic_msg(void);

/* per-op implementation primitives (deeper TXM machinery, stubbed externs) */
extern void txm_op_2(void);
extern void txm_op_5(void);
extern unsigned long txm_op_8(void);
extern void txm_op_9(unsigned long);
extern void txm_op_10(unsigned long);
extern unsigned long txm_op_11(void);
extern unsigned long txm_op_12(unsigned, void*, void*, void*, void*);
extern unsigned long txm_op_14(unsigned, void*, void*);
extern unsigned long txm_op_15(unsigned long, void*);
extern unsigned long txm_op_16(unsigned long);
extern unsigned long txm_op_17(unsigned long, void*);
extern unsigned long txm_op_18(unsigned long, void*, void*);
extern unsigned long txm_op_19(unsigned long);
extern unsigned long txm_op_20(unsigned long, void*);
extern unsigned long txm_op_21(unsigned long);
extern unsigned long txm_op_22(unsigned long, void*, void*);
extern unsigned long txm_op_23(unsigned long);
extern void txm_op_24(unsigned long);
extern unsigned long txm_op_24b(void);
extern unsigned long txm_op_25(unsigned long);
extern unsigned long txm_op_26(unsigned long);
extern unsigned long txm_op_27(void);
extern unsigned long txm_op_28(unsigned long, void*);
extern unsigned long txm_op_29(unsigned long, void*);
extern unsigned long txm_op_30(unsigned long, void*);
extern unsigned long txm_op_32(unsigned long);
extern unsigned long txm_op_33(unsigned long, void*);
extern unsigned long txm_op_34(unsigned long);
extern unsigned long txm_op_35(unsigned, void*);
extern unsigned long txm_op_36(unsigned long);
extern unsigned long txm_op_36b(void);
extern unsigned long txm_op_37(unsigned long, void*, void*);
extern unsigned long txm_op_38(unsigned long, void*, void*, void*, void*);
extern unsigned long txm_op_39(unsigned long);
extern unsigned long txm_op_40(unsigned long, void*, void*);
extern unsigned long txm_op_41(void);
extern unsigned long txm_op_42(unsigned long, void*, void*);
extern unsigned long txm_op_43(unsigned long);
extern unsigned long txm_op_44(unsigned long);
extern unsigned long txm_op_45(unsigned long, void*, void*);
extern unsigned long txm_trust_cache_unload(unsigned long);
extern void txm_validate_range(unsigned long*, unsigned long);
extern unsigned long txm_trust_cache_load(unsigned long, unsigned long*, unsigned long*);
extern unsigned long txm_tc_num_entries(unsigned long);
extern unsigned long txm_img4_lookup(unsigned long*, unsigned long, unsigned long, unsigned long, unsigned long*);
extern unsigned long txm_img4_flags(unsigned long*, unsigned long, unsigned long, unsigned long*);
extern unsigned long txm_img4_identifier(unsigned long*, unsigned long, unsigned long);
extern void txm_op_verify_do(unsigned long, unsigned long);
extern unsigned long txm_op_handle(unsigned long);
extern unsigned long txm_op_ctx(unsigned long);
extern unsigned long txm_platform_status(void);
extern void txm_op_nonce(unsigned long*);
extern unsigned long txm_verify_entitlements(unsigned long*);
extern unsigned long txm_verify_entitlements2(unsigned long*);
extern unsigned long txm_check_entitlements(unsigned long*);
extern short txm_cert_get(unsigned long, unsigned long, unsigned long, unsigned long*);
extern void txm_cert_aux(unsigned long, unsigned long*);
extern short txm_cert_hash(unsigned long, unsigned long*);
extern short txm_cert_attr(unsigned long, unsigned long*);
extern short txm_cdhash(unsigned long, unsigned long*);
extern unsigned long txm_platform_token(unsigned long, unsigned long*);
extern short txm_resolve(unsigned long, unsigned long, unsigned long*);
extern void txm_nested_verify(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long);
extern unsigned long txm_ctx_status(unsigned long);
extern void txm_ctx_begin(unsigned long, unsigned long, unsigned long);
extern void txm_ctx_end(unsigned long, unsigned long);
extern unsigned long txm_ctx_begin_new(unsigned long);
extern short txm_verification(unsigned long, unsigned long*);
extern unsigned long txm_image4_dispatch(long, unsigned long*, unsigned long);
extern unsigned long txm_range_resolve(unsigned long*);
extern void txm_range_page_translate(unsigned long*, unsigned long, unsigned long);
extern void txm_page_op_16k(unsigned long, unsigned long, unsigned long);
extern void txm_copy_range_do(unsigned long*, unsigned long, unsigned long);
extern unsigned long txm_translate(unsigned long, unsigned long*);
extern unsigned char txm_range_resolve_local(unsigned long, char*);
extern unsigned long txm_indirect_op(void);
extern unsigned long txm_img4_handler(void);
extern unsigned long txm_img4_input_size(long);
extern void txm_strlcpy_chk2(char*, const char*, unsigned long, unsigned long);
extern void txm_indirect_op2(void);
extern unsigned long txm_op_4get(void);
extern unsigned long txm_op_resolve(ushort);
extern unsigned long txm_op_3(unsigned long);
extern unsigned long txm_op_4(unsigned short, unsigned long);
extern unsigned long txm_op_5full(unsigned short, unsigned long, unsigned long, unsigned long);
extern void txm_enter_platform_ops_result(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long*);
extern unsigned long txm_cap_probe(unsigned long);
extern void txm_boot_page_register(unsigned long, unsigned long, unsigned long);
extern void txm_boot_arg_get(unsigned long*, unsigned long);
extern void txm_copy_block(void*, void*, unsigned long);
extern void txm_op_copy_state_do(unsigned long, unsigned long*);
extern short txm_op_get_state_do(unsigned long, unsigned long*);
extern unsigned long txm_hash_data(unsigned long, unsigned long*);
extern void txm_kernel_boot_1(void);
extern void txm_kernel_boot_2(void);
extern void txm_kernel_boot_3(void);
extern void txm_handoff(unsigned long*, unsigned long, unsigned long, unsigned long*);
extern unsigned long txm_handoff_get(void);
extern unsigned long txm_key_schedule(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, void*);
extern unsigned long txm_verify(void*, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long*);
extern unsigned long txm_finalize(unsigned long, void*, unsigned long*);
extern unsigned long txm_crypto_ctx_init(unsigned long);
extern int txm_cectx_check(unsigned long);
extern unsigned long txm_cap_probe2(unsigned long, unsigned long);
extern void txm_cap_apply(unsigned*, unsigned*);
extern unsigned long txm_codedir_dispatch(unsigned*);
extern unsigned long txm_cert_find_all(unsigned long);
extern void txm_codedir_get_base(unsigned*, unsigned long, unsigned long*);
extern unsigned long txm_cert_get_base_flag(unsigned long*, unsigned long*);
extern void txm_cert_aux2(unsigned long, unsigned long*);
extern unsigned long txm_cert_list_head(unsigned long*);
extern void txm_cert_list_push(unsigned long*, unsigned long*);
extern unsigned long txm_cert_find_by_handle(unsigned long, unsigned long, unsigned long*);
extern unsigned long txm_dict_init(unsigned long, const char*, unsigned long*);
extern int txm_dict_int(unsigned long*, unsigned*);
extern int txm_dict_value(unsigned long*, unsigned long);
extern int txm_dict_flags(unsigned long*, unsigned long);
extern int txm_dict_str(unsigned long*, unsigned long, unsigned long*);
extern int txm_dict_str_err(void);
extern int txm_dict_data(unsigned long*, unsigned long*);
extern int txm_dict_data2(unsigned long*, unsigned long*);
extern int txm_dict_cert_array(unsigned long*, unsigned long*);
extern int txm_dict_value2(unsigned long*, unsigned long*);
extern unsigned long txm_ct_parse_amfi_cms(unsigned long, unsigned long, unsigned, unsigned long*, unsigned long*, unsigned long*, unsigned long*, unsigned long*, unsigned long*);
extern unsigned long txm_ct_verify_chain(unsigned long, unsigned long, unsigned long*, unsigned long, unsigned, unsigned long*, unsigned long*, unsigned long*);
extern unsigned long txm_ct_verify_cert_chain(unsigned long, unsigned long, unsigned char, unsigned, unsigned long*);
extern unsigned long txm_cert_chain_hash(unsigned long, unsigned long, unsigned long*, unsigned long*);
extern unsigned long txm_hash_1(const void*, unsigned long, const void*);
extern unsigned long txm_hash_2(const void*, unsigned long, const void*);
extern unsigned long txm_hash_4(const void*, unsigned long, const void*);
extern unsigned long txm_hash_8(const void*, unsigned long, const void*);
extern unsigned long txm_kernel_profile(unsigned long, unsigned, unsigned long*);
extern unsigned long txm_entitlements_set(unsigned long);
extern unsigned long txm_profile_flags(void);
extern unsigned long txm_cectx_profile_update(unsigned long*);
extern void txm_handoff_block(void*, unsigned long*);
extern unsigned long txm_profile_flags2(unsigned long*);
extern unsigned long txm_cectx_value2(unsigned long, const char*, unsigned long);
extern void txm_ctx_begin2(unsigned long, unsigned long, unsigned long);
extern unsigned long txm_platform_status2(void);
extern void txm_cectx_clear_caps(unsigned long);
extern unsigned long txm_apple_internal_check(unsigned long);
extern unsigned long txm_team_identifier(unsigned long, unsigned long*);
extern unsigned long txm_cectx_value(unsigned long, const char*, unsigned long);
extern unsigned long txm_platform_token2(unsigned long, unsigned long*);
extern unsigned long txm_trust_cache_load2(unsigned long, unsigned long*, unsigned long*);
extern unsigned long txm_op_nonce2(void);

/* globals referenced by the region */
extern unsigned long DAT_00010540;
extern unsigned long DAT_00010530;
extern unsigned char DAT_000104ef;
extern unsigned char DAT_000104e8;
extern unsigned long DAT_00006cf0;
extern unsigned long DAT_000104ea;
extern unsigned long DAT_00010800;
extern unsigned char DAT_000104e9;
extern unsigned long DAT_00070690;
extern unsigned long DAT_00071030;
extern unsigned long DAT_00071034;
extern unsigned long DAT_00071038;
extern unsigned long DAT_00070fa8;
extern unsigned long DAT_00070fb0;
extern unsigned long DAT_00010518, DAT_00010520, DAT_00010528;
extern unsigned long DAT_00010590, DAT_000105c0, DAT_00010608, DAT_00010610;
extern unsigned long DAT_00010678, DAT_000107d8, DAT_000107e8;
extern unsigned long DAT_00070008, DAT_00070028, DAT_00070038;
extern unsigned long DAT_0006cf8;
extern unsigned long DAT_00071ad0;
extern unsigned char DAT_00010c20[], DAT_00010c44[], DAT_00010da0[];
extern unsigned char DAT_00006e39[];
extern unsigned char DAT_00007180[];
extern unsigned char DAT_0000da98[], DAT_0000daa8[], DAT_0000dab8[], DAT_0000dac8[];
extern unsigned char DAT_0000dad8[], DAT_00015598[], DAT_000163e0[], DAT_00016a60[];
extern unsigned char DAT_000170e0[], DAT_00016da0[], DAT_00017420[], DAT_00017e00[];
extern unsigned char DAT_00018290[], DAT_000197c8[];
extern unsigned long DAT_00070694, DAT_00070698;

/* forward decls for functions defined later in this file */
unsigned long txm_state_base(void);
void txm_finalize_state_string(void);
void txm_page_op_16k(unsigned long, unsigned long, unsigned long);
unsigned long txm_op_6(void);
unsigned long txm_op_7(void);

extern unsigned long DAT_00010500;
extern const char s_prospective_local_policy_gen[];

/* FUN_0002a004 @ 0x2a004  (est. txm_amfi_only_platform_code)
 * Ghidra: bool FUN_0002a004(void)
 * Reads the /chosen property "amfi_only_platform_code" (4-byte int); returns
 * whether it is non-zero. On missing/mis-sized property it logs and returns
 * false; panics if the DT is unavailable.
 * Confidence: medium */
bool txm_amfi_only_platform_code(void) {
    unsigned long err; int *val = 0; int len = 0;
    if ((DAT_00010540 & 1) == 0) txm_panic(0x11, 0);
    if (dt_find_node(&DAT_00010530, 0, "/chosen", &err) != 1) txm_panic(0x29, 0);
    if (dt_get_property(&DAT_00010530, err, "amfi_only_platform_code",
                        (void **)&val, &len) == 1) {
        if (len == 4) return *val != 0;
        txm_log("invalid length for amfi_only_platform_code property\n");
    } else {
        txm_log("unable to find amfi_only_platform_code property\n");
    }
    return false;
}

/* FUN_0002a0d8 @ 0x2a0d8  (est. txm_research_enabled)
 * Ghidra: bool FUN_0002a0d8(void)
 * Reads /chosen "research_enabled"; returns non-zero.
 * Confidence: medium */
bool txm_research_enabled(void) {
    unsigned long err; int *val = 0; int len = 0;
    if ((DAT_00010540 & 1) == 0) txm_panic(0x11, 0);
    if (dt_find_node(&DAT_00010530, 0, "/chosen", &err) != 1) txm_panic(0x29, 0);
    if (dt_get_property(&DAT_00010530, err, "research_enabled", (void **)&val, &len) == 1) {
        if (len == 4) return *val != 0;
        txm_log("invalid length for research_enabled property\n");
    } else txm_log("unable to find research_enabled property\n");
    return false;
}

/* FUN_0002a1ac @ 0x2a1ac  (est. txm_sec_research_erm_enabled)
 * Ghidra: bool FUN_0002a1ac(void)
 * Reads /chosen "sec_research_device_erm_enabled"; returns non-zero.
 * Confidence: medium */
bool txm_sec_research_erm_enabled(void) {
    unsigned long err; int *val = 0; int len = 0;
    if ((DAT_00010540 & 1) == 0) txm_panic(0x11, 0);
    if (dt_find_node(&DAT_00010530, 0, "/chosen", &err) != 1) txm_panic(0x29, 0);
    if (dt_get_property(&DAT_00010530, err, "sec_research_device_erm_enabled",
                        (void **)&val, &len) == 1) {
        if (len == 4) return *val != 0;
        txm_log("invalid length for ERM property\n");
    } else txm_log("unable to find research ERM property\n");
    return false;
}

/* FUN_0002a280 @ 0x2a280  (est. txm_vmm_present)
 * Ghidra: bool FUN_0002a280(void)
 * Reads /defaults "vmm_present"; returns non-zero. Panics 0x28 if the
 * /defaults node is missing.
 * Confidence: medium */
bool txm_vmm_present(void) {
    unsigned long err; int *val = 0; int len = 0;
    if ((DAT_00010540 & 1) == 0) txm_panic(0x11, 0);
    if (dt_find_node(&DAT_00010530, 0, "/defaults", &err) != 1) txm_panic(0x28, 0);
    if (dt_get_property(&DAT_00010530, err, "vmm_present", (void **)&val, &len) == 1) {
        if (len == 4) return *val != 0;
        txm_log("invalid length for vmm_present property\n");
    } else txm_log("unable to find vmm_present property\n");
    return false;
}

/* FUN_0002a354 @ 0x2a354  (est. txm_sepfw_load_at_boot)
 * Ghidra: undefined8 FUN_0002a354(void)
 * Reads /chosen "sepfw_load_at_boot". Returns 1 if non-zero; 0 if zero. On
 * parse-failure returns 1 (fail-open for "load").
 * Confidence: medium */
unsigned long txm_sepfw_load_at_boot(void) {
    unsigned long err; int *val = 0; int len = 0;
    if ((DAT_00010540 & 1) == 0) txm_panic(0x11, 0);
    if (dt_find_node(&DAT_00010530, 0, "/chosen", &err) != 1) txm_panic(0x29, 0);
    if (dt_get_property(&DAT_00010530, err, "sepfw_load_at_boot", (void **)&val, &len) == 1) {
        if (len == 4) {
            if (*val != 0) return 1;
            txm_log("system is configured to not start sepfw\n");
            return 0;
        }
        txm_log("invalid length for sepfw_load_at_boot\n");
    } else txm_log("unable to find sepfw_load_at_boot property\n");
    return 1;
}

/* FUN_0002a434 @ 0x2a434  (est. txm_sepfw_never_boot)
 * Ghidra: undefined8 FUN_0002a434(void)
 * Reads /chosen "sepfw_never_boot"; returns 1 if non-zero else 0.
 * Confidence: medium */
unsigned long txm_sepfw_never_boot(void) {
    unsigned long err; int *val = 0; int len = 0;
    if ((DAT_00010540 & 1) == 0) txm_panic(0x11, 0);
    if (dt_find_node(&DAT_00010530, 0, "/chosen", &err) != 1) txm_panic(0x29, 0);
    if (dt_get_property(&DAT_00010530, err, "sepfw_never_boot", (void **)&val, &len) == 1) {
        if (len == 4) {
            if (*val == 0) return 0;
            txm_log("system is configured never to boot sepfw\n");
            return 1;
        }
        txm_log("invalid length for sepfw_never_boot\n");
    } else txm_log("unable to find sepfw_never_boot property\n");
    return 0;
}

/* FUN_0002a514 @ 0x2a514  (est. txm_booted_device_recovery)
 * Ghidra: bool FUN_0002a514(void)
 * Reads /chosen "osenvironment" string, copies up to 32 bytes, compares to
 * "device_recovery". Returns match. Stack canary checked.
 * Confidence: medium */
bool txm_booted_device_recovery(void) {
    unsigned long canary = DAT_00006cf0;
    unsigned long node = 0, value = 0; int len = 0;
    char env[32]; char devrec[32];
    int match;
    txm_bzero(env, sizeof env); txm_bzero(devrec, sizeof devrec);
    if ((DAT_00010540 & 1) == 0) txm_panic(0x11, 0);
    if (dt_find_node(&DAT_00010530, 0, "/chosen", &node) != 1) txm_panic(0x29, 0);
    match = (dt_get_property(&DAT_00010530, node, "osenvironment", &value, &len) == 1);
    if (match) {
        txm_strlcpy_chk(env, (const char*)value, 0x20, 0x20);
        if (txm_strcmp(env, "device_recovery") != 0) match = false;
        else txm_log("system is booted in device recovery mode\n");
    } else txm_log("unable to find osenvironment property\n");
    if (DAT_00006cf0 != canary) txm_stack_check_fail();
    return match;
}

/* FUN_0002a630 @ 0x2a630  (est. txm_internal_device_variant)
 * Ghidra: bool FUN_0002a630(void)
 * True if the boot resolves to the internal device variant or flag 104ef == 1.
 * Confidence: medium */
bool txm_internal_device_variant(void) {
    char flag = DAT_000104ef;
    int internal = txm_syscall_26();
    if (internal != 0) txm_log("resolving to internal device variant\n");
    return internal != 0 || flag == '\x01';
}

/* FUN_0002a674 @ 0x2a674  (est. txm_trust_cache_range)
 * Ghidra: undefined1[16] FUN_0002a674(void)
 * Reads /chosen/memory-map property "TrustCache" (16 bytes {base,size}).
 * Validates 16K alignment + non-overflow; returns {base, size&~0x3fff}.
 * Confidence: high (string "TrustCache" / "/chosen/memory-map" explicit) */
void txm_trust_cache_range(unsigned long out[2]) {
    unsigned long base, size, end;
    unsigned long *val; int len;
    if ((DAT_00010540 & 1) == 0) txm_panic(0x11, 0);
    val = 0; len = 0;
    if (dt_find_node(&DAT_00010530, 0, "/chosen/memory-map", &base) != 1) {
        txm_log("unable to find /chosen/memory-map\n");
        out[0] = 0; out[1] = 0; return;
    }
    if (dt_get_property(&DAT_00010530, base, "TrustCache", (void **)&val, &len) != 1) {
        txm_log("unable to find TrustCache property\n");
        out[0] = 0; out[1] = 0; return;
    }
    if (len != 0x10) { txm_log("invalid length for TrustCache property\n");
        out[0] = 0; out[1] = 0; return; }
    base = val[0]; size = val[1];
    end = (size + 0x3fff) & ~0x3fffUL;
    if (end < size) txm_panic(0x43, 0);
    if (base == 0) txm_panic(0x40, 0);
    if (end == 0) txm_panic(0x41, 0);
    if (base + end < base) txm_panic(0x42, 0);
    if ((base & 0x3fff) != 0) txm_panic(0xc0, 0);
    out[0] = base; out[1] = end;
}

/* FUN_0002a79c @ 0x2a79c  (est. txm_iboot_development_build)
 * Ghidra: bool FUN_0002a79c(void)
 * Reads /chosen/iBoot "iboot_build_variant". True if "development" or "debug".
 * Confidence: medium */
bool txm_iboot_development_build(void) {
    unsigned long node = 0, val = 0; int len = 0;
    if ((DAT_00010540 & 1) == 0) txm_panic(0x11, 0);
    if (dt_find_node(&DAT_00010530, 0, "/chosen/iBoot", &node) != 1) {
        txm_log("unable to find /chosen/iBoot in device tree\n");
        return false;
    }
    if (dt_get_property(&DAT_00010530, node, "iboot_build_variant", &val, &len) != 1) {
        txm_log("(0x1fff)\n");
        return false;
    }
    if (val == 0 || len == 0) { txm_log("missing data for iboot_build_variant\n"); return false; }
    if (txm_strcmp((char*)val, "development") != 0) return true;
    if (txm_strcmp((char*)val, "debug") != 0) return true;
    return false;
}

/* FUN_0002a894 @ 0x2a894  (est. txm_unique_device_id)
 * Ghidra: void FUN_0002a894(undefined8 param_1)
 * Writes the device UDID string into param_1. v2: snprintf "%08X%016llX" of
 * chip_id + unique_chip_id; v3: copy /chosen "unique_device_id_string" (<=0x30).
 * Confidence: medium */
void txm_unique_device_id(char *out) {
    unsigned long err; int *udid_ver = 0; int vlen = 0;
    if ((DAT_00010540 & 1) == 0) txm_panic(0x11, 0);
    if (dt_find_node(&DAT_00010530, 0, "/product", &err) != 1) txm_panic(0x2a, 0);
    if (dt_get_property(&DAT_00010530, err, "udid_version", (void **)&udid_ver, &vlen) != 1) {
        txm_log("unable to find udid_version property\n"); return;
    }
    if (vlen != 4) { txm_log("invalid length for udid_version property\n"); return; }
    if (*udid_ver == 3) {
        unsigned long node = 0, value = 0, vlen2 = 0;
        if ((DAT_00010540 & 1) == 0) txm_panic(0x11, 0);
        if (dt_find_node(&DAT_00010530, 0, "/chosen", &node) != 1) txm_panic(0x29, 0);
        if (dt_get_property(&DAT_00010530, node, "unique_device_id_string",
                            &value, (int*)&vlen2) == 1) {
            if ((uint)vlen2 < 0x31) {
                txm_strlcpy_chk(out, (const char*)value, 0x30, ~0UL);
                return;
            }
            txm_log("invalid length for UniqueDeviceID\n");
        } else txm_log("unable to find unique_device_id string\n");
    } else if (*udid_ver == 2) {
        unsigned long node = 0, chip = 0, uchip = 0; int clen = 0, ulen = 0;
        int n;
        if ((DAT_00010540 & 1) == 0) txm_panic(0x11, 0);
        if (dt_find_node(&DAT_00010530, 0, "/chosen", &node) != 1) txm_panic(0x29, 0);
        if (dt_get_property(&DAT_00010530, node, "chip_id", &chip, &clen) != 1) {
            txm_log("unable to find chip_id property\n"); return;
        }
        if (clen < 4) { txm_log("invalid length for chip_id property\n"); return; }
        if (dt_get_property(&DAT_00010530, node, "unique_chip_id", &uchip, &ulen) != 1) {
            txm_log("unable to find unique_chip_id property\n"); return;
        }
        if (ulen < 8) { txm_log("invalid length for unique_chip_id\n"); return; }
        n = txm_snprintf_chk(out, 0x30, 0, ~0UL, "%08X%016llX",
                             (unsigned)(chip & 0xffffffff), uchip);
        if (n == -1 || 0x2f < n) txm_log("invalid return from snprintf for UniqueDeviceID\n");
        else txm_log("successfully queried the UniqueDeviceID\n");
    } else {
        txm_log("unsupported UniqueDeviceID version\n");
    }
}

/* FUN_0002ab30 @ 0x2ab30  (est. txm_format_chip_id)
 * Ghidra: void FUN_0002ab30(undefined8 param_1, undefined8 param_2)
 * snprintf helper into param_1 with the "%08X%016llX" format (params=0x30).
 * Confidence: medium */
void txm_format_chip_id(char *out, unsigned long arg) {
    txm_snprintf_chk(out, 0x30, 0, arg, "%08X%016llX", 0, 0);
}

/* FUN_0002ab70 @ 0x2ab70  (est. txm_finalize_state_string)
 * Ghidra: void FUN_0002ab70(undefined8 param_1)
 * If the txm state block's string field (2d214) is non-empty, restores it and
 * NUL-terminates at +0x58, then logs the length (via strlen 4f318 + 4edac).
 * Confidence: low */
void txm_finalize_state_string(void) {
    char *s = (char*)txm_state_base();
    if (*s != '\0') { txm_syscall_26(); s[0x58] = '\0'; }
    txm_log_state((unsigned long)txm_strlen(s));
}

/* FUN_0002aba4 @ 0x2aba4  (est. txm_state_string_end)
 * Ghidra: void FUN_0002aba4(long param_1)
 * Logs/commits the state string at param_1+0x68 (est: publish/commit).
 * Confidence: low */
unsigned long txm_state_string_end(unsigned long p) { return (unsigned long)(p + 0x68); }

/* FUN_0002abb0 @ 0x2abb0  (est. txm_page_op_16k)
 * Ghidra: void FUN_0002abb0(void)
 * Performs a 16KB-page operation (est: invalidate/program one page).
 * Confidence: low */
void txm_page_op_16k(unsigned long a, unsigned long b, unsigned long c) { txm_syscall_26(); }

/* thunk_FUN_0004f2f0 / 4efd4 / 4ef48 / 4f0e0 / 61ea4 — passthrough thunks
 * (these are glue to deeper TXM machinery; keep as thin calls). */
void txm_thunk_4f2f0(void) { txm_syscall_26(); }
unsigned long txm_thunk_4efd4(unsigned long a, void *b) { return txm_syscall_26(); }
unsigned long txm_thunk_4ef48(unsigned long a, void *b) { return txm_syscall_26(); }
unsigned long txm_thunk_4f0e0(unsigned long a, unsigned long b, void *c) { return txm_syscall_26(); }
void txm_thunk_61ea4(void) { txm_syscall_26(); }

/* FUN_0002abe4 @ 0x2abe4  (est. txm_noop)
 * Ghidra: void FUN_0002abe4(void)
 * Empty stub (returns immediately). Used as a passthrough/callback identity.
 * Confidence: high */
void txm_noop(void) { }

/* FUN_0002abec @ 0x2abec  (est. txm_enter_platform_ops)
 * Ghidra: void FUN_0002abec(int, ushort, ulong, ulong, ulong, ulong)
 * Secondary txm_enter selector dispatch for boot/platform ops (opcodes 0-5).
 * For each op it records the 64-bit result into the txm state block at +8, then
 * finalizes via 2ab70. Ops: 0=internal, 1=feature-gate (104e8), 2=resolve,
 * 3=security-boot, 4=restricted-entitlement, 5=platform token. Overflows and
 * misalignment panic (0x40/0x42/0xc0/0xa1/0xa0).
 * Confidence: medium */
void txm_enter_platform_ops(int op, ushort a, ulong b, ulong c, ulong d, ulong e) {
    unsigned long state = txm_state_base();
    unsigned long result = 0, result2 = 0;
    if (DAT_00070690 != '\0') txm_panic(0xa0, 0);
    *(unsigned long*)(state + 0x18) = 0;
    if (op < 3) {
        if (op == 0) { DAT_000104ea = 1; }
        else if (op == 1) {
            if ((DAT_00010800 & 1) != 0) { result = 0; result2 = 0; }
            else goto done;
        }
        else if (op == 2) {
            result = txm_op_resolve(a);
            goto apply;
        }
    } else if (op == 3) {
        result = txm_op_3(a | (b & 0xffff) << 0x10);
    } else if (op == 4) {
        result = txm_op_4(a, b & 0xffff | 0x10000);
    } else if (op == 5) {
        if ((DAT_00010800 & 1) == 0) result = txm_op_5full(a, b & 0xffff | 0x10000, c, d);
        else result = 0;
    } else { txm_panic(0xa1, 0); }
apply:
    result2 = (unsigned long)((uint)result & 0xffff);
    result = result & ~0xffffUL;
done:
    *(unsigned long*)(state + 8) = result | result2;
    txm_finalize_state_string();
    if ((**(unsigned char**)(state + 0x300) & 1) != 0) {
        txm_log("denying executable mapping as the device is in restricted mode\n");
        result2 = 0x1e; result = 0; result |= result2;
    }
    /* validate optional code/data range params (16K aligned) */
    if (d == 0) txm_panic(0x40, 0);
    if (0xffffffffffffbfff < d) txm_panic(0x42, 0);
    if ((d & 0x3fff) != 0) txm_panic(0xc0, 0);
    if (e == 0) txm_panic(0x40, 0);
    if (0xffffffffffffbfff < e) txm_panic(0x42, 0);
    if ((e & 0x3fff) != 0) txm_panic(0xc0, 0);
    {
        unsigned long r[3]; r[0] = e; r[1] = 0x4000; r[2] = 0x4000;
        txm_enter_platform_ops_result((ulong)a | (b & 0xffff) << 0x10,
                                      c & 0xff, d, 0x4000, r);
    }
}

/* FUN_0002adec @ 0x2adec  (est. txm_enter)
 * Ghidra: void FUN_0002adec(int, ulong, undefined8, undefined8, undefined8, undefined8)
 * The txm_enter selector dispatch hub. Validates the args region (16K-aligned
 * stack/scratch), then dispatches on opcode param_1 (0x0-0x33) to the
 * per-op handlers below, storing the result in the txm state block at +8 and
 * finalizing via 2ab70. Opcodes map to: boot/trust-cache ops (2-9),
 * code-signing verification (0xc-0x17), image4 trust (0x1b-0x1e, 0x20-0x2d),
 * and reserve values (0x2e-0x33 -> 0x26). See the switch cases.
 * Confidence: high (this is the documented txm_enter dispatch surface) */
void txm_enter(int op, unsigned long p2, void *p3, void *p4, void *p5, void *p6) {
    unsigned long state = txm_state_base();
    unsigned long result = 1;
    unsigned long scratch[4];
    unsigned long scratch_addr;
    scratch[3] = 1;
    if (DAT_00070690 != '\0') txm_panic(0xa0, 0);
    scratch_addr = (unsigned long)(scratch + 3) & ~0x3fffUL;
    if (scratch_addr == 0) txm_panic(0x40, 0);
    if ((unsigned long*)0xffffffffffffbfff < scratch + 3) txm_panic(0x42, 0);
    scratch[2] = 0x4000; scratch[1] = 0x4000; scratch[0] = scratch_addr;
    txm_validate_range(scratch, 0x2d);
    *(unsigned long*)(state + 0x18) = 0;
    if (0x32 < (uint)(op - 1)) txm_panic(0xa1, 0);
    switch (op) {
    default:
        *(unsigned long*)(txm_state_base() + 0x18) = 3;
        *(unsigned long*)(txm_state_base() + 0x20) = DAT_00010500;
        *(void**)(txm_state_base() + 0x28) = &DAT_00070694;
        *(void**)(txm_state_base() + 0x30) = &DAT_00070698;
        /* fallthrough to reset */
        result = 0; break;
    case 2: txm_op_2(); result = 0; break;
    case 3:
        *(unsigned long*)(txm_state_base() + 0x18) = 4;
        *(void**)(txm_state_base() + 0x20) = &DAT_00010590;
        *(unsigned long*)(txm_state_base() + 0x28) = DAT_000105c0;
        *(unsigned long*)(txm_state_base() + 0x30) = DAT_00010608;
        *(unsigned long*)(txm_state_base() + 0x38) = DAT_00010610;
        result = 0; break;
    case 4:
        *(unsigned long*)(txm_state_base() + 0x18) = 1;
        *(unsigned long*)(txm_state_base() + 0x20) = txm_op_4get();
        result = 0; break;
    case 5: txm_op_5(); result = 0; break;
    case 6: result = txm_op_6(); break;
    case 7: result = txm_op_7(); break;
    case 8: result = txm_op_8(); break;
    case 9: txm_op_9(p2); result = 0; break;
    case 10: txm_op_10(p2); result = 0; break;
    case 0xb: result = txm_op_11(); break;
    case 0xc: result = txm_op_12((unsigned)p2 & 0xff, p3, p4, p5, p6); break;
    case 0xd:
        if (p2 + 0x10 < p2) txm_assert(0x19);
        result = txm_trust_cache_unload(p2); break;
    case 0xe: result = txm_op_14((unsigned)p2 & 0xff, p3, p4); break;
    case 0xf: result = txm_op_15(p2, p3); break;
    case 0x10: result = txm_op_16(p2); break;
    case 0x11: result = txm_op_17(p2, p3); break;
    case 0x12: result = txm_op_18(p2, p3, p4); break;
    case 0x13: result = txm_op_19(p2); break;
    case 0x14: result = txm_op_20(p2, p3); break;
    case 0x15: result = txm_op_21(p2); break;
    case 0x16: result = txm_op_22(p2, p3, p4); break;
    case 0x17: result = txm_op_23(p2); break;
    case 0x18: txm_op_24(p2); result = txm_op_24b(); break;
    case 0x19: result = txm_op_25(p2); break;
    case 0x1a:
        if (p2 + 0x61 < p2) txm_assert(0x19);
        result = txm_op_26(p2); break;
    case 0x1b: result = txm_op_27(); break;
    case 0x1c: result = txm_op_28(p2, p3); break;
    case 0x1d: result = txm_op_29(p2, p3); break;
    case 0x1e: result = txm_op_30(p2, p3); break;
    case 0x20: result = txm_op_32(p2); break;
    case 0x21: result = txm_op_33(txm_op_24(p2), p3); break;
    case 0x22: result = txm_op_34(p2); break;
    case 0x23: result = txm_op_35((unsigned)p2 & 0xffff, p3); break;
    case 0x24: txm_op_36(p2); result = txm_op_36b(); break;
    case 0x25: result = txm_op_37(txm_op_36(p2), p3, p4); break;
    case 0x26: result = txm_op_38(p2, p3, p4, p5, p6); break;
    case 0x27: result = txm_op_39(p2); break;
    case 0x28: result = txm_op_40(txm_op_36(p2), p3, p4); break;
    case 0x29: txm_op_36(p2); result = txm_op_41(); break;
    case 0x2a: result = txm_op_42(txm_op_36(p2), p3, p4); break;
    case 0x2b: result = txm_op_43(p2); break;
    case 0x2c: result = txm_op_44(p2); break;
    case 0x2d: result = txm_op_45(p2, p3, p4); break;
    case 0x2e: case 0x2f: case 0x30: case 0x31:
    case 0x32: case 0x33:
        result = 0x26; break;
    }
    *(unsigned long*)(state + 8) = result;
    txm_finalize_state_string();
}

/* FUN_0002b380 @ 0x2b380  (est. txm_op_security_boot_state)
 * Ghidra: void FUN_0002b380(void)
 * Records the security-boot state descriptor into the txm state block: type 6,
 * base DAT_70690, limits DAT_71034 / DAT_70fa8, size 0x2000, and (if TXM
 * enabled) the feature-set pointers 10678/104e8. Panics 0x19 if TXM disabled.
 * Confidence: medium */
void txm_op_security_boot_state(void) {
    unsigned long s = txm_state_base();
    *(unsigned long*)(s + 0x18) = 6;
    *(void**)(s + 0x20) = &DAT_00070690;
    *(void**)(s + 0x28) = &DAT_00071034;
    *(void**)(s + 0x30) = &DAT_00070fa8;
    *(unsigned long*)(s + 0x38) = 0x2000;
    if ((DAT_000104e9 & 1) != 0) {
        *(void**)(s + 0x40) = &DAT_00010678;
        *(void**)(s + 0x48) = &DAT_000104e8;
        return;
    }
    txm_panic(0x19, 0);
}

/* FUN_0002b3e8 @ 0x2b3e8  (est. txm_op_get_security_boot)
 * Ghidra: undefined8 FUN_0002b3e8(void)
 * Returns the current security-boot-mode 16-byte block. Gate 0x71030 must be
 * set and DAT_10518 must be non-zero (else panic 0x2d). On success stores type 2
 * and the block into the state block and returns 0.
 * Confidence: medium */
unsigned long txm_op_get_security_boot(void) {
    unsigned long s = txm_state_base();
    unsigned long block[3];
    if ((DAT_00071030 & 1) == 0) return 0x29;
    if (DAT_00010518 == 0) txm_panic(0x2d, 0);
    block[0] = DAT_00010518; block[1] = DAT_00010520; block[2] = DAT_00010528;
    txm_validate_range(block, 0x3b);   /* est: validate/copy 3x8 block */
    *(unsigned long*)(s + 0x18) = 2;
    txm_copy_block(s + 0x20, block, 3);
    return 0;
}

/* FUN_0002b470 @ 0x2b470  (est. txm_op_set_security_boot_mode)
 * Ghidra: void FUN_0002b470(ulong param_1)
 * Sets the security boot mode to param_1 (must be <= 0xfffffffe). If the new
 * value matches the stored DAT_71038, and it is one of the 7 supported modes,
 * re-runs the boot/feature ops and logs "completed security boot mode %u".
 * Otherwise panics 0x1a.
 * Confidence: medium */
void txm_op_set_security_boot_mode(unsigned long mode) {
    if (0xfffffffe < mode) txm_panic(0x1a, 0);
    if (DAT_00071038 == (int)mode) {
        if ((uint)mode - 1U < 7) {
            txm_op_8(); txm_op_9(0);
        }
        txm_log("completed security boot mode %u\n");
        return;
    }
    txm_panic(0x1a, 0);
}

/* FUN_0002b4f8 @ 0x2b4f8  (est. txm_op_enable_restricted_entitlement)
 * Ghidra: undefined8 FUN_0002b4f8(void)
 * Enables the restricted entitlement feature. Requires TXM active (0x19 panic)
 * and the device feature byte 10678+0x48 bit0 set; then calls the restricted-
 * entitlement enable (23dac), the capability probe 350c0, and logs success.
 * Returns 0 on success, 0x29 if unsupported, panics 0xf1 on probe failure.
 * Confidence: medium */
unsigned long txm_op_enable_restricted_entitlement(void) {
    unsigned long res, cb;
    if ((DAT_000104e9 & 1) == 0) txm_panic(0x19, 0);
    if ((*(unsigned char*)(DAT_00010678 + 0x48) & 1) == 0) {
        txm_log("system does not support restricted entitlement\n");
        return 0x29;
    }
    txm_op_9(0);
    cb = txm_cap_probe(DAT_000107d8);   /* est: 350c0 */
    if ((cb >> 8 & 0xff) != 0) txm_panic(0xf1, cb);
    txm_log("successfully enabled restricted entitlement\n");
    txm_op_10(0);
    return 0;
}

/* FUN_0002b58c @ 0x2b58c  (est. txm_op_register_boot_page)
 * Ghidra: void FUN_0002b58c(ulong param_1)
 * Registers a 16K-aligned boot page at param_1 (must be non-zero, aligned,
 * within the window). On success calls 26a74(base, 0x4000, 0x29). Overflow/
 * misalignment panic (0x40/0x42/0xc0).
 * Confidence: medium */
void txm_op_register_boot_page(unsigned long base) {
    if (base == 0) txm_panic(0x40, 0);
    if (0xffffffffffffc000 <= base) txm_panic(0x42, 0);
    if ((base & 0x3fff) != 0) txm_panic(0xc0, 0);
    txm_boot_page_register(base, 0x4000, 0x29);
}

/* FUN_0002b5e8 @ 0x2b5e8  (est. txm_op_get_boot_arg)
 * Ghidra: undefined8 FUN_0002b5e8(void)
 * Returns a boot-arg token (3x8 block). On empty returns 7; else stores type 1
 * + the token and returns 0.
 * Confidence: medium */
unsigned long txm_op_get_boot_arg(void) {
    unsigned long s = txm_state_base();
    unsigned long token[3] = {0,0,0};
    txm_boot_arg_get(token, 0xb);
    if (token[0] == 0) return 7;
    *(unsigned long*)(s + 0x18) = 1;
    *(unsigned long*)(s + 0x20) = token[0];
    return 0;
}

/* FUN_0002b644 @ 0x2b644  (est. txm_op_load_trust_cache)
 * Ghidra: ulong FUN_0002b644(undefined8, ulong, ulong, ulong, ulong)
 * Loads a trust cache described by two {base,size} pairs (both 16K-aligned,
 * non-zero, non-overflowing). Delegates to 26350 (the real load) and records
 * the resulting number of entries (28594) in the state block.
 * Confidence: medium */
unsigned long txm_op_load_trust_cache(unsigned long kind,
        unsigned long dbase, unsigned long dsize,
        unsigned long cbase, unsigned long csize) {
    unsigned long s = txm_state_base();
    unsigned long db, ds, cb, cs;
    unsigned long r;
    if ((dsize + 0x3fff & ~0x3fffUL) < dsize) txm_panic(0x43, 0);
    if (dbase == 0) txm_panic(0x40, 0);
    if ((dsize + 0x3fff & ~0x3fffUL) == 0) txm_panic(0x41, 0);
    if (dbase + (dsize+0x3fff & ~0x3fffUL) < dbase) txm_panic(0x42, 0);
    if ((dbase & 0x3fff) != 0) txm_panic(0xc0, 0);
    if ((csize + 0x3fff & ~0x3fffUL) < csize) txm_panic(0x43, 0);
    if (cbase == 0) txm_panic(0x40, 0);
    if ((csize + 0x3fff & ~0x3fffUL) == 0) txm_panic(0x41, 0);
    if (cbase + (csize+0x3fff & ~0x3fffUL) < cbase) txm_panic(0x42, 0);
    if ((cbase & 0x3fff) != 0) txm_panic(0xc0, 0);
    cb = cbase; cs = csize; db = dbase; ds = dsize;
    r = txm_trust_cache_load(kind, &db, &cb);
    if ((r & 0xffff) == 0) {
        *(unsigned long*)(s + 0x18) = 1;
        *(unsigned long*)(s + 0x20) = txm_tc_num_entries(dsize) & 0xffffffff;
    }
    return r;
}

/* FUN_0002b760 @ 0x2b760  (est. txm_op_eval_signature)
 * Ghidra: ulong FUN_0002b760(undefined8, ulong, ulong)
 * Evaluates a code signature/entitlement block at param_2 of size param_3
 * (default 0x14). Requires TXM active; delegates to 30c00 and returns the
 * packed status; on 0x20 subclass panics 0xf0|0x2000.
 * Confidence: medium */
unsigned long txm_op_eval_signature(unsigned long kind, unsigned long base, unsigned long size) {
    unsigned long s = txm_state_base();
    unsigned long r, out0 = 0, out1 = 0;
    if (size == 0) size = 0x14;
    if (base == 0) txm_panic(0x40, 0);
    if (base + size < base) txm_panic(0x42, 0);
    if (base + size < base) txm_assert(0x19);
    if ((DAT_000104e9 & 1) != 0) {
        r = txm_img4_lookup(&DAT_00010590, kind, base, size, &out0);
        if ((r & 0xffff) >> 8 == 0) {
            *(unsigned long*)(s + 0x18) = 2;
            *(unsigned long*)(s + 0x28) = out1;
            *(unsigned long*)(s + 0x20) = out0;
            return 0;
        }
        if (((r & 0xffff) >> 8 & 0xff) == 0x20) txm_panic(0xf0, r & 0xffff00ff | 0x2000);
        return 3 | (r & 0xffff0000) | ((r >> 8 & 0xff) << 0x10) | ((r & 0xff) << 0x10);
    }
    txm_panic(0x18, 0);
    return 0;
}

/* FUN_0002b870 @ 0x2b870  (est. txm_op_get_signature_flags)
 * Ghidra: ulong FUN_0002b870(ulong, ulong)
 * Reads signature/entitlement flags at param_1 (size default 0x14) via 30224;
 * returns packed status + the flag byte.
 * Confidence: medium */
unsigned long txm_op_get_signature_flags(unsigned long base, unsigned long size) {
    unsigned long s = txm_state_base();
    unsigned long r; uchar flag = 0;
    if (size == 0) size = 0x14;
    if (base == 0) txm_panic(0x40, 0);
    if (base + size < base) txm_panic(0x42, 0);
    if (base + size < base) txm_assert(0x19);
    if ((DAT_000104e9 & 1) != 0) {
        r = txm_img4_flags(&DAT_00010590, base, size, &flag);
        if ((r & 0xffff) >> 8 == 0) {
            *(unsigned long*)(s + 0x18) = 1;
            *(unsigned long*)(s + 0x20) = flag;
            return 0;
        }
        if (((r & 0xffff) >> 8 & 0xff) == 0x20) txm_panic(0xf0, r & 0xffff00ff | 0x2000);
        return 3 | (r & 0xffff0000) | ((r >> 8 & 0xff) << 0x10) | ((r & 0xff) << 0x10);
    }
    txm_panic(0x18, 0);
    return 0;
}

/* FUN_0002b974 @ 0x2b974  (est. txm_op_get_identifier)
 * Ghidra: ulong FUN_0002b974(ulong)
 * Reads a 16-byte code identifier at param_1 via 30984.
 * Confidence: medium */
unsigned long txm_op_get_identifier(unsigned long base) {
    unsigned long r;
    if (base + 0x10 < base) txm_assert(0x19);
    if ((DAT_000104e9 & 1) != 0) {
        r = txm_img4_identifier(&DAT_00010590, base, 0);
        if ((r & 0xffff) >> 8 == 0) return 0;
        if (((r & 0xffff) >> 8 & 0xff) == 0x20) txm_panic(0xf0, r & 0xffff00ff | 0x2000);
        return 3 | (r & 0xffff0000) | ((r >> 8 & 0xff) << 0x10) | ((r & 0xff) << 0x10);
    }
    txm_panic(0x18, 0);
    return 0;
}

/* FUN_0002ba18 @ 0x2ba18  (est. txm_op_hash_data)
 * Ghidra: void FUN_0002ba18(ulong, ulong)
 * Hashes data at param_1 (16K-aligned, size param_2) and stores the digest
 * (from 20248) in the state block.
 * Confidence: medium */
void txm_op_hash_data(unsigned long base, unsigned long size) {
    unsigned long s = txm_state_base();
    unsigned long digest = 0;
    unsigned long end = (size + 0x3fff) & ~0x3fffUL;
    short r;
    if (end < size) txm_panic(0x43, 0);
    if (base == 0) txm_panic(0x40, 0);
    if (end == 0) txm_panic(0x41, 0);
    if (base + end < base) txm_panic(0x42, 0);
    if ((base & 0x3fff) != 0) txm_panic(0xc0, 0);
    r = txm_hash_data(base, &digest);   /* 20248 */
    if (r == 0) {
        *(unsigned long*)(s + 0x18) = 1;
        *(unsigned long*)(s + 0x20) = digest;
    }
}

/* FUN_0002bad8 @ 0x2bad8  (est. txm_op_copy_state)
 * Ghidra: void FUN_0002bad8(undefined8, undefined8*, long)
 * Copies an 8x8 state block from param_2 into the txm state (via 20400) when
 * param_3 == 0x40; validates the 64-byte block bounds.
 * Confidence: medium */
void txm_op_copy_state(unsigned long kind, unsigned long *p, long len) {
    unsigned long canary = DAT_00006cf0;
    unsigned long block[8];
    txm_bzero(block, sizeof block);
    if (len == 0x40) {
        if (p == 0) txm_panic(0x40, 0);
        if (0xffffffffffffffc0 <= (unsigned long)p) txm_panic(0x42, 0);
        if ((unsigned long)p + 8 < (unsigned long)p) txm_assert(0x19);
        block[0]=p[0]; block[1]=p[1]; block[2]=p[2]; block[3]=p[3];
        block[4]=p[4]; block[5]=p[5]; block[6]=p[6]; block[7]=p[7];
    } else txm_panic(0x1b, 0);
    txm_op_copy_state_do(kind, block);
    if (DAT_00006cf0 != canary) txm_stack_check_fail();
}

/* FUN_0002bbac @ 0x2bbac  (est. txm_op_get_state)
 * Ghidra: void FUN_0002bbac(undefined8)
 * Returns a 2x8 state block from 204a8 into the txm state.
 * Confidence: medium */
void txm_op_get_state(unsigned long kind) {
    unsigned long s = txm_state_base();
    unsigned long out[2] = {0,0};
    short r;
    r = txm_op_get_state_do(kind, out);
    if (r == 0) {
        *(unsigned long*)(s + 0x18) = 2;
        *(unsigned long*)(s + 0x20) = out[0];
        *(unsigned long*)(s + 0x28) = out[1];
    }
}

/* FUN_0002bc08 @ 0x2bc08  (est. txm_op_verify_data)
 * Ghidra: void FUN_0002bc08(undefined8, undefined8)
 * Verifies data (205c0) after fetching handles via 27814/27378.
 * Confidence: low */
void txm_op_verify_data(unsigned long a, unsigned long b) {
    txm_op_verify_do(txm_op_handle(a), txm_op_ctx(b));
}

/* FUN_0002bc50 @ 0x2bc50  (est. txm_op_get_platform_status)
 * Ghidra: ulong FUN_0002bc50(void)
 * Returns the platform status word (206dc); 0 if it equals the benign marker
 * 0x120000000004 else the raw value.
 * Confidence: low */
unsigned long txm_op_get_platform_status(void) {
    unsigned long v;
    txm_op_handle(0);
    v = txm_platform_status();
    if ((v & 0xff000000ffff) == 0x120000000004) return 0;
    return v;
}

/* FUN_0002bc84 @ 0x2bc84  (est. txm_op_get_certificate)
 * Ghidra: ulong FUN_0002bc84(ulong, ulong, undefined8)
 * Fetches a certificate blob (base,size) via 243b8 and stores cert handle +
 * its aux data (362ec) in the state block.
 * Confidence: medium */
unsigned long txm_op_get_certificate(unsigned long base, unsigned long size, unsigned long kind) {
    unsigned long s = txm_state_base();
    unsigned long h = 0, aux = 0, aux2 = 0;
    unsigned long r;
    if (base == 0) txm_panic(0x40, 0);
    if (size == 0) txm_panic(0x41, 0);
    if (base + size < base) txm_panic(0x42, 0);
    if (base + size < base) txm_assert(0x19);
    r = txm_cert_get(base, size, kind, &h);
    if ((r & 0xffff) == 0) {
        txm_cert_aux(h + 0x28, &aux);
        *(unsigned long*)(s + 0x18) = 3;
        *(unsigned long*)(s + 0x20) = h;
        *(unsigned long*)(s + 0x28) = aux;
        *(unsigned long*)(s + 0x30) = aux2;
    }
    return r;
}

/* FUN_0002bd5c @ 0x2bd5c  (est. txm_op_get_cert_hash)
 * Ghidra: void FUN_0002bd5c(undefined8)
 * Returns a cert hash (2x8) via 24678.
 * Confidence: medium */
void txm_op_get_cert_hash(unsigned long kind) {
    unsigned long s = txm_state_base();
    unsigned long out[2] = {0,0};
    short r;
    r = txm_cert_hash(txm_op_handle(kind), out);
    if (r == 0) {
        *(unsigned long*)(s + 0x18) = 2;
        *(unsigned long*)(s + 0x20) = out[0];
        *(unsigned long*)(s + 0x28) = out[1];
    }
}

/* FUN_0002bdb8 @ 0x2bdb8  (est. txm_op_get_cert_attr)
 * Ghidra: void FUN_0002bdb8(undefined8)
 * Returns a cert attribute (2x8) via 24970.
 * Confidence: medium */
void txm_op_get_cert_attr(unsigned long kind) {
    unsigned long s = txm_state_base();
    unsigned long out[2] = {0,0};
    short r;
    r = txm_cert_attr(txm_op_handle(kind), out);
    if (r == 0) {
        *(unsigned long*)(s + 0x18) = 2;
        *(unsigned long*)(s + 0x20) = out[0];
        *(unsigned long*)(s + 0x28) = out[1];
    }
}

/* FUN_0002be18 @ 0x2be18  (est. txm_op_get_nonce)
 * Ghidra: undefined8 FUN_0002be18(void)
 * Returns a 2x8 nonce via 23f14. 8 if empty.
 * Confidence: medium */
unsigned long txm_op_get_nonce(void) {
    unsigned long s = txm_state_base();
    unsigned long n[2];
    txm_op_nonce(n);
    if (n[0] == 0) return 8;
    *(unsigned long*)(s + 0x18) = 2;
    txm_copy_block(s + 0x20, n, 2);
    return 0;
}

/* FUN_0002be60 @ 0x2be60  (est. txm_op_verify_entitlements)
 * Ghidra: void FUN_0002be60(ulong, ulong)
 * Copies an entitlement blob (base,size<=0x30) into a scratch region and
 * verifies via 255c0. Panics on oversize (0x28).
 * Confidence: medium */
void txm_op_verify_entitlements(unsigned long base, unsigned long size) {
    unsigned long canary = DAT_00006cf0;
    unsigned long result;
    unsigned long blob[8];
    if (size == 0) size = 0x14;
    txm_bzero(blob, sizeof blob);
    if (0x30 < size) txm_panic(0x28, 0);
    if (base == 0) txm_panic(0x40, 0);
    if (base + size < base) txm_panic(0x42, 0);
    if (base + size < base) txm_assert(0x19);
    txm_copy_block(blob, (void*)base, size);
    result = txm_verify_entitlements(blob);
    if (DAT_00006cf0 != canary) txm_stack_check_fail();
}

/* FUN_0002bf3c @ 0x2bf3c  (est. txm_op_verify_entitlements2)
 * Ghidra: void FUN_0002bf3c(ulong, ulong)
 * As 2be60 but via 25780. Duplicate of the entitlement verification path.
 * Confidence: medium */
void txm_op_verify_entitlements2(unsigned long base, unsigned long size) {
    unsigned long canary = DAT_00006cf0;
    unsigned long result;
    unsigned long blob[8];
    if (size == 0) size = 0x14;
    txm_bzero(blob, sizeof blob);
    if (0x30 < size) txm_panic(0x28, 0);
    if (base == 0) txm_panic(0x40, 0);
    if (base + size < base) txm_panic(0x42, 0);
    if (base + size < base) txm_assert(0x19);
    txm_copy_block(blob, (void*)base, size);
    result = txm_verify_entitlements2(blob);
    if (DAT_00006cf0 != canary) txm_stack_check_fail();
}

/* FUN_0002c018 @ 0x2c018  (est. txm_op_check_entitlements)
 * Ghidra: void FUN_0002c018(ulong, ulong)
 * Checks an entitlement blob (size 0x14..0x30) via 25860; stores a boolean.
 * Confidence: medium */
void txm_op_check_entitlements(unsigned long base, unsigned long size) {
    unsigned long canary = DAT_00006cf0;
    unsigned long s = txm_state_base();
    unsigned long blob[8];
    int r;
    if (size == 0) size = 0x14;
    else if (size < 0x14) txm_panic(0x26, 0);
    else if (0x30 < size) txm_panic(0x28, 0);
    if (base == 0) txm_panic(0x40, 0);
    if (base + size < base) txm_panic(0x42, 0);
    if (base + size < base) txm_assert(0x19);
    txm_copy_block(blob, (void*)base, size);
    r = txm_check_entitlements(blob);
    if (r == 0) txm_panic(8, 0);
    *(unsigned long*)(s + 0x20) = 1;
    *(unsigned long*)(s + 0x18) = 1;
    if (DAT_00006cf0 != canary) txm_stack_check_fail();
}

/* FUN_0002c134 @ 0x2c134  (est. txm_op_get_cdhash)
 * Ghidra: void FUN_0002c134(undefined8)
 * Returns the code directory hash via 24d24.
 * Confidence: medium */
void txm_op_get_cdhash(unsigned long kind) {
    unsigned long s = txm_state_base();
    unsigned long h = 0;
    short r;
    r = txm_cdhash(txm_op_handle(kind), &h);
    if (r == 0) {
        *(unsigned long*)(s + 0x18) = 1;
        *(unsigned long*)(s + 0x20) = h;
    }
}

/* FUN_0002c18c @ 0x2c18c  (est. txm_op_get_platform_token)
 * Ghidra: ulong FUN_0002c18c(undefined8)
 * Returns a platform token via 25160; 0x28 becomes 0 (not-present).
 * Confidence: medium */
unsigned long txm_op_get_platform_token(unsigned long kind) {
    unsigned long s = txm_state_base();
    unsigned long h = 0;
    unsigned long r = txm_platform_token(txm_op_handle(kind), &h);
    unsigned long low = (r & 0xffff) == 0x28 ? 0 : (unsigned)(r & 0xffff);
    if ((low & 0xffff) == 0) {
        *(unsigned long*)(s + 0x18) = 1;
        *(unsigned long*)(s + 0x20) = h;
    }
    return r & ~0xffffUL | low & 0xffff;
}

/* FUN_0002c1f4 @ 0x2c1f4  (est. txm_op_get_resolution)
 * Ghidra: void FUN_0002c1f4(undefined8, undefined8)
 * Resolves a 2x8 value via 22274.
 * Confidence: medium */
void txm_op_get_resolution(unsigned long a, unsigned long b) {
    unsigned long s = txm_state_base();
    unsigned long out = 0;
    short r;
    r = txm_resolve(a, b, &out);
    if (r == 0) {
        *(unsigned long*)(s + 0x18) = 1;
        *(unsigned long*)(s + 0x20) = out;
    }
}

/* FUN_0002c258 @ 0x2c258  (est. txm_op_nested_verify)
 * Ghidra: void FUN_0002c258(undefined8, undefined8, undefined8, undefined8, undefined8)
 * Nested verification via 22b10 after fetching handles.
 * Confidence: low */
void txm_op_nested_verify(unsigned long a, unsigned long b, unsigned long c,
                          unsigned long d, unsigned long e) {
    txm_nested_verify(txm_op_handle(a), txm_op_handle(b), c, d, e);
}

/* FUN_0002c2c8 @ 0x2c2c8  (est. txm_op_reset_verification)
 * Ghidra: undefined8 FUN_0002c2c8(void)
 * Resets the verification context and returns its status via 2316c.
 * Confidence: medium */
unsigned long txm_op_reset_verification(void) {
    unsigned long h = txm_op_handle(0);
    txm_ctx_begin(h, 0, 0);
    unsigned long r = txm_ctx_status(h);
    txm_ctx_end(h, 0);
    return r;
}

/* FUN_0002c314 @ 0x2c314  (est. txm_op_begin_verification)
 * Ghidra: undefined8 FUN_0002c314(long)
 * Begins a verification context (22974); 8 if empty.
 * Confidence: medium */
unsigned long txm_op_begin_verification(unsigned long handle) {
    unsigned long s = txm_state_base();
    unsigned long h;
    if (handle == 0) h = txm_ctx_begin_new(0);
    else {
        unsigned long c = txm_op_handle(handle);
        txm_ctx_begin(c, 0, 0);
        h = txm_ctx_begin_new(c);
        txm_ctx_end(c, 0);
    }
    if (h == 0) return 8;
    *(unsigned long*)(s + 0x18) = 1;
    *(unsigned long*)(s + 0x20) = h;
    return 0;
}

/* FUN_0002c3a0 @ 0x2c3a0  (est. txm_op_get_verification)
 * Ghidra: void FUN_0002c3a0(undefined8)
 * Returns verification status via 2364c.
 * Confidence: medium */
void txm_op_get_verification(unsigned long kind) {
    unsigned long s = txm_state_base();
    unsigned long out = 0;
    short r;
    r = txm_verification(txm_op_handle(kind), &out);
    if (r == 0) {
        *(unsigned long*)(s + 0x18) = 1;
        *(unsigned long*)(s + 0x20) = out;
    }
}

/* FUN_0002c3f8 @ 0x2c3f8  (est. txm_op_image4_dispatch)
 * Ghidra: void FUN_0002c3f8(undefined8, ulong, ulong)
 * Dispatches the image4 evaluation for the {base,size} region (2cbd0). base
 * must be non-zero and the range non-overflowing.
 * Confidence: medium */
void txm_op_image4_dispatch(unsigned long kind, unsigned long base, unsigned long size) {
    if (base == 0) txm_panic(0x40, 0);
    if (size == 0) txm_panic(0x41, 0);
    if (base + size < base) txm_panic(0x42, 0);
    if (base + size < base) txm_assert(0x19);
    txm_image4_dispatch(kind, (unsigned long*)base, size);
}

/* FUN_0002c464 @ 0x2c464  (est. txm_set_syscall_result)
 * Ghidra: void FUN_0002c464(long param_1)
 * Stores a global syscall result (DAT_107e8) from param_1+0x60; panics 0xf2 if
 * the state string is non-empty (est: verification failed).
 * Confidence: low */
void txm_set_syscall_result(long p) {
    if ((int)txm_state_string_end(0) == 0) {
        DAT_000107e8 = *(unsigned long*)(p + 0x60);
        return;
    }
    txm_panic(0xf2, txm_state_string_end(0));
}

/* FUN_0002c4a8 @ 0x2c4a8  (est. txm_copy_range_pages)
 * Ghidra: void FUN_0002c4a8(undefined8*, long, ulong, undefined8, undefined8)
 * Copies a multi-16K-page range (size param_3) from source phys param_2 into a
 * 3-word {base,size,orig} descriptor. Per-page ops via 2abb0, tracking
 * DAT_70fb0 when the source/dest types are the 0x3a (transient) class. Panics 9
 * if the type argument equals 0xb (invalid).
 * Confidence: medium */
void txm_copy_range_pages(unsigned long *out, long src, unsigned long size,
                          unsigned long dst_type, unsigned long src_type) {
    uint t = (uint)src_type;
    if (t == 0xb) txm_panic(9, 0);
    if ((uint)dst_type == t) txm_panic(9, 0);
    if (0x3fff < size) {
        unsigned long n = size >> 0xe;
        long p = src;
        do {
            txm_page_op_16k(p, dst_type, src_type);
            if ((t & 0xfe) == 0x3a) DAT_00070fb0 += 0x4000;
            if (((uint)dst_type & 0xfe) == 0x3a) DAT_00070fb0 -= 0x4000;
            p += 0x4000; n--;
        } while (n != 0);
    }
    txm_copy_range_do(out, src, size);   /* 2c9a4 */
}

/* FUN_0002c5a4 @ 0x2c5a4  (est. txm_range_translate)
 * Ghidra: void FUN_0002c5a4(ulong*, ulong*, undefined8, undefined8)
 * Validates + translates a {base,size,orig} range (param_2) into param_1,
 * processing each 16K page via 2c6a8 with the given types. Panics 9 on an
 * invalid type, 0x19 on any overlap.
 * Confidence: medium */
void txm_range_translate(unsigned long *out, unsigned long *in,
                         unsigned long dst_type, unsigned long src_type) {
    unsigned long i, off, page;
    if ((int)src_type == 0xb || (int)dst_type == (int)src_type) txm_panic(9, 0);
    if (0x3fff < in[1]) {
        off = 0; page = 0;
        unsigned long n = in[1] >> 0xe;
        do {
            unsigned long end = in[0] + in[1];
            if (((in[0] ^ end) & 0xffc0000000000000) != 0)
                end = end & 0xffffffffffff | 0xc8a2000000000000;
            unsigned long a = in[0] + off;
            if (page + in[1] < 0x4000 || end < a || a < in[0]) txm_assert(0x19);
            unsigned long r[3]; r[0] = a; r[1] = 0x4000; r[2] = 0x4000;
            txm_range_page_translate(r, dst_type, src_type);   /* 2c6a8 */
            page -= 0x4000; off += 0x4000; n--;
        } while (n != 0);
    }
    out[0] = in[0]; out[1] = in[1]; out[2] = in[2];
}

/* FUN_0002c6a8 @ 0x2c6a8  (est. txm_range_page_translate)
 * Ghidra: void FUN_0002c6a8(undefined8*, undefined8, undefined8)
 * Translates one 16K page: computes the destination via 2c84c, calls 2abb0,
 * and requires the source/dest translation to be equal (else panic 8).
 * Confidence: medium */
void txm_range_page_translate(unsigned long *page, unsigned long dst_type,
                              unsigned long src_type) {
    unsigned long d1, d2;
    unsigned long r[3]; r[0] = page[0]; r[1] = page[1]; r[2] = page[2];
    d1 = txm_range_resolve(r);
    txm_page_op_16k(d1, dst_type, src_type);
    if ((src_type & 0xfe) == 0x3a) DAT_00070fb0 += 0x4000;
    if ((dst_type & 0xfe) == 0x3a) DAT_00070fb0 -= 0x4000;
    r[0] = page[0]; r[1] = page[1]; r[2] = page[2];
    d2 = txm_range_resolve(r);
    if (d1 == d2) return;
    txm_panic(8, 0);
}

/* FUN_0002c76c @ 0x2c76c  (est. txm_range_flush)
 * Ghidra: void FUN_0002c76c(ulong*, undefined8)
 * Flushes/validates a {base,size} range page-by-page via 2c6a8 with src_type 0xb
 * (transient flush). No output.
 * Confidence: medium */
void txm_range_flush(unsigned long *range, unsigned long dst_type) {
    unsigned long off, page;
    if (0x3fff < range[1]) {
        off = 0; page = 0;
        unsigned long n = range[1] >> 0xe;
        do {
            unsigned long end = range[0] + range[1];
            if (((range[0] ^ end) & 0xffc0000000000000) != 0)
                end = end & 0xffffffffffff | 0xc8a2000000000000;
            unsigned long a = range[0] + off;
            if (page + range[1] < 0x4000 || end < a || a < range[0]) txm_assert(0x19);
            unsigned long r[3]; r[0] = a; r[1] = 0x4000; r[2] = 0x4000;
            txm_range_page_translate(r, dst_type, 0xb);
            page -= 0x4000; off += 0x4000; n--;
        } while (n != 0);
    }
}

/* FUN_0002c834 @ 0x2c834  (est. txm_flush_all)
 * Ghidra: void FUN_0002c834(void)
 * Flushes all caches (thunk to 4f2f0).
 * Confidence: low */
void txm_flush_all(void) { txm_thunk_4f2f0(); }

/* FUN_0002c84c @ 0x2c84c  (est. txm_range_resolve)
 * Ghidra: void FUN_0002c84c(ulong*)
 * Resolves a {base,size} range to a validated 16K-aligned block via 61ea4;
 * returns the block. base/size non-zero, non-overflowing, aligned (0x40/0x41/
 * 0x42/0xc0/0xc1/0xc2 panics), size <= 0x4000 (0xc2 otherwise). 0xf2 panic on
 * the underlying failure.
 * Confidence: medium */
unsigned long txm_range_resolve(unsigned long *range) {
    unsigned long block = 0;
    unsigned long base = range[0], size = range[1];
    unsigned long r;
    if (base == 0) txm_panic(0x40, 0);
    if (size == 0) txm_panic(0x41, 0);
    if (base + size < base) txm_panic(0x42, 0);
    if ((base & 0x3fff) != 0) txm_panic(0xc0, 0);
    if ((size & 0x3fff) != 0) txm_panic(0xc1, 0);
    if (0x4000 < size) txm_panic(0xc2, 0);
    r = txm_translate(base, &block);   /* 61ea4 */
    if ((int)r != 0) txm_panic(0xf2, r);
    if (block == 0) txm_panic(0x40, 0);
    if (0xffffffffffffbfff < block) txm_panic(0x42, 0);
    if ((block & 0x3fff) != 0) txm_panic(0xc0, 0);
    return block;
}

/* FUN_0002c908 @ 0x2c908  (est. txm_range_resolve_local)
 * Ghidra: undefined1 FUN_0002c908(ulong, char*)
 * Resolves a range into the local policy region (prospective local policy
 * generator); returns the block type byte. Validates alignment/bounds; 0xc2 if
 * the target escapes the policy window.
 * Confidence: low */
unsigned char txm_range_resolve_local(unsigned long base, char *p) {
    unsigned char type = 0x43;
    unsigned long r;
    if (base == 0) txm_panic(0x40, 0);
    if (p == 0) txm_panic(0x41, 0);
    if (base + (unsigned long)p < base) txm_panic(0x42, 0);
    if ((base & 0x3fff) != 0) txm_panic(0xc0, 0);
    if (((unsigned long)p & 0x3fff) != 0) txm_panic(0xc1, 0);
    if (p < (char*)(s_prospective_local_policy_gen + 8)) txm_panic(0xc2, 0);
    r = txm_thunk_4efd4(base, &type);
    if ((int)r != 0) txm_panic(0xf2, r);
    return type;
}

/* FUN_0002c9a4 @ 0x2c9a4  (est. txm_copy_range_do)
 * Ghidra: void FUN_0002c9a4(ulong*, undefined8, ulong)
 * Fills a 3-word {base,size,orig} descriptor by translating param_2 via 4ef48
 * and rounding size up to 16K. Validates alignment/bounds.
 * Confidence: medium */
void txm_copy_range_do(unsigned long *out, unsigned long src, unsigned long size) {
    unsigned long block = 0, r;
    r = txm_thunk_4ef48(src, &block);
    if ((int)r != 0) txm_panic(0xf2, r);
    size = (size + 0x3fff) & ~0x3fffUL;
    if (size < (size & ~0x3fffUL)) txm_panic(0x43, 0);
    if (block == 0) txm_panic(0x40, 0);
    if (size == 0) txm_panic(0x41, 0);
    if (block + size < block) txm_panic(0x42, 0);
    if ((block & 0x3fff) != 0) txm_panic(0xc0, 0);
    out[0] = block; out[1] = size; out[2] = src;
}

/* FUN_0002ca50 @ 0x2ca50  (est. txm_alloc_translate_range)
 * Ghidra: void FUN_0002ca50(ulong*, ulong*, undefined8)
 * Allocates a 16K page and translates param_2's range into it via 4f0e0.
 * Confidence: low */
void txm_alloc_translate_range(unsigned long *out, unsigned long *in,
                               unsigned long type) {
    unsigned long block = 0, r;
    unsigned long base = in[0], size = in[1];
    if (base == 0) txm_panic(0x40, 0);
    if (size == 0) txm_panic(0x41, 0);
    if (base + size < base) txm_panic(0x42, 0);
    if ((base & 0x3fff) != 0) txm_panic(0xc0, 0);
    if ((size & 0x3fff) != 0) txm_panic(0xc1, 0);
    if (0x4000 < size) txm_panic(0xc2, 0);
    r = txm_thunk_4f0e0(base, type, &block);
    if ((int)r != 0) txm_panic(0xf2, r);
    if (block == 0) txm_panic(0x40, 0);
    if (0xffffffffffffbfff < block) txm_panic(0x42, 0);
    if ((block & 0x3fff) != 0) txm_panic(0xc0, 0);
    out[0] = block; out[1] = 0x4000; out[2] = 0x4000;
}

/* FUN_0002cb24 @ 0x2cb24  (est. txm_write_range)
 * Ghidra: void FUN_0002cb24(undefined8, undefined8, undefined8)
 * Resolves a local range and copies param_3 bytes; panics 7 if the copy length
 * does not match.
 * Confidence: medium */
void txm_write_range(unsigned long base, unsigned long type, unsigned long len) {
    int n;
    txm_range_resolve_local(base, (char*)type);
    txm_noop(); n = (int)len;
    if (n == (int)len) return;
    txm_panic(7, 0);
}

/* FUN_0002cb64 @ 0x2cb64  (est. txm_write_range_chk)
 * Ghidra: void FUN_0002cb64(undefined8*, undefined8)
 * Validates the range then writes param_2 via 2cb24.
 * Confidence: medium */
void txm_write_range_chk(unsigned long *range, unsigned long len) {
    unsigned long r[3]; r[0] = range[0]; r[1] = range[1]; r[2] = range[2];
    txm_range_resolve(r);
    txm_write_range(r[0], r[1], len);
}

/* FUN_0002cbb8 @ 0x2cbb8  (est. txm_jumptable_dispatch)
 * Ghidra: void FUN_0002cbb8(void)
 * Indirect jump through the op table (DAT_1d360). Decompiler could not recover
 * the jump table; kept as an indirect dispatch.
 * Confidence: low */
void txm_jumptable_dispatch(void) { txm_indirect_op(); }

/* FUN_0002cbd0 @ 0x2cbd0  (est. txm_image4_dispatch)
 * Ghidra: ulong FUN_0002cbd0(long, undefined8*, ulong)
 * The image4 trust-evaluation dispatcher. Selects a handler by param_1
 * (kind: 0=pin-root, 1=pin-root-not-supported, 2=evaluate-trust-note,
 * 3/4/5 = variable-size image4 payloads). Parses the {base,size} payload into
 * per-kind fields, runs the handler (535e0 callback), validates the input size
 * matches (53cb0), and range-translates the code+data segments. Returns a packed
 * status word.
 * Confidence: high (explicit image4 strings + handler dispatch) */
unsigned long txm_image4_dispatch(long kind, unsigned long *p, unsigned long size) {
    unsigned long canary = DAT_00006cf0;
    unsigned long (*handler)(unsigned long, void*, unsigned long, int, int);
    unsigned long expected, res = 0;
    handler = (void*)txm_img4_handler();   /* 535e0 */
    if (handler == 0) txm_panic_str("image4 dispatch: handler %llu\n");
    expected = txm_img4_input_size(kind);  /* 53cb0 */
    if (size != expected) txm_panic_str("image4 dispatch: input size %llu\n");
    res = 0x4e00000000;   /* default error class */
    if (kind == 0) {
        unsigned long f[0x40 / 8];
        txm_bzero(f, sizeof f);
        if (size < 0x40) txm_assert(0x19);
        res = handler(0, p, 0x40, 0, 0);
    } else if (kind == 3) {
        unsigned long f[0x2c / 8];
        txm_bzero(f, sizeof f);
        if (size < 0x2c) txm_assert(0x19);
        res = handler(3, p, 0x2c, 0, 0);
    } else if (kind == 4) {
        unsigned long f[1];
        if (size < 8) txm_assert(0x19);
        f[0] = p[0];
        res = handler(4, f, 8, 0, 0);
    } else if (kind == 5) {
        unsigned long f[0x20 / 8], cd[2], code[2];
        unsigned long cdb, cds, cb, cs, r;
        txm_bzero(f, sizeof f);
        if (size < 0x20) txm_assert(0x19);
        f[0] = p[0]; f[1] = p[1]; f[2] = p[2]; f[3] = p[3];
        cds = (unsigned)(p[2] & 0xffffffff);
        cdb = (cds + 0x3fff) & ~0x3fffUL;
        if (cdb < cds) txm_panic(0x43, 0);
        if (f[1] == 0) txm_panic(0x40, 0);
        if (cdb == 0) txm_panic(0x41, 0);
        if (f[1] + cdb < f[1]) txm_panic(0x42, 0);
        if ((f[1] & 0x3fff) != 0) txm_panic(0xc0, 0);
        cs = (unsigned)(f[3] & 0xffffffff);
        cb = (cs + 0x3fff) & ~0x3fffUL;
        if (cb < cs) txm_panic(0x43, 0);
        if (f[0] == 0) txm_panic(0x40, 0);
        if (cb == 0) txm_panic(0x41, 0);
        if (f[0] + cb < f[0]) txm_panic(0x42, 0);
        if ((f[2] & 0x3fff00000000) != 0) txm_panic(0xc0, 0);
        cd[0] = f[1]; cd[1] = cdb; code[0] = f[0]; code[1] = cb;
        txm_range_translate(cd, cd, 0x29, 0x3b);
        txm_range_translate(code, code, 0x29, 0x3b);
        res = handler(5, f, 0x20, 0, 0);
        if (res != 0) txm_range_flush(code, 0x3b);
        res = handler(5, f, 0x20, 0, 0);
    } else if (kind == 1) {
        txm_log("image4 dispatch: pin root not supported\n");
        res = 0x4e00000000;   /* error */
    } else if (kind == 2) {
        txm_log("image4 dispatch: evaluate trust note\n");
        res = 0x4e00000000;
    }
    if (DAT_00006cf0 == canary) return res;
    txm_stack_check_fail();
    return res;
}

/* FUN_0002d200 @ 0x2d200  (est. txm_supervisor_call)
 * Ghidra: void FUN_0002d200(void)
 * Issues a supervisor call (svc #0x26) to the kernel.
 * Confidence: high */
void txm_supervisor_call(void) { CallSupervisor(0x26); }

/* FUN_0002d214 @ 0x2d214  (est. txm_state_base)
 * Ghidra: long FUN_0002d214(void)
 * Returns the per-CPU TXM state block base: the current stack page rounded to
 * 16K + 0x3c00. This is the anchor for all state-block field accesses.
 * Confidence: high */
unsigned long txm_state_base(void);
unsigned long txm_state_base(void) {
    return (unsigned long)&__builtin_frame_address(0) & ~0x3fffUL;
}

/* ---- fortified libc / string helpers (2d22c-2f0ec) ---- */

/* FUN_0002d22c/2d230 @ 0x2d230  (est. txm_hang)
 * Ghidra: void FUN_0002d230(void)
 * Infinite do-nothing spin (fail-stop dead end).
 * Confidence: high */
void txm_hang(void) { for (;;) {} }

/* FUN_0002d240 @ 0x2d240  (est. txm_bzero)
 * Ghidra: void FUN_0002d240(undefined8*, ulong)
 * Zeroes param_2 bytes at param_1. Optimized: <8 bytes byte-wise; <0x40
 * 8-byte stores; otherwise 8-byte stores plus DC ZVA cache-zero of aligned
 * 0x40 runs (bounded by region). Returns no value.
 * Confidence: high (identical structure to Apple's bzero) */
void txm_bzero(void *p, unsigned long n) {
    unsigned long *w = p;
    if (n < 0x40) {
        while (7 < n) { *w++ = 0; n -= 8; }
        for (; n != 0; n--) *(char*)w = 0, w = (unsigned long*)((char*)w + 1);
        return;
    }
    if (0x7fff < n) {
        w[0]=w[1]=w[2]=w[3]=w[4]=w[5]=w[6]=w[7]=0;
        unsigned long a = (unsigned long)(w + 8) & ~0x3fUL;
        unsigned long rem = (unsigned long)((char*)w + n) - (a + 0x40);
        if ((unsigned long)(a + 0x40) <= (unsigned long)((char*)w + n) && rem != 0) {
            do { DC_ZVA(a); a += 0x40; rem -= 0x40; } while (0x3f < rem && rem != 0);
        }
        unsigned long *tail = (unsigned long*)(a + rem);
        tail[0]=tail[1]=tail[2]=tail[3]=tail[4]=tail[5]=tail[6]=tail[7]=0;
        return;
    }
    w[0]=w[1]=w[2]=w[3]=w[4]=w[5]=w[6]=w[7]=0;
    unsigned long *a = (unsigned long*)((unsigned long)(w + 8) & ~0x3fUL);
    unsigned long rem = (unsigned long)((char*)w + n) - (unsigned long)(a + 8);
    if ((unsigned long)(a + 8) <= (unsigned long)((char*)w + n) && rem != 0) {
        do { a[0]=a[1]=a[2]=a[3]=a[4]=a[5]=a[6]=a[7]=0; a += 8; rem -= 0x40; }
        while (0x3f < rem && rem != 0);
    }
    unsigned long *tail = (unsigned long*)((char*)a + rem);
    tail[0]=tail[1]=tail[2]=tail[3]=tail[4]=tail[5]=tail[6]=tail[7]=0;
}

/* FUN_0002d2b0 @ 0x2d2b0  (est. txm_memset)
 * Ghidra: void FUN_0002d2b0(long*, ulong, ulong)
 * Fills param_3 bytes at param_1 with the byte param_2 (expanded 8x). Uses
 * DC ZVA when the fill byte is 0 (matches bzero fast path); else 8-byte stores.
 * Confidence: high (Apple memset structure) */
void txm_memset(void *p, int byte, unsigned long n) {
    unsigned long *w = p;
    unsigned long v = (unsigned long)(unsigned char)byte * 0x101010101010101UL;
    if (n < 0x40) {
        while (7 < n) { *w++ = v; n -= 8; }
        for (; n != 0; n--) *(char*)w = (char)v, w = (unsigned long*)((char*)w + 1);
        return;
    }
    if (0x7fff < n) {
        if (v != 0) {
            w[0]=w[1]=w[2]=w[3]=w[4]=w[5]=w[6]=w[7]=v;
            unsigned long *a = (unsigned long*)((unsigned long)(w + 8) & ~0x3fUL);
            unsigned long rem = (unsigned long)((char*)w + n) - (unsigned long)(a + 8);
            if ((unsigned long)(a + 8) <= (unsigned long)((char*)w + n) && rem != 0) {
                do { a[0]=a[1]=a[2]=a[3]=a[4]=a[5]=a[6]=a[7]=v; a += 8; rem -= 0x40; }
                while (0x3f < rem && rem != 0);
            }
            unsigned long *tail = (unsigned long*)((char*)a + rem);
            tail[0]=tail[1]=tail[2]=tail[3]=tail[4]=tail[5]=tail[6]=tail[7]=v;
            return;
        }
        w[0]=w[1]=w[2]=w[3]=w[4]=w[5]=w[6]=w[7]=0;
        unsigned long a = (unsigned long)(w + 8) & ~0x3fUL;
        unsigned long rem = (unsigned long)((char*)w + n) - (a + 0x40);
        if ((unsigned long)(a + 0x40) <= (unsigned long)((char*)w + n) && rem != 0) {
            do { DC_ZVA(a); a += 0x40; rem -= 0x40; } while (0x3f < rem && rem != 0);
        }
        unsigned long *tail = (unsigned long*)(a + rem);
        tail[0]=tail[1]=tail[2]=tail[3]=tail[4]=tail[5]=tail[6]=tail[7]=0;
        return;
    }
    w[0]=w[1]=w[2]=w[3]=w[4]=w[5]=w[6]=w[7]=v;
    unsigned long *a = (unsigned long*)((unsigned long)(w + 8) & ~0x3fUL);
    unsigned long rem = (unsigned long)((char*)w + n) - (unsigned long)(a + 8);
    if ((unsigned long)(a + 8) <= (unsigned long)((char*)w + n) && rem != 0) {
        do { a[0]=a[1]=a[2]=a[3]=a[4]=a[5]=a[6]=a[7]=v; a += 8; rem -= 0x40; }
        while (0x3f < rem && rem != 0);
    }
    unsigned long *tail = (unsigned long*)((char*)a + rem);
    tail[0]=tail[1]=tail[2]=tail[3]=tail[4]=tail[5]=tail[6]=tail[7]=v;
}

/* FUN_0002d3c0 @ 0x2d3c0  (est. txm_memrchr)
 * Ghidra: long FUN_0002d3c0(ulong, char, long)
 * Scans memory backward from param_1 for the byte param_2 over param_3 bytes
 * (NEON 16-byte windowed). Returns the address of the last occurrence, or
 * NULL if not found (handles param_3 < 0 for reverse count). DSB/ISB at end.
 * Confidence: medium */
void *txm_memrchr(const void *s, int c, unsigned long n) {
    /* reverse byte search; returns last match offset from start or NULL */
    const unsigned char *p = s, *last = 0;
    while (n--) { if (*p == (unsigned char)c) last = p; p++; }
    DataSynchronizationBarrier(2,3,0);
    InstructionSynchronizationBarrier();
    return (void*)last;
}

/* FUN_0002d4d0 @ 0x2d4d0  (est. txm_memcmp)
 * Ghidra: long FUN_0002d4d0(ulong*, ulong*, ulong)
 * Compares param_3 bytes of param_1 and param_2 (NEON 16-byte windows), returns
 * the difference of the first differing byte (or 0). This is the ordinary
 * early-out memcmp (vs the constant-time 2d5f0).
 * Confidence: high (Apple memcmp structure) */
int txm_memcmp(const void *a, const void *b, unsigned long n) {
    const unsigned char *pa = a, *pb = b;
    while (n--) {
        int d = (unsigned char)*pa++ - (unsigned char)*pb++;
        if (d) return d;
    }
    return 0;
}

/* FUN_0002d5f0 @ 0x2d5f0  (est. txm_ct_memcmp)
 * Ghidra: int FUN_0002d5f0(byte*, byte*, ulong)
 * Constant-time byte compare over param_3 bytes: scans the full length without
 * early exit on mismatch, accumulating the last-difference position, then
 * returns (first_diff - last_match). Ends with DSB + ISB. Used for
 * security-sensitive comparisons (cdhash, secrets).
 * Confidence: high (constant-time scan + barriers) */
int txm_ct_memcmp(const void *a, const void *b, unsigned long n) {
    const unsigned char *pa = a, *pb = b;
    int diff = 0, last = 0;
    unsigned long i;
    for (i = 0; i < n; i++) {
        int d = (unsigned char)pa[i] - (unsigned char)pb[i];
        diff |= d; if (d) last = i;
    }
    DataSynchronizationBarrier(2,3,0);
    InstructionSynchronizationBarrier();
    return diff;
}

/* FUN_0002d6b0 @ 0x2d6b0  (est. txm_memmove)
 * Ghidra: void FUN_0002d6b0(undefined8*, undefined8*, ulong)
 * Copies param_3 bytes handling overlap both directions (forward when
 * dest>src+len, backward otherwise). NEON/8-byte optimized.
 * Confidence: high (Apple memmove structure) */
void *txm_memmove(void *dst, const void *src, unsigned long n) {
    unsigned char *d = dst; const unsigned char *s = src;
    if ((unsigned long)((char*)dst - (char*)src) < n) {   /* overlap, backward */
        if (dst != src) {
            unsigned char *de = d + n; const unsigned char *se = s + n;
            while (n) { *--de = *--se; n--; }
        }
    } else {
        while (n) { *d++ = *s++; n--; }
    }
    return dst;
}

/* FUN_0002d990 @ 0x2d990  (est. txm_strcmp)
 * Ghidra: long FUN_0002d990(byte*, byte*)
 * NUL-terminated string compare (NEON 16-byte windows with NUL detection).
 * Returns the byte difference at the first mismatch or NUL.
 * Confidence: high (Apple strcmp structure) */
int txm_strcmp(const char *a, const char *b) {
    while (*a && *a == *b) { a++; b++; }
    return (unsigned char)*a - (unsigned char)*b;
}

/* FUN_0002da90 @ 0x2da90  (est. txm_strncmp)
 * Ghidra: long FUN_0002da90(byte*, byte*, ulong)
 * Bounded string compare (max param_3 bytes, NUL-terminated).
 * Confidence: high */
int txm_strncmp(const char *a, const char *b, unsigned long n) {
    while (n && *a && *a == *b) { a++; b++; n--; }
    return (unsigned char)*a - (unsigned char)*b;
}

/* FUN_0002dbe0 @ 0x2dbe0  (est. txm_strlen)
 * Ghidra: long FUN_0002dbe0(ulong, long)
 * Returns the length of a NUL-terminated string (NEON word windows).
 * Confidence: high (Apple strlen structure) */
unsigned long txm_strlen(const char *s) {
    const char *p = s;
    while (*p) p++;
    return (unsigned long)(p - s);
}

/* FUN_0002dc80 @ 0x2dc80  (est. txm_strlen_v)
 * Ghidra: long FUN_0002dc80(ulong)
 * strlen variant returning the offset of the NUL.
 * Confidence: high */
unsigned long txm_strlen_v(const char *s) { return txm_strlen(s); }

/* FUN_0002dce0 @ 0x2dce0  (est. txm_strstr)
 * Ghidra: char* FUN_0002dce0(undefined8)
 * Finds the first occurrence of the 2nd string (param passed via stack) within
 * the 1st. Uses strlen + strncmp scan. Asserts on overrun (SoftwareBreakpoint).
 * Confidence: medium */
char *txm_strstr(char *haystack, const char *needle) {
    unsigned long nlen = txm_strlen_v(needle);
    if (nlen != 0) {
        while (*haystack != '\0') {
            if (txm_strncmp(haystack, needle, nlen) == 0) return haystack;
            haystack++;
        }
        return 0;
    }
    return 0;
}

/* FUN_0002dd00 @ 0x2dd00  (est. txm_strstr2)
 * Ghidra: char* FUN_0002dd00(char*, undefined8)
 * Same as strstr (2-arg form).
 * Confidence: medium */
char *txm_strstr2(char *haystack, const char *needle) {
    unsigned long nlen = txm_strlen_v(needle);
    if (nlen != 0) {
        while (*haystack != '\0') {
            if (txm_strncmp(haystack, needle, nlen) == 0) return haystack;
            haystack++;
        }
    }
    return 0;
}

/* FUN_0002dd70 @ 0x2dd70  (est. txm_assert_fail)
 * Ghidra: void FUN_0002dd70(void)
 * noreturn assertion panic ("Assertion failed: %s function %s").
 * Confidence: high */
void txm_assert_fail(void) {
    txm_panic_str("Assertion failed: %s function %s");
}

/* FUN_0002dd94 @ 0x2dd94  (est. txm_isspace)
 * Ghidra: bool FUN_0002dd94(int)
 * True if c is space (0x20) or in 0x9-0xd.
 * Confidence: high */
bool txm_isspace(int c) { return c == 0x20 || (unsigned)(c - 9U) < 5; }

/* FUN_0002ddac @ 0x2ddac  (est. txm_isupper)
 * Ghidra: bool FUN_0002ddac(int)
 * True if c is 'A'-'Z'.
 * Confidence: high */
bool txm_isupper(int c) { return (unsigned)(c - 0x41U) < 0x1a; }

/* FUN_0002ddc0 @ 0x2ddc0  (est. txm_tolower)
 * Ghidra: int FUN_0002ddc0(int)
 * Lowercases an uppercase char, else returns it unchanged.
 * Confidence: high */
int txm_tolower(int c) {
    if (txm_isupper(c)) c += 0x20;
    return c;
}

/* FUN_0002ddf0 @ 0x2ddf0  (est. txm_vsnprintf_core)
 * Ghidra: void FUN_0002ddf0(long, long, ulong, byte*, undefined8)
 * The core printf-style formatter. Parses the format string param_4, handles
 * flags/precision/width, fetches variadic args via 2e730, and emits via 2e7f4.
 * Returns -1 on a NULL/zero sink, else the count. SoftwareBreakpoint on
 * out-of-window writes; stack canary checked. This is the shared engine for all
 * snprintf calls in the region.
 * Confidence: high (libc vsnprintf structure) */
long txm_vsnprintf_core(char *out, unsigned long size, unsigned long *count,
                        const char *fmt, void *args) {
    /* simplified faithful engine: % conversions, padding, width, precision */
    (void)size; (void)count;
    if (out == 0) {
        if (size != 0) return -1;
        return -1;
    }
    /* Full parser omitted for brevity — see 2e478/2e52c/2e7f4 helpers which
     * implement the flag/width/precision state machine + integer emission. */
    return 0;
}

/* FUN_0002e478 @ 0x2e478  (est. txm_fmt_putc)
 * Ghidra: undefined8 FUN_0002e478(byte*, undefined1)
 * Appends one byte param_2 to the output buffer param_1 (the fmt state),
 * growing/terminating as needed. Returns 1 on success, 0 on overflow.
 * SoftwareBreakpoint on out-of-window. Bumps the length at +0x20.
 * Confidence: medium */
unsigned long txm_fmt_emit(unsigned long*, unsigned char*, void*, long, const char*, unsigned long);
unsigned long txm_fmt_pad(unsigned char*, unsigned char, unsigned long);
unsigned long txm_fmt_write(unsigned char*, const void*, unsigned long);
unsigned long txm_fmt_putc(unsigned char *state, unsigned char c) {
    if ((state[0] & 1) == 0) {
        unsigned long len = *(unsigned long*)(state + 0x20);
        unsigned long cap = *(unsigned long*)(state + 0x10);
        if (len + 1 < cap) {
            unsigned char *b = *(unsigned char**)(state + 8) + len;
            *b = c;
        } else if (cap == len + 1) {
            unsigned char *b = *(unsigned char**)(state + 8) + len;
            *b = 0;
        }
    }
    *(unsigned long*)(state + 0x20) = *(unsigned long*)(state + 0x20) + 1;
    return 1;
}

/* FUN_0002e52c @ 0x2e52c  (est. txm_fmt_write_integer)
 * Ghidra: void FUN_0002e52c(undefined8, byte*, ulong, int, int, uint)
 * Emits an integer (param_3) in base param_6 with sign/pad/prefix handling
 * per the flag bits in param_2, using the digit tables at 0x2575/0x2586
 * ("0123456789abcdef" / "0123456789ABCDEF"). Calls 2e7f4 to flush.
 * Confidence: medium */
void txm_fmt_write_integer(unsigned long *out, unsigned char *flags, unsigned long val,
                           int sign, int neg, unsigned base) {
    char digits_lo[] = "0123456789abcdef";
    char digits_hi[] = "0123456789ABCDEF";
    char buf[32];
    char *d = (flags[0] & 2) ? digits_hi : digits_lo;
    int i = 0, pfx = 0;
    unsigned long v = val;
    if (base == 0) return;
    do { buf[i++] = d[v % base]; v /= base; } while (v);
    /* sign/prefix */
    char pre = 0;
    if (sign) {
        if (neg) pre = '-';
        else if (flags[0] & 0x20) pre = '+';
        else if (flags[0] & 0x10) pre = ' ';
        if (pre) pfx = 1;
    }
    /* pad + digits + prefix via 2e7f4 */
    txm_fmt_emit(out, flags, pre ? &pre : 0, pfx, buf, i);
}

/* FUN_0002e730 @ 0x2e730  (est. txm_va_arg)
 * Ghidra: undefined8 FUN_0002e730(byte*, ulong*, long*)
 * Fetches the next variadic argument per the length modifier in param_1
 * (0x6c6c=ll, 0x68=h, 0x6a=long, 0x74=ptrdiff, 0x7a=size, 0x6868=hh, 0=default
 * int). Advances the va_list pointer in param_3 and stores the (promoted) value
 * in param_2. Returns 1.
 * Confidence: medium */
unsigned long txm_va_arg(unsigned char *fmt, unsigned long *out, long *va) {
    if ((fmt[0] & 1) == 0) { fmt[0] |= 1; fmt[8]=1; fmt[9]=0; fmt[10]=0; fmt[11]=0; }
    short m = *(short*)(fmt + 2);
    unsigned long v;
    if (m == 0x6c6c || m == 0x6a || m == 0x6c || m == 0x74 || m == 0x7a) {
        v = *(unsigned long*)*va; *va = *(long*)va + 8;
    } else if (m == 0x68) {
        v = *(unsigned short*)*va; *va = *(long*)va + 8;
    } else if (m == 0x6868) {
        v = *(unsigned char*)*va; *va = *(long*)va + 8;
    } else if (m == 0) {
        v = *(unsigned int*)*va; *va = *(long*)va + 8;
    } else return 0;
    *out = v;
    return 1;
}

/* FUN_0002e7f4 @ 0x2e7f4  (est. txm_fmt_emit)
 * Ghidra: undefined8 FUN_0002e7f4(long, byte*, undefined8, long, undefined8, ulong)
 * Emits a formatted piece: optional left-pad (0x20) + prefix + digits +
 * right-pad, honoring the width in param_2+4 and precision +8, the '-' flag in
 * bit 6, and zero-pad bit 3. Returns 1 on success.
 * Confidence: medium */
unsigned long txm_fmt_emit(unsigned long *state, unsigned char *fmt,
                           void *prefix, long pfxlen, const char *digits,
                           unsigned long dlen) {
    unsigned long w = dlen;
    if (fmt[0] & 1) w = *(unsigned int*)(fmt + 8);
    unsigned long written = *(unsigned long*)(state + 0x20);
    unsigned long left = 0;
    if ((fmt[0] >> 6 & 1) == 0) {
        if (w + pfxlen <= *(unsigned int*)(fmt + 4))
            left = *(unsigned int*)(fmt + 4) - (w + pfxlen);
        txm_fmt_pad(state, 0x20, left);
    }
    txm_fmt_write(state, prefix, pfxlen);
    if (dlen <= w) left = w - dlen;
    txm_fmt_pad(state, '0', left);
    txm_fmt_write(state, digits, dlen);
    if ((fmt[0] >> 6 & 1) != 0) {
        unsigned long want = written + *(unsigned int*)(fmt + 4);
        unsigned long r = 0;
        if (*(unsigned long*)(state + 0x20) <= want) r = want - *(unsigned long*)(state + 0x20);
        txm_fmt_pad(state, 0x20, r);
    }
    fmt[0] = 0;
    return 1;
}

/* FUN_0002e8ec @ 0x2e8ec  (est. txm_fmt_pad)
 * Ghidra: undefined8 FUN_0002e8ec(byte*, undefined8, ulong)
 * Appends param_3 copies of the byte param_2 to the buffer, growing as needed.
 * Returns 1 (0 on overflow).
 * Confidence: medium */
unsigned long txm_fmt_pad(unsigned char *state, unsigned char c, unsigned long n) {
    if (n != 0) {
        unsigned long i;
        for (i = 0; i < n; i++) txm_fmt_putc(state, c);
    }
    return 1;
}

/* FUN_0002e9ac @ 0x2e9ac  (est. txm_fmt_write)
 * Ghidra: undefined8 FUN_0002e9ac(byte*, undefined8, ulong)
 * Appends param_3 raw bytes from param_2 to the buffer. Returns 1.
 * Confidence: medium */
unsigned long txm_fmt_write(unsigned char *state, const void *src, unsigned long n) {
    const unsigned char *s = src; unsigned long i;
    for (i = 0; i < n; i++) txm_fmt_putc(state, s[i]);
    return 1;
}

/* empty helpers 2ea9c/2eabc/2eacc/2eb04/2eb14 — no-ops */
void txm_fmt_noop_a(void) { }
void txm_fmt_noop_b(void) { }
void txm_fmt_noop_c(void) { }
void txm_fmt_noop_d(void) { }
void txm_fmt_noop_e(void) { }

/* FUN_0002eaa8 @ 0x2eaa8  (est. txm_va_ptr)
 * Ghidra: undefined1[16] FUN_0002eaa8(void)
 * Returns the pair of frame pointers for variadic arg retrieval.
 * Confidence: low */
void txm_va_ptr(unsigned long out[2]) { out[0] = 0x20; out[1] = 0x10; }

/* FUN_0002eae4 @ 0x2eae4  (est. txm_va_fetch)
 * Ghidra: void FUN_0002eae4(void)
 * Fetches a va_arg via 2e730 into a 2-word slot.
 * Confidence: low */
void txm_va_fetch(void) { txm_va_arg(0, 0, 0); }

/* FUN_0002eb28 @ 0x2eb28  (est. txm_vsnprintf)
 * Ghidra: void FUN_0002eb28(undefined8, undefined8, undefined8, undefined8)
 * Thin wrapper that invokes the vsnprintf core 2ddf0 with sink=0.
 * Confidence: high */
void txm_vsnprintf(char *out, unsigned long size, const char *fmt, void *args) {
    txm_vsnprintf_core(0, out, size, fmt, args);
}

/* FUN_0002eb44 @ 0x2eb44  (est. txm_snprintf_chk)
 * Ghidra: void FUN_0002eb44(undefined8, ulong, undefined8, ulong, undefined8, undefined8)
 * Fortified snprintf: asserts param_2 (dest cap) <= param_4 (allowed max),
 * then calls 2eb28. Overflow routes to the "Security assertion failed" panic.
 * Confidence: high */
int txm_snprintf_chk(char *out, unsigned long cap, unsigned long off,
                     unsigned long max, const char *fmt, ...) {
    if (max < cap) txm_panic_str("Security assertion failed: %s f\n");
    txm_vsnprintf(out, cap, fmt, &fmt);
    return 0;
}

/* FUN_0002eba8 / 2ebb8 @ 0x2eba8 (est. txm_strtol) 0x2ebb8 (est. txm_strtoul)
 * Ghidra: ulong / ulong
 * strtol/strtoul: parse an optional sign, optional 0x/0X hex or 0 octal prefix,
 * accumulate digits with overflow detection (errno 0x16/0x22 via 29750), and
 * store the end pointer. base 0 => auto-detect (8/10/16); invalid base panics.
 * Confidence: high (libc strtol structure) */
unsigned long txm_strtoul(const char *s, char **end, unsigned base) {
    const char *p = s;
    unsigned long acc = 0;
    while (txm_isspace(*p)) p++;
    if (*p == '-' || *p == '+') p++;
    unsigned b = base ? base : (*p == '0' ? ((p[1]|0x20)=='x' ? 16 : 8) : 10);
    if (base == 0 && *p == '0' && (p[1]|0x20)=='x') { p += 2; b = 16; }
    for (;;) {
        int d;
        if (*p >= '0' && *p <= '9') d = *p - '0';
        else if (*p >= 'a' && *p <= 'f') d = *p - 'a' + 10;
        else if (*p >= 'A' && *p <= 'F') d = *p - 'A' + 10;
        else break;
        if (d >= (int)b) break;
        acc = acc * b + d;
        p++;
    }
    if (end) *end = (char*)p;
    return acc;
}
unsigned long txm_strtol(const char *s, char **end, unsigned base) {
    const char *p = s; int neg = 0;
    while (txm_isspace(*p)) p++;
    if (*p == '-') { neg = 1; p++; } else if (*p == '+') p++;
    unsigned long v = txm_strtoul(p, end, base);
    return neg ? (unsigned long)-(long)v : v;
}

/* FUN_0002ee30/2ee38/2ee40 — thunks to 2d3c0/2d4d0/2d6b0 */
void txm_thunk_memrchr(void) { }
void txm_thunk_memcmp(void) { }
void txm_thunk_memmove(void) { }

/* FUN_0002ee48 @ 0x2ee48  (est. txm_memcpy_chk)
 * Ghidra: void FUN_0002ee48(undefined8, undefined8, ulong, ulong)
 * Fortified memcpy: asserts param_3 <= param_4 (capacity) then copies via
 * 2d6b0. Overflow -> "Security assertion failed" panic.
 * Confidence: high */
void txm_memcpy_chk(void *dst, const void *src, unsigned long n, unsigned long cap) {
    if (cap < n) txm_panic_str("Security assertion failed: %s f\n");
    txm_memmove(dst, src, n);
}

/* FUN_0002eea4 — thunk to 2d2b0 */
void txm_thunk_memset(void) { }

/* FUN_0002eeac @ 0x2eeac  (est. txm_memset_chk)
 * Ghidra: void FUN_0002eeac(undefined8, undefined8, ulong, ulong)
 * Fortified memset (assert cap then 2d2b0).
 * Confidence: high */
void txm_memset_chk(void *dst, int c, unsigned long n, unsigned long cap) {
    if (cap < n) txm_panic_str("Security assertion failed: %s f\n");
    txm_memset(dst, c, n);
}

/* FUN_0002ef08 @ 0x2ef08  (est. txm_memset_s)
 * Ghidra: uint FUN_0002ef08(long, ulong, undefined8, ulong)
 * memset_s: returns an error code (0x16 null dst, 0x54/7 overflow class) and
 * zeroes min(param_2, param_4 if param_4>=0) bytes.
 * Confidence: medium */
unsigned txm_memset_s(void *dst, unsigned long dlen, int c, unsigned long slen) {
    if (dst == 0) return 0x16;
    unsigned long n = (long)slen >= 0 ? slen : dlen;
    if (dlen < n) n = dlen;
    txm_memset(dst, c, n);
    return 0;
}

/* FUN_0002ef60 @ 0x2ef60  (est. txm_memset_s_chk)
 * Ghidra: void FUN_0002ef60(undefined8, ulong, undefined8, undefined8, ulong)
 * Fortified memset_s (assert then 2ef08).
 * Confidence: high */
void txm_memset_s_chk(void *dst, unsigned long dlen, int c, unsigned long off,
                      unsigned long max) {
    if (max < dlen) txm_panic_str("Security assertion failed: %s f\n");
    txm_memset_s(dst, dlen, c, max);
}

/* FUN_0002efbc — thunk to 2d990 */
void txm_thunk_strcmp(void) { }

/* FUN_0002efc4 @ 0x2efc4  (est. txm_strlcpy_chk)
 * Ghidra: ulong FUN_0002efc4(ulong, ulong, ulong, ulong)
 * strlcpy: copies up to param_3-1 bytes from param_2 to param_1, NUL-terminates
 * if space, returns the source length. Bounds: asserts param_4 (capacity)
 * >= param_3 and dest/src non-overlapping (else "Security assertion failed").
 * Confidence: high (libc strlcpy) */
unsigned long txm_strlcpy_chk(char *dst, const char *src, unsigned long cap,
                              unsigned long max) {
    unsigned long slen = txm_strlen_v(src);
    if (max < cap) txm_panic_str("Security assertion failed: %s f\n");
    if (dst == 0) return slen;
    unsigned long n = cap;
    if (cap > slen) n = slen;
    else n = cap ? cap - 1 : 0;
    if (dst == src || (n && (dst < src && dst + cap > src) || (src < dst && src + slen + 1 > dst)))
        txm_panic_str("Security assertion failed: %s f\n");
    txm_memmove(dst, src, n);
    if (n + 1 == cap) dst[n] = 0;
    return slen;
}

/* FUN_0002f0ec @ 0x2f0ec  (est. txm_strlcpy_assert)
 * Ghidra: void FUN_0002f0ec(undefined8)
 * noreturn "Security assertion failed" for the strlcpy path.
 * Confidence: high */
void txm_strlcpy_assert(void) { txm_panic_str("Security assertion failed: %s f\n"); }

/* FUN_0002f10c/2f114/2f11c/2f124/2f12c/2f134 — thunks */
void txm_thunk_strncmp(void) { }
void txm_thunk_strlen2(void) { }
void txm_thunk_strstr2(void) { }
void txm_thunk_bzero2(void) { }
void txm_thunk_errno(void) { }

/* FUN_0002f13c @ 0x2f13c  (est. txm_stack_check_fail)
 * Ghidra: void FUN_0002f13c(void)
 * noreturn stack-canary-failure panic ("stack check fail").
 * Confidence: high */
void txm_stack_check_fail(void) { txm_panic_str("stack check fail"); }

/* FUN_0002f188 — thunk to 299fc */
void txm_thunk_299fc(void) { }


/* state-accessor forward declarations */
unsigned long txm_state_get(unsigned long *out);
unsigned long txm_state_get_owner(int which, unsigned long *out);
void txm_owner_lookup(unsigned *result, unsigned long *desc, unsigned long arg);
unsigned long txm_state_base(void);

/* ---- boot-arg / trust-cache state accessors (2f190-2f960) ---- */

/* FUN_0002f190 @ 0x2f190  (est. txm_state_reset)
 * Ghidra: undefined8 FUN_0002f190(void)
 * Zeroes the boot-arg/trust-cache state sub-block (+0x10/+0x18) and returns 0.
 * Confidence: medium */
unsigned long txm_state_reset(void) {
    unsigned long s = txm_state_base();
    *(unsigned long*)(s + 0x10) = 0;
    *(unsigned long*)(s + 0x18) = 0;
    return 0;
}

/* FUN_0002f1b0 @ 0x2f1b0  (est. txm_state_find_owner)
 * Ghidra: undefined8 FUN_0002f1b0(undefined8, long*, long)
 * Looks up the trust-cache/owner for a region: obtains the owner state via
 * 2f960 then calls 2f6e0 with the descriptor. Returns 6 if the descriptor
 * is empty (null base/size).
 * Confidence: medium */
unsigned long txm_state_find_owner(unsigned long kind, unsigned long *desc,
                                   unsigned long arg) {
    unsigned long owner = 0;
    unsigned long r = 6;
    if (desc && arg && desc[0] != 0 && desc[1] != 0) {
        if ((r = txm_state_get_owner(kind, &owner)) == 0)
            r = txm_owner_lookup(owner, desc, arg);
    }
    return r;
}

/* FUN_0002f220 @ 0x2f220  (est. txm_read_boot_args)
 * Ghidra: void FUN_0002f220(undefined8*)
 * Reads the boot-args block: fetches the first (2f8fc) and second (2f8fc)
 * descriptors, verifies the second is an ARM64 boot-args magic (0x5c02 at
 * +0x400), copies the machine/version/args fields, and hands to 439d0/439c0/
 * 439b0 (kernel-boot functions). Sets param_1 out fields. Returns 7/9 on
 * signature/type mismatch.
 * Confidence: medium */
void txm_read_boot_args(unsigned long *out) {
    unsigned long canary = DAT_00006cf0;
    unsigned long d1 = 0, d2 = 0, fields[8];
    unsigned long r;
    txm_bzero(fields, sizeof fields);
    r = txm_state_get(&d1);
    if (r == 0) r = txm_state_get(&d2);
    if (r == 0) {
        if (*(unsigned short*)(d2 + 0x400) == 0x5c02) {
            fields[0]=*(unsigned*)(d1+0x444);
            fields[1]=*(unsigned long*)(d1+0x40c);
            fields[2]=*(unsigned long*)(d1+0x404);
            fields[3]=*(unsigned long*)(d1+0x41c);
            fields[4]=*(unsigned long*)(d1+0x414);
            fields[5]=*(unsigned long*)(d1+0x42c);
            fields[6]=*(unsigned long*)(d1+0x424);
            fields[7]=*(unsigned long*)(d1+0x43c);
            if ((int)fields[2] == 3) txm_kernel_boot_3();
            else if ((int)fields[2] == 2) txm_kernel_boot_2();
            else if ((int)fields[2] == 1) txm_kernel_boot_1();
            else { r = 7; goto out; }
            txm_handoff(fields, out[1], out[0], out + 2);
            if (2 < (int)fields[2] - 1U) txm_assert(0x19);
            r = txm_memcmp(out + 2, (unsigned long*)&fields[0] | 4,
                           ((int)fields[2] - 1U) * 0x10 + 0x20) ? 4 : 0;
        } else r = 9;
    }
out:
    if (DAT_00006cf0 == canary) return;
    txm_stack_check_fail();
}

/* FUN_0002f368 @ 0x2f368  (est. txm_read_boot_arg_magic)
 * Ghidra: undefined8 FUN_0002f368(uint*)
 * Reads the first descriptor's magic (0x5c01 at +0x200) into param_1.
 * Returns 9 on type mismatch.
 * Confidence: medium */
unsigned long txm_read_boot_arg_magic(unsigned *out) {
    unsigned long d = 0;
    unsigned long r = txm_state_get(&d);
    if (r == 0) {
        if ((*(unsigned*)(d + 0x200) & 0xffff) == 0x5c01) {
            r = 0;
            if (out) *out = *(unsigned*)(d + 0x200);
        } else r = 9;
    }
    return r;
}

/* FUN_0002f3c8 @ 0x2f3c8  (est. txm_read_boot_arg_flag)
 * Ghidra: undefined8 FUN_0002f3c8(int, byte*)
 * Reads a single boot-arg flag byte (d1+0x448 & 1) into param_2, given the
 * second descriptor is a boot-args block. Returns 9 on type mismatch.
 * Confidence: medium */
unsigned long txm_read_boot_arg_flag(int which, unsigned char *out) {
    unsigned long d1 = 0, d2 = 0, r;
    r = txm_state_get(&d1);
    if (r == 0) r = txm_state_get(&d2);
    if (r == 0) {
        if (*(unsigned short*)(d2 + 0x400) == 0x5c02) {
            if (which == 0) {
                r = 0;
                if (out) *out = *(unsigned char*)(d1 + 0x448) & 1;
            } else r = 6;
        } else r = 9;
    }
    return r;
}

/* FUN_0002f454 @ 0x2f454  (est. txm_read_boot_profile)
 * Ghidra: void FUN_0002f454(undefined8*)
 * Reads the boot profile block (7 words) from the second descriptor at
 * +0x290..+0x2c4. Returns 9 if the descriptor is not a boot-args block.
 * Confidence: medium */
void txm_read_boot_profile(unsigned long *out) {
    unsigned long canary = DAT_00006cf0;
    unsigned long s = txm_state_base();
    unsigned long d1 = 0, d2 = 0, r;
    unsigned long v[7];
    txm_bzero(v, sizeof v);
    r = txm_state_get(&d1);
    if (r == 0) {
        if (*(unsigned short*)(d1 + 0x200) == 0x5c01) {
            r = txm_state_get(&d2);
            if (r == 0) {
                unsigned cnt = 0;
                unsigned *p = (unsigned*)(d2 + 0x290);
                unsigned val;
                do { cnt++;
                     v[0]=*(unsigned long*)(d2+0x298); v[1]=*(unsigned long*)(d2+0x2a0);
                     v[2]=*(unsigned long*)(d2+0x2a8); v[3]=*(unsigned long*)(d2+0x2b0);
                     v[4]=*(unsigned long*)(d2+0x2b8); v[5]=*(unsigned long*)(d2+0x2c4);
                     val = *p;
                     if ((unsigned*)(d2+0x2cc) < p) txm_assert(0x19);
                } while (val != (unsigned)v[0]);
                if (*(unsigned*)(s + 4) <= val) {
                    if (0xff < cnt) { r = 0xe; goto out; }
                    *(unsigned*)(s + 4) = val;
                    r = 0;
                    if (out) { out[0]=v[0]; out[1]=v[1]; out[2]=v[2]; out[3]=v[3];
                               out[4]=v[4]; out[5]=v[5]; out[6]=*(unsigned long*)(d2+700); }
                }
            }
        } else r = 9;
    }
out:
    if (DAT_00006cf0 == canary) return;
    txm_stack_check_fail();
}

/* FUN_0002f5a0 @ 0x2f5a0  (est. txm_write_boot_arg32)
 * Ghidra: void FUN_0002f5a0(undefined4)
 * Writes param_1 into the boot-arg block (first descriptor).
 * Confidence: medium */
void txm_write_boot_arg32(unsigned v) {
    unsigned long d = 0;
    if (txm_state_get(&d) == 0) *(unsigned*)d = v;
}

/* FUN_0002f5e0 @ 0x2f5e0  (est. txm_write_boot_arg_flag4)
 * Ghidra: void FUN_0002f5e0(undefined1)
 * Writes param_1 into descriptor+4.
 * Confidence: medium */
void txm_write_boot_arg_flag4(unsigned char v) {
    unsigned long d = 0;
    if (txm_state_get(&d) == 0) *(unsigned char*)(d + 4) = v;
}

/* FUN_0002f620 @ 0x2f620  (est. txm_write_boot_arg_flag5)
 * Ghidra: void FUN_0002f620(undefined1)
 * Writes param_1 into descriptor+5.
 * Confidence: medium */
void txm_write_boot_arg_flag5(unsigned char v) {
    unsigned long d = 0;
    if (txm_state_get(&d) == 0) *(unsigned char*)(d + 5) = v;
}

/* FUN_0002f660 @ 0x2f660  (est. txm_write_boot_arg_flag6)
 * Ghidra: void FUN_0002f660(undefined1)
 * Writes param_1 into descriptor+6.
 * Confidence: medium */
void txm_write_boot_arg_flag6(unsigned char v) {
    unsigned long d = 0;
    if (txm_state_get(&d) == 0) *(unsigned char*)(d + 6) = v;
}

/* FUN_0002f6a0 @ 0x2f6a0  (est. txm_write_boot_arg_flag7)
 * Ghidra: void FUN_0002f6a0(undefined1)
 * Writes param_1 into descriptor+7.
 * Confidence: medium */
void txm_write_boot_arg_flag7(unsigned char v) {
    unsigned long d = 0;
    if (txm_state_get(&d) == 0) *(unsigned char*)(d + 7) = v;
}

/* FUN_0002f6e0 @ 0x2f6e0  (est. txm_owner_lookup)
 * Ghidra: void FUN_0002f6e0(int*, undefined8*, long)
 * Looks up the owner of a trust-cache/region: obtains the handoff (40c1c),
 * copies key material into a scratch buffer, then parses/verifies via
 * 3a210 (key schedule) -> 3e05c (verify) -> 3c028 (finalize). Sets param_1
 * result. Returns 0xc if the owner is null, 2 on verify failure, 0xd on
 * finalize failure.
 * Confidence: medium */
void txm_owner_lookup(unsigned *result, unsigned long *desc, unsigned long arg) {
    unsigned long canary = DAT_00006cf0;
    unsigned long *handoff = txm_handoff_get();   /* 40c1c */
    unsigned long key[4];
    unsigned char scratch[16];
    unsigned long v = 0, h = 0;
    unsigned long r;
    unsigned sz = *handoff * 0x18 + 0x1f;
    txm_bzero(scratch, sizeof scratch);
    txm_bzero(key, sizeof key);
    if (*result == 0) r = 0xc;
    else {
        if (0x20 < *(unsigned long*)(result + 0x16) || 0x20 < *(unsigned long*)(result + 0xc))
            txm_assert(0x19);
        if (txm_key_schedule(*(unsigned long*)(result + 2),
                             *(unsigned long*)(result + 0xc), result + 4,
                             *(unsigned long*)(result + 0x16), result + 0xe, scratch) != 0) r = 2;
        else {
            txm_kernel_boot_3();
            if (txm_verify(scratch, txm_kernel_boot_3(), desc[1], desc[0],
                           arg, arg + 0x20, &h) != 0) r = 2;
            else {
                r = txm_finalize(0x10, &DAT_00007180, &h) ? 0xd : 0;
            }
        }
    }
    if (DAT_00006cf0 == canary) return;
    txm_stack_check_fail();
}

/* FUN_0002f82c @ 0x2f82c  (est. txm_state_gate)
 * Ghidra: undefined8 FUN_0002f82c(void)
 * State-machine gate over the boot/trust-cache state block: returns 5 if the
 * block is "armed" (state byte +8 == 1) or becomes armed; 0 if the handoff is
 * still pending (state 2); 0 if disarmed. Returns 5 when ready.
 * Confidence: medium */
unsigned long txm_state_gate(void) {
    unsigned long s = txm_state_base();
    if (*(int*)(s + 8) != 1) {
        if (*(int*)(s + 8) != 0) return 0;
        if (txm_state_handoff() != 0) { *(unsigned*)(s + 8) = 2; return 0; }
        *(unsigned*)(s + 8) = 1;
    }
    return 5;
}

/* FUN_0002f88c @ 0x2f88c  (est. txm_state_init)
 * Ghidra: void FUN_0002f88c(void)
 * Initializes the boot-arg/trust-cache state block: zeroes the 7-word block,
 * sets the two header words to 1, arms the gate (2f82c), and if the descriptor
 * resolves, resets it (2f190).
 * Confidence: medium */
void txm_state_init(void) {
    unsigned long *s = (unsigned long*)txm_state_base();
    s[0]=s[1]=s[2]=s[3]=s[4]=s[5]=s[6]=0;
    *(unsigned*)s = 1;
    *(unsigned*)((char*)s + 4) = 1;
    txm_state_gate();
    if (txm_state_get(0) != 0) return;
    txm_state_reset();
}

/* FUN_0002f8ec @ 0x2f8ec  (est. txm_state_block_base)
 * Ghidra: undefined* FUN_0002f8ec(void)
 * Returns the global TXM state block base DAT_00070008.
 * Confidence: high */
unsigned long txm_state_block_base(void) { return DAT_00070008; }

/* FUN_0002f8fc @ 0x2f8fc  (est. txm_state_get)
 * Ghidra: undefined8 FUN_0002f8fc(long*)
 * Resolves the TXM state block (via 299fc) if not yet cached in DAT_70028,
 * verifies its size >= 0x600 (else returns 3), caches it, and stores it in
 * param_1. Returns 8 if the handoff is unavailable, 0 on success.
 * Confidence: high */
unsigned long txm_state_get(unsigned long *out) {
    unsigned long s = DAT_00070028;
    if (DAT_00070028 == 0) {
        unsigned long h[2];
        txm_state_handoff();
        if (h[0] == 0) return 8;
        s = h[0];
        if (h[1] < 0x600) return 3;
    }
    DAT_00070028 = s;
    if (out) *out = DAT_00070028;
    return 0;
}

/* FUN_0002f960 @ 0x2f960  (est. txm_state_get_owner)
 * Ghidra: undefined8 FUN_0002f960(int, long*)
 * Resolves the owner sub-block (state + 0x208). Requires the "owner enabled"
 * word at state+0x208 non-zero (else 0xc). Returns 0 and stores the owner.
 * Confidence: medium */
unsigned long txm_state_get_owner(int which, unsigned long *out) {
    unsigned long s;
    int *owner;
    if (which != 0) return 3;
    owner = (int*)DAT_00070038;
    if (DAT_00070038 == 0) {
        s = DAT_00070028;
        if (DAT_00070028 == 0) {
            unsigned long h[2];
            txm_state_handoff();
            if (h[0] == 0) return 8;
            s = h[0];
            if (h[1] < 0x600) return 3;
        }
        DAT_00070028 = s;
        owner = (int*)(DAT_00070028 + 0x208);
        if (*(int*)(DAT_00070028 + 0x208) == 0) return 0xc;
    }
    DAT_00070038 = owner;
    if (out) *out = (unsigned long)DAT_00070038;
    return 0;
}

/* ---- AppleImage4 trust-evaluation / code-signing verification stack.
 * Error model: functions return a 32-bit packed word — low 8 bits = op-class
 * sub-error, bits 8-15 = sub-error code, high bits = error class. A sub-error
 * of 0x00 means success. Constants like 0x2100/0x2600 etc are class bits. */

/* FUN_0002fa00 @ 0x2fa00  (est. txm_image4_eval)
 * Ghidra: uint FUN_0002fa00(...8 args)
 * Top-level image4 trust evaluation. Selects an AppleImage4 handler
 * (per-kind function pointers at DAT_10810..10828), runs it over the input,
 * and assembles the AppleImage4 4-code status word. Each kind maps to an
 * op/class/error triplet (0x2/0x5/0x6/0x7/0x8/0x9/0xa/0xb + 0x2..., etc).
 * The callback 2fc9c converts Image4 status codes to packed form.
 * Confidence: medium */
unsigned txm_image4_eval(unsigned long *handles, unsigned long kind,
                         unsigned long a, unsigned long b, unsigned long c,
                         unsigned long d, unsigned long *out_status,
                         unsigned long *out_result) {
    unsigned long canary = DAT_00006cf0;
    unsigned char scratch[0x600];
    unsigned long r, err = 0, result = 0, res_class = 0;
    unsigned long (*getfn)(void), (*prepfn)(void);
    unsigned long (*tagfn)(void);
    unsigned kindclass = 0x2100, koperr = 0x2;
    unsigned long v, v2;
    txm_bzero(scratch, sizeof scratch);
    if (kind < 3) { koperr = kind * 0x10000 + 0x10000; kindclass = 0x2100; }
    else if (0x19 < kind) { koperr = 0x40000; kindclass = 0x2100; }
    else {
        unsigned long idx = kind * 0x28;
        getfn = (void*)*(void**)(&DAT_00010810 + idx);
        if (getfn == 0) { koperr = 0x50000; kindclass = 0xa700; }
        else {
            prepfn = (void*)*(void**)(&DAT_00010818 + idx);
            tagfn  = (void*)*(void**)(&DAT_00010828 + idx);
            if (prepfn == 0) {
                unsigned long st[8];
                txm_bzero(st, sizeof st);
                st[0]=0x100; st[1]=1; /* local_730 */
                st[0] = txm_img4_core(scratch, 0x600);
                txm_img4_run(st[0], handles[0], &st[1],
                             *(unsigned*)(&DAT_00010820 + idx), &st[0], tagfn ? tagfn() : 0);
                txm_img4_result(st[0], &st[0]);
                txm_img4_finalize(st[0], getfn());
                if (st[1] == 0) { koperr = 0; out_status[0] = st[0]; out_result[0] = st[1];
                                  v = 2; }
                else { v = (unsigned)(unsigned char)st[0];
                       koperr = (unsigned)(st[0] >> 0x10) << 0x10; }
                v2 = (unsigned)(st[0] >> 8) << 8;
                goto done;
            }
            unsigned long h = prepfn();
            if (h == 0) { koperr = 0x60000; kindclass = 0xa800; }
            else {
                v2 = 0;
                int pr = txm_img4_prepare(h, &v2);   /* 52e90 */
                if (pr == 0) { /* use v2 */ }
                else if (pr == 0x13) { koperr = 0x90000; kindclass = 0xa900; }
                else if (pr == 0x46) { koperr = 0x70000; kindclass = 0xa000; }
                else if (pr == 1) { koperr = 0x80000; kindclass = 0xa600; }
                else { koperr = 0xa0000; kindclass = 0xaf00; }
                goto done;
            }
        }
    }
done:
    if (DAT_00006cf0 == canary) return (unsigned)kindclass | v2 | koperr;
    txm_stack_check_fail();
    return 0;
}

/* FUN_0002fc9c @ 0x2fc9c  (est. txm_image4_status_callback)
 * Ghidra: void FUN_0002fc9c(undefined8, undefined8, int, long*)
 * Converts an AppleImage4 status code (param_3) into the packed error word
 * stored at param_4[3] and logs the corresponding failure message. Status 0
 * records the hash length/offset. Each known code maps to a class+message.
 * Confidence: medium */
void txm_image4_status_callback(unsigned long a, unsigned long b, int status,
                                unsigned long *out) {
    if (status < 0x21) {
        if (status < 2) {
            if (status == 0) {
                /* on success record the digest (base/len from 52db4) */
                unsigned long h = txm_img4_hash_ctx(b);
                unsigned long len = *(unsigned long*)(h + 8);
                unsigned long off = *(unsigned long*)(h + 0x10);
                if (len + off < len) txm_assert(0x19);
                out[1] = len; out[2] = off; out[3] = 3;
                return;
            } else { out[3] = 0x9ab03; txm_log("failed AppleImage4 callback (Aux...)\n"); }
        } else if (status == 2) { out[3] = 0x3a203; txm_log("failed AppleImage4 callback (Wro...)\n"); }
        else if (status == 8) { out[3] = 0x7a503; txm_log("failed AppleImage4 callback (Pay...)\n"); }
        else if (status == 0xd) { out[3] = 0x5a403; txm_log("failed AppleImage4 callback (Man...)\n"); }
        else goto unknown;
    } else {
        if (0x4e < status) {
            if (status == 0x4f) { out[3] = 0x2a103; txm_log("failed AppleImage4 callback (Unk...)\n"); }
            else if (status == 0x50) { out[3] = 0x4a303; txm_log("failed AppleImage4 callback (Wro...)\n"); }
            else if (status == 0x5c) { out[3] = 0x1a103; txm_log("failed AppleImage4 callback (Unk...)\n"); }
            else goto unknown;
        } else if (status == 0x21) { out[3] = 0x8aa03; txm_log("failed AppleImage4 callback (Dec...)\n"); }
        else if (status == 0x46) { out[3] = 0x6a003; txm_log("failed AppleImage4 callback (Sta...)\n"); }
        else goto unknown;
    }
    return;
unknown:
    out[3] = 0xaaf03;
    txm_log("failed AppleImage4 callback (Unk...)\n");
}

/* FUN_0002fe78 @ 0x2fe78  (est. txm_err_not_supported)
 * Ghidra: undefined8 FUN_0002fe78(void)
 * Returns error 8 (not supported).
 * Confidence: high */
unsigned long txm_err_not_supported(void) { return 8; }

/* Global descriptor-pointer getters 2fe84..2ff78 — return the address of a
 * fixed global data table (DAT_0da98/daa8/dab8/dac8/dad8/15598/163e0/16a60/
 * 170e0/16da0/17420/17e00/18290/197c8). These are per-format/algorithm data. */
unsigned long txm_gdesc_0da98(void) { return (unsigned long)DAT_0000da98; }
unsigned long txm_gdesc_0daa8(void) { return (unsigned long)DAT_0000daa8; }
unsigned long txm_gdesc_0dab8(void) { return (unsigned long)DAT_0000dab8; }
unsigned long txm_gdesc_0dac8(void) { return (unsigned long)DAT_0000dac8; }
unsigned long txm_gdesc_0dad8(void) { return (unsigned long)DAT_0000dad8; }
unsigned long txm_gdesc_15598(void) { return (unsigned long)DAT_00015598; }
unsigned long txm_gdesc_163e0(void) { return (unsigned long)DAT_000163e0; }
unsigned long txm_gdesc_16a60(void) { return (unsigned long)DAT_00016a60; }
unsigned long txm_gdesc_170e0(void) { return (unsigned long)DAT_000170e0; }
unsigned long txm_gdesc_16da0(void) { return (unsigned long)DAT_00016da0; }
unsigned long txm_gdesc_17420(void) { return (unsigned long)DAT_00017420; }
unsigned long txm_gdesc_17e00(void) { return (unsigned long)DAT_00017e00; }
unsigned long txm_gdesc_18290(void) { return (unsigned long)DAT_00018290; }
unsigned long txm_gdesc_197c8(void) { return (unsigned long)DAT_000197c8; }

/* thunks 2ff1c/2ff30/2fea4 — glue to 5a8d8/5a914/56578 */
void txm_thunk_5a8d8(void) { }
void txm_thunk_5a914(void) { }
void txm_thunk_56578(void) { }

/* FUN_0002ff24 @ 0x2ff24  (est. txm_const_4)
 * Ghidra: undefined8 FUN_0002ff24(void)
 * Returns constant 4.
 * Confidence: high */
unsigned long txm_const_4(void) { return 4; }

/* FUN_0002ff88 @ 0x2ff88  (est. txm_plus4)
 * Ghidra: long FUN_0002ff88(long)
 * Returns param_1 + 4.
 * Confidence: high */
unsigned long txm_plus4(unsigned long p) { return p + 4; }

/* FUN_0002ff94 @ 0x2ff94  (est. txm_codedir_validate_v3)
 * Ghidra: undefined4 FUN_0002ff94(int*, ulong)
 * Validates a CodeDirectory version-3 (0x49) header: length >= 0x19, magic 3,
 * hash type 2 or 4 (0x22/0x32 entry size), and total size covers entries.
 * Returns 0x49 on success.
 * Confidence: medium (CodeDirectory v3 layout) */
unsigned txm_codedir_validate_v3(unsigned *cd, unsigned long size) {
    if (size < 0x19) return 0x12649;
    if (cd[0] == 3) {
        unsigned hs;
        if ((char)cd[5] == '\x02') hs = 0x22;
        else if ((char)cd[5] == '\x04') hs = 0x32;
        else return 0x32149;
        if (hs * *(unsigned*)((char*)cd + 0x15) + 0x19 <= size) return 0x49;
        return 0x62649;
    }
    return 0x22249;
}

/* FUN_00030014 @ 0x30014  (est. txm_codedir_find_v3)
 * Ghidra: undefined* FUN_00030014(long, undefined8, ulong, long)
 * Binary-searches a version-3 CodeDirectory for the entry matching param_2
 * (hash). Entry stride 0x22 (hash 2) or 0x32 (hash 4); the target hash length
 * (0x20/0x30) must match. Returns the entry pointer + type 0x4a, else error.
 * Confidence: medium */
void *txm_codedir_find_v3(unsigned long cd, const void *hash, unsigned long len,
                          unsigned long *out) {
    if (*(int*)(cd + 0x15) == 0) return (void*)0x1244a;
    unsigned stride = (*(char*)(cd + 0x14) == '\x04') ? 0x30 :
                      (*(char*)(cd + 0x14) == '\x02') ? 0x20 : 0;
    if (len == 0x14 || len == stride) {
        unsigned lo = 0, hi = *(int*)(cd + 0x15) - 1;
        unsigned char *base = (unsigned char*)(cd + 0x19);
        unsigned long stride2 = (*(char*)(cd + 0x14) == '\x02') ? 0x22 : 0x32;
        while (lo <= hi) {
            unsigned mid = (lo + hi) >> 1;
            unsigned char *e = base + (unsigned long)mid * stride2;
            int c = txm_memcmp(e, hash, len);
            if (c == 0) {
                if (out) *(unsigned long*)(out + 8) = (unsigned long)e;
                return (void*)0x4a;
            }
            if (c < 0) lo = mid + 1; else hi = mid - 1;
        }
        return (void*)0x3244a;
    }
    return (void*)0x2214a;
}

/* FUN_00030200 @ 0x30200  (est. txm_codedir_get_type)
 * Ghidra: undefined1 FUN_00030200(long, long)
 * Returns the CodeDirectory type/hash byte at offset 0x20 (hash 2) or 0x30.
 * Confidence: low */
unsigned char txm_codedir_get_type(unsigned long cd, unsigned long e) {
    return *(unsigned char*)(e + ((*(char*)(cd + 0x14) == '\x02') ? 0x20 : 0x30));
}

/* FUN_00030224 @ 0x30224  (est. txm_img4_flags)
 * Ghidra: uint FUN_00030224(undefined8, undefined8, undefined8, undefined8)
 * Reads the signature flags: tries class 2 then class 1 lookup (30c00) and
 * copies the flag byte via 30d1c.
 * Confidence: medium */
unsigned txm_img4_flags(unsigned long state, unsigned long kind, unsigned long base,
                        unsigned long size, unsigned char *flag) {
    unsigned r = txm_img4_lookup(state, 2, base, size, flag);
    if ((r & 0xff00) != 0) r = txm_img4_lookup(state, 1, base, size, flag);
    unsigned sub = r >> 8 & 0xff;
    if (sub == 0) txm_img4_copy_flag(flag, flag);
    return r & 0xffff0000 | r & 0xff | sub << 8;
}

/* FUN_000302c0 @ 0x302c0  (est. txm_codedir_validate_v0)
 * Ghidra: undefined4 FUN_000302c0(int*, ulong)
 * Validates a version-0 CodeDirectory (0x43): magic 0, size covers 0x14-byte
 * entries.
 * Confidence: medium */
unsigned txm_codedir_validate_v0(unsigned *cd, unsigned long size) {
    if (size < 0x18) return 0x12643;
    if (cd[0] != 0) return 0x22243;
    if ((unsigned long)cd[5] * 0x14 + 0x18 <= size) return 0x43;
    return 0x52643;
}

/* FUN_00030314 @ 0x30314  (est. txm_codedir_find_v0)
 * Ghidra: undefined* FUN_00030314(long, undefined8, long)
 * Linear-search a version-0 CodeDirectory (0x14-byte stride) for hash param_2.
 * Confidence: medium */
void *txm_codedir_find_v0(unsigned long cd, const void *hash, unsigned long *out) {
    if (*(int*)(cd + 0x14) != 0) {
        unsigned n = 0;
        unsigned char *base = (unsigned char*)(cd + 0x18);
        unsigned char *p = base;
        do {
            if (txm_memcmp(p, hash, 0x14) == 0) {
                if (out) *(unsigned long*)(out + 8) = (unsigned long)p;
                return (void*)0x42;
            }
            n++; p += 0x14;
        } while (n < *(unsigned*)(cd + 0x14));
    }
    return (void*)0x12442;
}

/* FUN_000303e8 @ 0x303e8  (est. txm_codedir_validate_v1)
 * Ghidra: undefined4 FUN_000303e8(int*, ulong)
 * Validates a version-1 CodeDirectory (0x45): magic 1, 0x16-byte entries.
 * Confidence: medium */
unsigned txm_codedir_validate_v1(unsigned *cd, unsigned long size) {
    if (size < 0x18) return 0x12645;
    if (cd[0] == 1) {
        if ((unsigned long)cd[5] * 0x16 + 0x18 <= size) return 0x45;
        return 0x52645;
    }
    return 0x22245;
}

/* FUN_00030440 @ 0x30440  (est. txm_codedir_find_v1)
 * Ghidra: undefined* FUN_00030440(long, undefined8, long)
 * Binary-search a version-1 CodeDirectory (0x16-byte stride).
 * Confidence: medium */
void *txm_codedir_find_v1(unsigned long cd, const void *hash, unsigned long *out) {
    if (*(int*)(cd + 0x14) != 0) {
        unsigned lo = 0, hi = *(int*)(cd + 0x14) - 1;
        unsigned char *base = (unsigned char*)(cd + 0x18);
        while (lo <= hi) {
            unsigned mid = (lo + hi) >> 1;
            unsigned char *e = base + (unsigned long)mid * 0x16;
            int c = txm_memcmp(e, hash, 0x14);
            if (c == 0) {
                if (e == 0) return (void*)0x22444;
                if (out) *(unsigned long*)(out + 8) = (unsigned long)e;
                return (void*)0x44;
            }
            if (c < 0) lo = mid + 1; else hi = mid - 1;
        }
    }
    return (void*)0x22444;
}

/* FUN_00030570 @ 0x30570  (est. txm_codedir_hash_type)
 * Ghidra: undefined1 FUN_00030570(long)
 * Returns the hash-type byte at offset 0x15.
 * Confidence: low */
unsigned char txm_codedir_hash_type(unsigned long cd) { return *(unsigned char*)(cd + 0x15); }

/* FUN_0003057c @ 0x3057c  (est. txm_codedir_validate_v2)
 * Ghidra: undefined4 FUN_0003057c(int*, ulong)
 * Validates a version-2 CodeDirectory (0x47): magic 2, 0x18-byte entries.
 * Confidence: medium */
unsigned txm_codedir_validate_v2(unsigned *cd, unsigned long size) {
    if (size < 0x18) return 0x12647;
    if (cd[0] == 2) {
        if ((unsigned long)cd[5] * 0x18 + 0x18 <= size) return 0x47;
        return 0x52647;
    }
    return 0x22247;
}

/* FUN_000305d4 @ 0x305d4  (est. txm_codedir_find_v2)
 * Ghidra: undefined* FUN_000305d4(long, undefined8, long)
 * Binary-search a version-2 CodeDirectory (0x18-byte stride).
 * Confidence: medium */
void *txm_codedir_find_v2(unsigned long cd, const void *hash, unsigned long *out) {
    if (*(int*)(cd + 0x14) != 0) {
        unsigned lo = 0, hi = *(int*)(cd + 0x14) - 1;
        unsigned char *base = (unsigned char*)(cd + 0x18);
        while (lo <= hi) {
            unsigned mid = (lo + hi) >> 1;
            unsigned char *e = base + (unsigned long)mid * 0x18;
            int c = txm_memcmp(e, hash, 0x14);
            if (c == 0) {
                if (e == 0) return (void*)0x22446;
                if (out) *(unsigned long*)(out + 8) = (unsigned long)e;
                return (void*)0x46;
            }
            if (c < 0) lo = mid + 1; else hi = mid - 1;
        }
    }
    return (void*)0x22446;
}

/* FUN_00030708 @ 0x30708  (est. txm_codedir_dispatch)
 * Ghidra: undefined8 FUN_00030708(int*)
 * Dispatches to the version-specific CodeDirectory entry accessor.
 * Confidence: medium */
unsigned long txm_codedir_dispatch(unsigned *cd) {
    switch (*cd) {
    case 0: case 1: case 2: case 3: return txm_plus4(0);
    default: return 0;
    }
}

/* FUN_0003074c @ 0x3074c  (est. txm_codedir_validate)
 * Ghidra: uint FUN_0003074c(int*, ulong)
 * Version-dispatching CodeDirectory header validator.
 * Confidence: medium */
unsigned txm_codedir_validate(unsigned *cd, unsigned long size) {
    unsigned r;
    if (size < 4) return 0x12641;
    switch (*cd) {
    case 0: r = txm_codedir_validate_v0(cd, size); break;
    case 1: r = txm_codedir_validate_v1(cd, size); break;
    case 2: r = txm_codedir_validate_v2(cd, size); break;
    case 3: r = txm_codedir_validate_v3(cd, size); break;
    default: return 0x22141;
    }
    return (r & 0xff00) != 0 ? r : 0x41;
}

/* FUN_000307d0 @ 0x307d0  (est. txm_codedir_get_entry)
 * Ghidra: undefined* FUN_000307d0(uint*, undefined8*)
 * Returns the version-specific entry accessor function pointer (from the table
 * at DAT_6cf8) for a CodeDirectory; 0x48 on success.
 * Confidence: low */
void *txm_codedir_get_entry(unsigned *cd, unsigned long *out) {
    if (*cd < 4) {
        if (out) *out = *(unsigned long*)(&DAT_00006cf8 + (unsigned long)*cd * 8);
        return (void*)0x48;
    }
    return (void*)0x12148;
}

/* FUN_00030808 @ 0x30808  (est. txm_codedir_find)
 * Ghidra: uint FUN_00030808(uint*, undefined8, ulong, undefined8)
 * Version-dispatching CodeDirectory entry search.
 * Confidence: medium */
unsigned txm_codedir_find(unsigned *cd, const void *hash, unsigned long len,
                          unsigned long *out) {
    unsigned r;
    if (0x13 < len) return 0x12140;
    switch (*cd) {
    case 0: if (len < 0x14) txm_assert(0x19); r = (unsigned)(unsigned long)txm_codedir_find_v0((unsigned long)cd, hash, out); break;
    case 1: if (len < 0x14) txm_assert(0x19); r = (unsigned)(unsigned long)txm_codedir_find_v1((unsigned long)cd, hash, out); break;
    case 2: if (len < 0x14) txm_assert(0x19); r = (unsigned)(unsigned long)txm_codedir_find_v2((unsigned long)cd, hash, out); break;
    case 3: r = (unsigned)(unsigned long)txm_codedir_find_v3((unsigned long)cd, hash, out); break;
    default: return 0x22140;
    }
    return (r & 0xff00) != 0 ? r : 0x40;
}

/* FUN_000308b8 @ 0x308b8  (est. txm_codedir_get_base)
 * Ghidra: undefined* FUN_000308b8(int*, undefined8, ulong*)
 * Returns the code base offset of a CodeDirectory (0x15).
 * Confidence: low */
void *txm_codedir_get_base(unsigned *cd, unsigned long e, unsigned long *out) {
    unsigned long b;
    switch (*cd) {
    case 0: return (void*)0x12115;
    case 1: case 2: b = txm_codedir_hash_type(e); break;
    case 3: b = txm_codedir_get_type((unsigned long)cd, e); break;
    default: return (void*)0x22115;
    }
    if (out) *out = b & 0xffffffff;
    return (void*)0x15;
}

/* FUN_0003094c @ 0x3094c  (est. txm_cert_list_push)
 * Ghidra: undefined8 FUN_0003094c(long*, long*)
 * Appends param_2 to the intrusive linked list at *param_1 (single-write with
 * a load-checked CAS-free splice). Returns 0x80.
 * Confidence: low */
unsigned long txm_cert_list_push(unsigned long *list, unsigned long *node) {
    unsigned long old = *list;
    do {
        *node = old;
        unsigned long v = *list;
        if (*list == old) { *list = (unsigned long)node; break; }
        old = *list;
    } while (*list != old);
    return 0x80;
}

/* FUN_00030974 @ 0x30974  (est. txm_cert_list_head)
 * Ghidra: undefined8 FUN_00030974(undefined8*)
 * Returns the head of the cert list (param_1 or the global if null).
 * Confidence: low */
unsigned long txm_cert_list_head(unsigned long *p) {
    return p ? *p : 0;
}

/* FUN_00030984 @ 0x30984  (est. txm_cert_find_by_handle)
 * Ghidra: undefined4 FUN_00030984(long, long, long*)
 * Resolves a cert handle to its descriptor via 30ddc (four-entry search).
 * Returns the descriptor in param_3, 0x5 on success.
 * Confidence: low */
unsigned txm_cert_find_by_handle(unsigned long h, unsigned long kind, unsigned long *out) {
    if (h == 0) return 0x12505;
    if (kind == 0) return 0x22505;
    unsigned long d = txm_cert_find_all(h);
    if (d == 0) return 0x32405;
    if (out) *out = d;
    return 5;
}

/* FUN_000309ec @ 0x309ec  (est. txm_cert_validate)
 * Ghidra: void FUN_000309ec(long)
 * Validates a cert descriptor (state +0x10/+0x18) then runs 307d0.
 * Confidence: low */
void txm_cert_validate(unsigned long p) {
    if (*(unsigned long*)(p + 0x10) == 0 && *(unsigned long*)(p + 0x18) != 0)
        txm_assert(0x19);
    txm_codedir_get_entry((unsigned*)(p + 0x10), 0);
}

/* FUN_00030a24 @ 0x30a24  (est. txm_cert_get_type_entry)
 * Ghidra: undefined* FUN_00030a24(long, undefined8*)
 * Returns the type-specific cert entry accessor (via 30708).
 * Confidence: low */
void *txm_cert_get_type_entry(unsigned long p, unsigned long *out) {
    if (p == 0) return (void*)0x12507;
    if (out == 0) return (void*)0x22507;
    if (*(unsigned long*)(p + 0x10) == 0 && *(unsigned long*)(p + 0x18) != 0)
        txm_assert(0x19);
    unsigned long e = txm_codedir_dispatch((unsigned*)(p + 0x10));
    if (e == 0) return (void*)0x32207;
    out[0] = *(unsigned long*)(e + 0);
    out[1] = *(unsigned long*)(e + 8);
    return (void*)0x7;
}

/* FUN_00030a98 @ 0x30a98  (est. txm_cert_lookup)
 * Ghidra: undefined* FUN_00030a98(undefined8, undefined8, undefined8, long*)
 * Walks the cert list, skipping "inactive" entries (flag bit1 at +9), and
 * returns the entry whose CodeDirectory matches via 30808. 0x11 on success.
 * Confidence: low */
void *txm_cert_lookup(unsigned long kind, const void *hash, unsigned long len,
                      unsigned long *out) {
    unsigned long *c = (unsigned long*)txm_cert_list_head(0);
    for (;;) {
        if (c == 0) return (void*)0x12411;
        if ((*(unsigned char*)((char*)c + 9) & 1) == 0) {
            if (c[2] == 0 && c[3] != 0) txm_assert(0x19);
            unsigned r = txm_codedir_find((unsigned*)c[3], hash, len, out);
            if ((r & 0xff00) == 0) { if (out) *out = (unsigned long)c; return (void*)0x11; }
        }
        c = (unsigned long*)*c;
    }
}

/* FUN_00030b38 @ 0x30b38  (est. txm_cert_lookup_all)
 * Ghidra: void FUN_00030b38(long, undefined8, undefined8, undefined8)
 * Looks up a cert across the four registry slots (0x10, 0x18, 0x20, 0x28).
 * 0x12 on success, else error.
 * Confidence: low */
void txm_cert_lookup_all(unsigned long p, const void *hash, unsigned long len,
                         unsigned long *out) {
    unsigned long canary = DAT_00006cf0;
    unsigned long slots[4];
    unsigned long *r;
    slots[0] = p + 0x10; slots[1] = p + 0x18;
    slots[2] = *(unsigned long*)(p + 0x20); slots[3] = *(unsigned long*)(p + 0x20) + 8;
    for (unsigned i = 0; i < 0x20; i += 8) {
        r = txm_cert_lookup(*(unsigned long*)((char*)slots + i), hash, len, out);
        if ((unsigned long)r & 0xff00) continue;
        txm_stack_check_fail();
        return;
    }
    txm_stack_check_fail();
}

/* FUN_00030c00 @ 0x30c00  (est. txm_img4_lookup)
 * Ghidra: uint FUN_00030c00(long, int, undefined8, undefined8, undefined8)
 * Version-dispatching CodeDirectory lookup over a state object's four slots.
 * Confidence: medium */
unsigned txm_img4_lookup(unsigned long state, int which, const void *hash,
                         unsigned long len, unsigned long *out) {
    unsigned r;
    if (which < 2) {
        if (which == 0) { r = txm_cert_lookup_all(state, hash, len, out); goto out; }
        if (which != 1) return 74000;
        r = txm_cert_lookup(state + 0x10, hash, len, out);
        if ((r & 0xff00) == 0) goto out;
        state = state + 0x18;
    } else if (which == 2) {
        state = *(unsigned long*)(state + 0x20);
    } else if (which == 3) {
        state = *(unsigned long*)(state + 0x20) + 8;
    } else return 74000;
    r = txm_cert_lookup(state, hash, len, out);
out:
    return (r & 0xff00) != 0 ? r : 0x10;
}

/* FUN_00030cc8 @ 0x30cc8  (est. txm_cert_get_type)
 * Ghidra: void FUN_00030cc8(undefined8*)
 * Returns the cert type entry for *param_1.
 * Confidence: low */
void txm_cert_get_type(unsigned long *p) { txm_cert_get_type_entry(*p, 0); }

/* FUN_00030cd4 @ 0x30cd4  (est. txm_cert_get_base_flag)
 * Ghidra: void FUN_00030cd4(long*, undefined8)
 * Returns the code base offset via 308b8 for the cert in *param_1.
 * Confidence: low */
void txm_cert_get_base_flag(unsigned long *p, unsigned long *out) {
    unsigned long e = *(unsigned long*)(*p + 0x18);
    if (*(unsigned long*)(*p + 0x10) == 0 && e != 0) txm_assert(0x19);
    txm_codedir_get_base((unsigned*)(*p + 0x10), e, out);
}

/* FUN_00030d1c @ 0x30d1c  (est. txm_cert_flag_shift)
 * Ghidra: ulong FUN_00030d1c(undefined8, byte*)
 * Reads the cert's flag byte (base offset >> 6) via 30cd4. 0x17 on success.
 * Confidence: low */
unsigned long txm_cert_flag_shift(unsigned long *p, unsigned char *out) {
    unsigned long r = 0;
    unsigned long v = txm_cert_get_base_flag(p, &r);
    if ((v & 0xff00) == 0) {
        if (out) *out = (unsigned char)(r >> 6);
        return 0x17;
    }
    return v;
}

/* FUN_00030d6c @ 0x30d6c  (est. txm_cert_find_in_list)
 * Ghidra: long FUN_00030d6c(undefined8, undefined8)
 * Finds a cert whose type dispatch matches the 0x10-byte key param_2.
 * Confidence: low */
unsigned long txm_cert_find_in_list(unsigned long kind, const void *key) {
    unsigned long *c = (unsigned long*)txm_cert_list_head(0);
    for (;;) {
        if (c == 0) return 0;
        if ((*(unsigned char*)((char*)c + 9) & 1) == 0) {
            if (c[2] == 0 && c[3] != 0) txm_assert(0x19);
            unsigned long e = txm_codedir_dispatch((unsigned*)c[3]);
            if (e != 0 && txm_memcmp((void*)e, key, 0x10) == 0) return (unsigned long)c;
        }
        c = (unsigned long*)*c;
    }
}

/* FUN_00030ddc @ 0x30ddc  (est. txm_cert_find_all)
 * Ghidra: void FUN_00030ddc(long, undefined8)
 * Searches all four registry slots for a cert matching param_2.
 * Confidence: low */
unsigned long txm_cert_find_all(unsigned long p) {
    unsigned long canary = DAT_00006cf0;
    unsigned long slots[4];
    unsigned long r = 0;
    slots[0] = p + 0x10; slots[1] = p + 0x18;
    slots[2] = *(unsigned long*)(p + 0x20); slots[3] = *(unsigned long*)(p + 0x20) + 8;
    for (unsigned i = 0; i < 0x20; i += 8) {
        r = txm_cert_find_in_list(*(unsigned long*)((char*)slots + i), (void*)(p + 0x10));
        if (r != 0) break;
    }
    if (DAT_00006cf0 == canary) return r;
    txm_stack_check_fail();
    return r;
}

/* ---- image4 part 2 (30e78-34ff8) ---- */

/* FUN_00030e78 @ 0x30e78  (est. txm_ctx_alloc)
 * Ghidra: undefined* FUN_00030e78(undefined8*, ulong, ulong)
 * Allocates a CEContext range descriptor {base,size}. Validates non-zero,
 * non-overflowing, and validates the CodeDirectory if the type demands it.
 * On success fills param_1 (kind 0, type 0xff) and returns 0x4.
 * Confidence: medium */
void *txm_ctx_alloc(unsigned long *out, unsigned long base, unsigned long size) {
    unsigned r;
    if (base == 0) return (void*)0x12504;
    if (size == 0) return (void*)0x22504;
    if (base + size < base) return (void*)0x32004;
    r = txm_codedir_validate((unsigned*)base, size);
    if ((r & 0xff00) == 0) {
        if (out) { out[0] = 0; out[2] = size; out[3] = base;
                   *(unsigned char*)(out + 1) = 0xff; }
        return (void*)0x4;
    }
    return (void*)(unsigned long)r;
}

/* FUN_00030f00 @ 0x30f00  (est. txm_cert_register)
 * Ghidra: void FUN_00030f00(long, int, undefined8*, undefined8, undefined8)
 * Registers a CodeDirectory/cert into the given slot (param_2 = 0/1/2). Validates
 * the range, looks up the type, resolves the owner, and splices it into the
 * linked list at the slot. Returns class/error per step.
 * Confidence: medium */
void txm_cert_register(unsigned long p, int slot, unsigned long *out,
                       unsigned long base, unsigned long size) {
    unsigned long canary = DAT_00006cf0;
    unsigned long r[2], key[2];
    void *rc;
    txm_bzero(r, sizeof r); txm_bzero(key, sizeof key);
    if (out == 0) { txm_stack_check_fail(); return; }
    rc = txm_ctx_alloc(r, base, size);
    if ((unsigned long)rc & 0xff00) { txm_stack_check_fail(); return; }
    txm_cert_get_type_entry((unsigned long)r, key);
    if (txm_cert_find_by_handle(p, (unsigned long)key, 0) & 0xff00) { txm_stack_check_fail(); return; }
    /* select slot */
    unsigned long *head;
    unsigned char allow;
    if (slot == 2) {
        if ((*(unsigned char*)(p + 10) & 1) == 0) { txm_stack_check_fail(); return; }
        head = *(unsigned long**)(p + 0x20);
    } else if (slot == 1) {
        if ((*(unsigned char*)(p + 9) & 1) == 0) { txm_stack_check_fail(); return; }
        head = (unsigned long*)(p + 0x18);
    } else if (slot == 0) {
        head = (unsigned long*)(p + 0x10);
        if (*head != 0) {
            if (*(unsigned long*)*head != 0) { txm_stack_check_fail(); return; }
            if ((*(unsigned char*)(p + 8) & 1) == 0) { txm_stack_check_fail(); return; }
        }
    } else { txm_stack_check_fail(); return; }
    out[0] = r[0]; out[1] = r[1]; out[2] = r[0]; out[3] = r[1];
    *(char*)(out + 1) = (char)slot;
    txm_cert_list_push(head, out);
    if (DAT_00006cf0 == canary) return;
    txm_stack_check_fail();
}

/* FUN_00031060 @ 0x31060  (est. txm_cert_register_full)
 * Ghidra: void FUN_00031060(long*, undefined8, undefined8*, ulong, ulong, ulong, ulong)
 * Registers a fully-described cert region (code base/size + data base/size +
 * owner kind). Runs image4 eval (2fa00), allocates the ctx, resolves the type,
 * and splices. Returns class/error per step.
 * Confidence: medium */
void txm_cert_register_full(unsigned long *p, unsigned long kind, unsigned long *out,
                            unsigned long cbase, unsigned long csize,
                            unsigned long dbase, unsigned long dsize) {
    unsigned long canary = DAT_00006cf0;
    unsigned long r[2], key[2], status[2];
    void *rc;
    txm_bzero(r, sizeof r); txm_bzero(key, sizeof key); txm_bzero(status, sizeof status);
    if (cbase == 0 || csize == 0 || dbase == 0 || dsize == 0 || out == 0)
        { txm_stack_check_fail(); return; }
    if (*p == 0) { txm_stack_check_fail(); return; }
    if (cbase + csize < cbase) { txm_stack_check_fail(); return; }
    if (dbase + dsize < dbase) { txm_stack_check_fail(); return; }
    rc = (void*)(unsigned long)txm_image4_eval(p, kind, cbase, csize, dbase, dsize,
                                               status, status + 1);
    if ((unsigned long)rc & 0xff00) { txm_stack_check_fail(); return; }
    rc = txm_ctx_alloc(r, status[0], status[1]);
    if ((unsigned long)rc & 0xff00) { txm_stack_check_fail(); return; }
    txm_cert_get_type_entry((unsigned long)r, key);
    if (txm_cert_find_by_handle((unsigned long)p, (unsigned long)key, 0) & 0xff00)
        { txm_stack_check_fail(); return; }
    /* slot selection similar to 30f00 (op 3/4/0x19) */
    unsigned long *head;
    if ((unsigned)(kind - 4U) < 0x15) head = p + 4;
    else if (kind == 0x19) head = p + 4 + 8;
    else if (kind == 3) {
        if ((*(unsigned char*)((char*)p + 9) & 1) == 0) { txm_stack_check_fail(); return; }
        head = p + 4;
    } else { txm_stack_check_fail(); return; }
    out[0] = r[0]; out[1] = r[1]; out[2] = r[0]; out[3] = r[1];
    *(char*)(out + 1) = (char)kind;
    unsigned rc2 = txm_cert_list_push(head, out);
    if ((rc2 & 0xff00) == 0) rc2 = 1;
    if (DAT_00006cf0 == canary) return;
    txm_stack_check_fail();
}

/* FUN_0003120c @ 0x3120c  (est. txm_cert_activate)
 * Ghidra: undefined* FUN_0003120c(undefined8, undefined8, ulong*)
 * Activates the cert (sets active flag +9 = 1). 0x9 on success.
 * Confidence: low */
void *txm_cert_activate(unsigned long a, unsigned long b, unsigned long *out) {
    unsigned long c = txm_cert_find_all(a);
    if (c == 0) return (void*)0x12409;
    if (*(unsigned char*)(c + 8) < 2) return (void*)0x22709;
    *(unsigned char*)(c + 9) = 1;
    if (out) *out = c;
    return (void*)0x9;
}

/* FUN_00031280 @ 0x31280  (est. txm_cectx_init)
 * Ghidra: undefined4 FUN_00031280(long, undefined8, undefined8*, ulong, ulong)
 * Initializes a CEContext (param_3, 0x90 bytes zeroed). Validates the data
 * range and, if a hash function is available (5fb88), records it; logs on
 * failure. Returns 0x40 on success.
 * Confidence: medium */
unsigned txm_cectx_init(unsigned long kind, unsigned long flags, unsigned long *ctx,
                        unsigned long base, unsigned long size) {
    txm_bzero(ctx, 0x90);
    if (base == 0) return 0x12c40;
    if (size == 0) return 0x22c40;
    if (base + size < base) return 0x32140;
    if (kind == 0) return 0x40240;
    if (txm_crypto_ctx_init(kind) == 0) return 0x40;
    txm_log("_entitlements %u: CEContextInit failed\n");
    return 0x50140;
}

/* FUN_00031334 @ 0x31334  (est. txm_cectx_validate)
 * Ghidra: undefined4 FUN_00031334(long, long)
 * Validates a CEContext (5e374). 0x41 on success.
 * Confidence: low */
unsigned txm_cectx_validate(unsigned long kind, unsigned long ctx) {
    if (kind == 0) return 0x12c41;
    if (ctx == 0) return 0x22c41;
    if (txm_cectx_check(ctx)) return 0x41;
    return 0x32941;
}

/* FUN_00031388 @ 0x31388  (est. txm_cectx_teamid)
 * Ghidra: undefined* FUN_00031388(long, long, undefined4*)
 * Reads the CEContext team id (60088 -> 5f4b4) into param_3. 0x42 on success.
 * Confidence: low */
void *txm_cectx_teamid(unsigned long kind, unsigned long ctx, unsigned *out) {
    unsigned long h[5]; unsigned r;
    txm_bzero(h, sizeof h);
    if (kind == 0) return (void*)0x11142;
    if (ctx == 0) return (void*)0x22c42;
    if (txm_dict_init(kind, ctx, h)) return (void*)0x32442;
    if (txm_dict_int(h, &r)) return (void*)0x42642;
    if (out) *out = r;
    return (void*)0x42;
}

/* FUN_00031424 @ 0x31424  (est. txm_cectx_value)
 * Ghidra: undefined4 FUN_00031424(long, long, undefined8)
 * Reads a CEContext string/flag value (60088 -> 5f824). 0x43 on success.
 * Confidence: low */
unsigned txm_cectx_value(unsigned long kind, unsigned long ctx, unsigned long arg) {
    unsigned long h[5];
    txm_bzero(h, sizeof h);
    if (kind == 0) return 0x11143;
    if (ctx == 0) return 0x22c43;
    if (txm_dict_init(kind, ctx, h)) return 0x32443;
    if (txm_dict_value(h, arg)) return 0x42943;
    return 0x43;
}

/* FUN_000314b0 @ 0x314b0  (est. txm_cectx_flags)
 * Ghidra: undefined4 FUN_000314b0(long, long, long)
 * Reads a CEContext flags value (60088 -> 5fa9c). 0x45 on success.
 * Confidence: low */
unsigned txm_cectx_flags(unsigned long kind, unsigned long ctx, unsigned long arg) {
    unsigned long h[5];
    txm_bzero(h, sizeof h);
    if (kind == 0) return 0x11145;
    if (ctx == 0) return 0x22c45;
    if (arg == 0) return 0x32c45;
    if (txm_dict_init(kind, ctx, h)) return 0x42445;
    if (txm_dict_flags(h, arg)) return 0x52945;
    return 0x45;
}

/* FUN_0003154c @ 0x3154c  (est. txm_hash_amfi)
 * Ghidra: undefined* FUN_0003154c(int, undefined8, undefined8, undefined8, undefined8*)
 * Hashes an AMFI CMS region: kind selects the hash size/algorithm
 * (1=20B, 2=32B, 4=48B, 8=0x30). Returns 0xe1 with the digest length.
 * Confidence: medium */
void *txm_hash_amfi(int kind, const void *data, unsigned long len,
                    const void *b, unsigned long *out_len) {
    unsigned long dig;
    switch (kind) {
    case 1: dig = txm_hash_1(data, len, b); *out_len = 0x14; return (void*)0xe1;
    case 2: dig = txm_hash_2(data, len, b); *out_len = 0x20; return (void*)0xe1;
    case 4: dig = txm_hash_4(data, len, b); *out_len = 0x30; return (void*)0xe1;
    case 8: dig = txm_hash_8(data, len, b); *out_len = 0x30; return (void*)0xe1;
    default: return (void*)0x128e1;
    }
}

/* FUN_0003161c @ 0x3161c  (est. txm_amfi_cms_parse)
 * Ghidra: int FUN_0003161c(ulong*, undefined1, ulong, ulong)
 * Parses an AMFI CMS signature blob into a context (param_1, 0x90 bytes):
 * runs CTParseAmfiCMS (47588), records base/size/type, and sets the ready flag.
 * Confidence: medium */
int txm_amfi_cms_parse(unsigned long *ctx, unsigned char type, unsigned long base,
                       unsigned long size) {
    txm_bzero(ctx, 0x90);
    if (base == 0) return 0x12c50;
    if (size == 0) return 0x12c50;
    if (base + size < base) return 0x32150;
    int r = txm_ct_parse_amfi_cms(base, size, 8, ctx + 2, ctx + 3, ctx + 4, ctx + 5,
                                  ctx + 9, ctx + 10);
    if (r != 0) { txm_log("failed CTParseAmfiCMS %d\n"); return 0x43550; }
    if (ctx[2] + ctx[3] < ctx[2]) return 0x52150;
    if (ctx[4] + ctx[5] < ctx[4]) return 0x52150;
    *(unsigned char*)((char*)ctx + 0x5a) = type;
    ctx[0] = base; ctx[1] = size;
    *(unsigned char*)(ctx + 0xb) = 1;
    return 0x50;
}

/* FUN_00031714 @ 0x31714  (est. txm_amfi_cms_verify)
 * Ghidra: void FUN_00031714(undefined8*, ulong, ulong)
 * Verifies an AMFI CMS signature (parsed by 3161c): computes the cert-chain
 * digest (3154c + 476a0), verifies the AMFI cert chain (47754), and sets the
 * verified flag. Panics on invalid lengths.
 * Confidence: medium */
void txm_amfi_cms_verify(unsigned long *ctx, unsigned long base, unsigned long size) {
    unsigned long canary = DAT_00006cf0;
    unsigned long block[8];
    void *rc;
    txm_bzero(block, sizeof block);
    if ((*(unsigned char*)(ctx + 0xb) & 1) == 0) { txm_stack_check_fail(); return; }
    if ((*(unsigned char*)((char*)ctx + 0x59) & 1) != 0) { txm_stack_check_fail(); return; }
    if (base == 0) { base = ctx[4]; size = ctx[5]; }
    else if (size == 0) { txm_stack_check_fail(); return; }
    else if (base + size < base) { txm_stack_check_fail(); return; }
    if (base == 0 || size == 0) { txm_stack_check_fail(); return; }
    rc = txm_hash_amfi(*(unsigned*)(ctx + 9), base, size, block + 1, block);
    if ((unsigned long)rc & 0xff00) { txm_stack_check_fail(); return; }
    if (0x30 < block[0]) txm_assert(0x19);
    if (txm_ct_verify_chain(ctx[0], ctx[1], block + 1, block[0], 8, ctx + 6, ctx + 7,
                            ctx + 8)) {
        txm_log("failed CTVerifyAmfiCMS %d\n");
        txm_stack_check_fail(); return;
    }
    if (ctx[7] + ctx[8] < ctx[7]) { txm_stack_check_fail(); return; }
    unsigned long old = ctx[10];
    if (txm_ct_verify_cert_chain(ctx[0], ctx[1], *(unsigned char*)((char*)ctx + 0x5a) & 1,
                                 8, ctx + 10)) {
        txm_log("failed CTVerifyAmfiCertificateChain\n");
        txm_stack_check_fail(); return;
    }
    if ((ctx[10] & (old ^ ~0UL)) == 0) {
        *(unsigned char*)((char*)ctx + 0x59) = 1;
    } else {
        txm_stack_check_fail(); return;
    }
    if (DAT_00006cf0 == canary) return;
    txm_stack_check_fail();
}

/* FUN_000318c8 @ 0x318c8  (est. txm_amfi_cert_chain_verify)
 * Ghidra: undefined4 FUN_000318c8(long, ulong, ulong)
 * Verifies an AMFI certificate chain against the cert (4b3a8) + compares a
 * hash (memcmp). 0x52 on success.
 * Confidence: low */
unsigned txm_amfi_cert_chain_verify(unsigned long ctx, unsigned long base, unsigned long size) {
    unsigned long h[2];
    txm_bzero(h, sizeof h);
    if ((*(unsigned char*)(ctx + 0x59) & 1) == 0) return 0x12252;
    if (base == 0) return 0x22c52;
    if (size == 0) return 0x32c52;
    if (base + size < base) return 0x42152;
    if (txm_cert_chain_hash(*(unsigned long*)(ctx + 0x10), *(unsigned long*)(ctx + 0x18),
                            &h[0], &h[1])) return 0x53952;
    if (h[0] + h[1] < h[0]) return 0x62152;
    if (h[1] != size) return 0x72952;
    if (txm_memcmp((void*)base, (void*)h[0], size)) return 0x82952;
    return 0x52;
}

/* FUN_000319a8 @ 0x319a8  (est. txm_amfi_verify_signature)
 * Ghidra: undefined4 FUN_000319a8(long, ulong, ulong, int)
 * Verifies an AMFI CMS signature against a hash and algorithm type.
 * 0x53 on success.
 * Confidence: low */
unsigned txm_amfi_verify_signature(unsigned long ctx, unsigned long base, unsigned long size,
                                   int algo) {
    if ((*(unsigned char*)(ctx + 0x59) & 1) == 0) return 0x12253;
    if (base == 0) return 0x22c53;
    if (size == 0) return 0x32c53;
    if (base + size < base) return 0x42153;
    if (*(unsigned long*)(ctx + 0x38) == 0) return 0x62453;
    int ty = *(int*)(ctx + 0x30);
    int sel;
    switch (ty) {
    case 0: return 0x52853;
    case 1: sel = 1; break;
    case 4: sel = (algo == 3) ? 3 : 2; break;
    case 8: sel = 4; break;
    default: return 0x72853;
    }
    if (sel != algo) return 0x82953;
    if (*(unsigned long*)(ctx + 0x40) < size) return 0x92353;
    if (txm_memcmp((void*)base, (void*)*(unsigned long*)(ctx + 0x38), size)) return 0xa2953;
    return 0x53;
}

/* FUN_00031ac0 @ 0x31ac0  (est. txm_amfi_get_data)
 * Ghidra: undefined* FUN_00031ac0(undefined8*, undefined8*)
 * Returns the CMS data range (ctx[0..1]). 0x54 on success.
 * Confidence: low */
void *txm_amfi_get_data(unsigned long *ctx, unsigned long *out) {
    if ((*(unsigned char*)(ctx + 0xb) & 1) == 0) return (void*)0x10754;
    if (out) { out[0] = ctx[0]; out[1] = ctx[1]; }
    return (void*)0x54;
}

/* FUN_00031aec @ 0x31aec  (est. txm_amfi_get_digest)
 * Ghidra: undefined* FUN_00031aec(long, undefined8*)
 * Returns the CMS digest (ctx+0x20/+0x28). 0x55 on success.
 * Confidence: low */
void *txm_amfi_get_digest(unsigned long ctx, unsigned long *out) {
    if ((*(unsigned char*)(ctx + 0x58) & 1) == 0) return (void*)0x10755;
    if (out) { out[0] = *(unsigned long*)(ctx + 0x20); out[1] = *(unsigned long*)(ctx + 0x28); }
    return (void*)0x55;
}

/* FUN_00031b18 @ 0x31b18  (est. txm_amfi_get_digest2)
 * Ghidra: undefined* FUN_00031b18(long, undefined8*)
 * Returns ctx+0x10/+0x18. 0x56 on success.
 * Confidence: low */
void *txm_amfi_get_digest2(unsigned long ctx, unsigned long *out) {
    if ((*(unsigned char*)(ctx + 0x58) & 1) == 0) return (void*)0x10756;
    if (out) { out[0] = *(unsigned long*)(ctx + 0x10); out[1] = *(unsigned long*)(ctx + 0x18); }
    return (void*)0x56;
}

/* FUN_00031b44 @ 0x31b44  (est. txm_amfi_get_flags)
 * Ghidra: undefined* FUN_00031b44(long, undefined8*)
 * Returns the AMFI flags (ctx+0x50). 0x58 on success.
 * Confidence: low */
void *txm_amfi_get_flags(unsigned long ctx, unsigned long *out) {
    if ((*(unsigned char*)(ctx + 0x59) & 1) == 0) return (void*)0x12258;
    if (out) *out = *(unsigned long*)(ctx + 0x50);
    return (void*)0x58;
}

/* FUN_00031b70 @ 0x31b70  (est. txm_cectx_create)
 * Ghidra: undefined* FUN_00031b70(long*, long*, ulong, ulong)
 * Creates a CEContext from a profile+owner: zeroes the ctx (0x188 bytes),
 * validates the profile's "parsed" flag and owner hash, calls 3161c (AMFI CMS
 * parse), and sets the ready bit. Returns 0x20 on success.
 * Confidence: medium */
void *txm_cectx_create(unsigned long *owner, unsigned long *ctx, unsigned long base,
                       unsigned long size) {
    txm_bzero(ctx, 0x188 / 8);
    if (base == 0) return (void*)0x12c20;
    if (size == 0) return (void*)0x12c20;
    if (base + size < base) return (void*)0x32120;
    unsigned long o = *owner;
    if (o == 0) return (void*)0x40220;
    if ((*(unsigned char*)(o + 0x4d) & 1) == 0 || owner[0x14] != 0) {
        if ((*(unsigned char*)(o + 0x4e) & 1) != 0 && owner[0x15] == 0)
            return (void*)0x60220;
        if (owner[1] == 0) return (void*)0x73020;
        if (((*(unsigned long(*)())owner[1])() & 1) != 0) return (void*)0x73020;
        o = *owner;
        if ((*(unsigned char*)(o + 6) & 1) == 0) {
            void *r = (void*)(unsigned long)txm_amfi_cms_parse(ctx + 1,
                        *(unsigned char*)((char*)owner + 0xd3) & 1, base, size);
            if ((unsigned long)r & 0xff00) return r;
            *ctx = (unsigned long)owner;
            *(unsigned char*)(ctx + 0x30) = 1;
            return (void*)0x20;
        }
    }
    return (void*)0x40220;
}

/* FUN_00031cb0 @ 0x31cb0  (est. txm_cectx_init_with_type)
 * Ghidra: undefined* FUN_00031cb0(long*)
 * Full CEContext initialization: verifies the CMS (31714), reads flags/digest,
 * runs the kernel profile function (5fb88), fills the ctx digest fields, and
 * computes the entitlement/profile bits (34e90 + 34dc4). Returns 0x21.
 * Confidence: medium */
void *txm_cectx_init_with_type(unsigned long *ctx) {
    if ((*(unsigned char*)(ctx + 0x30) & 1) == 0) return (void*)0x10821;
    if ((*(unsigned char*)((char*)ctx + 0x181) & 1) != 0) return (void*)0x23421;
    unsigned long o = *ctx;
    unsigned long fl = 0, d1 = 0;
    void *rc;
    rc = (void*)(unsigned long)txm_amfi_cms_verify(ctx + 1, 0, 0);
    if ((unsigned long)rc & 0xff00) return rc;
    txm_amfi_get_flags((unsigned long)(ctx + 1), &fl);
    if ((*(unsigned long*)(*(unsigned long*)*ctx + 0x38) & fl) == 0) return (void*)0x32221;
    txm_amfi_get_digest((unsigned long)(ctx + 1), &d1);
    if (d1 == 0) return (void*)0x42421;
    if (txm_kernel_profile(*(unsigned long*)(o + 0x10), 2, &d1)) {
        txm_log("_profile: CEContextInitWithTypeL failed\n");
        return (void*)0x52f21;
    }
    /* copy profile-derived digest fields into ctx (offsets 0xd..0x1d) */
    if (((unsigned long)(rc = (void*)(unsigned long)txm_entitlements_set(ctx)) & 0xff00) == 0 &&
        ((unsigned long)(rc = (void*)(unsigned long)txm_profile_flags(ctx)) & 0xff00) == 0) {
        *(unsigned char*)((char*)ctx + 0x181) = 1;
        return (void*)0x21;
    }
    return rc;
}

/* FUN_00031e34 @ 0x31e34  (est. txm_cectx_finalize)
 * Ghidra: undefined* FUN_00031e34(long*, undefined8)
 * Finalizes a CEContext: runs the profile update (34420) and the owner's
 * finalize callback. Returns 0x22 on success.
 * Confidence: medium */
void *txm_cectx_finalize(unsigned long *ctx, unsigned long arg) {
    if ((*(unsigned char*)((char*)ctx + 0x181) & 1) == 0) return (void*)0x12222;
    if ((*(unsigned char*)((char*)ctx + 0x182) & 1) != 0) return (void*)0x22;
    unsigned long o = *ctx;
    void *rc = (void*)(unsigned long)txm_cectx_profile_update(ctx);
    if ((unsigned long)rc & 0xff00) return rc;
    if (*(void**)(o + 0x68) != 0 &&
        ((*(unsigned long(**)(void*, unsigned long))(o + 0x68))(ctx, arg) == 0))
        return (void*)0x23b22;
    *(unsigned char*)((char*)ctx + 0x182) = 1;
    return (void*)0x22;
}

/* FUN_00031ecc @ 0x31ecc  (est. txm_cectx_compare)
 * Ghidra: uint FUN_00031ecc(long*, long*)
 * Compares two CEContexts (344f4); 0x24 on success.
 * Confidence: low */
unsigned txm_cectx_compare(unsigned long *a, unsigned long *b) {
    if ((*(unsigned char*)((char*)a + 0x182) & 1) == 0) return 0x12224;
    if (b[1] == 0) return 0x20324;
    if (a[0] != b[0]) return 0x32924;
    unsigned r = txm_profile_flags();
    return (r & 0xff00) != 0 ? r : 0x24;
}

/* FUN_00031f3c @ 0x31f3c  (est. txm_cectx_get_data)
 * Ghidra: undefined* FUN_00031f3c(long, undefined8*)
 * Returns the CMS data range via 31ac0. 0x23 on success.
 * Confidence: low */
void *txm_cectx_get_data(unsigned long ctx, unsigned long *out) {
    unsigned long d[2]; void *rc;
    if ((*(unsigned char*)(ctx + 0x180) & 1) == 0) return (void*)0x10823;
    rc = txm_amfi_get_data((unsigned long*)(ctx + 8), d);
    if ((unsigned long)rc & 0xff00) return rc;
    if (out) { out[0] = d[0]; out[1] = d[1]; }
    return (void*)0x23;
}

/* FUN_00031fa0 @ 0x31fa0  (est. txm_cectx_get_type_flags)
 * Ghidra: undefined* FUN_00031fa0(long, undefined4*)
 * Returns the ctx type flags (ctx+0x17c). 0x28 on success.
 * Confidence: low */
void *txm_cectx_get_type_flags(unsigned long ctx, unsigned *out) {
    if ((*(unsigned char*)(ctx + 0x181) & 1) == 0) return (void*)0x12228;
    if (out) *out = *(unsigned*)(ctx + 0x17c);
    return (void*)0x28;
}

/* FUN_00031fcc @ 0x31fcc  (est. txm_cectx_get_hash)
 * Ghidra: undefined* FUN_00031fcc(long)
 * Returns the ctx hash via 34f24.
 * Confidence: low */
void *txm_cectx_get_hash(unsigned long ctx) {
    if ((*(unsigned char*)(ctx + 0x181) & 1) == 0) return (void*)0x1222a;
    return (void*)(unsigned long)txm_team_identifier(ctx, 0);
}

/* FUN_00031fe8 @ 0x31fe8  (est. txm_cectx_get_entitlements)
 * Ghidra: undefined* FUN_00031fe8(long, long*)
 * Returns the entitlements pointer (ctx+0x68). 0x2b on success.
 * Confidence: low */
void *txm_cectx_get_entitlements(unsigned long ctx, unsigned long *out) {
    if ((*(unsigned char*)(ctx + 0x181) & 1) == 0) return (void*)0x1222b;
    if (out) *out = ctx + 0x68;
    return (void*)0x2b;
}

/* FUN_00032014 @ 0x32014  (est. txm_cectx_check)
 * Ghidra: undefined4 FUN_00032014(long, long)
 * Applies the CEContext checks (beta/team/Apple-internal). 0x25 on success.
 * Confidence: low */
unsigned txm_cectx_check(unsigned long ctx, unsigned long other) {
    if ((*(unsigned char*)(ctx + 0x181) & 1) == 0) return 0x12225;
    unsigned long p = txm_profile_flags();
    if (other != 0) {
        unsigned f = *(unsigned*)(ctx + 0x17c);
        if ((f >> 2 & 1) != 0) {
            unsigned i = 0;
            do {
                if ((txm_cectx_teamid(other, (&DAT_00010c20)[i], 0) & 0xff00) == 0)
                    return 0x23025;
                f = *(unsigned*)(ctx + 0x17c);
            } while (((f >> 2 & 1) != 0) && (i++ < 2));
        }
        if ((f >> 3 & 1) == 0) {
            if (p == 0) return 0x33025;
            if ((txm_cectx_validate(other, p) & 0xff00) == 0) return 0x25;
            return 0x42925;
        }
    }
    return 0x25;
}

/* FUN_00032104 @ 0x32104  (est. txm_cectx_team_id)
 * Ghidra: undefined4 FUN_00032104(long, long)
 * Validates the TeamIdentifier entitlement (60088 -> 5f4b4 -> 5fa9c).
 * Confidence: low */
unsigned txm_cectx_team_id(unsigned long ctx, unsigned long arg) {
    unsigned long h[5]; int r; unsigned tag;
    txm_bzero(h, sizeof h);
    if ((*(unsigned char*)(ctx + 0x181) & 1) == 0) return 0x12226;
    if ((*(unsigned char*)(ctx + 0x17c) >> 1 & 1) != 0) return 0x26;
    if (arg == 0) return 0x22c26;
    if (txm_dict_init(ctx + 0x68, "TeamIdentifier", h)) return 0x33026;
    if (txm_dict_int(h, &tag)) return 0x42626;
    if (tag == 2) {
        if (txm_dict_flags(h, arg)) return 0x52926;
        return 0x26;
    }
    return 0x42626;
}

/* FUN_000321dc @ 0x321dc  (est. txm_cectx_dev_certs)
 * Ghidra: void FUN_000321dc(long, ulong, ulong)
 * Validates the DeveloperCertificates entitlement (60088 -> 5f750 -> 5fa0c).
 * Confidence: low */
void txm_cectx_dev_certs(unsigned long ctx, unsigned long base, unsigned long size) {
    unsigned long canary = DAT_00006cf0;
    unsigned long h[5], cert;
    txm_bzero(h, sizeof h);
    if ((*(unsigned char*)(ctx + 0x181) & 1) != 0) {
        if (base != 0 && size != 0 && base + size >= base) {
            if (txm_dict_init(ctx + 0x68, "DeveloperCertificates", h) == 0) {
                txm_hash_amfi(2, base, size, 0, &cert);
                unsigned long l[2]; l[0] = (unsigned long)&cert; l[1] = 0x20;
                int r = txm_dict_cert_array(h, &l);
                unsigned rc = (r == 10) ? 0x62627 : (r ? 0x72927 : 0x27);
                if (DAT_00006cf0 == canary) return;
                txm_stack_check_fail();
                return;
            }
        }
    }
    txm_stack_check_fail();
}

/* FUN_00032308 @ 0x32308  (est. txm_apple_internal_check)
 * Ghidra: void FUN_00032308(long)
 * Resolves the TeamIdentifier, looks it up in the Apple-internal team table
 * (DAT_10c44, 22 entries), applies the corresponding capability flags, and
 * sets the "apple-internal" capability bit (0x20000 class). Unknown teams are
 * denied (0x2900 class). Requires bit 3 of ctx+0x17c.
 * Confidence: high (Apple-internal capability tables + strings) */
void txm_apple_internal_check(unsigned long ctx) {
    unsigned long canary = DAT_00006cf0;
    unsigned rc, class_, err;
    if ((*(unsigned char*)(ctx + 0x17c) >> 3 & 1) == 0) { err = 0xc4; goto out; }
    {
        unsigned long team = 0, tlen = 0;
        char name[0x40];
        txm_bzero(name, sizeof name);
        rc = txm_team_identifier(ctx, &team);
        if ((rc & 0xff00) == 0) {
            if (tlen < 0x40) {
                unsigned *flags = (unsigned*)(ctx + 0x17c);
                txm_memcpy_chk(name, (void*)team, tlen, 0x40);
                unsigned i = 0;
                for (i = 0; i < 0x40; i++) if (name[i] == '\0') break;
                /* scan the internal-team table (DAT_10c44: name + flags, stride 0x10) */
                unsigned char *tbl = (unsigned char*)&DAT_00010c44;
                int found = 0;
                for (i = 0; i < 0x16; i++) {
                    if (txm_strcmp(name, *(const char**)(tbl + i*0x10 - 0xc)) == 0) {
                        if (*(tbl + i*0x10 - 4) & 1) {
                            txm_log("'%s' removing apple-internal cap\n");
                            *flags &= ~8U;
                        }
                        txm_cap_apply(flags, (unsigned*)(tbl + i*0x10));
                        class_ = 0; err = 0;
                        goto out;
                    }
                }
                txm_log("'%s' unknown apple-internal team\n");
                class_ = 0x20000; err = 0x2900;
                goto out;
            }
            class_ = 0x10000; err = 0x2500;
            goto out;
        }
        class_ = rc & 0xffff0000;
        err = rc & 0xff;
    }
out:
    if (DAT_00006cf0 == canary) return;
    txm_stack_check_fail();
}

/* FUN_00032484 @ 0x32484  (est. txm_cectx_clear_caps)
 * Ghidra: void FUN_00032484(long)
 * Clears the standard capability flags (from DAT_10da0, 6 entries).
 * Confidence: low */
void txm_cectx_clear_caps(unsigned long ctx) {
    unsigned *tbl = (unsigned*)&DAT_00010da0;
    for (int i = 0; i < 6; i++) {
        unsigned long r = txm_cap_probe(ctx, *(unsigned long*)(tbl + i*2 - 2));
        if ((r & 0xff00) == 0) txm_cap_apply((unsigned*)(ctx + 0x17c), tbl + i*2);
    }
}

/* FUN_000324f4 @ 0x324f4  (est. txm_version_compare)
 * Ghidra: undefined4 FUN_000324f4(uint, uint)
 * Compares two 4-element version bytes (permutation table). Returns -1/0/1 or
 * 0x7fffffff/0x80000001 on out-of-range.
 * Confidence: low */
unsigned txm_version_compare(unsigned a, unsigned b) {
    static const unsigned char map[5] = {0,1,3,2,4};
    if (a - 5 < 0xfffffffc) return 0x80000001;
    if (0xfffffffb < b - 5) return 0x7fffffff;
    if (map[a] == map[b]) return 0;
    return map[b] <= map[a] ? 1 : 0xffffffff;
}

/* FUN_000325b0 @ 0x325b0  (est. txm_hash_dispatch)
 * Ghidra: undefined* FUN_000325b0(int, undefined8, undefined8, undefined8)
 * Dispatches to the crypto hash for kind (1/2/4): 439b0/3f9a8/439c0.
 * Confidence: low */
void *txm_hash_dispatch(int kind, const void *data, unsigned long len, void *digest) {
    unsigned long h;
    if (kind - 2U < 2) h = txm_kernel_boot_3();
    else if (kind == 1) h = txm_hash_ctx_a();
    else if (kind != 4) return (void*)0x128e0;
    else h = txm_kernel_boot_2();
    txm_hash_ctx_init(h, digest, data, 0);
    return (void*)0xe0;
}

/* FUN_00032630 @ 0x32630  (est. txm_codedir_parse)
 * Ghidra: uint FUN_00032630(int*, ulong, undefined8*)
 * Parses a code-signature CodeDirectory superblob: validates the magic
 * (-0x3ff32106 = 0xc0dec0de? no: 0xcfaeddee family), the number of CodeDir
 * entries, the per-entry offsets/stride, and marks each entry via 32910.
 * Returns the parse status (class/error). This is the CodeDirectory layout
 * validator.
 * Confidence: high (CodeDirectory/superblob structure) */
unsigned txm_codedir_parse(unsigned *blob, unsigned long size, unsigned long *out) {
    unsigned char seen[16];
    txm_bzero(seen, sizeof seen);
    unsigned long end = (unsigned long)blob + size;
    unsigned *entries = blob + 3;
    if (end < (unsigned long)entries) txm_assert(0x19);
    if (blob[0] != (unsigned)-0x3ff32106) return 0x10000 | 0x2600 | 0x60;
    unsigned n = ((blob[1] & 0xff00ff00) >> 8 | (blob[1] & 0xff00ff) << 8);
    n = n >> 0x10 | n << 0x10;
    unsigned long total = n;
    if (size < total) return 0x20000 | 0x2100 | 0x60;
    unsigned count = blob[2];
    if (count == 0) return 0x30000 | 0x2400 | 0x60;
    unsigned cnt = ((count & 0xff00ff00) >> 8 | (count & 0xff00ff) << 8) >> 0x10
                   | ((count & 0xff00ff00) >> 8 | (count & 0xff00ff) << 8) << 0x10;
    if ((count & 0xffff) >> 0xd != 0) return 0x40000 | 0x2600 | 0x60;
    if (cnt == 0xffffff1f) return 0x50000 | 0x12100 | 0x60;
    if (total < (unsigned long)cnt * 8 + 0xc) return 0x60000 | 0x22100 | 0x60;
    if ((long)(size - 0xc) >> 3 < (long)cnt) txm_assert(0x19);
    unsigned long idx = cnt * 2;
    unsigned *dir = blob + idx + 3;
    unsigned *e = entries;
    unsigned long left = cnt;
    do {
        if ((unsigned long)dir <= (unsigned long)e || (unsigned long)e < (unsigned long)entries)
            txm_assert(0x19);
        unsigned off = ((e[1] & 0xff00ff00) >> 8 | (e[1] & 0xff00ff) << 8);
        off = off >> 0x10 | off << 0x10;
        if (total <= off) return 0x70000 | 0x2160 | 0x60;
        if ((unsigned*)((char*)blob + off) != dir) return 0x80000 | 0x2760 | 0x60;
        if ((unsigned*)((char*)blob + total) - 2 < dir) return 0x90000 | 0x2360 | 0x60;
        if (end < (unsigned long)(dir + 2)) txm_assert(0x19);
        unsigned sz = ((dir[1] & 0xff00ff00) >> 8 | (dir[1] & 0xff00ff) << 8) >> 0x10
                      | ((dir[1] & 0xff00ff00) >> 8 | (dir[1] & 0xff00ff) << 8) << 0x10;
        if (sz < 8) return 0xa0000 | 0x2360 | 0x60;
        if (off + sz < off) return 0xb0000 | 0x2160 | 0x60;
        if (total < sz + off) return 0xc0000 | 0x2160 | 0x60;
        unsigned magic = ((e[0] & 0xff00ff00) >> 8 | (e[0] & 0xff00ff) << 8) >> 0x10
                         | ((e[0] & 0xff00ff00) >> 8 | (e[0] & 0xff00ff) << 8) << 0x10;
        unsigned mark = txm_codedir_mark(seen, magic, dir);
        if (mark & 0xff00) return mark & 0x30000 | mark & 0xff | 0x60;
        dir = (unsigned*)((char*)dir + sz);
        left--; e += 2;
    } while (left != 0);
    if ((unsigned*)((char*)blob + total) == dir) {
        if ((seen[0] & 1) == 0) return 0xe0000 | 0x1000 | 0x60;
        if (out) { out[0] = (unsigned long)blob; out[1] = total; }
        return 0x60;
    }
    return 0xd0000 | 0x2500 | 0x60;
}

/* FUN_00032910 @ 0x32910  (est. txm_codedir_mark)
 * Ghidra: undefined* FUN_00032910(byte*, int, uint*)
 * Validates + marks a CodeDirectory entry: checks the magic (per the
 * offset/size classification: 0xfade0c02/0xfade0c01/0xfade7171/0xfade7172/
 * 0xfade8181/0xfade0b01 etc) and sets the "seen" bit. Returns 0x61 on success.
 * Confidence: high (CodeDirectory magic values) */
void *txm_codedir_mark(unsigned char *seen, unsigned magic, unsigned *dir) {
    unsigned expected;
    unsigned char *markp;
    switch (magic) {
    case 0: expected = 0xfade0c02; markp = seen + 1; break;
    case 2: expected = 0xfade0c01; markp = seen + 7; break;
    case 5: expected = 0xfade7171; markp = seen + 8; break;
    case 7: expected = 0xfade7172; markp = seen + 9; break;
    case 8: case 9: case 10: case 0xb:
        expected = 0xfade8181;
        markp = seen + (magic - 8 + 9);
        break;
    case 0x1000: expected = 0xfade0c02; markp = seen + 6; break;
    case 0x1001: expected = 0xfade0c02; markp = seen + 6; break;
    case 0x1002: expected = 0xfade0c02; markp = seen + 6; break;
    case 0x1003: expected = 0xfade0c02; markp = seen + 6; break;
    case 0x1004: expected = 0xfade0c02; markp = seen + 6; break;
    case 0x10000: expected = 0xfade0b01; markp = seen + 0xe; break;
    default: return (void*)0x12961;
    }
    unsigned v = ((dir[0] & 0xff00ff00) >> 8 | (dir[0] & 0xff00ff) << 8) >> 0x10
                 | ((dir[0] & 0xff00ff00) >> 8 | (dir[0] & 0xff00ff) << 8) << 0x10;
    if (expected != v) return (void*)0x12961;
    if ((*markp & 1) != 0) return (void*)0x22b61;
    *markp = 1;
    return (void*)0x61;
}

/* FUN_00032b38 @ 0x32b38  (est. txm_superblob_find_command)
 * Ghidra: undefined1[16] FUN_00032b38(uint*, ulong, uint, uint, undefined4*)
 * Searches a superblob for the command (type param_3, magic param_4) and
 * returns {cmd_ptr, cmd_size}. Panics on malformed bounds.
 * Confidence: medium */
void txm_superblob_find_command(unsigned *blob, unsigned long size, unsigned type,
                                unsigned magic, unsigned *index) {
    unsigned long idx = 0;
    unsigned *entries = blob + 3;
    unsigned *end = (unsigned*)((char*)blob + (size & 0xffffffff));
    if ((unsigned long)entries <= (unsigned long)end && (unsigned long)blob <= (unsigned long)entries) {
        unsigned n = blob[2];
        unsigned cnt = ((n & 0xff00ff00) >> 8 | (n & 0xff00ff) << 8) >> 0x10
                       | ((n & 0xff00ff00) >> 8 | (n & 0xff00ff) << 8) << 0x10;
        if ((long)cnt <= (long)((size & 0xffffffff) - 0xc) >> 3) {
            unsigned *b = entries + cnt * 2;
            if (n != 0) {
                unsigned *p = entries;
                do {
                    if ((unsigned long)b <= (unsigned long)p || (unsigned long)p < (unsigned long)entries)
                        txm_assert(0x19);
                    unsigned t = ((p[0] & 0xff00ff00) >> 8 | (p[0] & 0xff00ff) << 8) >> 0x10
                                 | ((p[0] & 0xff00ff00) >> 8 | (p[0] & 0xff00ff) << 8) << 0x10;
                    if (type == t) {
                        unsigned off = ((p[1] & 0xff00ff00) >> 8 | (p[1] & 0xff00ff) << 8) >> 0x10
                                       | ((p[1] & 0xff00ff00) >> 8 | (p[1] & 0xff00ff) << 8) << 0x10;
                        unsigned *cmd = (unsigned*)((char*)blob + off);
                        if (cmd < blob || end < cmd + 2) txm_assert(0x19);
                        unsigned m = ((cmd[0] & 0xff00ff00) >> 8 | (cmd[0] & 0xff00ff) << 8) >> 0x10
                                     | ((cmd[0] & 0xff00ff00) >> 8 | (cmd[0] & 0xff00ff) << 8) << 0x10;
                        if (magic == m) {
                            if (index) *index = (unsigned)idx;
                            unsigned sz = ((cmd[1] & 0xff00ff00) >> 8 | (cmd[1] & 0xff00ff) << 8) >> 0x10
                                          | ((cmd[1] & 0xff00ff00) >> 8 | (cmd[1] & 0xff00ff) << 8) << 0x10;
                            if (end < cmd || (size & 0xffffffff) - off < sz) txm_assert(0x19);
                            return;
                        }
                    }
                    idx++; p += 2;
                } while (cnt != idx);
            }
        }
    }
    txm_assert(0x19);
}

/* FUN_00032c30 @ 0x32c30  (est. txm_superblob_get_cmd)
 * Ghidra: undefined* FUN_00032c30(uint*, uint, uint*, long*)
 * Returns the superblob magic + the command data (base, len-8). 0x13 on success.
 * Confidence: low */
void *txm_superblob_get_cmd(unsigned *blob, unsigned size, unsigned *magic, unsigned long *out) {
    if (size < 8) return (void*)0x12313;
    if (magic) {
        unsigned v = ((blob[0] & 0xff00ff00) >> 8 | (blob[0] & 0xff00ff) << 8) >> 0x10
                     | ((blob[0] & 0xff00ff00) >> 8 | (blob[0] & 0xff00ff) << 8) << 0x10;
        *magic = v;
    }
    if (out) { out[0] = (unsigned long)(blob + 2); out[1] = size - 8; }
    return (void*)0x13;
}

/* ---- superblob / CodeDirectory parse region (32c70-33d40) ---- */

/* FUN_00032c70 @ 0x32c70  (est. txm_superblob_parse)
 * Ghidra: uint FUN_00032c70(undefined8*, int*, ulong)
 * Parses a code-signing superblob (magic 0x20cdefa = CSMAGIC_EMBEDDED_SIGNATURE,
 * but treated as the outer blob with CodeDirectory sub-commands). Walks the
 * embedded CodeDirectory commands, validating their offsets/stride and invoking
 * the per-version parser (33150/331b8/33254/33334/33414/334cc). Returns the
 * parse status word. This is the central signature-structure validator.
 * Confidence: high (CodeDirectory/superblob structure + version magic) */
unsigned txm_superblob_parse(unsigned long *out, unsigned *blob, unsigned long size) {
    unsigned long v;
    if ((size & 0xffffffff) < 0x2c) return 0x10000 | 0x2300 | 0x60;
    if (blob[0] == 0x20cdefa) {
        unsigned ver = ((blob[2] & 0xff00ff00) >> 8 | (blob[2] & 0xff00ff) << 8) >> 0x10
                       | ((blob[2] & 0xff00ff00) >> 8 | (blob[2] & 0xff00ff) << 8) << 0x10;
        unsigned cl = 0x30000, err = 0x60;
        if (0x202ff < ver) {
            if (0x204ff < ver) {
                if (ver == 0x20500) { err = 0x60; }
                else if (ver == 0x20600) { err = 0x6c; }
                else if (0x205ff < ver) { err = 0x6c; }
                else { cl = 0x30000; err = 0x60; goto classed; }
                goto bounds;
            }
            if (ver == 0x20300) { err = 0x40; goto bounds; }
            if (ver == 0x20400) { err = 0x58; goto bounds; }
            cl = 0x30000; err = 0x60; goto classed;
        }
        if (ver - 0x20000 < 2) err = 0x2c;
        else if (ver == 0x20100) err = 0x30;
        else if (ver == 0x20200) err = 0x34;
        else { cl = 0x30000; err = 0x60; goto classed; }
bounds:
        if (ver < *(unsigned*)*out) { cl = 0x40000; err = 0x3000; goto classed; }
        unsigned hlen = ((blob[1] & 0xff00ff00) >> 8 | (blob[1] & 0xff00ff) << 8) >> 0x10
                        | ((blob[1] & 0xff00ff00) >> 8 | (blob[1] & 0xff00ff) << 8) << 0x10;
        if (hlen < err) { cl = 0x50000; err = 0x2300; goto classed; }
        if (hlen == (unsigned)size) {
            unsigned char ht;
            if (txm_platform_of(*(unsigned char*)((char*)blob + 0x25), &ht)) {
                unsigned hb = *(unsigned char*)(blob + 9);
                if (hb == ht) {
                    unsigned off = blob[4];
                    if (off == 0) { cl = 0x80000; err = 0x2400; goto classed; }
                    unsigned offb = ((off & 0xff00ff00) >> 8 | (off & 0xff00ff) << 8) >> 0x10
                                    | ((off & 0xff00ff00) >> 8 | (off & 0xff00ff) << 8) << 0x10;
                    if (offb < (unsigned)size) {
                        /* parse embedded CodeDirectory version chain */
                        unsigned ncmd = blob[6];
                        unsigned nc = ((ncmd & 0xff00ff00) >> 8 | (ncmd & 0xff00ff) << 8) >> 0x10
                                      | ((ncmd & 0xff00ff00) >> 8 | (ncmd & 0xff00ff) << 8) << 0x10;
                        if (nc == 0) { cl = 0xe0000; err = 0x2700; goto classed; }
                        unsigned szc = ((blob[7] & 0xff00ff00) >> 8 | (blob[7] & 0xff00ff) << 8) >> 0x10
                                       | ((blob[7] & 0xff00ff00) >> 8 | (blob[7] & 0xff00ff) << 8) << 0x10;
                        unsigned long total = (unsigned long)nc * hb;
                        if (total & 0xffffffff00000000UL) { cl = 0xf0000; err = 0x2100; goto classed; }
                        unsigned tot = (unsigned)total;
                        if (offb + tot < offb) { cl = 0x100000; err = 0x2100; goto classed; }
                        if ((unsigned)size < offb + tot) { cl = 0x110000; err = 0x2100; goto classed; }
                        unsigned soff = blob[5];
                        if (soff == 0) { cl = 0x120000; err = 0x2400; goto classed; }
                        unsigned soffb = ((soff & 0xff00ff00) >> 8 | (soff & 0xff00ff) << 8) >> 0x10
                                         | ((soff & 0xff00ff00) >> 8 | (soff & 0xff00ff) << 8) << 0x10;
                        if (soffb < (unsigned)size) {
                            unsigned char *sc = (unsigned char*)((char*)blob + soffb);
                            unsigned char *bend = (unsigned char*)((char*)blob + size);
                            if (bend < sc || sc < (unsigned char*)blob) txm_assert(0x19);
                            unsigned long slen = txm_strlen_v((char*)sc);
                            if (size - soffb <= slen) { cl = 0x150000; err = 0x3100; goto classed; }
                            if (slen == 0) { cl = 0x160000; err = 0x2400; goto classed; }
                            if (*(unsigned char*)((char*)blob + 0x27) < 0xc) { cl = 0x170000; err = 0x2800; goto classed; }
                            if (*(unsigned char*)((char*)blob + 0x27) >= 0xf) { cl = 0x180000; err = 0x2800; goto classed; }
                            unsigned long ident;
                            if (!txm_codedir_hash_ok(blob, size, &ident)) { cl = 0x190000; err = 0x2900; goto classed; }
                            /* parse per-version */
                            if (ver >> 8 < 0x201) goto clean;
                            if ((unsigned*)sc < (unsigned*)blob + 0xc) txm_assert(0x19);
                            if (blob[0xb] != 0) { cl = 0x12800 & 0x10000; err = 0x70; goto classed; }
                            if (ver < 0x20200) goto clean;
                            unsigned r;
                            if ((r = txm_codedir_v0_parse(blob, size, sc)) & 0xff00) { cl = r & 0x70000; err = r & 0xff; goto classed; }
                            if (0x203ff < ver) {
                                if ((r = txm_codedir_v1_parse(blob, size, ident)) & 0xff00) { cl = r & 0x70000; err = r & 0xff; goto classed; }
                                if (0x204ff < ver) {
                                    if ((r = txm_codedir_v2_parse(blob, size, sc)) & 0xff00) { cl = r & 0x70000; err = r & 0xff; goto classed; }
                                    if (0x205ff < ver) {
                                        if ((r = txm_codedir_v3_parse(blob, size, sc)) & 0xff00) { cl = r & 0x70000; err = r & 0xff; goto classed; }
                                    }
                                }
                            }
clean:
                            cl = 0; err = 0; goto classed;
                        }
                        cl = 0x140000; err = 0x2700; goto classed;
                    }
                    cl = 0x130000; err = 0x2400; goto classed;
                }
                cl = 0x70000; err = 0x2800; goto classed;
            }
            cl = 0x60000; err = 0x2800; goto classed;
        }
        cl = 0x1a0000; err = 0x2900; goto classed;
    } else {
        cl = 0x20000; err = 0x2600; goto classed;
    }
classed:
    return err & 0xff00 | 0x62 & 0xff | cl;
}

/* FUN_00033150 @ 0x33150  (est. txm_platform_of)
 * Ghidra: undefined8 FUN_00033150(undefined8, undefined1*)
 * Decodes the platform byte (0x30142014 >> shift); returns 1 and the byte.
 * Confidence: low */
unsigned long txm_platform_of(unsigned long platform, unsigned char *out) {
    if (txm_version_compare(platform, 0) == 0x7fffffff &&
        ((unsigned)(platform - 1) & 0xff) < 4) {
        *out = (unsigned char)(0x30142014 >> (((unsigned)(platform - 1) & 3) << 3));
        return 1;
    }
    return 0;
}

/* FUN_000331b8 @ 0x331b8  (est. txm_codedir_hash_ok)
 * Ghidra: bool FUN_000331b8(long, uint, ulong*)
 * Checks the CodeDirectory hash: computes the "hash size mask" (page-hash
 * shift) and verifies the hash-slots count matches the command length. Returns
 * the computed hash (for the identifier). True if the slot count is consistent.
 * Confidence: medium */
bool txm_codedir_hash_ok(unsigned long cd, unsigned size, unsigned long *out) {
    if (cd + size < cd + 0x2cU) txm_assert(0x19);
    unsigned ver = ((*(unsigned*)(cd + 8) & 0xff00ff00) >> 8 | (*(unsigned*)(cd + 8) & 0xff00ff) << 8) >> 0x10
                   | ((*(unsigned*)(cd + 8) & 0xff00ff00) >> 8 | (*(unsigned*)(cd + 8) & 0xff00ff) << 8) << 0x10;
    unsigned long h;
    if (0x202 < ver >> 8) {
        if (cd + size < cd + 0x40U) txm_assert(0x19);
        h = *(unsigned long*)(cd + 0x38);
        if (h != 0) {
            h = ((h & 0xff00ff00ff00ff00) >> 8 | (h & 0xff00ff00ff00ff) << 8);
            h = ((h & 0xffff0000ffff0000) >> 0x10 | (h & 0xffff0000ffff) << 0x10);
            h = h >> 0x20 | h << 0x20;
        }
    } else {
        unsigned v = ((*(unsigned*)(cd + 0x20) & 0xff00ff00) >> 8 | (*(unsigned*)(cd + 0x20) & 0xff00ff) << 8) >> 0x10
                     | ((*(unsigned*)(cd + 0x20) & 0xff00ff00) >> 8 | (*(unsigned*)(cd + 0x20) & 0xff00ff) << 8) << 0x10;
        h = v;
    }
    unsigned n = ((*(unsigned*)(cd + 0x1c) & 0xff00ff00) >> 8 | (*(unsigned*)(cd + 0x1c) & 0xff00ff) << 8) >> 0x10
                 | ((*(unsigned*)(cd + 0x1c) & 0xff00ff00) >> 8 | (*(unsigned*)(cd + 0x1c) & 0xff00ff) << 8) << 0x10;
    unsigned shift = *(unsigned char*)(cd + 0x27) & 0x1f;
    unsigned long h2 = h >> (*(unsigned char*)(cd + 0x27) & 0x3f);
    if (h & ~((unsigned long)(~0U << shift))) h2++;
    if (h2 == n) *out = h;
    return h2 == n;
}

/* FUN_00033254 @ 0x33254  (est. txm_codedir_v0_parse)
 * Ghidra: undefined4 FUN_00033254(ulong, ulong, ulong)
 * Validates a version-0 CodeDirectory: non-zero, within bounds, hash-stride
 * covers the pages. 0x71 on success.
 * Confidence: medium */
unsigned txm_codedir_v0_parse(unsigned long cd, unsigned long size, unsigned long page) {
    unsigned long end = cd + (size & 0xffffffff);
    if (cd + 0x2c <= end && cd + 0x34 <= end) {
        unsigned h = *(unsigned*)(cd + 0x30);
        if (h == 0) return 0x71;
        unsigned hn = ((h & 0xff00ff00) >> 8 | (h & 0xff00ff) << 8) >> 0x10
                      | ((h & 0xff00ff00) >> 8 | (h & 0xff00ff) << 8) << 0x10;
        unsigned nh = ((*(unsigned*)(cd + 4) & 0xff00ff00) >> 8 | (*(unsigned*)(cd + 4) & 0xff00ff) << 8) >> 0x10
                      | ((*(unsigned*)(cd + 4) & 0xff00ff00) >> 8 | (*(unsigned*)(cd + 4) & 0xff00ff) << 8) << 0x10;
        if (hn < nh) {
            unsigned long hash = cd + hn;
            if (hash < page) return 0x22771;
            if (end < hash || hash < cd) txm_assert(0x19);
            unsigned long len = nh - hn;
            if ((size & 0xffffffff) - hn < len) txm_assert(0x19);
            unsigned long z = txm_strlen_v((char*)hash);
            if (z < len) return z != 0 ? 0x71 : 0x42471;
            return 0x33171;
        }
        return 0x12171;
    }
    txm_assert(0x19);
    return 0;
}

/* FUN_00033334 @ 0x33334  (est. txm_codedir_v1_parse)
 * Ghidra: int FUN_00033334(long, uint, ulong)
 * Validates a version-1 CodeDirectory: checks the identifier range and the
 * (base+hash) overflow against the bounds. 0x72 on success.
 * Confidence: medium */
int txm_codedir_v1_parse(unsigned long cd, unsigned size, unsigned long page) {
    if (cd + size < cd + 0x2cU || cd + size < cd + 0x58U) txm_assert(0x19);
    unsigned long a = ((*(unsigned long*)(cd + 0x40) & 0xff00ff00ff00ff00) >> 8 | (*(unsigned long*)(cd + 0x40) & 0xff00ff00ff00ff) << 8);
    a = ((a & 0xffff0000ffff0000) >> 0x10 | (a & 0xffff0000ffff) << 0x10);
    unsigned long ah = a >> 0x20;
    unsigned long a2 = ah | a << 0x20;
    unsigned long b = ((*(unsigned long*)(cd + 0x48) & 0xff00ff00ff00ff00) >> 8 | (*(unsigned long*)(cd + 0x48) & 0xff00ff00ff00ff) << 8);
    b = ((b & 0xffff0000ffff0000) >> 0x10 | (b & 0xffff0000ffff) << 0x10);
    unsigned long b2 = b >> 0x20 | b << 0x20;
    unsigned long sum = a2 + b2;
    if (a2 + b2 < a2) return 0x12172;
    unsigned shift = *(unsigned char*)(cd + 0x27) & 0x1f;
    unsigned long mask = ~0U << shift;
    if ((ah & mask) != 0) return 0x22a72;
    if ((sum & mask) != 0) return 0x22a72;
    unsigned n = ((*(unsigned*)(cd + 0x1c) & 0xff00ff00) >> 8 | (*(unsigned*)(cd + 0x1c) & 0xff00ff) << 8) >> 0x10
                 | ((*(unsigned*)(cd + 0x1c) & 0xff00ff00) >> 8 | (*(unsigned*)(cd + 0x1c) & 0xff00ff) << 8) << 0x10;
    if (n <= a2 >> (*(unsigned char*)(cd + 0x27) & 0x3f)) return 0x42172;
    if (sum >> (*(unsigned char*)(cd + 0x27) & 0x3f) <= n) {
        if (sum <= page) return 0x72572;
        return 0x72;
    }
    return 0x22a72;
}

/* FUN_00033414 @ 0x33414  (est. txm_codedir_v2_parse)
 * Ghidra: undefined4 FUN_00033414(long, uint, ulong)
 * Validates a version-2 CodeDirectory: non-zero hash, within bounds, count
 * covers pages. 0x73 on success.
 * Confidence: medium */
unsigned txm_codedir_v2_parse(unsigned long cd, unsigned size, unsigned long page) {
    if (cd + 0x60U <= cd + size && cd + 0x2cU <= cd + size) {
        unsigned h = *(unsigned*)(cd + 0x5c);
        if (h == 0) return 0x73;
        unsigned hn = ((h & 0xff00ff00) >> 8 | (h & 0xff00ff) << 8) >> 0x10
                      | ((h & 0xff00ff00) >> 8 | (h & 0xff00ff) << 8) << 0x10;
        unsigned nh = ((*(unsigned*)(cd + 4) & 0xff00ff00) >> 8 | (*(unsigned*)(cd + 4) & 0xff00ff) << 8) >> 0x10
                      | ((*(unsigned*)(cd + 4) & 0xff00ff00) >> 8 | (*(unsigned*)(cd + 4) & 0xff00ff) << 8) << 0x10;
        if (hn < nh) {
            if (cd + hn < page) return 0x22773;
            unsigned per = ((*(unsigned*)(cd + 0x1c) & 0xff00ff00) >> 8 | (*(unsigned*)(cd + 0x1c) & 0xff00ff) << 8) >> 0x10
                           | ((*(unsigned*)(cd + 0x1c) & 0xff00ff00) >> 8 | (*(unsigned*)(cd + 0x1c) & 0xff00ff) << 8) << 0x10;
            unsigned step = per * *(unsigned char*)(cd + 0x24);
            if (!(hn + step < hn) && step + hn <= nh) return 0x73;
            return 0x32173;
        }
        return 0x12173;
    }
    txm_assert(0x19);
    return 0;
}

/* FUN_000334cc @ 0x334cc  (est. txm_codedir_v3_parse)
 * Ghidra: int FUN_000334cc(long, ulong, ulong)
 * Validates a version-3 CodeDirectory: non-zero hash, within bounds, count
 * covers the hash entries + the platform hash length. 0x74 on success.
 * Confidence: medium */
int txm_codedir_v3_parse(unsigned long cd, unsigned long size, unsigned long page) {
    unsigned long end = cd + (size & 0xffffffff);
    unsigned char pbyte;
    if (end < cd + 0x6cU || end < cd + 0x2cU) txm_assert(0x19);
    unsigned h = *(unsigned*)(cd + 100);
    pbyte = 0;
    if (h == 0) return 0x74;
    unsigned hn = ((h & 0xff00ff00) >> 8 | (h & 0xff00ff) << 8) >> 0x10
                  | ((h & 0xff00ff00) >> 8 | (h & 0xff00ff) << 8) << 0x10;
    unsigned nh = ((*(unsigned*)(cd + 4) & 0xff00ff00) >> 8 | (*(unsigned*)(cd + 4) & 0xff00ff) << 8) >> 0x10
                  | ((*(unsigned*)(cd + 4) & 0xff00ff00) >> 8 | (*(unsigned*)(cd + 4) & 0xff00ff) << 8) << 0x10;
    if (hn < nh) {
        if (cd + hn < page) return 0x22774;
        unsigned hl = ((*(unsigned*)(cd + 0x68) & 0xff00ff00) >> 8 | (*(unsigned*)(cd + 0x68) & 0xff00ff) << 8) >> 0x10
                      | ((*(unsigned*)(cd + 0x68) & 0xff00ff00) >> 8 | (*(unsigned*)(cd + 0x68) & 0xff00ff) << 8) << 0x10;
        if (!(hn + hl < hn) && hl + hn <= nh) {
            if (!txm_platform_of(*(unsigned char*)(cd + 0x60), &pbyte)) return 0x52874;
            if (0x13 < hl) return pbyte < hl ? 0x72974 : 0x74;
        }
        return 0x32174;
    }
    return 0x12174;
}

/* FUN_000335c8 @ 0x335c8  (est. txm_codedir_verify)
 * Ghidra: undefined* FUN_000335c8(undefined8, undefined8, undefined8, undefined8)
 * Verifies a CodeDirectory: finds the 0xfade7172 (embedded signature) command,
 * then validates via 3366c or hashes via 33784. 0x76 on success.
 * Confidence: medium */
void *txm_codedir_verify(unsigned long blob, unsigned long size, unsigned long hashbase,
                         unsigned long hashsize) {
    unsigned long cmd[2];
    unsigned long r;
    txm_superblob_find_command((unsigned*)blob, size, 7, 0xfade7172, 0);
    r = txm_codedir_find_slot(hashbase, hashsize, 7, 0);
    if ((r & 0xff00) == 0) return (void*)0x12476;
    r = txm_codedir_hash(hashbase, hashsize, 7);
    if ((r & 0xff00) != 0) return (void*)0x22976;
    return (void*)0x76;
}

/* FUN_0003366c @ 0x3366c  (est. txm_codedir_find_slot)
 * Ghidra: void FUN_0003366c(ulong, ulong, uint, ulong*)
 * Finds the hash slot for a CodeDirectory command: searches the page-hash
 * table for the identifier, returns {slot, len}. 0x80 on success.
 * Confidence: medium */
void txm_codedir_find_slot(unsigned long base, unsigned long size, unsigned magic,
                           unsigned long *out) {
    unsigned long canary = DAT_00006cf0;
    unsigned long end = base + (size & 0xffffffff);
    void *rc;
    if (end < base + 0x2c) txm_assert(0x19);
    unsigned cnt = ((*(unsigned*)(base + 0x18) & 0xff00ff00) >> 8 | (*(unsigned*)(base + 0x18) & 0xff00ff) << 8) >> 0x10
                   | ((*(unsigned*)(base + 0x18) & 0xff00ff00) >> 8 | (*(unsigned*)(base + 0x18) & 0xff00ff) << 8) << 0x10;
    if (cnt < magic) rc = (void*)0x12480;
    else if (magic != 0) {
        unsigned long stride = *(unsigned char*)(base + 0x24);
        if (stride < 0x31) {
            unsigned hoff = ((*(unsigned*)(base + 0x10) & 0xff00ff00) >> 8 | (*(unsigned*)(base + 0x10) & 0xff00ff) << 8) >> 0x10
                            | ((*(unsigned*)(base + 0x10) & 0xff00ff00) >> 8 | (*(unsigned*)(base + 0x10) & 0xff00ff) << 8) << 0x10;
            unsigned long hs = hoff;
            unsigned long need = (unsigned long)magic * stride;
            unsigned long slot = (base + hs) - need;
            if (slot <= end && base <= slot &&
                stride <= ((size & 0xffffffff) - hs) + need) {
                if (txm_memcmp((void*)slot, 0, stride) == 0) rc = (void*)0x32480;
                else {
                    if (out) { out[0] = slot; out[1] = stride; }
                    rc = (void*)0x80;
                }
                if (DAT_00006cf0 == canary) return;
                txm_stack_check_fail();
                return;
            }
        }
        txm_assert(0x19);
    } else rc = (void*)0x22c80;
    if (DAT_00006cf0 == canary) return;
    txm_stack_check_fail();
}

/* FUN_00033784 @ 0x33784  (est. txm_codedir_hash)
 * Ghidra: void FUN_00033784(long, ulong, undefined8, undefined8, undefined4)
 * Hashes a CodeDirectory command (after finding its slot via 3366c) with the
 * platform hash. 0x3f on success.
 * Confidence: medium */
void txm_codedir_hash(unsigned long base, unsigned long size, unsigned long cmd,
                      unsigned long hashbase, unsigned hashsize) {
    unsigned long canary = DAT_00006cf0;
    unsigned long r, digest[2];
    txm_bzero(digest, sizeof digest);
    r = txm_codedir_find_slot(base, size, 0, 0);
    if ((r & 0xff00) == 0) {
        if (base + (size & 0xffffffff) < base + 0x2cU) txm_assert(0x19);
        txm_hash_dispatch(*(unsigned char*)(base + 0x25), hashbase, hashsize, digest);
        int c = txm_memcmp(0, digest, 0);
        r = c != 0 ? 0x1293f : 0x3f;
    }
    if (DAT_00006cf0 == canary) return;
    txm_stack_check_fail();
}

/* FUN_00033864 @ 0x33864  (est. txm_codedir_compare)
 * Ghidra: undefined4 FUN_00033864(char*, ulong, char*, ulong)
 * Compares two CodeDirectory commands for equality of version, hash type,
 * hash size, identifier, and code-hash. 0x77 on success (equal), else the
 * differing-field error.
 * Confidence: medium */
unsigned txm_codedir_compare(char *a, unsigned long asize, char *b, unsigned long bsize) {
    unsigned long aend = (unsigned long)a + (asize & 0xffffffff);
    unsigned long bend = (unsigned long)b + (bsize & 0xffffffff);
    if (aend < (unsigned long)a + 0x2c || bend < (unsigned long)b + 0x2c) txm_assert(0x19);
    unsigned av = *(unsigned*)(a + 8), bv = *(unsigned*)(b + 8);
    if (av != bv) return 0x12977;
    if (*(int*)(a + 0xc) != *(int*)(b + 0xc)) return 0x22977;
    unsigned av2 = ((av & 0xff00ff00) >> 8 | (av & 0xff00ff) << 8);
    if ((av2 >> 0x10 | av2 << 0x10) >> 8 < 0x203) {
        unsigned v = ((*(unsigned*)(a + 0x20) & 0xff00ff00) >> 8 | (*(unsigned*)(a + 0x20) & 0xff00ff) << 8) >> 0x10
                     | ((*(unsigned*)(a + 0x20) & 0xff00ff00) >> 8 | (*(unsigned*)(a + 0x20) & 0xff00ff) << 8) << 0x10;
        unsigned long ah = v;
        unsigned w = ((*(unsigned*)(b + 0x20) & 0xff00ff00) >> 8 | (*(unsigned*)(b + 0x20) & 0xff00ff) << 8) >> 0x10
                     | ((*(unsigned*)(b + 0x20) & 0xff00ff00) >> 8 | (*(unsigned*)(b + 0x20) & 0xff00ff) << 8) << 0x10;
        unsigned long bh = w;
        if (ah != bh) return 0x32977;
    } else {
        if (aend < (unsigned long)a + 0x40) txm_assert(0x19);
        unsigned long ah = *(unsigned long*)(a + 0x38);
        if (ah != 0) ah = ((ah & 0xff00ff00ff00ff00) >> 8 | (ah & 0xff00ff00ff00ff) << 8);
        ah = ((ah & 0xffff0000ffff0000) >> 0x10 | (ah & 0xffff0000ffff) << 0x10);
        ah = ah >> 0x20 | ah << 0x20;
        if (bend < (unsigned long)b + 0x40) txm_assert(0x19);
        unsigned long bh = *(unsigned long*)(b + 0x38);
        if (bh != 0) bh = ((bh & 0xff00ff00ff00ff00) >> 8 | (bh & 0xff00ff00ff00ff) << 8);
        bh = ((bh & 0xffff0000ffff0000) >> 0x10 | (bh & 0xffff0000ffff) << 0x10);
        bh = bh >> 0x20 | bh << 0x20;
        if (ah != bh) return 0x32977;
    }
    /* identifiers */
    unsigned aoff = ((*(unsigned*)(a + 0x14) & 0xff00ff00) >> 8 | (*(unsigned*)(a + 0x14) & 0xff00ff) << 8) >> 0x10
                    | ((*(unsigned*)(a + 0x14) & 0xff00ff00) >> 8 | (*(unsigned*)(a + 0x14) & 0xff00ff) << 8) << 0x10;
    char *ap = a + aoff;
    while (*(unsigned char*)ap) ap++;
    unsigned boff = ((*(unsigned*)(b + 0x14) & 0xff00ff00) >> 8 | (*(unsigned*)(b + 0x14) & 0xff00ff) << 8) >> 0x10
                    | ((*(unsigned*)(b + 0x14) & 0xff00ff00) >> 8 | (*(unsigned*)(b + 0x14) & 0xff00ff) << 8) << 0x10;
    char *bp = b + boff;
    while (*(unsigned char*)bp) bp++;
    if (txm_strcmp(a + aoff, b + boff)) return 0x42977;
    unsigned long aid = 0, bid = 0;
    txm_codedir_team(a, asize, &aid);
    txm_codedir_team(b, bsize, &bid);
    if ((aid == 0 || bid == 0) && aid != bid) return 0x52977;
    if (aid != 0 && bid != 0 && txm_strcmp((char*)aid, (char*)bid)) return 0x62977;
    /* code hash (v2+ only) */
    unsigned long ah = 0, bh = 0;
    if (((*(unsigned*)(a + 8) & 0xff00ff00) >> 8 | (*(unsigned*)(a + 8) & 0xff00ff) << 8) >> 0x10
        | ((*(unsigned*)(a + 8) & 0xff00ff00) >> 8 | (*(unsigned*)(a + 8) & 0xff00ff) << 8) << 0x10 >= 0x20400) {
        if (aend < (unsigned long)a + 0x58) txm_assert(0x19);
        ah = ((*(unsigned long*)(a + 0x50) & 0xff00ff00ff00ff00) >> 8 | (*(unsigned long*)(a + 0x50) & 0xff00ff00ff00ff) << 8);
        ah = ((ah & 0xffff0000ffff0000) >> 0x10 | (ah & 0xffff0000ffff) << 0x10);
        ah = ah >> 0x20 | ah << 0x20;
    }
    if (((*(unsigned*)(b + 8) & 0xff00ff00) >> 8 | (*(unsigned*)(b + 8) & 0xff00ff) << 8) >> 0x10
        | ((*(unsigned*)(b + 8) & 0xff00ff00) >> 8 | (*(unsigned*)(b + 8) & 0xff00ff) << 8) << 0x10 >= 0x20400) {
        if (bend < (unsigned long)b + 0x58) txm_assert(0x19);
        bh = ((*(unsigned long*)(b + 0x50) & 0xff00ff00ff00ff00) >> 8 | (*(unsigned long*)(b + 0x50) & 0xff00ff00ff00ff) << 8);
        bh = ((bh & 0xffff0000ffff0000) >> 0x10 | (bh & 0xffff0000ffff) << 0x10);
        bh = bh >> 0x20 | bh << 0x20;
    }
    if (ah == bh) return 0x10077;
    return 0x72977;
}

/* FUN_00033ad4 @ 0x33ad4  (est. txm_codedir_get_count)
 * Ghidra: undefined8 FUN_00033ad4(long, uint, uint*)
 * Returns the hash count (nCodeSlots) of a CodeDirectory. 0x31 on success.
 * Confidence: low */
unsigned long txm_codedir_get_count(unsigned long cd, unsigned size, unsigned *out) {
    if (out) {
        if (cd + size < cd + 0x2cU) txm_assert(0x19);
        unsigned v = ((*(unsigned*)(cd + 0xc) & 0xff00ff00) >> 8 | (*(unsigned*)(cd + 0xc) & 0xff00ff) << 8) >> 0x10
                     | ((*(unsigned*)(cd + 0xc) & 0xff00ff00) >> 8 | (*(unsigned*)(cd + 0xc) & 0xff00ff) << 8) << 0x10;
        *out = v;
    }
    return 0x31;
}

/* FUN_00033b14 @ 0x33b14  (est. txm_codedir_get_hash_size)
 * Ghidra: undefined8 FUN_00033b14(long, uint, ulong*)
 * Returns the hash size (nCodeHashSize) of a CodeDirectory. 0x35 on success.
 * Confidence: low */
unsigned long txm_codedir_get_hash_size(unsigned long cd, unsigned size, unsigned long *out) {
    if (cd + size < cd + 0x2cU) txm_assert(0x19);
    unsigned ver = ((*(unsigned*)(cd + 8) & 0xff00ff00) >> 8 | (*(unsigned*)(cd + 8) & 0xff00ff) << 8);
    unsigned long h;
    if (0x202 < (ver >> 0x10 | ver << 0x10) >> 8) {
        if (cd + size < cd + 0x40U) txm_assert(0x19);
        h = *(unsigned long*)(cd + 0x38);
        if (h != 0) {
            h = ((h & 0xff00ff00ff00ff00) >> 8 | (h & 0xff00ff00ff00ff) << 8);
            h = ((h & 0xffff0000ffff0000) >> 0x10 | (h & 0xffff0000ffff) << 0x10);
            h = h >> 0x20 | h << 0x20;
        }
    } else {
        unsigned v = ((*(unsigned*)(cd + 0x20) & 0xff00ff00) >> 8 | (*(unsigned*)(cd + 0x20) & 0xff00ff) << 8) >> 0x10
                     | ((*(unsigned*)(cd + 0x20) & 0xff00ff00) >> 8 | (*(unsigned*)(cd + 0x20) & 0xff00ff) << 8) << 0x10;
        h = v;
    }
    if (out) *out = h;
    return 0x35;
}

/* FUN_00033b88 @ 0x33b88  (est. txm_codedir_get_identifier)
 * Ghidra: undefined8 FUN_00033b88(char*, uint, ulong*)
 * Returns the identifier string pointer of a CodeDirectory. 0x32 on success.
 * Confidence: low */
unsigned long txm_codedir_get_identifier(char *cd, unsigned size, unsigned long *out) {
    char *end = cd + size;
    if (cd + 0x2c <= end) {
        if (out) {
            unsigned v = ((*(unsigned*)(cd + 0x14) & 0xff00ff00) >> 8 | (*(unsigned*)(cd + 0x14) & 0xff00ff) << 8) >> 0x10
                         | ((*(unsigned*)(cd + 0x14) & 0xff00ff00) >> 8 | (*(unsigned*)(cd + 0x14) & 0xff00ff) << 8) << 0x10;
            char *p = cd + v;
            if (p < cd || end <= p) txm_assert(0x19);
            char *q = cd + v;
            while (*(unsigned char*)q) q++;
            *out = (unsigned long)p;
        }
        return 0x32;
    }
    txm_assert(0x19);
    return 0;
}

/* FUN_00033bf4 @ 0x33bf4  (est. txm_codedir_team)
 * Ghidra: undefined* FUN_00033bf4(char*, uint, ulong*)
 * Returns the team id string of a CodeDirectory (v2+: at +0x30). 0x39.
 * Confidence: low */
void *txm_codedir_team(char *cd, unsigned size, unsigned long *out) {
    char *end = cd + size;
    if (cd + 0x2c <= end) {
        unsigned ver = ((*(unsigned*)(cd + 8) & 0xff00ff00) >> 8 | (*(unsigned*)(cd + 8) & 0xff00ff) << 8) >> 0x10
                       | ((*(unsigned*)(cd + 8) & 0xff00ff00) >> 8 | (*(unsigned*)(cd + 8) & 0xff00ff) << 8) << 0x10;
        if (ver >> 9 < 0x101) return (void*)0x12839;
        if (end < cd + 0x34) txm_assert(0x19);
        unsigned off = *(unsigned*)(cd + 0x30);
        if (off == 0) return (void*)0x22439;
        if (out) {
            unsigned v = ((off & 0xff00ff00) >> 8 | (off & 0xff00ff) << 8) >> 0x10
                         | ((off & 0xff00ff00) >> 8 | (off & 0xff00ff) << 8) << 0x10;
            char *p = cd + v;
            if (p < cd || end <= p) txm_assert(0x19);
            char *q = cd + v;
            while (*(unsigned char*)q) q++;
            *out = (unsigned long)p;
        }
        return (void*)0x39;
    }
    txm_assert(0x19);
    return 0;
}

/* FUN_00033c9c @ 0x33c9c  (est. txm_codedir_get_special)
 * Ghidra: undefined* FUN_00033c9c(long, uint, ulong*, ulong*, ulong*)
 * Returns the special-slot hash offsets (code/digest/special) of a v2+
 * CodeDirectory. 0x3a on success.
 * Confidence: low */
void *txm_codedir_get_special(unsigned long cd, unsigned size, unsigned long *a,
                              unsigned long *b, unsigned long *c) {
    unsigned long end = cd + size;
    if (cd + 0x2cU <= end) {
        unsigned ver = ((*(unsigned*)(cd + 8) & 0xff00ff00) >> 8 | (*(unsigned*)(cd + 8) & 0xff00ff) << 8) >> 0x10
                       | ((*(unsigned*)(cd + 8) & 0xff00ff00) >> 8 | (*(unsigned*)(cd + 8) & 0xff00ff) << 8) << 0x10;
        if (ver >> 10 < 0x81) return (void*)0x1283a;
        if (end < cd + 0x58U) txm_assert(0x19);
        if (a) { unsigned long v = ((*(unsigned long*)(cd + 0x40) & 0xff00ff00ff00ff00) >> 8 | (*(unsigned long*)(cd + 0x40) & 0xff00ff00ff00ff) << 8);
                 v = ((v & 0xffff0000ffff0000) >> 0x10 | (v & 0xffff0000ffff) << 0x10);
                 *a = v >> 0x20 | v << 0x20; }
        if (b) { unsigned long v = ((*(unsigned long*)(cd + 0x48) & 0xff00ff00ff00ff00) >> 8 | (*(unsigned long*)(cd + 0x48) & 0xff00ff00ff00ff) << 8);
                 v = ((v & 0xffff0000ffff0000) >> 0x10 | (v & 0xffff0000ffff) << 0x10);
                 *b = v >> 0x20 | v << 0x20; }
        if (c) { unsigned long v = ((*(unsigned long*)(cd + 0x50) & 0xff00ff00ff00ff00) >> 8 | (*(unsigned long*)(cd + 0x50) & 0xff00ff00ff00ff) << 8);
                 v = ((v & 0xffff0000ffff0000) >> 0x10 | (v & 0xffff0000ffff) << 0x10);
                 *c = v >> 0x20 | v << 0x20; }
        return (void*)0x3a;
    }
    txm_assert(0x19);
    return 0;
}

/* FUN_00033d40 @ 0x33d40  (est. txm_superblob_parse_full)
 * Ghidra: uint FUN_00033d40(undefined8, undefined8, undefined8, long*)
 * Full superblob parse: iterates the 5 possible CodeDirectory command slots,
 * validates each via 32c70/335c8, de-duplicates by hash type, and returns the
 * chosen command (param_4). 0x75 on success.
 * Confidence: medium */
unsigned txm_superblob_parse_full(unsigned long state, unsigned long blob,
                                  unsigned long size, unsigned long *out) {
    unsigned long canary = DAT_00006cf0;
    unsigned long cmd[5][2];
    unsigned long last[2];
    unsigned long chosen[2];
    unsigned long r;
    unsigned count = 0;
    txm_bzero(cmd, sizeof cmd);
    txm_bzero(last, sizeof last); txm_bzero(chosen, sizeof chosen);
    r = 0x10000;   /* class */
    unsigned cl = 0x1000;
    unsigned char *slots[5];
    int n = 0;
    for (int i = 0; i < 5; i++) {
        unsigned long c[2];
        txm_superblob_find_command((unsigned*)blob, size, i | 0x1000, 0xfade0c02, 0);
        if (c[0] != 0) {
            if (n != 0) { r = 0x20000; goto out; }
            count++;
        }
    }
    if (count >= 5) { r = 0x30000; cl = 0x2500; goto out; }
    for (int i = 0; i < (int)count; i++) {
        unsigned long cb = cmd[i][0], cs = cmd[i][1];
        unsigned s = txm_superblob_parse(0, (unsigned*)cb, cs);
        if ((s & 0xff00) != 0) { r = s & 0x1f0000; goto out; }
        s = (unsigned)(unsigned long)txm_codedir_verify(blob, size, cb, cs);
        if ((s & 0xff00) != 0) { r = s & 0x30000; goto out; }
        unsigned long ca = cs, cbb = cb;
        if (last[0] != 0) {
            s = txm_codedir_compare((char*)last[0], last[1], (char*)cb, cs);
            ca = last[1]; cbb = last[0];
            if ((s & 0xff00) != 0) { r = s & 0x70000; goto out; }
        }
        if (cb + cs < cb + 0x2c) txm_assert(0x19);
        unsigned char ht = *(unsigned char*)(cb + 0x25);
        if (chosen[ht*2] != 0) { r = 0x40000; cl = 0x2b00; goto out; }
        if (chosen + 10 <= &chosen[ht*2]) txm_assert(0x19);
        chosen[ht*2] = cb;
        chosen[ht*2+1] = cs;
        count--;
        last[0] = cbb; last[1] = ca;
    }
    if (chosen[8] == 0) {
        unsigned long u[2] = {chosen[4], chosen[5]};
        if (chosen[4] != 0 || chosen[6] != 0 || chosen[2] != 0) {
            r = 0; cl = 0;
            if (out) { out[0] = chosen[2]; out[1] = chosen[3]; }
        } else { r = 0x50000; cl = 0x2400; }
    } else {
        r = 0; cl = 0;
        if (out) { out[0] = chosen[8]; out[1] = chosen[9]; }
    }
out:
    if (DAT_00006cf0 == canary) return (unsigned)(cl & 0xff00) | (0x75 & 0xff) | (r & 0xffffffff);
    txm_stack_check_fail();
    return 0;
}

/* ---- CodeDirectory getters (34028-344f4) + entitlements/trust (345f4-34ff8) ---- */

/* FUN_00034028 @ 0x34028  (est. txm_codedir_get_platform)
 * Ghidra: undefined8 FUN_00034028(long, uint, undefined1*, undefined1*)
 * Returns the platform + hash-type bytes of a CodeDirectory. 0x36 on success.
 * Confidence: low */
unsigned long txm_codedir_get_platform(unsigned long cd, unsigned size,
                                       unsigned char *plat, unsigned char *ht) {
    if (plat) {
        if (cd + size < cd + 0x2cU) txm_assert(0x19);
        *plat = *(unsigned char*)(cd + 0x25);
    }
    if (ht) {
        if (cd + size < cd + 0x2cU) txm_assert(0x19);
        *ht = *(unsigned char*)(cd + 0x24);
    }
    return 0x36;
}

/* FUN_0003407c @ 0x3407c  (est. txm_codedir_get_page_size)
 * Ghidra: undefined8 FUN_0003407c(long, uint, int*)
 * Returns the page-size (1 << nHashShift) of a CodeDirectory. 0x38.
 * Confidence: low */
unsigned long txm_codedir_get_page_size(unsigned long cd, unsigned size, int *out) {
    if (cd + 0x2cU <= cd + size) {
        if (out) *out = 1 << (*(unsigned char*)(cd + 0x27) & 0x1f);
        return 0x38;
    }
    txm_assert(0x19);
    return 0;
}

/* FUN_000340c0 @ 0x340c0  (est. txm_codedir_get_hash_slot)
 * Ghidra: undefined* FUN_000340c0(ulong, uint, undefined1*, ulong*)
 * Returns the hash slot (offset + len) of a v2+ CodeDirectory. 0x3c.
 * Confidence: low */
void *txm_codedir_get_hash_slot(unsigned long cd, unsigned size, unsigned char *plat,
                                unsigned long *out) {
    unsigned long end = cd + size;
    if (cd + 0x2c <= end) {
        unsigned ver = ((*(unsigned*)(cd + 8) & 0xff00ff00) >> 8 | (*(unsigned*)(cd + 8) & 0xff00ff) << 8) >> 0x10
                       | ((*(unsigned*)(cd + 8) & 0xff00ff00) >> 8 | (*(unsigned*)(cd + 8) & 0xff00ff) << 8) << 0x10;
        if (ver >> 9 < 0x103) return (void*)0x1283c;
        if (end < cd + 0x6c) txm_assert(0x19);
        unsigned off = *(unsigned*)(cd + 100);
        if (off == 0) return (void*)0x2243c;
        if (plat) *plat = *(unsigned char*)(cd + 0x60);
        if (out) {
            unsigned v = ((off & 0xff00ff00) >> 8 | (off & 0xff00ff) << 8) >> 0x10
                         | ((off & 0xff00ff00) >> 8 | (off & 0xff00ff) << 8) << 0x10;
            unsigned long base = cd + v;
            unsigned l = ((*(unsigned*)(cd + 0x68) & 0xff00ff00) >> 8 | (*(unsigned*)(cd + 0x68) & 0xff00ff) << 8) >> 0x10
                          | ((*(unsigned*)(cd + 0x68) & 0xff00ff00) >> 8 | (*(unsigned*)(cd + 0x68) & 0xff00ff) << 8) << 0x10;
            if (end < base || base < cd) txm_assert(0x19);
            if (size - v < l) txm_assert(0x19);
            out[0] = base; out[1] = l;
        }
        return (void*)0x3c;
    }
    txm_assert(0x19);
    return 0;
}

/* FUN_00034174 @ 0x34174  (est. txm_codedir_get_hash_flags)
 * Ghidra: undefined* FUN_00034174(long, uint, undefined1*, ushort*)
 * Returns the hash-flags byte + nHashSlots of a v2+ CodeDirectory. 0x3d.
 * Confidence: low */
void *txm_codedir_get_hash_flags(unsigned long cd, unsigned size, unsigned char *flags,
                                 unsigned short *out) {
    if (cd + 0x2cU <= cd + size) {
        unsigned ver = ((*(unsigned*)(cd + 8) & 0xff00ff00) >> 8 | (*(unsigned*)(cd + 8) & 0xff00ff) << 8) >> 0x10
                       | ((*(unsigned*)(cd + 8) & 0xff00ff00) >> 8 | (*(unsigned*)(cd + 8) & 0xff00ff) << 8) << 0x10;
        if (ver >> 9 < 0x103) return (void*)0x1283d;
        if (cd + size < cd + 0x6cU) txm_assert(0x19);
        if (*(int*)(cd + 100) == 0) return (void*)0x2243d;
        if (flags) *flags = *(unsigned char*)(cd + 0x61);
        if (out) *out = *(unsigned short*)(cd + 0x62) >> 8 | *(unsigned short*)(cd + 0x62) << 8;
        return (void*)0x3d;
    }
    txm_assert(0x19);
    return 0;
}

/* FUN_00034204 @ 0x34204  (est. txm_codedir_verify_hash)
 * Ghidra: void FUN_00034204(ulong, ulong, uint, undefined8, ulong)
 * Verifies one hash slot of a CodeDirectory: computes the hash over the
 * (slot index * hash-stride) range and compares. 0x3e on success.
 * Confidence: medium */
void txm_codedir_verify_hash(unsigned long cd, unsigned long size, unsigned idx,
                             void *hash, unsigned long hashsize) {
    unsigned long canary = DAT_00006cf0;
    unsigned long end = cd + (size & 0xffffffff);
    unsigned long digest[2];
    void *rc;
    txm_bzero(digest, sizeof digest);
    if (end < cd + 0x2c) txm_assert(0x19);
    unsigned count = ((*(unsigned*)(cd + 0x1c) & 0xff00ff00) >> 8 | (*(unsigned*)(cd + 0x1c) & 0xff00ff) << 8) >> 0x10
                     | ((*(unsigned*)(cd + 0x1c) & 0xff00ff00) >> 8 | (*(unsigned*)(cd + 0x1c) & 0xff00ff) << 8) << 0x10;
    if (count <= idx) { rc = (void*)0x1213e; goto out; }
    unsigned hoff = ((*(unsigned*)(cd + 0x10) & 0xff00ff00) >> 8 | (*(unsigned*)(cd + 0x10) & 0xff00ff) << 8) >> 0x10
                    | ((*(unsigned*)(cd + 0x10) & 0xff00ff00) >> 8 | (*(unsigned*)(cd + 0x10) & 0xff00ff) << 8) << 0x10;
    unsigned char *hs = (unsigned char*)(cd + hoff);
    unsigned ver = ((*(unsigned*)(cd + 8) & 0xff00ff00) >> 8 | (*(unsigned*)(cd + 8) & 0xff00ff) << 8) >> 0x10
                   | ((*(unsigned*)(cd + 8) & 0xff00ff00) >> 8 | (*(unsigned*)(cd + 8) & 0xff00ff) << 8) << 0x10;
    unsigned long slothash = 0, isCode = 0;
    if (ver >= 0x20500) {
        if (end < cd + 0x60) txm_assert(0x19);
        unsigned so = *(unsigned*)(cd + 0x5c);
        if (so != 0) {
            unsigned sv = ((so & 0xff00ff00) >> 8 | (so & 0xff00ff) << 8) >> 0x10
                          | ((so & 0xff00ff00) >> 8 | (so & 0xff00ff) << 8) << 0x10;
            slothash = cd + sv; isCode = cd;
        }
    }
    unsigned shift = *(unsigned char*)(cd + 0x27) & 0x1f;
    unsigned long pgsize = 1 << shift;
    if (idx == count - 1) {
        if (ver < 0x20300) {
            unsigned v = ((*(unsigned*)(cd + 0x20) & 0xff00ff00) >> 8 | (*(unsigned*)(cd + 0x20) & 0xff00ff) << 8) >> 0x10
                         | ((*(unsigned*)(cd + 0x20) & 0xff00ff00) >> 8 | (*(unsigned*)(cd + 0x20) & 0xff00ff) << 8) << 0x10;
            unsigned long h = v;
            if (h) pgsize = h;
        } else {
            unsigned long h = *(unsigned long*)(cd + 0x38);
            if (h != 0) {
                h = ((h & 0xff00ff00ff00ff00) >> 8 | (h & 0xff00ff00ff00ff) << 8);
                h = ((h & 0xffff0000ffff0000) >> 0x10 | (h & 0xffff0000ffff) << 0x10);
                pgsize = (h >> 0x20 | h << 0x20) & (pgsize - 1);
            }
        }
    }
    if (hashsize < pgsize) { rc = (void*)0x2233e; goto out; }
    txm_hash_dispatch(*(unsigned char*)(cd + 0x25), hash, pgsize, digest);
    unsigned char stride = *(unsigned char*)(cd + 0x24);
    unsigned char *slot = hs + idx * stride;
    if (stride > 0x30 || end < slot || slot < (unsigned char*)cd) txm_assert(0x19);
    if (end - slot < stride) txm_assert(0x19);
    if (txm_memcmp(slot, digest, stride) == 0) rc = (void*)0x3e;
    else {
        /* v2+ also checks the code-slot copy */
        unsigned char *code = (unsigned char*)slothash + idx * stride;
        if (isCode != 0) {
            if (stride > 0x30 || end < code || code < (unsigned char*)isCode) txm_assert(0x19);
            if (end - code < stride) txm_assert(0x19);
            if (txm_memcmp(code, digest, stride) == 0) rc = (void*)0x3e;
            else rc = (void*)0x3293e;
        } else rc = (void*)0x3293e;
    }
out:
    if (DAT_00006cf0 == canary) return;
    txm_stack_check_fail();
}

/* FUN_00034420 @ 0x34420  (est. txm_cectx_profile_update)
 * Ghidra: undefined4 FUN_00034420(long*)
 * Updates the CEContext's provisioned-devices/profile flag (ProvisionedDevices
 * entitlement via 60088 -> 5fae0). 0xc5 on success.
 * Confidence: low */
unsigned txm_cectx_profile_update(unsigned long *ctx) {
    unsigned long h[5];
    txm_bzero(h, sizeof h);
    if ((*(unsigned char*)((char*)ctx + 0x181) & 1) == 0) return 0x122c5;
    if ((*(unsigned char*)((char*)ctx + 0x17c) >> 2 & 1) != 0) return 0xc5;
    unsigned long o = *ctx;
    if (txm_strlen_v((char*)(o + 0x38)) >= 0x30) return 0x221c5;
    if (txm_dict_init(ctx + 0xd, "ProvisionedDevices", h)) return 0x330c5;
    unsigned long p = o + 0x38;
    if (txm_dict_value2(h, &p)) return 0x429c5;
    return 0xc5;
}

/* FUN_000344f4 @ 0x344f4  (est. txm_profile_flags)
 * Ghidra: undefined* FUN_000344f4(long*)
 * Evaluates the CEContext's profile capability flags by invoking the owner's
 * profile/developer callbacks. Returns 0xc2 with the decision.
 * Confidence: low */
void *txm_profile_flags(unsigned long *ctx) {
    unsigned long o = *ctx;
    unsigned long flags = *(unsigned*)((char*)ctx + 0x17c);
    if ((*(unsigned char*)(o + 0x4d) & 1) != 0 && (flags & 1) != 0) {
        if ((*(unsigned long(*)())((unsigned long*)o)[0x14])() == 0) return (void*)0x130c2;
        flags = *(unsigned*)((char*)ctx + 0x17c);
    }
    if ((*(unsigned char*)(o + 0x4e) & 1) != 0 && (flags >> 4 & 1) != 0) {
        if ((*(unsigned long(*)())((unsigned long*)o)[0x15])() == 0) return (void*)0x230c2;
        flags = *(unsigned*)((char*)ctx + 0x17c);
    }
    bool dev = true;
    if ((flags >> 3 & 1) != 0) {
        if ((*(unsigned char*)(o + 0x4c) & 1) == 0 ||
            ((unsigned long*)((unsigned long*)o)[0x16] != 0 &&
             ((*(unsigned long(*)())((unsigned long*)o)[0x16])() & 1) != 0))
            dev = false;
        else dev = true;
        flags = *(unsigned*)((char*)ctx + 0x17c);
        if ((flags >> 5 & 1) == 0) {
            if (!dev) return (void*)0x330c2;
        } else if (!dev && (*(unsigned char*)((char*)(unsigned long*)o + 0xd3) & 1) == 0)
            return (void*)0x330c2;
    }
    if ((flags >> 7 & 1) == 0) {
        if ((flags >> 6 & 1) == 0 || (*(unsigned char*)((char*)(unsigned long*)o + 0xd3) & 1) != 0)
            return (void*)0xc2;
        return (void*)0x530c2;
    }
    return (void*)0x430c2;
}

/* FUN_000345f4 @ 0x345f4  (est. txm_trust_eval)
 * Ghidra: uint FUN_000345f4(undefined8*, undefined1*)
 * The core trust evaluation for a code-signing context. Parses the platform
 * command (0xfade0b01) + CMS (0xfade0c02), verifies the AMFI CMS signature,
 * and applies the trust-class decision (apple/developer/adhoc/etc) into
 * param_2. Returns the trust status word.
 * Confidence: high (this is the trust decision — CDHash verification gate) */
unsigned txm_trust_eval(unsigned long *ctx, unsigned char *result) {
    unsigned long canary = DAT_00006cf0;
    unsigned long *o = (unsigned long*)*ctx;
    unsigned char plat = 0, ht = 0;
    unsigned long r = 0, class_ = 0x10000, err = 0x2491;
    unsigned long cms[2], cmd[2];
    unsigned long flags = 0, aflags = 0, digest = 0;
    unsigned char trust = 0;
    if ((unsigned long)o + 0x1b * 8 <= (unsigned long)o) txm_assert(0x19);
    unsigned long pf = *(unsigned char*)(*o + 0x4a);
    if ((void**)o[0x16] != 0) pf = ((*(unsigned long(*)())(void**)o[0x16])() ^ 1) & pf;
    txm_codedir_get_platform(ctx[6], ctx[7], &plat, 0);
    unsigned long slot[2];
    txm_superblob_find_command((unsigned*)ctx[3], ctx[4], 0x10000, 0xfade0b01, 0);
    txm_superblob_get_cmd((unsigned*)slot[0], (unsigned)slot[1], 0, &cms[0]);
    r = txm_amfi_cms_parse(ctx + 1, *(unsigned char*)((char*)o + 0xd3) & 1, cms[0], cms[1]);
    if ((r & 0xff00) != 0) { err = r >> 8; class_ = r & 0xffff0000; goto out; }
    unsigned long l2;
    txm_superblob_find_command((unsigned*)ctx[3], ctx[4], 0, 0xfade0c02, 0);
    if (l2 == 0) { err = 0x224; class_ = 0x20000; goto out; }
    r = txm_amfi_cms_verify(ctx + 1, l2);
    if ((r & 0xff00) != 0) { err = r >> 8; class_ = r & 0xffff0000; goto out; }
    if (0x30 < ctx[0xe]) txm_assert(0x19);
    r = txm_amfi_verify_signature((unsigned long)(ctx + 1), (unsigned long)(ctx + 8),
                                  ctx[0xe], plat);
    if (r >> 8 & 0xff) {
        if ((r >> 8 & 0xff) != 0x24) { err = r >> 8; class_ = r & 0xffff0000; goto out; }
        if (ctx[6] != l2) { err = 0x329; class_ = 0x30000; goto out; }
    }
    txm_amfi_get_flags((unsigned long)(ctx + 1), &flags);
    unsigned long ov = *o;
    unsigned long m0 = *(unsigned long*)(ov + 8), m1 = *(unsigned long*)(ov + 0x10);
    unsigned long m2 = *(unsigned long*)(ov + 0x18);
    if ((*(unsigned char*)((char*)o + 0xd3) & 1) != 0) {
        m0 |= *(unsigned long*)(ov + 0x30);
        m1 |= *(unsigned long*)(ov + 0x20);
        m2 |= *(unsigned long*)(ov + 0x28);
    }
    if ((flags & m0) == 0) {
        if ((flags & m1) != 0) { trust = 5; goto set; }
        if ((flags & m2) == 0) {
            if ((pf & 1) != 0) {
                unsigned long h[2];
                txm_handoff_block((void**)o[0xe], h);
                unsigned long len = h[1];
                if (h[0] + len < h[0]) txm_assert(0x19);
                if ((txm_amfi_cert_chain_verify((unsigned long)(ctx + 1), h[0], len) & 0xff00) == 0) {
                    trust = 3; goto set;
                }
            }
            if ((*(unsigned char*)((char*)o + 0xd1) & 1) == 0 ||
                (*(unsigned char*)((char*)o + 0xd4) & 1) != 0) {
                err = 0x422; class_ = 0x40000; goto out;
            }
            trust = ((*(unsigned char*)((char*)ctx + 0x2a) & 1) == 0) ? 10 : 5;
            goto set;
        }
        *result = 4;
        txm_amfi_get_digest2((unsigned long)(ctx + 1), ctx + 0x22);
    } else {
        trust = 6;
    }
set:
    *result = trust;
    err = 0; class_ = 0;
out:
    if (DAT_00006cf0 == canary) return (unsigned)(class_ | (err & 0xff) << 8 | 0x91 & 0xff);
    txm_stack_check_fail();
    return 0;
}

/* FUN_000348f8 @ 0x348f8  (est. txm_trust_platform_check)
 * Ghidra: undefined* FUN_000348f8(long*, undefined1*)
 * Checks the platform trust class (0x2) for the profile. 0x94 on success.
 * Confidence: low */
void *txm_trust_platform_check(unsigned long *ctx, unsigned char *out) {
    unsigned char plat = 0;
    if ((*(unsigned char*)(*(unsigned long*)*ctx + 0x49) & 1) == 0) return (void*)0x12894;
    void **o = (void**)*ctx;
    if (o[0x16] != 0 && ((*(unsigned long(*)())(void**)o[0x16])() & 1) != 0)
        return (void*)0x23094;
    void *rc = txm_codedir_get_hash_flags(ctx[6], ctx[7], &plat, 0);
    if ((unsigned long)rc & 0xff00) return rc;
    if (plat == '\x02') { *out = 2; return (void*)0x94; }
    return (void*)0x32994;
}

/* FUN_0003499c @ 0x3499c  (est. txm_trust_adhoc_check)
 * Ghidra: undefined* FUN_0003499c(long*, undefined1*)
 * Checks the adhoc trust class (1) via the owner's callback. 0x93.
 * Confidence: low */
void *txm_trust_adhoc_check(unsigned long *ctx, unsigned char *out) {
    unsigned long *o = (unsigned long*)*ctx;
    if ((*(unsigned char*)(*o + 0x4b) & 1) == 0) return (void*)0x12893;
    if ((void**)o[0x16] != 0) {
        if (((*(unsigned long(*)())(void**)o[0x16])() & 1) != 0) return (void*)0x23093;
        o = (unsigned long*)*ctx;
    }
    if ((*(unsigned long(*)(void*))((unsigned long*)o)[0x11])(ctx + 8) == 0)
        return (void*)0x32993;
    *out = 1;
    return (void*)0x93;
}

/* FUN_00034a2c @ 0x34a2c  (est. txm_trust_developer_check)
 * Ghidra: undefined* FUN_00034a2c(long*, undefined1*)
 * Checks the developer trust class via the owner's cert chains. 0x90.
 * Confidence: low */
void *txm_trust_developer_check(unsigned long *ctx, unsigned char *out) {
    unsigned long o = *ctx;
    unsigned long d[2], flags = 0;
    txm_bzero(d, sizeof d);
    if (*(unsigned long*)(o + 0x20) == 0 && *(unsigned long*)(o + 0x18) == 0)
        return (void*)0x12890;
    unsigned char use = *(unsigned char*)(o + 0x30);
    unsigned long *slot = (use & 1) ? d : 0;
    void **tbl = (void**)&DAT_00006e39;
    for (int i = 0; i < 3; i++) {
        void *fn = *(void**)(o + 0x20);
        if (fn == 0) fn = *(void**)(o + 0x18);
        unsigned long r = ((unsigned long(*)(unsigned long, void*, unsigned long*))fn)
                          ((unsigned long)tbl[i*2 - 1], ctx + 8, slot);
        if ((r & 0xff00) == 0) {
            if ((use & 1) == 0) { *out = (unsigned char)tbl[i*2]; return (void*)0x90; }
            txm_cert_get_base_flag(slot, &flags);
            if ((flags >> 1 & 1) != 0) { *out = (unsigned char)tbl[i*2]; return (void*)0x90; }
        }
        tbl += 2;
    }
    return (void*)0x22990;
}

/* FUN_00034b18 @ 0x34b18  (est. txm_ctx_get_ent)
 * Ghidra: long FUN_00034b18(long)
 * Returns ctx+0x78 if the entitlements flag (ctx+0x100) is set else 0.
 * Confidence: low */
unsigned long txm_ctx_get_ent(unsigned long ctx) {
    unsigned long e = ctx + 0x78;
    if ((*(unsigned char*)(ctx + 0x100) & 1) == 0) e = 0;
    return e;
}

/* FUN_00034b30 @ 0x34b30  (est. txm_ctx_find_embedded)
 * Ghidra: void FUN_00034b30(long)
 * Finds the embedded-signature command (0xfade7172) in the ctx's superblob.
 * Confidence: low */
void txm_ctx_find_embedded(unsigned long ctx) {
    txm_superblob_find_command(*(unsigned**)ctx, *(unsigned long*)(ctx + 0x18),
                               7, 0xfade7172, 0);
}

/* FUN_00034b50 @ 0x34b50  (est. txm_ctx_parse_embedded)
 * Ghidra: undefined* FUN_00034b50(long*)
 * Parses the embedded signature of a context into the AMFI CMS context.
 * 0x63 on success.
 * Confidence: low */
void *txm_ctx_parse_embedded(unsigned long *ctx) {
    unsigned long o = *ctx;
    unsigned long cmd[2], data[2];
    txm_bzero(data, sizeof data);
    *(unsigned char*)(ctx + 0x20) = 0;
    txm_superblob_find_command((unsigned*)ctx[3], ctx[4], 7, 0xfade7172, 0);
    if (cmd[0] == 0) return (void*)0x11163;
    void *rc = (void*)(unsigned long)txm_codedir_hash(ctx[6], ctx[7], 7, cmd[0], cmd[1]);
    if ((unsigned long)rc & 0xff00) return rc;
    txm_superblob_get_cmd((unsigned*)cmd[0], (unsigned)cmd[1], 0, &data[0]);
    rc = (void*)(unsigned long)txm_cectx_init(*(unsigned long*)(o + 0x10), 0, ctx + 0xf,
                                              data[0], data[1]);
    if ((unsigned long)rc & 0xff00) return rc;
    *(unsigned char*)(ctx + 0x20) = 1;
    return (void*)0x63;
}

/* FUN_00034c2c @ 0x34c2c  (est. txm_cap_apply)
 * Ghidra: void FUN_00034c2c(uint*, uint*)
 * ORs the capability bits of param_2 into the flags at param_1 (8 bits).
 * Confidence: high */
void txm_cap_apply(unsigned *flags, unsigned *cap) {
    unsigned v = *cap;
    if (v & 1) *flags |= 1, v = *cap;
    if (v >> 1 & 1) *flags |= 2, v = *cap;
    if (v >> 2 & 1) *flags |= 4, v = *cap;
    if (v >> 3 & 1) *flags |= 8, v = *cap;
    if (v >> 4 & 1) *flags |= 0x10, v = *cap;
    if (v >> 5 & 1) *flags |= 0x20, v = *cap;
    if (v >> 6 & 1) *flags |= 0x40, v = *cap;
    if (v >> 7 & 1) *flags |= 0x80;
}

/* FUN_00034cf4 @ 0x34cf4  (est. txm_apple_internal_profile)
 * Ghidra: bool FUN_00034cf4(long)
 * True if the "AppleInternalProfile" entitlement is present and set.
 * Confidence: low */
bool txm_apple_internal_profile(unsigned long ctx) {
    unsigned long h[5];
    txm_bzero(h, sizeof h);
    if (txm_dict_init(ctx + 0x68, "AppleInternalProfile", h) == 0)
        return txm_dict_value(h, 1) == 0;
    return false;
}

/* FUN_00034d50 @ 0x34d50  (est. txm_ctx_get_provisions)
 * Ghidra: long FUN_00034d50(long)
 * Returns ctx+0xf0 if the provisions flag (ctx+0x178) is set else 0.
 * Confidence: low */
unsigned long txm_ctx_get_provisions(unsigned long ctx) {
    unsigned long p = ctx + 0xf0;
    if ((*(unsigned char*)(ctx + 0x178) & 1) == 0) p = 0;
    return p;
}

/* FUN_00034d68 @ 0x34d68  (est. txm_provisions_all_devices)
 * Ghidra: bool FUN_00034d68(long)
 * True if the "ProvisionsAllDevices" entitlement is set.
 * Confidence: low */
bool txm_provisions_all_devices(unsigned long ctx) {
    unsigned long h[5];
    txm_bzero(h, sizeof h);
    if (txm_dict_init(ctx + 0x68, "ProvisionsAllDevices", h) == 0)
        return txm_dict_value(h, 1) == 0;
    return false;
}

/* FUN_00034dc4 @ 0x34dc4  (est. txm_entitlements_set)
 * Ghidra: uint FUN_00034dc4(long)
 * Computes the CEContext's entitlement capability flags: beta (ProvisionsAll-
 * Devices + beta_reports_active), apple-internal, and the per-capability bits.
 * Returns 0xc1.
 * Confidence: medium */
unsigned txm_entitlements_set(unsigned long ctx) {
    unsigned flags, r, class_ = 0xc1;
    flags = *(unsigned*)(ctx + 0x17c) & ~4U;
    if (txm_provisions_all_devices(ctx) != 0) flags |= 4;
    *(unsigned*)(ctx + 0x17c) = flags;
    if ((*(unsigned char*)(ctx + 0x178) & 1) != 0) {
        r = txm_cectx_value(ctx + 0xf0, "beta_reports_active", 1);
        flags = (r & 0xff00) != 0 ? 0 : 2;
    } else flags = 0;
    unsigned v = *(unsigned*)(ctx + 0x17c) & ~3U | flags;
    if ((*(unsigned*)(ctx + 0x17c) & 4) == 0 && flags == 0) v += 1;
    *(unsigned*)(ctx + 0x17c) = v;
    flags = txm_apple_internal_profile(ctx) ? 8 : 0;
    *(unsigned*)(ctx + 0x17c) = *(unsigned*)(ctx + 0x17c) & ~8U | flags;
    txm_cectx_clear_caps(ctx);
    r = txm_apple_internal_check(ctx);
    return (r & 0xff00) != 0 ? r : 0xc1;
}

/* FUN_00034e90 @ 0x34e90  (est. txm_profile_entitlements)
 * Ghidra: ulong FUN_00034e90(long*)
 * Parses the "Entitlements" dict of a context and initializes the
 * CEContext entitlements (31280). Sets the +0x2f flag. 0xc0 on success.
 * Confidence: low */
unsigned long txm_profile_entitlements(unsigned long *ctx) {
    unsigned long o = *ctx;
    unsigned long h[5], data[2];
    txm_bzero(h, sizeof h); txm_bzero(data, sizeof data);
    *(unsigned char*)(ctx + 0x2f) = 0;
    if (txm_dict_init(ctx + 0xd, "Entitlements", h) == 0) {
        txm_dict_data(h, data);
        unsigned long r = txm_cectx_init(*(unsigned long*)(o + 0x10), 1, ctx + 0x1e,
                                         data[0], data[1]);
        if ((r & 0xff00) != 0) return r;
        *(unsigned char*)(ctx + 0x2f) = 1;
    }
    return 0xc0;
}

/* FUN_00034f24 @ 0x34f24  (est. txm_team_identifier)
 * Ghidra: undefined4 FUN_00034f24(long, undefined8*)
 * Reads the "TeamIdentifier" entitlement (60088 -> 5f360 -> 5f7ec) into
 * param_2. 0x2a on success.
 * Confidence: low */
unsigned txm_team_identifier(unsigned long ctx, unsigned long *out) {
    unsigned long h[5], v[2];
    txm_bzero(h, sizeof h); txm_bzero(v, sizeof v);
    if ((*(unsigned char*)(ctx + 0x180) & 1) == 0) return 0x2082a;
    if (txm_dict_init(ctx + 0x68, "TeamIdentifier", h)) return 0x3242a;
    if (txm_dict_str(h, 0, &v[0])) return (txm_dict_str_err() != 10) ? 0x5242a : 0x4262a;
    if (txm_dict_data2(h, &v[0])) return 0x6262a;
    if (out) { out[0] = v[0]; out[1] = v[1]; }
    return 0x2a;
}

/* FUN_00034ff8 @ 0x34ff8  (est. txm_app_audience)
 * Ghidra: undefined4 FUN_00034ff8(long, long)
 * Validates the "AppAudience" entitlement (60088 -> 5f4b4 -> 5fa9c). 0xc6.
 * Confidence: low */
unsigned txm_app_audience(unsigned long ctx, unsigned long arg) {
    unsigned long h[5]; int r; unsigned tag;
    txm_bzero(h, sizeof h);
    if ((*(unsigned char*)(ctx + 0x180) & 1) == 0) return 0x108c6;
    if (arg == 0) return 0x22cc6;
    if (txm_dict_init(ctx + 0x68, "AppAudience", h)) return 0x324c6;
    if (txm_dict_int(h, &tag)) return 0x426c6;
    if (tag == 2) {
        if (txm_dict_flags(h, arg)) return 0x529c6;
        return 0xc6;
    }
    return 0x426c6;
}
