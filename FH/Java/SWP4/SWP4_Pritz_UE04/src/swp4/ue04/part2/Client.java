package swp4.ue04.part2;

public class Client {
    private String host;
    private int port;
    private int receivingPort;
    private String group;

    public Client(String host, int port, int receivingPort, String group) {
        this.host = host;
        this.port = port;
        this.receivingPort = receivingPort;
        this.group = group;
    }

    public String getHost() {
        return host;
    }

    public int getPort() {
        return port;
    }

    public int getReceivingPort() {
        return receivingPort;
    }

    public String getGroup() {
        return group;
    }

    @Override
    public String toString() {
        return "Client{" +
                "host='" + host + '\'' +
                ", port=" + port +
                ", receivingPort=" + receivingPort +
                ", group='" + group + '\'' +
                '}';
    }
}
