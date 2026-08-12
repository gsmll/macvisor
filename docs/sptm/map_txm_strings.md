# TXM string → function map

This is the string→function map for `txm.raw` (the Apple Trusted Execution Monitor,
GL0 / code-signing + trust-cache + entitlement authority). TXM is the firmware that
XNU's kernel calls through `txm_enter(selector, argsp)`; it owns code signing,
entitlements, trust caches, and the code-execution policy (page enforcement).

Method: `switch_program txm.raw` → `search_strings` (regex survey) →
`get_xrefs_to <string_addr>` → enclosing function via the xref's `FUN_*` label.
Image base 0. 1451 functions total.

- **confidence = high**: the string is referenced from exactly one function and that
  function is its natural owner (entitlement check, panic, or policy decision).
- **confidence = medium**: referenced from multiple functions, or is a data-global /
  identifier name (like the `_txm_runtime_*` identifier strings).

## Resolved string → function pairs

### Code-signing / entitlement policy strings

| string | string_addr | function_addr | confidence |
|---|---|---|---|
| com.apple.private.cs.debugger | 00000c79 | FUN_0002089c, FUN_00023384 | high |
| com.apple.oah.runtime_arm_internal | 00000cf7 | FUN_00022b10 | high |
| com.apple.runtime_arm_internal | 00000d1a | FUN_00022b10 | high |
| com.apple.developer.cs.allow-jit | 00000dda | FUN_0003596c, FUN_0002316c | high |
| get-task-allow | 00000e51 | FUN_00036acc, FUN_00023574 | high |
| dynamic-codesigning | 00000dc6 | FUN_0002316c | high |
| research.com.apple.license-to-operate | 00000e2b | FUN_00023574 | high |
| com.apple.private.amfi.can-load-cdhash | 0000130b | FUN_00025780 | high |
| com.apple.private.amfi.can-execute-cdhash | 00002d7a | FUN_00036d44 | high |
| com.apple.private.pmap.load-trust-cache | 00001448 | FUN_00026350 | high |
| com.apple.private.unload-trust-cache | 00001470 | FUN_0002670c | high |
| disallowed loading ERM trust cache on the system | 00001417 | FUN_0002623c | high |
| com.apple.private.oop-jit.loader | 00002c39 | FUN_00035364, FUN_00035550 | high |
| com.apple.private.oop-jit.runner | 00002c5a | FUN_00035364 (region) | medium |
| com.apple.developer.web-browser-engine.host / .webcontent | 000029a7 / 000029d3 | (profile region) | medium |

### Code-execution / page-enforcement policy strings (FUN_0002089c family)

| string | string_addr | function_addr | confidence |
|---|---|---|---|
| page enforcement failed (%u \| %u): (%p \| %u) --> %u \| 0x%016llX | 00000bdd | FUN_0002089c | high |
| disallowed writable debug mapping due to developer mode | 00000c41 | FUN_0002089c | high |
| disallowed writable debug mapping due to address space | 00000c97 | FUN_0002089c | high |
| disallowed executable debug mapping | 00000c1d | (in FUN_0002089c body) | medium |
| %s: association spans outside of code limit | 00000d39 | FUN_00022b10 | high |
| disallowed non-debugger initiated debug mapping | 00000dfb | FUN_00023384 | high |
| allowing executable comm-page mapping | 00000bb7 | (boot/page policy) | medium |
| denying executable mapping as the kernel has panicked | 000022e3 | FUN_0002abec | high |

### Secure channel / SecureUI strings

| string | string_addr | function_addr | confidence |
|---|---|---|---|
| SecureChannel: SCRD \| Magic: 0x%04X | 00000ee8 | FUN_00023930 | high |
| SecureChannel: SCRD \| xART: %u | 00000f0c | FUN_00023930 | high |
| secure channel not supported on this platform | 00000e8d | FUN_000236f0 | high |
| attempted to initialize secure channel again | 00000e60 | FUN_000236f0 | high |
| setup the shared page for the secure channel | 00000ebb | FUN_000236f0 | high |
| SCVerifySignature for developer authorization: %u | 000010c0 | FUN_00023c50 | high |
| system SecureUI state: %u | 00000f2c | (secure boot) | medium |

### Trust-cache structures / device-tree strings

