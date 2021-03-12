package swp4.basics.collections;

public class CapacityStack extends Stack {
    
    public int[] stackArr;
    private int capacity = 0;

    public CapacityStack(int capacity) {
        this.capacity = capacity;
        this.stackArr = new int[capacity];
    }

    @Override
    public void push(int item) {
        if(tos == (capacity -1)) {
            System.out.println("..:: Stack Overflow ::..");
        }
        else {
            super.push(item);
        }
    }
}
