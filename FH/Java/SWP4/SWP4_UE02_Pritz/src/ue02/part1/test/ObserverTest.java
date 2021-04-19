package ue02.part1.test;


import ue02.part1.patterns.impl.ConcreteObserver;
import ue02.part1.patterns.impl.TimerSubject;

public class ObserverTest {

    public static void main(String[] args) {
        TimerSubject subject = new TimerSubject(10,1000);
        subject.attach(new ConcreteObserver());
        subject.attach(new ConcreteObserver());
        subject.runTimer();
    }
}
