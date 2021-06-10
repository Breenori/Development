package swp4.ue05.part2.ui.model;

import neobio.alignment.PairwiseAlignment;
import swp4.ue05.part2.domain.AlignmentResult;

import java.util.ArrayList;
import java.util.List;

public class AlignmentModel {

    private AlignmentResult currentAlignment;
    private List<AlignmentResult> alignments;

    public AlignmentModel(AlignmentResult currentAlignment, List<AlignmentResult> alignments) {
        this.currentAlignment = currentAlignment;
        this.alignments = alignments;
    }

    public AlignmentModel() {
        this.currentAlignment = null;
        this.alignments = new ArrayList<>();
    }

    public AlignmentResult getCurrentAlignment() {
        return currentAlignment;
    }

    public void setCurrentAlignment(AlignmentResult currentAlignment) {
        this.currentAlignment = currentAlignment;
    }

    public List<AlignmentResult> getAlignments() {
        return alignments;
    }

    public void setAlignments(List<AlignmentResult> alignments) {
        this.alignments = alignments;
    }

    public boolean addAlignment(AlignmentResult pairwiseAlignment) {
        return alignments.add(pairwiseAlignment);
    }

    public boolean removeAlignment(AlignmentResult pairwiseAlignment) {
        return alignments.remove(pairwiseAlignment);
    }
}
