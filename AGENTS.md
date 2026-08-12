# AGENTS.md — Decompilation contract

Every agent working in this repo MUST read this file first. It defines the
rules for decompiling the macOS hypervisor out of `kernelcache.arm64.kc` in
Ghidra and writing the recreation into this tree.

## Ground truth

- Ground truth is the Ghidra `FUN_*` name + address. **Estimated names are
  guesses** — never assert an identity as fact.
- Every estimated name carries a `confidence`: `high` (strong evidence:
  boot chain, trap registration, matching strings), `medium` (inferred from
  callers/callees), `low` (shape-only guess).
- The manifest (`docs/manifest.json`) and `FUN_*` comments are the source of
  truth, not the file layout.

## Ghidra usage (mandatory)

1. Connect once at session start:
   - write `{"project":"kernelcache"}` to `xd://mcp__ghidra_connect_instance`
   - confirm with `xd://mcp__ghidra_list_instances` (ignore `server_status`).
2. Use small, targeted calls only:
   `get_function_by_address`, `get_function_callees`, `get_function_callers`,
   `decompile_function`, `get_xrefs_to` (one address), `search_strings`,
   `read_memory` ≤ 256 bytes, `analyze_data_region`, `search_functions`.
3. NEVER run whole-program `search_instructions` or `read_memory` > 256 bytes
   (30 s timeouts). Instruction searches are allowed only inside an already
   identified function via the `function` param.
4. On a 30 s timeout: retry once, then split the request (smaller `limit`,
   one function at a time, narrower scope).

## Claim protocol

- Before decompiling an address not already in `docs/manifest.json`, append an
  entry `{"status":"claimed","tree":"<tree>"}` plus the known fields.
- NEVER modify an entry whose `status` is `claimed` or `decompiled` by another
  tree. If an address you need is claimed by another tree, leave it and note it
  in your own `notes`.
- Only the `shared-utils` tree may fill `osfmk/arm64/hypervisor/hv_internal.h`.
- After finishing a function: write the code, then flip the manifest entry to
  `status:"decompiled"` and fill `file`, `estimated_name`, `confidence`, `notes`.
- Manifest edits: read the current file, apply your change, write the whole file
  back. Do not leave the file in an invalid JSON state at any point.

## Code output contract

File header (every file):

```c
/* Recreated from kernelcache.arm64.kc (xnu-12377.121.10 RELEASE_ARM64_T8142, image base fffffe0007004000). Ground truth: Ghidra FUN_ names + addresses; all names are estimates. */
```

Function header comment (every function — template):

```c
/* FUN_fffffe000b984d4c @ 0xfffffe000b984d4c   (est. hv_support_init)
 * Ghidra: undefined8 FUN_fffffe000b984d4c(void)
 * <2-4 English sentences: purpose, inputs, outputs, side effects>
 * Confidence: high|medium|low
 * Notes: <Ghidra artifacts: DAT_/string refs, UnkSytemRegRead(op0,op1,CRn,CRm,op2)
 *   encodings, decompiler warnings such as "Removing unreachable block"> */
```

Rules:
- Keep the logic faithful to the decompile. Rename locals/params meaningfully.
- **English-first is mandatory on FIRST write**: function bodies must use
  meaningful English identifiers (locals, params, globals). Raw Ghidra
  identifiers (`uVar4`, `local_88`, `DAT_fffffe...`, `FUN_fffffe...` as a code
  identifier) in a body are a DEFECT and fail acceptance. Use the shared
  global naming table in `osfmk/arm64/hypervisor/hv_internal.h` for globals
  (add a named extern there when a global is missing).
- For every unresolved artifact keep an inline comment with its exact Ghidra
  name and address: `DAT_fffffe0007e0d800 /* EL2 features */`,
  `FUN_fffffe000b987fa8 /* est. hv_el2_feature_detect */`.
- EL2 sysreg reads stay literal:
  `UnkSytemRegRead(3,4,0xc,0xb,1) /* op1=4 ⇒ EL2; register identity unverified */`.
- Shared-kernel dependencies are declared as externals in headers with a
  one-line note; NEVER decompile them:
  `extern void *kalloc(size_t); /* kernel, not recreated */`.
