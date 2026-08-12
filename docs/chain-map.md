# chain-map.md — Boot chain and hypervisor-tied function map

Ground truth: Ghidra `FUN_*` names + addresses from `kernelcache.arm64.kc`
(image base `fffffe0007004000`). All human names are estimates with
confidence. Updated by the decompilation agents as they discover edges.

## Boot chain (verified edges, complete to the kernel entry)

Full chain from the kernel image entry point down to the hypervisor init.
Every edge below was re-verified this session with `get_function_callers` /
`get_function_callees` on each hop. Both boot functions are documented only
(shared kernel, `status:stubbed`); the hv init functions are owned by
`support-init` and live in `osfmk/arm64/hypervisor/hv_support.c`.

```
MACH_HEADER @ fffffe0007004000   (kernel image base / Mach-O header)
  └─ program entry → entry @ fffffe000c110000
        ├─ param_1==0: sets VBAR_EL1 to 0xfffffe000b75c000, ISB, halt (early);
        │     otherwise selects the per-CPU boot function by
        │     *(code **)(per-cpu + 0xb8) and calls it
        └─ calls → FUN_fffffe000b95af80   (est. arm_cpu_init, per-CPU early boot)
              ├─ sets up EL1/EL2 control (CPACR_EL1, CNTKCTL_EL1, TLBI_VMALLE1IS)
              ├─ logs "arm_cpu_init(): cpu %d online" (string @ fffffe000c09f2dc)
              └─ calls → FUN_fffffe000b8243f0   (est. kernel_bootstrap)
                    ├─ FUN_fffffe000b7fddc0 / b812f5c   (kernel, shared-dep)
                    └─ calls → FUN_fffffe000b8239e0   (est. kernel_bootstrap_thread)
                          ├─ boot step log "hv_support_init" (string @ fffffe0007059587)
                          ├─ DAT_fffffe0007e41db0 = FUN_fffffe000b984d4c()
                          │      (est. hv_support_init)  ← the ONLY caller of hv_support_init
                          │     ├─ currentel == EL2 (0x8) check
                          │     ├─ "apple-isa-vm-quota" device property
                          │     │     (via FUN_fffffe000c09c084/c09c31c)
                          │     ├─ "hv_apple_isa_vm_quota" boot-arg (via FUN_fffffe000c09cbf0)
                          │     ├─ calls → FUN_fffffe000b987fa8  (est. hv_el2_feature_detect)
                          │     │     ← the ONLY caller of hv_el2_feature_detect
                          │     │     ├─ reads EL2 sysregs UnkSytemRegRead(3,4,0xc,0xb,1),
                          │     │     │     (3,4,0xf,0xc,6)
                          │     │     ├─ reads aidr_el1, id_aa64pfr0_el1, id_aa64pfr1_el1
                          │     │     └─ writes DAT_fffffe0007e0d800 (EL2 features),
                          │     │          DAT_fffffe0007e0d818/0x1c/0x1e (SoC/feature flags)
                          │     └─ returns 1 → stored to DAT_fffffe0007e41db0 (hv availability)
                          └─ ... rest of kernel boot (not recreated — shared kernel)

Alternate early-boot caller of kernel_bootstrap_thread:
FUN_fffffe000c0e7b08   (est. early kernel bootstrap: vm_mem_bootstrap, atm_init,
                       trap_telemetry_init, console_init, stackshot_init,
                       mac_policy_init, task_init, thread_init, workq_init,
                       turnstiles_init, page_worker_init, exception_init,
                       sfi_init, kernel_thread_create, ...)
  └─ calls → FUN_fffffe000b8239e0   (est. kernel_bootstrap_thread)
```

FUN_fffffe000b984ed8  (est. hv_available, mach-trap dispatcher)
  ├─ reads DAT_fffffe0007e41db0 (hv availability)
  ├─ dispatches cmd (param_1+8) through 19-entry op table PTR_FUN_fffffe0007e0d750
  │     └─ handlers (index:addr): 0:b984fd8 1:b985588 2:b985bf0 3:b986898
  │        4:b986d84 5:b986d94 6:b989040(vcpu-core) 7:b9897bc 8:b9899b0
  │        9:b989a44(vcpu-core) 10:b98e488 11:b986e50(vcpu-core)
  │        12:b986da4 13:NULL 14:b986f1c 15:b98e788 16:b98e964
  │        17:b986ff4 18:NULL
  ├─ err -0x516bff1=0xfae9400f (hv unavailable), -0x516bfff=0xfae94001 (default)
  └─ trace FUN_fffffe000bd30528(0x10c0015/6) when DAT_fffffe000c68ac90 bit0 set
FUN_fffffe000be39fd0  (est. hv_vmm_present, mach trap handler)
  └─ calls FUN_fffffe000bf77834("vmm-present", …)  (boot property getter)
```

## Boot-path call sites of hv_* (every entry into the hypervisor from boot code)

`hv_*` is entered from boot code in exactly two places (both inside
`kernel_bootstrap_thread`, `FUN_fffffe000b8239e0`); both are owned by
`support-init` and already decompiled in `hv_support.c`:

1. `DAT_fffffe0007e41db0 = FUN_fffffe000b984d4c()` — the primary boot entry.
   `hv_support_init` runs once on the boot CPU; its return value is the hv
   availability flag consumed by the mach-trap dispatcher
   `FUN_fffffe000b984ed8` (est. hv_available). The boot step is logged under
   the name `"hv_support_init"` (string @ `fffffe0007059587`).
2. `FUN_fffffe000b984d4c` → `FUN_fffffe000b987fa8` (`hv_el2_feature_detect`) —
   the only EL2 feature detection, reached solely from within `hv_support_init`.

No other boot-code function references `FUN_fffffe000b984d4c` or
`FUN_fffffe000b987fa8` (`get_function_callers` on both returns exactly one
caller each: `fffffe000b8239e0` and `fffffe000b984d4c` respectively). The rest
of the hypervisor is entered at runtime through the mach-trap op table
`PTR_FUN_fffffe0007e0d750` via `FUN_fffffe000b984ed8` (see below), never from
boot code.

## Hypervisor cluster (0xfffffe000b984xxx – 0xfffffe000b98exxx)

Core functions (see `docs/manifest.json` for per-function detail):

| Address | Est. name | Tree | Notes |
|---|---|---|---|
| `fffffe000b984d4c` | hv_support_init | support-init | boot entry |
| `fffffe000b984ed8` | hv_available | support-init | reads availability flag |
| `fffffe000b987fa8` | hv_el2_feature_detect | support-init | EL2 sysreg reads |
| `fffffe000b989a44` | hv_vcpu_core (hub) | vcpu-core | 16.8 KB; refs "hv_vcpu.c"; no direct callers (table-dispatched) |
| `fffffe000b989040` | hv_vcpu_create (est.) | vcpu-core | copyin 0x10; binds per-cpu slot `tpidr_el1+0x4d8`; err `0xfae94002/3/6` |
| `fffffe000b989390` | vcpu alloc/init | vcpu-core | called by b989040 |
| `fffffe000b988e70` | hv_vcpu_destroy (est.) | vcpu-core | error path of b989040 |
| `fffffe000b98533c` | vcpu object release | vcpu-core | refcount 1 path of b989040 |
| `fffffe000b98503c` | hv_vcpu_* (est.) | vcpu-core | callee of hub |
| `fffffe000b9866d0` | hv_vcpu_* (est.) | vcpu-core | callee of hub |
| `fffffe000b986e50` | hv_vcpu_* (est.) | vcpu-core | callee of hub |
| `fffffe000b988358` | hv_vcpu_* (est.) | vcpu-core | callee of hub |
| `fffffe000b9895b8` | hv_el2_state_build | el2-state | writes per-CPU EL2 state @ param_2+0x4000… |
| `fffffe000b98dd40` | hv_el2_state_apply | el2-state | merges template EL2 regs into active |
| `fffffe000b98dd04` | hv_vcpu_run_prepare | el2-state | run request setup; calls b986e50 |
| `fffffe000b98ded4` | hv_el2_state_commit | el2-state | dirty-flag commit loop |
| `fffffe000b98e020` | hv_copyin_user | el2-state | validate+copyin user buffer |
| `fffffe000b98e12c` | hv_vcpu_slot_op | el2-state | slot refcount + copyin/out |
| `fffffe000b98e344` | hv_el2_pt_alloc | el2-state | alloc 0x4000 EL2 translation block |
| `fffffe000b98e99c` | hv_el2_pt_alloc_wrapper | el2-state | table-dispatched wrapper |

## Trap table & dispatchers

- **Corrected:** `fffffe0007e35080` is NOT a mach trap table — it is a
  VM-statistics / boot-arg name table (see trap-dispatch section below).
  The real hv mach-trap dispatch is the 19-entry op table `PTR_FUN_fffffe0007e0d750`.
- Name/registration table `fffffe0007e35080` (enumerated exhaustively by
  trap-dispatch): only `hv_vmm_present` (`FUN_fffffe000be39fd0`) is hv; every
  other handler is a VM-stat handler or shared munger.
- Second name table: `fffffe0007e35880` — entries reference VM subsystem names
  (`vm_do_collapse_terminate` @ `fffffe00070c5fda`, `vm_do_collapse_terminate_failure`
  @ `fffffe00070c5ff2`, `vm_should_cow_but_wired` @ `fffffe00070c6010`,
  `vm_create_upl_extra_cow` @ `fffffe00070c6033`). **These are NOT hv traps** —
  do not treat as hypervisor entries.
- Boot-arg descriptor region: `fffffe0007e2bd80` — entries for `hv_support`
  (@ `fffffe00070b84d5`) and `hv_disable` (@ `fffffe00070b84e0`) both point to
  dispatcher `FUN_fffffe000bda3ca8` (shared argument munger; decompile once in
  trap-dispatch, do not recreate per entry). Boot-arg value storage near
  `DAT_fffffe0007e41db0` / `DAT_fffffe0007e9a6d8`.
- `hv_vm_create` / `hv_vcpu_run` literal strings are ABSENT from the binary.
  Find remaining hv trap handlers via the trap table record handlers, not names.

## Data anchors ("everything tied to the hypervisor")

| Address | Meaning | Xref evidence |
|---|---|---|
| `fffffe0007e0d7f0` | hv quota | written by hv_support_init |
| `fffffe0007e0d800` | EL2 features | written by hv_el2_feature_detect; read by b98dd40, b9895b8 |
| `fffffe0007e41db0` | hv availability | written by bootstrap (hv_support_init return); read by b984ed8 |
| `fffffe000c7a9f28` | data ref to `IKOT_HYPERVISOR` string | string @ fffffe0007072550 |
| `fffffe0007e2bda8`/`7e2bdb8`/`7e2be08` | boot-arg table region (hv_support/hv_disable) | strings @ fffffe00070b84d5/e0 |

## vcpu-core edges (from vcpu-core agent)

### vcpu create/bind path (`FUN_fffffe000b989040`, est. hv_vcpu_create)
```
FUN_fffffe000b989040 (hv_vcpu_create)
  ├─ copyin  FUN_fffffe000b95c144   (kernel, shared-dep)
  ├─ cpu     FUN_fffffe000b866ec4   (kernel, shared-dep)
  ├─ lock    FUN_fffffe000b7f0afc / b7f1e4c / b7f1e80   (kernel)
  ├─ → FUN_fffffe000b989390   (est. hv_vcpu_alloc_init)
  │     ├─ alloc FUN_fffffe000b8a6c14   (kernel)
  │     ├─ map  FUN_fffffe000b8b51c8    (kernel vm_map_enter)
  │     └─ unwind b8a8078 / b7f62e8 / b8b6860   (kernel)
  ├─ → FUN_fffffe000b9895b8   (el2-state tree, hv_el2_state_build)
  ├─ → FUN_fffffe000b988e70   (est. hv_vcpu_destroy, error path)
  ├─ → FUN_fffffe000b98533c   (est. hv_vcpu_object_release, refcount 1)
  ├─ copyout FUN_fffffe000b95d6f4  (kernel)
  └─ panic  FUN_fffffe000c0f86a4 / c0f8674   (kernel)
