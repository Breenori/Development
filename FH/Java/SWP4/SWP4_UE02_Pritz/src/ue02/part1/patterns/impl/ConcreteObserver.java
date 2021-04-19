package ue02.part1.patterns.impl;

import ue02.part1.patterns.Observer;
import ue02.part1.patterns.Subject;
import ue02.part1.patterns.ToggleObserver;

public class ConcreteObserver extends ToggleObserver {

    @Override
    public void update(Subject source, Object argument) {
        System.out.println("Observer: " + this + " received notification from: " + source + " with argument: " + argument);
    }
}
