package swp4.basics.threading;

import swp4.basics.threading.impl.TimerEvent;

public interface TimerListener {

    public void update(TimerEvent event);
}
