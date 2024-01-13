package swp4.ue03.components;

import swp4.ue03.profiling.Subject;

import java.util.*;

public interface Component extends Subject, Runnable {

    // saves all metrics for all components
    Set<String> reservedNames = new HashSet<>();

    // every component has an ID and a name which they can be identified with
    int getId();
    String getName();

    // every component has an activity status and can be turned off to stop data generation
    void turnOff();
    boolean isActive();

    // if users want to find out which metrics
    Set<String> getMetricNames();

    // When writing new components, they have to register their metrics to avoid duplicates between components
    boolean registerMetrics(List<String> names);

    // check if a metric exists
    static boolean metricExists(String name) {
        return reservedNames.contains(name);
    }
}
