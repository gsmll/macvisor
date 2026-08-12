# Secure Kernel (GL1) — cL4 microkernel decompilation

Target: `ringminus1/sk/cl4_kernel.raw` (6.9 MB arm64e Mach-O extracted from
`exclavecore_bundle.t8142.RELEASE.im4p`). Ghidra program `cl4_kernel.raw`,
image base 0, **18,248 functions** (0x11c0..0x687da8). Version string:
"cL4 microkernel (cL4 (679.100.61))".

- cL4 is Apple's seL4-derived microkernel. Recreated code goes in
  `osfmk/arm64/sk/sk_region_*.c`.
- Names: use seL4/cL4 vocabulary (threads, caps, IPC, sched, vspace,
  notification, endpoints, CNode, TCB, etc.); confidence medium unless a
  string/header matches (high).
- Same contract as docs/sptm/AGENTS.md + WORKER.md: English-first, no stubs,
  manifest claim protocol, findings log, GENTER/GEXIT opaque.
- Wave batches are RANGE-based: each worker calls list_functions (limit
  20000, program cl4_kernel.raw) itself and filters to its address range.
