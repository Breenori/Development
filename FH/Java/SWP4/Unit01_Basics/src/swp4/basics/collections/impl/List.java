package swp4.basics.collections.impl;

public class List {

    private Node head;
    private Node tail;
    private int size;

    public void prepend( Object o ) {
        head = new Node( o, head );
        if( tail == null ) {
            tail = head;
        }
        size++;
    }

    public void append( Object o ) {
        Node n = new Node( o, null );
        if( head == null ) {  // list is empty
            head = tail = n;
        } else {
            tail.next = n;
            tail = n;
        }
        size++;
    }

    public Object first() {
        return head != null ? head.val : null;
    }

    public Object last() {
        return tail != null ? tail.val : null;
    }

    public boolean remove( Object o ) {
        Node n = head;
        Node pred = null;
        if (n != null && n.val.equals( o )) {
            head = n.next;
            if( head == null ) {
                tail = head;
            }
            return true;
        }
        while (n != null && !n.val.equals( o ) ) {
            pred = n;
            n = n.next;
        }
        if (n == null) {
            return false;
        }
        pred.next = n.next;
        if( n == tail ){
            tail = pred;
        }
        return true;
    }

    public boolean contains( Object o ) {
        Node n = head;
        while( n != null ) {
            if( n.val.equals( o ) ) {
                return true;
            }
            n = n.next;
        }
        return false;
    }

    public Object getElementAt( int pos ) {
        int i = 0;
        Node n = head;
        while( n != null ) {
            if( i == pos ) {
                return n.val;
            }
            i++;
            n = n.next;
        }
        return null;
    }

    public int getSize() {
        return size;
    }

    public Object getLastElement() {
        return tail != null ? tail.val : null;
    }

    public Object getFirstElement() {
        return head != null ? head.val : null;
    }


    // inner class
    private class Node {
        public Object val;
        public Node next;

        public Node(Object val, Node next) {
            this.val = val;
            this.next = next;
        }
    }



}
