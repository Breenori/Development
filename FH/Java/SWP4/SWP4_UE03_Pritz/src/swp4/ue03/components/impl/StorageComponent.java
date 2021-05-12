package swp4.ue03.components.impl;

import swp4.ue03.components.ConcreteComponent;

import java.util.*;

public class StorageComponent extends ConcreteComponent {
    private static int storeCount = 0;
    List<String> taskList = new ArrayList(Arrays.asList("FileZilla","OpenSSH","apache2","TensorFlow","suspiciousCryptoMiner.exe.gz"));

    int readspeed = 0;
    int writespeed = 0;

    // speeds in MB/s
    public StorageComponent(int readspeed, int writespeed) {
        if (registerMetrics(Arrays.asList("storage-access"))) {
            active = true;
            id = ++storeCount;
            this.readspeed = readspeed * 1024 * 1024;
            this.writespeed = writespeed * 1024 * 1024;
        }
    }

    private void queryTasks() {
        int i = 0;
        int sum = 0;
        for(String task : taskList) {
            metrics.put("storage-processes;"+task+";read", metricRandomizer.nextInt(readspeed+1));
            metrics.put("storage-processes;"+task+";write", metricRandomizer.nextInt(writespeed+1));
        }
    }

    protected void queryMetrics() {
        if(isActive()) {
            int total = metricRandomizer.nextInt(5000);
            metrics.put("storage-access", total);
            queryTasks();
        }
    }
}
