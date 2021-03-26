package swp4.basics.test;

import swp4.basics.patterns.impl.ConcreteObserver;
import swp4.basics.patterns.impl.TimerSubject;

public class ObserverTest {

    public static void main(String[] args) {
        TimerSubject subject = new TimerSubject(10,1000);
        subject.attach(new ConcreteObserver());
        subject.runTimer();
    }
}
