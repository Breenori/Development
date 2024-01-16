package swp4.ue04.part2;


import swp4.ue04.part2.buffer.MessageBuffer;
import swp4.ue04.part2.buffer.impl.MessageBufferImpl;
import swp4.ue04.part2.handler.impl.AliveMessageHandler;
import swp4.ue04.part2.handler.impl.ConnectMessageHandler;
import swp4.ue04.part2.handler.impl.QuitMessageHandler;
import swp4.ue04.part2.handler.impl.SendMessageHandler;
import swp4.ue04.part2.process.MessageProcessor;
import swp4.ue04.part2.process.impl.MessageProcessorImpl;
import swp4.ue04.part2.receiver.MessageReceiver;
import swp4.ue04.part2.receiver.impl.MessageReceiverImpl;
import swp4.ue04.part2.sender.MessageSender;
import swp4.ue04.part2.sender.impl.MessageSenderImpl;

import java.net.DatagramSocket;
import java.net.SocketException;

public class ChatServer {

    private void initAndStartServer( int serverPort ) {
        try {
            // create a serversocket to receive and send messages from
            DatagramSocket serverSocket = new DatagramSocket( serverPort );

            // then create messagebuffers to intermediately store the messages before processing or sending them
            MessageBuffer receiveBuffer = new MessageBufferImpl( 100 );
            MessageBuffer sendBuffer = new MessageBufferImpl( 100 );

            // create a sharedserverstate to manage clients and buffers centrally
            SharedServerState sharedServerState = new SharedServerState( serverSocket, receiveBuffer, sendBuffer );

            // create instances to receive, send and process messages
            MessageReceiver receiver = new MessageReceiverImpl( sharedServerState );
            MessageSender sender = new MessageSenderImpl( sharedServerState );
            MessageProcessor processor = new MessageProcessorImpl( sharedServerState );

            // add all the different message handlers for different message types
            processor.addHandler( new ConnectMessageHandler(  sharedServerState ) );
            processor.addHandler( new SendMessageHandler( sharedServerState ) );
            processor.addHandler( new QuitMessageHandler( sharedServerState ) );
            processor.addHandler( new AliveMessageHandler( sharedServerState ) );

            // create and start threads for receiving, sending and processing packets
            Thread receiverThread = new Thread( receiver );
            Thread senderThread = new Thread( sender );
            Thread processorThread = new Thread( processor );
            processorThread.start();
            senderThread.start();
            receiverThread.start();

            // before ending, wait for all threads to end.
            receiverThread.join();
        } catch( InterruptedException | SocketException e ) {
            System.err.println( "Unable to start ChatServer, verify if port is already in use: " + serverPort );
        }
    }



    public static void main(String[] args) {
        new ChatServer().initAndStartServer( 9999 );
    }

}
