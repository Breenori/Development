package swp4.ue03.components.impl;

import swp4.ue03.components.ConcreteComponent;
import java.util.Arrays;


public class MemoryComponent extends ConcreteComponent {

    private static int memoryCount = 0;
    private int capacity;

    public MemoryComponent(int capacity) {
        // A memory component has two metrics used and free (in megabytes)
        if (registerMetrics(Arrays.asList("used","free"))) {
            this.capacity = capacity * 1024;
            active = true;
            id = ++memoryCount;
        }
    }

    protected void queryMetrics() {
        if(isActive()) {
            metrics.put("used", metricRandomizer.nextInt(capacity + 1));
            metrics.put("free", capacity - (int) metrics.get("used"));
        }
    }

}
