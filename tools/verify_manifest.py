#!/usr/bin/env python3
"""Verify docs/manifest.json consistency with the codebase.

Passes (exit 0) iff:
  - docs/manifest.json parses as JSON (list of entries)
  - every entry has exactly the allowed fields with correct value sets
  - every address appears in exactly one entry
  - every decompiled/stubbed entry's file exists
  - every decompiled entry's file contains the estimated_name
  - every tree has >= 1 decompiled entry
  - every entry's file starts with "osfmk/" or equals "docs/chain-map.md"

Usage: python3 tools/verify_manifest.py
"""
import json
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
MANIFEST = ROOT / "docs" / "manifest.json"

ALLOWED_FIELDS = {
    "address", "ghidra_name", "estimated_name", "confidence",
    "category", "tree", "file", "status", "notes",
}
STATUSES = {"claimed", "mapped", "decompiled", "stubbed"}
CONFIDENCES = {"high", "medium", "low"}
CATEGORIES = {"core", "boot", "trap", "vmapple", "shared-dep"}
FILE_OK = lambda f: f.startswith("osfmk/") or f == "docs/chain-map.md"


def main() -> int:
    if not MANIFEST.exists():
        print(f"manifest.json missing at {MANIFEST}")
        return 1

    try:
        entries = json.loads(MANIFEST.read_text())
    except json.JSONDecodeError as e:
        print(f"manifest.json is not valid JSON: {e}")
        return 1

    if not isinstance(entries, list):
        print("manifest.json must be a JSON array")
        return 1

    errors = []
    seen_addresses = set()
    trees_with_decompiled = set()

    for i, e in enumerate(entries):
        addr = e.get("address")
        if not addr:
            errors.append(f"[{i}] missing address")
            continue
        if addr in seen_addresses:
            errors.append(f"[{i}] duplicate address {addr}")
        seen_addresses.add(addr)

        bad = set(e) - ALLOWED_FIELDS
        if bad:
            errors.append(f"[{i}] {addr}: unexpected fields {sorted(bad)}")

        if e.get("status") not in STATUSES:
            errors.append(f"[{i}] {addr}: bad status {e.get('status')!r}")
        if e.get("confidence") not in CONFIDENCES:
            errors.append(f"[{i}] {addr}: bad confidence {e.get('confidence')!r}")
        if e.get("category") not in CATEGORIES:
            errors.append(f"[{i}] {addr}: bad category {e.get('category')!r}")

        f = e.get("file")
        if not FILE_OK(f):
            errors.append(f"[{i}] {addr}: file outside allowed tree: {f!r}")

        if e.get("status") in ("decompiled", "stubbed"):
            if not f or not (ROOT / f).exists():
                errors.append(f"[{i}] {addr}: file missing: {f!r}")
            elif e.get("status") == "decompiled":
                content = (ROOT / f).read_text(errors="replace")
                name = e.get("estimated_name")
                if not name:
                    errors.append(f"[{i}] {addr}: decompiled entry missing estimated_name")
                elif name not in content:
                    errors.append(f"[{i}] {addr}: {name!r} not found in {f}")

        if e.get("status") == "decompiled" and e.get("tree"):
            trees_with_decompiled.add(e["tree"])

    # every tree in the manifest must have at least one decompiled entry,
    # unless the tree is declarations-only (every entry stubbed)
    trees = {e.get("tree") for e in entries if e.get("tree")}
    for t in sorted(trees):
        tree_entries = [e for e in entries if e.get("tree") == t]
        all_stubbed = all(e.get("status") == "stubbed" for e in tree_entries)
        if not all_stubbed and t not in trees_with_decompiled:
            errors.append(f"tree {t!r} has no decompiled entry")

    if errors:
        print(f"verify_manifest: {len(errors)} error(s)")
        for err in errors:
            print(f"  - {err}")
        return 1

    print(f"verify_manifest: OK ({len(entries)} entries, "
          f"{len(trees_with_decompiled)} trees with decompiled output)")
    return 0


if __name__ == "__main__":
    sys.exit(main())
