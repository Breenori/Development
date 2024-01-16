package swp4.basics.test;

import swp4.basics.collections.Stack;
import swp4.basics.collections.impl.CapacityStack;
import swp4.basics.collections.impl.ArrayStack;
import swp4.basics.collections.impl.CompositeListStack;
import swp4.basics.collections.impl.InheritanceListStack;
import swp4.basics.patterns.factory.StackFactory;
import swp4.basics.patterns.factory.StackType;
import swp4.basics.patterns.factory.impl.StackFactoryImpl;

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

        StackFactory factory = new StackFactoryImpl();
        Stack inheritanceStack = factory.createStack(StackType.INHERITANCE_STACK);
        Stack compositeStack = factory.createStack(StackType.COMPOSITE_STACK);

        inheritanceStack.push("A");
        inheritanceStack.push("B");
        Object a = inheritanceStack.pop();
        Object b = compositeStack.pop();

        System.out.println("Popped from inheritanceStack: "+a);
        System.out.println("Popped from compositeStack: "+b);
        System.out.println("Type of inheritanceStack: "+inheritanceStack);
        System.out.println("Type of compositeStack: "+compositeStack);

        /* //old
        Stack s1 = new ArrayStack();
        s1.push("Andreas");
        s1.push("Michael");
        s1.push("Stephan");

        String a = (String)s1.pop();
        System.out.println(a);

        a = (String)s1.pop();
        System.out.println(a);

        a = (String)s1.pop();
        System.out.println(a);

        InheritanceListStack ihls = new InheritanceListStack();
        ihls.push("Andreas");
        ihls.push("Thorsten");

        a = (String) ihls.pop();
        System.out.println(a);
        a = (String) ihls.pop();
        System.out.println(a);

        CompositeListStack cls = new CompositeListStack();
        cls.push("Jochen");
        a = (String) cls.pop();
        System.out.println(a);
        */
    }

}