```

### vcpu run/exit dispatch hub (`FUN_fffffe000b989a44`, est. hv_vcpu_run)
No direct callers — table-dispatched via DAT_fffffe0007e0d798 / ptr fffffe000d20adb3.
```
FUN_fffffe000b989a44 (hv_vcpu_run, 16.8KB, decompiler-fallback)
  ├─ → FUN_fffffe000b986e50   (est. hv_vcpu_attach)
  ├─ → FUN_fffffe000b9866d0   (est. hv_vcpu_map_memory)
  ├─ → FUN_fffffe000b98503c   (est. hv_vcpu_state_merge)
  ├─ → FUN_fffffe000b988358   (est. hv_vcpu_save_el2_state)
  ├─ → el2-state: b98dd04, b98dd40, b98ded4, b98e020, b98e12c, b98e344, b9895b8
  └─ kernel: b8a6c14, b8b6860, b8a8078, b8b122c, b8b51c8, b866ec4, b7f*,
             b7619c8, b75f118, b75f3c4, b8b49e8, b96c6d4, b968948, b8078cc,
             b95ecd8, b97019c, b7a1dd8, bf481a4, b8563f8, b91ae80, b91accc,
             b758d80; panic c0e0620/c0e11ec/c0f1874/c0e4d74
```

### remaining seed callees (kernel deps — stubbed, never decompiled)
- `FUN_fffffe000b988358` → FUN_fffffe000b9888a4, FUN_fffffe000b75f118 (kernel)
- `FUN_fffffe000b98533c` → FUN_fffffe000b987c44, b8b122c, b8afa78, b862b6c, b8627ac, b7f09dc (kernel)
- `FUN_fffffe000b986e50` → FUN_fffffe000b986b34, b793cf4, b8afa78, c0e1c3c (kernel)
- `FUN_fffffe000b9866d0` → FUN_fffffe000b948ac8, b8ada1c, b7e0b70, b78d628 (kernel)

## el2-state edges (from el2-state agent)

### callers
```
FUN_fffffe000b989040 (vcpu-core, hv_vcpu_create) ──► FUN_fffffe000b9895b8 (hv_el2_state_build)
FUN_fffffe000b989a44 (vcpu-core, hv_vcpu_run)    ──► FUN_fffffe000b9895b8, b98dd40,
        b98dd04, b98ded4, b98e020, b98e12c, b98e344
FUN_fffffe000b98e99c (el2-state, wrapper)        ──► FUN_fffffe000b98e344 (no callers of its own)
```

### seed callees
- `FUN_fffffe000b9895b8` (hv_el2_state_build) — no callees
- `FUN_fffffe000b98dd40` (hv_el2_state_apply) — no callees
- `FUN_fffffe000b98dd04` (hv_vcpu_run_prepare) → FUN_fffffe000b986e50 (vcpu-core)
- `FUN_fffffe000b98ded4` (hv_el2_state_commit) — no callees
- `FUN_fffffe000b98e020` (hv_copyin_user) → b8b51c8, b8afb18, b8a8078 (kernel, stubbed)
- `FUN_fffffe000b98e12c` (hv_vcpu_slot_op) → b7f62e8, b8b6860, b8b49e8, b8b122c,
  thunk_b8a8078@b9141a4 (kernel, stubbed)
- `FUN_fffffe000b98e344` (hv_el2_pt_alloc) → b8a6c14, b8b51c8, b7f62e8, b8b6860,
  b96c6d4 (TLB flush), c0f1874 (panic, noreturn) — all kernel, stubbed
- `FUN_fffffe000b98e99c` (hv_el2_pt_alloc_wrapper) → FUN_fffffe000b98e344

### data refs
- DAT_fffffe0007d813d8 = {int,char*} fault table: {19,"VM_MAP_WIRE"@7067b6b,
  {20,"VM_MAP_UNWIRE"@7067b77} — passed to kernel_copyin (b8afb18) in hv_copyin_user
- DAT_fffffe0007d81408 = {int,char*} fault table: {20,"VM_MAP_UNWIRE"@7067b77,
  {19,"VM_MAP_WIRE"@7067b6b} — passed to kernel_copyin2 (b8b122c) in hv_vcpu_slot_op
- DAT_fffffe0007e0d800 (EL2 features) read into active +0x4090 in hv_el2_state_build
- DAT_fffffe0007e0da68 read (==0) guards the build path
- DAT_fffffe0007e0d81e feature bit 0; DAT_fffffe0007e31628 SoC feature index (>4 clears TCR bit)

## trap-dispatch tree (hv.c / hv.h)

### Trap dispatch record layout (from FUN_fffffe000bda3ca8, est. trap_arg_munger)
```
record +0x10  copyin_flag  : bool (fetch 4-byte user arg via copy helper)
record +0x28  copy         : copyin/copyout helper, copy(record, buf, 4)
record +0x30  copyout_flag : bool (handler produces a result to return)
record +0x38  arg_size     : 8 or 4 (selects handler call shape below)
record +0x48  handler      : handler(record, &value, arg_size)
```
Munger (shared, stubbed — decompiled ONCE here): copy in → if caller wants a
result and copyout_flag, call handler; 8-byte arg is range-checked to 32-bit
(else err 0x22). Recorded in `osfmk/arm64/hypervisor/hv.c` + `hv.h`.

### Name/registration table 0xfffffe0007e35080 — exhaustive enumeration
Paged in 8×256 B windows (0x7e35080–0x7e35800). Every handler pointer classified:
| Handler | Est. role | hv? |
|---|---|---|
| `fffffe000be39fd0` ("hv_vmm_present" @ 0x70c592c) | hv_vmm_present | **HV** |
| `fffffe000bda3ca8` | shared arg munger | no (shared) |
| `fffffe000bda45c0` | sibling munger (body 0x7e0db50+0x0) | no (shared) |
| `fffffe000be3b6f8` / `be3b784` / `be3b80c` / `be3b8c8` | VM stat handlers | no |
| `fffffe000bda5734` | VM stat handler | no |
Names for the non-hv entries: `global_enable`, `local_enable`,
`fault_busy_retry_count`, `self_region_footprint`, `self_region_page_size`,
`self_region_info_flags`, `mem_entry_wimg_non_writable`, `lock_contention`,
"Number of VM fault operations … busy page" — all VM subsystem boot-args/sysctls.
**Conclusion: hv_vmm_present is the only hypervisor entry in the whole table.**

### hv mach-trap op table PTR_FUN_fffffe0007e0d750 — verified index by index
Read 160 B = 19×8 B pointers (see Boot chain for the map). trap-dispatch owns
14 handlers, all reconstructed in hv.c + manifest `decompiled`:
```
idx0  b984fd8  hv_capabilities        idx10 b98e488 hv_trap_op_10 (unid.)
idx1  b985588  hv_vm_create           idx11 b986e50 (vcpu-core)
idx2  b985bf0  hv_vm_destroy          idx12 b986da4 hv_vm_map_shared
idx3  b986898  hv_vm_map              idx13 NULL
idx4  b986d84  hv_vm_protect (stub)   idx14 b986f1c hv_vm_set_trap_debug
idx5  b986d94  hv_vm_unmap            idx15 b98e788 hv_trap_op_15 (unid.)
idx6  b989040  (vcpu-core)            idx16 b98e964 hv_trap_op_16 (unid.)
idx7  b9897bc  hv_vcpu_destroy        idx17 b986ff4 hv_vm_map_region
idx8  b9899b0  hv_vcpu_run            idx18 NULL
idx9  b989a44  (vcpu-core hub)
```
Edges into vcpu-core/el2-state (owned by those trees, not recreated here):
- `hv_vm_create`(b985588) → `b9866d0`(vcpu-core), `b98533c`(vcpu-core release)
- `hv_vcpu_destroy`(b9897bc) → `b988e70`(vcpu-core), `b9882ac`
- `hv_vcpu_run`(b9899b0) → `b988358`(vcpu-core)
- `hv_trap_op_16`(b98e964) → `b98e344`(el2-state)
- `hv_trap_op_10`(b98e488) → `b98e74c`(el2-state finalize)
Shared-kernel deps stubbed (never decompiled): b95c144/b95d6f4 (copyin/copyout),
b986b34 (vm owner lookup), b8b51c8/b8b49e8/b8a8078 (vm_map), b7eb624/b7f089c
(alloc), b7f0afc/b7f1e4c/b7f1e80/b7f0ac8/b7f1e80 (locks, DAT_fffffe000c62c0b8),
b862b6c/b8627ac (refcount), b793cf4/b8afa78/b8a6c14/b7f62e8/b8b6860,
b866ec4 (per-cpu), b8afa78, panic c0e1c3c/c0f1874/c0f86a4/c0f8674.

## shared-utils edges (from shared-utils agent)

Cross-tree helper shared by >=2 trees, newly stubbed in the manifest
(tree=shared-utils, status=stubbed, category=core, not yet decompiled):
```
FUN_fffffe000b987c44 (est. hv_vm_owner_teardown)
  ├─ called by FUN_fffffe000b985588 (hv_vm_create, trap-dispatch) — unwind path
  └─ called by FUN_fffffe000b98533c (hv_vcpu_object_release, vcpu-core) — teardown