- FULL-AUDIT RULE (branch scope, per maintainer): kernel functions that the
  hypervisor calls DIRECTLY (its touch set — copyin/copyout, locks, alloc/free,
  refcount, boot-arg/property getters, per-cpu access, panic, messaging) ARE
  recreated with bodies into `osfmk/arm64/hypervisor/hv_kernel_glue.c` /
  `hv_kernel_glue.h` (tree `hv-deps`), each with the standard function header
  comment and a note that it is kernel code recreated for audit. Their own
  callees (2+ levels into the kernel, e.g. copyin's fault path) remain stubbed
  externs — that is the audit boundary; the whole-kernel closure is out of
  scope. When you stub a direct callee of hypervisor code, add it to the
  manifest with `category:"shared-dep"` and `tree:"hv-deps"` so the hv-deps
  sweep picks it up.
- BOOT-AUDIT RULE (branch scope, per maintainer): the boot path IS audited
  (decompiled with bodies), not just mapped. Owned by tree `boot-audit`
  (files `osfmk/kern/startup.c` / `startup.h` for kernel_bootstrap and
  kernel_bootstrap_thread and their direct boot-step callees; the kernel entry
  `fffffe000c110000` and `arm_cpu_init` `fffffe000b95af80` are reconstructed
  with bodies or annotated disassembly in `osfmk/arm64/start.s`).
  Boot-step callees of `kernel_bootstrap_thread` (`fffffe000b8239e0`) such as
  idle_thread_create, sched_startup, thread_daemon_init, thread_bind,
  mapping_adjust, clock_service_create, kdp_init, PE_init_iokit,
  mac_policy_initmach, dtrace_early_init, code-signing lockdown,
  provisioning_profile_init, trust_cache_init, OSKextRemoveKextBootstrap,
  machine_lockdown, PE_lockdown_iokit, hv_support_init are recreated into
  `osfmk/kern/startup.c` (hv_support_init stays in the hypervisor module).
  Deeper kernel machinery those steps call (scheduler/VM/IOKit internals)
  stays stubbed externs — same audit boundary as hv-deps.
- If the decompiler fails, write assembly-level notes + partial reconstruction,
  set `status:"decompiled"`, `confidence:"low"`, and record the fallback used.

## Decompiler fallbacks (fixed order)

1. `Unable to find unique hash for varnode` (known on `fffffe000b989a44`):
   a. `set_function_prototype` with a guessed signature, retry `decompile_function`.
   b. `analyze_function_complete`.
   c. `disassemble_function` + `get_function_pcode` + decompile the callees.
   Record which fallback was used in `notes`.
2. MCP timeout: retry once, then split the request.
3. Handler pointer resolves to a generic dispatcher: decompile the dispatcher
   once (in the `trap-dispatch` tree), then follow its indirect targets. Do not
   recreate the dispatcher in every tree.

## House rules

- Never run formatters, linters, or project-wide test suites.
- Append discovered call-graph edges to `docs/chain-map.md` with both addresses.
- Work only in your assigned files + `docs/manifest.json` + `docs/chain-map.md`.

## Security findings log (mandatory)

Every agent MUST log security-relevant observations noticed during
decompilation into `docs/findings.md` (append-only; read the file, add your
entries, write it back — do not edit others' entries). Each entry:

```markdown
## [<tree>] <address> <estimated_name>
- **Observation**: <what you noticed: unchecked index/bounds, missing
  validation, unverified copyin length, EL2 register not restored, refcount
  anomaly, shared-state race, weak privilege check, odd constant, etc.>
- **Evidence**: <Ghidra facts: instruction/offset/global/call, e.g. "no
  bounds check on idx before `*local + idx*0x80 + 0x80` write in hv_vcpu_create">
- **Severity (hypothesis)**: informational | low | medium | high
- **Confidence**: high | medium | low   (how sure you are the observation is real)
```

Rules: label severity as a *hypothesis*, never a claim; no entry without
Evidence; if you noticed nothing suspicious in a function, say nothing. These
feed the final security audit doc (docs/audit.md).
