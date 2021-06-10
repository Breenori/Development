package swp4.ue05.part2.domain;

import neobio.alignment.PairwiseAlignment;

import java.util.Objects;

public class AlignmentResult {

    private long id;
    private PairwiseAlignment pairwiseAlignment;
    private String sequence1;
    private String sequence2;
    private int match;
    private int mismatch;
    private int gap;
    private int  algorithm;
    private static long currentid = 0;

    public AlignmentResult(PairwiseAlignment pairwiseAlignment, String sequence1, String sequence2, int match, int mismatch, int gap, int algorithm) {
        id = ++currentid;
        this.pairwiseAlignment = pairwiseAlignment;
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

    public PairwiseAlignment getPairwiseAlignment() {
        return pairwiseAlignment;
    }

    public void setPairwiseAlignment(PairwiseAlignment pairwiseAlignment) {
        this.pairwiseAlignment = pairwiseAlignment;
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
        return pairwiseAlignment.toString();
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        AlignmentResult that = (AlignmentResult) o;
        return id == that.id;
    }

    @Override
    public int hashCode() {
        return Objects.hash(id);
    }
}
