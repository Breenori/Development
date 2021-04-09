package swp4.ue01.part2.collections;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

public class MovieSymbolTable {
    // holds all the nodes and their values
    private ArrayList<MovieNode> nodes;
    // holds all indexes for movies (to map them easily later)
    private ArrayList<Integer> movieIdx;
    // Map to store the names of actors/movies to their indices
    private Map<String,Integer> nodeHash;

    private int nodeCount;

    public MovieSymbolTable() {
        nodes = new ArrayList<>();
        nodeHash = new HashMap<>();
        nodeCount = 0;
        movieIdx = new ArrayList<>();
    }

    // adds a new movie or actor to the table
    public void add(String value, int nodeId, boolean isMovie) {
        nodes.add(new MovieNode(value,isMovie));
        nodeHash.put(value,nodeCount);

        // if its a movie, also log its index in the separate arraylist
        if(isMovie) {
            movieIdx.add(nodeId);
        }
        nodeCount++;
    }

    // returns the value for the node of the given nodeId
    public String getValue(int nodeId) {
        return nodes.get(nodeId).getValue();
    }

    // returns the index for the node of the given value
    public int getIndex(String value) {
        return nodeHash.get(value) != null ? nodeHash.get(value) : -1;
    }

    // returns whether a node is a movie or not
    public boolean isMovie(int nodeId) {
        return nodes.get(nodeId).isMovie();
    }

    // returns whether a node is a actor or not
    public boolean isActor(int nodeId) {
        return !nodes.get(nodeId).isMovie();
    }

    // returns the amount of nodes.
    public int size() {
        return nodes.size();
    }

    // returns a list of all movie indices
    public ArrayList<Integer> getMovies() {
        return movieIdx;
    }

}
