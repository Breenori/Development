package swp4.ue03.test;

import swp4.ue03.pattern.composite.Metric;

import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class DashboardTest {


    public static void main(String[] args) {
        Metric<Integer> cpuMetric = new Metric<>(5);

        Map<String, Integer> processes = new HashMap<>();
        processes.put("minecraft.exe",95);
        processes.put("java.runtime",3);
        Metric<Map<String,Integer>> processMetric = new Metric<>(processes);

        System.out.println(cpuMetric);
        System.out.println(processMetric);
    }
}
