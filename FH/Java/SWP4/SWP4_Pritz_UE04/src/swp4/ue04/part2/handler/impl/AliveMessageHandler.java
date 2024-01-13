package swp4.ue04.part2.handler.impl;

import swp4.ue04.part2.Client;
import swp4.ue04.part2.SharedServerState;
import swp4.ue04.part2.handler.AbstractMessageHandler;
import swp4.ue04.part2.message.Message;

import java.util.Collections;
import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.atomic.AtomicBoolean;

public class AliveMessageHandler extends AbstractMessageHandler {

    private static final char COMMAND = 'o';

    // List to manage active clients and detect absent clients
    private Map<Client, Boolean> clientsAlive = Collections.synchronizedMap(new HashMap<>());
    private AtomicBoolean stopRequest = new AtomicBoolean(false);

    public AliveMessageHandler(SharedServerState sharedServerState) {
        super(sharedServerState);

        // create a new thread to monitor clients and remove inactive ones
        Thread aliveThread = new Thread( () -> {
            try {
                while(!stopRequest.get()) {
                    // first, copy a list of all clients to the map and set their activity to inactive (false)
                    // and also send each client a message to ask about their activity
                    for(Client curClient : sharedServerState.getClients())  {
                        sharedServerState.getSendMessageBuffer().add(
                                new Message(curClient.getHost(), curClient.getReceivingPort(), 'a', "")
                        );
                        clientsAlive.put(curClient, false);
                    }
                    // Then, wait 60 seconds and afterwards check how many clients responded
                    Thread.sleep(60000);

                    // if clients havent responded, their activity is still inactive (false)
                    // they will then be removed and notified with an error
                    for(Map.Entry<Client, Boolean> clientInfo : clientsAlive.entrySet()) {
                        if(!(clientInfo.getValue())) {
                            sharedServerState.removeClient(clientInfo.getKey());
                            sharedServerState.getSendMessageBuffer().add(
                                new Message(clientInfo.getKey().getHost(), clientInfo.getKey().getReceivingPort(), 'e', "2: You've been disconnected")
                            );
                            clientsAlive.remove(clientInfo.getKey());
                        }
                    }
                    // afterwards, wait another 60 seconds to have an interval of 120s
                    Thread.sleep(60000);
                }
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        });
        aliveThread.start();
    }

    @Override
    public boolean handle(Message message) {
        if(COMMAND == message.getCommand()) {
            // if the server receives a message with command "o" from the client,
            // get the right client corresponding to the message
            // then set its activity to active in the list (= true)
            clientsAlive.put(sharedServerState.getClientForMessage(message), true);
            return true;
        }
        return false;
    }
}
