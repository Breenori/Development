package swp4.basics.threading.worker.impl;

import java.util.Random;

public class Master implements Runnable{

    private TaskList taskList;

    public Master(TaskList taskList) {
        this.taskList = taskList;
    }

    @Override
    public void run() {
        // Master continuously produces new problems
        Random random = new Random();
        try {
            for(int i=0; i < 10; i++) {
                taskList.put(new AdditionTask(random.nextInt(100), random.nextInt(100)));
                Thread.sleep(500);
                taskList.put(new SubtractionTask(random.nextInt(100), random.nextInt(100)));
            }
        }catch(InterruptedException e) {}
    }
}
