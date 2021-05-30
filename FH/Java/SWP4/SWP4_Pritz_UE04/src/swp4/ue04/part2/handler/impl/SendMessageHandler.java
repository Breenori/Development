package swp4.ue04.part2.handler.impl;

import swp4.ue04.part2.Client;
import swp4.ue04.part2.SharedServerState;
import swp4.ue04.part2.handler.AbstractMessageHandler;
import swp4.ue04.part2.message.Message;

public class SendMessageHandler extends AbstractMessageHandler {

    private static final char COMMAND = 's';

    public SendMessageHandler(SharedServerState sharedServerState) {
        super(sharedServerState);
    }


    @Override
    public boolean handle(Message message) {
        if(COMMAND == message.getCommand()) {
            String data = message.getData().trim();
            // every message needs to contain a colon
            if(data.contains(":")) {
                Client sender = sharedServerState.getClientForMessage(message);

                // if client is logged in
                if(sender != null) {
                    // distribute the message to all clients in the same group as the sender
                    for (Client receiver : sharedServerState.getClientsInGroup(sender.getGroup())) {
                        if (sender != receiver) {
                            sharedServerState.getSendMessageBuffer().add(
                                    new Message(receiver.getHost(), receiver.getReceivingPort(), 'm', data)
                            );
                        }
                    }
                } else {
                    // if the user isnt logged in, send an error message
                    sharedServerState.getSendMessageBuffer().add(
                            new Message(message.getHost(), message.getPort(), 'e', "2: You are not logged in.")
                    );
                }


                return true;
            } else {
                System.err.println("Invalid Send message from client: " + message);
            }
        }

        return false;
    }
}