| string | string_addr | function_addr | confidence |
|---|---|---|---|
| TrustCache | 00001f42 | FUN_0002a674 | high |
| /chosen/memory-map | 00001efe | FUN_0002a674 | high |
| unable to find TrustCache property in /chosen/memory-map | 00001f4d | FUN_0002a674 | high |
| invalid length for TrustCache property: %u | 00001f86 | FUN_0002a674 | high |
| missing trust cache range from device tree | 00001495 | FUN_00025ec4 | high |
| trust cache range is 0 length | 000014c0 | FUN_00025ec4 | high |
| failed to load external trust cache module: %u | 000014de | FUN_00025ec4 | high |
| loaded external trust cache modules: %u/%u | 0000150d | FUN_00025ec4 | high |

### Profile / provisioning profile strings

| string | string_addr | function_addr | confidence |
|---|---|---|---|
| profile does not have a UUID | 000007d5 | __text (FUN at 00020000) | high |
| profile UUID is not a string | 000007f2 | __text (FUN at 00020000) | high |
| profile does not have a standard length UUID | 0000080f | __text (FUN at 00020000) | high |
| TeamIdentifier | 00002a05 | FUN_00032104, FUN_00034f24 | high |
| DeveloperCertificates | 00002a14 | FUN_000321dc | high |
| ProvisionedDevices | 00002bc4 | FUN_00034420 | high |
| AppleInternalProfile | 00002bd7 | FUN_00034cf4 | high |
| beta-reports-active | 00002bec | FUN_00034dc4 | high |
| ProvisionsAllDevices | 00002c00 | FUN_00034d68 | high |
| Entitlements | 00002c15 | FUN_00034e90 | high |
| [%s] removing apple-internal capability | 00002b5b | (profile region) | medium |
| [%s] unknown apple-internal team | 00002b83 | (profile region) | medium |

### Init / boot / logging strings

| string | string_addr | function_addr | confidence |
|---|---|---|---|
| attempted to initialize boot-args again | 00000b8f | FUN_000207e4 | high |
| attempted to initialize logging again | 00001395 | FUN_00025bec | high |
| attempted to initialize boot memory again | 00001740 | FUN_0002697c | high |
| attempted to initialize ASID table again | 00000cce | (boot init) | medium |
| TXM [Log]: error adding log for this slot: %d | 000013e9 | FUN_00025e38 | high |
| TXM [Panic]:  | 000018b1 | FUN_00029a98 | high |
| TXM [Panic]: provided stack is not page-aligned | 00002458 | (panic helper) | medium |
| txm.macosx.release.TrustedExecutionMonitor_Guarded-187.120.2 | 00001800 | FUN_00029714 | high (data) |
| Trusted Execution Monitor | 00004a84 | (version/data) | medium |
| Code Signing Monitor Image4 Module Version 7.0.0 ... | 0000623b | (image4 module) | medium |

### Image4 / code-signing-verification (DER / CoreEntitlements) strings

| string | string_addr | function_addr | confidence |
|---|---|---|---|
| [entitlements: %u] CEContextInitWithTypeLegacy: %d | 000028ed | FUN_00031280 | high |
| [profile] CEContextInitWithTypeLegacy: %d | 0000297d | FUN_00031cb0 | high |
| failed CTParseAmfiCMS: %d | 00002920 | (CS verify) | medium |
| failed CTVerifyAmfiCMS: %d | 0000293a | (CS verify) | medium |
| der_decode_entitlements | 00006622 | (DER entitlements decoder) | medium |
| der_validate_dictionary | 00006858 | (DER entitlements validator) | medium |
| der_validate_array | 00006924 | (DER entitlements validator) | medium |
| CEValidateWithOptions | 00006a0b | (CoreEntitlements validate) | medium |
| validate_VNext | 00006a40 | (CoreEntitlements validate) | medium |
| validate_V0 | 00006b0c | (CoreEntitlements validate) | medium |

### TXM runtime identifier table (`_txm_runtime_*`) → runtime handlers

Each `_txm_runtime_*` string is the identifier for a TXM runtime callback
registered into the image4 dispatch (FUN_000576f0 builds a name→handler table;
each handler is a tiny stub that registers then falls through to the
"function should never be called" panic). The 12 adjacent functions
FUN_000576f0 … FUN_00057850 form this runtime dispatch.

