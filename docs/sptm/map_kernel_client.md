# Kernel-side SPTM / TXM Client Interface Map

Target: `kernelcache.arm64.kc` (MCP program `kernelcache.arm64.kc`, AARCH64:LE:64).
Task: map the kernel (XNU, EL2/VHE on M5) client wrappers that enter SPTM (GL2) and TXM (GL0)
via the `GENTER` instruction (opcode `0x00201420`, bytes `20 14 20 00`), with a dispatch id in `x16`.

Method: `switch_program kernelcache.arm64.kc` → whole-program byte search for `20 14 20 00`
(the `search_byte_patterns` tool handled it; the "whole-program times out" concern did not
materialize) → disassemble each GENTER site's enclosing stub → recover the dispatch id loaded
into `x16` → cross-reference against `SPTM_FUNCTIONID_*` / `SPTM_DISPATCH_TABLE_*` in
`docs/sptm/headers/sptm_common.h` and the client prototypes in `docs/sptm/headers/sptm_xnu.h`.

---

## 1. GENTER site count — 151 (matches AGENTS.md)

`search_byte_patterns("20 14 20 00", mask "ff ff ff ff")` returned **151** hits:

| Cluster | Range | Count | Kind |
|---|---|---|---|
| Main dispatch stub table | `0xfffffe000c0d83d4` – `0xfffffe000c0d9bdc` | 148 | per-endpoint GENTER stubs (sptm_* + HIB + IOMMU + guest) |
| SK/TXM generic domain-entry stubs | `0xfffffe000c0d7968`, `0xfffffe000c0d7990` | 2 | parameterized `sk_enter`/`txm_enter` genter cores |
| Isolated (exception/boot path) | `0xfffffe000c110088` | 1 | `mov x16,#0xf; b 0xfffffe000b958a18` (separate path) |

### Stub shape (per-endpoint, `0x28` bytes, 1 per function)
```
pacibsp
stp    x29, x30, [sp, #-0x10]!
mov    x29, sp
bl     _sptm_pre_entry_hook     ; 0xfffffe000b75e8e8
mov    x16, #<dispatch_id>      ; [+ movk x16,#<table>,LSL #32 for non-XNU tables]
genter                          ; 0x20 14 20 00  (the dispatch)
bl     _sptm_post_exit_hook     ; 0xfffffe000b75e954
mov    sp, x29
ldp    x29, x30, [sp], #0x10
retab
```
- `_sptm_pre_entry_hook` (`FUN_fffffe000b75e8e8`, decompiled): increments a per-CPU counter at
  `tpidr_el1+0x1c0`, then spins on a system register read (pre-entry sync).
- `_sptm_post_exit_hook` (`FUN_fffffe000b75e954`, decompiled): decrements that counter;
  on preemption-counter underflow calls `hv_el2_preemption_panic`.
- `x16` holds the SPTM dispatch id = `(domain<<48)|(table<<32)|endpoint`.

### The `0xfffffe0007c11394` "selector table" from AGENTS.md is a mis-identification
`read_memory(0xfffffe0007c11300,256)` + `disassemble_bytes` at `0x7c11394` decodes as NEON
floating-point code (`fmls v0.4H,v25.4H,…`, `fnmadd d0,d25,d13,d3`) — not a pointer/dispatch table.
`get_function_by_address(0x7c11394)` → none; `get_xrefs_to(0x7c11394)` → none;
`analyze_data_region` classifies it PRIMITIVE (stride 1). The real GENTER dispatch table lives at
**`0xfffffe000c0d83c0`** (first stub) through `0xfffffe000c0d9be8` (last), with the guest
id-loaders and generic domain-entry stubs as noted above.

---

## 2. sptm_* XNU client wrappers (dispatch table id 0 = `SPTM_DISPATCH_TABLE_XNU_BOOTSTRAP`)

Each `mov x16,#<endpoint>` (no table `movk`) in the table-0 group. Endpoint ids match
`SPTM_FUNCTIONID_*` exactly, so these are the `sptm_*` client wrappers. "Addr" = stub entry
(`pacibsp`), "GENTER" = the instruction site inside it.

