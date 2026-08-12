# Ring −1 Security Audit — `docs/sptm/audit.md`

Synthesis of the ring −1 (Guarded Execution Feature) decompilation recreation in
this tree. Ground truth is the Ghidra `FUN_*` name + address in each program
(`sptm.raw`, `txm.raw`, `cl4_kernel.raw`/slice manifests, `kernelcache.arm64.kc`);
all human names are estimates unless header-matched (see `docs/sptm/AGENTS.md`).
This document consolidates the security observations logged incrementally in
`docs/sptm/findings.md` (759 entries) and the structural map in
`docs/sptm/chain-map.md`. Every claim below cites an address + the function and
its `findings.md` section so it can be cross-checked in Ghidra.

**Severity is a hypothesis, not a claim** (per `AGENTS.md`). The bulk of the
"high" findings are **fail-closed gates**: the gate's correctness is load-bearing,
but *no weakness was observed* — a bypass would require a bug in code that is
explicitly engineered to hard-panic on every invariant violation. They are
labelled as such below, separately from the few real anomalies where an actual
flawed behavior was observed in the transcription.

---

## 1. Executive summary

### 1.1 The stack

Four guarded/privileged software layers were decompiled, from most to least
privileged:

```
GL2  SPTM (Secure Page Table Monitor)      sptm.raw    512 functions
GL0  TXM  (Trusted Execution Monitor)      txm.raw     1451 functions
GL1  cL4  (Secure Kernel, seL4-style)      slice manifests  ~28,278 functions
EL1  XNU kernel client stubs               kernelcache.arm64.kc  ~50 GENTER sites
```

- **SPTM (GL2)** is the only software that writes page-table entries; the kernel
  is a *client* (`sptm_map_page`, `sptm_retype`). It owns the pmap engine
  (`sptm_retype`/`sptm_map_page`/`sptm_nest_region`), the guarded dispatch
  state machine (`sptm_dispatch_transition` @ `000e6bc0`), the IOMMU drivers
  (UAT / NVMe / T8110 DART / SART), the hibernation integrity machinery
  (`sptm_hib_*`), and the AES-GCM/SHA crypto primitives.
- **TXM (GL0)** implements code-signing / entitlements / trust-caches / IMG4
  evaluation and the anti-replay manifest gate — i.e. the *executable-code
  allow-list* policy.
- **cL4 Secure Kernel (GL1)** is the seL4-style microkernel serving Exclaves:
  syscall/IPC marshalling, capabilities, vspace, scheduler, Swift runtime
  (XnuUpcallsV2, object-service dispatch), metadata decoders, and crypto.
- **XNU EL2 client** — the ~50 `sptm_*`/`txm_*` GENTER stubs in
  `osfmk/arm64/sptm/kernel_client.c` (each a tiny `x16 = dispatch_id; GENTER;`
  sequence) plus the `txm_enter` 40-selector dispatcher.

### 1.2 Coverage state

Per `docs/sptm/manifest.json`: **32,254 of 32,318 entries decompiled** (64 still
`claimed`). Per-tree: SPTM **512**, TXM **1451**, cL4 SK **~28,278** (aggregate of
the slice/region manifests), kernel-client **~50**. Recreation lives in
`osfmk/arm64/sptm/` (19 files), `osfmk/arm64/txm/` (8 files), `osfmk/arm64/sk/`
(231 files). The ring −1 pmap/dispatch/IOMMU/hib cores and the TXM policy core
were decompiled **in full** (no extern-only shells — the FULL-AUDIT rule); a
handful of large opaque bodies (Swift register-forwarding, an unrecovered
protocol decoder) are transcribed faithfully but kept at `low` confidence.

### 1.3 Methodology

- **Ground truth** = Ghidra `FUN_` name + address; public API names from the
  Apple-published SDK headers in `docs/sptm/headers/` (`sptm_common.h`,
  `sptm_xnu.h`, `debug_header.h`) get `high` confidence.
- **English-first** on first write: no `uVar4`/`DAT_`/`FUN_` identifiers in any
  body; Ghidra names stay in comments only.
- Every function carries a header comment with purpose, inputs/outputs, side
  effects, and a `high|medium|low` confidence label.
