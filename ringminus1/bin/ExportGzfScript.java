//ExportGzfScript.java — postScript: write the imported program as a GZF packed file.
//@category Export
import ghidra.app.script.GhidraScript;
import ghidra.util.task.ConsoleTaskMonitor;
import ghidra.framework.model.DomainFile;
import ghidra.util.task.TaskMonitor;
import java.io.File;

public class ExportGzfScript extends GhidraScript {
    @Override
    public void run() throws Exception {
        String out = System.getenv("GZF_OUT");
        if (out == null) {
            out = "/Users/gabesmall/macvisor/ringminus1/gzfs/" + currentProgram.getName() + ".gzf";
        }
        TaskMonitor monitor = new ConsoleTaskMonitor();
        DomainFile df = currentProgram.getDomainFile();
        df.packFile(new File(out), monitor);
        println("GZF written: " + out);
    }
}
