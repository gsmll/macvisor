# ring −1 call-graph map (SPTM / TXM / Secure Kernel)

Call-graph edges discovered while decompiling. Append with both addresses:
`FUN_0009c2c8 (sptm_map_page) → FUN_0009d000 (sptm_retype)`.

## Entry surfaces (to map)

- GENTER entry stub + guarded-level dispatch (x16 selector decode)
- SPTM exception vectors (SPTM_VECTOR_IRQ/FIQ/SERROR/SYNC)
- SPTMArgs bootstrap (SPTM runs before XNU)
- Dispatch tables: XNU_BOOTSTRAP, TXM_BOOTSTRAP, SK_BOOTSTRAP, DART/SART/NVME/UAT/SHART/HIB
