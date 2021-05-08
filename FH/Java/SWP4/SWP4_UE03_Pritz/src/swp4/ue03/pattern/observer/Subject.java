package swp4.ue03.pattern.observer;

public interface Subject {
    void attach(Observer observer);
    void detach(Observer observer);
    void notifyObserver(long noteId);
}
