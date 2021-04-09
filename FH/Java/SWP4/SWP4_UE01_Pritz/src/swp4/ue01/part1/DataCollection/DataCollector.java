package swp4.ue01.part1.DataCollection;

import java.io.FileWriter;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

public class DataCollector {
    int charCmp;
    int logOp;
    int addOp;
    int multOp;
    int indOp;
    int cmp;
    int assOp;
    Map<Character,CharacterStat> charCmpTable;

    public DataCollector() {
        charCmp = 0;
        logOp = 0;
        addOp = 0;
        multOp = 0;
        indOp = 0;
        cmp = 0;
        assOp = 0;
        charCmpTable = new HashMap<>();
    }

    public void clear() {
        charCmp = 0;
        logOp = 0;
        addOp = 0;
        multOp = 0;
        indOp = 0;
        cmp = 0;
        assOp = 0;
        charCmpTable.clear();
    }

    public void logCharCmp(char letter, boolean success) {
        charCmp++;
        CharacterStat stat = charCmpTable.get(letter);
        if(stat != null) {
            stat.updateStats(success);
        } else {
            charCmpTable.put(letter, new CharacterStat());
            charCmpTable.get(letter).updateStats(success);
        }
    }
    public void logLogOp() {
        logOp++;
    }
    public void logAddOp() {
        addOp++;
    }
    public void logMultOp() {
        multOp++;
    }
    public void logIndOp() {
        indOp++;
    }
    public void logCmp() {
        cmp++;
    }
    public void logAssOp() {
        assOp++;
    }

    public void logLogOp(int amount) {
        logOp+=amount;
    }
    public void logAddOp(int amount) {
        addOp+=amount;
    }
    public void logMultOp(int amount) {
        multOp+=amount;
    }
    public void logIndOp(int amount) {
        indOp+=amount;
    }
    public void logCmp(int amount) {
        cmp+=amount;
    }
    public void logAssOp(int amount) {
        assOp+=amount;
    }

    public void printStatistics() {
        System.out.println("Statistics of comparison:");
        System.out.println("Chars compared:\t\t\t\t"+charCmp);
        System.out.println("Logical operations:\t\t\t"+logOp);
        System.out.println("Additive operations:\t\t\t"+addOp);
        System.out.println("Multiplicative operations:\t"+multOp);
        System.out.println("Index operations:\t\t\t"+indOp);
        System.out.println("Attempted comparisons:\t\t"+cmp);
        System.out.println("Assignment operations:\t\t"+assOp);
    }

    public void writeToFile(String filename) {
        try(FileWriter fout = new FileWriter(filename)) {
            fout.write("Statistics of comparison:\n");
            fout.write("Characters compared;Logical operations;Additive operations;Multiplicative operations;Index operations;Attempted comparisons;Assignment operations;\n");
            fout.write(charCmp+";"+logOp+";"+addOp+";"+multOp+";"+indOp+";"+cmp+";"+assOp+"\n");
            fout.write("\n");

            String successLine = "";
            String failLine = "";
            for(char key : charCmpTable.keySet()) {
                fout.write(key+";");
                successLine += charCmpTable.get(key).getSuccessfulComparisons()+";";
                failLine += charCmpTable.get(key).getFailedComparisons()+";";
            }
            fout.write("\n");
            fout.write(successLine+"\n");
            fout.write(failLine+"\n");

        } catch(IOException e)
        {
            System.out.println("Coult not write to file: " + filename);
            e.printStackTrace();
        }
    }
}
