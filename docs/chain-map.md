# chain-map.md — Boot chain and hypervisor-tied function map

Ground truth: Ghidra `FUN_*` names + addresses from `kernelcache.arm64.kc`
(image base `fffffe0007004000`). All human names are estimates with
confidence. Updated by the decompilation agents as they discover edges.

## Boot chain (verified edges)

```
FUN_fffffe000b8243f0  (est. kernel_bootstrap)
  └─ calls → FUN_fffffe000b8239e0  (est. kernel_bootstrap_thread)
        ├─ boot step log "hv_support_init" (string @ fffffe0007059587)
        ├─ calls → FUN_fffffe000b984d4c   (est. hv_support_init)
        │     ├─ currentel == EL2 (0x8) check
        │     ├─ "apple-isa-vm-quota" device property (via FUN_fffffe000c09c084/c09c31c)
        │     ├─ "hv_apple_isa_vm_quota" boot-arg (via FUN_fffffe000c09cbf0)
        │     ├─ calls → FUN_fffffe000b987fa8  (est. hv_el2_feature_detect)
        │     │     ├─ reads EL2 sysregs UnkSytemRegRead(3,4,0xc,0xb,1), (3,4,0xf,0xc,6)
        │     │     ├─ reads aidr_el1, id_aa64pfr0_el1, id_aa64pfr1_el1
        │     │     └─ writes DAT_fffffe0007e0d800 (EL2 features),
        │     │          DAT_fffffe0007e0d818/0x1c/0x1e (SoC/feature flags)
        │     └─ returns 1 → stored to DAT_fffffe0007e41db0 (hv availability)
        └─ ... rest of kernel boot (not recreated — shared kernel)

FUN_fffffe000b984ed8  (est. hv_available) reads DAT_fffffe0007e41db0
FUN_fffffe000be39fd0  (est. hv_vmm_present, mach trap handler)
  └─ calls FUN_fffffe000bf77834("vmm-present", …)  (boot property getter)
```

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
| `fffffe000b98dd40` | hv_el2_features_read | el2-state | reads DAT_fffffe0007e0d800 |
| `fffffe000b98dd04` | hv_* (est.) | el2-state | callee of hub |
| `fffffe000b98ded4` | hv_* (est.) | el2-state | callee of hub |
| `fffffe000b98e020` | hv_* (est.) | el2-state | callee of hub |
| `fffffe000b98e12c` | hv_* (est.) | el2-state | callee of hub |
| `fffffe000b98e344` | hv_* (est.) | el2-state | callee of hub |

## Trap table & dispatchers

- Mach trap table region: `fffffe0007e35080` (record layout ≈40–56 bytes;
  fields observed: name ptr, handler ptr, string ptrs, arg size, copyin/copyout
  helpers at record +0x28). `hv_vmm_present` name @ `fffffe00070c592c` → handler
  `FUN_fffffe000be39fd0`.
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

## Correction log

- 2026-08-11: the four strings at `fffffe00070c5fda/ff2/6010/6033` are
  `vm_*` subsystem names (from the `vm_create` byte-pattern hits), not
  `hv_vm_create` trap names. Recorded as a table of VM names; trap-dispatch
  tree uses table record handlers instead.
