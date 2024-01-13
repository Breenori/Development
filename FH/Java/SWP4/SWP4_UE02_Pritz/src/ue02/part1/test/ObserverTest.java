package ue02.part1.test;


import ue02.part1.patterns.impl.Timer;

public class ObserverTest {

    public static void test_reference() {
        Timer s1 = new Timer(2,1000);
        Timer s2o1 = new Timer(10,2000);
        Timer s3o2 = new Timer(10,1500);
        Timer o3 = new Timer(10,1000);

        s1.attachObserver(s2o1);
        s1.attachObserver(s3o2);
        s2o1.attachObserver(o3);
        s3o2.attachObserver(o3);
        o3.attachObserver(s1);
        s1.runTimer();
    }

    public static void test_suppress() {
        Timer s1 = new Timer(3,1000);
        Timer obs1 = new Timer(10, 1000);
        Timer obs2 = new Timer(10, 1000);

        s1.attachObserver(obs1);
        s1.attachObserver(obs2);
        obs2.setInactive();
        s1.runTimer();
        obs2.setActive();
    }

    public static void test_aspects() {
        Timer s1 = new Timer(2,1000);
        Timer obs1 = new Timer(10, 1000);
        Timer obs2 = new Timer(10, 1000);

        s1.attachObserver(obs1);
        s1.attachObserver(obs2);
        obs2.subscribeAspect("TimerEnd");
        obs2.setInactive();
        s1.runTimer();
        obs2.setActive();
    }

    public static void test_block() {
        Timer s1 = new Timer(5,1000);
        Timer obs1 = new Timer(10, 1000);

        s1.block(obs1);
        s1.attachObserver(obs1);
    }

    public static void main(String[] args) {
        //test_reference();
        //test_suppress();
        //test_aspects();
        test_block();
    }
}
