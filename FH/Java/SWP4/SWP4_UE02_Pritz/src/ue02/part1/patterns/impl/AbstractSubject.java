package ue02.part1.patterns.impl;


import ue02.part1.patterns.Observer;
import ue02.part1.patterns.Subject;

import java.util.HashSet;
import java.util.Set;

public abstract class AbstractSubject implements Subject {

    protected Set<Observer> registeredObservers = new HashSet<>();
    private int currentId = 0;

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

    public void notifyObserver(long noteId, String aspect) {
        for(Observer observer : registeredObservers) {
            observer.update(this, getState(), noteId, aspect);
        }
        currentId++;
    }

    @Override
    public void notifyObserver(long noteId) {
        notifyObserver(noteId, "default");
    }


    public abstract Object getState();
}
