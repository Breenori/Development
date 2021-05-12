package swp4.ue03.pattern.composite;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class Metric<T> {
    T metricItem;

    public Metric(T metricItem) {
        this.metricItem = metricItem;
    }

    public void queryMetric(T metricItem) {
        this.metricItem = metricItem;
    }

    @Override
    public String toString() {
        return "Metric{" +
                "item = "+metricItem+
                '}';
    }
}
