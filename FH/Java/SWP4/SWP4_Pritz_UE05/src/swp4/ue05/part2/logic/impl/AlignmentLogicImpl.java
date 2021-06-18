package swp4.ue05.part2.logic.impl;

import swp4.ue05.part2.logic.AlignmentLogic;
import swp4.ue05.part2.ui.model.AlignmentModel;


public class AlignmentLogicImpl implements AlignmentLogic {
    @Override
    public boolean addAlignment(AlignmentModel model) {
        // only add an alignment if the model and currentalignment is not null
        return model != null && model.getCurrentAlignment() != null && model.addAlignment(model.getCurrentAlignment());
    }

    @Override
    public AlignmentModel getAlignments(AlignmentModel model) {
        return model;
    }

    @Override
    public boolean removeAlignment(AlignmentModel model) {
        // only start removal process if model and currentALignment is not null
        return model != null && model.getCurrentAlignment() != null && model.removeAlignment(model.getCurrentAlignment());
    }

}
