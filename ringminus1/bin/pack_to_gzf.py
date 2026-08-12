# pack_to_gzf.py — pyghidra modern API: export a program from the ringminus1 project to GZF.
import sys, traceback

LOG = "/Users/gabesmall/macvisor/ringminus1/logs/pyghidra_run.log"
PROJECT_DIR = "/Users/gabesmall/macvisor/ringminus1/ghidra"
PROJECT_NAME = "ringminus1"
PROGRAM = sys.argv[1] if len(sys.argv) > 1 else "sptm.raw"
OUT = sys.argv[2] if len(sys.argv) > 2 else "/Users/gabesmall/macvisor/ringminus1/gzfs/" + PROGRAM + ".gzf"

def log(m):
    with open(LOG, "a") as f:
        f.write(m + "\n")

try:
    import pyghidra
    from java.io import File
    log("opening project " + PROJECT_DIR + " " + PROJECT_NAME)
    project = pyghidra.open_project(PROJECT_DIR, PROJECT_NAME)
    log("project opened; program path=/" + PROGRAM)
    with pyghidra.program_context(project, "/" + PROGRAM) as program:
        log("program loaded: " + program.getName())
        program.saveToPackedFile(File(OUT), pyghidra.task_monitor())
        log("GZF written: " + OUT)
except Exception:
    log("EXCEPTION:\n" + traceback.format_exc())
