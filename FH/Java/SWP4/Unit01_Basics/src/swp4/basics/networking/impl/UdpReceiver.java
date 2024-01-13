package swp4.basics.networking.impl;

import swp4.basics.networking.Receiver;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;

public class UdpReceiver implements Receiver {

    @Override
    public void startListening(Integer port) {
        try(DatagramSocket socket = new DatagramSocket(port)) {
            byte[] buffer = new byte[2048];
            DatagramPacket pkt = new DatagramPacket(buffer, buffer.length);
            System.out.println("UdpReceiver is listening on port "+port);
            while(true) {
                socket.receive(pkt);
                String message = new String(pkt.getData(), 0, pkt.getData().length);
                System.out.println("---------------------------");
                System.out.println("Receiving message from "+pkt.getAddress());
                System.out.println(message);
                System.out.println("---------------------------");
            }
        } catch(IOException | NumberFormatException e) {
            e.printStackTrace();
        }
    }
}
