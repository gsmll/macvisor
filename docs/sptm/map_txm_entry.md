# TXM entry surface & key structures

`txm.raw` = Apple **Trusted Execution Monitor (TXM)**, GL0 firmware. It is the
authority for code signing, entitlements, trust caches, and code-execution policy
(the kernel calls it via `txm_enter(selector, argsp)`; Apple's selector names are
`kTXMKernelSelector*`). Image base 0, AARCH64:LE:64:AppleSilicon, 1451 functions,
~475 KB, code at `0x20000` (section label `__text`).

The binary embeds an MH_MAGIC_64 Mach-O header at `0x00000000`; `Reset @ 00000000`
is the Mach-O entry label. Only export: `Reset -> 00000000`.

## 1. Entry / dispatch hierarchy

```
kernel txm_enter(endpoint_id, argsp)
   │  (no caller/xref — reached directly from EL1, the entry root)
   ▼
FUN_0002adec   ← TXM SELECTOR DISPATCH ROOT (switch on param_1 = endpoint/selector 0x0..0x33)
   │
   ├─ selector 0x2d → FUN_0002c3f8 → FUN_0002cbd0   image4 dispatch (ops 0..5)
   ├─ selector 0x03 → sets up trust-cache array at DAT_00010590
   ├─ selector 0x04 → FUN_00029714                   build/version query (returns 0x1800)
   ├─ selector 0x0d → FUN_0002670c                   unload-trust-cache
   ├─ selector 0x29 → FUN_00023574                   entitlement / policy query
   ├─ selector 0x2a → FUN_00023384                   code-signing / debug-mapping policy
   ├─ selector 0x28 → FUN_00023254 → FUN_0002316c    code-region association + exec check
   └─ … (full switch list below)
```

- **FUN_0002adec** (0002adec, no callers/xrefs): the `txm_enter` selector
  dispatcher. Validates selector `< 0x34`, writes per-call state into the TXM
  per-CPU context from FUN_0002d214 (stack-derived per-CPU struct at
  `sp & ~0x3fff + 0x3c00`), dispatches on `param_1` (0x0–0x33), stores the return
  in `ctx+8`, then FUN_0002ab70 performs the return/exit (signal handler + 
  FUN_0004f318/FUN_0004edac).
- **FUN_0002c3f8** (0002c3f8): image4 dispatch entry — validates buffer
  bounds/alignment then calls **FUN_0002cbd0**.
- **FUN_0002cbd0** (0002cbd0): image4 dispatch — loads a handler table from
  FUN_000535e0 and dispatches operation index 0–5 (pin-root, evaluate-trust, …);
  raises "image4 dispatch: handler/input-size" panics (strings 0000239b/000023ba).

### Selector → handler map (from FUN_0002adec switch)

| selector | handler | role (from decompile + strings) |
|---|---|---|
| 0x00 | (inline, context setup) | per-call context reset |
| 0x02 | FUN_0002b380 | context/code-limits init (writes &DAT_00071034, &DAT_00070fa8) |
| 0x03 | (inline) | trust-cache array init at DAT_00010590 |
| 0x04 | FUN_00029714 | return build/version (0x1800) |
| 0x05 | FUN_00023f54 | (image4 / runtime) |
| 0x06 | FUN_0002b4f8 | |
| 0x07 | FUN_0002b3e8 | |
| 0x08 | FUN_00023b50 | |
| 0x09 | FUN_0002b470 | |
| 0x0a | FUN_0002b58c | |
| 0x0b | FUN_0002b5e8 | |
| 0x0c | FUN_0002b644 | |
| 0x0d | FUN_0002670c | **unload-trust-cache** (com.apple.private.unload-trust-cache) |
| 0x0e | FUN_0002b760 | |
| 0x0f | FUN_0002b870 | |
| 0x10 | FUN_0002b974 | |
| 0x11 | FUN_0002ba18 | |
| 0x12 | FUN_0002bad8 | |
| 0x13 | FUN_0002bbac | |
| 0x14 | FUN_0002bc08 | |
| 0x15 | FUN_0002bc50 | |
| 0x16 | FUN_0002bc84 | |
| 0x17 | FUN_0002bd5c | |
| 0x18 | FUN_00027814 + FUN_00024838 | |
| 0x19 | FUN_0002bdb8 | |
| 0x1a | FUN_00025528 | |
| 0x1b | FUN_0002be18 | |
| 0x1c | FUN_0002be60 | |
| 0x1d | FUN_0002bf3c | |
| 0x1e | FUN_0002c018 | |
| 0x1f | (inline) | context reset |
| 0x20 | FUN_0002c134 | |
| 0x21 | FUN_00027814 + FUN_00024e80 | |
| 0x22 | FUN_0002c18c | |
| 0x23 | FUN_0002c1f4 | |
| 0x24 | FUN_0002811c + FUN_00022348 | |
| 0x25 | FUN_0002811c + FUN_00022660 | |
| 0x26 | FUN_0002c258 | |
| 0x27 | FUN_0002c2c8 | |
| 0x28 | FUN_0002811c + FUN_00023254 | **code-region association** (→ FUN_0002316c exec check) |
| 0x29 | FUN_0002811c + FUN_00023574 | entitlement/policy query (get-task-allow, license-to-operate) |
| 0x2a | FUN_0002811c + FUN_00023384 | code-signing / debug-mapping policy |
| 0x2b | FUN_0002c314 | |
| 0x2c | FUN_0002c3a0 | |
| 0x2d | FUN_0002c3f8 | **image4 dispatch** (→ FUN_0002cbd0) |
| 0x2e–0x33 | (returns 0x26) | unimplemented selectors |

