# cL4 SK region sched — compile-fix task

You are fixing compile errors in one mechanically-transcribed cL4 Secure Kernel recreation file so it
compiles with 0 errors. The file was produced by faithful mechanical translation of Ghidra
decompiles; the FUN_ addresses and logic are GROUND TRUTH — DO NOT change logic, control flow, or the
FUN_/address comments. Your job is ONLY to make it compile cleanly while preserving the exact
transcribed behavior.

## File: osfmk/arm64/sk/sk_region_sched_<N>.c

## Verify command (must end at 0 errors)
clang -std=gnu17 -ferror-limit=0 -fsyntax-only -I osfmk/arm64/sk -I osfmk/arm64/sptm \
  -I osfmk/arm64/hypervisor -I osfmk/kern osfmk/arm64/sk/sk_region_sched_<N>.c

## Common error classes and their fixes (in priority order)
1. **Undeclared function called** (implicit declaration / "call to undeclared function X"): add an
   `extern` prototype for the helper near the top of the file (or in the existing extern block), with
   a `/* FUN_<addr> */` comment if the FUN_ address is known from the call site comment. If the
   arity is unknown or varies, use variadic `(unsigned long, ...)` or a permissive `(...)`.
2. **Conflicting/redundant zero-arg forward declarations**: the file has a block of `void FUN_x();`
   (or `type FUN_x();`) declarations that conflict with later parameterized prototypes of the same
   FUN_. DELETE the redundant zero-arg declaration when a parameterized prototype for the same FUN_
   exists elsewhere in the file. Keep the parameterized one.
3. **Unknown type `uint`/`ulong`/`undefined8`/`undefined1`/`byte`/`ushort`/`undefined`/`code`**: add
   a typedef at the top of the file:
   ```c
   typedef uint64_t undefined8; typedef uint8_t undefined1; typedef uint64_t undefined;
   typedef uint8_t byte; typedef uint16_t ushort; typedef uint32_t uint; typedef uint64_t ulong;
   ```
   (only if not already present). Prefer these to changing call sites.
4. **Call with wrong number/type of args** (too many/few arguments, incompatible pointer/int
   conversion at a call): the transcribed call passes Ghidra's register pair or an extra arg. Fix the
   CALL SITE minimally so it compiles: cast the offending argument or drop/join as needed to match a
   permissive callee prototype `(...)`. Keep the transcribed constants. When a callee returns a
   16-byte pair that is assigned to a 64-bit local, cast `(uint64_t)`.
5. **`void (*)() name;` syntax error** (function-pointer local declared with empty param list):
   change to `void (*name)(void);` (or a typedef `typedef void (*code_fn_t)(void);`).
6. **Assignment from `void` / assigning pointer to integer**: cast the RHS to the target type
   `(uint64_t)`, `(uint8_t)` etc. Do not alter the transcribed value flow.
7. **`(**)` double-indirect call**: `(**(code **)(obj+0x60))(...)` — if it fails to parse, rewrite as
   `(*(void (**)(void))(obj + 0x60))()` with the same argument list, or cast through a local
   `code_fn_t` typedef. Keep semantics.

## Rules
- NEVER change function logic, branch conditions, constants, or the FUN_/Ghidra comments.
- NEVER delete a function body. NEVER rename FUN_ symbols.
- Do NOT touch manifest.json, findings.md, chain-map.md, or other files.
- Do NOT run formatters/linters. Only the clang verify command above.
- Iterate: run verify, fix errors, repeat until **0 errors**. Warnings are acceptable (note the count
  in your result).

## Result (structured JSON)
{
  "file": "...",
  "errors_before": <count>, "errors_after": 0,
  "warnings": <count>,
  "edits": [ {"kind":"extern-added|decl-removed|typedef|cast|call-fix", "symbol":"FUN_x / fn", "count":N} ... ],
  "note": "<any unresolved/risky decisions>"
}
