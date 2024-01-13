package swp4.ue03.test;

import swp4.ue03.components.impl.*;
import swp4.ue03.profiling.impl.Profiler;
import swp4.ue03.protocol.impl.*;

public class DashboardTest {

    private static void test_example() {
        // Create all the components with customizable
        MemoryComponent ramComp = new MemoryComponent(32);
        NetworkComponent netComp = new NetworkComponent(150,40);
        ProcessorComponent cpuComp = new ProcessorComponent();
        PowerComponent psuComp = new PowerComponent(750);
        StorageComponent storeComp = new StorageComponent(250, 80);

    public static void main(String[] args) {
        // Create all the components with customizable
        MemoryComponent ramComp = new MemoryComponent(32);
        NetworkComponent netComp = new NetworkComponent(150,40);
        ProcessorComponent cpuComp = new ProcessorComponent();
        PowerComponent psuComp = new PowerComponent(750);
        StorageComponent storeComp = new StorageComponent(250, 80);

        // Create and configure the profilers
        Profiler p1 = new Profiler();
        p1.addProtocol(MemoryProtocol.getInstance());
        p1.addProtocol(NetworkProtocol.getInstance());
        p1.addProtocol(PowerProtocol.getInstance());

        Profiler p2 = new Profiler();
        p2.addThreshold("cpu-utilization",90);
        p2.addProtocol(ProcessorProtocol.getInstance());
        p2.addProtocol(StorageProtocol.getInstance());

        // Tell the profilers which components to monitor.
        ramComp.attach(p1);
        netComp.attach(p1);
        psuComp.attach(p1);

        storeComp.attach(p2);
        cpuComp.attach(p2);

        // "Start" all the components
        Thread ramThread = new Thread(ramComp);
        Thread netThread = new Thread(netComp);
        Thread psuThread = new Thread(psuComp);
        Thread cpuThread = new Thread(cpuComp);
        Thread storeThread = new Thread(storeComp);

        ramThread.start();
        netThread.start();
        psuThread.start();
        cpuThread.start();
        storeThread.start();


        // wait 10 seconds for generation of data
        try {
            Thread.sleep(10000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        // Print protocols to console and CSV
        p1.print(ProtocolPrinter.protocolType.NUMBER, 5);
        p2.print(ProtocolPrinter.protocolType.CSV, 15, "test.csv");

        // shut down all the components (and their threads)
        ramComp.turnOff();
        netComp.turnOff();
        psuComp.turnOff();
        cpuComp.turnOff();
        storeComp.turnOff();
    }
    private static void test_unstarted() {
        ProcessorComponent cpuComp = new ProcessorComponent();
        Profiler p = new Profiler();
        cpuComp.attach(p);

        ProtocolPrinter pp = new ProtocolPrinter();
        pp.addProtocol(ProcessorProtocol.getInstance());

        pp.print(ProtocolPrinter.protocolType.NUMBER, p.getData(), 10);
    }
    private static void test_no_subprotocols() {
        ProcessorComponent cpuComp = new ProcessorComponent();
        Profiler p = new Profiler();
        cpuComp.attach(p);
        Thread cpuT = new Thread(cpuComp);
        cpuT.start();

        try {
            Thread.sleep(3000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        // protocolprinter without specified protocols
        ProtocolPrinter pp = new ProtocolPrinter();

        pp.print(ProtocolPrinter.protocolType.NUMBER, p.getData(), 10);
        cpuComp.turnOff();
    }

    public static void main(String[] args) {
        test_example();
        //test_unstarted();
        //test_no_subprotocols();
    }
}
