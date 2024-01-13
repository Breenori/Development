package swp4.ue04.part2.handler;

import swp4.ue04.part2.message.Message;

public interface MessageHandler {
    public boolean handle(Message message);
}
