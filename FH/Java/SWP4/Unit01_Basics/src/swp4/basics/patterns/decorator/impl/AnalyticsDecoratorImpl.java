package swp4.basics.patterns.decorator.impl;

import swp4.basics.collections.List;
import swp4.basics.patterns.decorator.AnalyticsDecorator;

import java.util.Iterator;

public class AnalyticsDecoratorImpl implements AnalyticsDecorator {

    private List decoratedList;
    private int callsToPrepend = 0;
    private int callsToAppend = 0;
    private int callsToRemove = 0;
    private int callsToContains = 0;
    private int callsToFirst = 0;
    private int callsToLast = 0;
    private int callsToPrint = 0;
    private int callsToIterator = 0;

    public AnalyticsDecoratorImpl(List decoratedList) {
        this.decoratedList = decoratedList;
    }

    @Override
    public void prepend(Object o) {
        callsToPrepend++;
        decoratedList.prepend(o);
    }
    @Override
    public void append(Object o) {
        callsToAppend++;
        decoratedList.append(o);
    }
    @Override
    public Object first() {
        callsToFirst++;
        return decoratedList.first();
    }
    @Override
    public Object last() {
        callsToLast++;
        return decoratedList.last();
    }
    @Override
    public boolean remove(Object o) {
        callsToRemove++;
        return decoratedList.remove(o);
    }
    @Override
    public boolean contains(Object o) {
        callsToContains++;
        return decoratedList.contains(o);
    }
    @Override
    public Object getElementAt(int pos) {
        return decoratedList.getElementAt(pos);
    }
    @Override
    public int getSize() {
        return decoratedList.getSize();
    }
    @Override
    public Object getLastElement() {
        return decoratedList.getLastElement();
    }
    @Override
    public Object getFirstElement() {
        return decoratedList.getFirstElement();
    }
    @Override
    public void print() {
        callsToPrint++;
        decoratedList.print();
        printAnalytics();
    }
    @Override
    public Iterator<Object> iterator() {
        callsToIterator++;
        return decoratedList.iterator();
    }
    @Override
    public void printAnalytics() {
        System.out.println("---------------------------------");
        System.out.println("Calls to prepend: " + callsToPrepend);
        System.out.println("Calls to append: " + callsToAppend);
        System.out.println("Calls to first: " + callsToFirst);
        System.out.println("Calls to last: " + callsToLast);
        System.out.println("Calls to contains: " + callsToContains);
        System.out.println("Calls to remove: " + callsToRemove);
        System.out.println("Calls to print: " + callsToPrint);
        System.out.println("Calls to iterator: " + callsToIterator);
        System.out.println("---------------------------------");
    }
}
