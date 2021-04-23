package ue02.part1.patterns.impl;

import ue02.part1.patterns.Observer;
import ue02.part1.patterns.Subject;

import java.util.ArrayList;


public class ToggleObserver implements Observer {

    private boolean active = true;

    public void toggle() {
        active = !active;
    }

    public boolean isActive() {
        return active;
    }

    @Override
    public void update(Subject source, Object argument) {
        System.out.println("Observer: " + this + " received notification from: " + source + " with argument: " + argument);
    }
}