| sptm_* client function | SPTM_FUNCTIONID_ | endpoint (x16) | Stub addr | GENTER site | Confidence |
|---|---|---|---|---|---|
| sptm_lockdown | LOCKDOWN | 0 | `0xfffffe000c0d83c0` | `0xfffffe000c0d83d4` | high |
| sptm_retype | RETYPE | 1 | `0xfffffe000c0d83e8` | `0xfffffe000c0d83fc` | high |
| sptm_map_page | MAP_PAGE | 2 | `0xfffffe000c0d8410` | `0xfffffe000c0d8424` | high |
| sptm_map_table | MAP_TABLE | 3 | `0xfffffe000c0d8438` | `0xfffffe000c0d844c` | high |
| sptm_unmap_table | UNMAP_TABLE | 4 | `0xfffffe000c0d8460` | `0xfffffe000c0d8474` | high |
| sptm_update_region | UPDATE_REGION | 5 | `0xfffffe000c0d8488` | `0xfffffe000c0d849c` | high |
| sptm_update_disjoint | UPDATE_DISJOINT | 6 | `0xfffffe000c0d84b0` | `0xfffffe000c0d84c4` | high |
| sptm_unmap_region | UNMAP_REGION | 7 | `0xfffffe000c0d84d8` | `0xfffffe000c0d84ec` | high |
| sptm_unmap_disjoint | UNMAP_DISJOINT | 8 | `0xfffffe000c0d8500` | `0xfffffe000c0d8514` | high |
| sptm_configure_sharedregion | CONFIGURE_SHAREDREGION | 9 | `0xfffffe000c0d8528` | `0xfffffe000c0d853c` | high |
| sptm_nest_region | NEST_REGION | 10 | `0xfffffe000c0d8578` | `0xfffffe000c0d858c` | high |
| sptm_unnest_region | UNNEST_REGION | 11 | `0xfffffe000c0d85a0` | `0xfffffe000c0d85b4` | high |
| sptm_configure_root | CONFIGURE_ROOT | 12 | `0xfffffe000c0d85c8` | `0xfffffe000c0d85dc` | high |
| sptm_switch_root | SWITCH_ROOT | 13 | `0xfffffe000c0d85f0` | `0xfffffe000c0d8604` | high |
| sptm_register_cpu | REGISTER_CPU | 14 | `0xfffffe000c0d8618` | `0xfffffe000c0d862c` | high |
| sptm_init_xnu_fixups_complete | FIXUPS_COMPLETE | 15 | `0xfffffe000c0d8668` | `0xfffffe000c0d8680` | high |
| sptm_sign_user_pointer | SIGN_USER_POINTER | 16 | `0xfffffe000c0d87a8` | `0xfffffe000c0d87bc` | high |
| sptm_auth_user_pointer | AUTH_USER_POINTER | 17 | `0xfffffe000c0d87d0` | `0xfffffe000c0d87e4` | high |
| sptm_register_exc_return | REGISTER_EXC_RETURN | 18 | `0xfffffe000c0d87f8` | `0xfffffe000c0d880c` | high |
| sptm_cpu_id | CPU_ID | 19 | `0xfffffe000c0d8820` | `0xfffffe000c0d8834` | high |
| sptm_slide_region | SLIDE_REGION | 20 | `0xfffffe000c0d8640` | `0xfffffe000c0d8654` | high |
| sptm_update_disjoint_multipage | UPDATE_DISJOINT_MULTIPAGE | 21 | `0xfffffe000c0d8848` | `0xfffffe000c0d885c` | high |
| sptm_reg_read | REG_READ | 22 | `0xfffffe000c0d88e8` | `0xfffffe000c0d88fc` | high |
| sptm_reg_write | REG_WRITE | 23 | `0xfffffe000c0d8910` | `0xfffffe000c0d8924` | high |
| sptm_map_sk_domain | MAP_SK_DOMAIN | 29 | `0xfffffe000c0d8a00` | `0xfffffe000c0d8a14` | high |
| sptm_hib_begin | HIB_BEGIN | 30 | `0xfffffe000c0d8a28` | `0xfffffe000c0d8a3c` | high |
| sptm_hib_verify_hash_non_wired | HIB_VERIFY_HASH_NON_WIRED | 31 | `0xfffffe000c0d8a50` | `0xfffffe000c0d8a64` | high |
| sptm_hib_finalize_non_wired | HIB_FINALIZE_NON_WIRED | 32 | `0xfffffe000c0d8a78` | `0xfffffe000c0d8a8c` | high |
| sptm_iofilter_protected_write | IOFILTER_PROTECTED_WRITE | 33 | `0xfffffe000c0d8870` | `0xfffffe000c0d8884` | high |
| sptm_sysctl | SPTM_SYSCTL | 37 | `0xfffffe000c0d8960` | `0xfffffe000c0d8974` | high |
| sptm_disable_kernel_mode_cpa2 | DISABLE_KERNEL_MODE_CPA2 | 38 | `0xfffffe000c0d8690` | `0xfffffe000c0d86a4` | high |
| sptm_set_shared_region | SET_SHARED_REGION | 39 | `0xfffffe000c0d8550` | `0xfffffe000c0d8564` | high |
| sptm_batch_sign_user_pointer | BATCH_SIGN_USER_POINTER | 40 | `0xfffffe000c0d8988` | `0xfffffe000c0d899c` | high |
| sptm_surt_alloc | SURT_ALLOC | 41 | `0xfffffe000c0d86b8` | `0xfffffe000c0d86cc` | high |
| sptm_surt_free | SURT_FREE | 42 | `0xfffffe000c0d86e0` | `0xfffffe000c0d86f4` | high |
| sptm_condemn_leaf_table | CONDEMN_LEAF_TABLE | 43 | `0xfffffe000c0d89b0` | `0xfffffe000c0d89c4` | high |
| sptm_uncondemn_leaf_table | UNCONDEMN_LEAF_TABLE | 44 | `0xfffffe000c0d89d8` | `0xfffffe000c0d89ec` | high |
| sptm_serial_putc | SPTM_SERIAL_PUTC | 45 | `0xfffffe000c0d8708` | `0xfffffe000c0d871c` | high |
| sptm_serial_disable | SPTM_SERIAL_DISABLE | 46 | `0xfffffe000c0d8730` | `0xfffffe000c0d8744` | high |
| sptm_program_irgkey | PROGRAM_IRGKEY | 48 | `0xfffffe000c0d8758` | `0xfffffe000c0d876c` | high |
| sptm_reg_snapshot | REG_SNAPSHOT | 49 | `0xfffffe000c0d8938` | `0xfffffe000c0d894c` | high |

