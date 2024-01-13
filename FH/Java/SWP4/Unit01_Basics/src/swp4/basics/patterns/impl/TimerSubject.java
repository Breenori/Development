package swp4.basics.patterns.impl;

public class TimerSubject extends AbstractSubject {

    private int ticks = 0;
    private int interval = 0;

    public TimerSubject(int ticks, int interval) {
        this.ticks = ticks;
        this.interval = interval;
    }

    public void runTimer() {
        if(ticks > 0 && interval > 0) {
            while(ticks > 0){
                try {
                    Thread.sleep(interval);
                } catch(InterruptedException e) {}
                ticks--;
                notifyObserver();
            }
        }
    }

    @Override
    public Object getState() {
        return ticks;
    }

    public void attach(ConcreteObserver observer) {
        ChangeManager.getInstance().attachObserver(this,observer);
    }
}
