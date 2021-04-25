package ue02.part1.patterns.impl;

import ue02.part1.patterns.Observer;
import ue02.part1.patterns.Subject;

import java.util.*;
import java.util.concurrent.ConcurrentLinkedDeque;
import java.util.concurrent.ConcurrentLinkedQueue;

public class UpdateOnceChangeManager {
    private static UpdateOnceChangeManager instance = null;
    private Map<Subject, Set<Observer>> observers = new HashMap<>();
    private Map<Observer, Boolean> observerActivity = new HashMap<>();
    private Map<Observer, Queue<Message>> messageBuffer = new HashMap<>();
    private Map<Observer, Set<Long>> noteIdMap = new HashMap<>();
    private Map<Observer, Set<String>> observerAspects = new HashMap<>();
    private Map<Subject, Set<Observer>> blocked = new HashMap<>();

    private ChangeCollector collector = new ChangeCollector();

    private UpdateOnceChangeManager() {}

    public static UpdateOnceChangeManager getInstance() {
        if(instance == null) {
            instance = new UpdateOnceChangeManager();
        }
        return instance;
    }

    public void activateObserver(Observer observer) {
        observerActivity.put(observer,true);

        // if observer was previously inactive, send all the buffered messages
        if(messageBuffer.containsKey(observer) && !messageBuffer.get(observer).isEmpty())
        {
            System.out.println("Notifications during inactivity:");
            while(!messageBuffer.get(observer).isEmpty()) {
                Message message = messageBuffer.get(observer).remove();
                collector.update(message.getSubject(), message.getArgument(), message.getId(), message.getAspect());
            }
        }
    }
    public void deactivateObserver(Observer observer) {
        observerActivity.put(observer,false);
    }
    public boolean isActive(Observer observer) {
        if(observerActivity.containsKey(observer)) {
            return observerActivity.get(observer);
        } else
        {
            return true;
        }

    }

    public void attachObserver(Subject subject, Observer observer) {
        if(!observers.containsKey(subject))
        {
            observers.put(subject, new HashSet<>());
        }
        if(!isBlocked(subject, observer)) {
            Set<Observer> obs = observers.get(subject);
            obs.add(observer);
            subject.attach(collector);
        } else {
            observer.update(subject, "Blocked from observation.", -1, "block");
        }


    }
    public void detachObserver(Subject subject, Observer observer) {
        if(observers.containsKey(subject))
        {
            observers.get(subject).remove(observer);
        }
    }

    public void subscribeAspect(Observer observer, String aspect) {
        if(!observerAspects.containsKey(observer)) {
            observerAspects.put(observer, new HashSet<>());
        }
        observerAspects.get(observer).add(aspect);
    }
    public void unsubscribeAspect(Observer observer, String aspect) {
        if(observerAspects.containsKey(observer)) {
            observerAspects.get(observer).remove(aspect);
        }
    }

    public void block(Subject subject, Observer observer) {
        if(!blocked.containsKey(subject)) {
            blocked.put(subject, new HashSet<>());
        }
        blocked.get(subject).add(observer);
    }
    public void unblock(Subject subject, Observer observer) {
        if(blocked.containsKey(subject)) {
            blocked.get(subject).remove(observer);
        }
    }
    public boolean isBlocked(Subject subject, Observer observer) {
        if(!blocked.containsKey(subject)) {
            return false;
        }

        return blocked.get(subject).size()>0 && blocked.get(subject).contains(observer);
    }

    private boolean observerWants(Observer observer, String aspect) {
        if(observerAspects.containsKey(observer) && observerAspects.get(observer).size()>0 && !observerAspects.get(observer).contains(aspect)) {
            return false;
        }

        return true;
    }

    private class ChangeCollector implements Observer {
        @Override
        public void update(Subject source, Object argument, long noteId, String aspect) {
            Set<Observer> obs = observers.get(source);
            for(Observer observer : obs) {
                if(isActive(observer)) {
                    // forward update to actual observers
                    if(!noteIdMap.containsKey(observer))
                    {
                        noteIdMap.put(observer, new HashSet<>());
                    }

                    if(!noteIdMap.get(observer).contains(noteId))
                    {
                        noteIdMap.get(observer).add(noteId);
                        if(observerWants(observer, aspect)) {
                            System.out.print("From ChangeManager - ");
                            observer.update(source, argument, noteId, aspect);
                        }
                    }
                } else {
                    if(observerWants(observer, aspect)) {
                        if(!messageBuffer.containsKey(observer)) {
                            messageBuffer.put(observer, new ConcurrentLinkedQueue<>());
                        }
                        messageBuffer.get(observer).add(new Message(source, argument, noteId,aspect));
                    }
                }
            }
        }
    }

    private class Message {
        private Subject subject;
        private Object argument;
        private long id;
        private String aspect;

        public Message(Subject subject, Object argument, long id, String aspect) {
            this.subject = subject;
            this.argument = argument;
            this.id = id;
            this.aspect = aspect;
        }

        public Subject getSubject() {
            return subject;
        }
        public Object getArgument() {
            return argument;
        }
        public long getId() { return id;}
        public String getAspect() {
            return aspect;
        }
    }
}
