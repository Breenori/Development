package swp4.basics.networking.impl;

import swp4.basics.networking.Sender;

import java.io.IOException;
import java.net.*;

public class UdpSender implements Sender {
    @Override
    public void send(String host, Integer port, String message) {
        try(DatagramSocket socket = new DatagramSocket()) {
            byte[] buffer = message.getBytes();
            System.out.println("UdpSender is sending message: "+ message);
            InetAddress addr = InetAddress.getByName(host);
            DatagramPacket pkt = new DatagramPacket(buffer, buffer.length, addr, port);
            socket.send(pkt);
        } catch(IOException e) {
            e.printStackTrace();
        }
    }
}
