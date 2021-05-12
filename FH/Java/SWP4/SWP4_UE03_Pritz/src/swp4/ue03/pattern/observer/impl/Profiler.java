package swp4.ue03.pattern.observer.impl;

import swp4.ue03.pattern.composite.Metric;
import swp4.ue03.pattern.observer.Observer;
import swp4.ue03.pattern.observer.Subject;

import java.util.List;
import java.util.Map;

public class Profiler implements Observer {

    Map<Subject, List<Metric>> loggedMetrics;

    @Override
    public void update(Subject source, Object argument) {
        System.out.println("Observer: " + this + " received notification from: " + source + " with argument: " + argument);
    }
}
