# Security findings log

Append-only log of security-relevant observations made during decompilation.
Format per AGENTS.md 'Security findings log'. Each entry labels severity as a
hypothesis, never a claim, and carries Ghidra evidence.

---

## [entitlements] fffffe000b985ae4 hv_entitlement_tier

- **Observation**: The entitlement tier gate is entirely client-visible: the
  hypervisor trusts the calling process's own entitlement strings. The
  vmapple tier (3) and private-hypervisor tier (4) both elevate the returned
  level, and tier 4 additionally requires the kernel-config flag
  DAT_fffffe0007e255f8 bit 0x1010. There is no per-call re-validation that the
  tier is still current; the caller's cred is read fresh each call via
  per_cpu_base(FUN_fffffe000b866ec4) + FUN_fffffe000b8663e8 (current_task),
  but the tier value returned is used by the caller to size capabilities.
- **Evidence**: three `(**(code **)(DAT_fffffe0007e93310 + 0x1c0))(cred,
  "<entitlement>")` probes against com.apple.security.hypervisor (level 1),
  com.apple.private.hypervisor.vmapple (level 3), com.apple.private.hypervisor
  (level 4 with DAT_fffffe0007e255f8 & 0x1010). No bounds/TOCTOU check on the
  returned tier between probe and use.
- **Severity (hypothesis)**: low — entitlement checks are the intended gate;
  the risk is a mis-scoped caller getting tier 3 when it only holds the base
  entitlement (probe-returned `has_security` fallback), not a privilege
  bypass.
- **Confidence**: medium — the tier encoding (0/1/3/4) is inferred, not
  independently verified.

## [entitlements] fffffe000b987d9c hv_caps_feature_mask

- **Observation**: The capability feature mask is built from the caller's
  entitlement tier, but for tiers < 2 the function falls back to a *default*
  mask (2) when `per_cpu_base`/`current_task` returns NULL or the
  com.apple.private.virtualization probe fails — i.e. a NULL/task-resolution
  failure yields a non-zero capability set rather than an explicit deny.
- **Evidence**: `uVar9 = 2; mask[0xd] = 2;` then `if (lVar3==0) uVar9 = 2;`
  else probe `com.apple.private.virtualization` -> `uVar9 = 0x202` or 2.
  Mask words are then OR'ed with capability bits (mask[0]|0x100000 etc.).
- **Severity (hypothesis)**: informational — defaulting to tier-2-like caps on
  an entitlement-probe failure could over-grant a caller whose task lookup
  failed; but tier<2 callers already hold only a weak entitlement.
- **Confidence**: medium — the NULL path value (2 vs 0) is decompiler-derived
  and the semantic of capability word bits is unverified.

## [entitlements] fffffe000b988038 hv_caps_cpu_report

- **Observation**: The CPU/memory report writes unvalidated feature words read
  straight from per-CPU cache/topology tables (PTR_PTR_fffffe000c5b3f58/60/68)
  and ID registers into a caller-visible 0x1b3-byte block. The cache
  block-size field at +0x1a1/+0x1a9 is computed as `0x40 - (size & 0x3f)`;
  if a page-size table entry reported a block size >= 0x40 this underflows to
  a huge shift value reported to the caller.
- **Evidence**: `lVar10 = 0x40 - (*(ulong *)(puVar9 + 0x50) & 0x3f);` stored to
  `*(long *)(report + 0x1a1)` / `+0x1a9`. No upper-bound check on the table
  value before subtraction.
- **Severity (hypothesis)**: informational/low — the value is derived from
  trusted per-CPU topology tables (kernel-set), so an attacker would need to
  corrupt kernel data first; but a defensive caller should clamp.
- **Confidence**: low — the topology-table contents are kernel-owned and
  presumed sane.

## [entitlements] fffffe000c0f8cfc cred_has_entitlement (sandbox probe)

- **Observation**: The universal sandbox entitlement probe (DAT_fffffe0007e93310
  slot +0x1c0) is referenced from 100+ kernel sysctl/ops tables — it is the
  single choke point for entitlement checks, so a weakness here affects every
  hypervisor capability gate. Ghidra's body analysis collapses it to a 4-byte
  stub (mis-analyzed), so its exact return contract is unverified; callers
  treat "return 0 == entitled".
- **Evidence**: analyze_function_complete reports body fffffe000c0f8cfc-
  c0f8cff (4 bytes, pacibsp only) yet raw bytes show a real prologue
  (stp x29,x30; adrp; add); xref_count 100. Callers in hv_entitlements.c/
  hv_vmapple.c rely on `==0` semantics.
- **Severity (hypothesis)**: informational — universal-primitive trust anchor;
  no bug observed, but the contract is not independently confirmed.
- **Confidence**: low — the 4-byte body is a Ghidra analysis artifact, not an
  observed defect.

## [entitlements] fffffe0007e0d7f0 quota consumption (boot-arg / quota)

- **Observation**: The ISA VM quota is written by hv_support_init into
  DAT_fffffe0007e0d7f0/7f4/7f8 and the derived pool DAT_fffffe000c5b83b0-b8,
  clamped to INT_MAX (0x7fffffff). The quota boot-arg override path
  (hv_apple_isa_vm_quota) applies the *unclamped* parsed value directly when
  the enable bit DAT_fffffe0007e255f8 bit 4 is set, bypassing the INT_MAX
  clamp. Consumers (hv_vm_create b985588, hv_vcpu_object_release b98533c)
  decrement the pool.
- **Evidence**: hv_support.c: `quota = (quota < 0x80000000u) ? quota :
  0x7fffffff;` for the DT path; the boot-arg path
  `rc = FUN_fffffe000c09cbf0(...); if (rc) { DAT_fffffe000c5b83b0 = boot_quota;
  ... }` stores boot_quota unclamped.
- **Severity (hypothesis)**: low — an unclamped boot-arg quota could let the
  pool exceed INT_MAX and wrap the decrement-based accounting; requires an
  entitlement-gated caller plus a privileged boot-arg, so low impact.
- **Confidence**: medium — the clamp is applied only in the DT branch per the
  decompile; the exact quota-consumption arithmetic in the other trees is not
  re-audited here.
