package swp4.ue04.part2.process.impl;


import swp4.ue04.part2.SharedServerState;
import swp4.ue04.part2.handler.MessageHandler;
import swp4.ue04.part2.message.Message;
import swp4.ue04.part2.process.MessageProcessor;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class MessageProcessorImpl implements MessageProcessor {

    private SharedServerState sharedServerState;
    private List<MessageHandler> handlerList = Collections.synchronizedList(new ArrayList<>());

    public MessageProcessorImpl(SharedServerState sharedServerState) {
        this.sharedServerState = sharedServerState;
    }

    @Override
    public void addHandler(MessageHandler handler) {
        handlerList.add(handler);
    }

    @Override
    public void removeHandler(MessageHandler handler) {
        handlerList.remove(handler);
    }

    // Periodisch nachschauen ob es neue nachrichten gibt, und je alle messagehandlers durchprobieren ob wer auswerten kann
    @Override
    public void run() {
        Message message;
        while((message = sharedServerState.getReceiverMessageBuffer().get()) != null) {
            try {
                sharedServerState.getReceiverMessageBuffer().delete(message);
                System.out.println("MessageProcessor received message: "+message);

                for(MessageHandler handler : handlerList) {
                    if(handler.handle(message)) {
                        System.out.println("Handler "+handler+" handled message: "+message);
                    }
                }

                Thread.sleep(200);
            } catch(InterruptedException e) {}
        }
    }
}