## 2. Code-signing verification entry points

The executable-code policy is the heart of TXM. Chain:

- **FUN_0002089c** (0002089c) — page-enforcement / executable-mapping authority.
  Consults `FUN_0002c908` for the requested region type, checks debug entitlements
  (`com.apple.private.cs.debugger` 00000c79, `allow-jit` 00000dda), the comm-page
  rule, association code-limit (00000d39), and raises "page enforcement failed"
  (00000bdd) / "disallowed writable debug mapping" (00000c41/00000c97) /
  "disallowed executable debug mapping" (00000c1d).
- **FUN_0002abec** → FUN_0002089c (caller of the page-enforcement core) and raises
  "denying executable mapping as the kernel has panicked" (000022e3).
- **FUN_00023254** (selector 0x28) — creates/associates a code region
  (`FUN_0002316c` verifies execution eligibility via `dynamic-codesigning`/
  `allow-jit` entitlements 00000dc6/00000dda and the association object state).
- **FUN_0002316c** — execution check: verifies JIT entitlement, association type,
  and code-limit binding before permitting execution.
- **FUN_00022b10** — executable debug-mapping check (OAH/runtime entitlements
  00000cf7/00000d1a, association code-limit 00000d39).
- **FUN_00023384** / **FUN_00023574** / **FUN_00036acc** / **FUN_0003596c** —
  entitlement-family checks (cs.debugger, get-task-allow 00000e51,
  license-to-operate 00000e2b, allow-jit 00000dda).
- **FUN_00025780** / **FUN_00036d44** — `amfi.can-load-cdhash` /
  `amfi.can-execute-cdhash` (0000130b / 00002d7a) CD-hash authority.

## 3. Trust-cache structures

- **FUN_00026350** (00026350) — trust-cache load. Reads a trust-cache range
  (param_2 = {start,len,typ}), validates the `com.apple.private.pmap.load-trust-cache`
  entitlement (00001448), locks the TC subsystem (FUN_000262c4), and installs the
  cache into the TC array at **DAT_00010590** via FUN_00031060; updates the
  counters DAT_0007101c/20/24/28. Selector 0x03 sets up DAT_00010590.
- **FUN_0002a674** — parses `/chosen/memory-map/TrustCache` from the device tree
  (strings TrustCache 00001f42, /chosen/memory-map 00001efe) into a
  `{paddr, size, type}` descriptor; validates page alignment.
- **FUN_00025ec4** — external trust-cache module loader: parses DT trust-cache
  range (00001495), errors on 0-length (000014c0), loads N modules
  ("loaded external trust cache modules: %u/%u" 0000150d), and builds the TC list.
- **FUN_0002670c** — unload-trust-cache (selector 0x0d; entitlement
  00001470).
- **FUN_0002623c** — disallows ERM (extended-research-mode) trust cache on the
  system (00001417).
