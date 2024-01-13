package swp4.ue04.part2.sender.impl;

import swp4.ue04.part2.SharedServerState;
import swp4.ue04.part2.message.Message;
import swp4.ue04.part2.sender.MessageSender;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.InetAddress;

public class MessageSenderImpl implements MessageSender {

    private SharedServerState sharedServerState;

    public MessageSenderImpl(SharedServerState sharedServerState) {
        this.sharedServerState = sharedServerState;
    }

    @Override
    public void run() {
        // implement Consumer logic
        Message message;

        // periodically check for new messages in the buffer
        while( ( message = sharedServerState.getSendMessageBuffer().get() ) != null ) {
            try {
                sharedServerState.getSendMessageBuffer().delete(message);
                byte[] messageRaw = (message.getCommand() + message.getData()).getBytes();
                DatagramPacket pkt = new DatagramPacket(
                        messageRaw,
                        messageRaw.length,
                        InetAddress.getByName(message.getHost()),
                        message.getPort()
                );

                // if message has been found, send the packets from the buffer
                sharedServerState.getServerSocket().send(pkt);
            } catch( IOException e ) {
                System.err.println( "Failed to send message: " + message );
            }
        }
    }

}
