# kernelcache.md — Target facts

Target of this branch: the macOS hypervisor, recreated from the production
kernelcache decompiled in Ghidra.

## Binary facts (verified 2026-08-11)

- Program: `kernelcache.arm64.kc`
- Executable path: `/private/tmp/kernelcache.arm64.kc`
- Architecture: `AARCH64:LE:64:AppleSilicon`, compiler `default`
- Image base: `fffffe0007004000`
- Memory size: 120,930,304 bytes (5337 memory blocks)
- Functions: 244,284 (symbols stripped — all names are `FUN_*`)
- Kernel version string (at `fffffe0007045595`):
  `Darwin Kernel Version 25.5.0: Tue Jun  9 22:28:17 PDT 2026; root:xnu-12377.121.10~1/RELEASE_ARM64_T8142`

## Ghidra connection recipe

1. Confirm instance: write `{}` to `xd://mcp__ghidra_list_instances`.
   (`server_status` reports `connected:false` spuriously — trust `list_instances`.)
2. Connect: write `{"project":"kernelcache"}` to `xd://mcp__ghidra_connect_instance`
   (198 tools register on connect).
3. Confirm program: `xd://mcp__ghidra_list_open_programs` → `kernelcache.arm64.kc`
   must be current.

## MCP workflow facts

- Small targeted calls work: `get_function_by_address`, `get_function_callees`,
  `get_function_callers`, `decompile_function`, `get_xrefs_to` (one address),
  `search_strings`, `read_memory` ≤ 256 bytes, `analyze_data_region`, `search_functions`.
- Whole-program scans time out at 30 s: `search_instructions` (e.g. `msr el2`,
  `hvc`), large `read_memory`. Only run instruction searches inside an
  already-identified function via the `function` param, or after the closure is known.
- On any timeout: retry once, then split the request.

## Hypervisor anchors

### Strings (address → value)

| Address | Value |
|---|---|
| `fffffe0007059587` | `hv_support_init` (boot log name) |
| `fffffe00070725dd` | `hv_vcpu.c` (source-file string, panic paths) |
| `fffffe0007072550` | `IKOT_HYPERVISOR` |
| `fffffe000707250e` | `com.apple.private.hypervisor.vmapple` |
| `fffffe0007072533` | `com.apple.private.hypervisor` |
| `fffffe00070724f0` | `com.apple.security.hypervisor` |
| `fffffe00070b84d5` | `hv_support` (boot-arg) |
| `fffffe00070b84e0` | `hv_disable` (boot-arg) |
| `fffffe00070c592c` | `hv_vmm_present` |
| `fffffe0007071e5e` | `hv_apple_isa_vm_quota` |
| `fffffe0007071e74` | `hv_vm_t.hv_vm_percpu_t` |
| `fffffe00070c5886` | `hypervisor guest` |
| `fffffe00070c58af` | `Request that the hypervisor take a live kernel dump` |

### Functions (address → what we established)

| Address | Established identity |
|---|---|
| `fffffe000b8239e0` | kernel bootstrap thread (logs `"hv_support_init"` boot step; calls `fffffe000b984d4c`; stores return to `fffffe0007e41db0`) |
| `fffffe000b984d4c` | `hv_support_init` (EL2 check, `apple-isa-vm-quota` property, `hv_apple_isa_vm_quota` boot-arg, calls `fffffe000b987fa8`, returns 1) |
| `fffffe000b987fa8` | EL2 feature/SoC detection (EL2 sysreg reads, `aidr_el1`, `id_aa64pfr0/1`; writes `fffffe0007e0d800`, `fffffe0007e0d818/1c/1e`) |
| `fffffe000b984ed8` | reads hv availability global `fffffe0007e41db0` (likely `hv_vmm_present`/`hv_available`) |
| `fffffe000b9895b8` | EL2 register state builder (writes per-CPU EL2 state at `param_2+0x4000`…; EL2 sysreg reads; refs `fffffe0007e0d800`, `fffffe0007e0d81e`, `fffffe0007e0da68`, `fffffe0007e31628`) |
| `fffffe000b989a44` | large `hv_vcpu.c`-linked function (16.8 KB; **decompiler fails**: `Unable to find unique hash for varnode`) |
| `fffffe000b98dd40` | reads EL2 features global `fffffe0007e0d800` |
| `fffffe000bda3ca8` | generic trap argument-munger from the `vm_create` trap table entry |

### Globals (xrefs enumerate "everything tied to the hypervisor")

| Address | Meaning |
|---|---|
| `fffffe0007e0d7f0` | quota (written by `hv_support_init`) |
| `fffffe0007e0d800` | EL2 features (written by EL2 detect) |
| `fffffe0007e41db0` | hv availability flag (written by bootstrap from `hv_support_init` return) |
| `fffffe000c7a9f28` | data ref to `IKOT_HYPERVISOR` — IPC kobject ops |
| `fffffe0007e2bda8` / `fffffe0007e2bdb8` | data refs to hv globals / boot-arg strings |

### Trap table

- Table region: `fffffe0007e35880` (40-byte repeating entries).
- Name pointers: `fffffe00070c5fda`, `fffffe00070c5ff2`, `fffffe00070c6010`, `fffffe00070c6033`.
- Registered munger: `fffffe000bda3ca8` — generic argument munger; the real trap
  handlers sit behind the entry's function pointers (decompile the munger to learn
  the entry layout, then follow the handler pointers).
