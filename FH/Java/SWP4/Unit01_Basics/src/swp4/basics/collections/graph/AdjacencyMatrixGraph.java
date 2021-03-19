package swp4.basics.collections.graph;

public class AdjacencyMatrixGraph extends Graph {

    private final boolean[][] adjacencyMatrix;

    public AdjacencyMatrixGraph(int noOfVertices) {
        this.adjacencyMatrix = new boolean[noOfVertices][noOfVertices];
    }

    private boolean isValidIndex(int index) {
        return index >= 0 && index <= adjacencyMatrix.length;
    }

    @Override
    public boolean addEdge(int src, int dest) {
        return isValidIndex(src) && isValidIndex(dest) && (this.adjacencyMatrix[src][dest] = true);
    }

    @Override
    public boolean removeEdge(int src, int dest) {
        return isValidIndex(src) && isValidIndex(dest) && !(this.adjacencyMatrix[src][dest] = false);
    }

    @Override
    public boolean hasEdge(int src, int dest) {
        return isValidIndex(src) && isValidIndex(dest) && this.adjacencyMatrix[src][dest];
    }
}
