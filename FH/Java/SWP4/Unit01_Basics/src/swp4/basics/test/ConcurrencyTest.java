package swp4.basics.test;

import swp4.basics.threading.concurrency.Incrementable;
import swp4.basics.threading.concurrency.impl.IncrementableImpl;
import swp4.basics.threading.concurrency.impl.SyncedIncrementableImpl;

public class ConcurrencyTest {
    public static void testIncrementableImpl() throws InterruptedException {
        Incrementable incrementable = new IncrementableImpl();

        // create a thread that call increment 1000 times
        Thread a = new Thread() {
            @Override
            public void run() {
                for(int i=0; i < 1000; i++) {
                    incrementable.increment();
                }
            }
        };

        Thread b = new Thread() {
            @Override
            public void run() {
                for(int i=0; i < 1000; i++) {
                    incrementable.decrement();
                }
            }
        };

        a.start();
        b.start();

        a.join();
        b.join();

        incrementable.print();

    }
    public static void testSyncedIncrementableImpl() throws InterruptedException {
        Incrementable incrementable = new SyncedIncrementableImpl();

        // create a thread that call increment 1000 times
        Thread a = new Thread() {
            @Override
            public void run() {
                for(int i=0; i < 1000; i++) {
                    incrementable.increment();
                }
            }
        };

        Thread b = new Thread() {
            @Override
            public void run() {
                for(int i=0; i < 1000; i++) {
                    incrementable.decrement();
                }
            }
        };

        a.start();
        b.start();

        a.join();
        b.join();

        incrementable.print();

    }

    public static void main(String[] args) {
        try {
            System.out.println("Unsynced: ");
            testIncrementableImpl();
            System.out.println("Synced: ");
            testSyncedIncrementableImpl();
        } catch(InterruptedException e) {}
    }

}
