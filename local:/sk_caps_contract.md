# SK Caps-Region Decompile Contract (cl4_kernel.raw 0x80000-0x100000)

You are decompiling the cL4 (seL4-derived) Secure Kernel caps region from Ghidra
program `cl4_kernel.raw` into English C. READ these FIRST:
- /Users/gabesmall/macvisor/docs/sptm/AGENTS.md
- /Users/gabesmall/macvisor/docs/sptm/WORKER.md
- /Users/gabesmall/macvisor/docs/sptm/SK.md

## Your slice
File `/tmp/slices/slice_NN.txt` lists addresses (one per line: `ADDR GHIDRA_NAME`)
in ascending order. Decompile EVERY one in order.

## Per function
1. `switch_program {"program":"cl4_kernel.raw"}` then `get_function_by_address {"address":"0x<ADDR>","program":"cl4_kernel.raw"}` to confirm entry/body/signature.
2. `decompile_function {"address":"0x<ADDR>","program":"cl4_kernel.raw"}`. On 30s timeout retry once, then fall back (set_function_prototype -> analyze_function_complete -> disassemble_function + get_function_pcode).
3. Write an English-first C body into YOUR slice file
   `/Users/gabesmall/macvisor/osfmk/arm64/sk/sk_region_caps_NN.c` (create with
   standard header; template below). Use seL4/cL4 vocabulary (caps, CNode,
   TCB, endpoints, notifications, sched, vspace, IPC). NO code-level Ghidra
   identifiers in bodies (uVar, local_x, DAT_, FUN_ as identifiers) — keep in
   comments only. GENTER/GEXIT render as GENTER()/GEXIT() with a comment.
4. Track manifest flips + findings in YOUR report; DO NOT edit manifest.json or
   findings.md yourself (the batch lead consolidates serially to avoid JSON
   corruption). Return them structured.

## Function header template
```
/* FUN_000xxxxx @ 0x000xxxxx   (est. <name>)
 * Ghidra: <signature>
 * <2-4 English sentences: purpose, inputs, outputs, side effects>
 * Confidence: medium|low|high
 * Notes: <Ghidra artifacts: DAT_/string refs, decompiler warnings, fallback used> */
```

## File header (top of your slice file)
```
/* Recreated from cl4_kernel.raw (cL4 Secure Kernel, arm64e, image base 0) —
 * the cL4 microkernel (GL1). Ground truth: Ghidra FUN_ names + addresses.
 * All names are estimates unless string/header matched.
 * Slice NN: 0x80000-0x100000 caps region. */
```

## Return (structured, REQUIRED)
Return a JSON object:
{
  "slice": NN,
  "completed": [{"address":"0x...","ghidra_name":"FUN_...","estimated_name":"...","confidence":"...","notes":"..."}],
  "failed": [{"address":"...","reason":"..."}],
  "findings": [{"address":"...","name":"...","observation":"...","evidence":"...","severity":"...","confidence":"..."}],
  "compile": {"errors":N,"warnings":N,"command":"..."}
}

## Rules
- English-first on first write, no stubs, no guessed bodies.
- Keep logic faithful to the decompile.
- If decompiler fails, use the fallback chain and note it (confidence low).
- Do NOT edit manifest.json, findings.md, chain-map.md, or other files.
- Do NOT run formatters/linters/project-wide tests.
- Verify compile: clang -fsyntax-only -I osfmk/arm64/sptm -I osfmk/arm64/hypervisor -I osfmk/kern <your slice file>
