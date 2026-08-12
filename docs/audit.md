# Hypervisor Security Audit — `docs/audit.md`

Synthesis of the decompiled hypervisor recreation in this tree. Ground truth
is the Ghidra `FUN_` name + address from `kernelcache.arm64.kc`
(xnu-12377.121.10 RELEASE_ARM64_T8142, image base `fffffe0007004000`); all
human names are estimates (see `AGENTS.md`). Addresses throughout let you
cross-check any claim in Ghidra. This document consolidates the security
observations logged incrementally in `docs/findings.md` and the structural
map in `docs/chain-map.md`.

Register names are ESTIMATES — the kernelcache is stripped, so the EL2 state
block offsets were identified from the 64-bit constants written to them, not
from the sysreg encoding. Treat every register identity as unverified.

---

## 1. Architecture overview

The hypervisor is a Type-2 (paravirtualized) EL2 hypervisor for
Apple-silicon (T8142). The kernel boots at EL1, brings up EL2 support
during boot, and exposes a Hypervisor.framework-style operation table to
userland through mach traps. A guest runs as a vCPU bound to a physical CPU;
guest exits are handled by a small fixed EL2 vector table that saves guest
state, re-enters the EL1 kernel, and dispatches to C-level handlers. The
guest's memory is backed by a per-VM **host vm_map** plus a small fixed
**stage-2 EL2 translation table**; guest faults funnel into the kernel
`vm_fault` family.

### 1.1 EL2 vs EL1 boundary

```
EL0 (guest userland) ── EL1 (guest kernel) ── EL2 (hypervisor, this code)
   guest vCPU run via hv_vcpu_run hub ──▶ VBAR_EL2 vectors ──▶ save guest
   EL1 state, verify PAC "JOP hash", write exit reason ──▶ eret into the EL1
   kernel exception handler ──▶ C dispatch (classify / fault) ──▶ vm_fault
   ──▶ return to guest (eret).
```

- The kernel runs at EL1 (`kernel_entry @ fffffe000c110000`, VBAR_EL1 =
  `0xfffffe000b75c000`).
- EL2 bring-up is gated on `hv_support_init` (`FUN_fffffe000b984d4c`) reading
  `currentel == 8` and the chip id (`DAT_fffffe0007e0c03c`, high byte `0x61`).
  Availability is stored in `hv_available_flag` (`DAT_fffffe0007e41db0`).
- EL2 feature detection (`FUN_fffffe000b987fa8`) fills `hv_el2_features`
  (`DAT_fffffe0007e0d800`) and the SoC flags `DAT_fffffe0007e0d818/1c/1e`.
- The per-CPU EL2 state (register banks, translation pages, guest save area)
  is built by `hv_el2_state_build` (`FUN_fffffe000b9895b8`) and stored at the
  vcpu's EL2 base (`el2_state + 0x4000..`, see `struct hv_el2_state` in
  `hv_vmm.h`).

### 1.2 Guest-exit path

`hv_vcpu_run` hub (`FUN_fffffe000b989a44`, 16.8 KB, vcpu-core) runs the guest
and, on each exit, dispatches on the reason word at `el2_state+0x4008`.
The EL2 vector table (`hv_el2.c`, tree el2-vectors):

| Vector | Address | Reason |
|---|---|---|
| sync  | `FUN_fffffe000b760b94` (body `b760b10`) | 1 |
| error | `FUN_fffffe000b7615bc` | 2 |
| irq   | `FUN_fffffe000b760f04` | 3 |
| fiq   | `FUN_fffffe000b761260` | 4 |

Common dispatch `FUN_fffffe000b761930` re-enters the EL1 kernel handlers
(`b75deac/b75df7c/b75e000/b75e058`). C-level handling:
- `hv_el2_guest_esr_classify` (`FUN_fffffe000b96743c`) — ESR EC decode.
- `hv_el2_guest_fault` (`FUN_fffffe000b967768`) — synthesises the guest IPA
  from HPFAR_EL2 and drives `vm_fault`.
- `hv_el2_guest_irq` (`b967004`) / `hv_el2_guest_fiq` (`b966c74`).
- Return to guest: `FUN_fffffe000b75e468` / `b75e5cc` (restore + `eret`).

