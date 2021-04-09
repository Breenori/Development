package swp4.ue01.part2.collections.graph;

import swp4.ue01.part2.calculation.BaconIndexCalculator;
import swp4.ue01.part2.collections.MovieSymbolTable;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.AbstractMap;
import java.util.ArrayList;
import java.util.Map.Entry;
import java.util.Random;

public class MovieGraph implements Graph {



    private MovieSymbolTable mst;
    private ArrayList<Entry<Integer,Integer>> adjacencyList;
    private ArrayList<Integer> movieStartIdx;


    public MovieGraph(String filename) {
        this.mst = new MovieSymbolTable();
        this.adjacencyList = new ArrayList<>();
        this.movieStartIdx = new ArrayList<>();

        // open file
        try (BufferedReader bReader = new BufferedReader(new InputStreamReader(new FileInputStream(filename)))) {
            String line;
            int entryNum = 0;

            // read every line
            while((line=bReader.readLine()) != null) {
                // cache the start indices of movies in the adjacencylist.
                movieStartIdx.add(entryNum);
                int movieNum = -1;
                // splits the line into movies + actors
                String[] elements = line.split("/");

                // deal with each new item in the line
                for(int i=0; i < elements.length; i++) {
                    String value = elements[i].strip();

                    // if node with specific value doesn't exist, create it.
                    if(mst.getIndex(value) == -1) {
                        if(i == 0) { // if movie
                            mst.add(value, mst.size(), true);
                            movieNum = mst.size()-1;
                        } else {
                            mst.add(value, mst.size(), false);
                        }

                        // if the new node is a person, also add an edge to the movie (first element in line)
                        if(i != 0) { // person
                            addEdge(mst.size()-1, movieNum);
                            entryNum++;
                        }
                    } else {
                        // if actors or movies already exist, all thats left is to create the edges
                        if(i == 0)
                        {
                            // this shouldn't happen, but just in case. (since every line should be a NEW movie)
                            movieNum = mst.getIndex(value);
                        } else {
                            addEdge(mst.getIndex(value), movieNum);
                            entryNum++;
                        }
                    }
                }
            }
            // finally, add a "cached" entry AFTER all movies are finished. (to have continuous areas between index and index+1)
            movieStartIdx.add(entryNum);
        } catch(IOException e) {
            System.err.println("Could not read file " + filename);
            e.printStackTrace();
        }
        System.out.println("Successfully created graph for "+filename+".");

        // finally, use the graph/adjacencylist to calculate the bacon index.
    }

    @Override
    public boolean addEdge(int src, int dest) {

        // add the edge, so the movie is always the first node
        if(mst.isMovie(src)) {
            return adjacencyList.add(new AbstractMap.SimpleEntry(src,dest));
        } else {
            return adjacencyList.add(new AbstractMap.SimpleEntry(dest,src));
        }
    }

    @Override
    public boolean removeEdge(int src, int dest) {
        if(mst.isMovie(src)) {
            return adjacencyList.remove(new AbstractMap.SimpleEntry(src,dest));
        } else {
            return adjacencyList.remove(new AbstractMap.SimpleEntry(dest,src));
        }
    }

    @Override
    public boolean hasEdge(int src, int dest) {
        if(src == dest) {
            return true;
        }
        return hasEdge(0,adjacencyList.size());
    }

    // determines whether the nodes have an edge between a specific range (speeds up the process significantly, by utilizing movie index caching)
    public boolean hasEdge(int src, int dest, int start, int end) {
        if(src == dest) {
            return true;
        }
        // make sure movie is first node...
        if(mst.isMovie(dest)) {
            int tmp = src;
            src = dest;
            dest = tmp;
        }

        // search in the designated range
        for(int i=start; i < end; i++) {
            if(adjacencyList.get(i).getValue() == dest)
            {
                return true;
            }
        }

        return false;
    }

    // returns a list of actors that are connected to the initial actor via movies
    public ArrayList<Integer> getConnectedActors(int index, ArrayList<Integer> scanned) {
        ArrayList<Integer> values = new ArrayList();

        // if index a movie, terminate.
        if(mst.isMovie(index))
        {
            System.out.println("Specified index is a movie, not an actor. Terminating.");
            return values;
        }

        ArrayList<Integer> allMovies = mst.getMovies();
        // Iterate through all movies, and check if the actor starrs in it
        for(int mi=0; mi<allMovies.size(); mi++) {
            int movieIdx = allMovies.get(mi);
            int mstart = movieStartIdx.get(mi);
            int mend = movieStartIdx.get(mi+1);
            if(hasEdge(index,movieIdx,mstart,mend) && !scanned.contains(movieIdx)) {
                // Then log all actors that play in that movie to the list
                for(int mci=mstart; mci < mend; mci++) {
                    if(adjacencyList.get(mci).getValue() != index)
                    {
                        values.add(adjacencyList.get(mci).getValue());
                    }
                }
                // also, mark the items as scanned.
                scanned.add(movieIdx);
                scanned.add(index);
            }

        }

        // finally return the arraylist
        return values;
    }

    // returns the Bacon-Index for the given actors
    public int getBaconIndex(String name1, String name2) {
        return BaconIndexCalculator.calculateBaconIndex(this, this.mst, name1, name2);
    }

    public void testRandomBacons() {
        // random actors to check if bacon-index seems feasible
        Random rand = new Random();
        for(int i=0; i < 1000; i++) { // Try for 1000 random pairs
            int p1 = 1;//rand.nextInt(mst.size());
            int p2 = 2;//rand.nextInt(mst.size());

            if(mst.isActor(p1) && mst.isActor(p2)) {
                System.out.println("'"+mst.getValue(p1)+"' and '"+mst.getValue(p2)+"':"+BaconIndexCalculator.calculateBaconIndex(this, mst, mst.getValue(p1), mst.getValue(p2)));
            }
        }
    }

}
