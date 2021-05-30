package swp4.ue04.part2.handler.impl;

import swp4.ue04.part2.SharedServerState;
import swp4.ue04.part2.handler.AbstractMessageHandler;
import swp4.ue04.part2.message.Message;

public class QuitMessageHandler extends AbstractMessageHandler {

    private static final char COMMAND = 'q';

    public QuitMessageHandler(SharedServerState sharedServerState) {
        super(sharedServerState);
    }


    @Override
    public boolean handle(Message message) {
        if(COMMAND == message.getCommand()) {
            // quit message has no data, just remove the client
            sharedServerState.removeClient(
                    sharedServerState.getClientForMessage(message)
            );
        }
        return false;
    }
}
