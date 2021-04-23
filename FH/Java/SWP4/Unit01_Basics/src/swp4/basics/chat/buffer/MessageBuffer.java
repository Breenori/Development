package swp4.basics.chat.buffer;

import swp4.basics.chat.message.Message;

public interface MessageBuffer {
    void add(Message message);
    Message get();
    void delete(Message message);
}
