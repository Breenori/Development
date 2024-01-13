package swp4.basics.threading.worker.impl;

import swp4.basics.threading.worker.CalculationTask;

import java.sql.SQLOutput;
import java.util.Random;

public class Worker implements Runnable {
    private String name;
    private TaskList taskList;

    public Worker(String name, TaskList taskList) {
        this.name = name;
        this.taskList = taskList;
    }

    @Override
    public void run() {
        CalculationTask task;
        Random r = new Random();

        while((task = taskList.get())!=null) {
            try {
                taskList.delete(task);
                int result = task.execute();
                System.out.println("Worker "+name+" calculated result: "+ task.describe() + result);
                Thread.sleep(r.nextInt(2000));
            } catch(InterruptedException e) {}
            if(task == null) {
                System.err.println("Task was null.");
            }
        }
    }
}
