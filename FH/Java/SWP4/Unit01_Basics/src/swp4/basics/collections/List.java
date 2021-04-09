package swp4.basics.collections;

import java.util.Iterator;

public interface List extends Iterable {
    void prepend(Object o);

    void append(Object o);

    Object first();

    Object last();

    boolean remove(Object o);

    boolean contains(Object o);

    Object getElementAt(int pos);

    int getSize();

    Object getLastElement();

    Object getFirstElement();

    void print();

    @Override
    Iterator<Object> iterator();
}
