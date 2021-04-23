package swp4.basics.networking.impl;

import swp4.basics.networking.Sender;

public class UdpClient {
    public static void main(String[] args) {
        Sender sender = new UdpSender();
        sender.send("localhost",9000,"These are not the droids you are looking for...");
    }
}
