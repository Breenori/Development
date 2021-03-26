package swp4.basics.collections.impl;

import swp4.basics.collections.Stack;

public class InheritanceListStack extends List implements Stack {
    @Override
    public void push(Object value) {
        this.prepend(value);
    }

    @Override
    public Object pop() {
        Object o = first();
        remove(o);
        return o;
    }
}
