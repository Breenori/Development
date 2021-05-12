package swp4.ue03.components.impl;

import swp4.ue03.components.ConcreteComponent;

import java.util.ArrayList;
import java.util.Arrays;

public class PowerComponent extends ConcreteComponent {
    private static int powerCount = 0;
    private int wattage = 0;

    // power component has wattage in watts
    public PowerComponent(int wattage) {
        if (registerMetrics(Arrays.asList("powerconsumption"))) {
            active = true;
            id = ++powerCount;
            this.wattage = wattage;
        }
    }

    protected void queryMetrics() {
        if(isActive()) {
            metrics.put("powerconsumption", metricRandomizer.nextInt(wattage+1));
        }
    }
}
