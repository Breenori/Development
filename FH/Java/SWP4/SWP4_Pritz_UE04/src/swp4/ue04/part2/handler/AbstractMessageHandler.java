package swp4.ue04.part2.handler;


import swp4.ue04.part2.SharedServerState;

public abstract class AbstractMessageHandler implements MessageHandler {

    protected SharedServerState sharedServerState;

    // every MessageHandler needs the serverstate to interact with clients
    public AbstractMessageHandler(SharedServerState sharedServerState) {
        this.sharedServerState = sharedServerState;
    }
}