- TC array root: **DAT_00010590**; per-TC entry holds {count, size, flags} with
  the counter globals DAT_0007101c/20/24/28.

## 4. TXM init / boot

- **`__text`** (00020000, body 00020000–00020177) — TXM entry/init. Reads a
  profile (`FUN_00031fe8`), parses its UUID, and looks it up against the
  **association table at 0x10000** (16-byte UUID entries; loop with
  `thunk_FUN_0002d990` comparing against base 0x10000 stepping 8 bytes up to 0xb0).
  Raises the profile-UUID panics (000007d5/000007f2/0000080f). This selects the
  active TXM profile/configuration at boot.
- **FUN_0002adec** context getter **FUN_0002d214** — returns per-CPU TXM context
  at `(sp & ~0x3fff) + 0x3c00` (the TXM thread/context struct).
- Per-selector per-call context: FUN_0002adec writes context fields at offsets
  +0x18..+0x48 (state, buffer/limits, code-limits pointers) before dispatch.

## 5. Image4 / secure-channel / runtime callback surfaces

- **FUN_0002cbd0 / FUN_0002c3f8** — image4 dispatch (see §1); handler table from
  FUN_000535e0.
- **FUN_00053cd4 / FUN_00053d38** — image4 **trap** input marshalling/validation:
  copies a fixed-size selector argument block and checks length/bounds
  ("trap input has unexpected length" 000042f5, "user buffer is null/zero/exceeds"
  000043e0/00004407/00004435).
- Image4 trap handlers (each a selector, dispatched via the runtime table):
  - **FUN_00053604** set_release_type (000042d6)
  - **FUN_00053728** slot/nonce setup (no-slot panic 00004347)
  - **FUN_000538a8** roll_nonce (entitlement check, no-slot panic 00004347,
    "caller not entitled to roll nonce" 00004364)
  - **FUN_000539ec** activate_image ("no image for handle" 00004394,
    "caller not entitled to activate image" 000043b2, "activation failed" 00003034)
  - **FUN_00053ba4** set_boot_uuid ("failed to set boot uuid" 0000448a)
- **Secure channel**: FUN_000236f0 (secure-channel init; "secure channel not
  supported" 00000e8d, "setup the shared page" 00000ebb), FUN_00023930 (SCRD
  magic/xART reporting 00000ee8/00000f0c), FUN_00023c50 (SCVerifySignature for
  developer auth 000010c0).
- **TXM runtime callback table**: **FUN_000576f0 … FUN_00057850** — the
  `_txm_runtime_*` identifier table (12 adjacent functions, one per callback)
  that registers the image4 runtime dispatch; each handler falls through to the
  "function should never be called" panic (00005463).

## 6. Key globals referenced by entry code

| global | use |
|---|---|
| DAT_00010590 | trust-cache array root (selector 0x03, FUN_00026350) |
| DAT_0007101c/20/24/28 | trust-cache counters (count, code size, data size) |
| DAT_00071034 / DAT_00070fa8 / DAT_00010678 | code-limits / debug-mode / executable-policy state |
| DAT_00006cf0 | stack canary (checked on return from every dispatch fn) |
| DAT_00006f0a / auStack_3b guard | init stack-guard compare |
| 0x10000 | boot profile / association UUID table (referenced by `__text`) |
| DAT_000104e9 / 000104ea / 000104f2 / 0001074e | boot-state / debug / page-state flags |

## Confidence

- **high**: selector dispatch root FUN_0002adec (decompiled switch, no callers =
  external entry), code-signing entry FUN_0002089c, trust-cache FUN_00026350/
  0002a674/00025ec4, `__text` init, image4 dispatch FUN_0002cbd0, trap
  marshalling FUN_00053cd4/00053d38.
- **medium**: exact `kTXMKernelSelector` integer↔name mapping for the many
  inline/unnamed handlers (0x05–0x27 etc.) — roles inferred from decompile
  structure and referenced globals; the selector *numbers* match the observed
  handlers but Apple's literal `kTXMKernelSelector*` enum values were not present
  as strings in this binary.

## Files

- Full function inventory (1451 addresses): `ringminus1/logs/txm_funcs.txt`
- String→function table: `docs/sptm/map_txm_strings.md`
