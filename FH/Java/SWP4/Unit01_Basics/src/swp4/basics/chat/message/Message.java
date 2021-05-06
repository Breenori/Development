package swp4.basics.chat.message;

public class Message {
    private String host;
    private int port;
    private char command;
    private String data;

    public Message(String host, int port, char command, String data) {
        this.host = host;
        this.port = port;
        this.command = command;
        this.data = data;
    }

    public String getHost() {
        return host;
    }
    public int getPort() {
        return port;
    }
    public char getCommand() {
        return command;
    }
    public String getData() {
        return data;
    }

    @Override
    public String toString() {
        return "Message{" +
                "host='" + host + '\'' +
                ", port=" + port +
                ", command=" + command +
                ", data='" + (data != null ? data.trim() : "<NO DATA>") + '\'' +
                '}';
    }
}
