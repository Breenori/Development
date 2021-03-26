package swp4.ue01.test;

import swp4.ue01.search.BMSearch;
import swp4.ue01.search.BruteSearch;

public class SearchTest {
    public static void main(String[] args) {
        int pos1 = BruteSearch.search("Ich verkaufe Bananen.", "Bananen.");
        System.out.println(pos1);

        int pos2 = BMSearch.search("Ich verkaufe Bananen.", "Bananen.", 0);
        System.out.println(pos2);
    }
}
