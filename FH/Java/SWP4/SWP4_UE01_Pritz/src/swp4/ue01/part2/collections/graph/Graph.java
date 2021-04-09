package swp4.ue01.part2.collections.graph;

public interface Graph {

    boolean addEdge( int src, int dest );

    boolean removeEdge( int src, int dest );

    boolean hasEdge( int src, int dest );

}
