package swp4.basics.threading;

public interface Timer extends Runnable {

    boolean addTimerListener(TimerListener listener);

    boolean removeTimerLister(TimerListener listener);

    String getTimerName();

    void start();
}
