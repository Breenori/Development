package ue02.part1.patterns.impl;

import ue02.part1.patterns.Observer;
import ue02.part1.patterns.Subject;

import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;

public class ChangeManager {
    private static ChangeManager instance = null;
    private Map<Subject, Set<Observer>> observers = new HashMap<>();
    private ChangeCollector collector = new ChangeCollector();

    private ChangeManager() {}

    public static ChangeManager getInstance() {
        if(instance == null) {
            instance = new ChangeManager();
        }
        return instance;
    }

    public void attachObserver(Subject subject, Observer observer) {
        if(!observers.containsKey(subject))
        {
            observers.put(subject, new HashSet<>());
        }
        Set<Observer> obs = observers.get(subject);
        obs.add(observer);

        subject.attach(collector);
        // TODO: change manager registers itself as observer
    }

    private class ChangeCollector implements Observer {

        public void toggle() {

        }

        @Override
        public void update(Subject source, Object argument) {
            Set<Observer> obs = observers.get(source);
            for(Observer observer : obs) {
                System.out.print("From ChangeManager - ");
                // forward update to actual observers
                observer.update(source, argument);
            }
        }
    }
}
