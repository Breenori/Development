package swp4.ue05.part2.ui.view.impl;

import swp4.ue05.part2.domain.AlignmentResult;

import javax.swing.*;
import java.util.List;

public class AlignmentListModel extends AbstractListModel<AlignmentResult> {

    private List<AlignmentResult> alignments;

    public AlignmentListModel(List<AlignmentResult> alignments) {
        this.alignments = alignments;
    }

    @Override
    public int getSize() {
        return alignments.size();
    }

    @Override
    public AlignmentResult getElementAt(int index) {
        if(index < getSize()) {
            return alignments.get(index);
        }
        return null;
    }
}
