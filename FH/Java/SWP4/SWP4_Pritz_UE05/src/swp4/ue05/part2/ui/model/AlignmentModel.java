package swp4.ue05.part2.ui.model;

import swp4.ue05.part2.domain.AlignmentItem;

import java.util.ArrayList;
import java.util.List;

public class AlignmentModel {

    private AlignmentItem currentAlignment;
    private List<AlignmentItem> alignments;

    public AlignmentModel(AlignmentItem currentAlignment, List<AlignmentItem> alignments) {
        this.currentAlignment = currentAlignment;
        this.alignments = alignments;
    }

    public AlignmentModel() {
        this.currentAlignment = null;
        this.alignments = new ArrayList<>();
    }

    public AlignmentItem getCurrentAlignment() {
        return currentAlignment;
    }

    public void setCurrentAlignment(AlignmentItem currentAlignment) {
        this.currentAlignment = currentAlignment;
    }

    public List<AlignmentItem> getAlignments() {
        return alignments;
    }

    public void setAlignments(List<AlignmentItem> alignments) {
        this.alignments = alignments;
    }

    public boolean addAlignment(AlignmentItem pairwiseAlignment) {
        return alignments.add(pairwiseAlignment);
    }

    public boolean removeAlignment(AlignmentItem pairwiseAlignment) {
        return alignments.remove(pairwiseAlignment);
    }
}
