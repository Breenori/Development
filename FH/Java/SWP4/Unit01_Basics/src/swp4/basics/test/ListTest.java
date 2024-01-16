package swp4.basics.test;

import swp4.basics.collections.List;
import swp4.basics.collections.impl.SingleLinkedList;
import swp4.basics.patterns.decorator.impl.AnalyticsDecoratorImpl;

import java.util.Iterator;

public class ListTest {
    public static void main(String[] args) {
        List list = new AnalyticsDecoratorImpl(new SingleLinkedList());
        list.append("A");
        list.append("B");
        list.append("C");
        list.append("D");

        System.out.println("While-loop: ");
        Iterator<Object> iterator = list.iterator();
        while(iterator.hasNext()) {
            Object element = iterator.next();
            System.out.println(" "+element);
        }

        System.out.println();
        System.out.println("For-Loop: ");
        for(Iterator<Object> listIterator = list.iterator(); listIterator.hasNext();) {
            Object element = listIterator.next();
            System.out.println(element);
        }

        System.out.println();
        System.out.println("Enhanced For-Loop: ");
        for(Object element : list) {
            System.out.println(element);
        }
    }
}
