package swp4.ue04.part2;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.*;
import java.util.concurrent.atomic.AtomicBoolean;

public class ChatClient {

    private String chatroom;
    private String nickname;
    private int receivePort;
    private String serverHost;
    private int serverPort;
    private boolean loggedIn = false;
    private AtomicBoolean running = new AtomicBoolean( true );
    private DatagramSocket socket;

    public void startAndInitClient( String[] args )   {
        try {
            // take argument from console
            chatroom = args[0];
            nickname = args[1];
            receivePort = Integer.valueOf(args[2]);
            serverHost = args[3];
            serverPort = Integer.valueOf(args[4]);
            socket = new DatagramSocket();

            // create a new thread for the blocking method "receive" of the socket
            Thread thread = new Thread(() -> {
                try (DatagramSocket receiver = new DatagramSocket(receivePort)) {
                    while (running.get()) {
                        byte[] buffer = new byte[2048];
                        DatagramPacket pkt = new DatagramPacket(buffer, buffer.length);
                        //System.out.print("Client waiting for incoming messages in group: " + chatroom +"  - ");
                        receiver.receive(pkt);

                        // depending on the message start, process the messages differently
                        String data = new String(buffer).trim();
                        switch(data.substring(0,1)) {
                            case "o":
                                loggedIn = true;
                                System.out.println("Connected to "+chatroom+" (Local: "+data.substring(1)+")");
                                break;
                            case "m":
                                System.out.println(data.substring(1));
                                break;
                            case "e":
                                System.err.println("Error: "+data.substring(1));
                                // error 1: connection limit, error 2: logged out because of missing alive
                                if(data.charAt(1)=='1' || data.charAt(1)=='2') {
                                    loggedIn = false;
                                }
                                break;
                            case "a":
                                //System.out.println("Are you still alive?");
                                byte[] m = ("o").getBytes();
                                socket.send(new DatagramPacket(m, m.length,  InetAddress.getByName(serverHost), serverPort));
                                break;
                        }

                    }
                } catch (IOException e) {
                    System.err.println( "Failed to receive Paket from server..." );
                }
            });
            // make the thread a daemon, so it is being terminated along with the main thread.
            thread.setDaemon(true);
            thread.start();

            // first of all, send a connect message to the server
            String ConnPacket = "c " + receivePort + " " + chatroom;
            InetAddress addr = InetAddress.getByName(serverHost);
            byte[] ConnMessage = ConnPacket.getBytes();
            DatagramPacket ConnPkt = new DatagramPacket(ConnMessage, ConnMessage.length, addr, serverPort);
            socket.send(ConnPkt);
            Thread.sleep(1000);

            // after connecting, continuously read from the console
            BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
            while(running.get()) {
                String userdata = reader.readLine().trim();
                if(loggedIn) {
                    byte[] m;
                    // if the sent message is the letter q, quit the client application
                    if (userdata.equals("q")) {
                        m = ("q").getBytes();
                        running.set(false);
                        System.out.println("You've been logged out.");
                    } else {
                        // if it isn't q, send a full message and the nickname
                        m = ("s <" + nickname + ">: " + userdata).getBytes();
                    }

                    if(userdata.length() > 0) {
                        DatagramPacket SendPkt = new DatagramPacket(m, m.length, addr, serverPort);
                        socket.send(SendPkt);
                    }
                } else { // if the user isn't logged in and tries to send a message, he gets an error message and the program terminates
                    System.err.println("You are not logged in. Please try reconnecting.");
                    running.set(false);
                }
            }


        } catch( SocketException e ) {
            running.set( false );
            System.err.println( "The client could not be started for server " + serverHost
                    +":"+serverPort + ". Is the server running?" );
            e.printStackTrace();

        } catch( UnknownHostException e ) {
            running.set( false );
            System.err.println( "The host " + serverHost + " could not be found!"  );
            e.printStackTrace();
        } catch( InterruptedException | IOException e ) {
            running.set( false );
            e.printStackTrace();
        }
    }



    public static void main(String[] args) throws  Exception {
        new ChatClient( ).startAndInitClient( args );
    }
}