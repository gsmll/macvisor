# diag.py — dump available globals/API surface in the pyghidra CLI script context.
import sys
LOG = "/Users/gabesmall/macvisor/ringminus1/logs/pyghidra_diag.log"
with open(LOG, "w") as f:
    f.write("argv: " + repr(sys.argv) + "\n")
    g = sorted(globals().keys())
    f.write("globals: " + repr(g) + "\n")
    try:
        import pyghidra
        f.write("pyghidra attrs: " + repr([a for a in dir(pyghidra) if not a.startswith("_")]) + "\n")
    except Exception as e:
        f.write("pyghidra import err: " + repr(e) + "\n")
    for name in ("flat_api", "currentProgram", "state", "api"):
        f.write("%s defined: %s\n" % (name, name in dir()))