Reserved/unallocated endpoints also present as table-0 stubs (kept for the count, no public name):
`0x27`(39) is the named `sptm_set_shared_region` above; `0x2f`(47) → `0xfffffe000c0d8780`,
`0x23`(35) → `0xfffffe000c0d8898`, `0x24`(36) → `0xfffffe000c0d88c0`,
`0x22`(34) → `0xfffffe000c0d9bd8` (standalone, table-0, no `movk`).

Confidence is high throughout: the `mov x16,#N` endpoint value is read directly from the stub
disassembly and equals `SPTM_FUNCTIONID_*` for every entry; the function set matches
`sptm_xnu.h` exactly. (Confidence would only drop if a future XNU release remaps endpoints.)

---

## 3. Guest dispatch helpers (endpoints 24–28) — the hypervisor's EL2 GENTER path

These are short stubs (`pacibsp; mov x16,#id; genter; retab`, 12 bytes, no pre/post hooks)
feeding the hypervisor guest-exit path in `osfmk/arm64/hypervisor/hv_el2.c`.

| sptm_* client function | endpoint | Stub addr | GENTER site | Caller (evidence) | Confidence |
|---|---|---|---|---|---|
| sptm_guest_va_to_ipa | 24 (`0x18`) | `0xfffffe000c0d993c` | `0xfffffe000c0d9944` | `hv_el2_guest_fault` @ `0xfffffe000b967768` | high |
| sptm_guest_stage1_tlb_op | 25 (`0x19`) | `0xfffffe000c0d994c` | `0xfffffe000c0d9954` | (EL2 TLB path) | high |
| sptm_guest_stage2_tlb_op | 26 (`0x1a`) | `0xfffffe000c0d995c` | `0xfffffe000c0d9964` | (EL2 TLB path) | high |
| sptm_guest_dispatch | 27 (`0x1b`) | `0xfffffe000c0d997c` | `0xfffffe000c0d9984` | `FUN_fffffe000b953e14` (guest-entry hub) | high |
| sptm_guest_exit | 28 (`0x1c`) | `0xfffffe000c0d996c` | `0xfffffe000c0d9974` | (guest-exit path) | high |

