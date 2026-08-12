# Security findings log — ring −1 (SPTM / TXM / Secure Kernel)

Every agent MUST append security-relevant observations here while decompiling.
Template (same as the hypervisor findings):

```markdown
## [<tree>] <address> <estimated_name>
- **Observation**: <what you noticed>
- **Evidence**: <Ghidra facts: instruction/offset/global/call>
- **Severity (hypothesis)**: informational | low | medium | high
- **Confidence**: high | medium | low
```

No entry without Evidence. Severity is a hypothesis, never a claim. These feed
`docs/sptm/audit.md` at the end of the project.
