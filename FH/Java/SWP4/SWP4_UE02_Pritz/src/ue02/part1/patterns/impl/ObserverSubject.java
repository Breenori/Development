package ue02.part1.patterns.impl;

import ue02.part1.patterns.Observer;
import ue02.part1.patterns.Subject;


public abstract class ObserverSubject extends AbstractSubject implements Observer {


    public ObserverSubject() {

    }

    public void setActive() {
        UpdateOnceChangeManager.getInstance().activateObserver(this);
    }
    public void setInactive() {
        UpdateOnceChangeManager.getInstance().deactivateObserver(this);
    }
    public boolean isActive() {
        return UpdateOnceChangeManager.getInstance().isActive(this);
    }

    public void attachObserver(Observer observer) {
        UpdateOnceChangeManager.getInstance().attachObserver(this,observer);
    }
    public void detachObserver(Observer observer) {
        UpdateOnceChangeManager.getInstance().detachObserver(this,observer);
    }

    public void subscribeAspect(String aspect) {
        UpdateOnceChangeManager.getInstance().subscribeAspect(this,aspect);
    }
    public void unsubscribeAspect(String aspect) {
        UpdateOnceChangeManager.getInstance().unsubscribeAspect(this,aspect);
    }

    public void block(Observer observer) {
        UpdateOnceChangeManager.getInstance().block(this, observer);
    }
    public void unblock(Observer observer) {
        UpdateOnceChangeManager.getInstance().unblock(this, observer);
    }

    @Override
    public void update(Subject source, Object argument, long noteId, String aspect) {
        System.out.println("Observer: " + this + " received "+aspect+" notification (ID="+noteId+") from: " + source + " with argument: " + argument);
    }

}