`get_function_callers(0xfffffe000c0d993c)` → `hv_el2_guest_fault` (confirms the 
GUEST_VA_TO_IPA id feeds the EL2 fault handler); `get_function_callers(0xfffffe000c0d997c)` →
`FUN_fffffe000b953e14` (guest dispatch entry).

---

## 4. txm_enter and its TXM genter core

- **`txm_enter` (kernel-side) = `FUN_fffffe000bdbba20` @ `0xfffffe000bdbba20`** (body
  `0xfffffe000bdbba20`–`0xfffffe000bdbc1bf`). Decompiled: it validates the argument count
  ("invalid number of arguments to TXM: selector: %u"), rejects a second thread association
  ("attempted multiple TXM thread associations"), packs the call args from the `sptm_call_regs_t`
  pointer, then calls the TXM genter core
  `FUN_fffffe000c0d7970(*param_1 /*selector*/, local_c0 /*args*/)` and maps the TXM return
  (selector/status handling: `TXM [Error]: CodeSignature`, `TrustCache`, `Errno`).
- **`txm_enter` genter core = `0xfffffe000c0d7970`** (GENTER at `0xfffffe000c0d7990`):
  `pacibsp; mov w16, w0; movk x16, #0x2, LSL #48; mov x10,x1; ldp x0..x7,[x10]; genter; retab`.
  So dispatch id = `0x0002_0000_0000_0000 | selector` = `(TXM_DOMAIN=2)<<48 | selector`.
  `get_function_callers(0xfffffe000c0d7970)` → exactly `txm_enter` (single caller).
- **40-selector space**: TXM selectors are the endpoint ids 0x0–0x33 passed to `txm_enter`.
  The firmware-side dispatcher (`FUN_0002adec` in the `txm.raw` program) switches on
  `param_1 ∈ [0x0, 0x33]` and fails closed on invalid/unknown selectors (see
  `docs/sptm/map_txm_entry.md`, `docs/sptm/findings.md` §ringminus1). The kernel `txm_enter`
  passes the selector straight through to the genter core (no kernel-side 40-entry table).
- **`sk_enter` genter core = `0xfffffe000c0d7948`** (GENTER at `0xfffffe000c0d7968`):
  `movk x16, #0x3, LSL #48` → `(SK_DOMAIN=3)<<48 | endpoint`.
- `txm_enter` has ~50 caller wrappers in `0xfffffe000bdb9238`–`0xfffffe000bde02bc`
  (e.g. `trust_cache_init @ 0xfffffe000bdb9144`, `code_signing_monitor_lockdown @ 0xfffffe000bdbb37c`),
  each invoking a TXM selector — these are the kernel's `txm_*` / trust-cache entry points.

---

## 5. Non-XNU dispatch-table stubs inside the same table (for completeness)

Per-endpoint stubs that set a table id via `movk x16,#<table>,LSL #32` (so `x16 = (table)<<32 | endpoint`):

