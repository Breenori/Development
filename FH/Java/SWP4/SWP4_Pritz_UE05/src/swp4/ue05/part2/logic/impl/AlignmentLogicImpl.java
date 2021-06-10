package swp4.ue05.part2.logic.impl;

import neobio.alignment.PairwiseAlignment;
import swp4.ue05.part2.domain.AlignmentResult;
import swp4.ue05.part2.logic.AlignmentLogic;
import swp4.ue05.part2.ui.model.AlignmentModel;

import java.util.Iterator;

public class AlignmentLogicImpl implements AlignmentLogic {
    @Override
    public boolean addAlignment(AlignmentModel model) {
        return model != null && model.getCurrentAlignment() != null && model.addAlignment(model.getCurrentAlignment());
    }

    @Override
    public AlignmentModel getAlignments(AlignmentModel model) {
        return model;
    }

    @Override
    public boolean removeAlignment(AlignmentModel model) {
        return model != null && model.getCurrentAlignment() != null && model.removeAlignment(model.getCurrentAlignment());
    }

    @Override
    public AlignmentModel updateAlignment(AlignmentModel model) {
        if(model.getAlignments().contains(model.getCurrentAlignment()))
        {
            Iterator<AlignmentResult> alignmentIterator = model.getAlignments().iterator();
            while(alignmentIterator.hasNext());
            {
                alignmentIterator.next();
            }
        }
        return null;
    }
}
