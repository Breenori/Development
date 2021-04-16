package swp4.basics.threading.impl;

import swp4.basics.threading.Timer;

public class TimerEvent {

    private Timer source;
    private int currentTick;
    private String timerName;

    public TimerEvent(Timer source, int currentTick, String timerName) {
        this.source = source;
        this.currentTick = currentTick;
        this.timerName = timerName;
    }

    public Timer getSource() {
        return source;
    }

    public int getCurrentTick() {
        return currentTick;
    }

    public String getTimerName() {
        return timerName;
    }

    @Override
    public String toString() {
        return "TimerEvent{" +
                "source=" + source +
                ", currentTick=" + currentTick +
                ", timerName='" + timerName + '\'' +
                '}';
    }
}
