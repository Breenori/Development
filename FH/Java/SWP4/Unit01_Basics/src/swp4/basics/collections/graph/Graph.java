package swp4.basics.collections.graph;

public abstract class Graph {

    public abstract boolean addEdge(int src, int dest);
    public abstract boolean removeEdge(int src, int dest);
    public abstract boolean hasEdge(int src, int dest);

}
