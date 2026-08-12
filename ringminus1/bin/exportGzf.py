# exportGzf.py — postScript: write the imported program as a GZF packed file.
# @category Export
from ghidra.util.task import ConsoleTaskMonitor
from java.io import File
import os

name = currentProgram.getName()
out = os.environ.get("GZF_OUT", "/tmp/ringminus1/" + name + ".gzf")
df = currentProgram.getDomainFile()
monitor = ConsoleTaskMonitor()
df.saveToPackedFile(File(out), monitor)
print("GZF written: " + out)
