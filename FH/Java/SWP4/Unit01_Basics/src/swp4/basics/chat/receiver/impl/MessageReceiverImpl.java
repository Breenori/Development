package swp4.basics.chat.receiver.impl;

import swp4.basics.chat.SharedServerState;
import swp4.basics.chat.message.Message;
import swp4.basics.chat.receiver.MessageReceiver;

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
        byte[] buffer = new byte[2048];
        DatagramPacket pkt = new DatagramPacket(buffer, buffer.length);
        while(!stopRequest.get()) {
            try {
                sharedServerState.getServerSocket().receive(pkt);
                String message = new String(buffer, 0 , buffer.length);
                if(message.length()>0) {
                    char command = message.charAt(0);
                    if(message.length() > 1) {
                        sharedServerState.getReceiverMessageBuffer().add(
                                new Message(pkt.getAddress().getHostName(), pkt.getPort(), command, message.substring(1))
                        );
                    }
                }
            } catch(IOException e) {
                System.err.println("Received an error processing the buffer. "+e.getMessage());
            }
        }
    }
}
