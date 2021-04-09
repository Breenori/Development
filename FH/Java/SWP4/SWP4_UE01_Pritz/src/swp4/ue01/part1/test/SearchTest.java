package swp4.ue01.part1.test;

import swp4.ue01.part1.DataCollection.DataCollector;
import swp4.ue01.part1.search.BMSearch;
import swp4.ue01.part1.search.BruteSearch;
import swp4.ue01.part1.search.KMPSearch;

import java.util.Random;

public class SearchTest {
    public static void main(String[] args) {
        normalTest();
        //emptyTest();
        //binaryTest();
        //baseTest();
        //aminoTest();
        //asciiTest();
    }

    static String getRandomText(int length, int chars) {
        String text="";
        Random r = new Random();
        for(int i=0; i < length; i++)
        {
            text+=(char)r.nextInt(chars);
        }
        return text;
    }

    static void normalTest() {
        int pos1 = BruteSearch.search("Das ist ein Text!", "Text");
        System.out.println("Pattern found at position "+pos1+".");

        int pos2 = BMSearch.search("Das ist ein Text!", "Text");
        System.out.println("Pattern found at position "+pos2+".");

        int pos3 = KMPSearch.search("Das ist ein Text!", "Text");
        System.out.println("Pattern found at position "+pos3+".");
    }
    static void emptyTest() {
        int pos1 = BruteSearch.search("Das ist ein Text!", "");
        System.out.println("Pattern found at position "+pos1+".");

        int pos2 = BMSearch.search("", "Text");
        System.out.println("Pattern found at position "+pos2+".");

        int pos3 = KMPSearch.search("", "");
        System.out.println("Pattern found at position "+pos3+".");
    }

    static void binaryTest() {
        DataCollector dc1 = new DataCollector();
        DataCollector dc2 = new DataCollector();
        DataCollector dc3 = new DataCollector();

        for(int len=10; len <= 1000; len*=10) {
            for(int i=0; i < 1000; i++) {
                String text = getRandomText(len, 2);
                String pattern = getRandomText(10,2);

                int pos1 = BruteSearch.search(text, pattern, 0, dc1);
                int pos2 = BruteSearch.search(text, pattern, 0, dc1);
                int pos3 = BruteSearch.search(text, pattern, 0, dc1);
            }
            dc1.writeToFile("datacollector/BF_binary_"+len+".csv");
            dc2.writeToFile("datacollector/BM_binary_"+len+".csv");
            dc3.writeToFile("datacollector/KMP_binary_"+len+".csv");
        }


    }
    static void baseTest() {
        DataCollector dc1 = new DataCollector();
        DataCollector dc2 = new DataCollector();
        DataCollector dc3 = new DataCollector();

        for(int len=10; len <= 1000; len*=10) {
            for(int i=0; i < 1000; i++) {
                String text = getRandomText(len, 2);
                String pattern = getRandomText(10,2);

                int pos1 = BruteSearch.search(text, pattern, 0, dc1);
                int pos2 = BruteSearch.search(text, pattern, 0, dc2);
                int pos3 = BruteSearch.search(text, pattern, 0, dc3);
            }
            dc1.writeToFile("datacollector/BF_basepair_"+len+".csv");
            dc2.writeToFile("datacollector/BM_basepair_"+len+".csv");
            dc3.writeToFile("datacollector/KMP_basepair_"+len+".csv");
        }

    }
    static void aminoTest() {
        DataCollector dc1 = new DataCollector();
        DataCollector dc2 = new DataCollector();
        DataCollector dc3 = new DataCollector();

        for(int len=10; len <= 1000; len*=10) {
            for(int i=0; i < 1000; i++) {
                String text = getRandomText(len, 2);
                String pattern = getRandomText(10,2);

                int pos1 = BruteSearch.search(text, pattern, 0, dc1);
                int pos2 = BruteSearch.search(text, pattern, 0, dc2);
                int pos3 = BruteSearch.search(text, pattern, 0, dc3);
            }
            dc1.writeToFile("datacollector/BF_amino_"+len+".csv");
            dc2.writeToFile("datacollector/BM_amino_"+len+".csv");
            dc3.writeToFile("datacollector/KMP_amino_"+len+".csv");
        }

    }
    static void asciiTest() {
        DataCollector dc1 = new DataCollector();
        DataCollector dc2 = new DataCollector();
        DataCollector dc3 = new DataCollector();

        for(int len=10; len <= 1000; len*=10) {
            for(int i=0; i < 1000; i++) {
                String text = getRandomText(len, 2);
                String pattern = getRandomText(10,2);

                int pos1 = BruteSearch.search(text, pattern, 0, dc1);
                int pos2 = BruteSearch.search(text, pattern, 0, dc2);
                int pos3 = BruteSearch.search(text, pattern, 0, dc3);
            }
            dc1.writeToFile("datacollector/BF_ascii_"+len+".csv");
            dc2.writeToFile("datacollector/BM_ascii_"+len+".csv");
            dc3.writeToFile("datacollector/KMP_ascii_"+len+".csv");
        }

    }

}
