package swp4.basics.collections.graph;

public class AdjacencyMatrixGraph implements Graph {

    private boolean[][] adjacencyMatrix;

    public AdjacencyMatrixGraph( int noOfVertices ) {
        this.adjacencyMatrix = new boolean[noOfVertices][noOfVertices];
    }


    @Override
    public boolean addEdge(int src, int dest) {
        if( src >= adjacencyMatrix.length || dest >= adjacencyMatrix.length ) {
            return false;
        }
        return this.adjacencyMatrix[src][dest] = true;
    }

    @Override
    public boolean removeEdge(int src, int dest) {
        if( src >= adjacencyMatrix.length || dest >= adjacencyMatrix.length ) {
            return false;
        }
        return !(this.adjacencyMatrix[src][dest] = false);
    }

    @Override
    public boolean hasEdge(int src, int dest) {
        if( src >= adjacencyMatrix.length || dest >= adjacencyMatrix.length ) {
            return false;
        }
        return this.adjacencyMatrix[src][dest]; //this.adjacencyMatrix[src][dest] == true;
    }
}
