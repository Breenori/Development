package ue02.part1.patterns.impl;

import ue02.part1.patterns.Subject;

public class Timer extends ObserverSubject {

    private int ticks = 0;
    private int interval = 0;
    private long currentId;

    public Timer(int ticks, int interval) {
        this.ticks = ticks;
        this.interval = interval;
    }

    public void runTimer() {
        if(ticks > 0 && interval > 0) {
            int tmpTicks = ticks;
            while(ticks > 0){
                try {
                    Thread.sleep(interval);
                } catch(InterruptedException e) {}
                ticks--;
                if(ticks == tmpTicks/2)
                {
                    notifyObserver(currentId++, "TimerHalf");
                }
                notifyObserver(currentId++, "TimerTick");
            }
            notifyObserver(currentId++, "TimerEnd");
            ticks = tmpTicks;
        }
    }

    @Override
    public void update(Subject source, Object argument, long noteId, String aspect) {
        super.update(source, argument, noteId, aspect);
        if(noteId != -1)
        {
            ticks = (int)argument;
            notifyObserver(noteId, aspect);
        }
    }

    @Override
    public Object getState() {
        return ticks;
    }

}
