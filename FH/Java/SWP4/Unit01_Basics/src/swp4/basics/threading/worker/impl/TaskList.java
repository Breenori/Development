package swp4.basics.threading.worker.impl;

import java.util.List;
import swp4.basics.threading.worker.CalculationTask;

import java.util.ArrayList;
import java.util.Collections;
import java.util.concurrent.atomic.AtomicInteger;

public class TaskList {
    private final AtomicInteger maxSize;
    private final List<CalculationTask> taskList = Collections.synchronizedList(new ArrayList<>());
    private final AtomicInteger retries = new AtomicInteger(0);

    private static final AtomicInteger MAX_RETRIES = new AtomicInteger(10);

    public TaskList(int maxSize) {
        this.maxSize = new AtomicInteger(maxSize);
    }

    // called by Master
    public synchronized void put(CalculationTask task) {
        while(taskList.size() == maxSize.get()) {
            try {
                wait();
            } catch (InterruptedException e) {
            }
        }

        taskList.add(0,task);
        notifyAll();
    }

    // called by Worker
    public synchronized CalculationTask get() {
        try {
            while(taskList.size() < 1 && retries.get() < MAX_RETRIES.get()) {
                wait(2000); // causes invoking thread to
                retries.incrementAndGet();
            }
        } catch (InterruptedException e) {

        }
        if(taskList.size() == 0 || retries.get() == MAX_RETRIES.get()) {
            return null;
        } else {
            return taskList.get(taskList.size()-1);
        }
    }

    // called by Worker
    public synchronized void delete(CalculationTask task) {
        taskList.remove(task);
    }
}
