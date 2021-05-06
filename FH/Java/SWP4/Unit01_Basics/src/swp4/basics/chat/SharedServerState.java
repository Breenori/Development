package swp4.basics.chat;

import swp4.basics.chat.buffer.MessageBuffer;
import swp4.basics.chat.message.Message;

import java.net.DatagramSocket;
import java.sql.Array;
import java.util.*;

public class SharedServerState {

    private DatagramSocket serverSocket;
    private MessageBuffer receiverMessageBuffer;
    private MessageBuffer sendMessageBuffer;
    private List<Client> clients = Collections.synchronizedList(new ArrayList<>());
    private Map<String, List<Client>>  clientGroups = Collections.synchronizedMap(new HashMap<>());

    public SharedServerState(DatagramSocket serverSocket, MessageBuffer receiverMessageBuffer, MessageBuffer sendMessageBuffer) {
        this.serverSocket = serverSocket;
        this.receiverMessageBuffer = receiverMessageBuffer;
        this.sendMessageBuffer = sendMessageBuffer;
    }

    public synchronized DatagramSocket getServerSocket() {
        return serverSocket;
    }

    public synchronized MessageBuffer getReceiverMessageBuffer() {
        return receiverMessageBuffer;
    }

    public synchronized MessageBuffer getSendMessageBuffer() {
        return sendMessageBuffer;
    }

    public synchronized void addClient(Client client) {
        this.clients.add(client);
        /* old fashioned way
        if(!this.clientGroups.containsKey(client.getGroup())){
            this.clientGroups.put(client.getGroup(), new ArrayList<>());
        }
         */
        this.clientGroups.computeIfAbsent(client.getGroup(), tmp -> new ArrayList<>());
        this.clientGroups.get(client.getGroup()).add(client);
    }

    public synchronized List<Client> getClientsInGroup(String group) {
        return this.clientGroups.get(group);
    }

    public synchronized Client getClientForMessage(Message message) {
        for(Client client : clients) {
            if(client.getPort() == message.getPort() && client.getHost().equals(message.getHost())) {
                return client;
            }
        }

        return null;
    }
}
