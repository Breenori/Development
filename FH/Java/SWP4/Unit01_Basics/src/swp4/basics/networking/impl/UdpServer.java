package swp4.basics.networking.impl;

import swp4.basics.networking.Receiver;
import swp4.basics.networking.impl.UdpReceiver;

public class UdpServer {
    public static void main(String[] args) {
        Receiver udpr = new UdpReceiver();
        udpr.startListening(9000);
    }
}
