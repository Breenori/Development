package swp4.basics.collections.impl;

import swp4.basics.collections.Stack;

public class CompositeListStack implements Stack {

    private SingleLinkedList stackElementList = new SingleLinkedList();

    @Override
    public void push(Object value) {
        stackElementList.prepend(value);
    }

    @Override
    public Object pop() {
        Object o = stackElementList.first();
        stackElementList.remove(o);
        return o;
    }
}
