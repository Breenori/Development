package swp4.ue05.part2.ui.view.impl;

import swp4.ue05.part2.domain.AlignmentItem;

import javax.swing.*;
import java.util.List;

public class AlignmentListModel extends AbstractListModel<AlignmentItem> {

    private List<AlignmentItem> alignments;

    public AlignmentListModel(List<AlignmentItem> alignments) {
        this.alignments = alignments;
    }

    @Override
    public int getSize() {
        return alignments.size();
    }

    @Override
    public AlignmentItem getElementAt(int index) {
        if(index < getSize()) {
            return alignments.get(index);
        }
        return null;
    }
}
