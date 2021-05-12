package swp4.ue03.components.impl;

import swp4.ue03.components.ConcreteComponent;

import java.util.*;

public class ProcessorComponent extends ConcreteComponent {

    private static int cpuCount = 0;
    List<String> taskList = new ArrayList(Arrays.asList("FileZilla","OpenSSH","apache2","TensorFlow","suspiciousCryptoMiner.exe.gz"));

    // a processor has a main utilization as well as subtasks and their utilization
    public ProcessorComponent() {
        if (registerMetrics(Arrays.asList("cpu-utilization"))) {
            active = true;
            id = ++cpuCount;
        }
    }

    // Query all processes, so they are randomized and add up to the total utilization
    private void queryTasks() {
        int i = 0;
        int sum = 0;
        for(String task : taskList) {
            int value = metricRandomizer.nextInt(((int)metrics.get("cpu-utilization") - sum) / (taskList.size() - i++)) + 1;
            metrics.put("cpu-processes;"+task,value);
            sum += value;
        }
    }

    protected void queryMetrics() {
        if(isActive()) {
            int total = metricRandomizer.nextInt(51) + 50;
            metrics.put("cpu-utilization", total);
            queryTasks();
        }
    }
}
