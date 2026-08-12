# cL4 Secure Kernel decompile — sub-range batch

## Contract (binding — read docs/sptm/AGENTS.md, docs/sptm/SK.md, docs/sptm/WORKER.md first)
- You are decompiling a 64KB sub-range of Apple's cL4 Secure Kernel (seL4-derived microkernel).
- Ghidra program is ALREADY switched to `cl4_kernel.raw` (image base 0). Do NOT switch it.
- Ground truth = Ghidra `FUN_*` name + address. English-first on FIRST write: NO code-level Ghidra
  identifiers (`uVar4`, `local_88`, `DAT_...`) in any body — keep them in comments only.
- Use seL4/cL4 vocabulary (threads, caps, IPC, sched, vspace, notification, endpoints, CNode, TCB,
  SchedContext, preemption, etc.). Confidence `medium` unless a string/header matches (`high`).
- This is cL4 Scheduler/thread machinery (file = sk_region_sched). Name functions from callers,
  strings, and structure.

## MCP usage
- `batch_decompile` ({"functions":"FUN_x,...,FUN_y"}) decompiles many at once — USE THIS (chunks of
  ~40-60). On a 30s timeout retry once, then split.
- `decompile_function` for one-offs.
- `get_function_by_address` / `get_function_callers` / `get_function_callees` to name functions.
- `search_strings` (regex) to find naming strings near an address.
- On programs with multiple address spaces prefix `mem:` — not needed here.

## Your task
1. Read your function list: `docs/sptm/sk_range_<N>.txt` (one `FUN_x at x` per line, sorted by addr).
2. Work in ADDRESS ORDER. For EVERY function in your list:
   a. batch_decompile it (with neighbors).
   b. Write an English-first C body into YOUR file (see below) with the standard header comment.
   c. Determine estimated_name, confidence, notes.
3. Do NOT touch docs/sptm/manifest.json, findings.md, or other agents' files — the orchestrator
   centralizes those. Do NOT run compilers. Do NOT run formatters/linters.
4. Security findings: keep a private list, return it in your result (orchestrator logs them).

## Your output file
`osfmk/arm64/sk/sk_region_sched_<N>.c` — create it. Standard header at top:
```
/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel, GL1, arm64e, image
 * base 0) — the cL4 microkernel (cL4 (679.100.61)), seL4-derived. Ground truth: Ghidra FUN_ names
 * + addresses. All names are estimates unless string-matched. */
```
Each function:
```c
/* FUN_001807a4 @ 0x001807a4   (est. <name>)
 * Ghidra: <signature>
 * <2-4 English sentences: purpose, inputs, outputs, side effects>
 * Confidence: medium|high|low
 * Notes: <Ghidra artifacts, callers, decompiler warnings> */
<english C body>
```
Trivial thunks (a body that just calls one shared function, often 4-byte aliases) are fine to
write compactly — still include the header comment and the faithful body.

## External dependencies
Call targets in OTHER sub-ranges or earlier regions are declared as extern prototypes at the top of
your file with a one-line note (e.g. `extern void cl4_preempt_disable(void); /* 0x17dbac */`).
Keep the FUN_ address in the extern comment. Shared types: define minimal local structs only if
needed; prefer passing through as `void*`/`uint64_t` and note the layout in comments.

## Result (structured)
Return JSON:
{
  "subrange": <N>,
  "file": "osfmk/arm64/sk/sk_region_sched_<N>.c",
  "functions": [ {"address":"001807a4","estimated_name":"...","confidence":"medium","notes":"...", "decompiled":true|false} ... ],
  "total": <count>, "completed": <count>,
  "security_findings": [ {"address":..., "name":..., "observation":..., "evidence":..., "severity":..., "confidence":...} ... ]
}
Include EVERY function in your list (all 2619 in range → your ~300-460 subset). For any you could
not decompile (decompiler failure after fallback), set decompiled:false, confidence low, and note
the fallback used — do not skip it.