- A dedicated **verification sweep** (`ringminus1/logs/verify/VERIFIED.md`)
  re-checked ~200 low/medium bodies against fresh decompiles + disassembly and
  upgraded or fixed them; see §6.

---

## 2. Severity ranking

The `findings.md` log has **no `critical`** entries. There are **~19 `high`**
entries, of which **18 are fail-closed gate/hypothesis findings** (the gate is
security-critical but no weakness was observed) and **1 is a real anomaly**
(`0x006825d0` free-list arbitrary-write). The tables below separate the two
classes explicitly.

### 2.1 Real anomalies (observed flawed behavior)

These are actual discrepancies/behaviors observed in the decompiled source that
a security reviewer should treat as live concerns. Severity/confidence as
labelled in `findings.md`.

| Address (fn) | Name (est.) | Severity | Finding | Notes |
|---|---|---|---|---|
| `0x006825d0` | sk_free_list_insert | **high** | VB2_7/r71 | allocator free-list coalesce derives every written pointer from node-supplied `{next,len}`; a forged/overlapping block could splice arbitrary pointers into the free list → **arbitrary write through the allocator**. Confidence medium (block-metadata layout estimated). |
| `0x004b9634`/`0x004b97b4`/`0x004b992c` | sk_meta_decode_{sub,merge,slot} | medium | SkR45 | metadata decoders index a dispatch table from the **top byte of each length-prefixed stream element with no bounds check** (`(word>>0x38)*8 + 0x679ac0`); a top-byte value outside the table → OOB indirect call (CFI in the kernel). `0x4b97b4` additionally calls a function pointer read straight from the decoded stream (PAC bit masked off). Reachability depends on stream provenance (guest-controlled Mach-O metadata vs trusted kernel data). |
| `0x0067f8f0` | AES-256 key expand (sk_slice_r71) | medium | VB2_3 | transcription loop-counter bug truncated the round-key schedule to 5 iterations / 192 bytes instead of 7 / 240; wrong round keys for round 6+ → **corrupted AES-256 encrypt/decrypt**. Corrected; ground-truth verified. |
| `0x004b23d8` | sk_vas_page_release | low–medium | SkR41 | per-region page bitmap + 16-bit refcount: the decrement `*(u16*)count = rc-1` runs **unconditionally after the bit-clear with no `rc!=0` precheck**; a guest-triggerable bitmap/refcount desync → 16-bit underflow + spurious freelist push (heap reuse of a live region). Relies on the "present ⇒ refcount≥1" invariant. |
| `0x004088d8` | sk_drace_check | medium | sk | the cL4 **data-race detector installs a raw machine-instruction trampoline into memory at runtime** (self-modifying code inside GL1). In-kernel code mutation is integrity-sensitive; the fatal path on first-detector-mode mitigates. Confidence low (exact install target not recovered). |
| `00004478` | sk_slab_mark | low/medium | VB2_5 | **inverted size-class branch**: the transcribed body performed the `first+0x48 = run-count` store for `type==2` and skipped it otherwise — the exact opposite of the decompile (`if (type==2) goto done;`). Wrong run-count metadata into the slab header could misclassify a slab node and yield an oversized/undersized object. Corrected. |
| `0x0037dc2c`/`0x00384740` | sk_desc_assign / cL4_obj_copy5 | medium | VB2_7/syscalls | indirect calls through vtable pointers loaded from descriptor tag metadata (`*(type-8)+{0x10,0x18,0x20,0x28,0x8}`), gated only by the `+0x52` inline-flag bit → a caller-passed attacker-influenced descriptor tag yields a **controlled function-pointer call**. |
| `0x000017f4` | sk_boot_run | medium (hypothesis) | BootRunExpand | boot path is a **GL1 trust boundary**: ~20 vtable methods dispatched through PAC-authenticated pointers; the device-tree walk trusts the node range returned by the `+0xe0` method and writes the `0x6ac0xx` root-object table from the 8-word scratch record **with no bounds check**, before page tables are live. A hostile DT (or buggy `+0xe0`) could corrupt the root object table. |

