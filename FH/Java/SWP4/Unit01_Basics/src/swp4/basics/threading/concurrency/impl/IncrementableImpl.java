package swp4.basics.threading.concurrency.impl;

import swp4.basics.threading.concurrency.Incrementable;

public class IncrementableImpl implements Incrementable {

    static int value = 0;
    static int callsToIncrement = 0;
    static int callsToDecrement = 0;

    @Override
    public void increment() {
        callsToIncrement++;
        value++;
    }

    @Override
    public void decrement() {
        callsToDecrement++;
        value--;
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
