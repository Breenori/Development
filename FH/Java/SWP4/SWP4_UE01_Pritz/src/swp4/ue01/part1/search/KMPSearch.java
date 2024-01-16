package swp4.ue01.part1.search;

import swp4.ue01.part1.DataCollection.DataCollector;

public class KMPSearch {


    public static int search(String text, String pattern, int offset, DataCollector dc) {
        dc.logAssOp(3); // parameters, excluding dc

        if(pattern.isEmpty() || text.isEmpty())
        {
            return -1;
        }

        int[] lp = getLeapTbl(pattern, dc);
        int pos = offset;
        int pIndex = 0;
        dc.logAssOp(3); // variables above

        dc.logLogOp(3); // while (exit)
        while(pos < text.length() && pIndex < pattern.length()) {
            dc.logLogOp(3); // while

            dc.logLogOp(2); // while (/exit)
            dc.logIndOp(2);
            while(pIndex >= 0 && text.charAt(pos) != pattern.charAt(pIndex)) {
                dc.logLogOp(2); // while
                dc.logIndOp(2);
                dc.logCharCmp(text.charAt(pos),true);
                pIndex = lp[pIndex];
                dc.logAssOp();
                dc.logIndOp();
            }

            if(pIndex < pattern.length()) {
                dc.logCharCmp(text.charAt(pos),false);
            }

            pos++;
            pIndex++;
            dc.logAssOp(2);
            dc.logAddOp(2);

            dc.logCmp();
        }

        dc.logLogOp();
        dc.logAddOp(1);
        dc.logAssOp();

        return pIndex==pattern.length() ? pos - pattern.length() : -1;
    }
    public static int search(String text, String pattern, int offset) {
        if(pattern.isEmpty() || text.isEmpty())
        {
            return -1;
        }

        int[] lp = getLeapTbl(pattern);
        int pos_text = offset;
        int pos_pattern = 0;

        while(pos_text < text.length() && pos_pattern < pattern.length()) {
            while(pos_pattern >= 0 && text.charAt(pos_text) != pattern.charAt(pos_pattern)) {
                pos_pattern = lp[pos_pattern];
            }

            pos_text++;
            pos_pattern++;
        }

        return pos_pattern==pattern.length() ? pos_text - pattern.length() : -1;
    }
    public static int search(String text, String pattern){
        return search(text,pattern,0);
    }


    static int[] getLeapTbl(String pattern) {
        if(pattern.isEmpty()) {
            return null;
        }

        int[] leapTbl = new int[pattern.length()];
        int pIndex = 0;
        int prefixSize = -1;

        leapTbl[0] = prefixSize;
        while(pIndex < pattern.length()) {
            while(prefixSize >= 0 && pattern.charAt(pIndex) != pattern.charAt(prefixSize)) {
                prefixSize = leapTbl[prefixSize];
            }

            pIndex++;
            prefixSize++;
            if(pIndex < pattern.length()) {
                leapTbl[pIndex] = prefixSize;
            }
        }

        return leapTbl;
    }
    static int[] getLeapTbl(String pattern, DataCollector dc) {
        if(pattern.isEmpty()) {
            return null;
        }

        dc.logAssOp(2); // parameters

        int[] leapTbl = new int[pattern.length()];
        int pIndex = 0;
        int prefixSize = -1;
        dc.logAssOp(3);

        leapTbl[0] = prefixSize;
        dc.logIndOp();
        dc.logAssOp();

        dc.logLogOp();
        while(pIndex < pattern.length()) {
            dc.logLogOp();

            dc.logLogOp(2);
            dc.logIndOp(2);
            while(prefixSize >= 0 && pattern.charAt(pIndex) != pattern.charAt(prefixSize)) {
                dc.logLogOp(2);
                dc.logIndOp(2);

                prefixSize = leapTbl[prefixSize];
                dc.logAssOp();
                dc.logIndOp();
            }

            pIndex++;
            prefixSize++;
            dc.logAssOp(2);
            dc.logAddOp(2);

            dc.logLogOp();
            if(pIndex < pattern.length()) {
                leapTbl[pIndex] = prefixSize;
                dc.logIndOp();
                dc.logAssOp();
            }
        }

        dc.logAssOp();
        return leapTbl;
    }
}
