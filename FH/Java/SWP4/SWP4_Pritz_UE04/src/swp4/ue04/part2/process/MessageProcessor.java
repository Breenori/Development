package swp4.ue04.part2.process;

import swp4.ue04.part2.handler.MessageHandler;

public interface MessageProcessor extends Runnable{

    void addHandler(MessageHandler handler);
    void removeHandler(MessageHandler handler);
}