Supporting medium/real concerns from the same sweep (see §6): `0x00372a44`
sk_desc_copy OOB read (11 words from `*(param_1-8)` unbounded), `0x000b3cfc`
sk_htbl_finish indirect-call + pointer-store, `0x0040eac8` sk_cont_result_dispatch
code-pointer dispatch on attacker-influenceable record contents.

### 2.2 Fail-closed gates (high *hypothesis* — no weakness observed)

Each is the sole/strongest control at its boundary; a bypass would require a bug
in code that hard-panics on every invariant violation. Listed with the boundary
each one guards.

| Address (fn) | Name (est.) | Guarded boundary | Confidence |
|---|---|---|---|
| `000e6bc0` | sptm_dispatch_transition | **ring-1 state machine**: validates state/event/capability bounds via `000e7068`/`000e70b4`; every illegal transition is a hard panic ("invalid_state"/"invalid_event_type"/…). | medium |
| `000c1128`/`000c12a4` | sptm_hib_verify_hash_non_wired_page / _finalize | **sole software integrity check over hibernated non-wired memory**; the kernel compares the digest at `0x94948`. Page index + content bound into the SHA-2 context. | high |
| `000cfaec`/`000cd0bc` | sptm_t8110dart_map_table / unmap | **which physical memory a DART client can DMA to/from** (hard 0x3ffffffffff bound + per-DART bound, per-client guard). | medium |
| `000c8fb8`/`000c93d8` | sptm_t8110dart_enable/disable_translation | **DMA translation on/off**; per-stream guard + acquire-variant gating (0xbf1). | high |
| `000c9728` | sptm_t8110dart_init | pre-translation configuration: only a self-consistent DART window becomes live (version/granule/STE/PAGE-size asserts). | high |
| `000c1e94`/`000c2908` | sptm_nvme_ans_sha_reg / admin_queue_regs | **NVMe DMA queue pages confined to the SPTM-owned guest region**; BAR/guest-window paddr checks are complete and fail-closed. | high |
| `0002089c` | txm_page_enforcement | **executable-mapping authority gate** (cs.debugger / debug-flag / comm-page bits = the code-execution policy). Highest-value TXM surface. | high |
| `00022b10` | txm_exec_debug_mapping_check | OAH/runtime JIT-debug mapping admission (`0xcf7`/`0xd1a` identifier compare). | high |
| `0002316c` | txm_exec_check | JIT execution-eligibility (0xdc6/0xdda entitlements, JIT bit). | high |
| `00023384` | txm_cs_debug_policy | debug-mapping admission (com.apple.private.cs.debugger). | high |
| `00024970` | txm_trust_cache_load | prospective trust-cache build bounds. | medium |
| `00025160` | txm_cdhash_accelerate | entitlement acceleration cache registration. | high |
| `00025780` | txm_amfi_cdhash_reg | amfi.can-load-cdhash registration gate. | high |
| `00025ec4` | txm_external_tc_load | boot trust-cache install (module/offset table bounds). | high |
| `00026350` | txm_trust_cache_load | load-trust-cache admission (`com.apple.private.pmap.load-trust-cache`). | high |
| `0005fb88` | txm_entitlements_blob_parse | caller-supplied entitlements blob → trusted policy boundary. | high |
| `000592b4` | txm_manifest_trust_evaluate | **anti-replay / odometer gate** (prevents a downgraded/replayed boot manifest). | high |
| `000345f4` | txm_trust_eval | **the trust decision gate**: AMFI CMS flags vs policy masks + cert-chain verify; failure class 0x40000 on unapproved. | medium |

The dispatch/DART/NVMe gates (SPTM) and the entire TXM code-signing layer are
**defense-in-depth**: every violation is a panic or a deterministic deny, never a
silent continue.

---

## 3. Per-tree findings

### 3.1 SPTM (GL2) — `osfmk/arm64/sptm/`

**DART / NVMe / DMA gates.** The IOMMU layer is the DMA-constraint boundary:
- DART map/unmap bound paddr to a hard `0x3ffffffffff` cap + per-DART bound and
  validate the leaf FTE against instance/client/level before writing
  (`000cfaec`/`000cd0bc`, high).
