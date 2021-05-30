package swp4.ue04.part2;

import swp4.ue04.part2.buffer.MessageBuffer;
import swp4.ue04.part2.message.Message;

import java.net.DatagramSocket;
import java.util.*;

public class SharedServerState {

    private final int maxClients = 10;

    private DatagramSocket serverSocket;
    private MessageBuffer receiverMessageBuffer;
    private MessageBuffer sendMessageBuffer;
    private List<Client> clients = Collections.synchronizedList(new ArrayList<>());
    private Map<String, List<Client>>  clientGroups = Collections.synchronizedMap(new HashMap<>());

    public SharedServerState(DatagramSocket serverSocket, MessageBuffer receiverMessageBuffer, MessageBuffer sendMessageBuffer) {
        // initialize the serverstate using parameters
        this.serverSocket = serverSocket;
        this.receiverMessageBuffer = receiverMessageBuffer;
        this.sendMessageBuffer = sendMessageBuffer;
    }

    public synchronized boolean serverFull() {
        return clients.size() == maxClients;
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
        // add clients only if the server has capacity
        if(!serverFull()) {
            this.clients.add(client);
            this.clientGroups.computeIfAbsent(client.getGroup(), tmp -> new ArrayList<>());
            this.clientGroups.get(client.getGroup()).add(client);
        }
    }

    public synchronized void removeClient(Client client) {
        // if disconnecting client is the last one in the group, remove the group
        if(getClientsInGroup(client.getGroup()).size() == 1) {
            clientGroups.remove(client.getGroup());
        }
        clients.remove(client);
    }

    public List<Client> getClients() {
        return clients;
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
