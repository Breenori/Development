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
            if(data.length == 2) {
                Client client = new Client(message.getHost(), message.getPort(), Integer.parseInt(data[0]), data[1]);
                sharedServerState.addClient(client);

                sharedServerState.getSendMessageBuffer().add(
                        new Message(client.getHost(), client.getReceivingPort(), 'o', client.getHost()+":"+client.getPort())
                );

                return true;
            } else {
                System.err.println("Invalid Connect message from client: " + message);
            }
        }

        return false;
    }
}
