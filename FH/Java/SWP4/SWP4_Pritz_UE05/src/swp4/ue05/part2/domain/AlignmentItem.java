package swp4.ue05.part2.domain;

import java.util.Objects;

public class AlignmentItem {

    // an alignmentItem contains all inserted values and a unique id
    private long id;
    private String sequence1;
    private String sequence2;
    private int match;
    private int mismatch;
    private int gap;
    private int  algorithm;
    private static long currentid = 0;

    public AlignmentItem(String sequence1, String sequence2, int match, int mismatch, int gap, int algorithm) {
        id = ++currentid;
        this.sequence1 = sequence1;
        this.sequence2 = sequence2;
        this.match = match;
        this.mismatch = mismatch;
        this.gap = gap;
        this.algorithm = algorithm;
    }


    public long getId() {
        return id;
    }

    public void setId(long id) {
        this.id = id;
    }

    public String getSequence1() {
        return sequence1;
    }

    public void setSequence1(String sequence1) {
        this.sequence1 = sequence1;
    }

    public String getSequence2() {
        return sequence2;
    }

    public void setSequence2(String sequence2) {
        this.sequence2 = sequence2;
    }

    public int getMatch() {
        return match;
    }

    public void setMatch(int match) {
        this.match = match;
    }

    public int getMismatch() {
        return mismatch;
    }

    public void setMismatch(int mismatch) {
        this.mismatch = mismatch;
    }

    public int getGap() {
        return gap;
    }

    public void setGap(int gap) {
        this.gap = gap;
    }

    public int getAlgorithm() {
        return algorithm;
    }

    public void setAlgorithm(int algorithm) {
        this.algorithm = algorithm;
    }

    @Override
    public String toString() {
        // show the alignments id, the first 10 characters of each sequence as well as the scoring
        return "Alignment "+id+": "+(sequence1.length() <= 10 ? sequence1 : sequence1.substring(0,10))  + "::" + (sequence2.length() <= 10 ? sequence2 : sequence2.substring(0,10)) + " " + match + "/"+mismatch+"/"+gap;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        AlignmentItem that = (AlignmentItem) o;
        return id == that.id;
    }

    @Override
    public int hashCode() {
        return Objects.hash(id);
    }
}
