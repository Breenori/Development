package swp4.basics.patterns.factory;


import swp4.basics.collections.Stack;

public interface StackFactory {
    // Factory-Method
    public Stack createStack(StackType type);
}
