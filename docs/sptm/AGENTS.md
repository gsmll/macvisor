# AGENTS.md — ring −1 decompilation contract (SPTM / TXM / Secure Kernel)

Every agent working on the ring −1 (Guarded Execution Feature) targets MUST read
this file first. It defines the rules for decompiling Apple's ring −1 security
monitors out of the payloads in `ringminus1/` and writing the recreation into
this tree, following the same contract as the hypervisor decompilation.

## Targets (all extracted / loaded into Ghidra)

| Target | Payload | Ghidra program | Functions | Role |
|---|---|---|---|---|
| SPTM (GL2) | `ringminus1/bin/sptm.raw` (from `sptm.t8142.release.im4p`) | `sptm.raw` | 512 | Secure Page Table Monitor — the only software that writes page-table entries; kernel is a client (`sptm_map_page`) |
| TXM (GL0) | `ringminus1/bin/txm.raw` (from `txm.macosx.release.im4p`) | `txm.raw` | 1451 | Trusted Execution Monitor — code signing / entitlements / trust caches |
| Secure Kernel (GL1) | payload TBD (cryptex hunt pending) | — | — | seL4-style microkernel serving Exclaves |
| Kernel-side interface | already in `kernelcache.arm64.kc` | `kernelcache.arm64.kc` | 151 GENTER sites | `sptm_map_page` / `sptm_retype` / `txm_enter` client stubs + dispatch table (e.g. `0xfffffe0007c11394`) |

## Ground truth

- Ground truth is the Ghidra `FUN_*` name + address in each program.
- **Naming ground truth (stronger than estimates):** the Apple-published SDK
  headers copied to `docs/sptm/headers/` (`sptm_common.h`, `sptm_xnu.h`,
  `debug_header.h`). Use their exact identifiers for public API:
  `sptm_map_page`, `sptm_retype`, `sptm_guest_enter`, `txm_enter`, the
  `SPTM_DISPATCH_TABLE_*` ids, `SPTM_DOMAIN`, `sptm_call_regs_t`, the
  `SPTM_GENTER_*` kinds, frame types (`XNU_DEFAULT`, `XNU_PAGE_TABLE`, …),
  domains (`XNU_DOMAIN`, `TXM_DOMAIN`, `SK_DOMAIN`, …). Confidence for
  header-matched names is `high` (Apple's own API names).
- The manifest (`docs/sptm/manifest.json`) and `FUN_*` comments are the
  source of truth, not the file layout.

## Ghidra usage (mandatory)

1. The current MCP program is whichever of `sptm.raw` / `txm.raw` /
   `kernelcache.arm64.kc` you switched to via `switch_program` (`{"program":…}`).
   Always confirm with `list_instances` before addressing a function.
2. Small targeted calls only: `get_function_by_address`, `get_function_callees`,
   `get_function_callers`, `decompile_function`, `get_xrefs_to`, `search_strings`,
   `read_memory` ≤ 256 bytes, `analyze_data_region`, `search_functions`,
   `list_functions`.
3. On a 30 s timeout: retry once, then split the request.

## Apple-proprietary instructions (MANDATORY handling)

- `GENTER` = opcode `0x00201420`, `GEXIT` = opcode `0x00201400`. Ghidra will
  show them as unknown/invalid. They are the ONLY way into the guarded levels.
- In recreated code render them as `GENTER()` / `GEXIT()` with a comment:
  `/* GENTER opcode 0x00201420: enters GLx; the selector in x16 selects the
  dispatch endpoint (see SPTM_LOAD_DISPATCH_ID) */`.
- When a call site sets up `x16` before `GENTER`, decode the
  domain/table/endpoint bits per `sptm_common.h` (`SPTM_LOAD_DISPATCH_ID`) and
  name the target endpoint from the header.

## Code output contract

File header (every file):

```c
/* Recreated from sptm.t8142.release.im4p (SPTM, arm64e, image base 0) — the
 * Secure Page Table Monitor (GL2). Ground truth: Ghidra FUN_ names + addresses;
 * public API names from docs/sptm/headers/sptm_common.h. All names are
 * estimates unless header-matched. */
```

Function header comment (every function — template):

```c
/* FUN_0009c2c8 @ 0x0009c2c8   (est. sptm_map_page)
 * Ghidra: undefined8 FUN_0009c2c8(undefined8 param_1, undefined8 param_2)
 * <2-4 English sentences: purpose, inputs, outputs, side effects>
 * Confidence: high|medium|low
 * Notes: <Ghidra artifacts: DAT_/string refs, GENTER selector bits, decompiler
 *   warnings> */
```

Rules:
- Keep the logic faithful to the decompile. Rename locals/params meaningfully.
- **English-first is mandatory on FIRST write**: no code-level Ghidra
  identifiers (`uVar4`, `local_88`, `DAT_...`, `FUN_...` as an identifier) in
  any body. Ghidra names stay in comments only.
- For every unresolved artifact keep an inline comment with its exact Ghidra
  name and address.
- Shared kernel/hardware deps are declared extern with a one-line note.
- **FULL-AUDIT RULE: everything in SPTM and TXM is in scope — no stubs, no
  extern-only shells.** If the decompiler fails, write assembly-level notes +
  partial reconstruction, set `status:"decompiled"`, `confidence:"low"`, and
  record the fallback used (same fixed order as the hypervisor contract:
  set_function_prototype → analyze_function_complete → disassemble_function +
  get_function_pcode).

## Claim protocol

- Before decompiling an address not already in `docs/sptm/manifest.json`,
  append an entry `{"status":"claimed","tree":"<tree>"}` plus known fields.
- NEVER modify an entry whose `status` is `claimed` or `decompiled` by another
  tree/agent. If you need an address claimed by another agent, leave it and
  note it.
- After finishing a function: write the code, then flip the manifest entry to
  `status:"decompiled"` and fill `file`, `estimated_name`, `confidence`, `notes`.
- Manifest edits: read the current file, apply your change, write the whole
  file back. Never leave invalid JSON.

## File layout

- Recreated code lives in `osfmk/arm64/sptm/` (mirroring XNU's own
  `osfmk/arm64/sptm/` layout): `sptm.c`, `sptm_pmap.c`, `sptm_dispatch.c`,
  `txm.c`, plus shared headers `sptm_internal.h` (types from the SDK headers).
- TXM code in `osfmk/arm64/txm/`.
- Kernel-side client stubs (`sptm_map_page` etc.) stay in the existing
  kernelcache tree (`osfmk/arm64/hypervisor/` is the hypervisor scope; the
  sptm/txm client stubs go in `osfmk/arm64/sptm/kernel_client.c`).

## House rules

- Never run formatters, linters, or project-wide test suites.
- Append discovered call-graph edges to `docs/sptm/chain-map.md` with both
  addresses.
- Work only in your assigned files + `docs/sptm/manifest.json` +
  `docs/sptm/chain-map.md` + `docs/sptm/findings.md`.
- Verify command: `clang -fsyntax-only -I osfmk/arm64/sptm -I osfmk/arm64/hypervisor -I osfmk/kern <file>`.

## Security findings log (mandatory)

Every agent MUST log security-relevant observations into
`docs/sptm/findings.md` (append-only; read, add, write back). Same template as
the hypervisor findings: `## [<tree>] <address> <estimated_name>` with
Observation / Evidence / Severity (hypothesis) / Confidence. No entry without
Evidence. These feed `docs/sptm/audit.md` at the end.
