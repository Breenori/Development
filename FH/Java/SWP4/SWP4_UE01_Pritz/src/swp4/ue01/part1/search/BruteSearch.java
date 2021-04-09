package swp4.ue01.part1.search;

import swp4.ue01.part1.DataCollection.DataCollector;

public class BruteSearch {

    public static int search(String text, String pattern) {
        return search(text,pattern,0);
    }
    public static int search(String text, String pattern, int offset) {
        if(pattern.isEmpty() || text.isEmpty())
        {
            return -1;
        }

        int foundPos = -1;
        int pos = offset;
        int tLen = text.length();
        int pLen = pattern.length();

        while(pos>=0 && pos<tLen-pLen+1 && foundPos == -1)
        {
            int pIndex = 0;

            while(pIndex<pLen && pattern.charAt(pIndex)==text.charAt(pos+pIndex)) {
                pIndex++;
            }

            if(pIndex==pLen)
            {
                foundPos = pos;
            }

            pos++;
        }

        return foundPos;
    }
    public static int search(String text, String pattern, int offset, DataCollector dc) {
        if(pattern.isEmpty() || text.isEmpty())
        {
            return -1;
        }
        dc.logAssOp(3); // parameters, excluding dc

        int foundPos = -1;
        int pos = offset;
        int tLen = text.length();
        int pLen = pattern.length();
        dc.logAssOp(4); // above parameters

        // log operations for exit statement (not executed within while)
        dc.logLogOp(4);
        dc.logAddOp(2);
        while(pos>=0 && pos<tLen-pLen+1 && foundPos == -1)
        {
            dc.logLogOp(4);
            dc.logAddOp(2);

            int pIndex = 0;
            dc.logAssOp();

            // log operations for exit of while statement (not executed within while)
            dc.logLogOp(3);
            dc.logIndOp(2);
            dc.logAddOp();
            while(pIndex<pLen && pattern.charAt(pIndex)==text.charAt(pos+pIndex)) {
                dc.logCharCmp(text.charAt(pos+pIndex),true);
                pIndex++;
                // while statement
                dc.logLogOp(3);
                dc.logIndOp(2);
                dc.logAddOp(2); // once in while statement, once for pIndex
                dc.logAssOp();
            }

            dc.logCmp(); // if
            if(pIndex==pLen)
            {
                foundPos = pos;
                dc.logAssOp(); // foundPos
            }

            if(pIndex < pattern.length()) {
                // not counted in dc, due to the fact that this function caused the need for the if statement
                dc.logCharCmp(text.charAt(pos+pIndex),false);
            }


            dc.logAddOp(); // pos
            dc.logAssOp();
            pos++;
        }


        dc.logAssOp(); // return value
        return foundPos;
    }
}