```
hv_internal.h (`osfmk/arm64/hypervisor/hv_internal.h`, shared-utils-owned)
consolidates the shared kernel deps (copyin/copyout b95c144/b95d6f4, locks
b7f0afc/b7f1e4c/b7f1e80, per-cpu base b866ec4, panics c0f86a4/c0f8674/c0f1874,
LORelease, kernel_alloc/mem_validate/mem_release/memzero b8a6c14/b8b51c8/b8a8078/
b8b6860) and the hv cross-file prototypes (el2-state b9895b8/b98dd40/b98dd04/
b98ded4/b98e020/b98e12c/b98e344/b98e99c/b98e74c; vcpu-core b989040/b989390/
b988e70/b98533c/b98503c/b9866d0/b986e50/b988358/b989a44; entitlements
hv_entitlement_tier).

## vmapple-ipc / IKOT_HYPERVISOR anchor (from vmapple-ipc agent)

### IKOT_HYPERVISOR record (data @ fffffe000c7a9f28)
```
fffffe000c7a9f28  { name_ptr = fffffe0007072550 ("IKOT_HYPERVISOR"),
                    handler  = FUN_fffffe000b985e38 }   (record base)
```
The record sits in a name->handler/value table spanning ~fffffe000c7a9a00-7aa000.
Neighbouring hypervisor entries:
- `fffffe000c7a9e68` : "hv" entry -> value refs DAT_fffffe000c62c0c0 (hv lock),
  DAT_fffffe0007e0d7e8 (near hv quota global fffffe0007e0d7f0)
- `fffffe0007071e74` : "hv_vm_t.hv_vm_percpu_t" string (referenced from the region)
The referenced handler FUN_fffffe000b985e38 is hypervisor code: takes the hv lock
DAT_fffffe000c62c0c0, reads per-CPU state, and on container refcount 1 calls
FUN_fffffe000b98533c (est. hv_vcpu_object_release, vcpu-core).

### vmapple entitlement com.apple.private.hypervisor.vmapple (@ fffffe000707250e)
Referenced from 3 functions:
| Caller | Role | Owner |
|---|---|---|
| FUN_fffffe000b985588 | est. hv_vm_create (mach trap) | trap-dispatch (decompiled) |
| FUN_fffffe000b985ae4 | est. hv_entitlement_access_level | vmapple-ipc (decompiled) |
| FUN_fffffe000b96c158 | task entitlement flags (exec path) | vmapple-ipc (stubbed, kernel) |

`FUN_fffffe000b985ae4` (est. hv_entitlement_access_level) returns level 3 iff
`com.apple.private.hypervisor.vmapple`, else derived from
`com.apple.security.hypervisor`; level 4 needs `com.apple.private.hypervisor`
+ config bit `DAT_fffffe0007e255f8 & 0x1010`. Called by trap op idx0
(FUN_fffffe000b984fd8). Entitlement checks via
`(**(code**)DAT_fffffe0007e93310 + 0x1c0)(task, name)`.

### hv-deps direct-kernel-callee conversion (scope decision 2026-08-11, updated by hv-deps)
Direct kernel callees of the hv code were evaluated for body recreation
(get_function_callers + decompile per candidate; evidence in the manifest):
- CONVERTED (body) -> osfmk/arm64/hypervisor/hv_kernel_glue.c (+ .h):
  - FUN_fffffe000b8663e8 (current_task)
  - FUN_fffffe000b78fb24 (waitq_validate) — tiny self-contained (zone magic 0x15
    + waitq-lock register); ~130 callers but small enough to audit
  - FUN_fffffe000b7e0d8c (hv_object_lookup) — DETERMINED KERNEL container/
    object-registry lookup (type table DAT_fffffe0007d78658), NOT hypervisor-
    owned; small self-contained, direct callee of hv (b985e38, type 0x2d), so
    recreated per FULL-AUDIT
- LEFT as externs (universal XNU core; recreating = recreating core XNU):
  b866ec4 (per-CPU getter, decompiler panic-stub — not recreatable), b7f0afc/
  b7f1e80 (lck_mtx_lock/unlock on hv lock 0xc62c0b8; 100+ callers each),
  b8afa78 (os_release), b793cf4 (zfree), b862b6c (refcount dec), b95fe60
  (cache_type_lookup, 7 callers), c0f8cfc (cred_has_entitlement, 100+ callers).
  Newly documented as stubbed manifest entries (tree=hv-deps, file
  hv_kernel_glue.c): copyin b95c144, copyout b95d6f4, panics c0f86a4/c0f8674/
  c0e1c3c, lock variant b7f1e4c. All externs documented with Ghidra addresses.
  Reported to Main; a future branch may recreate the XNU lock/alloc core.

## entitlements tree (hv_entitlements.c)

### Entitlement/capability chain (op-table index 0, hv_capabilities = b984fd8)
```
FUN_fffffe000b984fd8 (hv_capabilities, trap-dispatch)
  ├─ → FUN_fffffe000b985ae4  (est. hv_entitlement_tier)   [entitlements]
  │     ├─ per_cpu_base FUN_fffffe000b866ec4 (thread->task, kernel extern)
  │     ├─ FUN_fffffe000b8663e8 (est. current_task, body in hv_kernel_glue.c)
  │     └─ (**(code**)(DAT_fffffe0007e93310 + 0x1c0))(cred, "<entitlement>")
  │           returns tier: 0 none / 1 com.apple.security.hypervisor /
  │           3 vmapple or private / 4 private + DAT_7e255f8&0x1010
  ├─ → FUN_fffffe000b987d9c  (est. hv_caps_feature_mask)   [entitlements]
  │     └─ 19-qword capability mask from tier; probes
  │        com.apple.private.virtualization for tier<2; reads
  │        DAT_fffffe0007e0d818 (implementer), DAT_fffffe0007e0d820 (features)
  ├─ → FUN_fffffe000b988038  (est. hv_caps_cpu_report)     [entitlements]
  │     ├─ cache block-shift for 0x1000/0x4000 pages (PTR_PTR_7e0c5b3f58/60/68)
  │     ├─ ctr_el0 / dczid_el0 / id_aa64dfr0/1, isar0/1, mmfr0/1, pfr0/1
  │     ├─ UnkSytemRegRead(3,0,0,7,2), (3,0,0,4,5), (3,0,0,4,4)
  │     ├─ cache geometry via FUN_fffffe000b95fe60 (kernel, cache_type_lookup)
  │     └─ DAT_fffffe0007e0c6ac topology selection; ends halt_baddata()
  └─ copyout FUN_fffffe000b95d6f4 (0x1b3 bytes)
