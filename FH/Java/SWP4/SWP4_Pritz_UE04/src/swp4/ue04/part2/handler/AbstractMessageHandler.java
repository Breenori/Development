package swp4.ue04.part2.handler;


import swp4.ue04.part2.SharedServerState;

public abstract class AbstractMessageHandler implements MessageHandler {

    protected SharedServerState sharedServerState;

    public AbstractMessageHandler(SharedServerState sharedServerState) {
        this.sharedServerState = sharedServerState;
    }
}
