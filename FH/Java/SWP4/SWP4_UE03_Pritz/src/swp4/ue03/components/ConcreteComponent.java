package swp4.ue03.components;

import swp4.ue03.profiling.Observer;

import java.util.*;

public abstract class ConcreteComponent implements Component, Comparable<ConcreteComponent> {

    protected int id = 0;
    // Avoid having own Random generator in each component
    protected static Random metricRandomizer = new Random();
    private static Set<String> reservedNames = new HashSet<>();

    // save all observers for each component
    protected Set<Observer> observers = new HashSet<>();

    // a list of all metrics of a component and their current value
    protected Map<String, Object> metrics = new HashMap<>();
    protected Set<String> metricNames = new HashSet<>();
    protected boolean active = false;

    // Updates all values of the current components metrics
    protected abstract void queryMetrics();

    @Override
    public void turnOff() {
        active = false;
    }

    @Override
    public int getId() {
        return id;
    }

    @Override
    public String getName() {
        String[] classPath = this.getClass().getName().split("\\.");
        return classPath[classPath.length-1]+id;
    }

    @Override
    public boolean isActive() {
        return active;
    }

    @Override
    public Set<String> getMetricNames() {
        return metrics.keySet();
    }

    @Override
    public boolean registerMetrics(List<String> names) {
        for(String name : names) {
            if (!Component.metricExists(name)) {
                metrics.put(name, 0);
                reservedNames.add(name);
            } else {
                System.err.println("Failed to initialize" + this + ".");
                metrics.clear();
                return false;
            }
        }
        return true;
    }

    // Notify all observers with the current values
    @Override
    public void notifyObserver() {
        for(Observer obs : observers) {
            obs.update(this, metrics);
        }
    }
    @Override
    public void run() {
        while(active) {
            try {
                // generate new values and send them to the observers every 1 seconds
                queryMetrics();
                notifyObserver();
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }

    @Override
    public void attach(Observer observer) {
        observers.add(observer);
    }

    @Override
    public void detach(Observer observer) {
        observers.remove(observer);
    }

    // Comparable in order to use TreeMaps for sorting later
    @Override
    public int compareTo(ConcreteComponent o) {
        return this.getName().compareTo(o.getName());
    }
}
