package swp4.basics.threading.concurrency.impl;

import swp4.basics.threading.concurrency.Incrementable;

import java.util.concurrent.atomic.AtomicInteger;

public class SyncedIncrementableImpl implements Incrementable {
    static AtomicInteger value = new AtomicInteger(0);
    static AtomicInteger callsToIncrement = new AtomicInteger(0);
    static AtomicInteger callsToDecrement = new AtomicInteger(0);

    @Override
    public synchronized void increment() {
        callsToIncrement.incrementAndGet();
        value.incrementAndGet();
    }

    @Override
    public synchronized void decrement() {
        callsToDecrement.incrementAndGet();
        value.decrementAndGet();
    }

    @Override
    public void print() {
        System.out.println("IncrementableImpl");
        System.out.println("-----------------------------------------");
        System.out.println("Actual value after execution: "+value);
        System.out.println("Calls to increment(): "+callsToIncrement);
        System.out.println("Calls to decrement(): "+callsToDecrement);
        System.out.println("-----------------------------------------");
    }
}
