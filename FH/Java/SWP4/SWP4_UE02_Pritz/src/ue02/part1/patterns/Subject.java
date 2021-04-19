package ue02.part1.patterns;

public interface Subject {
    void attach(Observer observer);
    void detach(Observer observer);
    void notifyObserver();
}
