package swp4.ue04.part2.receiver.impl;


import swp4.ue04.part2.SharedServerState;
import swp4.ue04.part2.message.Message;
import swp4.ue04.part2.receiver.MessageReceiver;

import java.io.IOException;
import java.net.DatagramPacket;
import java.util.concurrent.atomic.AtomicBoolean;

public class MessageReceiverImpl implements MessageReceiver {

    private SharedServerState sharedServerState;
    private AtomicBoolean stopRequest = new AtomicBoolean(false);

    public MessageReceiverImpl(SharedServerState sharedServerState) {
        this.sharedServerState = sharedServerState;
    }

    @Override
    public void run() {

        DatagramPacket pkt;
        // while there has not been a stopRequest, wait for messages from clients
        while(!stopRequest.get()) {
            try {
                byte[] buffer = new byte[2048];
                pkt = new DatagramPacket(buffer, buffer.length);
                sharedServerState.getServerSocket().receive(pkt);
                String message = new String(buffer, 0 , buffer.length);

                // if as message has been received, check if a command is present and add it to the buffer
                if(message.length()>0) {
                    char command = message.charAt(0);
                    if(message.length() > 1) {
                        sharedServerState.getReceiverMessageBuffer().add(
                                new Message(pkt.getAddress().getHostName(), pkt.getPort(), command, message.substring(1).trim())
                        );
                    }
                }
            } catch(IOException e) {
                System.err.println("Received an error processing the buffer. "+e.getMessage());
            }
        }
    }
}
