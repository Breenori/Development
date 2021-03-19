package swp4.basics.test;

import swp4.basics.collections.graph.AdjacencyMatrixGraph;
import swp4.basics.collections.graph.Graph;

public class GraphTest {
    public static void main(String[] args)
    {
        Graph g = new AdjacencyMatrixGraph(4);
        g.addEdge(1,3);
        g.addEdge(2,3);
        g.addEdge(2,1);

        System.out.println("Graph hasEdge(1, 3): " + g.hasEdge(1,3));
        System.out.println("Graph hasEdge(2, 3): " + g.hasEdge(2,3));
        System.out.println("Graph hasEdge(2, 1): " + g.hasEdge(2,1));
        System.out.println("Graph hasEdge(3, 2): " + g.hasEdge(3,2));

        boolean removed = g.removeEdge(1,3);
        System.out.println("Graph removeEdge(1, 3): " + g.hasEdge(1,3));
        System.out.println("Graph hasEdge(1, 3): " + g.hasEdge(1,3));
    }
}
