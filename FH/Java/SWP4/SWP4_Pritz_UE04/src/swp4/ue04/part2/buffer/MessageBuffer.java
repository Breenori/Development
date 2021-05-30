package swp4.ue04.part2.buffer;


import swp4.ue04.part2.message.Message;

public interface MessageBuffer {
    // adds a message to the buffer
    void add(Message message);
    // retrieves a message from the buffer
    Message get();
    // deletes a message from the buffer
    void delete(Message message);
}
