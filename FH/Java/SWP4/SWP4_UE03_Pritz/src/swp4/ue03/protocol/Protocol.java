package swp4.ue03.protocol;

import swp4.ue03.profiling.Subject;

import java.util.List;
import java.util.Map;

public interface Protocol {

    // every protocol needs to know how to evaluate data
    Map<String, List<Integer>> evaluateData(Map<Subject, Map<String, List<Integer>>> storedData, int seconds);
    Map<String, List<Integer>> evaluateData(Map<Subject, Map<String, List<Integer>>> storedData);

}