```
FUN_fffffe000b985588 (hv_vm_create, trap-dispatch) also calls
FUN_fffffe000b987d9c(owner+0x411, tier).

### Data anchors (entitlements)
| Address | Meaning |
|---|---|
| `fffffe0007e93310` | credential/sandbox ops table; slot +0x1c0 (idx 0x38) = entitlement probe (returns 0 = entitled), target FUN_fffffe000c0f8cfc |
| `fffffe0007e255f8` | kernel-config/boot-arg enable flags (bit 4 = hv_apple_isa_vm_quota override; bits 0x1010 gate tier 4) |
| `fffffe0007e0d818` | SoC implementer (hv_el2_feature_detect write; caps-mask read) |
| `fffffe0007e0d820` | hv feature flags (bits 1/2 gate caps-mask / cpu-report) |
| `fffffe0007e0c6ac` | cache/topology flag word (POPCOUNT selects cache-type entry) |

### Boot-args hv_support / hv_disable (descriptor table 0x7e2bd80)
The boot-arg descriptor region `fffffe0007e2bd80` has entries whose name
pointers are `hv_support` (@ fffffe00070b84d5) and `hv_disable`
(@ fffffe00070b84e0). Descriptor fields decoded from memory reads (16-byte
windows): entry storage pointer at `fffffe0007e2bd90` -> `fffffe0007e9a6d8`
(boot-arg value storage), and `fffffe0007e2bda8` -> `fffffe0007e41db0` (the hv
availability flag). Both name entries route through the shared argument munger
`FUN_fffffe000bda3ca8` (trap-dispatch, stubbed — decompiled once there). The
consult site is the availability flag `DAT_fffffe0007e41db0`, read by
`FUN_fffffe000b984ed8` (hv_available, support-init tree). Quota boot-arg
`hv_apple_isa_vm_quota` is read by hv_support_init via FUN_fffffe000c09cbf0.

### Quota consumers (owned by other trees, not re-decompiled here)
The quota pool `DAT_fffffe000c5b83b0-b8` (written by hv_support_init) is
consumed by:
- `FUN_fffffe000b985588` (hv_vm_create, trap-dispatch): reads pool, decrements
  by tier-selected index when tier>1.
- `FUN_fffffe000b98533c` (hv_vcpu_object_release, vcpu-core): reads/writes pool
  by type obj[0x425].
Both already decompiled by their owning trees; documented here, not recreated.

### Direct kernel deps converted / left (entitlements scope)
- CONVERTED (body): FUN_fffffe000b8663e8 (current_task) -> hv_kernel_glue.c
  (already by hv-deps).
- LEFT as externs in hv_kernel_glue.c (universal XNU core): b866ec4
  (per-CPU/task getter), FUN_fffffe000b95fe60 (cache_type_lookup, 7 kernel
  callers), FUN_fffffe000c0f8cfc (sandbox entitlement probe, 100+ callers).
- Security observations logged in docs/findings.md (entitlements sections).

## Correction log
- 2026-08-11: `fffffe0007e35080` was previously labelled the "Mach trap table
  region". It is actually a VM-statistics/boot-arg name table; the only
  hypervisor entry in it is `hv_vmm_present` (`FUN_fffffe000be39fd0`). The real
  hv mach-trap dispatch is the 19-entry op table `PTR_FUN_fffffe0007e0d750`.
- 2026-08-11: hv_available (FUN_fffffe000b984ed8) is a mach-trap dispatcher,
  not a simple flag reader: it dispatches through the 19-entry op table
  PTR_FUN_fffffe0007e0d750 (see Boot chain). Handlers 6/9/11 (b989040,
  b989a44, b986e50) belong to vcpu-core; the other 14 unclaimed handlers were
  recorded as mapped tree=trap-dispatch in the manifest for that tree to
  claim+decompile.
- 2026-08-11: the four strings at `fffffe00070c5fda/ff2/6010/6033` are
  `vm_*` subsystem names (from the `vm_create` byte-pattern hits), not
  `hv_vm_create` trap names. Recorded as a table of VM names; trap-dispatch
  tree uses table record handlers instead.

## hv-deps edges (from hv-deps agent, 2026-08-11)

Direct kernel callees of hv code, with the caller edge each was verified
against (`get_function_callers`). Every address below has a manifest entry
(tree=hv-deps, file `osfmk/arm64/hypervisor/hv_kernel_glue.c`).

### Recreated with bodies (hv_kernel_glue.c + hv_kernel_glue.h)
```
FUN_fffffe000b8663e8  current_task     <- hv_entitlement_access_level (b985ae4), vmapple
FUN_fffffe000b78fb24  waitq_validate   <- hv_ikot_hypervisor_handler (b985e38); also
                                            called by hv_object_lookup
FUN_fffffe000b7e0d8c  hv_object_lookup <- hv_ikot_hypervisor_handler (b985e38, type 0x2d)
```
Edges re-verified: `get_function_callers(b78fb24)` includes b985e38;
`get_function_callers(b7e0d8c)` includes b985e38 (plus ~27 kernel callers in
the b7e0-b7e9 container-registry cluster — evidence it is kernel, not hv).

### Kept as externs (universal XNU core / not recreatable) — evidence
| Address | Est. name | Caller-count evidence | Why extern |
|---|---|---|---|
| b95c144 | copyin | 100+ kernel callers | deep user-copy + fault machinery |
| b95d6f4 | copyout | 100+ kernel callers | deep user-copy + fault machinery |
| b7f0afc | lck_mtx_lock | 100+ kernel callers | full futex/waitq mutex |
| b7f1e80 | lck_mtx_unlock | 100+ kernel callers | full futex/waitq mutex |
| b866ec4 | current_cpu_datap | whole-kernel | decompiler collapses to panic stub (body PAC'd) |
| b8afa78 | os_release | universal | ARC-style release |
| b793cf4 | zfree_waitq | universal | zone free w/ waitq teardown |
| b862b6c | refcount_dec | universal | refcount hash dec + free |
| b95fe60 | cache_type_lookup | 7 kernel callers | cache-topology primitive |
| c0f8cfc | cred_has_entitlement | 100+ sysctl/ops callers | sandbox probe choke point |
| c09c084/c09c31c/c09cbf0 | DT/boot-arg getters | 45/55/100+ callers | device-tree / boot-arg parsers |
| c0f86a4/c0f8674/c0f1874/c0e1c3c | panics | noreturn | universal panic paths |
| bf77834 | boot_prop_getter | shared | 'vmm-present' boot property |

All externs are declared in `hv_kernel_glue.c`/`.h` with Ghidra FUN_ + address.

## boot-audit edges (from boot-audit agent, 2026-08-11)

Per the BOOT-AUDIT rule the boot path is now DECOMPILED with bodies, not just
mapped. Recreated in `osfmk/kern/startup.c` (+ `startup.h`) with the contract
header; the kernel entry is annotated in `osfmk/arm64/start.s`. These replace
the earlier documentation-only `stubbed` entries for the boot functions
(manifest: kernel_bootstrap_thread b8239e0, kernel_bootstrap b8243f0 flipped
`stubbed -> decompiled`, tree `boot-chain -> boot-audit`).

```
entry FUN_fffffe000c110000   (annotated in start.s; x0==4 panic, primary-CPU
                              Mach-O/VBAR setup, cpu-table walk by mpidr)
  ├─ (secondary / common) b 0xfffffe000b95af80   arm_cpu_init (cpu->+0xb8)
  │          or b 0xfffffe000b95b520   (alternate per-CPU boot func)
  ├─ FUN_fffffe000c114488  Mach-O header/load-command scan (primary CPU)
  ├─ FUN_fffffe000c114a34  early init-func table PTR_FUN_fffffe000c7c3dc0
  │                         then IC_IALLUIS/DSB/ISB
  └─ FUN_fffffe000c114000  panic stub (pacibsp -> FUN_fffffe000c0e11ec)

arm_cpu_init FUN_fffffe000b95af80  (startup.c)
  ├─ EL2/EL1 control (gated on DAT_fffffe0007e0da68), CPACR_EL1/CNTKCTL_EL1
  ├─ TLBI_VMALLE1IS; per-CPU boot continuation cpu->+0xb8 = b95b520
  └─ (boot CPU) FUN_fffffe000b8243f0(0)   kernel_bootstrap

kernel_bootstrap FUN_fffffe000b8243f0  (startup.c)
  ├─ FUN_fffffe000b8239e0   kernel_bootstrap_thread
  ├─ FUN_fffffe000b7fddc0   boot-continuation hook (kernel, extern)
  └─ FUN_fffffe000b812f5c   boot-continuation hook (kernel, extern)

kernel_bootstrap_thread FUN_fffffe000b8239e0  (startup.c) — boot steps in
order (each logged via FUN_fffffe000b924334 name-build + FUN_fffffe000bd31b80
kernel-thread-start record; boot-step callee in parens):
  idle_thread_create    FUN_fffffe000b8187d0   (recreated)
  sched_startup         FUN_fffffe000b818990   (recreated)
  thread_daemon_init    FUN_fffffe000b83d0ac   (recreated)
  thread_bind           FUN_fffffe000b81b388   (recreated)
  mapping_adjust        (no distinct call — inlined; log only)
  clock_service_create  (no distinct call — per-cpu kmem block; log only)
  kdp_init              FUN_fffffe000b776080   (recreated)
  hv_support_init       FUN_fffffe000b984d4c   (support-init tree) →
                          DAT_fffffe0007e41db0 = return (hv availability)
  PE_init_iokit         FUN_fffffe000c09e430   (recreated)
  mac_policy_initmach   indirect via DAT_fffffe000c68af08 (kernel fptr)
  dtrace_early_init     FUN_fffffe000b9da910   (recreated; empty body +
                          dtrace_kernel_symbol_mode boot-arg inline)
  code-signing lockdown FUN_fffffe000bdbb37c   (recreated)
  provisioning_profile  FUN_fffffe000bdbaa20   (recreated)
  trust_cache_init      FUN_fffffe000bdb9144   (recreated)
  OSKextRemoveKext...   FUN_fffffe000bf2413c   (recreated)
  machine_lockdown      FUN_fffffe000b969374   (recreated)
  PE_lockdown_iokit     FUN_fffffe000bf748bc   (recreated)
