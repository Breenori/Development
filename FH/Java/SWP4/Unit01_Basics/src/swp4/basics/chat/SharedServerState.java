package swp4.basics.chat;

import swp4.basics.chat.buffer.MessageBuffer;

import java.net.DatagramSocket;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class SharedServerState {
    private MessageBuffer receiverMessageBuffer;
    private DatagramSocket serverSocket;
    private List<Client> clients = Collections.synchronizedList(new ArrayList<>());

    public synchronized DatagramSocket getServerSocket() {
        return serverSocket;
    }

    public synchronized MessageBuffer getReceiverMessageBuffer() {
        return receiverMessageBuffer;
    }

    public synchronized void addClient(Client client) {
        this.clients.add(client);
    }
}