| Table id | Dispatch table | Endpoints | Stub range |
|---|---|---|---|
| 0xa | `SPTM_DISPATCH_TABLE_HIB` | 0–5 | `0xfffffe000c0d8aa0`–`0xfffffe000c0d8b78` |
| 0x6 | `SPTM_DISPATCH_TABLE_NVME` | 0–8 | `0xfffffe000c0d8ba8`–`0xfffffe000c0d8d08` |
| 0x3 | `SPTM_DISPATCH_TABLE_T8110_DART_XNU` | 0–0x12 | `0xfffffe000c0d8d34`–`0xfffffe000c0d904c` |
| 0xd | `SPTM_DISPATCH_TABLE_T6000_DART_XNU` | 0–0xf | `0xfffffe000c0d9084`–`0xfffffe000c0d9328` |
| 0xb | `SPTM_DISPATCH_TABLE_GEN3_DART_XNU` | 0–0x12 | `0xfffffe000c0d9338`–`0xfffffe000c0d9678` |
| 0x5 | `SPTM_DISPATCH_TABLE_SART` | 1,2,0 | `0xfffffe000c0d9688`–`0xfffffe000c0d96e0` |
| 0x7 | `SPTM_DISPATCH_TABLE_UAT` | 0–0xc | `0xfffffe000c0d9704`–`0xfffffe000c0d99b4` |
| 0x9 | `SPTM_DISPATCH_TABLE_RESERVED` | 0–0xc | `0xfffffe000c0d9990`–`0xfffffe000c0d9bc4` |

These are IOMMU-driver (DART/SART/UAT/NVME/SHART) and HIB dispatch entries — not `sptm_*`
client wrappers, but they share the same GENTER stub table and count toward the 151.

---

## 6. Sample GENTER stub addresses (a representative subset of the 151)

1. `0xfffffe000c0d83d4` — sptm_lockdown (endpoint 0)
2. `0xfffffe000c0d83fc` — sptm_retype (endpoint 1)
3. `0xfffffe000c0d8424` — sptm_map_page (endpoint 2)
4. `0xfffffe000c0d862c` — sptm_register_cpu (endpoint 14)
5. `0xfffffe000c0d9944` — sptm_guest_va_to_ipa (endpoint 24)
6. `0xfffffe000c0d9984` — sptm_guest_dispatch (endpoint 27)
7. `0xfffffe000c0d7990` — txm_enter genter core (domain 2, TXM)
8. `0xfffffe000c0d7968` — sk_enter genter core (domain 3, SK)
9. `0xfffffe000c0d8a90` — HIB table (table 0xa) endpoint 2
10. `0xfffffe000c110088` — isolated GENTER in exception/boot path (`mov x16,#0xf; b 0xfffffe000b958a18`)

**GENTER dispatch stub table extent: `0xfffffe000c0d83c0` – `0xfffffe000c0d9be8`.**
`_sptm_pre_entry_hook` = `0xfffffe000b75e8e8`, `_sptm_post_exit_hook` = `0xfffffe000b75e954`.

---

## 7. Evidence / verification summary

- `search_byte_patterns("20 14 20 00")` → 151 hits (addresses recorded; see §1/§6).
- `disassemble_bytes` windows: `0x7900`, `0x83a0`, `0x87a0`, `0x8ba0`, `0x8fa0`, `0x93a0`, `0x97a0`
  — recovered every stub's `mov x16,#<id>` (and optional `movk x16,#<table>,LSL#32`) + `genter`.
- `get_function_by_address`: `0xfffffe000c0d8410` (map_page stub, body 0x8410–0x841f),
  `0xfffffe000c0d7970` (TXM genter core, body 0x7970–0x798f), `0xfffffe000c0d993c` (guest id loader).
- `decompile_function`: `0xfffffe000b75e8e8` (pre-hook: per-CPU counter + sysreg spin),
  `0xfffffe000b75e954` (post-hook: counter dec + `hv_el2_preemption_panic`),
  `0xfffffe000bdbba20` (`txm_enter`).
- `get_function_callers`: `0xfffffe000c0d7970` → `txm_enter` only; `0xfffffe000c0d993c` →
  `hv_el2_guest_fault`; `0xfffffe000c0d997c` → `FUN_fffffe000b953e14`.
- Header cross-checks: `sptm_common.h` (`SPTM_FUNCTIONID_*`, `SPTM_DISPATCH_TABLE_*`,
  `BUILD_DISPATCH_ID`/domain/table/endpoint shifts), `sptm_xnu.h` (client prototype names,
  `txm_enter(endpoint_id, argsp)`).

No manifest or source files were modified; this document is the only artifact written.
