package swp4.ue03.components.impl;

import swp4.ue03.components.Component;
import swp4.ue03.components.ConcreteComponent;

import java.util.ArrayList;
import java.util.Arrays;

public class NetworkComponent extends ConcreteComponent {

    private static int networkCount = 0;
    int uplink = 0;
    int downlink = 0;

    // network component has downlink and uplink in mbits
    public NetworkComponent(int downlink, int uplink) {
        if (registerMetrics(Arrays.asList("received","sent"))) {
            active = true;
            id = ++networkCount;
            this.downlink = (int)(downlink / 8.0 * 1024 * 1024);
            this.uplink = (int)(uplink / 8.0 * 1024 * 1024);
        }
    }
    protected void queryMetrics() {
        if(isActive()) {
            metrics.put("received", metricRandomizer.nextInt(downlink + 1));
            metrics.put("sent", metricRandomizer.nextInt(uplink+1));
        }
    }
}
