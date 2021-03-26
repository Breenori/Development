package swp4.basics.collections.graph;

public interface Graph {

    boolean addEdge( int src, int dest );

    boolean removeEdge( int src, int dest );

    boolean hasEdge( int src, int dest );

}