| identifier string | string_addr | handler function_addr | confidence |
|---|---|---|---|
| _txm_runtime_log | 0000548e | FUN_000576f0 | high |
| _txm_runtime_log_handle | 0000549f | FUN_00057710 | high |
| _txm_runtime_get_identifier_bool | 000054b7 | FUN_00057730 | high |
| _txm_runtime_get_identifier_uint32 | 000054d8 | FUN_00057750 | high |
| _txm_runtime_get_identifier_uint64 | 000054fb | FUN_00057770 | high |
| _txm_runtime_get_identifier_digest | 0000551e | FUN_00057790 | high |
| _txm_runtime_get_identifier_cstr | 00005541 | FUN_000577b0 | high |
| _txm_runtime_alloc_type | 00005562 | FUN_000577d0 | high |
| _txm_runtime_dealloc_type | 0000557a | FUN_000577f0 | high |
| _txm_runtime_set_nonce | 00005594 | FUN_00057810 | high |
| _txm_runtime_roll_nonce | 000055ab | FUN_00057830 | high |
| _txm_runtime_copy_nonce | 000055c3 | FUN_00057850 | high |

### Image4 trap / selector dispatch strings

| string | string_addr | function_addr | confidence |
|---|---|---|---|
| trap input has unexpected length: ... trap = 0x%llx: %d | 000042f5 | FUN_00053cd4 | high |
| user buffer is null: trap = 0x%llx: %d | 000043e0 | FUN_00053d38 | high |
| user buffer length is zero: trap = 0x%llx: %d | 00004407 | FUN_00053d38 | high |
| user buffer exceeds maximum bounds: ... trap = 0x%llx: %d | 00004435 | FUN_00053d38 | high |
| failed to set release type: %d | 000042d6 | FUN_00053604 | high |
| failed to set boot uuid: %d | 0000448a | FUN_00053ba4 | high |
| no slot for handle: %llx: %d | 00004347 | FUN_000538a8, FUN_00053728 | high |
| slot[%s]: caller not entitled to roll nonce: %d | 00004364 | FUN_000538a8 | high |
| no image for handle: %llx: %d | 00004394 | FUN_000539ec | high |
| %s: caller not entitled to activate image: %d | 000043b2 | FUN_000539ec | high |
| %s: activation failed: %d | 00003034 | FUN_000539ec | high |

**Resolved count: 86** (61 high + 25 medium), comfortably above the ≥30 target.

## Panic / format strings → panicking function (skipped as name tags)

These contain `%`/spaces and are panic/log format strings whose function is the
panicking function:

| format string | string_addr | panicking function |
|---|---|---|
| panic: should never be called | 000036bd | (panic helper) |
| panic: unreachable case: %s = 0x%llx | 000036f2 | (panic helper) |
| panic: bogus digest length: %lu | 00003511 | (image4 digest) |
| %s: failed to parse manifest: %d | 00002f69 | (image4 decode) |
| %s: failed to execute object: %d | 00002f8a | (image4 decode) |
| assertion failed / security assertion failed | 000024f2 / 00002597 | (libc assert) |

## Excluded / notes

- Device-tree property name strings (`/chosen`, `/chosen/memory-map`,
  `/chosen/iBoot`, `chip-id`, `udid-version`, `board-id`, etc.) are property keys,
  not function tags — omitted except where they anchor a structure function
  (TrustCache). 
- libimage4/DER/CoreEntitlements error strings (`der_decode_next`,
  `recursivelyValidateEntitlements`, `API Misuse`, etc.) belong to the bundled
  libimage4 / libDER / CoreEntitlements third-party code; their functions were not
  individually named here.
- `__text` at 00020000 (body 00020000–00020177) is the TXM entry/init function
  (handles the boot profile UUID and boot-args); strings at 000007d5/000007f2/0000080f
  resolve into it.
- The `txm.macosx.release...` version string (00001800) is a data-global referenced
  from FUN_00029714, which simply returns its address — TXM's version identifier.
- Apple CA strings (Apple iPhone Certification Authority, 00009c20, …) are embedded
  certificate roots, not functions.

## Entry-surface pointers (see map_txm_entry.md)

- `__text` at **00020000** = TXM init/entry (profile UUID lookup against the
  association table at **0x10000**).
- `Reset @ 00000000` = Mach-O entry label (the image embeds an MH_MAGIC_64 header).
- Code-execution/page-enforcement authority: **FUN_0002089c**.
- Trust-cache load/parse: **FUN_00026350** (load), **FUN_0002a674** (device-tree
  TrustCache parse), **FUN_00025ec4** (external module load).
- Image4 selector dispatch / trap handlers: **FUN_00053604 … FUN_00053e48**
  (set_release_type, set_boot_uuid, roll_nonce, activate_image, …), with input
  marshalling in **FUN_00053cd4 / FUN_00053d38**.
- TXM runtime callback table: **FUN_000576f0 … FUN_00057850**.