```
Recreated boot-step callees also carry manifest entries (tree=boot-audit,
status=decompiled, file=osfmk/kern/startup.c): b8187d0, b818990, b83d0ac,
b81b388, b776080, c09e430, b9da910, bdbb37c, bdbaa20, bdb9144, bf2413c,
b969374, bf748bc. Security observations from the boot path are logged in
docs/findings.md (boot-audit sections: code-signing lockdown single-gate,
keepsyms symbol retention, EL2-control/hv-availability decoupling).

## EL2 exception vector table & guest-exit path (from el2-vectors tree)

Ground truth: Ghidra FUN_ names + addresses. Decompiled in
`osfmk/arm64/hypervisor/hv_el2.c` / `hv_el2.h` (tree `el2-vectors`). The
four EL2 vector handlers are large (each inlines the full guest-state save),
so they are the handler bodies the 0x80-byte vector slots resolve to. The
exact VBAR_EL2 base was not pinned — no `msr vbar_el2` write site was found
in the hv cluster (`hv_support_init` b984d4c, EL2 detect b987fa8,
`hv_vcpu_run` hub b989a44, `hv_vcpu_save_el2_state` b988358, el2-state build
b9895b8) nor in the boot path (kernel_entry c110000, arm_cpu_init b95af80,
kernel_bootstrap b8243f0). VBAR_EL2 is established during EL2 bring-up
outside the recreated code; `hv_el2_state_build` (b9895b8) captures the live
VBAR_EL2 into the per-CPU EL2 block at +0x4120 (HV_EL2_VBAR in hv_vmm.h).

### The full guest->EL2 exit flow (all addresses verified)

```
guest (EL1) exception  -->  VBAR_EL2 vector table
  └─ handler (one of):
        FUN_fffffe000b760b94 (sync,  body b760b10-b760ed7)  reason=1
        FUN_fffffe000b760f04 (irq,   body b760f04-b76125f)  reason=3
        FUN_fffffe000b761260 (fiq,   body b761260-b7615bb)  reason=4
        FUN_fffffe000b7615bc (error, body b7615bc-b7618ff)  reason=2
        ├─ save guest EL1 state: SP_EL0/1, MDSCR_EL1, tpidr_el1/el0/ro,
        │   PAR_EL1, CSSELR_EL1, guest GPRs x2..x30, FP q0..q31, fpsr/fpcr,
        │   SVE Z/P regs (cond. on CPTR_EL2 bit20/24), elr/spsr/far/esr_el1
        │     (offsets HV_EL2_FRAME_* in hv_el2.h)
        ├─ switch to per-CPU EL2 stack (tpidr_el2), restore hypervisor
        │   EL2 ctrl regs (cptr_el2, s3_3_c13_0_5, s3_0_c1_2_4,
        │   s3_4_c15_12_0, s3_6_c15_0_4/5, mdscr_el1, tpidr_el1/el0/ro)
        ├─ verify PAC "JOP hash" of saved sysregs; on mismatch panic
        │   "Sysreg JOP hash mismatch detected (guest state corruption)"
        ├─ write exit reason to guest-state +0x4008 (HV_EL2_FRAME_EXIT)
        └─ branch -> FUN_fffffe000b761930  (common dispatch)
                    └─ zero scratch GPRs, PAC-auth return addr, eret to
                       the EL1 kernel exception handler (VBAR_EL1 =
                       0xfffffe000b75c000, set by kernel_entry). Return
                       targets (from decompiler): sync(1) -> adrp 0xed8
                       target in the b75df48..b75e04c window; irq(3) ->
                       b75df48; fiq(4) -> b75dfcc; error(2) -> b75e04c.
                       These land inside the EL1 kernel handlers
                       b75deac/b75df7c/b75e000/b75e058.
  EL1 kernel handler -> guest-exit C dispatch:
        FUN_fffffe000b96743c  (est. hv_el2_guest_esr_classify, sync path)
          ├─ ESR EC bits[31:26] dispatch:
          │     0x18 (SVC) -> exit 8, iss to state+0x4018
          │     0x1d       -> exit 0xd
          │     0x20 (IABT)-> tpidr+0x8e0 counter, fault reason 5
          │     0x24 (DABT)-> tpidr+0x8d8 counter, fault reason 1/3
          │     0x3f (SMC-ish) -> 0x80000000 (iss3) / 8+afsr1 (iss0x20)
          │                     / 7 (iss0x21) / 1 (iss 0x23..0x26)
          │     other     -> host-abort panic (c0f0fa4) if pstate bit3,
          │                 else exit 10 if bit20; EC>0x34/unmapped ->
          │                 "Unrecognized guest trap exception" panic
          └─ -> FUN_fffffe000b967768  (est. hv_el2_guest_fault, abort path)
                 ├─ reason 0x18 -> FUN_fffffe000b98f304 (kernel hw-error)
                 ├─ resolve guest IPA: FAR (EA clear, in-guest) or
                 │   FAR[11:0] | (HPFAR_EL2[31:4]<<12) -> state+0x4028
                 ├─ FUN_fffffe000b968948 (disable debug exceptions)
                 ├─ validate+vm_fault via kernel b94b450/b89988c/b9879b8
                 │   (shared-dep, stubbed); exit 6/9/5 to state+0x4008
        FUN_fffffe000b967004  (est. hv_el2_guest_irq)  — ack, timer, CNTVCT
        FUN_fffffe000b966c74  (est. hv_el2_guest_fiq)  — ack, intc vtable
  return to guest:
        FUN_fffffe000b75e468 / FUN_fffffe000b75e5cc  (eret)
          ├─ restore elr/spsr_el1, fpcr/fpsr, SVE Z/P regs from frame
          ├─ re-arm PAC key (3,0,1,0,5) + T1SZ (3,0,1,0,6,0x10001)
          └─ ExceptionReturn()  (back to the guest)
        FUN_fffffe000b75e420  (exception-exit tail shared by EL1 handlers)
        FUN_fffffe000b75e8a8  ("Preemption count negative" panic, noreturn)
```

The exit reason at state+0x4008 (1 sync / 2 error / 3 irq / 4 fiq) is read
by the `hv_vcpu_run` hub FUN_fffffe000b989a44 (vcpu-core tree) at es+0x4008
to dispatch the exit back to userland. EL1 kernel exception handlers
(b75deac/b75df7c/b75e000/b75e058) are kernel vectors (shared-dep, stubbed)
that the EL2 dispatch re-uses; the hypervisor does not install a separate
VBAR_EL1.

Edges into vcpu-core/el2-state (owned by those trees): the hub
FUN_fffffe000b989a44 calls hv_vcpu_save_el2_state (b988358),
hv_el2_state_apply (b98dd40), hv_el2_state_commit (b98ded4), and the run
prepare (b98dd04) — see the vcpu-core / el2-state sections above.

Kernel deps stubbed for this tree (never decompiled): b75deac/b75df7c/
b75e000/b75e058 (EL1 vectors), b98f304 (hw-error), b968948 (debug disable),
b94b450/b89988c/b9879b8 (guest vm_fault), b966dd8 (irq ack), b9627e0,
c0d993c. Security observations in docs/findings.md (el2-vectors sections:
unhandled EC panic, JOP-hash guest-state integrity, host-abort handling,
SVC-ISS passthrough).

## Stage-2 MMU layer (guest -> host), from hv-pmap tree (2026-08-11)

Decompiled in `osfmk/arm64/hypervisor/hv_pmap.c` / `hv_pmap.h` (tree
`hv-pmap`). The guest->host memory boundary is built on a per-owner **host
vm_map** plus a fixed **EL2 stage-2 translation table**; the map/unmap entry
points funnel into a shared core, and the stage-2 fault path drives the kernel
vm_fault family.

### Map / unmap / region core
```
hv_vm_map     FUN_fffffe000b986898  (trap-dispatch, op table idx3)
hv_vm_unmap   FUN_fffffe000b986d94  (trap-dispatch, op table idx5)
  └─► hv_vm_map_core  FUN_fffffe000b9868a8  (trap-dispatch, hv.c)
        ├─ copyin 0x28 user arg block  (FUN_fffffe000b95c144 copyin, shared)
        ├─ hv_pmap_resolve_owner FUN_fffffe000b986b34  [hv-pmap, hv_pmap.c]
        │     └─ kernel_obj_lookup FUN_fffffe000b7e0f30 (kernel, shared-dep)
        │           └─ kernel_obj_lookup_core FUN_fffffe000b78d064 (kernel)
        │     └─ kernel_refcount_inc FUN_fffffe000b8af98c (kernel, shared-dep)
        ├─ range/bounds validation: page-mask (1<<*(owner+0x44))-1, allowed
        │   window owner+0x28/+0x30, cap 0x7ffffe000000, carry-checked add
        ├─ kernel_mem_validate FUN_fffffe000b8b51c8  (vm_map_enter, shared)
        ├─ kernel_copyout    FUN_fffffe000b8b49e8  (vm_map_protect, shared)
        └─ kernel_mem_release FUN_fffffe000b8a8078 (vm_map_remove, shared)
              └─ on failure: hv_pmap_unwind FUN_fffffe000b986d34  [hv-pmap]

