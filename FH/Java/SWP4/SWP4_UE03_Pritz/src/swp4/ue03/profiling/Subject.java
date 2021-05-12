package swp4.ue03.profiling;

public interface Subject {

    void attach(Observer observer);
    void detach(Observer observer);
    void notifyObserver();
}
