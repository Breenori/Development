package swp4.basics.chat.handler;

import swp4.basics.chat.message.Message;

public interface MessageHandler {
    public boolean handle(Message message);
}
