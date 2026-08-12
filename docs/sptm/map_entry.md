# SPTM Entry Surface & Dispatch Machinery Map

Program: `sptm.raw` (Apple Secure Page Table Monitor, GL2), `AARCH64:LE:64:AppleSilicon`, image base 0.
Ground truth: Ghidra `FUN_*`/addresses in `sptm.raw`; addresses below are Ghidra addresses == file offsets
(the file is an arm64e Mach-O whose `__TEXT` preferred vmaddr `0xfffffff027004000` is NOT applied — the
raw load uses base 0). Public API names from `docs/sptm/headers/sptm_common.h` / `sptm_xnu.h`.
File layout (from Mach-O load commands): `__text` @0x9c000 (0x5ca24), `__DATA_CONST.__const` @0x14000,
`__LATE_CONST` @0x1c000 (0x7c270), `__DATA`/`__auth_ptr` @0x100000, `__BOOTDATA.__data` @0x118000.

Note: GENTER (0x00201420) / GEXIT (0x00201400) are shown by Ghidra as unknown/misdisassembled; the raw
bytes are authoritative (verified below).

---

## (a) GENTER entry stubs & dispatch handler

### Entry point / boot — `0x000a8388` / `0x000ab000` — HIGH confidence
- Mach-O `LC_UNIXTHREAD` (`flavor 0x6`) PC = vmaddr `0xfffffff0270ac388` = **Ghidra `0xa8388`**.
- `0xa8388: b 0xab000` (trampoline; followed by 0x00 padding).
- **Boot entry `0xab000`** (est. `sptm_main`): `msr oslar_el1,xzr`; `msr DAIFSet,#0xf`;
  `mov x20,x0` (x0 = iBoot SPTM args); reads `[x20]` (compared to 0x3) and `[x20+0x480]`;
  writes struct tag `0x50534d54` ("TMSP") to the per-CPU dispatch state; initializes a small global
  struct at `0xaa000`; `adrp x0,0xa9000; msr vbar_el1,x0` (**installs vector table #1 @0xa9000**);
  checks `currentel==0x8` and sets `hcr_el2` bits; `adrp x25,0x1c000` / `adrp x26,0x118000`;
  zero-fills `0x1c000..0x1e000` (head of `__LATE_CONST`).

### Per-CPU bootstrap — `0x9c000` (est. `sptm_register_cpu`/per-cpu init) — MEDIUM confidence
- `0x9c000` is the first code in `__text`. Sets `PState.SP` (both SP_EL0/SP_EL1), then
  `adrp x10,0x9d000; msr vbar_el1,x10` (**installs vector table #2 @0x9d000**); configures
  `hcr_el2`, `tpidr_el1 = x0 << 14` (**per-CPU state base = cpu_id << 14**), `tpidrro_el0=0`,
  `tcr_el1=0xa5116511333108`, `MAIR`/`sctlr_el1`-style setup; loads per-CPU SP from `[x10+0x540]`
  (stack) and `[x10+0x4f0]`. Sets up a small struct at `0x9e000`.

### The GENTER *receiver* (SPTM side of a client's `genter #0`) — MEDIUM confidence
The client stubs (`sptm_map_page` etc.) do `SPTM_LOAD_DISPATCH_ID <domain,<table,<endpoint>; genter #0`
with `x16 = domain<<48 | table<<32 | endpoint` (per `sptm_common.h` `SPTM_LOAD_DISPATCH_ID`). On the
SPTM side the dispatch is a **state machine driven by `FUN_000e6bc0`** (est. `sptm_dispatch`) which
decompiles cleanly:

- **`FUN_000e6bc0 @ 0xe6bc0` — the dispatch/state-transition engine.** Reads current CPU
  (`tpidr_el2`/`tpidr_el1`), validates state byte at `cpu+0xa60` (`<0x17`) and event `param_1` (`<0xe`),
  indexes the **state-transition table at `0x16770`** (`base + state*0x1e0 + event*0x20`), validates
  permissions, and jumps to the entry's handler pointer (`*(&entry+8)`, PAC-signed). It also performs
  dispatch-ID validation against the **domain/table dispatch table** (base `0x95470`, see (d)):
  `plVar8 = (DAT_00095bf0 + domain*0x180 + (table&0xf)*0x18)` for XNU/TXM domains, else constant
  `0x95470`; `*plVar8`=entry-point, `plVar8[1]`=permissions bitmask. On invalid transitions it calls
  panic helpers (`FUN_000e7068`, `FUN_000e70b4`, `FUN_000f8804`, `FUN_000f8844`).

- **Context-save entry `FUN_000a0f7c @ 0xa0f7c`** (and twin **`FUN_000a111c @ 0xa111c`**): saves the
  caller's full GPR/FP/SIMD context (x19–x28, x29/x30, d8–d15, sp_el0, daif) into the per-CPU state
  area, bumps the nesting counter at `cpu+0xa68`, then calls `FUN_000e6bc0(3)` to run the state machine.

### SPTM's own GEN_NAMED_STUB entry stubs (SPTM → TXM / SK) — HIGH confidence
A contiguous run of `GEN_NAMED_STUB`-pattern functions (each `bti c; movk x16,#disp_id; b <entry>`):
- To **SK (domain 3), table 1**, endpoints 0..3 → `b 0xa111c`: `0xb25c0, 0xb25d8, 0xb25f0, 0xb2608`
- To **TXM (domain 2), table 1**, endpoints 0..5 → `b 0xa0f7c`: `0xb2620, 0xb2638, 0xb2650, 0xb2668, 0xb2680, 0xb2698`
  (decoded IDs, e.g. `0xb2620` loads `x16 = 0x2<<48 | 0x1<<32 | 0x0`.)
Adjacent: `0xb2584` (arg-munging call to `0xae214`), `0xb25a0`/`0xb25b0` (const getters returning
`0x14080` / `0x14030`).

### GENTER / GEXIT opcode sites (raw bytes) — HIGH confidence
- **GENTER (0x00201420) at `0xab8d8`** — SPTM's only GENTER (sets `vbar_el1`-class regs then GENTERs;
  Ghidra truncates here with "Bad instruction").
- **GEXIT (0x00201400) at `0xa0520, 0xa095c, 0xa0bf8, 0xa0d7c, 0xa126c, 0xa170c, 0xa2b50`** — the
  SPTM's return-to-caller / level-exit points (the "return" half of each dispatch/exception cycle).
  These sit in unanalyzed gaps (not in the 512 defined functions).

---

## (b) SPTM exception vector tables

Two 16-slot (0x800-byte) `VBAR_EL1`-format tables of 0x80-byte handlers:

### Vector table #1 — `0xa9000` (VBAR_EL1 set by boot @0xab08c) — HIGH confidence
- Slots 0..15 at `0xa9000, 0xa9080, … 0xa9780` (all start `adrp x8,0xaa000`; slot 15 is the last
  populated; `0xa9800` onward is 0x00). Verified each 0x80 slot repeats the identical handler skeleton.
- Each slot handler: loads the **per-CPU dispatch-state pointer from `[0xaa018]`**, if unclaimed
  stores `vector_type+1` into `state+0x18` and `0` into `state+0x48`, then reads `sreg(3,6,0xf,0x8,0)`
  (exception return state); if set reads `esr_el1/elr_el1/far_el1` (or their GL2 equivalents
  `sreg(3,6,0xf,0xa,5/6/7)`) into `state+0x20/0x28/0x30`; then **`mov x0,#0xdead; wfe; b` panic spin**
  (unexpected exception → dead loop). Slots store 1, 2, 3 at `state+0x18` (slot0/1/2).

### Vector table #2 — `0x9d000` (VBAR_EL1 set by per-CPU bootstrap @0x9c01c) — MEDIUM confidence
- Slots 0..15 at `0x9d000..0x9d780` (each starts `cmp`, 0x80 stride; `0x9d800` onward 0x00).
- Installed by the per-CPU bootstrap (the vector table used during CPU bring-up).

The `SPTM_VECTOR_IRQ/FIQ/SERROR/SYNC = 0..3` ids (sptm_common.h) are used by
**`FUN_000e7100 @ 0xe7100` (est. `sptm_exception_state_saved`)**: it validates `vector_type < 4`,
requires XNU's EL2 exception vector (`DAT_00095cf8`) and exc-return handler (`DAT_00095468`) to be
registered, then jumps to `FUN_000a0adc(xnu_vec_base + vector_type*8, param_1)` to hand the interrupt
to XNU.

---

## (c) SPTMArgs bootstrap structure / entry

- **SPTM-side args (from iBoot)**: passed in `x0` to the boot entry `0xab000` (`mov x20,x0`). Observed
  field offsets: `[+0x0]` magic/version (`== 0x3`), `[+0x8]`→x22, `[+0x10]`→x23, `[+0x18]`→x24,
  `[+0x480]` pointer (target of the "TMSP" tag struct). — MEDIUM confidence (layout inferred from reads).
- **XNU-side bootstrap args**: `sptm_bootstrap_args_xnu_t` in `docs/sptm/headers/sptm_xnu.h` (the
  structure SPTM passes *to* XNU; fields: `sptm_prev_ptes`, `physmap_base/end`, `first_avail_phys`,
  `phys_slide_papt/size`, `txm_thread_stacks`, cpu-stack bounds, `executables_papt_start/end`,
  `debug_header`, `num_asids`, `random_seed[0x107]`, `sk_bootstrapped`, `sptm_variant`,
  `xnu_triggered_panic`, `libsptm_state`, `auxkc_*`, timestamps, `hib_scratch_page_paddr`,
  `sptm_pmap_io_ranges`). — HIGH confidence (SDK header).
- Boot-time zeroing of `__LATE_CONST` head (`0x1c000..0x1e000`) happens in the boot path.

---

## (d) Function-pointer dispatch tables

### D1. State-transition table — `0x16770` (in `__DATA_CONST.__const`, 0x14000..0x19c98) — HIGH confidence
Referenced by `FUN_000e6bc0`. Layout: base `0x16770`, **state stride 0x1e0**, **event stride 0x20**;
per entry (0x20): `+0x0` current-state byte, `+0x8` **handler pointer (PAC-signed)**, `+0x10` next-state
byte, `+0x18` flags (bit0=validate dispatch id, bit1=hop check). 69 non-empty entries; decoded handler
addresses (low 39 bits after PAC strip; all point into `__text`):
`0xa0000, 0xa010c, 0xa016c, 0xa024c, 0xa0304, 0xa0478, 0xa0960, 0xa0e54, 0xa0ee8, 0xa1040, 0xa12c4,
0xa1270, 0xa14ac, 0xa14f8, 0xa151c, 0xa1580, 0xa1590, 0xa1710, 0xa175c, 0xa17ac, 0xe7100 (=FUN_000e7100),
0xe71c4 (=FUN_000e71c4), 0xe71d8 (=FUN_000e71d8)`. Event 2 → `0xa024c` is the common dispatch-call
handler (many states, flags=0x1 validate); event 5 → `0xa0478` is the exception-return restore path;
event 6 → `0xe7100` hands exceptions to XNU. Most `0xa0xxx` handlers are in **unanalyzed** regions.

### D2. Domain/table dispatch table — base `0x95470` (in `__LATE_CONST`) — HIGH confidence (structure) / LOW (content)
Indexed `[domain][SPTM_DISPATCH_TABLE_*]`: **domain stride 0x180, entry 0x18**, 16 table slots per
domain (tables 0..14 = `SPTM_DISPATCH_TABLE_*`, 15=INVALID). Entry fields: `+0x0` entry-point,
`+0x8` permissions bitmask (checked `>> cpu_state & 1`), `+0x10` reserved. Base for domains 0/3/4 is the
constant `0x95470`; XNU/TXM (domains 1/2) use the runtime pointer `DAT_00095bf0`. **Statically almost
empty**: only `domain=0 table=14` (INVALID) carries `perms=0x2` (`entry=0x0`); `DAT_00095bf0 == 0`.
→ The table is populated at runtime by `sptm_register_dispatch_table` (each domain registers its
entry-point + permission mask during bootstrap), so static entries are not resolvable to `FUN_xxx`.

### D3. `__auth_ptr` PAC-signed function pointers — `0x100010` — HIGH confidence
`__DATA.__auth_ptr` (0x18 bytes) holds two identical PAC-signed pointers (address portion `0xae464`,
PAC `0x80` in bits 63:56) → a `bti c` landing pad at `0xae464` (stack-probe/guard routine). Xrefs
from `0xae68c` and `0x136c0`.

---

## (e) Register/CPU interface & per-CPU state area

- **Public API** (`sptm_xnu.h:1773` `sptm_register_cpu(uint64_t physical_id)`; `sptm_common.h:1429`
  `sptm_get_cpu_state(sptm_logical_cpu_id, libsptm_cpu_state_t, bool*)`).
- **Per-CPU state base**: `tpidr_el1 = cpu_id << 14` (set at per-CPU bootstrap `0x9c044`), so each CPU's
  state struct occupies 0x4000 bytes. Boot also stores a pointer to the current CPU's dispatch state at
  **`[0xaa018]`** (global struct at `0xaa000`). — MEDIUM confidence
- **Per-CPU dispatch-state struct fields observed** (base = tpidr_el1, offsets from the decompiled
  dispatcher + GEXIT/exception code): `+0xa30` state byte (also written by vector handlers),
  `+0xa38`/`+0xa40` scratch, `+0xa50`, `+0xa60` **current dispatch-state index**, `+0xa68` **nesting
  counter** (hop depth), `+0xa70..+0xa80` saved `x0..x7` (call regs), `+0xa80..+0xaa8` saved regs,
  `+0xab0`/`+0xb68` callee-saved save area (per hop), `+0xf80` current vector_type. The GEXIT restore
  path (`0xa0478` etc.) reloads x19–x28/d8–d15/sp_el0/elr from `tpidr_el1+0xa70` region then `GEXIT`.

---

## Confidence summary
| Item | Address | Confidence |
|---|---|---|
| Boot entry (trampoline) | 0xa8388 | HIGH |
| Boot entry (real) | 0xab000 | HIGH |
| Per-CPU bootstrap | 0x9c000 | MEDIUM |
| Vector table #1 (VBAR) | 0xa9000 (16×0x80) | HIGH |
| Vector table #2 (VBAR) | 0x9d000 (16×0x80) | MEDIUM |
| Dispatch/state engine | FUN_000e6bc0 @ 0xe6bc0 | HIGH |
| Context-save entries | 0xa0f7c / 0xa111c | HIGH |
| SPTM→TXM/SK entry stubs | 0xb25c0..0xb2698 | HIGH |
| GENTER site | 0xab8d8 | HIGH |
| GEXIT sites | 0xa0520,0xa095c,0xa0bf8,0xa0d7c,0xa126c,0xa170c,0xa2b50 | HIGH |
| State-transition table | 0x16770 | HIGH |
| Domain/table dispatch table | 0x95470 | HIGH struct / LOW content |
| __auth_ptr | 0x100010 → 0xae464 | HIGH |
| Per-CPU state | tpidr_el1 = cpu_id<<14 | MEDIUM |
| Exception→XNU handoff | FUN_000e7100 @ 0xe7100 | HIGH |

Security note: the vector handlers end in a `0xdead` `wfe` panic spin and the state machine refuses
illegal transitions with a panic, matching the SPTM's "cannot gracefully fail" contract — the dispatch
tables (`0x95470`, `0x16770`) and the `GEXIT` sites (0xa0520 etc.) are the highest-value
decompilation targets to audit for transition/permission bypass.
