package swp4.ue04.part2.buffer.impl;

import swp4.ue04.part2.buffer.MessageBuffer;
import swp4.ue04.part2.message.Message;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.concurrent.atomic.AtomicInteger;

public class MessageBufferImpl implements MessageBuffer {

    private final AtomicInteger maxSize;
    // due to multithreading we need a synchronizedList
    private List<Message> messageBuffer = Collections.synchronizedList(new ArrayList<>());

    public MessageBufferImpl(int maxSize) {
        this.maxSize = new AtomicInteger(maxSize);
    }

    @Override
    public synchronized void add(Message message) {
        // if the list is full, wait till something is removed
        while(messageBuffer.size() == maxSize.get()) {
            try {
                wait(200);
            } catch(InterruptedException e) {

            }
        }

        // afterwards, remove add the message
        messageBuffer.add(message);
        notifyAll();
    }

    @Override
    public synchronized Message get() {
        // if the messageBuffer is empty, wait till there is an element
        while(messageBuffer.size() < 1) {
            try {
                wait(200);
            } catch(InterruptedException e) {

            }
        }
        return messageBuffer.get(0);
    }

    @Override
    public synchronized void delete(Message message) {
        // remove a message from the List
        messageBuffer.remove(message);
        notifyAll();
    }

}
