package swp4.basics.test;

import swp4.basics.threading.worker.impl.Master;
import swp4.basics.threading.worker.impl.TaskList;
import swp4.basics.threading.worker.impl.Worker;

public class WorkerTest {
    public static void main(String[] args) {
        TaskList taskList = new TaskList(5);
        Master master = new Master(taskList);

        Worker w1 = new Worker("Worker A", taskList);
        Worker w2 = new Worker("Worker B", taskList);

        Thread t1 = new Thread(w1);
        Thread t2 = new Thread(w2);


        new Thread(master).start();
        t1.start();
        t2.start();
    }
}
