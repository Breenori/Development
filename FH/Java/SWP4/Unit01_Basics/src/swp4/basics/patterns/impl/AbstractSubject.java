package swp4.basics.patterns.impl;

import swp4.basics.patterns.Observer;
import swp4.basics.patterns.Subject;

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