The hub reads the exit reason at `el2_state+0x4008` and the ESR/ISS words at
`+0x4010/+0x4018` to build the userland exit record.

### 1.3 Stage-2 MMU (guest → host memory)

Two-part construction:
1. **Host vm_map per VM owner.** `hv_vm_map_core` (`FUN_fffffe000b9868a8`,
   trap-dispatch) resolves the owner via `hv_pmap_resolve_owner`
   (`FUN_fffffe000b986b34`), validates the range against the owner's window
   (`owner+0x28/+0x30`) and page mask (`owner+0x44`), and drives
   `vm_map_enter`/`protect`/`remove` (`b8b51c8`/`b8b49e8`/`b8a8078`).
   The host map pointer lives at `owner+0x2120`.
2. **Fixed EL2 translation table.** `hv_el2_pt_alloc` (`FUN_fffffe000b98e344`)
   allocates a 0x4000-byte block (L1@+0x0, L2@+0x1000, L3@+0x2000, state@+0x4000)
   stored at `el2_state+0x4150`; `hv_el2_state_build` records the L2/L3 table
   pointers on the config slots 0xd/0xe. The page walk runs in hardware; the
   VMSAv8-64 descriptor format is modelled (as an estimate) in `hv_pmap.h`.

Guest fault resolution: a stage-2 translation fault goes through the EL2
vector → classify (`b96743c`) → `hv_el2_guest_fault` (`b967768`), which for
an EA-set / non-in-guest abort synthesises the IPA as
`FAR[11:0] | (HPFAR_EL2[31:4] << 12)` and calls the kernel vm_fault family
(`b94b450`/`b89988c`/`b9879b8`, shared deps).

### 1.4 Trap surface

