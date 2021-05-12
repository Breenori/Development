package swp4.ue03.protocol.impl;

import swp4.ue03.components.impl.MemoryComponent;
import swp4.ue03.components.impl.NetworkComponent;
import swp4.ue03.profiling.Subject;
import swp4.ue03.protocol.Protocol;

import java.util.*;

public class NetworkProtocol implements Protocol {
    private static NetworkProtocol networkProtocol = null;

    private NetworkProtocol() { }

    public static NetworkProtocol getInstance() {
        if(networkProtocol == null) {
            networkProtocol = new NetworkProtocol();
        }
        return networkProtocol;
    }

    @Override
    public Map<String, List<Integer>> evaluateData(Map<Subject, Map<String, List<Integer>>> storedData, int seconds) {
        Map<String, List<Integer>> tmp = new HashMap<>();

        // Search for the right components
        for(Subject subject : storedData.keySet()) {
            if (subject instanceof NetworkComponent) {
                // iterate through all the metrics for the right component and filter for time
                for (String key : storedData.get(subject).keySet()) {
                    ArrayList<Integer> current = (ArrayList<Integer>) storedData.get(subject).get(key);
                    int begin = seconds == 0 ? 0 : Math.max(current.size() - seconds, 0);
                    tmp.put(((NetworkComponent)subject).getName()+";"+key, current.subList(begin, current.size()));
                }
            }
        }

        return tmp;
    }

    @Override
    public Map<String, List<Integer>> evaluateData(Map<Subject, Map<String, List<Integer>>> storedData) {
        return evaluateData(storedData, 0);
    }
}