- `sptm_t8110dart_init` (`000c9728`) only makes a self-consistent window live
  (version ∈ {0x200,0x201,0x202,0x300}, single granule, per-stream PTE/slice
  cross-checks) — an inconsistent/overlapping IOMMU window cannot be enabled.
- NVMe queue registers confine DMA pages to the BAR/guest window with 4 KiB
  alignment + once-only previous-address checks (`000c1e94`/`000c2908`, high).
- SART teardown zeroes and re-verifies the three parallel tables + a power
  canary (`000c5a28`) so stale DMA permissions cannot survive teardown.

**Hibernation integrity.** `sptm_hib_verify_hash_non_wired_page`/`_finalize`
(`000c1128`/`000c12a4`, high) is the sole integrity check over hibernated
non-wired memory: it re-hashes every page (index+content) into the same SHA-2
context construction used at save time, domain-separated by ASCII salts
("GESH"/"1GAP"/"FFUB", `000bf9dc`) and hardened against double-hash
(`000c02bc`, panics) and non-DRAM/immutable pages. `sptm_hib_restore` (`000eb004`)
binds a dual SHA/HMAC digest and bounds the image1 size and CTRR key derivation
hygiene before the restore walk.

**Dispatch state machine.** `sptm_dispatch_transition` (`000e6bc0`) is the
guarded GENTER/GEXIT boundary: it indexes table `@0x16770 = state*0x1e0 +
event*0x20`, validates the next-state/handler/flags and capability bits, and
hard-panics on any illegal transition. The TXM/SK entry context-saves
(`000a0f7c`/`000a111c`) enforce a hop-depth spin and mask DAIF before stacking
saved registers — a bypass would allow stacked guarded calls to clobber each
other's saved state (context corruption). The SPTM→SK/TXM entry stubs
(`000b25c0..000b2698`) hard-code constant dispatch selectors (SK domain 3, TXM
domain 2), so a client cannot steer them to an arbitrary endpoint.

**Guest enter/exit.** `sptm_guest_dispatch`/`sptm_guest_enter` (`000f7924`/
`000f6368`) require interrupts masked, validate the guest state block is an
SPTM-managed paddr, and re-validate the FTE class + VTTBR_EL2 consistency on exit
— preventing entry with a forged state block or tampered translation state.
`sptm_guest_exit_handoff` (`000a1374`) validates the UAT handoff magic before
routing the exit to a guarded level.

**Crypto.** The crypto core (`000ae498`..`000b2204`) implements AES key
expansion (128/192/256), AES-GCM (NEON), GHASH, SHA-256/512, constant-time
compares (`sptm_ct_memcmp` `000b03b8`), and fortified-libc `_chk` wrappers that
panic on overflow. It is the substrate for the hibernation digest and any
secure-channel encryption; correctness here is load-bearing.

### 3.2 TXM (GL0) — `osfmk/arm64/txm/`

**Trust evaluation.** `txm_trust_eval` (`000345f4`) is the trust decision: the
trust class is computed from AMFI CMS flags vs the owner's policy masks (apple /
developer / adhoc) with an optional cdhash cert-chain verify (`txm_amfi_cms_verify`
`00031714`), and unapproved images fail class 0x40000. `txm_exec_check`
(`0002316c`), `txm_exec_debug_mapping_check` (`00022b10`) and
`txm_cs_debug_policy` (`00023384`) gate JIT/debug executability on the
`0xdc6`/`0xdda`/cs.debugger entitlements — the discriminator for allowed
executable memory.

**Entitlements.** `txm_entitlements_blob_parse` (`0005fb88`, high) is the
boundary where a caller-supplied entitlements blob becomes trusted policy (magic
0x6d783f3c = "<?xm"); `txm_ce_object_lookup` (`00060088`) trusts the name-table
value offset without re-validation (low-medium, depends on table provenance).
`txm_phys_to_virt` (`00061ea4`) confines the physmap to TXM-owned ranges + a PTE
page-state gate.

