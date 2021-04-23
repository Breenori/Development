package swp4.basics.chat.handler;

import swp4.basics.chat.SharedServerState;
import swp4.basics.chat.message.Message;

public abstract class AbstractMessageHandler implements MessageHandler {

    protected SharedServerState sharedServerState;

    public AbstractMessageHandler(SharedServerState sharedServerState) {
        this.sharedServerState = sharedServerState;
    }
}
