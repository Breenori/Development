package swp4.basics.collections.impl;

public class CapacityStack extends ArrayStack {

    private int capacity = 0;

    public CapacityStack(int capacity) {
        this.capacity = capacity;
        this.stackArr = new Object[capacity];
    }

    @Override
    public void push(Object item) {
        if(tos == (capacity -1)) {
            System.out.println("..:: Stack Overflow ::..");
        }
        else {
            super.push(item);
        }
    }
}