**Trust cache.** The executable allow-list is populated only through
entitlement-gated install: `txm_external_tc_load` (`00025ec4`),
`txm_trust_cache_load` (`00026350`, `00024970`), `txm_amfi_cdhash_reg`
(`00025780`), `txm_cdhash_accelerate` (`00025160`). `txm_page_enforcement`
(`0002089c`, high) is the per-mapping admission gate. `txm_rb_insert`
(`00021ddc`) rejects duplicate/overlapping code-region intervals (defense in
depth).

**Anti-replay.** `txm_manifest_trust_evaluate` (`000592b4`, high) runs trust
evaluation + an anti-replay/replay check; a manifest that fails trust or replay
is denied. The img4 property constraint engine (`txm_enforce_*_constraint`,
`0005b224`..`0005bb1c`) is the policy backstop for boot-chain/anti-replay values
(operator 8 panics on "not constrained"). The runtime callback table
(`000576f0-00057870`) is a chain of "function should never be called" dead-ends —
invoking an unwired slot is a fatal panic, not a graceful no-op.

### 3.3 cL4 Secure Kernel (GL1) — `osfmk/arm64/sk/`

**Syscall / IPC / message-register marshalling.** `cL4_cap_type_validate`
(`003876c4`) is the capability authorization gate for IPC/cap transfers (all
observed checks hard-deny). The `sk_desc_*` family (`0x0037dc2c`,
`0x00372a44`) dispatch through descriptor-tag vtable pointers (real anomaly, §2).
The tightbeam message-register foreach (`00381378`) dispatches 8 MR slots with
faithful slot mapping; the message decoder/dispatch region (`0x32-0x34`) uses
context-slot function-pointer dispatch whose unrecovered-jumptable call sites are
the highest-value follow-up targets (`003d9b94` etc., medium).

**Capabilities.** `sk_set_insert_key`/`sk_collection_remove_first`
(`0025a864`, `00272820`) fail closed on duplicates/overflows; the object-keyed
hash tables (`sk_htbl_*`, `000b3cfc`) re-key entries on grow — a wrong key
function changes capability-slot placement (corrected). Capability-id mapping
(`0x10c2b0`) canonicalizes tags deterministically.

**Vspace.** The per-CPU owner-mask isolation gate (`0x249a64`) denies a context
whose CPU is not in the `+0x50` owner byte (≤8 CPUs) rather than mapping it;
`sk_vspace_ctx_perm_mod` (`0x24c2ec`) requires clean size divisibility before a
permission change. COW fault authorization depends on span flag bits
(`00042abc`/`sk_span_search` family).

**Scheduler / runtime.** The Swift runtime (XnuUpcallsV2, `sk_swift_*` helpers)
and the object-service dispatch (`(*DAT_00658c00)` indirect) are transcribed
faithfully but kept at low/medium confidence because of opaque
register-forwarding; a handful of huge bodies (e.g. `0x21f7b0`, 2592-line Swift
string-protocol dispatch) are verified 1:1. The sync/thread path
(`sk_g_006b2690` table dispatch) is a single global code table — if it could be
corrupted, every sync/wake/suspend operation would indirect-call attacker-chosen
code (medium hypothesis).

**Metadata decoders.** `sk_meta_decode_*` (`0x004b9634`/`0x004b97b4`/`0x004b992c`)
treat stream contents as executable metadata with **unbounded jump-table
selection** (real anomaly, §2). The class-file reader (`004176ec` etc.) has OOB
read risk on malformed data if payload bounds are not enforced upstream.

**Crypto.** The kernel PRNG (`sk_prng_construct` `0x103b2c`) is seeded from a
GL0/SPTM supervisor request of 0x30 bytes — the trust root is external
(medium). The hash/crypto layer enables DIT + constant-time compares
(`0x104f78`) — good timing hygiene. `0x1120c4` uses **wyhash** (explicitly
non-cryptographic) for table bucketing — fine for indexing, must not be relied
on for MAC/authenticity. `0x0067f8f0` (AES-256 key expand) had the truncated
schedule bug (§2, corrected).

### 3.4 Kernel client (EL1) — `osfmk/arm64/sptm/kernel_client.c`

