package swp4.basics.test;

import swp4.basics.collections.List;
import swp4.basics.collections.impl.SingleLinkedList;
import swp4.basics.patterns.decorator.impl.AnalyticsDecoratorImpl;

public class AnalyticsTest {
    public static void main(String[] args) {
        List list = new AnalyticsDecoratorImpl(new SingleLinkedList());
        list.append("A");
        list.append("B");
        list.append("C");
        list.append("D");
        list.append("E");

        list.prepend("Z");
        list.prepend("Y");
        list.prepend("X");

        list.contains("A");
        list.contains("B");
        list.contains("C");

        list.remove("Z");
        list.remove("X");
        list.remove("Y");

        list.iterator();
        list.first();
        list.last();

        list.print();
    }
}
