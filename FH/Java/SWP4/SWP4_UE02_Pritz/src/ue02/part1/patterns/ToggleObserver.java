package ue02.part1.patterns;

public abstract class ToggleObserver implements Observer {

    private boolean active = true;

    public void toggle() {
        active = !active;
    }

    public boolean isActive() {
        return active;
    }
}
