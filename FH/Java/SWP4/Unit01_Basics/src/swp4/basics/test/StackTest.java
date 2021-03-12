package swp4.basics.test;

import swp4.basics.collections.CapacityStack;
import swp4.basics.collections.Stack;

public class StackTest {
    static int stack[] = new int[10];
    static int tos = -1;

    public static int pop() {
        if(tos < 0)
        {
            System.out.println("..:: Stack Underflow ::..");
            return -1;
        } else {
            return stack[tos--];
        }
    }

    public static void push(int item) {
        stack[++tos] = item;
    }

    public static void main(String[] args) {
        push(5);
        push(10);
        push(4);

        System.out.println("Version 1: static stack");

        int a = pop();
        System.out.println("Popped value: "+a);
        a = pop();
        System.out.println("Popped value: "+a);
        a = pop();
        System.out.println("Popped value: "+a);

        System.out.println("Version 2: stack class");

        Stack s1 = new Stack();
        s1.push(5);
        s1.push(10);
        s1.push(42);

        a = s1.pop();
        System.out.println("Popped value: "+a);
        a = s1.pop();
        System.out.println("Popped value: "+a);
        a = s1.pop();
        System.out.println("Popped value: "+a);

        System.out.println("Version 3: Capacity stack");

        Stack s2 = new CapacityStack(10);
        s2.push(5);
        s2.push(10);
        s2.push(42);

        a = s2.pop();
        System.out.println("Popped value: "+a);
        a = s2.pop();
        System.out.println("Popped value: "+a);
        a = s2.pop();
        System.out.println("Popped value: "+a);

        for(int i=0; i < 11; i++)
        {
            s2.push(i);
        }

    }

}
