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
idx0  b984fd8  hv_trap_op_0        idx10 b98e488 hv_trap_op_10
idx1  b985588  hv_vm_create        idx11 b986e50 (vcpu-core)
idx2  b985bf0  hv_vm_destroy       idx12 b986da4 hv_trap_op_12
idx3  b986898  hv_vm_map           idx13 NULL
idx4  b986d84  hv_trap_op_4 (stub) idx14 b986f1c hv_trap_op_14
idx5  b986d94  hv_vm_unmap         idx15 b98e788 hv_trap_op_15
idx6  b989040  (vcpu-core)         idx16 b98e964 hv_trap_op_16
idx7  b9897bc  hv_vcpu_destroy     idx17 b986ff4 hv_vm_map_region
idx8  b9899b0  hv_vcpu_run         idx18 NULL
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

### hv-deps direct-kernel-callee conversion (scope decision 2026-08-11)
Direct kernel callees of the vmapple/hv code were evaluated for body recreation:
- CONVERTED (body): FUN_fffffe000b8663e8 (current_task) -> hv_kernel_glue.c
- LEFT as externs (universal XNU core used by the whole kernel; recreating them
  is recreating core XNU, out of scope): b866ec4 (per-CPU getter, decompiler
  panic-stub), b7f0afc/b7f1e80 (lck_mtx_lock/unlock on hv lock 0xc62c0b8),
  b8afa78 (os_release), b793cf4 (zfree), b862b6c (refcount dec),
  b78fb24 (waitq validate), b7e0d8c (object lookup 0x2d). All documented as
  externs in hv_kernel_glue.c with Ghidra addresses. Reported to Main; a future
  branch may recreate the XNU lock/alloc core if desired.

## entitlements tree (hv_entitlements.c)

### Entitlement/capability chain (op-table index 0, hv_trap_op_0 = b984fd8)
```
FUN_fffffe000b984fd8 (hv_trap_op_0, trap-dispatch)
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