**GENTER ABI.** Each `sptm_*`/`txm_*` wrapper is a tiny GENTER stub:
pre-entry hook → `x16 = (domain<<48)|(table<<32)|endpoint` → `GENTER()`
(opcode `0x00201420`) → post-exit hook. The endpoint ids equal the
`SPTM_FUNCTIONID_*` constants from the SDK headers (SPTM_DOMAIN 0, XNU 1, TXM 2,
SK 3). `txm_enter` (`0x0002adec`) accepts selectors 0x0–0x33 and is **fail-closed
on invalid opcode** (reserved/unknown selectors return 0x26 or panic 0xa1).

**Entitlement probe.** TXM's trust-cache / code-signing gates probe
`com.apple.private.pmap.load-trust-cache` (`0x1448`),
`com.apple.private.amfi.can-load-cdhash` (`0x130b`), `com.apple.private.cs.debugger`
(`0xc79`) and the oop-jit/security-research strings through `txm_entitlement_check`
(`00022a38`); SPTM's guest/IOMMU endpoints are reached via the fixed entry stubs.
The dispatch selectors are constant, so a userland client cannot steer a stub to
an arbitrary guarded endpoint.

---

## 4. Attack-surface analysis

### 4.1 Reachability

| Surface | Reached from | Boundary gate | Representative findings |
|---|---|---|---|
| SPTM pmap (`sptm_map_page`/`retype`/`nest`) | kernel client (`sptm_*` GENTER stubs) → SPTM | `sptm_retype` transition-mask, `sptm_map_page` type/perm gates | `000ed6b4`, `000ee278` |
| TXM code-signing / trust-cache | `txm_enter` selectors → TXM | `txm_page_enforcement`, `txm_trust_*`, entitlements | `0002089c`, `000345f4`, `00026350` |
| DART/NVMe/SART/UAT | **device-facing** (DMA controllers), configured by SPTM | paddr bounds, per-stream guards, FTE class | `000cfaec`, `000c8fb8`, `000c1e94` |
| Guest enter/exit | **EL2/guest** (GENTER/GEXIT, exception vectors) | state-block validation, VTTBR consistency, DAIF mask | `000f7924`, `000f6368` |
| cL4 syscall/IPC/message-register | **exclave → GL1** | cap validate, owner-mask, descriptor-tag dispatch | `003876c4`, `0x249a64`, `0x0037dc2c` |
| Boot path (cbootinfo/DT) | **external boot image (GL1 trust boundary)** | bounds on untyped/DART tables, boot-object method dispatch | `0x000017f4`, `0x0006c5cc` |

