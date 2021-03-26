package swp4.basics.patterns.impl;

import swp4.basics.patterns.Observer;
import swp4.basics.patterns.Subject;

public class ConcreteObserver implements Observer {
    @Override
    public void update(Subject source, Object argument) {
        System.out.println("Observer: " + this + " received notification from: " + source + " with argument: " + argument);
    }
}
