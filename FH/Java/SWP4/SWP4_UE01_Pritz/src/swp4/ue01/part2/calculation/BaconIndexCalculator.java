package swp4.ue01.part2.calculation;

import swp4.ue01.part2.collections.MovieSymbolTable;
import swp4.ue01.part2.collections.graph.MovieGraph;

import java.util.ArrayList;

public class BaconIndexCalculator {
    // Calculates the BaconIndex between two actors using the given Graph and MovieSymboltable
    public static int calculateBaconIndex(MovieGraph graph, MovieSymbolTable mst, String name1, String name2) {
        // if names dont exist or aren't actors, return -1
        if(mst.getIndex(name1)==-1 || mst.getIndex(name2)==-1 || mst.isMovie(mst.getIndex(name1)) || mst.isMovie(mst.getIndex(name2))) {
            System.out.println("Couldn't calculate Bacon index, since the given names couldn't be found!");
            return -1;
        }

        int targetActorIndex = mst.getIndex(name2);

        if(mst.getIndex(name1) == targetActorIndex) {
            return 0;
        }

        // list all nodes (movies AND actors) that have already been scanned, to avoid cycles (or additional work)
        ArrayList<Integer> scanned = new ArrayList();
        int baconIndex = 0;

        // Arraylist to store all the current actors, from which the scan goes forward.
        // Start scan from actor with name1
        ArrayList<Integer> actors = new ArrayList();
        actors.add(mst.getIndex(name1));
        do {
            // hold initial size, to avoid looping past the original dataset.
            int initialSize = actors.size();
            // scan from all nodes inside <actors>
            for(int i=0; i < initialSize; i++) {
                int idx = actors.get(i);
                if(mst.isActor(idx)) {
                    // get all actors that starred in the same movies
                    ArrayList<Integer> tmpNbList = graph.getConnectedActors(idx, scanned);
                    scanned.add(idx);

                    // add the neighbors to the actors arraylist, so they will be scanned later.
                    tmpNbList.forEach(actors::add);
                }

                // remove actors that have already been scanned
                actors.remove(i);
                initialSize--;
            }

            // after each iteration increase bacon-index (= amount of movies distance from initial actor)
            baconIndex++;
        } while(!actors.isEmpty() && !actors.contains(targetActorIndex));

        // if all nodes have been searched (not found) or index has been determined, return value
        return actors.isEmpty() ? -1 : baconIndex;
    }
}
