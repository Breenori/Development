package swp4.basics.chat;

public class Client {
    private String host;
    private int port;
    private int wantedPort;
    private String group;

    public Client(String host, int port, int wantedPort, String group) {
        this.host = host;
        this.port = port;
        this.wantedPort = wantedPort;
        this.group = group;
    }
}