The mach-trap dispatcher `FUN_fffffe000b984ed8` (est. `hv_available`,
support-init) reads the availability flag and dispatches command
`param_1+8` through the 19-entry op table `PTR_FUN_fffffe0007e0d750`.
Full index→name map in `docs/chain-map.md` ("FINAL OP-TABLE INDEX -> NAME
MAP"). `hv_vmm_present` (`FUN_fffffe000be39fd0`) is the only hypervisor entry
in the boot-arg/name table at `fffffe0007e35080`.

### 1.5 IPC service

The vmapple service is an IPC kobject: the `IKOT_HYPERVISOR` record at
`fffffe000c7a9f28` references the handler `FUN_fffffe000b985e38`
(est. `hv_ikot_hypervisor_handler`, vmapple-ipc tree). It unlinks/releases
hypervisor container objects reached via IPC ports. Entitlement gating uses
three strings (`com.apple.security.hypervisor @ fffffe00070724f0`,
`com.apple.private.hypervisor.vmapple @ fffffe000707250e`,
`com.apple.private.hypervisor @ fffffe0007072533`) probed through the sandbox
credential-ops table `DAT_fffffe0007e93310` slot +0x1c0.

### 1.6 Boot chain

```
kernel entry fffffe000c110000
  └─ arm_cpu_init   FUN_fffffe000b95af80   (EL2/EL1 control, gated on DAT_7e0da68)
       └─ kernel_bootstrap FUN_fffffe000b8243f0
            └─ kernel_bootstrap_thread FUN_fffffe000b8239e0
                 └─ hv_support_init FUN_fffffe000b984d4c
                      ├─ EL2 + chip-id gate, ISA VM quota (DT + boot-arg)
                      └─ hv_el2_feature_detect FUN_fffffe000b987fa8
                 → DAT_fffffe0007e41db0 = return (hv availability)
```

---

## 2. File map

| File | Tree | Covers |
|---|---|---|
| `osfmk/arm64/hypervisor/hv_support.c` / `.h` | support-init | boot entry, EL2 detect, availability dispatcher |
| `osfmk/arm64/hypervisor/hv.c` / `hv.h` | trap-dispatch | op-table handlers, `hv_trap_record`, `hv_vmm_present` |
| `osfmk/arm64/hypervisor/hv_vcpu.c` / `.h` | vcpu-core | vcpu lifecycle + the run/exit hub |
| `osfmk/arm64/hypervisor/hv_vmm.c` / `.h` | el2-state | EL2 register state build/apply/commit, slot ops, pt alloc |
| `osfmk/arm64/hypervisor/hv_el2.c` / `.h` | el2-vectors | EL2 vector handlers + guest-exit C dispatch |
| `osfmk/arm64/hypervisor/hv_pmap.c` / `.h` | hv-pmap | stage-2 owner/map resolution + unwind |
| `osfmk/arm64/hypervisor/hv_vmapple.c` / `.h` | vmapple-ipc | IKOT_HYPERVISOR handler, container teardown |
| `osfmk/arm64/hypervisor/hv_entitlements.c` / `.h` | entitlements | entitlement tier, capability mask/report |
| `osfmk/arm64/hypervisor/hv_vm.h` | structs-audit | **consolidated** `hv_vm_t` (owner), `hv_vm_percpu_t`, region node |
| `osfmk/arm64/hypervisor/hv_kernel_glue.c` / `.h` | hv-deps | recreated direct kernel callees (current_task, waitq_validate, hv_object_lookup) |
| `osfmk/arm64/hypervisor/hv_glue_audit_{locks,mem,obj,panic,sys}.c` | hv-deps | FULL-AUDIT kernel touch-set recreation (2026-08-12): locks (lck_mtx_lock/unlock core, lock bits, spinlocks), mem (vm_map_wire/unwire/protect/enter, kernel_alloc {err,block}, zalloc core), obj (os_release/zfree_waitq/refcounts/obj-lookup), panics, sys (per_cpu_base disasm fallback, tlb_flush, paddr_type, memattr, trace, dt/boot-arg) |
| `osfmk/arm64/hypervisor/hv_internal.h` | shared-utils | shared kernel deps + cross-file prototypes + global naming table |
| `osfmk/kern/startup.c` / `startup.h`, `osfmk/arm64/start.s` | boot-audit | boot path recreation |
| `docs/chain-map.md` | — | boot chain, op-table map, per-tree edges |
| `docs/findings.md` | — | append-only security observations |
| `docs/audit.md` | — | this synthesis |
| `docs/manifest.json` | — | per-function ground truth (addresses, names, status) |

---

## 3. Attack surface inventory

Every guest→host (and userland→kernel) boundary, with the function addresses
that implement it.

### 3.1 Operation table handlers (mach-trap, userland → hv)

Dispatcher `FUN_fffffe000b984ed8` → op table `PTR_FUN_fffffe0007e0d750`.

| idx | handler | name (est.) | surface |
|---|---|---|---|
| 0 | `b984fd8` | hv_capabilities | entitlement-gated 0x1b3 report copyout; no copyin |
| 1 | `b985588` | hv_vm_create | copyin 0x1c; entitlement tier check; quota decrement; alloc owner + 0x430 slot array; per-cpu owner slot `+0x628` |
| 2 | `b985bf0` | hv_vm_destroy | per-cpu vm teardown; refcount; last-releaser panic |
| 3/5 | `b986898`/`b986d94` | hv_vm_map / unmap | → `hv_vm_map_core b9868a8` |
| 4 | `b986d84` | hv_vm_protect | bare branch stub into map core (protect) |
| 6 | `b989040` | hv_vcpu_create | copyin 0x10; binds per-cpu vcpu slot `tpidr+0x4d8` |
| 7 | `b9897bc` | hv_vcpu_destroy | per-cpu vcpu teardown + EL2 AMX/SVE disable |
| 8 | `b9899b0` | hv_vcpu_run | launch via `b988358` with EL2-feature-gated control mask |
| 9 | `b989a44` | hv_vcpu_run (hub) | the guest-exit dispatch hub (16.8 KB) |
| 10 | `b98e488` | hv_trap_op_10 | **CPU-bitmask vcpu-slot flush** (no copyin; see 3.7) |
| 11 | `b986e50` | hv_vcpu_attach | attach vcpu to container by id |
| 12 | `b986da4` | hv_vm_map_shared | copyin 0x20; maps guest mem + copies 8-byte handle out |
| 13/18 | NULL | — | dispatcher errors `0xfae9400f`/`0xfae94001` |
| 14 | `b986f1c` | hv_vm_set_trap_debug | copyin 0x18; hw debug-reg slot 0..9 via `b954160` |
| 15 | `b98e788` | hv_trap_op_15 | SVE/SVCR_EL2 mode select (mode 0..3) |
| 16 | `b98e964` | hv_trap_op_16 | SoC-feature-gated `hv_el2_pt_alloc` |
| 17 | `b986ff4` | hv_vm_map_region | copyin 0x34; interval-rbtree region insert |

### 3.2 HVC / guest synchronous exceptions

- Guest HVC / SVC → EL2 sync vector `FUN_fffffe000b760b94` → classify
  `FUN_fffffe000b96743c` (EC 0x18 SVC → exit 8, ISS to `el2_state+0x4018`;
  0x20 IABT; 0x24 DABT; 0x3f SMC-ish; unhandled → panic).
- The hub `b989a44` decodes the HVC class `0xc3000000` and other EC families.

### 3.3 Fault path (stage-2 → vm_fault)

- `hv_el2_guest_fault` `FUN_fffffe000b967768` — IPA synthesis from HPFAR_EL2
  (see finding), then `vm_fault` via `b94b450`/`b89988c`/`b9879b8`.

### 3.4 copyin / copyout (userland arg blocks)

- `copyin` `FUN_fffffe000b95c144` / `copyout` `FUN_fffffe000b95d6f4` — shared
  kernel externs (universal XNU user-copy machinery, not recreated).
- `hv_copyin_user` `FUN_fffffe000b98e020` (el2-state) — validate-then-copyin
  with the VM_MAP_WIRE fault table.
- `hv_vcpu_slot_op` `FUN_fffffe000b98e12c` — slot refcount + copyin/out.

### 3.5 Shared memory

- `hv_vm_map_shared` `FUN_fffffe000b986da4` — maps guest memory, returns a
  shared-region handle; copyout-failure path retains the mapping (finding).
- `hv_vcpu_map_memory` `FUN_fffffe000b9866d0` (vcpu-core) — page-alignment +
  page-size-mask validation before mapping.

### 3.6 IPC kobject

- `hv_ikot_hypervisor_handler` `FUN_fffffe000b985e38` (vmapple-ipc) — the
  IKOT_HYPERVISOR record handler at `fffffe000c7a9f28`; container unlink /
  object release. Depends on kernel object lookup `b7e0d8c` and
  `waitq_validate` `b78fb24`.

### 3.7 Trap-debug and the CPU-bitmask op

- `hv_vm_set_trap_debug` `FUN_fffffe000b986f1c` — selector 0..9 bound, but the
  vm-resource deref in `b954160` is unconditional (NULL-fault finding).
- `hv_trap_op_10` `FUN_fffffe000b98e488` — unbounded 0..63 slot index from a
  guest bitmask into the owner block (HIGH severity finding).

### 3.8 EL2 register restore / save

- `hv_vcpu_save_el2_state` `FUN_fffffe000b988358` (vcpu-core) — captures guest
  EL2 sysreg groups into `el2_state`; dirty-bit gated.
- `hv_el2_state_apply` `FUN_fffffe000b98dd40` / `hv_el2_state_commit`
  `FUN_fffffe000b98ded4` — template→active merge and dirty-flag commit.

---

## 4. Findings index (grouped by subsystem, from `docs/findings.md`)

Severity is a **hypothesis**, not a claim (per `AGENTS.md`).

| Subsystem | Address (fn) | Name (est.) | Severity (hypothesis) |
|---|---|---|---|
| entitlements | `b985ae4` | hv_entitlement_tier | low |
| entitlements | `b987d9c` | hv_caps_feature_mask | informational |
| entitlements | `b988038` | hv_caps_cpu_report | informational/low |
| entitlements | `c0f8cfc` | cred_has_entitlement | informational |
| entitlements | `7e0d7f0` | quota consumption | low |
| hv-deps | `b78fb24` | waitq_validate | informational/low |
| hv-deps | `b7e0d8c` | hv_object_lookup | low |
| hv-deps | `b95c144` | copyin | informational |
| boot-audit | `bdbb37c` | code_signing_monitor_lockdown | informational |
| boot-audit | `bf2413c` | oskext_remove_kext_bootstrap | informational/low |
| boot-audit | `b95af80` | arm_cpu_init (EL2 control) | informational |
| el2-vectors | `b96743c` | unknown EC → panic | **medium** |
| el2-vectors | `b967768` | HPFAR_EL2 IPA synthesis | low |
| el2-vectors | `b760b94..b7615bc` | guest-state PAC "JOP hash" | informational |
| el2-vectors | `b96743c` | SVC ISS passthrough | informational |
| el2-vectors | `b75e468` | SVE/FPSR restore on eret | low |
| hv-pmap | `b986b34` | resolve_owner map-pointer trust | informational/low |
| hv-pmap | `b9868a8`/`b986d34` | unwind releases owner only when unbound | informational |
| hv-pmap | EL2 stage-2 table | fixed small table, descriptor unobserved | informational |
| op-table-id | **`b98e488`** | **hv_trap_op_10 unbounded slot index** | **high** |
| op-table-id | `b986f1c` | hv_vm_set_trap_debug NULL deref | medium |
| op-table-id | `b986da4` | hv_vm_map_shared mapping persists on copyout fail | low |
| op-table-id | `b986d84` | hv_vm_protect bare stub | informational |
| op-table-id | `b984fd8` | hv_capabilities fixed-size copyout | informational |
| op-table-id | `b98e788`/`b98e964` | hv_trap_op_15/16 gated, bounds-checked | informational |

**Highest-priority:** `hv_trap_op_10` (`b98e488`) — guest-controlled
out-of-bounds write into the vm owner block (`owner + idx*0x10 + 0x12` and
`owner + idx*0x80 + 0x94` with `idx` in 0..63 and no `idx < 8` guard).

---

## 5. Review guide — how to read the codebase end to end

Suggested reading order to trace a guest from entry to teardown:

1. **Entry (userland → kernel):** `osfmk/kern/startup.c` (boot) then
   `hv_support.c` — `hv_support_init b984d4c` → `hv_el2_feature_detect
   b987fa8` → availability `DAT_7e41db0`. See `docs/chain-map.md` boot chain.
2. **Trap dispatch:** `hv_support.c` `hv_available b984ed8` dispatches the
   op table `PTR_FUN_fffffe0007e0d750`. Each handler is in `hv.c`
   (trap-dispatch) or `hv_vcpu.c` (vcpu-core).
3. **VM creation:** `hv_vm_create b985588` builds the owner block `hv_vm_t`
   (see `hv_vm.h`): quota/tier fields, per-cpu slot array, host map. The
   region tree node layout is in `hv_vm.h`.
4. **vCPU setup:** `hv_vcpu_create b989040` → `hv_vcpu_alloc_init b989390` →
   `hv_el2_state_build b9895b8` (builds the per-CPU EL2 state, `struct
   hv_el2_state` in `hv_vmm.h`).
5. **Run / guest-exit:** `hv_vcpu_run b989a44` (hub, `hv_vcpu.c`) runs the
   guest; exits go through the EL2 vectors (`hv_el2.c`), classify
   `b96743c`, fault `b967768`; the hub reads `el2_state+0x4008` to dispatch.
6. **Stage-2 MMU:** `hv_pmap.c` resolves the owner (`b986b34`), `hv_el2_pt_alloc
   b98e344` builds the translation tables; `hv_el2_state_apply b98dd40` and
   `hv_el2_state_commit b98ded4` maintain EL2 register state.
7. **Entitlements / capabilities:** `hv_entitlements.c` — `hv_entitlement_tier
   b985ae4` → `hv_caps_feature_mask b987d9c` → `hv_caps_cpu_report b988038`.
8. **IPC teardown:** `hv_vmapple.c` — `hv_ikot_hypervisor_handler b985e38`
   unlinks container objects; `hv_rbtree_unlink b9860bc` does the RB removal.
9. **Teardown:** `hv_vm_destroy b985bf0`, `hv_vcpu_destroy b988e70`,
   `hv_vcpu_object_release b98533c` (quota restore + per-slot array free).

To verify any claim: look up the address in Ghidra (`decompile_function` or
`get_function_by_address`), and cross-check the estimated name/confidence in
`docs/manifest.json`.

---

*Struct layout for the VM/owner, per-CPU, vCPU and EL2-state objects is
consolidated in `osfmk/arm64/hypervisor/hv_vm.h`, `hv_vcpu.h` and
`hv_vmm.h` (see the "structs consolidated" note in `docs/chain-map.md`).*
