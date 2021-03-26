package swp4.ue01.search;

import java.util.Collection;
import java.util.HashMap;
import java.util.Map;


public class BMSearch {
    public static int search(String text, String pattern, int offset) {
        Map<Character,Integer> table = makeOffsetTable(pattern);

        int tLen = text.length();
        int pLen = pattern.length();
        int pos = pLen+offset-1;
        boolean found = false;


        while(pos>=pLen-1 && pos<tLen && !found) {

            int pIndex = 0;
            while (pIndex < pLen && pattern.charAt(pLen-pIndex-1) == text.charAt(pos - pIndex)) {
                pIndex++;
            }

            if (pIndex == pLen) {
                return pos-(pLen-1);
            } else {
                if(table.containsKey(text.charAt(pos-pIndex))){
                    pos += table.get(text.charAt(pos-pIndex));
                } else {
                    pos += pLen;
                }
            }
        }

        return -1;
    }

    private static Map<Character,Integer> makeOffsetTable(String pattern) {
        Map<Character,Integer> table = new HashMap<Character,Integer>();

        for(int i=0; i < pattern.length()-1; i++) {
            table.put(pattern.charAt(i),pattern.length()-1-i);
        }

        return table;
    }

}
