package swp4.ue01.part1.search;

import swp4.ue01.part1.DataCollection.DataCollector;
import java.util.HashMap;
import java.util.Map;


public class BMSearch {

    public static int search(String text, String pattern) {
        return search(text, pattern, 0);
    }
    public static int search(String text, String pattern, int offset) {
        Map<Character, Integer> table = makeOffsetTable(pattern);

        int tLen = text.length();
        int pLen = pattern.length();
        int pos = pLen + offset - 1;
        int foundPos = -1;

        while (pos >= pLen - 1 && pos < tLen && foundPos == -1) {
            int pIndex = 0;

            while (pIndex < pLen && pattern.charAt(pLen - pIndex - 1) == text.charAt(pos - pIndex)) {
                pIndex++;
            }

            if (pIndex == pLen) {
                foundPos = pos - (pLen - 1);
            } else {
                if (table.containsKey(text.charAt(pos - pIndex))) {
                    pos += table.get(text.charAt(pos - pIndex));
                } else {
                    pos += pLen;
                }
            }
        }

        return foundPos;
    }
    public static int search(String text, String pattern, int offset, DataCollector dc) {
        Map<Character, Integer> table = makeOffsetTable(pattern, dc);
        dc.logAssOp(4); // assign table, and also pass the parameters, excluding dc

        int tLen = text.length();
        int pLen = pattern.length();
        int pos = pLen + offset - 1;
        int foundPos = -1;
        dc.logAssOp(4); // above parameters
        dc.logAddOp();


         // While (Exit)
        dc.logLogOp(5);
        dc.logAddOp();
        while (pos >= pLen - 1 && pos < tLen && foundPos == -1) {
            // while
            dc.logLogOp(5);
            dc.logAddOp();

            int pIndex = 0;
            dc.logAssOp(); // pIndex

            //while
            dc.logLogOp(3);
            dc.logAddOp(3);
            dc.logIndOp(2);
            while (pIndex < pLen && pattern.charAt(pLen - pIndex - 1) == text.charAt(pos - pIndex)) {
                //while
                dc.logCharCmp(text.charAt(pos - pIndex),true);
                dc.logLogOp(3);
                dc.logAddOp(3);
                dc.logIndOp(2);
                pIndex++;
                dc.logAddOp();
                dc.logAssOp();
            }

            // while comparison
            if(pIndex < pLen) {
                dc.logCharCmp(text.charAt(pos - pIndex),false);
            }

            dc.logLogOp(); //if
            if (pIndex == pLen) {
                foundPos = pos - (pLen - 1);
                dc.logAssOp(); // foundPos
                dc.logAddOp(2);
            } else {
                dc.logLogOp(); // bloew if
                dc.logAddOp();
                dc.logIndOp();
                if (table.containsKey(text.charAt(pos - pIndex))) {
                    pos += table.get(text.charAt(pos - pIndex));
                    dc.logIndOp(); // pos
                    dc.logAddOp(2);
                    dc.logAssOp();
                } else {
                    pos += pLen; // pos
                    dc.logAddOp();
                    dc.logAssOp();
                }
            }
            dc.logCmp(); // comparison loop
        }

        dc.logAssOp(); // return
        return foundPos;
    }

    private static Map<Character,Integer> makeOffsetTable(String pattern) {
        Map<Character,Integer> table = new HashMap<Character,Integer>();

        for(int i=0; i < pattern.length()-1; i++) {
            table.put(pattern.charAt(i),pattern.length()-1-i);
        }

        return table;
    }
    private static Map<Character,Integer> makeOffsetTable(String pattern, DataCollector dc) {
        Map<Character,Integer> table = new HashMap<Character,Integer>();
        dc.logAssOp();

        dc.logAssOp();
        dc.logLogOp();
        dc.logAddOp();
        for(int i=0; i < pattern.length()-1; i++) {
            dc.logLogOp();
            dc.logAddOp();

            table.put(pattern.charAt(i),pattern.length()-1-i);
            dc.logAssOp();
            dc.logIndOp();
            dc.logAddOp(2);

            dc.logAddOp();
        }

        return table;
    }

}
