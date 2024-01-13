package swp4.basics.patterns.factory.impl;

import swp4.basics.collections.Stack;
import swp4.basics.collections.impl.CompositeListStack;
import swp4.basics.collections.impl.InheritanceListStack;
import swp4.basics.patterns.factory.StackFactory;
import swp4.basics.patterns.factory.StackType;

public class StackFactoryImpl implements StackFactory {

    @Override
    public Stack createStack(StackType type) {
        if(StackType.COMPOSITE_STACK.equals(type)) {
            return new CompositeListStack();
        } else { //if (StackType.INHERITANCE_STACK.equals(type)) {
            return new InheritanceListStack();
        }
    }

}
