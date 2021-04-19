package ue02.part1.patterns.impl;


import ue02.part1.patterns.Observer;
import ue02.part1.patterns.Subject;

import java.util.HashSet;
import java.util.Set;

public abstract class AbstractSubject implements Subject {

    private Set<Observer> registeredObservers = new HashSet<>();

    @Override
    public void attach(Observer observer) {
        if(observer != null) {
            registeredObservers.add(observer);
        }
    }

    @Override
    public void detach(Observer observer) {
        if(observer !=null) {
            registeredObservers.remove(observer);
        }
    }

    @Override
    public void notifyObserver() {
        for(Observer observer : registeredObservers) {
            observer.update(this, getState());
        }
    }

    public abstract Object getState();
}
