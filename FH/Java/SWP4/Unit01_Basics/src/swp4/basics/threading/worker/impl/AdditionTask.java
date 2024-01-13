package swp4.basics.threading.worker.impl;

import swp4.basics.threading.worker.CalculationTask;

import java.util.concurrent.atomic.AtomicInteger;

public class AdditionTask implements CalculationTask {
    private final AtomicInteger op1 = new AtomicInteger(0);
    private final AtomicInteger op2 = new AtomicInteger(0);
    private final AtomicInteger value = new AtomicInteger(0);

    public AdditionTask(int op1, int op2) {
        this.op1.set(op1);
        this.op2.set(op2);
    }

    @Override
    public int execute() {
        return op1.get() + op2.get();
    }

    @Override
    public String describe() {
        return op1.get() + " + " + op2.get() + " = " + execute();
    }
}
