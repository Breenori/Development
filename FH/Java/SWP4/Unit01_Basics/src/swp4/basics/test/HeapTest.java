package swp4.basics.test;

import swp4.basics.collections.Heap;

public class HeapTest {

    public static void main(String[] args) {
        Heap heap = new Heap(10);
        heap.insert(5);
        heap.insert(15);
        heap.insert(42);

        heap.writeHeap();
        heap.insert(9);
        heap.writeHeap();

        int max = heap.remove();
        System.out.println("Max element in Heap: " + max);
        heap.writeHeap();
    }
}
