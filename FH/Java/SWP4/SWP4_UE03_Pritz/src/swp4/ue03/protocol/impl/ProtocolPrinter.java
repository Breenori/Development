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

    // filter the given data depending on the attached protocols
    // return data as a sorted TreeMap
    public synchronized TreeMap<String, List<Integer>> filter(Map<Subject, Map<String, List<Integer>>> totalData, int mins) {
        Map<String, List<Integer>> concData = new ConcurrentHashMap<>();

        for(Protocol protocol : protocolList) {
            // evaluate each subprotocol and add the metrics to the map
            Map<String, List<Integer>> evaluatedData = protocol.evaluateData(totalData, mins);
            for(String metric : evaluatedData.keySet()) {
                concData.put(metric, evaluatedData.get(metric));
            }
        }

        return new TreeMap<>(concData);
    }

    public synchronized void print(protocolType type, String filename, Map<Subject, Map<String, List<Integer>>> totalData, int seconds) {
        TreeMap<String, List<Integer>> evalData = filter(totalData, seconds);

        // If protocol should be numeric, print min/max/avg/median to console
        if(type == protocolType.NUMBER) {
            for(String metric : evalData.keySet()) {
                List<Integer> curValues = Collections.synchronizedList(evalData.get(metric));
                double min = curValues.stream().mapToDouble(d -> d).min().orElse(0.0);
                double max = curValues.stream().mapToDouble(d -> d).max().orElse(0.0);
                double avg = curValues.stream().mapToDouble(d -> d).average().orElse(0.0);
                double median = curValues.size()%2==0 ? (curValues.get(curValues.size()/2-1)+curValues.get(curValues.size()/2)) : curValues.get(curValues.size()/2);
                System.out.println(metric+": "+min+", "+max+", "+avg+", "+median);
            }
        } else { // if it should be printed as csv, open a new file to write
            try(FileWriter fout = new FileWriter(filename)) {
                fout.write(String.join(",",evalData.keySet())+"\n");

                // determine linecount, if period exceeds the components time alive then we print less lines
                // get the maximum amount of entries
                int linecount = 0;
                for(String metric : evalData.keySet()) {
                    linecount = Math.max(linecount, evalData.get(metric).size());
                }

                // print all metrics that are available in the given period
                for(int i=0; i < linecount; i++) {
                    boolean first = true;
                    // go through all metrics, every line
                    for(String metric:evalData.keySet()) {
                        if(first) {
                            first = false;
                        } else {
                            fout.write(",");
                        }
                        // print the metric in a comma separated fashion
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

    public synchronized void print(protocolType type, Map<Subject, Map<String, List<Integer>>> totalData, int seconds) {
        if(type == protocolType.NUMBER) {
            print(type, "",totalData, seconds);
        } else {
            System.err.println("To use the CSV output the filename field is mandatory!");
        }
    }

    // add a protocol to the ProtocolPrinter, so it knows what to print
    public void addProtocol(Protocol protocol) {
        protocolList.add(protocol);
    }
}
