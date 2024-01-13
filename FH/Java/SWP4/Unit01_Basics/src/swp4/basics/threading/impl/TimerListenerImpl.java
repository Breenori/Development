package swp4.basics.threading.impl;

import swp4.basics.threading.TimerListener;

public class TimerListenerImpl implements TimerListener {
    @Override
    public void update(TimerEvent event) {
        System.out.println("TimerListener notified by: " + event);
    }


}
