package swp4.basics.collections;

public class Stack {
    int stackArr[] = new int[10];
    int tos = -1;

    public void push(int item)
    {
        stackArr[++tos] = item;
    }

    public int pop()
    {
        if(tos < 0) {
            System.out.println("..:: Stack Underflow ::..");
            return -1;
        } else {
            return stackArr[tos--];
        }
    }
}
