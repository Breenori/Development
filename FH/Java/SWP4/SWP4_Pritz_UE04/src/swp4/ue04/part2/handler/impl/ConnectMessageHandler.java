package swp4.ue04.part2.handler.impl;


import swp4.ue04.part2.Client;
import swp4.ue04.part2.SharedServerState;
import swp4.ue04.part2.handler.AbstractMessageHandler;
import swp4.ue04.part2.message.Message;

public class ConnectMessageHandler extends AbstractMessageHandler {

    private static final char COMMAND = 'c';

    public ConnectMessageHandler(SharedServerState sharedServerState) {
        super(sharedServerState);
    }

    @Override
    public boolean handle(Message message) {
        if(COMMAND == message.getCommand()) {
            // message.getData() 1234 group_1
            String[] data = message.getData().split(" ");
            // connect message consists of port and group. both are needed, else we have an error.
            if(data.length == 2) {

                Client client = new Client(message.getHost(), message.getPort(), Integer.parseInt(data[0]), data[1]);

                // add the client to the server (login) only if the server still has capacity.
                if(!sharedServerState.serverFull()) {
                    sharedServerState.addClient(client);

                    // send an "o" message back to the client if they have been accepted
                    sharedServerState.getSendMessageBuffer().add(
                            new Message(client.getHost(), client.getReceivingPort(), 'o', client.getHost() + ":" + client.getPort())
                    );
                } else {
                    // if too many people are on the server, send an error message
                    sharedServerState.getSendMessageBuffer().add(
                            new Message(client.getHost(), client.getReceivingPort(), 'e', "1: Server capacity reached.")
                    );
                }
                return true;
            } else {
                System.err.println("Invalid Connect message from client: " + message);
            }
        }

        return false;
    }
}
