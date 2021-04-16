package swp4.basics.threading.impl;

import swp4.basics.threading.Timer;
import swp4.basics.threading.TimerListener;

import java.util.ArrayList;
import java.util.List;

public class TimerImpl implements Timer {

    private int ticks=0;
    private int interval = 0;
    private String timerName;
    private List<TimerListener> listeners = new ArrayList<>();

    public TimerImpl(int ticks, int interval, String timerName) {
        this.ticks = ticks;
        this.interval = interval;
        this.timerName = timerName;
    }

    @Override
    public boolean addTimerListener(TimerListener listener) {
        return listeners.add(listener);
    }

    @Override
    public boolean removeTimerLister(TimerListener listener) {
        return listeners.remove(listener);
    }

    @Override
    public String getTimerName() {
        return timerName;
    }

    @Override
    public void start() {
        if(ticks > 0 && interval > 0) {
            while(ticks > 0) {
                try {
                    Thread.sleep(interval);
                } catch(InterruptedException e) {}
                notifyListeners();
                ticks--;
            }
        }
    }

    private void notifyListeners() {
        for(TimerListener timerListener : listeners) {
            timerListener.update(new TimerEvent(this, ticks, timerName));
        }
    }

    @Override
    public void run() {
        start();
    }
}