Most of the highest-value SPTM/TXM controls are **device- or kernel-only
reachable** (a userland process cannot reach the DART/HIB/TXM trust-eval code
without first passing the kernel's GENTER/entitlement surface). The genuinely
userland-exposed, attacker-influenceable paths in GL1 are the **syscall /
message-register / capability** marshalling and the **metadata decoders**
(§2, §3.3), which is where the real anomalies concentrate.

### 4.2 The PAC key-rearming chain (APIAKey)

On every guest resume the hypervisor re-arms `APIAKeyLo_EL1` (`3,0,1,0,5`) with a
nonce derived via `pacga` from the per-CPU thread key `*pcpu` (a **16-bit signed
value**) and an incrementing context counter (`per-cpu+0xe0`), OR'ed with `0x700`;
`APIAKeyHi_EL1` (`3,0,1,0,6`) is written as the **constant `0x10001`**
(see `docs/findings.md` "hv_el2_return_to_guest — PAC key re-arm nonce
derivation", and `osfmk/arm64/hypervisor/hv_el2.c`; the same tail appears in
`hv_el2_exception_exit` `b75e420` and `hv_el2_eret_fast` `b75e5cc`).

**Amplifier hypothesis.** The re-armed instruction-authentication key seed
reduces to a 16-bit thread-key field and a constant high key — i.e. the *effective*
per-resume PAC key material is low-entropy and **the key registers are EL1/guest
readable sysregs** (they are written from EL2 but visible at EL1/EL0 via
`mrs`). If the 16-bit thread-key word is weak or attacker-influenceable, a guest
that can read the key registers could **forge PAC (pointer-authentication)
codes**, and because `APIAKeyHi` is constant `0x10001`, the total per-CPU key
search space is small enough to be an amplifier for any PAC forgery primitive.
Mitigating: the key is kernel-set per-CPU, `pacga` + the counter add entropy, and
the 16-bit field is a kernel datum a guest "should not" reach — so this is an
**informational/low hypothesis**, flagged for focused review rather than a
confirmed weakness. (Register identities are estimates per contract.)

### 4.3 The fail-closed design property

The dominant defensive property across all four layers is **fail-closed
engineering**: the ring-1 monitors are written so that *any* invariant violation,
unexpected state, or bounds breach **halts** (panic / noreturn `sptm_panic` /
`SoftwareBreakpoint` / deny) rather than continuing with corrupted state. The
recreation repeatedly documents "all bounds are hard panics (defense-in-depth)"
(`000e6bc0`), "the checks are complete and fail-closed" (`000c1e94`), and "every
invalid object hard-stops" (`sk_vspace_obj_check` `0x26c6d8`). The consequence is
that most SPTM/TXM "high" surfaces are **availability** risks (a hostile input
crashes the monitor) rather than **privilege-escalation** risks. The exceptions —
the places where the monitor *acts* on attacker-influenceable data — are the
metadata decoders, the descriptor-tag indirect dispatch, and the allocator
free-list (§2), and those are the priority.

---

## 5. Verification-sweep results

The sweep (`ringminus1/logs/verify/VERIFIED.md`, batches VB2/VB3/VB5/V0/V6/V7 +
`VerifyV*`) re-checked ~200 low/medium large-body transcriptions against fresh
decompiles and disassembly. Bug classes found were all **decompilation-fidelity
errors in the transcription**, not vulnerabilities in the binary:

- **Pair-return `x1` drops** — helpers returning `{lo,hi}` in `x0:x1` had the high
  word dropped (e.g. `0x001d4584`, `0x001de04c`, `0x000a46cc` in sk_region_sched /
  caps_08): the dispatch handler received the wrong object/capability id word.
- **Wrong callees** — e.g. `sk_log_consume` (`0005c278`) called `sk_memset` instead
  of `thunk_FUN_00114330`; `sk_re_parse_group_kind` (`0x004379bc`) routed scalar
  matches to the wrong helper (`sk_re_scan_newline` vs `sk_re_diag_emit_str`);
  `txm_exec_debug_mapping_check`'s OAH compare was mis-attributed.
- **Stubbed / condensed bodies** — e.g. `sk_boot_run` (`000017f4`) was a structural
  summary omitting the DT walk/CNode/TCB/page-table construction; `sk_re_scan_newline`
  (`0x0042f020`) dropped the UTF-16 newline-detect + advance; `sk_zone_ptr_size_impl`
  (`0000cc60`) was a `return 0` stub.
- **Fabricated calls / arguments** — e.g. `sk_parse_store_impl` invented a
  `sk_parse_u8` step that changed the stored value (`000b06a4`); `thread_suspend`
  (`0005fac0`) passed a `CONCAT44` phantom instead of the thread arg; dropped
  callback dispatch `(call+0x10)` in `004af468`.
- **Wrong offsets / inverted branches** — `sk_slab_mark` (`00004478`) inverted the
  size-class branch; `0x003a18`-family offset errors in frame/record layout;
  `sk_span_tree_remove_node` (`0003730c`) shifted slots one position off.

**Implication for trust in the decompiled source.** The sweep found real
fidelity errors concentrated in *low-confidence transcription* (Swift
register-forwarding bodies, large opaque decoders, sched/object-model helpers),
and every one was corrected to ground truth and compile-verified (0 errors per
edited TU). The important consequence is **the decompiled source cannot be
trusted at face value at the `low` confidence tier** — any security conclusion
drawn from a `low`-confidence body should be re-verified against the Ghidra
decompile or disassembly before being relied on. `high`-confidence bodies
(header-matched, verified 1:1) are trustworthy. The sweep also confirmed these
are **reconstruction** fixes — "no binary vulnerabilities introduced" — i.e. they
affect our *reading* of the binary, not the binary itself.

---

## 6. Recommendations for further review

Priority-ordered targets for the next audit pass:

1. **Metadata decoders** (`0x004b9634`/`0x004b97b4`/`0x004b992c`, SkR45): confirm
   the *provenance* of the streams that feed the unbounded jump-table selectors
   and the decoded-comparator call. If any stream is guest/exclave-controlled,
   this is a kernel CFI bug; if only trusted kernel code builds them, downgrade.
2. **Message-register marshalling** (`00381378` tightbeam, `0x32-0x34`
   message-decoder region): the unrecovered-jumptable call sites
   (`003d9b94`/`003d98d8`/`003dc97c`) dispatch through context-slot function
   pointers with no visible bounds check — resolve the tables and confirm slot
   validity.
3. **cbootinfo parse** (`0006c5cc`, `0x000017f4` boot path): the untyped-region
   and DART table population is bounds-checked, but the segment-slide/roottask
   computation and the direct `0x6ac0xx` root-table writes (no bounds check) merit
   focused review, plus the `sepfw`/amfi DT-getter fail-open defaults
   (`0002a354`/`0002a434`).
4. **DART ordering race** (`000b486c` sptm_uat_map_continue): the IOMMU-ownership
   check is gated on `sptm_debug_flags`; confirm whether that flag is clear in
   production, which would skip the ownership/type enforcement (base/lock checks
   remain).
5. **State-machine model check** (`000e6bc0` sptm_dispatch_transition): model the
   69-handler state/event table @0x16770 against the SDK's expected transition
   set to confirm no reachable unauthorized target state; verify the capability-
   bitset semantics.
6. **Recompile-and-fuzz parsers**: the DER/TLV decoder (`00044184`/`0004a2d0`),
   the entitlements-blob parser (`0005fb88`), the trust-cache superblob parser
   (`00032630`/`00032910`), the IMG4/mach-O metadata decoders, and the NVMe/DART
   register parsers are all recreated as compilable C — recompile and fuzz them
   (the binaries are gone but the recreated parsers preserve the control flow) to
   hunt for cases the hard-panic guards miss.
7. **APIAKey re-arm** (§4.2): confirm whether the 16-bit per-CPU thread-key field
   is ever attacker-influenceable, and whether `APIAKeyHi=0x10001` + EL1-readable
   keys materially shrink the PAC forgery space.
8. **The `0x006825d0` free-list anomaly**: confirm the block-metadata layout and
   whether a guest can actually forge an overlapping `{next,len}` to splice the
   free list (the one true `high`).

---

## 7. Honest limitations

- **Decompiled, not source.** Everything here is reconstructed from Ghidra
  decompiles of stripped binaries; the C is a *faithful English-first reading* of
  the decompiler's output, not Apple's source. Confidence tiers reflect how
  confidently the body matches the decompile+disassembly, not certainty about
  intent.
- **No dynamic validation.** None of this was executed or instrumented; all
  conclusions are static. Panics/fail-closed behavior is asserted from the
  control flow, not observed at runtime.
- **Register-ABI low-confidence bodies.** Swift register-forwarding bodies,
  `unaff_*`/`extraout_*` artifacts, and unrecovered-jumptable call sites make some
  GL1 bodies structurally opaque; these are kept `low`/`medium` and must not be
  relied on without re-verification (§5).
- **Names are estimates.** Function names are `est.` unless header/string-matched;
  a name may describe the wrong behavior. Register and sysreg identities (e.g.
  the APIAKey registers) are unverified per contract.
- **Findings severity is a hypothesis.** The `high` labels mostly denote
  *load-bearing fail-closed gates*, not demonstrated exploitable bugs; the single
  real `high` (`0x006825d0`) has medium confidence because the block-metadata
  layout is estimated. Reachability of the guest-triggerable surfaces is inferred,
  not demonstrated.

---

*Coverage/status ground truth: `docs/sptm/manifest.json` (32,254/32,318
decompiled). Call-graph edges: `docs/sptm/chain-map.md`. Per-function confidence:
`docs/sptm/manifest.json`. Verification verdicts:
`ringminus1/logs/verify/VERIFIED.md`. Header-matched names:
`docs/sptm/headers/`.*
