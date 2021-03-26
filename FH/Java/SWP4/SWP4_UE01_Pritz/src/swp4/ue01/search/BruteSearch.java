package swp4.ue01.search;

public class BruteSearch {

    public static int search(String text, String pattern, int offset) {

        int pos = offset;
        int tLen = text.length();
        int pLen = pattern.length();
        boolean found = false;

        while(pos>=0 && pos<tLen-pLen+1 && !found)
        {
            int pIndex = 0;
            while(pIndex<pLen && pattern.charAt(pIndex)==text.charAt(pos+pIndex)) {
                pIndex++;
            }

            if(pIndex==pLen)
            {
                return pos;
            }

            pos++;
        }

        return -1;
    }

    public static int search(String text, String pattern) {
        return search(text,pattern,0);
    }
}
