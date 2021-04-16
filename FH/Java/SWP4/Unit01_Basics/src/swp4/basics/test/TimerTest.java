package swp4.basics.test;

import swp4.basics.threading.Timer;
import swp4.basics.threading.impl.TimerImpl;
import swp4.basics.threading.impl.TimerListenerImpl;

public class TimerTest {
    public static void main(String[] args) {
        System.out.println("Sequential timer implementation:");
        Timer timer1 = new TimerImpl(10,100,"Timer 1");
        Timer timer2 = new TimerImpl(10,100,"Timer 2");

        timer1.addTimerListener(new TimerListenerImpl());
        timer2.addTimerListener(new TimerListenerImpl());

        timer1.start();
        timer2.start();

        System.out.println("-------------------");
        System.out.println("Concurrent timer implementation:");
        timer1 = new TimerImpl(10,100,"Timer 1");
        timer2 = new TimerImpl(10,100,"Timer 2");

        timer1.addTimerListener(new TimerListenerImpl());
        timer2.addTimerListener(new TimerListenerImpl());

        Thread t1 = new Thread(timer1);
        Thread t2 = new Thread(timer2);
        t1.start();
        t2.start();
    }
}
