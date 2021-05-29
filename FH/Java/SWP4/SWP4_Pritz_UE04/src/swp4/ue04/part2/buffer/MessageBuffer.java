package swp4.ue04.part2.buffer;


import swp4.ue04.part2.message.Message;

public interface MessageBuffer {
    void add(Message message);
    Message get();
    void delete(Message message);
}
