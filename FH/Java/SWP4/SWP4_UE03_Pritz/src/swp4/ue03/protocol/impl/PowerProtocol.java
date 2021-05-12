package swp4.ue03.protocol.impl;

import swp4.ue03.components.impl.MemoryComponent;
import swp4.ue03.components.impl.NetworkComponent;
import swp4.ue03.components.impl.PowerComponent;
import swp4.ue03.profiling.Subject;
import swp4.ue03.protocol.Protocol;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class PowerProtocol implements Protocol {

    private static PowerProtocol psuProtocol = null;

    private PowerProtocol() { }

    public static PowerProtocol getInstance() {
        if(psuProtocol == null) {
            psuProtocol = new PowerProtocol();
        }
        return psuProtocol;
    }

    @Override
    public Map<String, List<Integer>> evaluateData(Map<Subject, Map<String, List<Integer>>> storedData, int seconds) {
        Map<String, List<Integer>> tmp = new HashMap<>();

        // Search for the right components
        for(Subject subject : storedData.keySet()) {
            if (subject instanceof PowerComponent) {
                // iterate through all the metrics for the right component and filter for time
                for (String metric : storedData.get(subject).keySet()) {
                    ArrayList<Integer> current = (ArrayList<Integer>) storedData.get(subject).get(metric);
                    int begin = seconds == 0 ? 0 : Math.max(current.size() - seconds, 0);
                    tmp.put(((PowerComponent)subject).getName()+";"+metric, current.subList(begin, current.size()));
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
