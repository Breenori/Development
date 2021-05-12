package swp4.ue03.protocol.impl;

import swp4.ue03.components.Component;
import swp4.ue03.components.impl.MemoryComponent;
import swp4.ue03.profiling.Subject;
import swp4.ue03.protocol.Protocol;

import java.io.FileWriter;
import java.io.IOException;
import java.util.*;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.ConcurrentMap;

public class ProtocolPrinter {
    List<Protocol> protocolList = new ArrayList<>();
    public enum protocolType{NUMBER,CSV}

    public synchronized TreeMap<String, List<Integer>> filter(Map<Subject, Map<String, List<Integer>>> totalData, int mins) {
        Map<String, List<Integer>> concData = new ConcurrentHashMap<>();

        for(Protocol protocol : protocolList) {
            Map<String, List<Integer>> evaluatedData = protocol.evaluateData(totalData, mins);
            for(String metric : evaluatedData.keySet()) {
                concData.put(metric, evaluatedData.get(metric));
            }
        }

        return new TreeMap<>(concData);
    }

    public synchronized void print(protocolType type, String filename, Map<Subject, Map<String, List<Integer>>> totalData, int seconds) {
        TreeMap<String, List<Integer>> evalData = filter(totalData, seconds);

        if(type == protocolType.NUMBER) {
            for(String metric : evalData.keySet()) {
                List<Integer> curValues = Collections.synchronizedList(evalData.get(metric));
                double min = curValues.stream().mapToDouble(d -> d).min().orElse(0.0);
                double max = curValues.stream().mapToDouble(d -> d).max().orElse(0.0);
                double avg = curValues.stream().mapToDouble(d -> d).average().orElse(0.0);
                double median = curValues.size()%2==0 ? (curValues.get(curValues.size()/2-1)+curValues.get(curValues.size()/2)) : curValues.get(curValues.size()/2);
                System.out.println(metric+": "+min+", "+max+", "+avg+", "+median);
            }
        } else {
            try(FileWriter fout = new FileWriter(filename)) {
                fout.write(String.join(",",evalData.keySet())+"\n");
                int linecount = 0;
                for(String metric : evalData.keySet()) {
                    linecount = Math.max(linecount, evalData.get(metric).size());
                }

                for(int i=0; i < linecount; i++) {
                    boolean first = true;
                    for(String metric:evalData.keySet()) {
                        if(first) {
                            first = false;
                        } else {
                            fout.write(",");
                        }
                        if(i < evalData.get(metric).size()) {
                            fout.write(evalData.get(metric).get(i).toString());
                        }
                    }
                    fout.write("\n");
                }
            } catch(IOException e)
            {
                System.out.println("Could not write to file: " + filename);
                e.printStackTrace();
            }
        }
    }

    public void addProtocol(Protocol protocol) {
        protocolList.add(protocol);
    }
}
