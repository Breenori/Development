package swp4.basics.collections.impl;

import java.util.Arrays;

public class Heap {
    private int[] heap;
    private int level;

    public Heap(int capacity) {
        this.heap = new int[capacity];
        this.level = 0;
    }

    public void insert(int value)
    {
        this.level++;
        if (level < heap.length)
        {
            heap[level]=value;
            shiftUp(level);
        }
    }

    public int remove() {
        if(level >0){
            int value = heap[1];
            heap[1] = heap[level];
            level--;
            shiftDown(1);
            return value;
        } else {
            throw new IllegalStateException("Heap is empty!");
        }
    }


    public void writeHeap(){
        System.out.println("Heap:");
        for(int i=1; i <= level; i++)
        {
            System.out.print(" " + heap[i]);
        }
        System.out.println();
    }

    private void shiftUp(int pos){
        int element = heap[pos];
        heap[0] = Integer.MAX_VALUE;
        while(heap[parent(pos)] <= element) { // move up as lon as parent is smaller
            heap[pos] = heap[parent(pos)];
            pos = parent(pos);
        }
        heap[pos] = element;
    }

    private void shiftDown(int pos){
        int element = heap[pos];
        while(pos <= parent(level)) {
            int j = left(pos);
            if(j < level && heap[j] < heap[right(pos)]) {
                j = right(pos);
            }
            if(element >= heap[j]) {
                break;
            }
            heap[pos] = heap[j];
            pos = j;
        }
        heap[pos] = element; // final position of element.
    }

    private int parent(int pos) {
        return pos/2;
    }

    private int left(int pos) {
        return pos*2;
    }

    private int right(int pos) {
        return left(pos)+1;
    }
}
