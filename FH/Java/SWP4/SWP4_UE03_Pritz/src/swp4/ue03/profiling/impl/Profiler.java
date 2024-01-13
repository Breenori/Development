package swp4.ue03.profiling.impl;

import swp4.ue03.components.Component;
import swp4.ue03.profiling.Observer;
import swp4.ue03.profiling.Subject;
import swp4.ue03.protocol.Protocol;
import swp4.ue03.protocol.impl.ProtocolPrinter;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.ConcurrentMap;

public class Profiler implements Observer {

    // Profilers save EVERYTHING the components send them.
    private ConcurrentMap<Subject, Map<String, List<Integer>>> metricStorage = new ConcurrentHashMap<>();
    //  It is the ProtocolPrinters job to filter the data and print it.
    private ProtocolPrinter protocolPrinter = new ProtocolPrinter();
    // The user can set thresholds for specific metrics, so warnings will be sent
    private Map<String, Integer> thresholds = new ConcurrentHashMap<>();


    public void print(ProtocolPrinter.protocolType type, int seconds, String filename) {
        // delegate to protocolPrinter
        protocolPrinter.print(type, filename, metricStorage, seconds);
    }

    public void print(ProtocolPrinter.protocolType type, int seconds) {
        if(type != ProtocolPrinter.protocolType.NUMBER) {
            System.err.println("print method with CSV option requires filename.");
        } else {
            print(type, seconds, "");
        }
    }

    public void addThreshold(String name, int thresh) {
        thresholds.put(name,thresh);
    }

    // Add a protocol to the ProtocolPrinter, to define what to print
    public void addProtocol(Protocol protocol) {
        protocolPrinter.addProtocol(protocol);
    }

    // Everytime the Profiler receives an update, he runs through all metrics and adds them to the metricStorage
    @Override
    public synchronized void update(Subject source, Object argument) {
        if(argument != null && source != null) {
            // if the profiler has never received something from this component, add it to the map
            metricStorage.computeIfAbsent(source, tmp -> new HashMap<>());

            // go through all the metrics per subject and add them to the storage
            for (String metric : ((Map<String, List<Integer>>) argument).keySet()) {
                int value = (int)((Map) argument).get(metric);
                metricStorage.get(source).computeIfAbsent((String) metric, tmp -> new ArrayList<>());
                metricStorage.get(source).get(metric).add(value);

                // additionally, if thresholds have been set, check if they have been exceeded and print a warning
                for(String importantMetric : thresholds.keySet()) {
                    if(metric.contains(importantMetric) && value >= thresholds.get(importantMetric)) {
                        System.out.println("WARNING: Sensor "+metric+" exceeded threshold! ("+value+")");
                    }
                }
            }

            //System.out.println(this + " profiler received update from " + source + ": " + argument);
        }
    }
}
