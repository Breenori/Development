package swp4.basics.collections.graph;

import swp4.basics.collections.impl.SingleLinkedList;

public class AdjacencyListGraph implements Graph {

    private SingleLinkedList[] adjacencyList;

    public AdjacencyListGraph( int noOfVertices ) {
        this.adjacencyList = new SingleLinkedList[ noOfVertices ];
    }


    @Override
    public boolean addEdge(int src, int dest) {
        if( src >= adjacencyList.length || dest >= adjacencyList.length ) {
            return false;
        }
        if( this.adjacencyList[src] == null ) {
            this.adjacencyList[src] = new SingleLinkedList();
        }
        this.adjacencyList[src].append( dest );
        return this.adjacencyList[src].getLastElement().equals( dest );
    }

    @Override
    public boolean removeEdge(int src, int dest) {
        if( src >= adjacencyList.length || dest >= adjacencyList.length ) {
            return false;
        }
        return adjacencyList[src] != null ? adjacencyList[src].remove( dest ) : false;
    }

    @Override
    public boolean hasEdge(int src, int dest) {
        if( src >= adjacencyList.length || dest >= adjacencyList.length ) {
            return false;
        }
        return this.adjacencyList[src] != null ? this.adjacencyList[src].contains( dest ) : false;
    }

}
