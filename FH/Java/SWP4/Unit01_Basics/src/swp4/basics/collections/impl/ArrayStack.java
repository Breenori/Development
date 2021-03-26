package swp4.basics.collections.impl;

import swp4.basics.collections.Stack;

public class ArrayStack implements Stack {
    Object stackArr[] = new Object[10];
    int tos = -1;

    public void push(Object item)
    {
        stackArr[++tos] = item;
    }

    public Object pop()
    {
        if(tos < 0) {
            System.out.println("..:: Stack Underflow ::..");
            return -1;
        } else {
            return stackArr[tos--];
        }
    }
}
