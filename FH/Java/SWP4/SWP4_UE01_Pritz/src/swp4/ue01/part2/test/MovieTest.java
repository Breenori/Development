package swp4.ue01.part2.test;

import swp4.ue01.part2.collections.graph.MovieGraph;

import java.io.BufferedReader;
import java.io.InputStreamReader;

public class MovieTest {
    public static void main(String[] args) {
        MovieGraph m = new MovieGraph("movies.txt");

        //m.testRandomBacons();

        String name1 = " ";
        String name2 = " ";
        try {

            System.out.println("Press enter without content to exit.");
            // loop as long as
            while(!name1.isEmpty() && !name2.isEmpty()) {
                System.out.println("Please enter the first actors name:");
                name1 = readInputFromSystemIn();

                if(!name1.isEmpty()) {
                    System.out.println("Please enter the second actors name:");
                    name2 = readInputFromSystemIn();
                }

                if(!name1.isEmpty() && !name2.isEmpty()) {
                    System.out.println("Their bacon-index is: "+m.getBaconIndex(name1,name2));
                } else {
                    System.out.println("Enter detected. Exiting...");
                }
                System.out.println();
            }
        } catch(Exception e) {
            System.err.println("Couldn't read from console.");
            e.printStackTrace();
        }

    }

    public static String readInputFromSystemIn() throws Exception {
        BufferedReader reader = new BufferedReader( new InputStreamReader( System.in ) );
        return reader.readLine();
    }

}