hv_vm_map_region FUN_fffffe000b986ff4  (trap-dispatch, op table idx17)
  └─ region rbtree (owner+0x427) + node zone FUN_fffffe000b7eb624;
     RB unlink FUN_fffffe000b9860bc (shared-utils/trap-dispatch)

hv_vcpu_map_memory FUN_fffffe000b9866d0  (vcpu-core, hv_vcpu.c)
  └─ maps guest pages via FUN_fffffe000b948ac8 / b8ada1c (kernel vm_map)
```

### EL2 translation table (the actual stage-2 page tables)
```
hv_el2_pt_alloc FUN_fffffe000b98e344  (el2-state, hv_vmm.c)
  └─ alloc 0x8000 EL2 block: L1@+0x0, L2@+0x1000, L3@+0x2000, state@+0x4000
     base stored at vm+0x4150; TLB flush FUN_fffffe000b96c6d4 (shared-dep)

hv_el2_state_build FUN_fffffe000b9895b8  (el2-state, hv_vmm.c)
  ├─ programs HCR/SCTLR/TCR/TTBR state at +0x4000.. (see hv_vmm.h)
  └─ records L2/L3 table ptrs on vm config slots 0xd/0xe
     (est. layout documented in hv_pmap.h: HV_PT_*_OFF)
```

### Stage-2 fault path (how a guest fault reaches vm_fault)
```
guest data/instruction abort (stage-2 translation fault)
  -> VBAR_EL2 vector (b760b10/b760b94 sync) -> common dispatch b761930
     -> EL1 handler -> hv_el2_guest_esr_classify FUN_fffffe000b96743c
        -> hv_el2_guest_fault FUN_fffffe000b967768   (el2-vectors, hv_el2.c)
             ├─ synthesise guest IPA: FAR[11:0] | (HPFAR_EL2[31:4]<<12)
             │   (UnkSytemRegRead(3,5,1,0,0) = HPFAR_EL2)
             └─ vm_fault family on the resolved vm (owned by el2-vectors):
                  FUN_fffffe000b94b450 / b89988c / b9879b8  (kernel, shared)
```
The vm whose stage-2 fault is resolved is the same one returned by
`hv_pmap_resolve_owner`; the HPFAR_EL2 IPA synthesis and in-guest-range checks
are documented in hv_el2.c and findings.md [el2-vectors b967768].

## FINAL OP-TABLE INDEX -> NAME MAP (op-table-id tree, authoritative)

All 19 indices of the hv mach-trap op table `PTR_FUN_fffffe0007e0d750`
(dispatcher `FUN_fffffe000b984ed8`, est. hv_available) resolved this campaign.
Ground truth = Ghidra FUN_ address; estimated names carry confidence. Indices
marked *(unid.)* are described but not matched to a public Hypervisor.framework
API (evidence + attempted matches recorded in hv.c and manifest.json).

| idx | addr       | name                  | confidence | evidence |
|-----|------------|-----------------------|-----------|----------|
| 0   | b984fd8    | hv_capabilities       | medium     | 435-byte feature/CPU-ID report (entitlement tier -> feature mask -> id_aa64* regs), copyout 0x1b3; no copyin |
| 1   | b985588    | hv_vm_create          | medium     | entitlement tier check + quota counters + alloc vm/owner |
| 2   | b985bf0    | hv_vm_destroy         | medium     | per-cpu vm teardown + refcount release |
| 3   | b986898    | hv_vm_map             | low        | op0/mode0 -> map core (b8b51c8) |
| 4   | b986d84    | hv_vm_protect         | high       | stub: dsb; w1=1(op); w2=0(mode); b core@b9868a8 -> protect (b8a8078) |
| 5   | b986d94    | hv_vm_unmap           | low        | op0/mode1 -> unmap core (b8b49e8) |
| 6   | b989040    | hv_vcpu_create        | medium     | vcpu-core (decompiled in hv_vcpu.c) |
| 7   | b9897bc    | hv_vcpu_destroy       | medium     | per-cpu vcpu teardown + EL2 AMX/SVE disable |
| 8   | b9899b0    | hv_vcpu_run           | medium     | vcpu launch via b988358 with EL2 feature-gated mask |
| 9   | b989a44    | hv_vcpu_run (hub)     | medium     | vcpu-core 16.8KB run/exit-dispatch hub (hv_vcpu.c) |
| 10  | b98e488    | hv_trap_op_10 *(unid.)| low        | per-CPU vcpu-slot flush (64-bit CPU bitmask arg, no copyin); attempted: hv_vcpu_exec, map/unmap CPU propagation, shared-mem sync |
| 11  | b986e50    | hv_vcpu_attach        | medium     | vcpu-core (hv_vcpu.c) |
| 12  | b986da4    | hv_vm_map_shared      | medium     | copyin 0x20; hv_vcpu_map_memory(b9866d0, vcpu=0); copyout 8-byte shared-region handle at +0x18 |
| 13  | NULL       | — (unused)            | —          | dispatcher: unavail err 0xfae9400f |
| 14  | b986f1c    | hv_vm_set_trap_debug  | medium     | copyin 0x18 [id,value,reg-sel]; selector 0..9; b954160 configures hardware debug regs (panics on "debug exceptions enabled in kernel mode") |
| 15  | b98e788    | hv_trap_op_15 *(unid.)| low        | guest streaming-SVE/SVCR_EL2 mode select (mode 0..3), alloc 0x4000 EL2 SVE scratch; attempted: hv_vcpu_set_vtimer_offset, hv_vcpu_set_exec_mode, set_trap_debug |
| 16  | b98e964    | hv_trap_op_16 *(unid.)| low        | SoC-feature-gated hv_el2_pt_alloc (b98e344) when vcpu opcode count > 2; attempted: hv_vcpu_get_exec_time, hv_vcpu_set_vtimer_offset |
| 17  | b986ff4    | hv_vm_map_region      | medium     | 0x34 copyin; rbtree region insert with cap/bounds check |
| 18  | NULL       | — (unused)            | —          | dispatcher: default err 0xfae94001 |

Notes:
- Indices 6/9/11 are owned by the vcpu-core tree (hv_vcpu.c); 13/18 are NULL.
- The map/protect/unmap family (idx3/4/5) all funnel through the shared core
  `FUN_fffffe000b9868a8` (hv_vm_map_core, hv_pmap-owned) dispatching on (op,mode):
  (0,0)->map b8b51c8, op==0->unmap b8b49e8, op!=0->protect b8a8078. idx4 is a
  bare branch stub (no Ghidra function) that selects protect.
- idx0 (hv_capabilities), idx10/15/16 take a value arg or copyout only (no
  guest-memory copyin beyond their fixed arg block); idx1/3/12/14/17 copyin a
  fixed user arg block of 0x1c/0x28/0x20/0x18/0x34 bytes respectively.

## structs consolidated (structs-audit tree, 2026-08-11)

The scattered structure offsets have been consolidated into single,
evidence-commented definitions (no manifest change — structs are not
functions):
- `osfmk/arm64/hypervisor/hv_vm.h` (NEW) — `hv_vm_t` (the per-VM owner block:
  refcount +0x08, base +0x88, embedded hv_vm_config +0x2088.., host map
  +0x2120, tier +0x2128, quota_cap +0x2130, region rbtree root +0x2138,
  per-cpu vcpu slots +0x2148.., tier3 flag +0x2190), `hv_vm_percpu_t` (per-CPU
  state: el2_ctrl_ptr +0x1b8, nesting +0x1c0, resource_base +0x318, bound_vcpu
  +0x4d8, cpu_id +0x518, owner +0x628, dabt/iabt counters +0x8d8/+0x8e0), and
  `hv_vm_region_node` (node[0]=vm, node[2]=start, node[3]=start+size,
  node[4]=ret, node[5..7]=rbtree links).
- `hv_vmm.h` — `struct hv_el2_state` added (template bank +0x6a8..0x780,
  active bank +0x4030..0x40c0, dirty flags +0x738.., guest-saved +0x40c0..,
  capture groups, magic/exit_reason +0x4000/+0x4008, el2_block_base +0x4150);
  the old inline `struct hv_vm` moved to `hv_vm.h` as `hv_vm_t`.
- `hv_vcpu.h` — `hv_vcpu_t` completed/corrected (container +0x0, guest_mem
  +0x8, container copy +0x88, el2_state +0xb0, amx_enable +0xb8, vmm_ctx
  +0xc0, el2_extra +0xd0, generation +0xd8, attach_id +0xe0, attach_obj +0xf0,
  vcpu_id +0xf8).
- `hv.h` — `hv_trap_record_t` left as-is (already complete: +0x10 copyin_flag,
  +0x28 copy helper, +0x30 copyout_flag, +0x38 arg_size, +0x48 handler).
See `docs/audit.md` for the consolidated security audit synthesis.

## Guest hypercall (hvc) ABI — observed interface (tree hvc-abi)

Constants live in `osfmk/arm64/hv_hvc.h`; this section is the prose map.

Guest -> host hypercall path: guest `hvc` at EL0/EL1 traps to the EL2 vectors
(hv_el2.c), guest EL1 state is saved to el2_state (base = vcpu->el2_state),
and the run hub (`FUN_fffffe000b989a44`, est. hv_vcpu_run) dispatches the exit.

Two dispatch levels:
1. **Guest ESR classifier** `FUN_fffffe000b96743c` (hv_el2_guest_esr_classify,
   full body in hv_el2.c): decodes ESR_EL1 EC = (esr>>26) & 0x3f and writes
   raw ESR low 32 bits to es+0x4010, the ISS (`esr & 0x1ffffff`) to es+0x4018
   (SVC), and an exit-code word to es+0x4008. Standard ECs here: SVC 0x18->8,
   0x1d->0xd, IABT 0x20->fault5, DABT 0x24->fault1/3, SMC-ish 0x3f->0x80000000/
   7/8/1 by ISS. **HVC is NOT a handled class here** — it falls through to the
   host-abort / "Unrecognized guest trap" panic path.
2. **Run hub dispatch** (hv_vcpu_run case 0x8 -> `FUN_fffffe000b98a08c`, the
   inline ESR classifier `hv_esr_classify`): reads es[0x4018] (the exception
   ISS/immediate) into a scratch GPR and decodes the full (class|imm) token by
   a large compare tree (verified in the 3958-instruction disassembly): HVC64
   0xc3000000, HVC-hint 0xc1000000, IABT-channel 0x83000000, SVC/VM-op
   0xc6000000, plus the debug/arch 0x24-0x3fxxxxxx families.  HVC64 dispatch is
   gated: `imm<=6` AND `(container_enable_mask & (1<<imm)) != 0`.

Observed ESR-class tokens (run-hub family, UNVERIFIED labels — see hv_hvc.h):
- `0xc3000000` est. HVC(64-bit)  (EC bits[31:26]=0x30)  — imm 3..6 dispatched
- `0xc1000000` est. HVC(32-bit)/hint (EC bits[31:26]=0x30) — imm 1..0xf
- `0x83000000` est. IABT-channel (EC bits[31:26]=0x20) — imm 0xfeff/0xff01/0xff03
- `0xc6000000` est. SVC/VM-op   (EC bits[31:26]=0x31)  — imm 0x10..0x1a -> vm_op_dispatch

Cross-check: ARM-standard EC for these classes are SVC64 0x18 / HVC64 0x19 /
SMC64 0x1b / IABT-lower 0x21 / DABT-lower 0x24. The 0xc3-family tokens do NOT
match these, so they are an internal hypervisor class encoding (e.g. a tag bit
OR'd with EC<<26), not raw ESR_EL1 — recorded as observed, no claim.

**Known / unknown of the ABI (deepened by TreeRunHubDeep + targeted disasm):**
- [known] The hypercall SELECTOR is the `hvc #imm` immediate (ISS, es+0x4018),
  NOT a general-purpose register. The HVC64 case (0xfffffe000b98a76c) compares
  the ISS against 0xc3000003/0xc3000004/... (`mov/movk w9,#0xc300`; `subs
  xzr,x8,x9`) — no x16/x0 dispatch.
