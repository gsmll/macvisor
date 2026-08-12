# cL4 SK sched — consolidate into sk_region_sched.c

You are building the single consolidated file `osfmk/arm64/sk/sk_region_sched.c` for the cL4
Secure Kernel scheduler/thread region (0x180000-0x200000, 2619 functions) from the 8 slice files
produced by parallel transcription + compile-fix agents. The slices each compile to 0 errors as
standalone translation units, but combining them into one TU produces ~885 cross-file errors
(duplicate/conflicting shared externs, typedef redefinitions, per_cpu and string/DAT globals
redeclared differently, etc.).

## Goal
Produce a single `sk_region_sched.c` that:
- contains ALL 2619 function bodies (they already exist in the slices — do not rewrite/translate),
- has a standard cL4 recreation header,
- compiles with `clang -std=gnu17 -ferror-limit=0 -fsyntax-only -I osfmk/arm64/sk -I osfmk/arm64/sptm
  -I osfmk/arm64/hypervisor -I osfmk/kern osfmk/arm64/sk/sk_region_sched.c` → **0 errors**,
- preserves every FUN_/Ghidra comment and body verbatim.

## Inputs
- osfmk/arm64/sk/sk_region_sched_0.c … _7.c (slices, already 0-error standalone).

## Strategy (recommended)
1. Build `sk_region_sched.c` by concatenating the 8 slices in address order.
2. Resolve cross-file collisions in a SINGLE shared prelude at the top of the master, so that only
   ONE declaration of each shared symbol (per_cpu, s_*/DAT_* string/data globals, shared
   out-of-slice FUN_ helpers, typedefs like undefined8/uint/ulong/reg16/uint128_t/code/code_fn_t)
   exists before all slices' bodies. The cleanest way: for each slice, strip its own typedef block
   and its own extern prelude (keep bodies + function-local declarations), and rely on the master
   prelude. Do this mechanically; never alter function logic or bodies.
3. For shared FUN_ helpers declared with CONFLICTING signatures across slices (e.g.
   FUN_00355334 etc. declared as different return types in sched_7 vs elsewhere), pick ONE
   permissive signature (prefer `unsigned long NAME(...)` or `unsigned long NAME()`) and ensure all
   slices' calls compile against it; cast call sites only where a return VALUE is consumed with a
   specific type, and keep the transcribed constants/logic.
4. For `reg16`/`uint128_t` mismatches (sched_7 declares `reg16` struct and assigns to
   `uint128_t`), unify: if `reg16` is the only 128-bit carrier, typedef it consistently and cast
   assignments `(uint128_t)`/`(reg16)` at those sites, or define `reg16` as an alias compatible with
   the assignment. Keep bodies faithful.
5. `per_cpu` (sched_0 declares `extern uint8_t *per_cpu;`) — declare ONCE in the master prelude with
   the widest-useful type and cast at use sites; do not change logic.
6. After assembly, iterate the clang verify command until 0 errors. You may fix declaration/type/cast
   issues only — NEVER change function logic, branch conditions, constants, or FUN_/Ghidra comments,
   and NEVER delete a function body.

## Rules
- Do NOT touch manifest.json / findings.md / chain-map.md / other files.
- Do NOT run formatters/linters. Only the clang verify command above.
- If a cross-file conflict is genuinely unresolvable without changing logic, prefer a permissive
  cast/prototype that preserves behavior; note it.

## Result (structured JSON)
{
  "file": "osfmk/arm64/sk/sk_region_sched.c",
  "functions": <count of FUN_ headers in the master>,
  "errors": 0,
  "warnings": <count>,
  "slices_merged": 8,
  "collisions_resolved": <count>,
  "note": "<summary of resolution strategy and any residual semantic approximations>"
}
