package swp4.basics.chat.process;

import swp4.basics.chat.handler.MessageHandler;

public interface MessageProcessor extends Runnable{

    void addHandler(MessageHandler handler);
    void removeHandler(MessageHandler handler);
}