- [known] Enable gating: HVC64 hypercalls dispatch only if `imm<=6` AND the
  per-VM enable mask bit `(1<<imm)` is set (disasm `ldr x9,[x21,#0x1350]`,
  `lsl x10,x10,x8`, `and x9,x9,x10`, `cbz`); reconstruction noted the mask at
  container+0x2130 (offset unconfirmed).
- [known] Observed hypercall numbers: HVC64 imm 3..6; HVC-hint imm 1..0xf;
  IABT-channel imm 0xfeff/0xff01/0xff03; SVC/VM-op imm 0x10..0x1a (routed to
  hv_vm_op_dispatch b98e020 / hv_vcpu_slot_op b98e12c / per-slot map b9866d0,
  gated by container opcode count vm+0x2128, requires no attach id and no
  pending SPSR bit).
- [known] Args are read from the guest's SAVED GPR/vector registers in the EL2
  save frame (es+0x8..0x28; q0/q1 from sp+0x50/0x60; blob at sp+0x80) — x0-x3 /
  q0-q1 style GPR/vector passing, not a dedicated hypercall-arg register.
- [partial] Return: the emulated result is written back into the guest
  save-frame GPR region (es+0x8/+0x18/+0x28 = guest x0/x1/x2 slots) and the
  synthetic sentinel 0xfedefacafeadfad9 is injected there. The sentinel's exact
  role (return/status code in x0 vs. emulation-completed marker) is UNVERIFIED
  (the reconstruction records both readings).
- [unknown] Full 16-bit `hvc #imm` -> operation map beyond the observed numbers,
  per-operation arg->register layout, and exact guest error-code convention.
  Not derivable from the reconstructions; not fabricated.

Kernel-issued hvc: NONE observed in the recreated code. Every hvc/eret mention
is guest->host (traps into the run hub) or an ERET back to the guest
(return-to-guest paths b75e468/b75e5cc/b75e420). No kernel-side hvc to an
SPMC/SPTM world was found in the hypervisor closure; a whole-program
`search_instructions hvc` was not run (timeout, see kernelcache.md), so no
kernel hvc outside the closure is asserted either way.


## Ghidra DB annotations (tree ghidra-rename)

Ghidra DB annotated with estimated names from manifest: 73 decompiled functions renamed (FUN_* -> estimated_name via batch_rename_function_components); 1 skipped (b986d84 hv_vm_protect — bare branch stub, no Ghidra function symbol). No name conflicts encountered. Collision-fix names applied: b9897bc -> hv_vcpu_destroy_trap, b9899b0 -> hv_vcpu_run_trap.

## vmapple-deep conclusion (2026-08-11, from vmapple-deep agent)

### The vmapple surface is genuinely SMALL — no separate nested-VM vmm

Deep-dive verdict: this kernelcache has NO production nested-VM/vmapple vmm
module. The vmapple service is the IPC kobject handler + entitlement gate +
object-registry glue already mapped. Evidence (targeted MCP, all verified):

| # | Search / call | Result |
|---|---|---|
| 1 | `search_strings("vmapple")` | **1 hit TOTAL** in the 121 MB binary: the entitlement `com.apple.private.hypervisor.vmapple` (fffffe000707250e). A real vmapple module would carry many vmapple-named strings (trap/panic/log names); none exist. |
| 2 | `search_strings("hypervisor")` | 7 hits, all already mapped (3 entitlements, IKOT_HYPERVISOR, "hypervisor guest", live-dump sysctl, "Hypervisor info"). |
| 3 | `get_xrefs_to(vmapple entitlement)` | exactly 3 referencers, all owned: b985588 (hv_vm_create), b985ae4 (hv_entitlement_tier), b96c158 (kernel exec flags). |
| 4 | `get_function_callees(b985e38)` | all shared kernel deps (b78fb24, b793cf4, b7e0d8c, b7f0afc, b7f1e80, b862b6c, b866ec4, b8afa78, c0f8674, c0f86a4) + owned hv (b98533c, b9860bc). No vmm. |
| 5 | `get_function_callees(b985ae4)` + callers | only current_task + current_cpu_datap; **single caller b984fd8 (hv_capabilities)**. |
| 6 | region fffffe000c7a9a00..c7aa000 | generic kernel name->value registry (SPTM/DART/power names). Only hypervisor records: "hv" (c7a9e68) + IKOT_HYPERVISOR (c7a9f28). |
| 7 | `get_xrefs_to(IKOT string 7072550)` / `(b985e38)` | single data ref from IKOT record; handler referenced only by generic kernel IKOT kobject dispatch table (d20ad7c + c7a9f30), NO code caller. |
| 8 | hypervisor cluster BFS | no "nested"/secondary-guest state beyond the entitlement tier gate. |

### IKOT_HYPERVISOR kobject record (final form)
```
fffffe000c7a9f28  { type_id = 0x12d (301), name_ptr = 7072550 ("IKOT_HYPERVISOR"),
                    handler = FUN_fffffe000b985e38 }
```
- Single-handler kobject type in the generic kernel IKOT dispatch table
  (fffffe000c7b3340..7b37e0 records {name_ptr, registry_ptr, count}). The
  handler (b985e38) is invoked only via kernel kobject dispatch, never by a
  direct code call.
- The name->value registry also holds "hv" (fffffe000c7a9e68, value refs
  DAT_fffffe000c62c0c0 the hv lock) and the type-name
  "hv_vm_t.hv_vm_percpu_t" (fffffe0007071e74, data ref c7a9ef8 only).

### Nested-VM capability is the SAME Hypervisor.framework service
The vmapple entitlement only elevates `hv_entitlement_tier` (b985ae4) to
tier 3, which widens the capability set (hv_capabilities b984fd8) exposed by
the shared mach-trap op table PTR_FUN_fffffe0007e0d750 (dispatcher b984ed8)
already owned by trap-dispatch / vcpu-core / el2-state / hv-pmap. There is no
distinct vmapple trap set, panic path, or vmm function cluster.

Manifest: b985e38 + b9860bc flipped to `tree: vmapple-deep`; no new vmapple
functions added because the deep-dive found none beyond the 3 already
documented (b985e38, b985ae4 [entitlements-owned], b9860bc).

