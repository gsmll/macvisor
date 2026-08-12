# ring −1 decompile worker — batch contract (reuse for every wave)

You are a decompilation worker for the ring −1 project. Read
`docs/sptm/AGENTS.md` FIRST — it is the binding contract. Your job: faithfully
decompile a BATCH of functions from the SPTM/TXM Ghidra programs into English
C, exactly like the hypervisor decompilation.

## Per-batch procedure

1. Read `docs/sptm/AGENTS.md`, `docs/sptm/NAMING.md` (public API names),
   `docs/sptm/manifest.json`, `docs/sptm/findings.md`.
2. Switch MCP to the correct program: write `{"program":"sptm.raw"}` (or
   `txm.raw`) to `xd://mcp__ghidra_switch_program`; confirm with
   `xd://mcp__ghidra_list_instances`.
3. For EACH address in your batch:
   a. `get_function_by_address` → confirm entry/body/signature.
   b. Claim it: append `{"status":"claimed","tree":"ringminus1"}` to
      `docs/sptm/manifest.json` if not present (read → edit → write whole file,
      never invalid JSON).
   c. `decompile_function` (retry once on 30 s timeout, then split).
   d. Write the English C body into the file assigned for your batch, with the
      standard header comment (template in AGENTS.md). Rename locals/params;
      ZERO code-level Ghidra identifiers in the body (keep them in comments).
      GENTER/GEXIT → `GENTER()`/`GEXIT()` with a comment noting opcode +
      selector-in-x16.
   e. Flip the manifest entry to `status:"decompiled"` with `file`,
      `estimated_name`, `confidence`, `notes`.
4. Log any security-relevant observation to `docs/sptm/findings.md`
   (Observation/Evidence/Severity(hypothesis)/Confidence).
5. Verify each function compiles: `clang -fsyntax-only -I osfmk/arm64/sptm
   -I osfmk/arm64/hypervisor -I osfmk/kern <file>` (0 errors expected; note
   warnings).

## Rules (non-negotiable)

- English-first on FIRST write. No stubs, no hand-waving, no guessed bodies.
- Keep logic faithful to the decompile; the manifest/FUN_ names are ground
  truth; names from the SDK headers are high-confidence.
- If the decompiler fails: fallback order = set_function_prototype →
  analyze_function_complete → disassemble_function + get_function_pcode;
  record the fallback in `notes`.
- Never modify another agent's claimed/decompiled manifest entries.
- Do NOT run formatters/linters/project-wide tests.

## FAST PATH (verified 2026-08-12, all ring-1 programs)

The Ghidra HTTP server at `http://127.0.0.1:8089` serves the same endpoints
directly via curl, bypassing the MCP bridge (which saturates under concurrent
agents). Use these instead of `xd://mcp__ghidra_*` calls:
- `curl -s "http://127.0.0.1:8089/decompile_function?address=0xNNNN"`
- `curl -s "http://127.0.0.1:8089/get_function_by_address?address=0xNNNN"`
- `curl -s "http://127.0.0.1:8089/get_function_callers/callees?address=0xNNNN"`
- `curl -s "http://127.0.0.1:8089/search_strings?search_term=WORD"`
Confirm the current program with `curl -s http://127.0.0.1:8089/health`
(switch via the MCP `switch_program` when needed). Each decompile returns in
<1s; if the server is saturated, retry with 10-30s backoff.