## guest-fault tree (from guest-fault agent, 2026-08-11) — guest fault path decompiled

Per the FULL-AUDIT rule, the direct vm_fault-family callees of the guest fault
handler are now recreated with bodies (tree `guest-fault`, file
`osfmk/arm64/hypervisor/hv_el2.c`), replacing the earlier `stubbed` entries.

### The full guest memory-fault path (all addresses verified)

```
guest data/instruction abort (stage-2 translation fault)
  -> VBAR_EL2 sync vector (b760b10) -> common dispatch b761930
     -> EL1 kernel handler -> hv_el2_guest_esr_classify FUN_fffffe000b96743c
        (EC decode: SVC 0x18 -> exit 8; 0x1d -> exit 0xd; IABT 0x20 ->
         fault reason=ISS which=5; DABT 0x24 -> reason=ISS which=1/3;
         SMC-ish 0x3f -> 0x80000000/7/8/1; unhandled -> host-abort panic
         c0f0fa4 or "Unrecognized guest trap exception" panic c0e11ec)
        -> hv_el2_guest_fault FUN_fffffe000b967768   [guest-fault, hv_el2.c]
             |-- reason 0x18 (SVC/SError) -> FUN_fffffe000b98f304 (hw error)
             |-- resolve guest IPA:
             |     FAR direct (EA clear + in-guest) or
             |     FAR[11:0] | (HPFAR_EL2[31:4] << 12) -> state+0x4028
             |-- FUN_fffffe000b968948 (disable debug exceptions)
             |-- hv_el2_guest_pte_check FUN_fffffe000b94b450   [guest-fault]
             |     stage-2 walk: 0 = present+correct (no fault),
             |     5 = not-present, 2 = wrong attr/perm
             |     -> if 0: r=5 (resume)
             |-- kernel_vm_fault FUN_fffffe000b89988c   [guest-fault]
             |     XNU vm_fault on the guest vm (faultarg {2,0,0,0,0});
             |     err 0xe -> exit 9, 5 -> panic "vm_fault() KERN_FAILURE",
             |     0 -> exit 5 (resume)
             |     -> on failure: hv_el2_guest_fault_retry FUN_fffffe000b9879b8
             |          [guest-fault]: region rbtree (vm+0x427) lookup +
             |          fault-post (b7e16f0); success -> PC+=4, r=5
             \-- exit code -> state+0x4008 (5 resume / 6 out-of-range / 9 err)
```
Edges re-verified: `get_function_callees(b967768)` includes b94b450, b89988c,
b9879b8 (the recreated family) plus b98f304, b968948, c0d993c (stubbed
kernel). The vm resolved by the stage-2 fault is the same one returned by
`hv_pmap_resolve_owner` (b986b34, hv-pmap tree) — the fault path and the
map/unmap layer share the per-owner host vm_map.

### FULL-AUDIT boundary (this tree)
- RECREATED with bodies (hv_el2.c, tree guest-fault, manifest decompiled):
  b967768, b94b450, b89988c, b9879b8.
- STUBBED externs (2+ levels into XNU; manifest shared-dep, kept as externs
  in hv_el2.h): vm_fault_enter b89d5f8, b89de34, b94c554, c0d7b94/c0d7c20
  (page-validate / paddr-type), b94abbc (memattr resolve), lock bits
  b7f8ce0/b7f8d9c/b7f8e50, TLB b96c6d4, region lock b78fd40, fault-post
  b7e16f0, release b78cc20, LORelease, panics c0e11ec/c0f1874/c0f8674.
- ESR classifier b96743c verified full-faithful (corrected argument order
  reason/which to hv_el2_guest_fault, DABT sub-condition `< 0xfffffffd`,
  pstate bit20-first ordering). Security observations in findings.md
  (guest-fault sections: HPFAR_EL2 IPA synthesis, fault-driven fault
  injection / PC-advance retry, 32-bit stage-2 index truncation, guest-
  induced KERN_FAILURE host panic).

## kernel-iface edges (from kernel-iface agent)

### Panic / coredump "docommand" table (dump-request path, DATA)
The strings `hypervisor guest` (`fffffe00070c5886`) and `Request that the
hypervisor take a live kernel dump` (`fffffe00070c58af`) are the DESCRIPTION
(+0x18) text of two panic/coredump `docommand` command entries, not function
code. get_xrefs_to on each string returns a single DATA slot inside the table:
- `0x7e34f48` = entry "hvg"       → desc `hypervisor guest`     @ +0x18 (0x7e34f60)
- `0x7e34f98` = entry "trigger_kernel_coredump"
                                  → desc `Request that the hypervisor take a
                                    live kernel dump`           @ +0x18 (0x7e34fb0)
Entry layout (0x50-byte records, chained to list head `0x7e34f18`):
name@+0x00, value_or_func@+0x08, help@+0x10, description@+0x18, flags@+0x20
(=1), chain@+0x28, pad@+0x30, mask@+0x38. The +0x08 code pointer of
trigger_kernel_coredump (`0xfffffe000b8f9f08`) falls INSIDE
`FUN_fffffe000b8f91b8` (a large VM contiguous-page function) — it is NOT a
clean docommand entry point. The actual live-dump request is issued by shared
kernel panic/coredump code (stubbed). A first, VM-statistics `docommand` list
is headed at `0x7e34c40` (enumerated by trap-dispatch). Reconstructed as
read-only data in `osfmk/kern/hv_kernel_iface.c` (tree kernel-iface).

### hv presence consumers (complete xref closure on the availability flag)
`get_xrefs_to(DAT_fffffe0007e41db0)` returns exactly four references — the
complete consumer set:
```
DAT_fffffe0007e41db0  (hv_available_flag)
  ├─ [WRITE] fffffe000b823ee4  kernel_bootstrap_thread
  │        ← stores hv_support_init() (b984d4c) return = presence
  ├─ [READ]  fffffe000b984f08  hv_available (b984ed8)
  │        ← clear ⇒ every hv mach-trap returns 0xfae9400f
  ├─ [DATA]  fffffe0007e2bda8  hv_support   boot-arg descriptor (value
  │        │                    storage target = flag address)
  └─ [DATA]  fffffe0007e41dd0  hv_disable   boot-arg descriptor (value
                                   storage target = flag address)
```
Presence is ALSO reported through the IOKit `vmm-present` property by
`hv_vmm_present` (`FUN_fffffe000be39fd0`, trap-dispatch): it calls
`FUN_fffffe000bf77834("vmm-present", &local, 4)` (boot property getter,
entitlements tree) and copies the normalized 0/1 out via the trap record's
+0x28 helper. No hibernation / power-management / vm subsystem reads the
availability flag (only the four refs above). Files: `osfmk/kern/hv_kernel_iface.c`
+ `.h` (tree kernel-iface).


## hv-deps Sys touch-set (hv_glue_audit_sys.c) — call-graph edges

Recreated per FULL-AUDIT (tree hv-deps, category Sys). `→` marks a direct call
from a recreated body to a stubbed extern (2+ levels into XNU); sibling edges
(both recreated in the same file) are marked `↔`.

- `fffffe000b96c6d4` kernel_tlb_flush → `fffffe000b7a56d4` (flush core)
- `fffffe000b94172c` kernel_preempt_dec → `fffffe000b7f8ce0` (lock bit wait),
  `fffffe000b7f8ed0` (lock bit release), `fffffe000b815288` (preempt adjust),
  `fffffe000b83f58c` (thread preempt dec), `fffffe000b944b00` (deferred cb)
- `fffffe000b94abbc` kernel_memattr_resolve → `fffffe000c0fb940` (PV lookup),
  `fffffe000c0d84b0` (attr trace commit), `fffffe000c0e11ec`/`fffffe000c0f1874`
  (panics); ↔ `fffffe000b96c6d4` (TLB flush, tail)
- `fffffe000bd30528` kernel_trace → `fffffe000bd310e8` (kernel_trace_core, both
  branches; recreated sibling)
- `fffffe000bd310e8` kernel_trace_core → `fffffe000bd2d774` (buffer acquire),
  `fffffe000b7f89cc`/`fffffe000b7f8a60` (trace lock), `fffffe000b968948`
  (restore preempt), `fffffe000b9257c4` (trace emit), `fffffe000b8563f8` (reg
  write), `fffffe000c0e11ec`/`fffffe000c0f1874` (panics); ↔ `fffffe000b96c6d4`
- `fffffe000c09cbf0` kernel_boot_arg_get → `fffffe000b760950` (strncmp),
  `fffffe000b7608d0` (strlen), `fffffe000c09d008` (memfill), `fffffe000c09d080`
  (value parse), `fffffe000c09d2b0` (isdigit cb)
- `fffffe000c09c084` kernel_dt_node_lookup → `fffffe000b923854` (strcmp),
  `fffffe000c09c4b8` (next prop), `fffffe000c0e0620` (stack-check fail),
  `fffffe000c0e11ec` (panic); ↔ `fffffe000c09c31c` (dt_prop_get)
- `fffffe000c09c31c` kernel_dt_prop_get → `fffffe000b923854` (strcmp),
  `fffffe000c0e11ec` (panic)
- `fffffe000b866ec4` per_cpu_base → `fffffe000c0eae44` (zone_require_ro panic),
  `fffffe000c0eb104` (tro panic); body reconstructed from disassembly (LOW
  confidence, see manifest)
